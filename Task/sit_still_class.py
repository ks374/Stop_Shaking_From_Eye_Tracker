import threading
import time
import sit_still_cython #A cython package to retrieve data from dacq_data. 

class sit_still_class:
'''
This class define a subthread process to monitor the eye position. 
It can write the eye data into a csv file with timer. 
It should be able to detect shaking of the eye data and send an END signal to the task. 

-- Chenghang 4/24/2025
'''
    def __init__(self, task, app):
        self.task = task
        self.app = app
        self._running = True
        
        sit_still_init()
        
    def write_eye_data(self,filename):
        """Monitor a value and stop sprite task if needed"""
        head_writer(filename.encode('utf-8'))
        print("Start writing out the eye data. ")
        try:
            while self._running:
                sit_still_read()
                sit_still_writer(filename)
                
                #if current_value > 1:
                #    print(f"Value {current_value} exceeds threshold {self.threshold}. Stopping sprite display.")
                #    self.sprite_task.stop()
                #    self._running = False
                    
                time.sleep(0.001)  # Adjust monitoring frequency
                
        except KeyboardInterrupt:
            print("sit_still: Write eye data stopped. ")
            self._running = False