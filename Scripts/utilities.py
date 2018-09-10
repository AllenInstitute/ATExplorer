import os
def version():
    #Parse the version file
    currFolder = os.path.dirname(os.path.realpath(__file__))
    f = open(currFolder + "/VERSION.txt", 'r')
    return f.read().splitlines()
