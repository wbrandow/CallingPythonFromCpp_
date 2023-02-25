import re
import string

# Description: To use, simply call. 
#
# Example: ReadSalesToDict()
#
# Input: Reads from InputFile.txt
#
# Output: None
#
# Returns: Dictionary with item names as key and frquencies as values
#
def ReadSalesToDict():

    #open file
    salesFile = open ('Release\InputFile.txt')
    
    #read file into list of strings
    saleLinesTemp = salesFile.readlines()

    # create new list of strings stripped of newline characters
    saleLines = []
    for line in saleLinesTemp:
         saleLines.append(line.strip())

    # close file
    salesFile.close()
    
    # create dictionary
    itemSaleFrequencies = {saleLines[0]: 0}
    
    # If item already exists in dictionary, increment frequency. Otherwise, add to dictionary.
    for item in saleLines:
        if item in itemSaleFrequencies:
            itemSaleFrequencies[item] = itemSaleFrequencies[item] + 1
        else:
            itemSaleFrequencies[item] = 1
    
    # return dictionary of item names and sale frequencies
    return itemSaleFrequencies

# Description: To use, simply call.
#
# Example: PrintSalesList()
#
# Input: None. Calls ReadSalesToDict()
#
# Output: Prints item names and frequencies
#
# Returns: None
#
def PrintSalesList():
    # read InputFile.txt into dictionary
    itemSaleFrequencies = ReadSalesToDict()

    for itemName, saleFrequency in itemSaleFrequencies.items():
        print(itemName, saleFrequency)

# Description: To use, call with string argument.
#
# Example: PrintItemsSales("Bologna")
#
# Input: Takes string argument
#
# Output: None
#
# Returns: frequency for item passed by user
#
def PrintItemsSales(itemName):
    # read InputFile.txt into dictionary
    itemSaleFrequencies = ReadSalesToDict()

    if itemName in itemSaleFrequencies.keys():
        return itemSaleFrequencies[itemName]
    else:
        return 0


def WriteDataFile():
    # read InputFile.txt into dictionary
    itemSaleFrequencies = ReadSalesToDict()

    # open file for writing
    dataFile = open ('frequency.dat', 'w')

    # write item names and frequencies to file
    for itemName in itemSaleFrequencies:
        dataFile.write(itemName)
        dataFile.write(" ")
        dataFile.write(str(itemSaleFrequencies[itemName]))
        dataFile.write("\n")

    # close file
    dataFile.close()




   
