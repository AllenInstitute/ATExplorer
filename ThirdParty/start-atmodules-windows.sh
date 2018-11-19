#! /usr/bin/bash
atm_image_tag="sharmi/at_modules"
atm_container="atmodules"

echo " ======== Building and starting Docker container: $atm_container =============="
echo "Building image with tag: $atm_image_tag"
docker build -t  $atm_image_tag -f ./init/Dockerfile-atmodules
docker kill $atm_container
docker rm $atm_container

echo "Starting container: $atm_container"
docker run -d --name $atm_container \
-v e:/Documents/data:/mnt/data/  \
-v c:/pDisk/atExplorer/ThirdParty/atPipeline:/pipeline  \
-v c:/pDisk/atExplorer/ThirdParty/at_modules/src:/usr/local/at_modules/src  \
-i -t $atm_image_tag /bin/bash 
