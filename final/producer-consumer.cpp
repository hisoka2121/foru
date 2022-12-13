#include<iostream>
using namespace std;

int mutex=1,empty=5,full=0,flag=0;

void wait(char s){
    if(s=='p'){
        // cout<<"Empty1"<<empty<<endl;
        if(empty<=0){
            cout<<"Buffer is empty:"<<endl;
            return;
        }
        empty--;
    }else if(s=='c'){
        if(full<=0){
            cout<<"Buffer is empty:"<<endl;
            flag=1;
            return;
        }
        full--;
    }else{
        mutex--;
    }
}

void signal(char s){
    if(s=='p'){
        full++;
    }else if(s=='c'){
        empty++;
    }else{
        mutex++;
    }
}

void consumer(){
    wait('c');
    wait('m');
    signal('m');
    signal('c');
    if(flag==0){
        cout<<"Item consume from buffer: "<<full<<endl;
    }else{
        flag=0;
    }
}

void producer(){
    wait('p');
    wait('m');
    signal('m');
    signal('p');
    if(flag==0){
        cout<<"Item added to buffer: "<<full<<endl;
    }else{
        flag=0;
    }
}

int main(){
    int n;
    cout<<"Enter the size of buffer: "<<endl;
    cin>>n;
    empty=n;
    while(true){
        int choice;
        cout<<"1. Call Producer()"<<endl;
        cout<<"2. Call Consumer()"<<endl;
        cout<<"3. End"<<endl;
        cout<<"Select your choice: "<<endl;
        cin>>choice;
        switch(choice){
            case 1: producer(); break;
            case 2: consumer(); break;
            case 3: exit(0);
        }
        cout<<endl;
        cout<<endl;
    }

    return 0;
}