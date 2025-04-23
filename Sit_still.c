#include "Sti_still.h"
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Shared memory pointers and identifiers
static struct DACQINFO *dacq_data = NULL;  // Defined in datainfoe.h
static int shm_id = -1;
static int semid = -1;

// Data buffer configuration
#define BUFFER_SIZE 1024
static int buffer_x[BUFFER_SIZE];
static int buffer_y[BUFFER_SIZE];
static int buffer_index = 0;

void init() {
  if ((shmid = shmget((key_t)SHMKEY,
		      sizeof(DACQINFO), 0666 | IPC_CREAT)) < 0) {
    perror2("shmget", __FILE__, __LINE__);
    fprintf(stderr, "Sit_still:init -- kernel compiled with SHM/IPC?\n");
    exit(1);
  }

  if ((dacq_data = shmat(shmid, NULL, 0)) == NULL) {
    perror2("shmat", __FILE__, __LINE__);
    fprintf(stderr, "Sit_still:init -- kernel compiled with SHM/IPC?\n");
    exit(1);
  }
  if ((semid = psem_init(SEMKEY)) < 0) {
    perror("psem_init");
    fprintf(stderr, "%s: can't init semaphore\n", progname);
    exit(1);
  }
    
    // Replace with your shared memory key/ID
    key_t shm_key = 0x1234;  
    size_t shm_size = sizeof(struct ShmData);

    // Attach to existing shared memory
    shm_id = shmget(shm_key, shm_size, 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    shm_ptr = (struct ShmData *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }
}

void halt() {
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
    }
    shm_ptr = NULL;
}

void record() {
    if (!shm_ptr || buffer_index >= BUFFER_SIZE) {
        fprintf(stderr, "Buffer full or SHM not initialized\n");
        return;
    }
    // Copy data from shared memory to buffer
    memcpy(&buffer[buffer_index], shm_ptr, sizeof(struct ShmData));
    buffer_index++;
}