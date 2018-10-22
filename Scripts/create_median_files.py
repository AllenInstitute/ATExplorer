import os
import time
import json
import sys
import subprocess
import posixpath

def toPosixPath(winpath, prefix):
    p = posixpath.normpath(winpath.replace('\\', '/'))
    p = p[p.index(':') + 1:]
    p = "/" + prefix + p
    return p

def parseprojectroot(projectdirectory):
    print ("Project directory: " + projectdirectory)
    tok = projectdirectory.split(os.sep)
    dataind = tok.index('data')
    print ("Project data folder: " + tok[dataind+1])
    return tok[dataind+1]

def parse_project_directory(line):
    proj = line.split("raw")
    projectdirectory = proj[0]
    tok = line.split(os.sep)
    ribbondir = tok[len(tok)-2]
    sessiondir = tok[len(tok)-1]
    ribbon = int(ribbondir[6:])
    session = int(sessiondir[7:])
    return [projectdirectory, ribbon, session]

def get_channel_names(directory):
    directory_list = list()
    for root, dirs, files in os.walk(directory, topdown=False):
            for name in dirs:
                directory_list.append(os.path.join(root, name))
    return dirs

def get_channel_nums(statetablefile):
    df=pd.read_csv(statetablefile)
    uniq_ch=df.groupby(['ch']).groups.keys()
    return uniq_ch

def parsefile(fname):

    with open(fname) as f:
        content = f.readlines()

    if len(content)>1:
        print ("The File: "  + fname + " is corrupted!")
    else:
        #parse line
        fullline = content[0]
        fullinetok = fullline.split(",")
        section = int(fullinetok[1])
        owner = str(fullinetok[2])
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
    med['output_directory'] = toPosixPath(median_dir,"mnt")
    med['close_stack'] = close_stack

    with open(medianfile, 'w') as outfile:
          json.dump(med, outfile,indent=4)

if __name__ == "__main__":
    owner = "ATExplorer"
    firstsection = 0
    lastsection = 1
    mediantemplate = "../DockerDataFolders/pipeline/median_record_template.json"
    num_iter = 20
    processDir = "f:\\data\\M33"
    dirname = "f:\\data\\M33\\raw\\data\\Ribbon0004\\session01"
    print ("Processing folder: " + dirname)

    for sectnum in range(firstsection,lastsection+1):
        close_stack = False

        if sectnum==lastsection:
            close_stack = True

        projectdirectory = dirname.strip()
        project = parseprojectroot(projectdirectory)
        channels = get_channel_names(projectdirectory)
        [projectroot, ribbon,session] = parse_project_directory(projectdirectory)
        z = ribbon*100+sectnum
        print  ("This is your projectroot: " + projectroot)

        #create file that consists of celery job commands
        #filename = "log/runme_sect_%s_%d_%d_%s.sh"%(project, ribbon,session,sectnum)
        #f = open(filename,'w')

        for ch in channels:
            print ("Channel: " + str(ch))
            #print "PRINTING CHANNELS TEST"
            #print ch
            medianfile = "%s/logs/median_%s_%s_%s_%s_%d.json"%(processDir,project,ch,ribbon,session,sectnum)

            #stacks
            acq_stack   = "ACQ_Session%d_%s"%(int(session),ch)
            median_stack = "MED_Session%d_%s"%(int(session),ch)

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

                #upload acquisition stacks
                cmd = "docker exec renderapps python -m rendermodules.intensity_correction.calculate_multiplicative_correction"
                cmd = cmd + " --render.port 8080"
                cmd = cmd + " --input_json %s"%(toPosixPath(medianfile, "mnt"))

                p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
                for line in p.stdout.readlines():
                    print (line)

    print ("done")