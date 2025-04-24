import sys, types,os
from pype import *
import pygame as pg
import sit_still_class
import threading

"""
	Simple task that record eye data. 

	11/14/2024
	Chenghang
"""
def RunSet(app):
    app.taskObject.RunSet(app)

def cleanup(app):
    app.taskObject.cleanup(app)
    
def main(app):
    filename = "~\\Name.csv"
    task = fixationTask(app)
    sit_still_task = sit_still_class(task,app)
    
    app.taskObject = fixationTask(app)
    app.globals = Holder()
    app.idlefb()
    
    sit_still_thread = threading.Thread(target=sit_still_task.write_eye_data(filename),daemon=True)
    sit_still_thread.start()
    
    try:
        app.startfn = RunSet
    finally:
        task.cleanup()
        sit_still_task._running = False
        sit_still_thread.join(timeout = 1)

class fixationTask:

    def __init__(self,app):
        self.app = app

    def cleanup(self):
        #delete parameter table and anything else we created
        self.myTaskParams.destroy()

    def RunSet(self,app):
    	"""
	This is what is run when you hit the 'start' button (set as such in
	the 'main' function, defined at the end of this file).
	"""
	con(app,"Experiment start...\n")
	while True:
		UserInput = input("Num_drop = ")
		if UserInput > 0:
			for i in range(UserInput):
				app.reward(multiplier=5)
				app.idlefn(50)#time between juice drops
			UserInput = 0
		else:
			break;

