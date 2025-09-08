#include <stdio.h>

struct Process {
    int pid;        // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
};

int main() {
    int n, i, j;
    struct Process p[20];
    float avg_wt = 0, avg_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("\n");

    // Input processes
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].at);
        printf("Enter Burst Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
        printf("\n");
    }

    // Sort by Arrival Time (FCFS rule)
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Completion, TAT, WT
    int time = 0;
    for (i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at; // CPU waits if idle
        }
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    // Output Table
    printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    // Gantt Chart
    printf("\nGantt Chart:\n");
    for (i = 0; i < n; i++) {
        printf(" |  P%d  ", p[i].pid);
    }
    printf("|\n");

    int start = 0;
    printf("%d", p[0].at < 0 ? 0 : p[0].at);
    for (i = 0; i < n; i++) {
        printf("      %d", p[i].ct);
    }
    printf("\n");

    printf("\nAverage Waiting Time: %f", avg_wt / n);
    printf("\nAverage Turnaround Time: %f\n", avg_tat / n);


    return 0;
}

