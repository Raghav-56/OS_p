#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int optimalPage(int pages[], int n, int frames)
{
    vector<int> fr;
    int pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        // If page already in frame
        if (find(fr.begin(), fr.end(), pages[i]) != fr.end())
            continue;

        // Page fault occurs
        pageFaults++;

        // If frames not full, simply add the page
        if (fr.size() < frames)
        {
            fr.push_back(pages[i]);
        }
        else
        {
            // Find the page to replace
            int farthest = -1, replaceIndex = 0;

            // For each page currently in frames
            for (int j = 0; j < frames; j++)
            {
                int k;
                // Find when this page will be used next
                for (k = i + 1; k < n; k++)
                {
                    if (fr[j] == pages[k])
                        break;
                }

                // If page won't be used again, replace it
                if (k == n)
                {
                    replaceIndex = j;
                    break;
                }

                // Track the page that will be used furthest in future
                if (k > farthest)
                {
                    farthest = k;
                    replaceIndex = j;
                }
            }

            // Replace the victim page
            fr[replaceIndex] = pages[i];
        }

        // Print current state of frames
        cout << "After reference to page " << pages[i] << ": ";
        for (auto p : fr)
            cout << p << " ";
        cout << endl;
    }

    return pageFaults;
}

int main()
{
    int pages[] = {1, 3, 2, 3, 4, 1, 3, 6, 2, 1, 4, 5, 1, 2, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    int pageFaults = optimalPage(pages, n, frames);
    int hits = n - pageFaults;

    cout << "Total Page Faults: " << pageFaults << endl;
    cout << "Total Hits: " << hits << endl;
    cout << "Hit Ratio: " << (float)hits / n << endl;
}
