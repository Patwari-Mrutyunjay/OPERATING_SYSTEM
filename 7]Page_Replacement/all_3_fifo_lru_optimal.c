#include <stdio.h>

// Function prototypes
void fifo(int pages[], int n, int f);
void lru(int pages[], int n, int f);
void optimal(int pages[], int n, int f);

int main()
{
    int n, f, choice;

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

    printf("\n1. FIFO");
    printf("\n2. LRU");
    printf("\n3. Optimal");

    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        fifo(pages, n, f);
        break;

    case 2:
        lru(pages, n, f);
        break;

    case 3:
        optimal(pages, n, f);
        break;

    default:
        printf("Invalid Choice");
    }

    return 0;
}

// FIFO Page Replacement
void fifo(int pages[], int n, int f)
{
    int frame[f];
    int faults = 0;
    int front = 0; // Points to next page to replace

    // Initialize frames
    for (int i = 0; i < f; i++)
        frame[i] = -1;

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

        // Page fault
        if (found == 0)
        {
            frame[front] = pages[i];
            front = (front + 1) % f;
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
}

// LRU Page Replacement
void lru(int pages[], int n, int f)
{
    int frame[f];
    int faults = 0;

    // Initialize frames
    for (int i = 0; i < f; i++)
        frame[i] = -1;

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

        // Page fault
        if (found == 0)
        {
            int pos = -1;

            // Find empty frame
            for (int j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            // Apply LRU if frames are full
            if (pos == -1)
            {
                int least = i;

                for (int j = 0; j < f; j++)
                {
                    int k;

                    // Search last use of page
                    for (k = i - 1; k >= 0; k--)
                    {
                        if (frame[j] == pages[k])
                            break;
                    }

                    if (k < least)
                    {
                        least = k;
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
}

// Optimal Page Replacement
void optimal(int pages[], int n, int f)
{
    int frame[f];
    int faults = 0;

    // Initialize frames
    for (int i = 0; i < f; i++)
        frame[i] = -1;

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

        // Page fault
        if (found == 0)
        {
            int pos = -1;

            // Find empty frame
            for (int j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    pos = j;
                    break;
                }
            }

            // Apply Optimal if frames are full
            if (pos == -1)
            {
                int farthest = -1;

                for (int j = 0; j < f; j++)
                {
                    int k;

                    // Find next use of page
                    for (k = i + 1; k < n; k++)
                    {
                        if (frame[j] == pages[k])
                            break;
                    }

                    // Page never used again
                    if (k == n)
                    {
                        pos = j;
                        break;
                    }

                    // Find farthest future use
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
}