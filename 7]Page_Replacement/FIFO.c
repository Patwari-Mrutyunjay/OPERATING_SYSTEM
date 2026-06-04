#include <stdio.h>

int main()
{
    int pages[50], frames[20];
    int n, f;
    int i, j;

    int pageFaults = 0;

    // Points to frame to be replaced next
    int front = 0;

    int found;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initially all frames are empty
    for(i = 0; i < f; i++)
        frames[i] = -1;

    // Process each page
    for(i = 0; i < n; i++)
    {
        found = 0;

        // Check if page already exists
        for(j = 0; j < f; j++)
        {
            if(frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        // Page Fault
        if(found == 0)
        {
            // Replace oldest page
            frames[front] = pages[i];

            // Move to next frame in circular order
            front = (front + 1) % f;

            pageFaults++;
        }

        // Display frames
        printf("\nFrames: ");
        for(j = 0; j < f; j++)
        {
            if(frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
    }

    printf("\n\nTotal Page Faults = %d", pageFaults);

    return 0;
}