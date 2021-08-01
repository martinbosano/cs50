import re
from cs50 import get_int

### get input from user
while True:
    number = get_int("cardnumber: ")
    ### make sure it's a postivie integer
    if number > 0:
        break

##checksum variables
ccn = round(number)
cardnumber = str(number) 
checksum1 = 0
checksum2 = 0
remainder1 = 0
remainder2 = 0
digit1 = 0
digit2 = 0

### checksum function
while ccn > 0:
    remainder1 = ccn % 10
    checksum1 = checksum1 + remainder1
    ccn = (ccn - remainder1) // 10
    remainder2 = ccn % 10
    digit1 = (remainder2 * 2) % 10
    digit2 = (remainder2 * 2) // 10
    checksum2 = checksum2 + digit1 + digit2
    ccn = round((ccn - remainder2) // 10)
    
#checksum
checksum = (checksum1 + checksum2) % 10
    

### recognizing which card is and printing
if checksum == 0:
    if (len(cardnumber) == 13 or len(cardnumber) == 16) and re.search('^4', cardnumber):
        print("VISA")
    elif len(cardnumber) == 16 and re.search('^51|52|53|54|55', cardnumber):
        print("MASTERCARD")
    elif len(cardnumber) == 15 and re.search('^34|37', cardnumber):
        print("AMEX")
    else:
        print("INVALID")
### if isn't a valid card number, then
else:
    print("INVALID")