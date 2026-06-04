// ===============================
// FCFS Scheduling Program in C
// ===============================

#include <stdio.h>

int main()
{

    // n = number of processes
    int n;

    // Taking number of processes from user
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Arrays Declaration
    // pid = Process ID
    // at  = Arrival Time
    // bt  = Burst Time
    // ct  = Completion Time
    // tat = Turn Around Time
    // wt  = Waiting Time

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];

    // ==========================================
    // INPUT SECTION
    // ==========================================

    for (int i = 0; i < n; i++)
    {

        printf("\nProcess %d\n", i + 1);

        // Assigning process ID automatically
        pid[i] = i + 1;

        // Taking arrival time
        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        // Taking burst time
        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // ==========================================
    // SORTING BASED ON ARRIVAL TIME
    // ==========================================
    // FCFS works according to arrival order
    // So we sort processes by Arrival Time

    for (int i = 0; i < n - 1; i++)
    {

        for (int j = i + 1; j < n; j++)
        {

            // If current process arrives later,
            // swap it with earlier arriving process

            if (at[i] > at[j])
            {

                int temp;

                // Swap Arrival Time
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap Burst Time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap Process ID
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // ==========================================
    // COMPLETION TIME CALCULATION
    // ==========================================

    // Completion time of first process
    // = Arrival Time + Burst Time

    ct[0] = at[0] + bt[0];

    // Calculate completion time for remaining processes

    for (int i = 1; i < n; i++)
    {

        // If CPU becomes idle
        // Example:
        // Previous process ends at 5
        // Next process arrives at 8

        if (ct[i - 1] < at[i])
        {

            // CPU waits until process arrives
            ct[i] = at[i] + bt[i];
        }

        else
        {

            // Process already waiting
            // Start immediately after previous process

            ct[i] = ct[i - 1] + bt[i];
        }
    }

    // ==========================================
    // TURN AROUND TIME & WAITING TIME
    // ==========================================

    for (int i = 0; i < n; i++)
    {

        // Turn Around Time
        // TAT = Completion Time - Arrival Time

        tat[i] = ct[i] - at[i];

        // Waiting Time
        // WT = Turn Around Time - Burst Time

        wt[i] = tat[i] - bt[i];
    }

    // ==========================================
    // DISPLAY OUTPUT TABLE
    // ==========================================

    printf("\n====================================================");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    printf("\n====================================================");

    for (int i = 0; i < n; i++)
    {

        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i],
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    // ==========================================
    // AVERAGE TAT & WT
    // ==========================================

    double tatsum = 0;
    double wtsum = 0;

    // Add all TAT and WT values

    for (int i = 0; i < n; i++)
    {

        tatsum += tat[i];
        wtsum += wt[i];
    }

    // Calculate averages

    double tatavg = tatsum / n;
    double wtavg = wtsum / n;

    // Print averages

    printf("\n\nAverage Turn Around Time = %.2f", tatavg);
    printf("\nAverage Waiting Time     = %.2f", wtavg);

    printf("\n");

    printf("\n\nGantt Chart:\n\n");

    for (int i = 0; i < n; i++)
    {
        printf("|  P%d  ", pid[i]);
    }
    printf("|\n");

    printf("%d", at[0]);

    for (int i = 0; i < n; i++)
    {
        printf("      %d", ct[i]);
    }

    printf("\n");

    return 0;
}