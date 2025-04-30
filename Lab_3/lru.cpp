#include <iostream>
#include <list>
#include <algorithm>
using namespace std;
int main(){
    int p[]={1,3,2,3,4,1,3,6,2,1,4,5,1,2,3},
    n=15,F=3,f=0;
    list<int> fr;
    for(int i=0;i<n;i++){
        int pg=p[i];
        auto it=find(fr.begin(),fr.end(),pg);
        if(it==fr.end()){
            f++;
            if(fr.size()==F) fr.pop_back();
        } else fr.erase(it);
        fr.push_front(pg);
    }
    cout<<"Total Faults: "<<f<<endl;
    return 0;
}
