#!/usr/bin/python

import os, sys
import fnmatch
import subprocess
import filecmp

# https://stackoverflow.com/a/287944
class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def testCode( retcode, msg ):
  if retcode > 0:
    print bcolors.WARNING + msg + bcolors.ENDC
    sys.exit( 1 )

testDir = os.path.join( os.getcwd(), 'cases')
if not os.path.isdir( testDir ):
  print testDir, "isn't a directory"
  sys.exit( 1 )

executable = os.path.join(os.getcwd(), "run")
if not os.path.isfile( executable ):
  retcode = subprocess.call("make",shell=True)
  testCode( retcode, "\tFAILED to make the scanner" )

def generateResult(testFile, outFile):
    retcode = subprocess.call("python "+testFile+">"+outFile, shell=True)
    fileH = open(output, 'r')
    lines = fileH.readlines()
    fileH.close()

files = os.listdir( testDir )
for x in files:
  if fnmatch.fnmatch(x, "*.py"):
    testcase = os.path.join(testDir, x)
    output = testcase[:-3]+".out"
    generateResult(testcase, output)

    retcode = subprocess.call("./run < "+testcase+"> /tmp/out",shell=True)
    if retcode < 0:
      testCode( retcode, "\tFAILED to run test case "+x)
    else:
      if not os.path.isfile( output ):
        print bcolors.FAIL + "test case", x[:-3]+'.out', "doesn't exist" + bcolors.ENDC
        sys.exit( 1 )
      if not filecmp.cmp("/tmp/out", output):
        subprocess.call("diff "+output+" /tmp/out -y",shell=True)
        print bcolors.FAIL + "\tTEST CASE FAILED", x + bcolors.ENDC
      else :
        print bcolors.OKGREEN + "testcase:", x, "passed" + bcolors.ENDC


