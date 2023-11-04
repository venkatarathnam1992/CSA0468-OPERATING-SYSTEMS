#include <stdio.h>

struct Process {
    int id;          
    int burst_time;  
    int arrival_time; 
    int remaining_time; 
};


int findShortestJob(struct Process processes[], int n, int currentTime) {
    int shortestJob = -1;
    int shortestTime = __INT_MAX__;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= currentTime && processes[i].remaining_time < shortestTime && processes[i].remaining_time > 0) {
            shortestJob = i;
            shortestTime = processes[i].remaining_time;
        }
    }

    return shortestJob;
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter process details (arrival time and burst time):\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    int currentTime = 0;
    int completed = 0;

    printf("\nGantt Chart:\n");
    printf("0");

    while (completed < n) {
        int shortestJob = findShortestJob(processes, n, currentTime);
        if (shortestJob == -1) {
            currentTime++;
            continue;
        }

        processes[shortestJob].remaining_time--;

        printf(" -> P%d", processes[shortestJob].id);

        currentTime++;

        if (processes[shortestJob].remaining_time == 0) {
            completed++;
            int turnaround_time = currentTime - processes[shortestJob].arrival_time;
            int waiting_time = turnaround_time - processes[shortestJob].burst_time;

            printf(" (Turnaround Time: %d, Waiting Time: %d)", turnaround_time, waiting_time);
        }
    }

    printf("\n");

    return 0;
}

