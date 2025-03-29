// Round robin Scheduling algorithm in cpp

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class process
{
private:
    int id;
    int at, bt, ct, tat, wt;
    int remaining_bt;
    bool completed;

public:
    process() {}
    process(int id, int at, int bt)
    {
        this->id = id;
        this->at = at;
        this->bt = bt;
        this->completed = false;
        this->remaining_bt = bt;
    }

    void view_process()
    {
        cout << "Process " << id << " - AT: " << at << " BT: " << bt
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
    int time_quantum;

public:
    processes() : all_completed(false), current_time(0), time_quantum(3) {}

    processes(int count, int time_quantum) : all_completed(false), current_time(0)
    {
        n = count;
        ps = new process[n];
        this->time_quantum = time_quantum;

        for (int i = 0; i < n; i++)
        {
            int at, bt;
            cout << "Enter AT and BT for process " << i << ": ";
            cin >> at >> bt;
            ps[i] = process(i, at, bt);
        }
    }

    void set_all_completed()
    {
        all_completed = true;
        for (int i = 0; i < n; i++)
        {
            all_completed = all_completed && ps[i].completed;
        }
    }

    void calc_ct();
    void calc_tat();
    void calc_wt();
    void print_avg_times();

    void view_processes()
    {
        cout << "\nProcess Execution Details:" << endl;
        for (int i = 0; i < n; i++)
        {
            ps[i].view_process();
        }
        print_avg_times();
    }

    ~processes()
    {
        delete[] ps;
    }
};

void processes::calc_ct()
{
    queue<int> ready_queue; // FIFO queue for Round Robin
    vector<bool> is_completed(n, false);
    vector<int> remaining_bt(n);
    vector<bool> in_queue(n, false);

    // Initialize remaining burst time
    for (int i = 0; i < n; i++)
    {
        remaining_bt[i] = ps[i].bt;
    }

    current_time = 0;
    all_completed = false;

    while (!all_completed)
    {
        // Check for newly arrived processes
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && !is_completed[i] && !in_queue[i])
            {
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }

        if (ready_queue.empty())
        {
            current_time++;
            continue;
        }

        // Get the next process from queue
        int process_idx = ready_queue.front();
        ready_queue.pop();
        in_queue[process_idx] = false;

        // Execute for time quantum or until completion
        int execution_time = min(time_quantum, remaining_bt[process_idx]);
        current_time += execution_time;
        remaining_bt[process_idx] -= execution_time;

        // Check if process has completed
        if (remaining_bt[process_idx] == 0)
        {
            ps[process_idx].ct = current_time;
            is_completed[process_idx] = true;
            ps[process_idx].completed = true;
        }
        else
        {
            // Add newly arrived processes first
            for (int i = 0; i < n; i++)
            {
                if (ps[i].at <= current_time && !is_completed[i] && !in_queue[i])
                {
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }

            // Add the current process back to queue
            ready_queue.push(process_idx);
            in_queue[process_idx] = true;
        }

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

void processes::print_avg_times()
{
    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++)
    {
        avg_tat += ps[i].tat;
        avg_wt += ps[i].wt;
    }
    cout << "\nAverage TAT: " << avg_tat / n << endl;
    cout << "Average WT: " << avg_wt / n << endl;
}

int main()
{
    int n, time_quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> time_quantum;

    processes ps(n, time_quantum);

    ps.calc_ct();
    ps.calc_tat();
    ps.calc_wt();

    ps.view_processes();
    ps.print_avg_times();

    return 0;
}
