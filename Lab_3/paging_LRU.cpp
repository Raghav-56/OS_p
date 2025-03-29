#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
using namespace std;

void lru(int pages[], int n, int frames)
{
    // List to store pages in order of their use (most recently used at back)
    list<int> pageList;

    // Hash map to store page references
    unordered_map<int, list<int>::iterator> pageMap;

    int pageFaults = 0;

    for (int i = 0; i < n; i++)
    {
        // If page is not present in memory
        if (pageMap.find(pages[i]) == pageMap.end())
        {
            // If frames are full, remove the least recently used page
            if (pageList.size() == frames)
            {
                int lru = pageList.front();
                pageList.pop_front();
                pageMap.erase(lru);
            }

            // Add new page to the memory
            pageList.push_back(pages[i]);
            pageMap[pages[i]] = --pageList.end();
            pageFaults++;
        }
        // If page is already present in memory
        else
        {
            // Remove the page from its current position
            pageList.erase(pageMap[pages[i]]);

            // Add the page to the end as most recently used
            pageList.push_back(pages[i]);

            // Update the reference in the map
            pageMap[pages[i]] = --pageList.end();
        }

        // Print current state of pages in memory
        cout << "After reference to page " << pages[i] << ": ";
        for (auto p : pageList)
            cout << p << " ";
        cout << endl;
    }

    cout << "Total Page Faults: " << pageFaults << endl;
}

int main()
{
    int pages[] = {1, 3, 2, 3, 4, 1, 3, 6, 2, 1, 4, 5, 1, 2, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    lru(pages, n, frames);

    return 0;
}
