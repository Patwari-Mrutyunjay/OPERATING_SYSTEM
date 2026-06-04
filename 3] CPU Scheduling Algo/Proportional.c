#include <stdio.h>

int main()
{
    int n, totalCPU;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int share[n];
    int totalShare = 0;

    for(int i = 0; i < n; i++)
    {
        printf("Enter share of Task %d: ", i + 1);
        scanf("%d", &share[i]);

        totalShare += share[i];
    }

    printf("Enter total CPU time: ");
    scanf("%d", &totalCPU);

    printf("\nCPU Allocation:\n");

    for(int i = 0; i < n; i++)
    {
        float cpuTime = (share[i] * totalCPU) / (float)totalShare;

        printf("Task %d -> %.2f units\n", i + 1, cpuTime);
    }

    return 0;
}