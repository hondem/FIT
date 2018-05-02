#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdarg.h>

#define MMAP(pointer) { (pointer) = mmap(NULL, sizeof(*(pointer)), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0); }
#define UNMAP(pointer) { munmap((pointer), sizeof((pointer))); }
#define FATAL_ERROR(error_msg,exit_code){do{fprintf(stderr,"ERROR: %s\n",error_msg);exit(exit_code);}while(1);}

#define E_LOAD_ARGS 1
#define E_SEMAPHORE_FAIL -3
#define E_FILE_ERROR -4

#define SEM_MUTEX "semaphore_mutex"
#define SEM_BOARDED "semaphore_boarded"
#define SEM_BUS "semaphore_bus"
#define SEM_FILE_WRITE "semaphore_file_write"
#define SEM_RIDER_LEAVE "semaphore_rider_leave"

#define LOCKED 0
#define UNLOCKED 1

int processArgs(int argc, char *argv[], int *R, int *C, int *ART, int *ABT);
int getMin(int a, int b);
int getMax(int a, int b);
void busProcessMain(int rideInterval, int busCapacity);
void riderProcessMain();
void ridersGenProcessMain(int ridersAmount, int sleepInterval);
void initSemaphores();
void clearSemaphores();
void initSharedMemory(int _totalRiders);
void clearSharedMemory();
void writeToFile(const char *fmt, ...);

/* Semaphores */
sem_t *mutex = NULL;
sem_t *boarded = NULL;
sem_t *bus = NULL;
sem_t *file_write = NULL;
sem_t *rider_leave = NULL;

/* Shared memory variables */
int *waiting = NULL;
int *totalRiders = NULL;
int *instructionId = NULL;
int *riderId = NULL;
FILE *output = NULL;


int main(int argc, char *argv[]) {
    clearSemaphores();

    /* Args fetching and init */
    int R = 0, C = 0, ART = 0, ABT = 0;
    if(processArgs(argc, argv, &R, &C, &ART, &ABT) == 0) FATAL_ERROR("Failed to load arguments\n", E_LOAD_ARGS);

    /* Semaphores init */
    initSemaphores();

    /* Shared memory init */
    initSharedMemory(R);

    /* Duplicating process */
    pid_t busProcess = fork();

    if(busProcess == 0){
        /* If process is child */
        busProcessMain(ABT, C);
    } else if(busProcess > 0){
        /* If process is parent */
        pid_t ridersProcess = fork();

        /* Create riders generator */
        if(ridersProcess == 0){
            ridersGenProcessMain(R, ART);
        }

        waitpid(ridersProcess, NULL, 0);
    }

    waitpid(busProcess, NULL, 0);

    /* My mum and pepe says that I must tidy up my toys */
    clearSharedMemory();
    clearSemaphores();
    fclose(stdout);

    return 0;
}

/**
 * @brief Function to fetch arguments from command line
 * @param argc Number of arguments
 * @param argv Passed arguments
 * @param R Amount of riders
 * @param C Capacity of bus
 * @param ART Maximum interval between rider spawn
 * @param ABT Maximum interval of bus ride
 * @return If success, return 0, else 1
 */
int processArgs(int argc, char *argv[], int *R, int *C, int *ART, int *ABT){
    if(argc != 5) return 0;
    int retValue = 1;
    if(((*R = atoi(argv[1])) == 0) || *R <= 0) retValue = 0;
    if(((*C = atoi(argv[2])) == 0) || *C <= 0) retValue = 0;
    if(((*ART = atoi(argv[3])) == 0) || *ART < 0 || *ART > 1000) retValue = 0;
    if(((*ABT = atoi(argv[4])) == 0) || *ABT < 0 || *ABT > 1000) retValue = 0;
    return retValue;
}

/**
 * @brief Main function for bus process
 * @param rideInterval Maximum interval of bus ride
 * @param busCapacity Capacity of bus
 */
void busProcessMain(int rideInterval, int busCapacity){
    writeToFile("%d\t: BUS\t: start\n", (*instructionId)++);

    while(*totalRiders){
        sem_wait(file_write);
        writeToFile("%d\t: BUS\t: arrival\n", (*instructionId)++);
        sem_post(file_write);

        sem_wait(mutex);
        int n = getMin(*waiting, busCapacity);
        if(n > 0){
            sem_wait(file_write);
            writeToFile("%d\t: BUS\t: start boarding: %d\n", (*instructionId)++, *waiting);
            sem_post(file_write);
        }
        for(int i = 0; i < n; i++){
            sem_post(bus);
            sem_wait(boarded);
        }
        if(n > 0){
            sem_wait(file_write);
            writeToFile("%d\t: BUS\t: end boarding: %d\n", (*instructionId)++, *waiting);
            sem_post(file_write);
        }

        *waiting = getMax(*waiting - busCapacity, 0);
        sem_post(mutex);

        sem_wait(file_write);
        writeToFile("%d\t: BUS\t: depart\n", (*instructionId)++);
        sem_post(file_write);

        if(*totalRiders != 0){
            int time = rand() % rideInterval;
            usleep(time * 1000);
            sem_wait(file_write);
            writeToFile("%d\t: BUS\t: end\n", (*instructionId)++);
            sem_post(file_write);
            if(n > 0){
                for(int i = 0; i < n; i++){
                    sem_post(rider_leave);
                }
            }
        }
    }

    sem_wait(file_write);
    writeToFile("%d\t: BUS\t: finish\n", (*instructionId)++);
    sem_post(file_write);


    exit(EXIT_SUCCESS);
}

