// Michael Granberry
// COMP 322L
// Lab 2 - Batch Process Scheduling
// Spring 2023

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
    printf("ID\tArrival\tTotal\tStart\tEnd\tTurnaround\n");
    printf("--------------------------------------------------\n");
// for each process
    for(int i = 0; i < num_processes; i++) {
        // print the contents (id, arrival time, total_cycles) of each field of the table's index
        printf("p%d\t%d\t%d\t", table_ptr[i].id, table_ptr[i].arrival, table_ptr[i].total_cpu);
        // if process has been scheduled ("done" field is 1, print other contents (start time, end time, turnaround time)
        if(table_ptr[i].done == 1) {
            printf("%d\t%d\t%d", table_ptr[i].start_time, table_ptr[i].end_time, table_ptr[i].turnaround_time);
        }
        printf("\n");
    }

return;
}


//*************************************************************
void PROCEDURE_FOR_OPTION_1() {
    // declare local variables
    // prompt for total number of processes
    printf("How many processes: \n");
    scanf("%d", &num_processes);
    // allocate memory for table to hold process parameters
    table_ptr = (table_type* )calloc(num_processes, sizeof(table_type));
    // for each process
    for(int i = 0; i < num_processes; i++) {
        // prompt for arrival time, and total cycle time
        table_ptr[i].id = i;
        printf("Enter arrival cycle for process p%d: \n", i);
        scanf("%d",&table_ptr[i].arrival);
        printf("Enter total cycles for process p%d \n", i);
        scanf("%d",&table_ptr[i].total_cpu);
    }

    // print contents of table
    PROCEDURE_TO_PRINT_THE_CONTENTS_OF_THE_SCHEDULING_TABLE();
    return;
}


//*************************************************************
//FIFO algorithm
void PROCEDURE_FOR_OPTION_2() {
    // declare (and initialize when appropriate) local variables
    int number_of_done_processes = 0;
    int earliest_arrival;
    int earliest_index;
    int current_cycle = 0;
    // for each process, reset "done" field to 0
    for( int i = 0; i < num_processes; i++) {
        table_ptr[i].done = 0;
    }
    // while there are still processes to schedule
    while (number_of_done_processes < num_processes) {
        // initialize the earliest arrival time to INT_MAX (the largest integer value)
        earliest_arrival = INT_MAX;
        // for each process not yet scheduled
        for (int i = 0; i < num_processes; i++){
            if (table_ptr[i].done == 0) {
                // check if process has earlier arrival time than current earliest and update
                if(table_ptr[i].arrival < earliest_arrival){
                    earliest_arrival = table_ptr[i].arrival;
                    earliest_index = i;
                } //if
            } //if
        }//for
        // set start time, end time, turnaround time, done fields for unscheduled process with the earliest arrival time
        table_ptr[earliest_index].start_time = max(table_ptr[earliest_index].arrival, current_cycle);
        table_ptr[earliest_index].end_time = table_ptr[earliest_index].start_time + table_ptr[earliest_index].total_cpu;
        table_ptr[earliest_index].turnaround_time = table_ptr[earliest_index].end_time - table_ptr[earliest_index].arrival;

        // update current cycle time and increment number of processes scheduled
        current_cycle = table_ptr[earliest_index].end_time;
        table_ptr[earliest_index].done = 1;
        number_of_done_processes++;
    }// while

    // print contents of table
    PROCEDURE_TO_PRINT_THE_CONTENTS_OF_THE_SCHEDULING_TABLE();
    return;
}


//*************************************************************
//SJF algorithm
void PROCEDURE_FOR_OPTION_3() {
    // declare (and initialize when appropriate) local variables
    int number_of_done_processes = 0;
    int lowest_index;
    int lowest_total_cycle_time;
    int current_cycle = 0;
    int at_least_one; //at least one process is ready

    // for each process, reset "done" field to 0
    for( int i = 0; i < num_processes; i++) {
        table_ptr[i].done = 0;
    }

    // while there are still processes to schedule
    while (number_of_done_processes < num_processes) {
        // initialize the lowest total cycle time to INT_MAX (the largest integer value)
        lowest_total_cycle_time = INT_MAX;
        at_least_one = 0;
        // for each process not yet scheduled
        for (int i = 0; i < num_processes; i++) {
            if (table_ptr[i].done == 0) {
                // check if process has lower total cycle time than current lowest and has arrival time less than current cycle time and update
                if ((table_ptr[i].total_cpu < lowest_total_cycle_time) && (table_ptr[i].arrival <= current_cycle)) {
                    at_least_one = 1;
                    lowest_total_cycle_time = table_ptr[i].total_cpu;
                    lowest_index = i;
                }//if
            }//if

        }//for

        if (at_least_one == 0) {
            current_cycle++;
        }
        else {
            // set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
            table_ptr[lowest_index].start_time = max(table_ptr[lowest_index].arrival, current_cycle);
            table_ptr[lowest_index].end_time = table_ptr[lowest_index].start_time + table_ptr[lowest_index].total_cpu;
            table_ptr[lowest_index].turnaround_time = table_ptr[lowest_index].end_time - table_ptr[lowest_index].arrival;

            // update current cycle time and increment number of processes scheduled
            current_cycle = table_ptr[lowest_index].end_time;
            table_ptr[lowest_index].done = 1;
            number_of_done_processes++;
        }
    }//while

    // print contents of table
    PROCEDURE_TO_PRINT_THE_CONTENTS_OF_THE_SCHEDULING_TABLE();
    return;
}


