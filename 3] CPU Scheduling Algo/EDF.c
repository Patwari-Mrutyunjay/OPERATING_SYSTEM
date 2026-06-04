#include <stdio.h>

int main()
{
    int n;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    int deadline[n];

    for(int i = 0; i < n; i++)
    {
        printf("Enter deadline of Task %d: ", i + 1);
        scanf("%d", &deadline[i]);
    }

    printf("\nExecution Order (EDF):\n");

    for(int i = 0; i < n; i++)
    {
        int earliest = -1;
        int pos = -1;

        for(int j = 0; j < n; j++)
        {
            if(deadline[j] != -1)
            {
                if(earliest == -1 || deadline[j] < earliest)
                {
                    earliest = deadline[j];
                    pos = j;
                }
            }
        }

        printf("Task %d (Deadline = %d)\n", pos + 1, earliest);
        deadline[pos] = -1;
    }

    return 0;
}