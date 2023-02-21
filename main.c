#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// declare global variables including a table structure to hold scheduling information
struct node {
    int id, arrival, total_cpu, total_remaining, done, start_time, already_started, end_time, turnaround_time;

} *table_ptr = NULL;
typedef struct node table_type;

// Number of processes from user
int num_processes;

// optional: define a function that finds the maximum of two integers
#define max(a,b) (a > b ? a : b)

//***************************************************************
void PROCEDURE_TO_PRINT_THE_CONTENTS_OF_THE_SCHEDULING_TABLE() {
// declare local variables
// print table header
    printf("ID\tArrival Total\tStart\tEnd\tTurnaround");
    printf("--------------------------------------------------");
// for each process
    for(int i = 0; i < num_processes; i++) {
        // print the contents (id, arrival time, total_cycles) of each field of the table's index
        printf("%d\t%d\t%d\t", table_ptr[i].id, table_ptr[i].arrival, table_ptr[i].total_cpu);
        // if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time)
        if(table_ptr[i].done == 1) {
            printf("%d\t%d\t%d\t", table_ptr[i].start_time, table_ptr[i].end_time, table_ptr[i].turnaround_time);
        }
    }
    printf("\n");
return;
}


//*************************************************************
void PROCEDURE_FOR_OPTION_1() {
// declare local variables
// prompt for total number of processes
// allocate memory for table to hold process parameters
// for each process
// prompt for process id, arrival time, and total cycle time
// print contents of table
return;
}


//*************************************************************
void PROCEDURE_FOR_OPTION_2() {
// declare (and initilize when appropriate) local variables
// for each process, reset "done" field to 0
// while there are still processes to schedule
// initilize the earliest arrival time to INT_MAX (largest integer value)
// for each process not yet scheduled
// check if process has earlier arrival time than current earliest and update
// set start time, end time, turnaround time, done fields for unscheduled process with earliest arrival time
// update current cycle time and increment number of processes scheduled
// print contents of table
return;
}


//*************************************************************
void PROCEDURE_FOR_OPTION_3() {
// declare (and initilize when appropriate) local variables
// for each process, reset "done" field to 0
// while there are still processes to schedule
// initilize the lowest total cycle time to INT_MAX (largest integer value)
// for each process not yet scheduled
// check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update
// set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
// update current cycle time and increment number of processes scheduled
// print contents of table
return;
}


//*************************************************************
void PROCEDURE_FOR_OPTION_4() {
// declare (and initilize when appropriate) local variables
// for each process, reset "done", "total_remaining" and "already_started" fields to 0
// while there are still processes to schedule
// initilize the lowest total remaining time to INT_MAX (largest integer value)
// for each process not yet scheduled
// check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update
// check if process already partially-scheduled
// if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time
// set end time, turnaround time of process with lowest (and available) total remaining cycle time
// decrement total remaining time of process with lowest (and available) total remaining cycle time
// if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes
// print contents of table
return;
}


//*************************************************************
void PROCEDURE_FOR_OPTION_5() {
// free the schedule table if not NULL
return;
}


//*************************************************************
int main() {
    // declare local vars
    // while user has not chosen to quit
    // print menu of options
    // prompt for menu selection
    // call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
     // while loop
return 1; // indicates success
} // end of procedure
