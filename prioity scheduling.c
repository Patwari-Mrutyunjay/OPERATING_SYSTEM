#include<stdio.h>

struct process
{
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
    int rt;
};

int main()
{
    int n,i,j,time=0,completed=0,choice;
    struct process p[10],temp;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);
        p[i].pid=i+1;

        printf("Arrival Time: ");
        scanf("%d",&p[i].at);

        printf("Burst Time: ");
        scanf("%d",&p[i].bt);

        printf("Priority (smaller number = higher priority): ");
        scanf("%d",&p[i].pr);

        p[i].rt=p[i].bt;
    }

    printf("\n1. Priority Non Preemptive");
    printf("\n2. Priority Preemptive");
    printf("\nEnter choice: ");
    scanf("%d",&choice);

    switch(choice)
    {

    case 1:   // Non Preemptive
        for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(p[j].pr < p[i].pr)
                {
                    temp=p[i];
                    p[i]=p[j];
                    p[j]=temp;
                }
            }
        }

        time=0;

        for(i=0;i<n;i++)
        {
            if(time < p[i].at)
                time = p[i].at;

            time += p[i].bt;

            p[i].ct=time;
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
        }

        break;


    case 2:   // Preemptive
        while(completed<n)
        {
            int idx=-1;
            int highest=999;

            for(i=0;i<n;i++)
            {
                if(p[i].at<=time && p[i].rt>0 && p[i].pr<highest)
                {
                    highest=p[i].pr;
                    idx=i;
                }
            }

            if(idx!=-1)
            {
                p[idx].rt--;
                time++;

                if(p[idx].rt==0)
                {
                    completed++;
                    p[idx].ct=time;
                    p[idx].tat=p[idx].ct-p[idx].at;
                    p[idx].wt=p[idx].tat-p[idx].bt;
                }
            }
            else
            {
                time++;
            }
        }

        break;

    default:
        printf("Invalid choice");
    }


    float avg_tat=0,avg_wt=0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].pr,
               p[i].ct,p[i].tat,p[i].wt);

        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;
    }

    avg_tat/=n;
    avg_wt/=n;

    printf("\nAverage Turnaround Time = %.2f",avg_tat);
    printf("\nAverage Waiting Time = %.2f",avg_wt);

    return 0;
}
