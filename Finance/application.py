import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd, getprices

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# IEX API KEY pk_708275d414d844c39cf11b5f61988b94


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # gettting user data from database
    rows = db.execute(
        "SELECT symbol, name, shares FROM stocks JOIN StocksUsers ON stocks.id = StocksUsers.stock WHERE StocksUsers.user = ? AND shares > 0", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # getting list of stock symbols to query their current prices
    symbols = []
    for row in rows:
        symbols.append(row["symbol"])

    prices = getprices(symbols)

    # calculating total price of user's all stocks shares
    total = cash
    for row in rows:
        total = total + (row["shares"] * prices[row["symbol"]])

    # rendering index template
    return render_template("index.html", rows=rows, cash=cash, total=total, prices=prices)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # render buy template if the user is visiting this route with GET method
    if request.method == "GET":
        return render_template("buy.html")

    # getting form data and running some error checking
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    if lookup(symbol) == None:
        return apology("INVALID SYMBOL")

    if shares.isdecimal():
        if int(shares) < 1:
            return apology("INVALID SHARES")
    else:
        return apology("INVALID SHARES")

    # calculating total cost of shares to check if user can afford it
    stock = lookup(symbol)
    cash = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    total = int(shares) * stock["price"]

    if total > int(cash):
        return apology("NOT ENOUGH CASH")

    # adding record to stocks table
    if len(db.execute("SELECT * FROM stocks WHERE name = ? AND symbol = ?", stock["name"], stock["symbol"])) != 1:
        stockid = db.execute("INSERT INTO stocks (name, symbol) VALUES (?, ?)", stock["name"], stock["symbol"])
        # recording the buying process
        db.execute("INSERT INTO transactions (user, stock, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], stockid, int(shares), stock["price"], str(datetime.now()))    
    else:
        # recording the buying process
        stockid = db.execute("SELECT * FROM stocks WHERE name = ? AND symbol = ?", stock["name"], stock["symbol"])[0]["id"]
        db.execute("INSERT INTO transactions (user, stock, shares, price, timestamp) VALUES (?, ?, ?, ?, ?)",
                   session["user_id"], stockid, int(shares), stock["price"], str(datetime.now()))

    # updating user cash
    cash = int(cash) - total
    db.execute("UPDATE users SET cash = ? WHERE id = ?", str(cash), session["user_id"])

    # updating user's number of shares
    stockcheck = db.execute("SELECT * FROM StocksUsers WHERE user = ? AND stock = ?", session["user_id"], stockid)
    if len(stockcheck) == 1:
        db.execute("UPDATE StocksUsers SET shares = ? WHERE user = ? and stock = ?",
                   (stockcheck[0]["shares"]+int(shares)), session["user_id"], stockid)
    else:
        db.execute("INSERT INTO StocksUsers (user, stock, shares) VALUES (?, ?, ?)", session["user_id"], stockid, shares)

    # redirect user to index page
    flash("Bought!")
    return redirect(url_for("index"))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute(
        "SELECT symbol, shares, price, timestamp FROM Transactions JOIN stocks ON Transactions.stock=stocks.id WHERE user=?", session["user_id"])

    return render_template("history.html", rows=rows)
    

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    symbol = request.form.get("symbol")

    if lookup(symbol) == None:
        return apology("INVALID SYMBOL")
    else:
        return render_template("quoted.html", quote=lookup(symbol))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    # Assigning user inputs to variables
    username = request.form.get("username")
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if not username or not password or password != confirmation:     # Checking for a valid password
        return apology("PASSWORDS DONT MATCH")
    else:     # Checking if username already exists
        duplicant = db.execute("SELECT username FROM users WHERE username = ?", username)
        if len(duplicant) == 1:
            return apology("USERNAME ALREADY EXISTS")

    # registering user
    hashed_password = generate_password_hash(password)
    new_user = db.execute("INSERT INTO users(username, hash) VALUES (?, ?)", username, hashed_password)

    # Forget any user_id
    session.clear()

    # Remember which user has logged in
    session["user_id"] = new_user

    # returning user to login route
    flash("Registered successfully!")
    return redirect(url_for("index"))


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # rendering sell template
    if request.method == "GET":
        stocks = db.execute(
            "SELECT symbol FROM stocks JOIN StocksUsers ON StocksUsers.stock=stocks.id WHERE StocksUsers.user = ?", session["user_id"])
        return render_template("sell.html", stocks=stocks)

    # getting user's inputs
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    # running some error checking
    if symbol == None:
        return apology("INVALID SYMBOL")

    if int(shares) < 1:
        return apology("INVALID SHARES")

    sharesnum = db.execute("SELECT shares FROM StocksUsers JOIN stocks ON stocks.id=StocksUsers.stock WHERE symbol = ?", symbol)
    if int(shares) > sharesnum[0]["shares"]:
        return apology("NOT ENOUGH SHARES")

    # recording transaction and updating user's data
    stock = db.execute("SELECT id FROM stocks WHERE symbol = ?", symbol)[0]["id"]
    db.execute("INSERT INTO Transactions (user, stock, shares, price, timestamp) VALUES(?, ?, ?, ?, ?)",
               session["user_id"], stock, -(int(shares)), lookup(symbol)["price"], str(datetime.now()))
    db.execute("UPDATE StocksUsers SET shares=? WHERE user=? AND stock=?",
               (int(sharesnum[0]["shares"])-int(shares)), session["user_id"], stock)

    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[0]["cash"]
    db.execute("UPDATE users SET cash = ? WHERE id = ?", (cash + (int(shares) * lookup(symbol)["price"])), session["user_id"])

    flash("Sold!")
    return redirect(url_for("index"))


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():
    if request.method == "POST":
        # Getting form data
        currentpassword = request.form.get("currentpassword")
        newpassword = request.form.get("newpassword")
        confirmpassword = request.form.get("confirmpassword")

        # running some error checking
        if newpassword != confirmpassword:
            return apology("Passwords must match!")

        password = db.execute("SELECT hash FROM users WHERE id=?", session["user_id"])
        if not check_password_hash(password[0]["hash"], currentpassword):
            return apology("Wrong password!")

        # updating password
        db.execute("Update users SET hash=? WHERE id=?", generate_password_hash(newpassword), session["user_id"])
        flash("Password updated!")
        return redirect(url_for("index"))

    return render_template("account.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
