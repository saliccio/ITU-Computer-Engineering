#include <stdio.h>
#include <stdlib.h>

// Returns 1 if the request can be fulfilled with the available resources, returns 0 otherwise.
int can_allocate(const int* request, const int* available_resources) {
    for(int i = 0; i < 5; i++) {
        if(request[i] > available_resources[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int resources[5];	// Number of available resources
    FILE* resources_file = fopen("resources.txt", "r");
    for(int i = 0; i < 5; i++) {	// Read the max resources
        fscanf(resources_file, "%d", &resources[i]);
    }
    fclose(resources_file);

    int allocations[5][5];	// Number of allocations for each process
    FILE* allocations_file = fopen("allocations.txt", "r");
    for(int i = 0; i < 5; i++) {	// Read the allocations for each process
        for(int j = 0; j < 5; j++) {
            fscanf(allocations_file, "%d", &allocations[i][j]);
            resources[j] -= allocations[i][j];	// Max resources - allocated resources = available resources
        }
    }
    fclose(allocations_file);

    int requests[5][5];	// Number of requests for each process
    FILE* requests_file = fopen("requests.txt", "r");
    for(int i = 0; i < 5; i++) {	// Read the requests for each process
        for(int j = 0; j < 5; j++) {
            fscanf(requests_file, "%d", &requests[i][j]);
        }
    }
    fclose(requests_file);

    for(int i = 0; i < 5; i++) {	// Print information for each process
        printf("Information for process : P%d:\nAllocated resources : ", i + 1);
        for(int j = 0; j < 5; j++) {
            printf("R%d:%d ", j + 1, allocations[i][j]);
        }
        printf("\nResource request : ");
        for(int j = 0; j < 5; j++) {
            printf("R%d:%d ", j + 1, requests[i][j]);
        }
        printf("\n\n");
    }

    printf("Running order for processes: ");
    int finish_count = 0;	// Number of finished processes
    int finished[5] = {0};	// Array indicating if i_th process is finished
    while (finish_count < 5) {	// Loop runs until all processes have been finished
        int nothing_changed = 1;	// Flag that is 0 if at least one process has been finished in this iteration, 1 otherwise
        for(int i = 0; i < 5; i++) {	// For each process
            if(!finished[i] && can_allocate(requests[i], resources)) {	// If the process is not finished and its requests can be fulfilled
                for(int j = 0; j < 5; j++) {	// Return the resources allocated by the process to the available resources vector
                    resources[j] += allocations[i][j];
                }
                printf("P%d ", i + 1);	// Append this process to the running order
                nothing_changed = 0;	// Make the flag 0 since at least one process has been finished
                finish_count++;		// Increment the number of finished processes
                finished[i] = 1;	// Mark this process as finished
            }
        }
        if (nothing_changed) {	// If there cannot be any further changes, break the loop
            break;
        }
    }
    if (finish_count < 5) {		// If not all processes have been finished, then there is a deadlock
        printf("\nThere is a deadlock. ");
        for(int i = 0; i < 5; i++) {	// Check each process' finish flags, and print the processes that caused the deadlock (the ones that is left unfinished)
            if(!finished[i]) {
                printf("P%d ", i + 1);
            }
        }
        printf("are the cause of deadlock.\n");
    }

    return EXIT_SUCCESS;
}