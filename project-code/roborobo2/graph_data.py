import json
import sys
from pprint import pprint

analyzed_results = sys.argv[1]

def read_results():
	with open(analyzed_results, 'r') as data_file:
		data = json.loads(data_file.read())
	return data

def getDataTouples(graph_param):
	results = read_results()
	dataTouples = []

	for i in range(0, len(results)):
		dataTouples.append((i, results[str(i)][graph_param]))

	return dataTouples

def generatePlot(title, xLabel, yLabel, xMin, xMax, yMin, yMax, dataPointsMost, dataPointsLeast, dataPointsAverage, dataPointsSD):

	xTicks = generateTicks(int(xMin), int(xMax))
	yTicks = generateTicks(int(yMin), int(yMax))

	plotString = ''
	plotString += '\\begin{tikzpicture}\n'
	plotString += '\\begin{axis}[\n'
	
	plotString += '\ttitle={%s},\n' % title
	plotString += '\txlabel={%s},\n' % xLabel
	plotString += '\tylabel={%s},\n' % yLabel
	plotString += '\txmin=%s, xmax=%s,\n' % (xMin, xMax)
	plotString += '\tymin=%s, ymax=%s,\n' % (yMin, yMax)
	plotString += '\txtick={%s},\n' % xTicks
	plotString += '\tytick={%s},\n' % yTicks
	plotString += '\tymajorgrids=%s,\n' % 'true'
	plotString += '\tgrid style=%s,\n' % 'dashed'
	
	plotString += ']\n\n'

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'green'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsMost
	plotString += '\t};\n'

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'blue'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsAverage
	plotString += '\t};\n'

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'red'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsLeast
	plotString += '\t};\n'

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'blue!50'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsSD
	plotString += '\t};\n'

	plotString += '\\end{axis}\n'
	plotString += '\\end{tikzpicture}\n'
	
	

	return plotString

def generateTicks(var_min, var_max):
	delta = float(var_max - var_min) / 5
	ticks = []
	for i in range(0, 6):
		ticks.append(i*delta)
	return str(ticks)[1: len(str(ticks)) - 1].replace(', ', ',')

def convertTupleArrayToString(array):
	return str(array)[1: len(str(array)) - 1].replace('), ', ')').replace(', ', ',')


def main():
	data_properties = [
				'robots_eaten', 'energy_consumed_by_robot', 'group_size', 
				'energy_consumed_by_group', 'fitness', 'number_of_groups',
				'predators_eaten', 'robots_starved'
				]
				
	titles = [
			'Number of Robots Eaten per Generation',
			'Energy Consumed by Robot per Generation',
			'Size of Robot Groups per Generation',
			'Energy Consumed by Group Robots',
			'Fitness per Generation',
			'Number of Robot Groups per Generation',
			'Number of Predators Eaten',
			'Number of Robots Starved'
			]

	yBoundsList = ['0,25', '0,60', '0,3', '0,140', '0,1', '0,8', '0,8', '0,15']

	for i in range(0, 8):
	
		data_property = data_properties[i]
		fig_title = titles[i]
		x_label = 'Generation'
		y_label = titles[i].replace(' per Generation', '')
		xBounds = '0,150'.split(',')
		yBounds = yBoundsList[i].split(',')

		dataPointsMost = convertTupleArrayToString(getDataTouples('most_' + data_property))
		dataPointsLeast = convertTupleArrayToString(getDataTouples('least_' + data_property))
		dataPointsAverage = convertTupleArrayToString(getDataTouples('average_' + data_property))
		dataPointsSD = convertTupleArrayToString(getDataTouples('std_dev_' + data_property))

		plotString = generatePlot(fig_title, x_label, y_label, xBounds[0], xBounds[1], yBounds[0], yBounds[1], dataPointsMost, dataPointsLeast, dataPointsAverage, dataPointsSD)

		filename = data_properties[i] + '-' + analyzed_results.replace('.json', '').replace('.', '-') + '.tex'

		writeToFile(plotString, filename)


def writeToFile(plotString, nameOfFile):
	fig_file = open(nameOfFile, 'w')
	fig_file.write(plotString)
	fig_file.close()

main();	










