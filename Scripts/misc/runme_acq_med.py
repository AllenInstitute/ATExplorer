#import paramiko
import os
import time
import json
import sys
sys.path.insert(0,'/pipeline/sharmi/allen_SB_code/celery/')
from celery import Celery
#from tasks import run_celerycommand

def parse_project_directory(line):

        proj = line.split("raw")
        projectdirectory = proj[0]

        tok = line.split("/")
        ribbondir = tok[len(tok)-2]
        sessiondir = tok[len(tok)-1]
        ribbon = int(ribbondir[6:])
        session = int(sessiondir[7:])

        return [projectdirectory, ribbon, session]


def get_channel_names(directory):
        #return os.listdir(directory)
        directory_list = list()
        for root, dirs, files in os.walk(directory, topdown=False):
                for name in dirs:
                        directory_list.append(os.path.join(root, name))
        return dirs
############### trying to read section number #####################
#def get_section_num(directory):
#       with open('session_metadata.txt') as f:
#               content = f.readlines()
#               last_sect = int(content.split("Length")[1])-1
#       return last_sect


def get_channel_nums(statetablefile):
        df=pd.read_csv(statetablefile)
        uniq_ch=df.groupby(['ch']).groups.keys()
        return uniq_ch

def parseprojectroot(projectdirectory):
        print ("this is your directory: " + projectdirectory)
        tok = projectdirectory.split("/")
        dataind = tok.index('data')
        print ("this is your root: " + tok[dataind+1])
        return tok[dataind+1]

def parsefile(fname):

        with open(fname) as f:
                content = f.readlines()

        if len(content)>1:
                print ("File is corrupted...")
        else:
                #parse line

                fullline = content[0]
                fullinetok = fullline.split(",")
                section = int(fullinetok[1])
                owner = str(fullinetok[2])
                #owner = "TESTEXPERIMENT"

                line = fullinetok[0]

                proj = line.split("raw")
                projectdirectory = proj[0]

                tok = line.split("/")
                ribbondir = tok[len(tok)-2]
                sessiondir = tok[len(tok)-1]
                ribbon = int(ribbondir[6:])
                session = int(sessiondir[7:])

                return [projectdirectory, ribbon, session, section, owner,fullline]

def savemedianjson(med,medianfile,owner, project,acq_stack,median_stack,median_dir,minz,maxz,close_stack):

        med['render']['owner'] = owner
        med['render']['project'] = project
        med['input_stack'] = acq_stack
        med['output_stack'] = median_stack
        med['minZ'] = minz
        med['maxZ'] = maxz
        med['output_directory'] = median_dir
        med['close_stack'] = close_stack
        with open(medianfile, 'w') as outfile:
                json.dump(med, outfile,indent=4)


if __name__ == "__main__":

        owner = "Small_volumes_2018"
        mediantemplate = "template/median.json"
        firstsection = 0
        lastsection = 35
        num_iter = 20
        #bgrd_size = 50

        curdir = os.getcwd()

        for i in range (0,1):

                with open("/pipeline/leila/stitching/confirm_data2process") as f:
                        alldirnames = f.readlines()

                for dirname in alldirnames:
                        flatfield_dirname =  "%s/../../../../processed/Flatfield" %dirname.strip('\n')
                        print ("thiis is dirname: " + dirname)
                        print (flatfield_dirname)
                        if not os.path.exists(flatfield_dirname):
                                os.makedirs(flatfield_dirname)
                        for sectnum in range(firstsection,lastsection+1):
                                close_stack = False

                                if sectnum==lastsection:
                                        close_stack = True

                                projectdirectory = dirname.strip()
                                project = parseprojectroot(projectdirectory)
                                channels = get_channel_names(projectdirectory)
                                [projectroot, ribbon,session] = parse_project_directory(projectdirectory)
                                z = ribbon*100+sectnum
                                print  ("this is your projectroot: " + projectroot)



                                #create file that consists of celery job commands
                                filename = "log/runme_sect_%s_%d_%d_%s.sh"%(project, ribbon,session,sectnum)
                                f = open(filename,'w')


                                #create state table

                                #projectroot = "/nas/data/M246930_Scnn1a_4/"
                                statetablefile =projectroot+ "scripts/statetable_ribbon_%d_session_%d_section_%d"%(ribbon,session,sectnum)
                                #statetablefile = "/nas/data/M246930_Scnn1a_4/scripts/statetable_ribbon_%d_session_%d_section_%d"%(ribbon,session,sectnum)
                                print (projectroot)
                                print (statetablefile)
                                #exit(0)
                                #make state table
                                cmd = "docker exec luigiscripts python make_state_table_ext_multi_pseudoz.py "
                                cmd = cmd + "--projectDirectory %s "%projectroot
                                cmd = cmd + "--outputFile  %s "%statetablefile
                                cmd = cmd + "--oneribbononly True "
                                cmd = cmd + "--ribbon %d "%ribbon
                                cmd = cmd + "--session %d "%session
                                cmd = cmd + "--section %d "%sectnum
                                f.write(cmd+"\n")
                                #os.system(cmd)

                                #upload acquisition stacks
                                dcmd = "docker exec renderapps_develop python -m renderapps.dataimport.create_fast_stacks "
                                dcmd = dcmd + "--render.host ibs-forrestc-ux1 "
                                dcmd = dcmd + "--render.client_scripts /var/www/render/render-ws-java-client/src/main/scripts "
                                dcmd = dcmd + "--render.port 8988 "
                                dcmd = dcmd + "--render.memGB 5G "
                                dcmd = dcmd + "--log_level INFO "
                                dcmd = dcmd + "--statetableFile %s "%statetablefile
                                dcmd = dcmd + "--render.project %s "%project
                                dcmd = dcmd + "--projectDirectory %s "%projectroot
                                dcmd = dcmd + "--outputStackPrefix ACQ_S0%d"%(session)
                                dcmd = dcmd + " --render.owner %s "%owner
                                f.write(dcmd+"\n")
                                #os.system(dcmd)
                                #exit(0)
                                #dcmd = dcmd + "--projectDirectory %s "%projectroot


                                #print channels


                                for ch in channels:
                                        print ("Channel: " + str(ch))
                                        #print "PRINTING CHANNELS TEST"
                                        #print ch
                                        medianfile = "%s/log/median_%s_%s_%s_%s_%d.json"%(curdir,project,ch,ribbon,session,sectnum)

                                        #stacks
                                        acq_stack = "ACQ_S0%d_%s"%(int(session),ch)
                                        median_stack = "MED_S0%d_%s"%(int(session),ch)

                                        #directories
                                        median_dir = "%s/processed/Medians/"%projectroot

                                        #psf file, scale factor, and background size for deconvolution
                                        print (close_stack)
                                        if close_stack:
                                                #create median file
                                                firstz = ribbon*100+firstsection
                                                lastz = ribbon*100+lastsection
                                                print (firstz)
                                                print (lastz)
                                                with open(mediantemplate) as json_data:
                                                        med = json.load(json_data)
                                                savemedianjson(med,medianfile,owner, project,acq_stack,median_stack,median_dir,firstz,lastz,close_stack)



                                                #run
                                                mystr = "DAPI"
                                                cmd1 = "docker exec rm_container python -m rendermodules.intensity_correction.calculate_multiplicative_correction --render.port 8988 --input_json %s"%medianfile

                                                f.write(cmd1+"\n")
                                                print (cmd1)

                                f.close()
                                rcmd = "sh %s"%filename
                                print (rcmd)
                                #result = run_celerycommand.apply_async(args=[rcmd,os.getcwd()])
                                os.system(rcmd)
                                time.sleep(2)