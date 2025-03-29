#include <iostream>
using namespace std;
class CB {
private:
    int buf[3], size = 0, in = 0, out = 0;
public:
    bool empty() { return size == 0; }
    bool full() { return size == 3; }
    void add(int x) {
        if (!full()) {
            buf[in] = x;
            in = (in + 1) % 3;
            size++;
        }
    }
    int get() {
        int x = buf[out];
        out = (out + 1) % 3;
        size--;
        return x;
    }
};
int main() {
    CB buffer;
    for(int i = 1; i <= 5; i++) {
        if(!buffer.full()) {
            buffer.add(i);
            cout << "P:" << i << " ";
        } else cout << "FULL ";
    }
    while(!buffer.empty()) cout << "C:" << buffer.get() << " ";
    cout << endl;
    return 0;
}