//*************************************************************
//SRT algorithm
void PROCEDURE_FOR_OPTION_4() {

    // check if process already partially-scheduled
    // if so, set "start time", "already_started" fields of process with lowest (and available) total remaining cycle time
    // set end time, turnaround time of process with lowest (and available) total remaining cycle time
    // decrement total remaining time of process with lowest (and available) total remaining cycle time
    // if remaining time is 0, set done field to 1, increment cycle time and number of scheduled processes

    // declare (and initialize when appropriate) local variables
    int number_of_done_processes = 0;
    int lowest_index;
    int lowest_remaining;
    int current_cycle = 0;
    int at_least_one; //at least one process is ready

    // for each process, reset "done", "total_remaining" and "already_started" fields to 0
    for( int i = 0; i < num_processes; i++) {
        table_ptr[i].done = 0;
        table_ptr[i].already_started = 0;
        table_ptr[i].total_remaining = table_ptr[i].total_cpu;
    }

    // while there are still processes to schedule
    while (number_of_done_processes < num_processes) {
        // initialize the lowest total remaining time to INT_MAX (the largest integer value)
        lowest_remaining = INT_MAX;
        at_least_one = 0;
        // for each process not yet scheduled
        for (int i = 0; i < num_processes; i++) {
            if (table_ptr[i].done == 0) {
                // check if process has lower total remaining time than current lowest and has arrival time less than current cycle time and update
                if ((table_ptr[i].total_remaining < lowest_remaining) && (table_ptr[i].arrival <= current_cycle)) {
                    at_least_one = 1;
                    lowest_remaining = table_ptr[i].total_remaining;
                    lowest_index = i;
                }//if
            }//if

        }//for

        if (at_least_one == 0) {
            current_cycle++;
        }
        else {
            // set start time, end time, turnaround time, done fields for unscheduled process with lowest (and available) total cycle time
            if (table_ptr[lowest_index].already_started == 0) {
                table_ptr[lowest_index].start_time = max(table_ptr[lowest_index].arrival, current_cycle);
                table_ptr[lowest_index].already_started = 1;
            }

            table_ptr[lowest_index].end_time = current_cycle + 1;
            table_ptr[lowest_index].turnaround_time = table_ptr[lowest_index].end_time - table_ptr[lowest_index].arrival;
            table_ptr[lowest_index].total_remaining--;

            // update current cycle time and increment number of processes scheduled
            current_cycle++;
            if (table_ptr[lowest_index].total_remaining == 0) {
                table_ptr[lowest_index].done = 1;
                number_of_done_processes++;
            }//if
        }//else
    }//while

    // print contents of table
    PROCEDURE_TO_PRINT_THE_CONTENTS_OF_THE_SCHEDULING_TABLE();
}


//*************************************************************
//Free memory
void PROCEDURE_FOR_OPTION_5() {
    // free the schedule table if not NULL
    if (table_ptr != NULL) {
        free(table_ptr);
    }
    table_ptr = NULL;
return;
}

//*************************************************************
void menu () {
    // declare local vars
    int sel = 0;
    do {
        // print menu of options
        printf("\nBatch scheduling\n");
        printf("----------------\n");
        printf("1) Enter parameters\n");
        printf("2) Schedule processes with FIFO algorithm\n");
        printf("3) Schedule processes with SJF algorithm\n");
        printf("4) Schedule processes with SRT algorithm\n");
        printf("5) Quit and free memory\n");
        // prompts for menu selection
        printf("Enter a selection: ");
        scanf("%d", &sel);
        // while user has not chosen to quit
        // call appropriate procedure based on choice--use switch statement or series of if, else if, else statements
        switch (sel) {
            case 1:
                printf("\nEnter selection: %d\n", sel);
                PROCEDURE_FOR_OPTION_1();
                break;
            case 2:
                printf("\nEnter selection: %d\n", sel);
                PROCEDURE_FOR_OPTION_2();
                break;
            case 3:
                printf("\nEnter selection: %d\n", sel);
                PROCEDURE_FOR_OPTION_3();
                break;
            case 4:
                printf("\nEnter selection: %d\n", sel);
                PROCEDURE_FOR_OPTION_4();
                break;
            case 5:
                printf("\nEnter selection: %d\n", sel);
                PROCEDURE_FOR_OPTION_5();
                printf("Quitting program...\n");
                break;
        }
    } while (sel != 5); // while loop
    return;
}

//*************************************************************
int main() {
    // menu selection
    menu();
    return 1; // indicates success
} // end of procedure
