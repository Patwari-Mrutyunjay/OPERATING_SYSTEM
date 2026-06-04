#include <stdio.h>
#include <limits.h>

int main()
{
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n];
    int at[n];
    int bt[n];
    int pr[n];
    int ct[n];
    int tat[n];
    int wt[n];

    int completed[n];

    // Input process details
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Enter Priority: ");
        scanf("%d", &pr[i]);

        completed[i] = 0;
    }

    int time = 0;
    int count = 0;

    while(count < n)
    {
        int index = -1;
        int minPriority = INT_MAX;

        // Find highest priority process
        // (smaller number = higher priority)
        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time &&
               completed[i] == 0 &&
               pr[i] < minPriority)
            {
                minPriority = pr[i];
                index = i;
            }
        }

        // Execute selected process
        if(index != -1)
        {
            // Run process completely
            time += bt[index];

            ct[index] = time;

            // TAT = CT - AT
            tat[index] = ct[index] - at[index];

            // WT = TAT - BT
            wt[index] = tat[index] - bt[index];

            completed[index] = 1;

            count++;
        }
        else
        {
            // CPU is idle
            time++;
        }
    }

    printf("\n====================================================");
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT");
    printf("\n====================================================");

    for(int i = 0; i < n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d\t%d",
               pid[i],
               at[i],
               bt[i],
               pr[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    float avgWT = 0;
    float avgTAT = 0;

    // Calculate averages
    for(int i = 0; i < n; i++)
    {
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    avgWT /= n;
    avgTAT /= n;

    printf("\n\nAverage Waiting Time = %.2f", avgWT);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT);

    return 0;
}