#include <iostream>
#include <climits>
using namespace std;

class P {
public:
    int i, a, b, c, t, w, p, r;
    bool d;
    P(int id=0, int at=0, int bt=0, int pri=0) : i(id), a(at), b(bt), p(pri), c(0), t(0), w(0), r(bt), d(false) {}
    void show() { cout<<"P"<<i<<" AT:"<<a<<" BT:"<<b<<" Priority:"<<p<<" CT:"<<c<<" TAT:"<<t<<" WT:"<<w<<endl; }
};

int main() {
    P p[4] = {P(0, 0, 5, 2), P(1, 3, 7, 1), P(2, 5, 3, 3), P(3, 7, 2, 0)};
    int ct = 0, done = 0;
    while(done < 4) {
        int idx = -1, hp = INT_MAX;
        for(int i=0; i<4; i++)
            if(p[i].a <= ct && !p[i].d && p[i].p < hp) 
                hp = p[i].p, idx = i;
        if(idx == -1) { ct++; continue; }
        ct += p[idx].b;
        p[idx].c = ct, p[idx].t = ct - p[idx].a, p[idx].w = p[idx].t - p[idx].b;
        p[idx].d = true, done++;
    }
    for(int i=0; i<4; i++) 
        p[i].show();
    return 0;
}
