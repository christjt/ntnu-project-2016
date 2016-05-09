from ConfigParser import ConfigParser, RawConfigParser
import os
import sys
parser = ConfigParser()
parser.optionxform = str
parser.read('config/default-self_assembly_mechanisms.properties')
parser.set('config', 'gBatchMode', 'true')
parser.set('config', 'gDisplayMode', '2')
parser.set('config', 'gDisplayBestGenome', 'false')

with open('config/generated-self_assembly_mechanisms.properties', 'w') as configFile:
    parser.write(configFile)
os.system('mpirun  -np %s ./roborobo -l config/generated-self_assembly_mechanisms.properties' % sys.argv[1])


