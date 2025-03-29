#include <iostream>
using namespace std;

class P {
public:
    int i, a, b, c, t, w;
    P(int id = 0, int at = 0, int bt = 0) : i(id), a(at), b(bt), c(0) {}
    void show() { cout << "P" << i << " AT:" << a << " BT:" << b << " CT:" << c << " TAT:" << t << " WT:" << w << endl; }
};

int main() {
    P p[4] = {P(0, 0, 5), P(1, 3, 7), P(2, 5, 3), P(3, 7, 2)};
    p[0].c = p[0].a + p[0].b;
    for (int i = 1; i < 4; i++)
        p[i].c = p[i - 1].c + p[i].b;
    for (int i = 0; i < 4; i++)
        p[i].t = p[i].c - p[i].a, p[i].w = p[i].t - p[i].b, p[i].show();
    return 0;
}
