import React from 'react'
import ProjectCard from './ProjectCard';

class Projects extends React.Component {
  render(){
    return(
      <div className="section projects">
      <h2>Projects</h2>
      <div className="row">
        <ProjectCard
          name={"CS50 Finance"}
          details={"CS50X week 9 project, Finance. Users can create accounts to start query stock quotes and get realtime information from IEX api. Users can also buy and sell quotes. Users also able to view all transactions and update their account information."}
          tools={"HTML. CSS. Python. Flask. SQLite"}
        />
        <ProjectCard
          name={"Maily"}
          details={"CS50W2020 week 5 project. Maily is a front-end email client where user can create account, send emails, reply to emails, and archive or unarchive emails. All mails are stored inside the project database. Mails are sent, recieved and updated using the application API."}
          tools={"HTML. CSS. JavaScript. Python. Django. SQLite"}
        />
        <ProjectCard
          name={"Hangman"}
          details={"As part of Kalbonyan Almarsos program and The Modern JavaScript Bootcamp by Andrew Mead, I've built, Hangman, a word guessing game."}
          tools={"HTML. CSS. ES6. Babel. Webpack"}
        />
        <ProjectCard
          name={"Sir Magdi Yakoup"}
          details={"CS50W2018 week 1 project: Its the first project I've ever worked on. A simple portfolio website for Dr.Magdi Yakoup."}
          tools={"HTML. CSS. SASS"}
        />
        <ProjectCard
          name={"Todo App"}
          details={"As part of Kalbonyan Almarsos program and The Modern JavaScript Bootcamp course, I've built, Todo App, a web application helps you to keep your tasks organized."}
          tools={"HTML. CSS. ES6. Babel. Webpack"}
        />
        <ProjectCard
          name={"Weather journal"}
          details={"Weather jornal app is part of the 'Front End Web Development Professional Nanodegree Program' from Udacity. It asynchronously fetches the OpenWeatherMap API to get live weather data by city zipcode."}
          tools={"HTML. CSS. ES6. Node. Express"}
        />
        <ProjectCard
          name={"Explore Egypt"}
          details={"CS50x course: week 8 (homepage). Explore Egypt simply provides a brief look at Egypt's geography, government, economy, and main cities."}
          tools={"HTML. CSS. ES6"}
        />
        <ProjectCard
          name={"Notes App"}
          details={"As part of Kalbonyan Almarsos program and The Modern JavaScript Bootcamp course, I've built, Notes App, a note-taking web application."}
          tools={"HTML. CSS. ES6. Babel. Webpack"}
        />
        <ProjectCard
          name={"Encyclopedia"}
          details={"CS50W2020: Week 3 project. Encyclopedia is a wikipedia-like web application.Users can view, search, edit, and create entries."}
          tools={"HTML. CSS. Python. Django. SQLite"}
        />
        <ProjectCard
          name={"Deal"}
          details={"CS50W2020: Week 4 project. Deal is an ebay-like website. Users can sell and buy goods and products. Users can create a listing with, close auction anytime, place a bid on any listing, add any listing to their watchlist, add comments on listings, and control thier auctions."}
          tools={"HTML. CSS. Python. Django. SQLite"}
        />
      </div>
    </div>
    )
  }
}

export default Projects;