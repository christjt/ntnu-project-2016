from ConfigParser import ConfigParser, RawConfigParser
import os
import sys

n_trials = int(sys.argv[1])
initial_seed = int(sys.argv[2])
processes = int(sys.argv[3])
results_folder = sys.argv[4]


def run_trial(trial, seed):
    parser = ConfigParser()
    parser.optionxform = str
    parser.read('config/default-self_assembly_mechanisms.properties')
    parser.set('config', 'gBatchMode', 'true')
    parser.set('config', 'gDisplayMode', '2')
    parser.set('config', 'gDisplayBestGenome', 'false')
    parser.set('config', 'gRandomSeed', str(seed))
    parser.set('config', 'gStatisticsLog', os.path.join(results_folder, 'trial_%d.json' % trial))
    with open('config/generated-self_assembly_mechanisms.properties', 'w') as configFile:
        parser.write(configFile)

    os.system('mpirun  -np %d ./roborobo -l config/generated-self_assembly_mechanisms.properties' % processes)

for i in range(0, n_trials):
    print 'Running trial %d' % i
    run_trial(i, initial_seed + i*10)



