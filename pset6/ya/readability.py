### import functions
import sys

### get text input from user
paragraph = (input("Text: "))

### variables to collect
characters = 0
words = 1
sentences = 0
### variables collector loop
for word in paragraph:
    ## checks if is an ascii character but not a blank one
    if word.isalnum():
        characters += 1
    ### checks if it's a blank space
    elif word.isspace():
        words += 1
    ### checks if it's a punctuation sign
    elif word == "." or word == "?" or word == "!":
            sentences += 1

### coleman liau index
L = (100.0 * characters) / words
S = (100.0 * sentences) / words
index = round(0.0588 * L - 0.296 * S - 15.8)
grade = index;

### print the correct grade for the text
if grade < 1:
    print("Before Grade 1")
elif grade >= 1 and grade < 16:
    print(f"Grade {grade}")
elif grade >= 16:
    print("Grade 16+")