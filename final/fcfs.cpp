#include<iostream>
#include<map>
#include<vector> 

using namespace std;

vector<int> AT,BT,TAT,CT,WT;
multimap<int,int> mp;

void cal_CT(){
    int sum = 0;
    for(auto it=mp.begin(); it!=mp.end(); it++){
        sum += BT[it->second];
        CT[it->second] = sum;
        cout<<it->first<<" "<<it->second<<" "<<CT[it->second]<<endl;
    }
}

void cal_TAT_and_WT(int n){
    for(int i=0;i<n;i++){
        TAT[i]=CT[i]-AT[i];
    }

    for(int i=0;i<n;i++){
        WT[i]=TAT[i]-BT[i];
    }
}

int main(){
    int n;
    cout<<"Enter the number of Process: "<<endl;
    cin>>n;
    cout<<"Enter the Arrival time and Burst time of the process: "<<endl;
    for(int i=0;i<n;i++){
        int x,y;
        cout<<"AT["<<i<<"]= ";
        cin>>x;
        cout<<"BT["<<i<<"]= ";
        cin>>y;
        AT.push_back(x);
        BT.push_back(y); 
        mp.insert({x,i});
    }
    for(int i=0;i<n;i++){
        TAT.push_back(0);
        CT.push_back(0);
        WT.push_back(0);
    }


    cal_CT();
    cal_TAT_and_WT(n);
    cout<<"P "<<"AT "<<"BT "<<"CT "<<"TAT "<<"WT "<<endl;
    for(int i=0;i<n;i++){
        cout<<"P"<<i<<"  "<<AT[i]<<"  "<<BT[i]<<"  "<<CT[i]<<"  "<<TAT[i]<<"  "<<WT[i]<<endl;
    }

    return 0;
}