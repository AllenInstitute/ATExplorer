#! /usr/bin/bash

#AT_Modules
image_tag="sharmi/at_modules"
container="atmodules"
docker_file=./init/Dockerfile-atmodules
work_dir=./at_modules

echo " ======== Building and starting Docker container: $container =============="
echo "Building image with tag: $image_tag"
docker build -t $image_tag -f $docker_file $work_dir


echo "Killing container: $container"
docker kill $container
docker rm $container

echo "Starting container: $container"
docker run -d --name $container \
-v e:/Documents/data:/mnt/data/  \
-v c:/pDisk/atExplorer/ThirdParty/atPipeline/pipeline:/pipeline  \
-v c:/pDisk/atExplorer/ThirdParty/at_modules/src:/usr/local/at_modules/src  \
-i -t $image_tag /bin/bash

echo "Done.."
