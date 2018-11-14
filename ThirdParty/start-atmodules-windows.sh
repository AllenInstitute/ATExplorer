#! /usr/bin/bash
image_tag="sharmi/at_modules"
container="atmodules"

echo " ======== Building and starting Docker container: $container =============="
echo "Building image with tag: $image_tag"
docker build -t  $image_tag ./at_modules/

docker kill $container
docker rm $container

echo "Starting container: $container"
docker run -d --name $container \
-v e:/Documents/data:/mnt/data/  \
-v c:/pDisk/atExplorer/ThirdParty/atPipeline:/pipeline  \
-i -t $image_tag /bin/bash 
