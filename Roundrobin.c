#include <stdio.h>

int main()
{
    int n, tq;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n];
    int at[n];
    int bt[n];
    int rt[n];
    int ct[n];
    int tat[n];
    int wt[n];

    // Ready Queue
    int queue[100];

    // To check whether process already entered queue
    int visited[n];

    for(int i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    // Input process details
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;

        printf("\nProcess P%d\n", pid[i]);

        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);

        // Initially Remaining Time = Burst Time
        rt[i] = bt[i];
    }

    // Sort by Arrival Time
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(at[i] > at[j])
            {
                int temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;

                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = rt[i];
                rt[i] = rt[j];
                rt[j] = temp;
            }
        }
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    int front = 0;
    int rear = 0;

    int time = 0;
    int completed = 0;

    float avgWT = 0;
    float avgTAT = 0;

    while(completed < n)
    {
        // Add newly arrived processes
        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // CPU Idle
        if(front == rear)
        {
            time++;
            continue;
        }

        // Remove process from queue
        int idx = queue[front++];

        // Process needs more than Time Quantum
        if(rt[idx] > tq)
        {
            rt[idx] -= tq;
            time += tq;
        }

        // Process completes
        else
        {
            time += rt[idx];

            rt[idx] = 0;

            ct[idx] = time;

            // TAT = CT - AT
            tat[idx] = ct[idx] - at[idx];

            // WT = TAT - BT
            wt[idx] = tat[idx] - bt[idx];

            avgWT += wt[idx];
            avgTAT += tat[idx];

            completed++;
        }

        // Add newly arrived processes after execution
        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && visited[i] == 0)
            {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Put process back into queue if not completed
        if(rt[idx] > 0)
        {
            queue[rear++] = idx;
        }
    }

    printf("\n================================================");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT");
    printf("\n================================================");

    for(int i = 0; i < n; i++)
    {
        printf("\nP%d\t%d\t%d\t%d\t%d\t%d",
               pid[i],
               at[i],
               bt[i],
               ct[i],
               tat[i],
               wt[i]);
    }

    printf("\n\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}