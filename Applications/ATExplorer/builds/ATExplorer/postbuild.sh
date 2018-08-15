#! /bin/bash
echo "Hello Bash"

echo "Arg1: "$1
echo "Arg2: "$2
echo "Arg3: "$3
echo "Arg4: "$4

BUILD_FOLDER=$1
APP_RELEASES=$2
OUTPUTFILENAME=$3
BDSCOMMONDIR=$4

echo "BUILD_FOLDER: "$BUILD_FOLDER
echo "AppReleases: "$APP_RELEASES
echo "Outputfilename: "$OUTPUTFILENAME
echo "BDSCOMMONDIR: "$BDSCOMMONDIR

#Extract version
VERSION=`cat ../../VERSION.txt | tr -d '\r'`
APPNAME=ATExplorer
echo "Copy stuff"
mkdir $APP_RELEASES/$APPNAME

AppReleaseFolder=$APP_RELEASES/$APPNAME
SRC_DIR="./../../source"

#Borland Packages and dll's
#CG_REDIST="/cygdrive/c/CodeGear/Tokyo/bin"
CG_REDIST="/c/CodeGear/Tokyo/bin"
suffix="250.bpl"

#Other 3rd Party binaries
#miscRedist="/cygdrive/p/redist"
miscRedist="/p/redist"
files=(
$SRC_DIR/../*.txt                                
$SRC_DIR/*.ico                      
$BUILD_FOLDER/$OUTPUTFILENAME                       

#DS Binaries
$BUILD_FOLDER/dslFoundation.dll                         
$BUILD_FOLDER/dslVCLCommon.dll                      
$BUILD_FOLDER/atSSI.dll                             
$BUILD_FOLDER/atFoundation.dll                   
$BUILD_FOLDER/atVCLCommon.dll                       
$BUILD_FOLDER/poco_foundation.dll
$BUILD_FOLDER/tinyxml2.dll
$BUILD_FOLDER/sqlite.dll
$BUILD_FOLDER/libcurl.dll
$BUILD_FOLDER/navusbapi.dll
$BUILD_FOLDER/Thorlabs.MotionControl.Benchtop.StepperMotor.dll
$BUILD_FOLDER/Thorlabs.MotionControl.DeviceManager.dll
$BUILD_FOLDER/Thorlabs.MotionControl.DeviceManagerCLI.dll
$BUILD_FOLDER/Thorlabs.MotionControl.DeviceManagerUI.dll
$BUILD_FOLDER/Thorlabs.MotionControl.IntegratedStepperMotors.dll
$BUILD_FOLDER/Thorlabs.MotionControl.TCube.BrushlessMotor.dll
$BUILD_FOLDER/Thorlabs.MotionControl.TCube.DCServo.dll
$BUILD_FOLDER/Thorlabs.MotionControl.TCube.StepperMotor.dll
$BUILD_FOLDER/Thorlabs.MotionControl.TDIEngine.dll

$BDSCOMMONDIR/BPL/dslVCLComponents.bpl          
#$BDSCOMMONDIR/BPL/dslVCLVisualComponents.bpl    
$BDSCOMMONDIR/BPL/atVCLComponents.bpl               
$BDSCOMMONDIR/BPL/atVCLVisualComponents.bpl         
$BDSCOMMONDIR/BPL/atVCLAPTVisualComponents.bpl      
$BDSCOMMONDIR/BPL/atVCLDataModules.bpl             
$BDSCOMMONDIR/BPL/ATExplorerAppPackage.bpl

$CG_REDIST/borlndmm.dll                         
$CG_REDIST/cc32250mt.dll                        
$CG_REDIST/midas.dll                            

$CG_REDIST/bcbsmp$suffix                        
$CG_REDIST/dbexpress$suffix                     
$CG_REDIST/dbrtl$suffix                         
$CG_REDIST/dbxcds$suffix                        
$CG_REDIST/DBXCommonDriver$suffix               
$CG_REDIST/DBXDevartPostgreSQLDriver$suffix     
$CG_REDIST/DBXMySQLDriver$suffix                
$CG_REDIST/dsnap$suffix                         
$CG_REDIST/rtl$suffix                           
$CG_REDIST/vcl$suffix                           
$CG_REDIST/vclactnband$suffix                   
$CG_REDIST/vclimg$suffix                        
$CG_REDIST/vclx$suffix                          
$CG_REDIST/tee9$suffix                          
$CG_REDIST/vcldb$suffix                         
$CG_REDIST/IndySystem$suffix     
$CG_REDIST/IndyProtocols$suffix 
$CG_REDIST/IndyCore$suffix     
$miscRedist/dbexppgsql40.dll                                     
$miscRedist/msvcp110.dll                                     
$miscRedist/msvcr110.dll                                     
$miscRedist/vccorlib110.dll
$miscRedist/RaizeComponentsVcl250.bpl
$miscRedist/sbridge250.bpl
)

for file in "${files[@]}"
do 
    echo "Copying file: $file to $AppReleaseFolder" 
    cp $file $AppReleaseFolder
done

echo "Copying dcef browser files" 

cp -r -v /p/libs/DcefBrowser/bin/Win32/*                            $AppReleaseFolder
cp -r -v /p/libs/DcefBrowser/bin/Win32/*                            $BUILD_FOLDER
##instead of using local bin folder
cp $SRC_DIR/../*.txt                                                $BUILD_FOLDER
cp $SRC_DIR/*.ico                                                   $BUILD_FOLDER
