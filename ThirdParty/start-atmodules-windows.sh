#! /usr/bin/bash

#AT_Modules
image_tag="sharmi/at_modules"
container_name="atmodules"
docker_file=./init/Dockerfile-atmodules
work_dir=./at_modules

echo " ======== Building and starting Docker container with name: $container_name =============="
echo "Building image with tag: $image_tag"
docker build -t $image_tag -f $docker_file $work_dir

echo "Killing container with name: $container_name"
docker kill $container_name
docker rm $container_name

echo "Starting container with name: $container_name"
docker run -d --name $container_name \
-v e:/Documents/data:/mnt/  \
-v e:/Documents/data:/mnt/data/  \
-v c:/pDisk/atExplorer/ThirdParty/atPipeline/pipeline:/pipeline  \
-v c:/pDisk/atExplorer/ThirdParty/at_modules/src:/usr/local/at_modules/src  \
-i -t $image_tag /bin/bash

echo "Done.."
