#!/usr/bin/env python

import ConfigParser
import os, errno, sys, getpass
import getopt

# hacky way to find out what the name of the branch is
branch = os.popen('hg branch').readlines()
branch = branch[0].replace("\n","")
cwd = os.getcwd()

deps = [ \
    ['https://www.underworldproject.org/hg/SConfigure', 'config' ], \
    ['https://www.underworldproject.org/hg/credo', 'credo' ], \
    ['https://www.underworldproject.org/hg/gLucifer', 'gLucifer' ], \
    ['https://www.underworldproject.org/hg/PICellerator', 'PICellerator' ], \
    ['https://www.underworldproject.org/hg/StgDomain', 'StgDomain' ], \
    ['https://www.underworldproject.org/hg/StGermain', 'StGermain' ], \
    ['https://www.underworldproject.org/hg/StgFEM', 'StgFEM' ], \
    ['https://www.underworldproject.org/hg/Underworld', 'Underworld' ], \
    ['https://www.underworldproject.org/hg/UnderworldManual', 'Docs/Manual' ]]

# Check for run time flags
try:
    opts, args = getopt.getopt(sys.argv[1:], [], [
        "with-experimental=", "with-spmodel=", "with-pderework=", "with-xmlviewer", "with-importers=",
        "with-geothermal=", "with-magma=", "with-gocadtoolbox=", "with-spherical=", "with-solvers=", "with-cartesian=", "store-passwords=", "with-viscoelastic="])
except getopt.GetoptError, err:
    print str(err)
    sys.exit(2);

# Set password flag to False.. should be set to True for any repository requiring a password
password = False

# Do not save passwords in hgrc files unless instructed to
storePasswords = False  
for o, a in opts:
    if o == "--with-experimental" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/Experimental', 'Experimental']);
        print "\nNote that Experimental has been shutdown.  While you can still checkout the repository, " \
              "it is closed for further commits, and is now indeed broken.\n"\
              "If there is functionality in Experimental you require, please let us know at:\n\n" \
              "https://www.underworldproject.org/forums/ \n"
        raw_input("Press Enter to continue")  #note that this wont be python 3 compat
        password = True
    elif o == "--with-spmodel" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/SPModel', 'SPModel'])
    elif o == "--with-pderework" and a != "0" and a.lower() != "false":
        print "\nNote that PDERework is now deprecated.\n" \
              "If there is functionality you require, please let us know at:\n\n" \
              "https://www.underworldproject.org/forums/ \n"
        sys.exit(2);
    elif o == "--with-xmlviewer" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/UnderworldViewer', 'XMLViewer'])
    elif o == "--with-solvers" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/Solvers', 'Solvers'])
        password = True
    elif o == "--with-spherical" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/Spherical', 'Spherical'])
        password = True
    elif o == "--with-viscoelastic" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/Viscoelastic', 'Viscoelastic'])
        password = True
    elif o == "--with-geothermal" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/Geothermal', 'Geothermal'])
    elif o == "--with-magma" and a != "0" and a.lower() != "false":
        print "\nNote that the Magma toolbox is now deprecated.\n" \
              "If there is functionality you require, please let us know at:\n\n" \
              "https://www.underworldproject.org/forums/ \n"
        sys.exit(2);
    elif o == "--with-cartesian" and a != "0" and a.lower() != "false":
        deps.append(['https://bitbucket.org/underworldproject/cartesianearthbox', 'CartesianEarthBox'])
    elif o == "--with-importers" and a != "0" and a.lower() != "false":
        deps.append(['https://www.underworldproject.org/hg/Geothermal', 'Geothermal'])
        deps.append(['https://bitbucket.org/underworldproject/importerstoolbox', 'ImportersToolbox'])
    elif o == "--with-gocadtoolbox" and a != "0" and a.lower() != "false":
        print 'Error: GocadToolbox functionality has been moved into ImportersToolbox.'
        print 'Use --with-importers=1 to access toolbox.'
        sys.exit(2);
    elif o == "--store-passwords" and a != "0" and a.lower() != "false":
        storePasswords = True

# Make sure the '.hg' directory exists
try:
    os.mkdir('.hg')
except OSError, e:
    if e.errno != errno.EEXIST:
        raise OSError( e ) # if the error is the directory exists already, keep going

# Get username and password where required
username = ''
if password:
    username = raw_input('A username will be required for one or more repositories.\nUsername: ') 
    if username:
        password = getpass.getpass('Password: ')
# Download the dependancies...
for dep in deps:
    os.chdir(cwd)
    print dep[1], '...'
    if username:
        # First clone repository
        os.popen('hg clone '+dep[0].replace("://","://"+username+":"+password+"@")+' '+dep[1])
        # Now remove password information from hgrc file
        if storePasswords != True:
            c = ConfigParser.RawConfigParser()
            c.read(dep[1]+'/.hg/hgrc')
            try:
                c.set('paths', 'default', dep[0])
            except ConfigParser.Error:
                print 'error trying to modify hgrc file.. exiting'
                sys.exit(2);
            c.write( open( dep[1]+'/.hg/hgrc', 'w' ) )      
    else:
        os.popen('hg clone '+dep[0]+' '+dep[1])

    # And heres some more hackyness to get hg to switch branches
    # I couldn't find any functionality to do this in the python bindings.
    # JS - 12/11/2008
    os.chdir(dep[1])
    try:
        retVal = os.popen('hg status -m -r').readline(1)
        if retVal != '':
            print '********************************************'
            print 'Warning uncommitted changes found in: ',dep[1]
            inVal = raw_input("Press \'z\' to clean the uncommitted files"
                              " and update the repository\nAll other input will leave"
                              " the repository as is and skip the update: ")
            if inVal == 'z':
                retVal = os.system("hg up -C "+branch)
                print dep[1],' --- cleaned and updated'
            else:
                print dep[1],' --- update skipped'
        else:
            retVal = os.system("hg up "+branch)
            print dep[1],' --- update to',branch
    except:
        print "Fail"

