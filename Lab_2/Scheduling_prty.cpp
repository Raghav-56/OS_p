// Priority Scheduling algorithm in cpp
#include <iostream>
#include <vector>
using namespace std;

class process
{
private:
    int id, priority;
    int at, bt, ct, tat, wt;
    bool completed;

public:
    process() {}
    process(int id, int at, int bt, int priority)
    {
        this->id = id;
        this->at = at;
        this->bt = bt;
        this->priority = priority;
        this->completed = false;
    }

    void view_process()
    {
        cout << "Process " << id << " - AT: " << at << " BT: " << bt << " Priority: " << priority
             << " CT: " << ct << " TAT: " << tat << " WT: " << wt << endl;
    }

    ~process() {}

    friend class processes;
};

class processes
{
private:
    process *ps;
    int n;
    bool all_completed;
    int current_time;

public:
    processes() : all_completed(false), current_time(0), ps(nullptr), n(0) {}

    processes(int count)
    {
        n = count;
        ps = new process[n];
        all_completed = false;
        current_time = 0;

        for (int i = 0; i < n; i++)
        {
            int at, bt, priority;
            cout << "Enter AT, BT and Priority for process " << i << ": ";
            cin >> at >> bt >> priority;
            ps[i] = process(i, at, bt, priority);
        }
    }

    void calc_ct();
    void calc_tat();
    void calc_wt();
    void view_processes()
    {
        cout << "\nProcess Execution Details:" << endl;
        for (int i = 0; i < n; i++)
        {
            ps[i].view_process();
        }
    }

    ~processes()
    {
        if (ps)
            delete[] ps;
    }
};

void processes::calc_ct()
{
    vector<bool> is_completed(n, false);

    while (!all_completed)
    {
        vector<pair<int, int>> ready_queue; // <index, priority>
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && !is_completed[i])
            {
                ready_queue.push_back({i, ps[i].priority});
            }
        }

        if (ready_queue.empty())
        {
            current_time++;
            continue;
        }

        // Find highest priority process (lowest priority value)
        int idx = 0;
        for (int i = 1; i < ready_queue.size(); i++)
        {
            if (ready_queue[i].second < ready_queue[idx].second)
            {
                idx = i;
            }
        }

        // Process the selected process
        int process_idx = ready_queue[idx].first;

        // Update completion time
        current_time += ps[process_idx].bt;
        ps[process_idx].ct = current_time;
        ps[process_idx].completed = true;
        is_completed[process_idx] = true;

        // Check if all processes are completed
        all_completed = true;
        for (int i = 0; i < n; i++)
        {
            if (!is_completed[i])
            {
                all_completed = false;
                break;
            }
        }
    }
}

void processes::calc_tat()
{
    for (int i = 0; i < n; i++)
    {
        ps[i].tat = ps[i].ct - ps[i].at;
    }
}

void processes::calc_wt()
{
    for (int i = 0; i < n; i++)
    {
        ps[i].wt = ps[i].tat - ps[i].bt;
    }
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    processes ps(n);

    ps.calc_ct();
    ps.calc_tat();
    ps.calc_wt();

    ps.view_processes();

    return 0;
}
