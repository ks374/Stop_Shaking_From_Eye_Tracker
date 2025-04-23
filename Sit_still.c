#include "Sit_still.h"
#include <stddef.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Shared memory pointers and identifiers
static struct DACQINFO *dacq_data = NULL;  // Defined in datainfoe.h
static int shmid = -1;
static int semid = -1;

// Data buffer configuration
#define BUFFER_SIZE 1024
static int buffer_x[BUFFER_SIZE];
static int buffer_y[BUFFER_SIZE];
static double buffer_time[BUFFER_SIZE];
static int buffer_index = 0; //To make writer easier, the pointer only points to the position with recently added data. 

static struct timespec start_time;

void init() {
  if ((shmid = shmget((key_t)SHMKEY,
		      sizeof(DACQINFO), 0666 | IPC_CREAT)) < 0) {
    fprintf(stderr, "Sit_still:init -- kernel compiled with SHM/IPC?\n");
    exit(1);
  }

  if ((dacq_data = shmat(shmid, NULL, 0)) == NULL) {
    fprintf(stderr, "Sit_still:init -- kernel compiled with SHM/IPC?\n");
    exit(1);
  }
  if ((semid = psem_init(SEMKEY)) < 0) {
    perror("psem_init");
    fprintf(stderr, "Sit_still: can't init semaphore\n");
    exit(1);
  }
  clock_gettime(CLOCK_MONOTONIC, &start_time);
}

void halt() {
    if (shmdt(dacq_data) < 0) {
    perror("shmdt");
    }
    psem_free(semid);
}

static int buffer_check(){
    //Make sure the buffer_index is wihtin a reasonable range. 
    if (buffer_index >= BUFFER_SIZE){
        return (buffer_index % BUFFER_SIZE);
    }
    return buffer_index;
}

void read() {
    //Read dacq_data into the buffer once. It should be called wihtin some mainloop(). 
    if (!dacq_data) {
        fprintf(stderr, "Sti_still: Did not find dacq_data properly. \n");
        return;
    }
    
    buffer_index++;
    buffer_index = buffer_check();
    
    buffer_x[buffer_index] = dacq_data -> eye_x;
    buffer_y[buffer_index] = dacq_data -> eye_y;
    
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC,&now);
    buffer_time[buffer_index] = (now.tv_sec - start_time.tv_sec) + (now.tv_nsec-start_time.tv_nsec)/1e9;
}

void head_writer(char *filename) {
    FILE *fp = fopen(filename,"a");
    if (fp == NULL) {
        perror("fopen");
        return;
    }
    
    fprintf(fp,"TimeStamp,x,y");
    fclose(fp);
}

void writer(char *filename) {
    //This function is designed to simply read the eye positions. 
    //It does not include the read() function, so update the buffer first before doing anything. 
    FILE *fp = fopen(filename,"a");
    if (fp == NULL) {
        perror("fopen");
        return;
    }
    
    fprintf(fp,"%.6f,%d,%d\n",buffer_time[buffer_index],buffer_x[buffer_index],buffer_y[buffer_index]);
    fclose(fp);
}

