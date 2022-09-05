#!/usr/bin/env python 
"""
This scipt will update Underworld repositories to a specific branch.
The one argument this script uses is the branch name, eg.
	./updateRepos.py v1.3.x

"""

from mercurial import hg, ui, util
import urllib2
import ConfigParser
import os, errno
import sys

# check if there are 
if len(sys.argv) != 2:
   print "ERROR - must supply one argument only (the branch name), currently\n" 
   print sys.argv
   print "\nExample usage: ./updateRepos.py v1.3.x\n\n"
   sys.exit()

isGood = 0

# search input arg as a valid branch
branches = os.popen('hg branches').readlines()
for branch in branches:
   if( sys.argv[1] == branch.split(" ")[0] ):
      isGood = 1

if( isGood == 0 ):
   # search input arg as a valid tag
   tags = os.popen('hg tags').readlines()
   for tag in tags:
      if( sys.argv[1] == tag.split(" ")[0]):
         isGood = 1

if( isGood != 1 ):
   print "Invalid argument, cannot update the repository to " + sys.argv[1] 
   sys.exit(1)

# Get all the project directories. Check if the ".hg" directory exists on each one of them.
allDirs = os.listdir(os.curdir)
projects=['.']
for dir in allDirs:
   if os.path.exists(dir + "/.hg"):
      projects.append(dir)    

cwd = os.getcwd()

for dep in projects:
   if not os.path.exists(cwd + "/" + dep ):
      continue

   os.chdir(cwd + "/" + dep)

   retVal = os.popen('hg status -m -r').readline(1)
   if( retVal != '' ):
      print '********************************************'
      print 'Warning uncommitted changes found in: ',dep
      inVal = raw_input("Press \'z\' to clean the uncommitted files"
      " and update the repository\nAll other input will leave"
      " the repository as is and skip the update: ")
      if( inVal == 'z' ):
         retVal = os.system("hg up -C "+sys.argv[1])
         print dep,' --- cleaned and updated'
      else:
         print dep,' --- update skipped'
   else:
         retVal = os.system("hg up "+sys.argv[1])
         print dep,' --- update to',sys.argv[1]






















