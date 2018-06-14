import os
import glob
import json

#user input:
inputdir = "/nas4/KDM-SYN-100430B-L5_Deconv/Curated_SJS_2017/Deconvolved"
tilespecdirs = "/nas4/KDM-SYN-100430B-L5_Deconv/Curated_SJS_2017/Deconvolved_and_Ultraligned/alignment_intermediates/tilespecs/"
numberofsections = 49
host = "ibs-forrestc-ux1"
owner = "KDM_SYN"
project = "KDM_SYN_100430B_L5"
stack = "Stitched_Tubulin_7"
prealigned_stack = "Stitched_DAPI_7"
roughaligned_stack = "RoughAligned_DAPI_7"
deltaZ = 10


#setup
pm_script_dir = "/pipeline/forrestrender/render-ws-spark-client/src/main/scripts"
dockerstr = "docker exec renderapps_testsharmi  "
renderstr = " --render.host ibs-forrestc-ux1 --render.client_scripts /var/www/render/render-ws-java-client/src/main/scripts --render.port 8080 --render.memGB 5G --log_level INFO "
projectstr = " --render.project %s --render.owner %s "%(project,owner)
uploadcmdstr = dockerstr + "python -m renderapps.dataimport.upload_tiledir " + renderstr + projectstr
collection1 = "%s_col1"%stack



#1. upload

datadirs = os.listdir(inputdir)
for i in datadirs:

    parts = i.split("_")
    tileDirectory = inputdir + "/" + i
    tilespecDirectory = tilespecdirs + "/" + i
    outputStack = "Stitched_%s_%d"%(parts[1],int(parts[0][3:5]))

    uploadcmd = uploadcmdstr  + "--inputTileDirectory %s --tilespecDirectory %s --outputStack %s"%(tileDirectory, tilespecDirectory,outputStack)
    print uploadcmd
    #os.system(uploadcmd)
#exit(0)

#2. registration
regcmd = "java -cp /pipeline/sharmi/at_modules/allen/target/allen-1.0-SNAPSHOT-jar-with-dependencies.jar at_modules.Register "
siftparams = " --modelType 1 --percentSaturated 0.9f --maxEpsilon 2.5 --initialSigma 1.6 --steps 9 "
renderparams = " --baseDataUrl http://ibs-forrestc-ux1/render-ws/v1 --owner %s --project %s " %(owner, project)


for i in range (0,50):
    for ch in range(2,11):
        registrationparams = "--stack Stitched_DAPI_%d --referencestack Stitched_DAPI_1 --outputStack Registered_DAPI_%d  --section %d"%(ch,ch,i)
        regrun_cmd = regcmd + siftparams + renderparams + registrationparams
        print regrun_cmd
    #"--outputJson /home/sharmishtaas/testjson.json --outputtilespec /home/sharmishtaas/outputtilespec.json --referenceID TESTING12345 "
        os.system(regrun_cmd)
exit(0)



#3. Download to TrakEM2
docker exec renderapps_testsharmi python -m renderapps.TrakEM2.create_trakem2_subvolume_from_render
