#-------------------------------------------------------------------------------
# Purpose: Validate ATData
#-------------------------------------------------------------------------------

import ATExplorer

try:
    #Create an empty ATData object
    atData = ATExplorer.ATData()

    #Validate ATData in a folder of your choice
    atDataFolder = "X:\data\test041817\raw\map\Ribbon0060\map1"

    if atData.validate(atDataFolder):
        print ("ATData information" + atData.getInfo())
    else:
        print ("The folder: " + atDataFolder + " does not contain valid ATData..")

    print ("Done..")

except ATDataError as msg:
    print(msg)

except Exception as e:
    print("There was an exception: " + str(e))




