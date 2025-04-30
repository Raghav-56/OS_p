#include <iostream>
#include <queue>
using namespace std;
int main(){
    int p[]={1,3,2,3,4,1,3,6,2,1,4,5,1,2,3}, 
    n=15, F=3, faults=0, 
    a[3]={-1,-1,-1};
    queue<int> q;
    for(int i=0;i<n;i++){
        int pg = p[i]; bool hit = false;
        for(int x:a) 
            if(x==pg){ hit=1; break; }
        if(!hit){
            faults++;
            if(q.size()==F){
                int idx=q.front(); q.pop();
                a[idx]=pg; q.push(idx);
            } else {
                for(int j=0;j<F;j++) 
                    if(a[j]<0){ 
                        a[j]=pg; 
                        q.push(j); break; }
            }
        }
    }
    cout<<"Total Faults: "<<faults<<endl;
    return 0;
}
