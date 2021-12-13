from cs50 import get_string

# getting input from user
text = get_string("Text: ")
l = len(text)

# keeping track of words, letters, and sentences
words = 1
letters = 0
sentences = 0

# counting words, letter, and sentences per text
for i in range(l):
    if text[i].isalpha():
        letters += 1
    elif text[i] == " ":
        words += 1
    elif text[i] in [".", "?", "!"]:
        sentences += 1
    
# calculating Coleman-Liau index's L and S values
L = (letters / words) * 100
S = (sentences / words) * 100

# calculating Coleman-Liau index
grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade < 1:
    print("Before Grade 1")
elif grade > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade}")