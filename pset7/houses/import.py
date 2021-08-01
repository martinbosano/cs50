from cs50 import SQL
from sys import argv
import csv

if not len(argv) == 2:
    print("usage: python import.py (csv file)")
    exit(1)
    
db = SQL("sqlite:///students.db")
with open(argv[1], mode= 'r') as reader:
    reader = csv.DictReader(reader)
    for row in reader:
        name = row["name"]
        fullname = name.split()
        if len(fullname) == 2:
            first = fullname[0]
            middle = None
            last = fullname[1]
        else:
            first = fullname[0]
            middle = fullname[1]
            last = fullname[2]
        house = row['house']
        birth = int(row['birth'])
        
        db.execute("INSERT into students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
        first, middle, last, house, birth)
        


    exit(0)
    
    
     