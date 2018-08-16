docker run -t --name renderapps ^
-v d:/renderData:/renderData  ^
-v d:/renderData/pipeline:/pipeline  ^
-v c:/pDisk/atExplorer/ThirdParty/Render-Python-Apps:/usr/local/render-python-apps  ^
-p 7777:7777  -e "PASSWORD=$JUPYTERPASSWORD"  ^
-i -t render-p-apps:latest

