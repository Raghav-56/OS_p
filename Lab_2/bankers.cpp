#include <iostream>
using namespace std;
class P {
public:
    int i, a[2], m[2], n[2];
    P(int id=0) : i(id) { for(int j=0; j<2; j++) a[j] = m[j] = n[j] = 0; }
    void calcN() { n[0] = m[0] - a[0]; n[1] = m[1] - a[1]; }
};
class B {
private:
    P p[3];
    int av[2];
public:
    B() { for(int i=0; i<3; i++) p[i].i = i; }
    void init() {
        av[0] = 10; av[1] = 5;
        p[0].m[0] = 7; p[0].m[1] = 5;
        p[1].m[0] = 3; p[1].m[1] = 2;
        p[2].m[0] = 9; p[2].m[1] = 0;
        p[0].a[0] = 0; p[0].a[1] = 1; av[0] -= 0; av[1] -= 1;
        p[1].a[0] = 2; p[1].a[1] = 0; av[0] -= 2; av[1] -= 0;
        p[2].a[0] = 3; p[2].a[1] = 0; av[0] -= 3; av[1] -= 0;
        for(int i=0; i<3; i++) p[i].calcN();
        cout << "Avail: [" << av[0] << "," << av[1] << "]" << endl;
    }
    bool safe() {
        bool fin[3] = {0};
        int w[2] = {av[0], av[1]}, seq[3], cnt = 0;
        while(cnt < 3) {
            bool found = false;
            for(int i=0; i<3; i++) {
                if(!fin[i] && p[i].n[0] <= w[0] && p[i].n[1] <= w[1]) {
                    w[0] += p[i].a[0]; w[1] += p[i].a[1];
                    fin[i] = true; seq[cnt++] = i; found = true;
                }
            }
            if(!found) { cout << "Not safe" << endl; return false; }
        }
        cout << "Safe: P" << seq[0] << "->P" << seq[1] << "->P" << seq[2] << endl;
        return true;
    }
    bool req(int pid, int a, int b) {
        if(a > p[pid].n[0] || b > p[pid].n[1]) return false;
        if(a > av[0] || b > av[1]) return false;
        av[0] -= a; p[pid].a[0] += a; p[pid].n[0] -= a;
        av[1] -= b; p[pid].a[1] += b; p[pid].n[1] -= b;
        if(safe()) return true;
        av[0] += a; p[pid].a[0] -= a; p[pid].n[0] += a;
        av[1] += b; p[pid].a[1] -= b; p[pid].n[1] += b;
        return false;
    }
};
int main() {
    B b;
    b.init();
    b.safe();
    cout << (b.req(1, 1, 0) ? "Granted" : "Denied") << endl;
    return 0;
}
