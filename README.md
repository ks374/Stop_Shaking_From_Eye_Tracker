# Stop_Shaking_From_Eye_Tracker
Train the animal to stop shaking based on his/her eye data


## Plan: 
Write a stopper.c and stopper.h: 
    We need to include the dacqinfo.h so our code know the structure of the semid. 
    Importantly, this needs to be same as the current PYPE version. So we need dacqinfo_dacq.h and dacqinfo_dacq2p.h. Need an argument to select the correct .h file. 
    
    main(): 
        handle the include of dacqinfo.h file. 
        get the semid segment. (cope the part of code from comedi_server.c)
        Init a timer. 
        Fetch eye position x and y as quick as possible. Save the eye data together with the timer. 
        Have a data writer to write everything into a text or csv file. 
        
    Analyzer: 
        Position buffer: save a series of timer, eye position x and y. 
        The analyzer will have a spatial 
        For example, if a shake continues for 2 seconds, and the monkey move left and right 5 times, each vibration will be 400ms. 