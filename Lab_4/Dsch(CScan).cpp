#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int req[] = {82, 170, 43, 140, 24, 16, 190};
    int n = 7, head = 50, disk_size = 200, dir = 1;
    int total = 0, pos = 0;
    int arr[8];
    for(int i=0;i<n;i++) arr[i]=req[i];
    arr[n]=head;
    sort(arr, arr+n+1);
    for(int i=0;i<=n;i++) if(arr[i]==head) { pos=i; break; }
    cout<<"Order: ";
    if(dir) {
        for(int i=pos;i<=n;i++) cout<<arr[i]<<" ";
        cout<<disk_size-1<<" ";
        for(int i=pos-1;i>=0;i--) cout<<arr[i]<<" ";
        total += (disk_size-1-arr[pos]);
        total += (disk_size-1-arr[0]);
        total += (arr[pos-1]-arr[0]);
    } else {
        for(int i=pos;i>=0;i--) cout<<arr[i]<<" ";
        cout<<0<<" ";
        for(int i=pos+1;i<=n;i++) cout<<arr[i]<<" ";
        total += (arr[pos]-0);
        total += (arr[n]-0);
        total += (arr[n]-arr[pos+1]);
    }
    cout<<"\nTotal Head Movement: "<<total<<endl;
    return 0;
}