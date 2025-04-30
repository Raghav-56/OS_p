#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    int req[] = {82, 170, 43, 140, 24, 16, 190};
    int n = 7, head = 50, disk_size = 200, dir = 1; // dir: 1=right, 0=left
    int total = 0, pos = 0;
    int arr[8];
    for(int i=0;i<n;i++) arr[i]=req[i];
    arr[n]=head;
    sort(arr, arr+n+1);
    for(int i=0;i<=n;i++) if(arr[i]==head) { pos=i; break; }
    cout<<"Order: ";
    if(dir) {
        for(int i=pos;i<=n;i++) cout<<arr[i]<<" ";
        for(int i=pos-1;i>=0;i--) cout<<arr[i]<<" ";
        for(int i=pos+1;i<=n;i++) total+=arr[i]-arr[i-1];
        for(int i=pos-1;i>=0;i--) total+=arr[i+1]-arr[i];
    } else {
        for(int i=pos;i>=0;i--) cout<<arr[i]<<" ";
        for(int i=pos+1;i<=n;i++) cout<<arr[i]<<" ";
        for(int i=pos-1;i>=0;i--) total+=arr[i+1]-arr[i];
        for(int i=pos+1;i<=n;i++) total+=arr[i]-arr[i-1];
    }
    cout<<"\nTotal Head Movement: "<<total<<endl;
    return 0;
}