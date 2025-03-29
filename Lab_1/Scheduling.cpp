#include <iostream>
using namespace std;

class process
{
private:
    int at, bt, ct, tat, wt;
    bool completed;

public:
    process() {}
    process(int at, int bt)
    {
        this->at = at;
        this->bt = bt;
        this->completed = false;
    }

    void view_process()
    {
        cout << "AT: " << at << " BT: " << bt << " CT: " << ct << " TAT: " << tat << " WT: " << wt << endl;
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
    processes() : all_completed(false), current_time(0) {}
    processes()
    {
        cout << "Enter no of processes: ";
        cin >> this->n;
        ps = new process[n];
        for (int i = 0; i < n; i++)
        {
            int at, bt;
            cout << "Enter AT and BT for process " << i << ": ";
            cin >> at >> bt;
            ps[i] = process(at, bt);
        }
    }
    void set_all_completed(bool all_completed)
    {
        for (int i = 0; i < n; i++)
        {
            this->all_completed = all_completed && ps[i].completed;
        }
    }
    void calc_ct_fcfs();
    void calc_ct_sjf();
    void calc_tat();
    void calc_wt();
    void print_avg_times();
    void view_processes()
    {
        for (int i = 0; i < this->n; i++)
        {
            ps[i].view_process();
        }
        print_avg_times();
    }
    void processing_interface();
    ~processes()
    {
        delete[] ps;
    }
};

void processes::calc_ct_fcfs()
{
    ps[0].ct = ps[0].bt;
    for (int i = 1; i < n; i++)
    {
        ps[i].ct = ps[i - 1].ct + ps[i].bt;
    }
}
void processes::calc_ct_sjf()
{
    ps[0].ct = ps[0].bt;
    while (all_completed == false)
    {
        all_completed = true;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].completed == false && ps[i].at <= current_time)
            {
                ps[i].ct = current_time + ps[i].bt;
                current_time = ps[i].ct;
                ps[i].completed = true;
            }
            if (ps[i].completed == false)
            {
                all_completed = false;
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

void processes::processing_interface()
{
    int choice;
    cout << "which scheduling type do you want to use?" << endl;
    cout << "1. FCFS" << endl;
    cout << "2. SJF" << endl;
    cin >> choice;

    if (choice == 1)
    {

        calc_ct_fcfs();
        calc_tat();
        calc_wt();
        view_processes();
    }
    else if (choice == 2)
    {

        calc_ct_sjf();
        calc_tat();
        calc_wt();
        view_processes();
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }
}

int main()
{
    process p0(0, 5);
    process p1(3, 7);
    process p2(5, 3);
    process p3(7, 2);

    processes ap;

    ap.processing_interface();

    return 0;
}
