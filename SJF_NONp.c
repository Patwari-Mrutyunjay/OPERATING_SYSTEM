#include <stdio.h>
#include <limits.h>

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n];
    int ct[n], tat[n], wt[n];
    int completed[n];

    // Input
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess %d\n", pid[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);

        completed[i] = 0;
    }

    int time = 0;               //time Current CPU time.
    int count = 0;               //Number of completed processes.

    // SJF Non-Preemptive
    while(count < n)
    {
        int min_bt = INT_MAX;
        int index = -1;

        // Find shortest job among arrived processes
        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && completed[i] == 0)
            {
                if(bt[i] < min_bt)
                {
                    min_bt = bt[i];
                    index = i;
                }
            }
        }

        // If process found
        if(index != -1)
        {
            time = time + bt[index];

            ct[index] = time;

            completed[index] = 1;

            count++;
        }
        else
        {
            // CPU idle
            time++;
        }
    }

    // Calculate TAT and WT
    for(int i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];

        wt[i] = tat[i] - bt[i];
    }

    // Display
    printf("\n================================================");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    printf("\n================================================");

    float total_tat = 0;
    float total_wt = 0;

    for(int i = 0; i < n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i]);

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\n\nAverage Turn Around Time = %.2f",
           total_tat / n);

    printf("\nAverage Waiting Time = %.2f",
           total_wt / n);

    return 0;
}