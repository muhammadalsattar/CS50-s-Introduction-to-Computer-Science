import csv
import sys
import re

# checking for args number
if len(sys.argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    sys.exit()

# reading sequence file
sequences = open(sys.argv[2], "r")
sequence = sequences.read()


# a dictionary to keep track of STRs repeats count
strcount = {
    'AGATC': 0,
    'TTTTTTCT': 0,
    'AATG': 0,
    'TCTAG': 0,
    'GATA': 0,
    'TATC': 0,
    'GAAA': 0,
    'TCTG': 0
}

# counting each STR longest reapeats
for i in strcount:
    strlen = len(i)
    count = 0
    j = 0
    while j in range(len(sequence)):
        # keeping track of repeats found
        if sequence[j: j+strlen] == i:
            count += 1
            j = j + strlen
        
        # updating repeats count
        else:
            if strcount[i] < count:
                strcount[i] = count
            
            count = 0
            j += 1


person = "No match"
counter = 0

# checking for person whose STRs matches
with open(sys.argv[1], "r") as file:
    data = csv.DictReader(file)
    for row in data:
        for i in strcount:
            if i in row:
                if int(row[i]) == int(strcount[i]):
                    counter += 1
        
        if counter == 8 or counter == 3:
            person = row["name"]
        
        counter = 0

# printing person name if found
print(person)