/**
 * @brief Main function for riders generator
 * @param ridersAmount Amount of riders to generate
 * @param sleepInterval Maximum interval between rider spawn
 */
void ridersGenProcessMain(int ridersAmount, int sleepInterval){

    for(int i = 0; i < ridersAmount; i++){
        pid_t new_rider = fork();
        if(new_rider == 0){
            riderProcessMain();
        }
        int time = rand() % sleepInterval;
        usleep(time * 1000);
    }

    exit(EXIT_SUCCESS);
}

/**
 * @brief Main function for rider
 */
void riderProcessMain(){
    int id = (*riderId)++;

    sem_wait(file_write);
    writeToFile("%d\t: RID %d\t: start\n", (*instructionId)++, id);
    sem_post(file_write);

    sem_wait(mutex);
    (*waiting)++;

    sem_wait(file_write);
    writeToFile("%d\t: RID %d\t: enter : %d\n", (*instructionId)++, id, *waiting);
    sem_post(file_write);

    sem_post(mutex);
    sem_wait(bus);

    sem_wait(file_write);
    writeToFile("%d\t: RID %d\t: boarding\n", (*instructionId)++, id);
    sem_post(file_write);

    (*totalRiders)--;

    sem_post(boarded);

    sem_wait(rider_leave);

    sem_wait(file_write);
    writeToFile("%d\t: RID %d\t: finish\n", (*instructionId)++, id);
    sem_post(file_write);
    exit(EXIT_SUCCESS);
}

/**
 * @brief Get greater value
 * @param a First INT
 * @param b Second INT
 * @return Greater INT
 */
int getMax(int a, int b){
    return (a >= b) ? a : b;
}

/**
 * @brief Get lower value
 * @param a First INT
 * @param b Second INT
 * @return Lower INT
 */
int getMin(int a, int b){
    return (a <= b) ? a : b;
}

/**
 * @brief Initialization of semaphores
 */
void initSemaphores(){
    mutex = sem_open(SEM_MUTEX, O_CREAT | O_EXCL, 0666, UNLOCKED);
    bus = sem_open(SEM_BUS, O_CREAT | O_EXCL, 0666, LOCKED);
    boarded = sem_open(SEM_BOARDED, O_CREAT | O_EXCL, 0666, LOCKED);
    file_write = sem_open(SEM_FILE_WRITE, O_CREAT | O_EXCL, 0666, UNLOCKED);
    rider_leave = sem_open(SEM_RIDER_LEAVE, O_CREAT | O_EXCL, 0666, LOCKED);
    if(mutex == SEM_FAILED || bus == SEM_FAILED || boarded == SEM_FAILED || file_write == SEM_FAILED || rider_leave == SEM_FAILED) FATAL_ERROR("Failed to open semaphores\n", E_SEMAPHORE_FAIL);
}

/**
 * @brief Clearing up semaphores
 */
void clearSemaphores(){
    sem_close(mutex);
    sem_close(bus);
    sem_close(boarded);
    sem_close(file_write);
    sem_close(rider_leave);
    sem_unlink(SEM_MUTEX);
    sem_unlink(SEM_RIDER_LEAVE);
    sem_unlink(SEM_BUS);
    sem_unlink(SEM_BOARDED);
    sem_unlink(SEM_FILE_WRITE);
}

/**
 * @brief Initialization of shared memory
 * @param _totalRiders Amount of riders
 */
void initSharedMemory(int _totalRiders){
    MMAP(output);
    output = fopen("proj2.out", "w");
    if(output == NULL) FATAL_ERROR("Failed to create file\n", E_FILE_ERROR);
    MMAP(waiting);
    *waiting = 0;
    MMAP(riderId);
    *riderId = 1;
    MMAP(totalRiders);
    *totalRiders = _totalRiders;
    MMAP(instructionId);
    *instructionId = 1;
}

/**
 * @brief Clear shared memory
 */
void clearSharedMemory(){
    UNMAP(waiting);
    UNMAP(output);
    UNMAP(totalRiders);
    UNMAP(riderId);
}

/**
 * @brief Write certain text to output file
 * @param fmt Text format
 * @param ... Arguments passed to be formatted
 */
void writeToFile(const char *fmt, ...){
    va_list args;
    va_start(args, fmt);
    vfprintf(output, fmt, args);
    va_end(args);
    fflush(output);
}
