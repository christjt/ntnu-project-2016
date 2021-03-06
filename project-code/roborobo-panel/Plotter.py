from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
from math import sqrt
import Tkinter as Tk
from os import path

class Plotter(Tk.Canvas, FileSystemEventHandler):

    def __init__(self, root, log_path):
        observer = Observer()
        observer.schedule(self, path.dirname(log_path))
        observer.start()
        self.log_path = log_path
        f = Figure(figsize=(6, 6), dpi=100)
        self.plot = f.add_subplot(111)
        self.plot.set_ylim([0, 1.4])
        self.canvas = FigureCanvasTkAgg(f, master=root)
        self.canvas.show()
        self.canvas.get_tk_widget().pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

        toolbar = NavigationToolbar2TkAgg(self.canvas, root)
        toolbar.update()
        self.canvas._tkcanvas.pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

    def on_modified(self, event):
        if event.src_path != self.log_path:
            return
        with open(event.src_path, 'r') as log:
            self.update(log.readlines())

    def update(self, log):
        genome_points = []
        elite_points = []
        avg_points = []
        sd_points = []
        for line in log:
            genomes, elites = line.split(':')
            fitness_values = [float(fitness) for fitness in genomes.split(',')]
            best_genome = max(fitness_values)
            genome_points.append(best_genome)
            avg_fitness = sum(fitness_values)/len(fitness_values)
            avg_points.append(avg_fitness)
            standard_dev = sqrt((1.0/len(fitness_values)*sum([(fitness - avg_fitness)*(fitness - avg_fitness) for fitness in fitness_values])))
            sd_points.append(standard_dev)
            if len(elites) > 1:
                best_elite = max([float(fitness) for fitness in elites.split(',')])
                elite_points.append(best_elite)
            else:
                elite_points.append(0)
        self.plot.cla()
        self.plot.plot(genome_points, label='Best fitness')
        self.plot.plot(elite_points, label='Elite fitness')
        self.plot.plot(avg_points, label='Avg fitness')
        self.plot.plot(sd_points, label='SD fitness')
        self.plot.legend()
        self.plot.set_ylim([0, 1.4])
        self.canvas.show()

