#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

void calculateWaitingTime(struct Process p[], int n) {
    p[0].waiting_time = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
    }
}

void calculateTurnaroundTime(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart\n");
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", p[i].id);
    }
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        printf("   %d", p[i].waiting_time + p[i].burst_time);
    }
    printf("\n");
}

void sortByBurstTime(struct Process p[], int n) {
    struct Process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].burst_time > p[j+1].burst_time) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i+1;
        printf("Enter burst time for process P%d: ", p[i].id);
        scanf("%d", &p[i].burst_time);
    }

    // Sort processes by burst time (SJF)
    sortByBurstTime(p, n);

    // Calculate waiting time and turnaround time
    calculateWaitingTime(p, n);
    calculateTurnaroundTime(p, n);

    // Print process information
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    // Print Gantt Chart
    printGanttChart(p, n);

    return 0;
}
