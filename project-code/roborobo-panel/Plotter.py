from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import Tkinter as Tk


class Plotter(Tk.Canvas, FileSystemEventHandler):

    def __init__(self, root, log_path):
        observer = Observer()
        observer.schedule(self, log_path)
        observer.start()

        f = Figure(figsize=(6, 6), dpi=100)
        self.plot = f.add_subplot(111)
        self.plot.set_ylim([0, 1.2])
        self.canvas = FigureCanvasTkAgg(f, master=root)
        self.canvas.show()
        self.canvas.get_tk_widget().pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

        toolbar = NavigationToolbar2TkAgg(self.canvas, root)
        toolbar.update()
        self.canvas._tkcanvas.pack(side=Tk.TOP, fill=Tk.BOTH, expand=1)

    def on_modified(self, event):
        with open(event.src_path, 'r') as log:
            self.update(log.readlines())

    def update(self, log):
        genome_points = []
        elite_points = []
        for line in log:
            genomes, elites = line.split(':')
            best_genome = max([float(fitness) for fitness in genomes.split(',')])
            genome_points.append(best_genome)
            if len(elites) > 1:
                best_elite = max([float(fitness) for fitness in elites.split(',')])
                elite_points.append(best_elite)
        self.plot.cla()
        self.plot.plot(genome_points, label='best fitness')
        self.plot.plot(elite_points, label='elite fitness')
        self.plot.legend()
        self.plot.set_ylim([0, 1.2])
        self.canvas.show()

