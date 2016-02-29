import Tkinter as Tk
import matplotlib
from Plotter import Plotter
from math import sin, pi
from numpy import arange
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
matplotlib.use('TKAgg')
from matplotlib.figure import Figure

root = Tk.Tk()
plotter = Plotter(root, '../roborobo2/prj/SelfAssemblyMechanisms/data/ea')

run_btn = Tk.Button(root, text="run");

root.mainloop()

