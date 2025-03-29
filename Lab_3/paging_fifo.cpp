#include <iostream>
#include <queue>
#include <string>
using namespace std;

void fifoPageReplacement(int pages[], int n, int frames)
{
    // Initialize frames with -1 indicating empty
    int *frameArray = new int[frames];
    for (int i = 0; i < frames; i++)
        frameArray[i] = -1;

    // Queue to track the order of page loading (FIFO)
    queue<int> frameQueue;

    int pageFaults = 0;
    int hits = 0;

    // Process each page reference
    for (int i = 0; i < n; i++)
    {
        // Check if page is already in a frame
        bool pageFound = false;
        for (int j = 0; j < frames; j++)
        {
            if (frameArray[j] == pages[i])
            {
                pageFound = true;
                hits++;
                break;
            }
        }

        // If page is not in any frame, page fault occurs
        if (!pageFound)
        {
            pageFaults++;

            // Check if there's an empty frame available
            bool emptyFrameFound = false;
            for (int j = 0; j < frames; j++)
            {
                if (frameArray[j] == -1)
                {
                    frameArray[j] = pages[i];
                    frameQueue.push(j); // Add this frame index to queue
                    emptyFrameFound = true;
                    break;
                }
            }

            // If no empty frame, replace the oldest page (FIFO)
            if (!emptyFrameFound)
            {
                int oldestFrameIndex = frameQueue.front();
                frameQueue.pop();
                frameArray[oldestFrameIndex] = pages[i];
                frameQueue.push(oldestFrameIndex); // Add back after replacement
            }
        }

        // Display current state of frames
        cout << "Reference to page " << pages[i] << " - Frames: ";
        for (int j = 0; j < frames; j++)
            cout << (frameArray[j] == -1 ? "Empty" : to_string(frameArray[j])) << " ";
        cout << (pageFound ? "(Hit)" : "(Fault)") << endl;
    }

    cout << "\nSummary:" << endl;
    cout << "Total Page Faults: " << pageFaults << endl;
    cout << "Total Hits: " << hits << endl;
    cout << "Hit Ratio: " << (float)hits / n << endl;

    delete[] frameArray;
}

int main()
{
    int pages[] = {1, 3, 2, 3, 4, 1, 3, 6, 2, 1, 4, 5, 1, 2, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    cout << "Using frames: " << frames << endl;
    cout << "Page reference string: ";
    for (int i = 0; i < n; i++)
        cout << pages[i] << " ";
    cout << endl
         << endl;

    fifoPageReplacement(pages, n, frames);

    return 0;
}
