#include <iostream>
#include <queue>
using namespace std;

class P {
public:
    int i, a, b, c, t, w, r;
    bool d;
    P(int id=0, int at=0, int bt=0) : i(id), a(at), b(bt), c(0), t(0), w(0), r(bt), d(false) {}
    void show() { cout<<"P"<<i<<" AT:"<<a<<" BT:"<<b<<" CT:"<<c<<" TAT:"<<t<<" WT:"<<w<<endl; }
};

int main() {
    P p[4] = {P(0, 0, 5), P(1, 3, 7), P(2, 5, 3), P(3, 7, 2)};
    queue<int> rq; int ct = 0, done = 0;
    bool inQ[4] = {false};
    while(done < 4) {
        for(int i=0; i<4; i++)
            if(p[i].a <= ct && !p[i].d && !inQ[i]) rq.push(i), inQ[i] = true;
        if(rq.empty()) { ct++; continue; }
        int idx = rq.front(); rq.pop(); inQ[idx] = false;
        int exec = min(2, p[idx].r);
        ct += exec; p[idx].r -= exec;
        if(p[idx].r == 0) {
            p[idx].c = ct, p[idx].t = ct - p[idx].a, p[idx].w = p[idx].t - p[idx].b;
            p[idx].d = true, done++;
        } else {
            for(int i=0; i<4; i++)
                if(p[i].a <= ct && !p[i].d && !inQ[i]) 
                    rq.push(i), inQ[i] = true;
            rq.push(idx), inQ[idx] = true;
        }
    }
    for(int i=0; i<4; i++) 
        p[i].show();
    return 0;
}
