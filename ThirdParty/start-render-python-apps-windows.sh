#! /usr/bin/bash

#RENDER PYTHON APPS
image_tag="fcollman/render-python-apps"
container="renderapps_multchan"
docker_file=./init/Dockerfile-RenderPythonApps
work_dir=./Render-Python-Apps

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
-v c:/pDisk/atExplorer/ThirdParty/Render-Python-Apps:/usr/local/render-python-apps  \
-i -t $image_tag /bin/bash

echo "Done.."
