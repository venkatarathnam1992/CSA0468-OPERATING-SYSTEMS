#include <stdio.h>

int main() {
    int bt[10], wt[10], tat[10], n, total = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("p%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (bt[j] < bt[i]) {
                
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++) {
        wt[i] = 0;
        for (int j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
        total += wt[i];
    }

    float avg_wt = (float)total / n;
    total = 0;

    printf("\nProcess  Burst Time  Waiting Time  Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total += tat[i];
        printf("p%d\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    float avg_tat = (float)total / n;

    printf("Average Waiting Time = %f\n", avg_wt);
    printf("Average Turnaround Time = %f\n", avg_tat);
}

