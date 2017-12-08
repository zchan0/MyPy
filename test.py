#!/usr/bin/python

import os, sys
import fnmatch
import subprocess
import filecmp

def testCode( retcode, msg ):
  if retcode > 0:
    print msg
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
        print "test case", x[:-3]+'.out', "doesn't exist"
        sys.exit( 1 )
      if not filecmp.cmp("/tmp/out", output):
        subprocess.call("diff "+output+" /tmp/out -y",shell=True) 
        print "\tTEST CASE FAILED", x
      else :
        print "\x1b[6;30;42m" + "testcase:", x, "passed" + "\x1b[0m"


