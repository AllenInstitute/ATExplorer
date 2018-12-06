#! /usr/bin/bash

#AT MODULES
atm_image_tag="sharmi/at_modules"
atm_container="atmodules"

echo " ======== Building and starting Docker container: $atm_container =============="
echo "Building image with tag: $atm_image_tag"
docker build -t  $atm_image_tag -f ./init/Dockerfile-atmodules ./at_modules
docker kill $atm_container
docker rm $atm_container

echo "Starting container: $atm_container"
docker run -d --name $atm_container \
-v /Users/synbio/Documents/data:/mnt/data/  \
-v /Users/synbio/ATExplorer/ThirdParty/atPipeline:/pipeline  \
-v /Users/synbio/ATExplorer/ThirdParty/at_modules/src:/usr/local/at_modules/src  \
-i -t $atm_image_tag /bin/bash 

#RENDER PYTHON APPS
rpa_image_tag="fcollman/render-python-apps"
rpa_container="renderapps_multchan"

echo " ======== Building and starting Docker container: $rpa_container =============="
echo "Building image with tag: $rpa_image_tag"
docker build -t $rpa_image_tag -f ./init/Dockerfile-RenderPythonApps ./Render-Python-Apps
docker kill $rpa_container
docker rm $rpa_container 

echo "Starting container: $rpa_container"
docker run -d --name $rpa_container  \
-v /Users/synbio/Documents/data:/mnt/data/  \
-v /Users/synbio/ATExplorer/ThirdParty/atPipeline:/pipeline  \
-v /Users/synbio/ATExplorer/ThirdParty/Render-Python-Apps:/usr/local/render-python-apps  \
-i -t $rpa_image_tag /bin/bash


#Render Service, mongo & ndviz stuff
docker-compose -f ./init/docker-compose-mac.yml up -d
