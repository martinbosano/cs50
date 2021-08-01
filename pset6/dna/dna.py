# import functions 
import csv
from sys import argv, exit

# make sure the input is correct
if not len(argv) == 3:
    print("usage: dna.py database.csv sequence.txt")
    exit(1)

# create a dictionary for the sequence
headers = {}

# opening the csv database
with open(argv[1], mode= 'r') as database:
    database = next(csv.reader(database))
    counter = 0
    for row in database:
        if row != 'name':
            headers[row] = 0
# opening the sequence
with open(argv[2], mode = 'r') as sequence:
    sequence1 = sequence.read()
# counter of coincidences
maxCounter = 0
# comparing the sequence
for key in headers:
    j = len(key)
    for i in range(len(sequence1)):
        counter = 0
        if key == sequence1[i:j+i]:
            counter += 1
            while sequence1[i:j+i] == sequence1[i+j:i+j+j]:
                counter += 1
                i += j
            if counter > headers[key]:
                headers[key] = counter         
# bool for match
matchfound = False

# itering through the database and the headers dictionary
with open(argv[1], mode= 'r') as subjects:
    subjects = csv.DictReader(subjects, delimiter=',')
    for row in subjects:
        matchcounter = 0
        for key in headers:
            if int(row[key]) == headers[key]:
                matchcounter += 1
                if matchcounter == len(headers):
                    matchfound = True
                    print(row['name'])
                    break
# if match isn't found, prints no match
if matchfound == False:
        print("No match")
                
                
 