def sit_still_init():
    init()

def sit_still_halt():
    halt()

def sit_still_read():
    read_eyedata()

def sit_still_head_writer(filename: str):
    head_writer(filename.encode('utf-8'))

def sit_still_writer(filename: str):
    writer(filename.encode('utf-8'))