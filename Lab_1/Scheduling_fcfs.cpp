#include <iostream>
using namespace std;

class process
{
private:
    int at, bt, ct, tat, wt;

public:
    process() {}
    process(int at, int bt)
    {
        this->at = at;
        this->bt = bt;
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

public:
    processes() {}
    processes(process p0, process p1, process p2, process p3)
    {
        int n;
        cout << "Enter no of processes: ";
        cin >> n;
        ps = new process[n];
        for (int i = 0; i < n; i++)
        {
            int at, bt;
            cout << "Enter AT and BT for process " << i << ": ";
            cin >> at >> bt;
            ps[i] = process(at, bt);
        }
    }
    void calc_ct();
    void calc_tat();
    void calc_wt();
    void view_processes()
    {
        for (int i = 0; i < 4; i++)
        {
            ps[i].view_process();
        }
    }
    ~processes() {}
};

void processes::calc_ct()
{
    ps[0].ct = ps[0].bt;
    for (int i = 1; i < 4; i++)
    {
        ps[i].ct = ps[i - 1].ct + ps[i].bt;
    }
}
void processes::calc_tat()
{
    for (int i = 0; i < 4; i++)
    {
        ps[i].tat = ps[i].ct - ps[i].at;
    }
}
void processes::calc_wt()
{
    for (int i = 0; i < 4; i++)
    {
        ps[i].wt = ps[i].tat - ps[i].bt;
    }
}

int main()
{
    process p0(0, 5);
    process p1(3, 7);
    process p2(5, 3);
    process p3(7, 2);

    processes ap(p0, p1, p2, p3);

    ap.calc_ct();
    ap.calc_tat();
    ap.calc_wt();

    ap.view_processes();

    return 0;
}
