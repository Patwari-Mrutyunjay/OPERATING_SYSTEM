#include <stdio.h>

// function to swap two numbers
void swap(int *a, int *b)
{
    int temp;
    temp = *a;   // store a in temp
    *a = *b;     // copy b to a
    *b = temp;   // copy temp to b
}

int main()
{
    int n,i,j;

    int p[20];   // process number
    int at[20];  // arrival time
    int bt[20];  // burst time
    int ct[20];  // completion time
    int tat[20]; // turnaround time
    int wt[20];  // waiting time

    float avg_wt=0, avg_tat=0; // variables for averages

    printf("Enter number of processes: ");
    scanf("%d",&n);

    // Input AT and BT
    for(i=0;i<n;i++)
    {
        p[i] = i+1;

        printf("\nProcess %d Arrival Time: ",p[i]);
        scanf("%d",&at[i]);

        printf("Process %d Burst Time: ",p[i]);
        scanf("%d",&bt[i]);
    }

    // Sort according to Arrival Time using swap
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(at[i] > at[j])
            {
                swap(&at[i],&at[j]);
                swap(&bt[i],&bt[j]);
                swap(&p[i],&p[j]);
            }
        }
    }

    // Completion time for first process
    ct[0] = at[0] + bt[0];

    // Completion time for remaining processes
    for(i=1;i<n;i++)
    {
        if(ct[i-1] < at[i]) // CPU idle condition
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    // Calculate TAT and WT
    for(i=0;i<n;i++)
    {
        tat[i] = ct[i] - at[i];   // turnaround time
        wt[i] = tat[i] - bt[i];   // waiting time

        avg_tat += tat[i];       // sum of TAT
        avg_wt += wt[i];         // sum of WT
    }

    // Print table
    printf("\nP\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i],at[i],bt[i],ct[i],tat[i],wt[i]);
    }

    // Calculate averages
    avg_tat = avg_tat / n;
    avg_wt = avg_wt / n;

    printf("\nAverage Turnaround Time = %.2f",avg_tat);
    printf("\nAverage Waiting Time = %.2f",avg_wt);

    return 0;
}
