#-------------------------------------------------------------------------------
# Purpose: Interact with ATData
#-------------------------------------------------------------------------------

import atexplorer as at
import dsl
try:
    #gLogger = dsl.gLogger
    #gLogger.logToFile("p:\\MyLog.txt")

    print("AtExplorer version: " + at.getVersion())
    dataPath = "F:\\data\\M33\\"

    #Create an empty ATData object
    atData = at.ATIFData(dataPath, False)
    atData.populate()

    #Some trivial data info
    print( "Number of Ribbons: " + str(atData.getNumberOfRibbons()))
    ribbon = atData.getFirstRibbon()

    while ribbon:
        print ("Ribbon Alias: " + ribbon.getAlias())
        print ("Number of sections: " + str(ribbon.getSectionCount()))
        ribbon = atData.getNextRibbon()


    #Render render("anOwner", "aProject")
    #stackList = {"DAPI_STACK", "GFP"}
    #atData.createRenderStack(stackList, dapiChannel, RAW, 0, 45)


    if atData.validate():
        print ("ATData information" + atData.getInfo())
    else:
        print ("The folder: " + dataPath + " does not contain valid ATData..")

    print ("Done..")

except Exception as e:
    print("There was an exception: " + str(e))

