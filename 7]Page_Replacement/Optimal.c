#include <stdio.h>

int main()
{
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frame[f];

    // Initially all frames are empty
    for (int i = 0; i < f; i++)
    {
        frame[i] = -1;
    }

    int faults = 0;

    for (int i = 0; i < n; i++)
    {
        int found = 0;

        // Check page hit
        for (int j = 0; j < f; j++)
        {
            if (frame[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        // Page Fault
        if (found == 0)
        {
            int pos = -1;

            // Check for empty frame
            for (int j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            // If frames are full, apply Optimal
            if (pos == -1)
            {
                int farthest = -1;

                for (int j = 0; j < f; j++)
                {
                    int k;

                    // Search forward for next use
                    for (k = i + 1; k < n; k++)
                    {
                        if (frame[j] == pages[k])
                        {
                            break;
                        }
                    }

                    // Page never used again
                    if (k == n)
                    {
                        pos = j;
                        break;
                    }

                    // Keep track of farthest future use
                    if (k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            faults++;
        }

        // Display frames
        printf("\nAfter %d : ", pages[i]);

        for (int j = 0; j < f; j++)
        {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    return 0;
}