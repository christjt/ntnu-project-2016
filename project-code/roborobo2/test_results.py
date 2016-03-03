from ConfigParser import ConfigParser, RawConfigParser
import os
parser = ConfigParser()
parser.optionxform = str
parser.read('config/default-self_assembly_mechanisms.properties')
parser.set('config', 'gBatchMode', 'false')
parser.set('config', 'gDisplayMode', '0')
parser.set('config', 'gDisplayBestGenome', 'true')
with open('config/default-self_assembly_mechanisms.properties', 'w') as configFile:
    parser.write(configFile)
os.system('mpirun  -np 1 ./roborobo -l config/default-self_assembly_mechanisms.properties')


