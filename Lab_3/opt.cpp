#include <iostream>
using namespace std;
int main(){
    int p[]={1,3,2,3,4,1,3,6,2,1,4,5,1,2,3},
    n=15,F=3,f=0,fr[3]={-1,-1,-1};
    for(int i=0;i<n;i++){
        int pg=p[i],hit=0;
        for(int j=0;j<F;j++) 
            if(fr[j]==pg) hit=1;
        if(!hit){
            f++;
            int used=0;
            for(int j=0;j<F;j++) 
                used+=fr[j]>=0;
            if(used<F){
                for(int j=0;j<F;j++) 
                    if(fr[j]<0){ fr[j]=pg; break; }
            } else {
                int idx=0,mx=-1;
                for(int j=0;j<F;j++){
                    int k;
                    for(k=i+1;k<n && p[k]!=fr[j];k++);
                    int dist = (k<n? k: 1e9);
                    if(dist>mx){ mx=dist; idx=j; }
                }
                fr[idx]=pg;
            }
        }
    }
    cout<<"Total Faults: "<<f<<endl;
    return 0;
}
