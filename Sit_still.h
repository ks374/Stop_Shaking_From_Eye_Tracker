#ifndef SIT_STILL_H
#define SIT_STILL_H

#include "dacqinfo_old.h"
#include "psems.h"

void init();
void halt();
void read_eyedata();
void head_writer(char *filename);
void writer(char *filename);
//void analyzer();

#endif
