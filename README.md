# Stop_Shaking_From_Eye_Tracker
Train the animal to stop shaking based on his/her eye data

# How to use: 
pip/conda install Cython if you don't have it. 
Compile sit_still.c in your working python environment using: 
python ./Cython_compile.py build_ext --inplace

Use use the methods, use: 
from sit_still_cython import *

Check the Task folder for example task files. 


## Methods: 
Sit_still.c: 
    We need to include the dacqinfo.h so our code know the structure of the semid. 
    Importantly, this needs to be same as the current PYPE version. So we need dacqinfo_dacq.h and dacqinfo_dacq2p.h. Need an argument to select the correct .h file. 
    
    init(): 
        handle the include of dacqinfo.h file. 
        get the semid segment. (cope the part of code from comedi_server.c)
    
    halt():
        Stop the semid and release the segment. 
        
    Record():
        Init a timer. 
        Fetch eye position x and y as quick as possible. Save the eye data together with the timer. 
        Have a data writer to write everything into a text or csv file. 
        
    Analyzer(): 
        Position buffer: save a series of timer, eye position x and y. 
        Spatial filter: The analyzer will have a spatial filter: based on the base measurement. 
        Frequency filter: For example, if a shake continues for 2 seconds, and the monkey move left and right 5 times, each vibration will be 400ms. 
        