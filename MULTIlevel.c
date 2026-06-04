#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n];
    int at[n];
    int bt[n];
    int type[n];

    int ct[n];
    int tat[n];
    int wt[n];

    // Input process details
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Enter Type (1-System, 2-User): ");
        scanf("%d", &type[i]);
    }

    int time = 0;

    // Execute System Processes first using FCFS
    for(int i = 0; i < n; i++)
    {
        if(type[i] == 1)
        {
            // CPU Idle
            if(time < at[i])
            {
                time = at[i];
            }

            time += bt[i];

            ct[i] = time;
        }
    }

    // Execute User Processes next using FCFS
    for(int i = 0; i < n; i++)
    {
        if(type[i] == 2)
        {
            // CPU Idle
            if(time < at[i])
            {
                time = at[i];
            }

            time += bt[i];

            ct[i] = time;
        }
    }

    // Calculate TAT and WT
    for(int i = 0; i < n; i++)
    {
        // TAT = CT - AT
        tat[i] = ct[i] - at[i];

        // WT = TAT - BT
        wt[i] = tat[i] - bt[i];
    }

    printf("\n====================================================");
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT");
    printf("\n====================================================");

    for(int i = 0; i < n; i++)
    {
        if(type[i] == 1)
        {
            printf("\nP%d\t%d\t%d\tSYS\t%d\t%d\t%d",
                   pid[i], at[i], bt[i],
                   ct[i], tat[i], wt[i]);
        }
        else
        {
            printf("\nP%d\t%d\t%d\tUSR\t%d\t%d\t%d",
                   pid[i], at[i], bt[i],
                   ct[i], tat[i], wt[i]);
        }
    }

    float avgWT = 0;
    float avgTAT = 0;

    for(int i = 0; i < n; i++)
    {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("\n\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}