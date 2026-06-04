// ===================================================
// SRTF (Shortest Remaining Time First) Scheduling
// ===================================================
// SRTF is the preemptive version of SJF.
//
// CPU always selects the process having:
// -> Minimum Remaining Time
//
// If a new process arrives with smaller burst time,
// current process is interrupted (preempted).
// ===================================================

#include<stdio.h>
#include<limits.h>

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    int pid[n], at[n], bt[n];
    int rt[n], ct[n], tat[n], wt[n];

    // Input
    for(int i=0; i<n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess %d\n", pid[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);

        rt[i] = bt[i];   // Remaining Time = Burst Time
    }

    int time = 0;
    int count = 0;

    // SRTF Scheduling
    while(count < n)
    {
        int min_bt = INT_MAX;
        int index = -1;

        // Find process with min_btimum remaining time
        for(int i=0; i<n; i++)
        {
            if(at[i] <= time && rt[i] > 0)
            {
                if(rt[i] < min_bt)
                {
                    min_bt = rt[i];
                    index = i;
                }
            }
        }

        // Process found
        if(index != -1)
        {
            rt[index]--;   // Execute for 1 unit

            time++;

            // Process completed
            if(rt[index] == 0)
            {
                ct[index] = time;
                count++;
            }
        }
        else
        {
            // CPU Idle
            time++;
        }
    }

    // Calculate TAT and WT
    for(int i=0; i<n; i++)
    {
        tat[i] = ct[i] - at[i];

        wt[i] = tat[i] - bt[i];
    }

    // Display Output
    printf("\n================================================");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    printf("\n================================================");

    float total_tat = 0;
    float total_wt = 0;

    for(int i=0; i<n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i],
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i]);

        total_tat += tat[i];
        total_wt += wt[i];
    }

    printf("\n\nAverage Turn Around Time = %.2f",
           total_tat/n);

    printf("\nAverage Waiting Time = %.2f",
           total_wt/n);

    printf("\n");

    return 0;
}