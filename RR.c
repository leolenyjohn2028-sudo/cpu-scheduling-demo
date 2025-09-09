#include <stdio.h>

struct Process {
    int id;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, i, quantum, time = 0, done;
    float totalWT = 0, totalTAT = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Burst Time for Process %d: ", p[i].id);
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].waitingTime = 0;
        p[i].turnaroundTime = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    printf("\nGantt Chart:\n");
    printf("0");


    do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (p[i].remainingTime > 0) {
                done = 0;

                if (p[i].remainingTime > quantum) {
                    time += quantum;
                    p[i].remainingTime -= quantum;
                    printf(" | P%d | %d", p[i].id, time);
                } else {
                    time += p[i].remainingTime;
                    p[i].waitingTime = time - p[i].burstTime;
                    p[i].turnaroundTime = time;
                    p[i].remainingTime = 0;
                    printf(" | P%d | %d", p[i].id, time);
                }
            }
        }
    } while (!done);

    for (i = 0; i < n; i++) {
        totalWT += p[i].waitingTime;
        totalTAT += p[i].turnaroundTime;
    }

    printf("\n\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n",
               p[i].id, p[i].burstTime, p[i].waitingTime, p[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
