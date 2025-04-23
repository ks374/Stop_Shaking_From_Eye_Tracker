cdef extern from "Sit_still.h":       
    void init()
    void halt()
    void read()
    void head_writer(char *filename)
    void writer(char *filename)