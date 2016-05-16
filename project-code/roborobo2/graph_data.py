import json
import sys
from pprint import pprint

analyzed_results = sys.argv[1]
graphs_out_file = sys.argv[2]

def read_results():
	with open(analyzed_results, 'r') as data_file:
		data = json.loads(data_file.read())
	return data

def getDataTouples(graph_param):
	results = read_results()
	dataTouples = []

	for i in range(0, len(results)):
		dataTouples.append((i, results[str(i)][graph_param][0]))

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
	plotString += '\tlegend pos=%s,\n' % 'outer north east'
	plotString += '\tymajorgrids=%s,\n' % 'true'
	plotString += '\tgrid style=%s,\n' % 'dashed'
	
	plotString += ']\n\n'

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'green'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsMost
	plotString += '\t};\n'
	plotString += '\t\\addlegend{%s}\n' % 'Best case'

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'blue'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsAverage
	plotString += '\t};\n'
	plotString += '\t\\addlegend{%s}\n' % 'Average case'

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'red'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsLeast
	plotString += '\t};\n'
	plotString += '\t\\addlegend{%s}\n' % 'Worst case' 

	plotString += '\\addplot[\n'
	plotString += '\tcolor=%s,\n' % 'blue!50'
	plotString += '\t]\n'
	plotString += '\tcoordinates {\n'
	plotString += '\t%s\n' % dataPointsSD
	plotString += '\t};\n'
	plotString += '\t\\addlegend{%s}\n' % 'Standard Deviation' 

	plotString += '\\end{axis}\n'
	plotString += '\\end{tikzpicture}\n'
	
	

	return plotString

def generateTicks(var_min, var_max):
	delta = (var_max - var_min) / 5
	ticks = []
	for i in range(0, 6):
		ticks.append(i*delta)
	return str(ticks)[1: len(str(ticks)) - 1].replace(', ', ',')

def convertTupleArrayToString(array):
	return str(array)[1: len(str(array)) - 1].replace('), ', ')').replace(', ', ',')


def main():
	data_property = raw_input('Name of json property to graph(ex. robots_eaten): ')
	fig_title = raw_input('Title of figure: ')
	x_label = raw_input('Label for x-axis: ')
	y_label = raw_input('Label for y-axis: ')
	xBounds = raw_input('Boundaries for x-axis(ex. 0,150): ').split(',')
	yBounds = raw_input('Boundaries for y-axis(ex. 0,150): ').split(',')

	dataPointsMost = convertTupleArrayToString(getDataTouples('most_' + data_property))
	dataPointsLeast = convertTupleArrayToString(getDataTouples('least_' + data_property))
	dataPointsAverage = convertTupleArrayToString(getDataTouples('average_' + data_property))
	dataPointsSD = convertTupleArrayToString(getDataTouples('average_' + data_property))

	plotString = generatePlot(fig_title, x_label, y_label, xBounds[0], xBounds[1], yBounds[0], yBounds[1], dataPointsMost, dataPointsLeast, dataPointsAverage, dataPointsSD)

	writeToFile(plotString)


def writeToFile(string):
	fig_file = open(graphs_out_file, 'w')
	fig_file.write(string)
	fig_file.close()

main();	










