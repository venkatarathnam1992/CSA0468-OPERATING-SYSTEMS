#include <stdio.h>

// Process structure to store process details
struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
};

// Function to find the process with the highest priority
int findHighestPriority(struct Process processes[], int n, int current_time) {
    int highest_priority = -1;
    int highest_priority_idx = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
            if (highest_priority == -1 || processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_idx = i;
            }
        }
    }

    return highest_priority_idx;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", processes[i].id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for Process %d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for Process %d: ", processes[i].id);
        scanf("%d", &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }

    int current_time = 0;

    printf("Process execution order:\n");

    while (1) {
        int highest_priority_idx = findHighestPriority(processes, n, current_time);

        if (highest_priority_idx == -1)
            break;

        processes[highest_priority_idx].remaining_time--;

        printf("Time %d: Process %d\n", current_time, processes[highest_priority_idx].id);
        current_time++;

        if (processes[highest_priority_idx].remaining_time == 0) {
            int turnaround_time = current_time - processes[highest_priority_idx].arrival_time;
            int waiting_time = turnaround_time - processes[highest_priority_idx].burst_time;

            total_waiting_time += waiting_time;
            total_turnaround_time += turnaround_time;
        }
    }

    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
