#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int period[n];

    for(int i = 0; i < n; i++)
    {
        printf("Enter period of Task %d: ", i + 1);
        scanf("%d", &period[i]);
    }

    printf("\nPriority Order (Rate Monotonic Scheduling):\n");

    for(int i = 0; i < n; i++)
    {
        int highest = -1;
        int pos = -1;

        for(int j = 0; j < n; j++)
        {
            if(period[j] != -1)
            {
                if(highest == -1 || period[j] < highest)
                {
                    highest = period[j];
                    pos = j;
                }
            }
        }

        printf("Task %d (Period = %d)\n", pos + 1, highest);
        period[pos] = -1;
    }

    return 0;
}