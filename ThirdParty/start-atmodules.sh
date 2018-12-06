#! /usr/bin/bash

#AT MODULES
atm_image_tag="sharmi/at_modules"
atm_container="atmodules"

echo " ======== Building and starting Docker container: $atm_container =============="
echo "Building image with tag: $atm_image_tag"
docker build -t $atm_image_tag -f ./init/Dockerfile-atmodules ./at_modules
docker kill $atm_container
docker rm $atm_container

echo "Starting container: $atm_container"
docker run -d --name $atm_container \
-v /Users/synbio/Documents/data:/mnt/data/  \
-v /Users/synbio/ATExplorer/ThirdParty/atPipeline:/pipeline  \
-v /Users/synbio/ATExplorer/ThirdParty/at_modules/src:/usr/local/at_modules/src  \
-i -t $atm_image_tag /bin/bash 
