#include <iostream>
#include <algorithm>
using namespace std;

class P {
public:
    int i, a, b, c, t, w;
    P(int id = 0, int at = 0, int bt = 0) : i(id), a(at), b(bt), c(0) {}
    void show() { cout << "P" << i << " AT:" << a << " BT:" << b << " CT:" << c << " TAT:" << t << " WT:" << w << endl; }
};

int main() {
    P p[4] = {P(0, 0, 5), P(1, 3, 7), P(2, 5, 3), P(3, 7, 2)};
    sort(p, p + 4, [](P x, P y){ return x.a < y.a; });
    int ct = p[0].c = p[0].a + p[0].b;
    for (int i = 0, next, minB; i < 3;) {
        next = -1, minB = 9999;
        for (int j = 1; j < 4; j++)
            if (!p[j].c && p[j].a <= ct && p[j].b < minB)
                minB = p[j].b, next = j;
        if (next != -1) p[next].c = ct += p[next].b, i++;
        else
            for (int j = 1; j < 4; j++)
                if (!p[j].c) { ct = p[j].a; break; }
    }
    for (int i = 0; i < 4; i++)
        p[i].t = p[i].c - p[i].a, p[i].w = p[i].t - p[i].b, p[i].show();
    return 0;
}
