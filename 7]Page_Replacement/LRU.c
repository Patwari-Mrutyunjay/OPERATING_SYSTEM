#include <stdio.h>

int main()
{
    int n, f;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter page reference string:\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    int frame[f];
    int recent[f];   // Stores last used position of pages

    int faults = 0;

    // Initialize frames as empty
    for(int i = 0; i < f; i++)
    {
        frame[i] = -1;
        recent[i] = -1;
    }

    // Process each page
    for(int i = 0; i < n; i++)
    {
        int found = 0;

        // Check whether page is already present
        for(int j = 0; j < f; j++)
        {
            if(frame[j] == pages[i])
            {
                found = 1;          // Page Hit
                recent[j] = i;      // Update last used position
                break;
            }
        }

        // Page Fault
        if(found == 0)
        {
            int pos = 0;

            // Find least recently used page
            for(int j = 1; j < f; j++)
            {
                if(recent[j] < recent[pos])
                {
                    pos = j;
                }
            }

            // Replace LRU page
            frame[pos] = pages[i];

            // Store current position
            recent[pos] = i;

            faults++;
        }

        // Display frame contents
        printf("\nAfter %d : ", pages[i]);

        for(int j = 0; j < f; j++)
        {
            if(frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d\n", faults);

    return 0;
}