from cs50 import SQL
from sys import argv
import csv

if not len(argv) == 2:
    print("usage: python import.py house")
    exit(1)


db = SQL("sqlite:///students.db")
student = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])
for row in student:
    if row['middle'] == None:
        print(row['first'] + " " + row['last'] + "," + " " + "born" + " " + str(row['birth']))
    else:
        print(row['first'] + " " + row['middle'] + " " + row['last'] + "," + " " + "born" + " " + str(row['birth']))
exit(0)