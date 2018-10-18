docker run --rm -t --name renderapps ^
-v F:/data:/mnt/data/  ^
-v c:/pDisk/atExplorer/DockerDataFolders/pipeline:/pipeline  ^
-v c:/pDisk/atExplorer/ThirdParty/Render-Python-Apps:/usr/local/render-python-apps  ^
-p 7777:7777  -e "PASSWORD=$JUPYTERPASSWORD"  ^
-i -t render-p-apps:latest

