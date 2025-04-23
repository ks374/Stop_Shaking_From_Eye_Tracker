#ifndef SIT_STILL_H
#define SIT_STILL_H 

#include "dacqinfo_dacq.h"
#include "psems.h"

void init();
void halt();
void read();
void head_writer(char *filename);
void writer(char *filename);
//void analyzer();

#endif