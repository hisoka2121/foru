#include<bits/stdc++.h>
using namespace std;

int wrt;
int m;
vector<int> buffer;
int reader_count;

void print()
{

cout<<"Current File Status"<<endl;
cout<<"Reader Count:"<<reader_count<<endl;
for(int i=0;i<buffer.size();i++)

{
cout<<buffer[i]<<",";

}
cout<<endl;
}

int wait(int *s)
{
while((*s)<=0)
{
cout<<"Entered Infinite Loop !!!!"<<endl;

return (*s);
}
if((*s)>0)
{
cout<<*s;
(*s)--;
return (*s);
}
}

int signal(int *s)
{
(*s)++;
return (*s);
}

void reader()
{

wait(&m);
if(m==-1)
{
return;
}
reader_count++;
if(reader_count==1)
{
wait(&wrt);
if(wrt==-1)
{
return;
}
}
signal(&m);
cout<<"Performing File Read"<<endl;
print();
wait(&m);
reader_count--;
if(reader_count==0)
{
signal(&wrt);
}
signal(&m);
}

void writer()
{
wait(&m);
if(m==-1)
{

return;
}
cout<<"Performing Write Operation"<<endl;
int a=rand()%10;
buffer.push_back(a);
signal(&m);
}
int main()
{

m=1;
wrt=1;
reader_count=0;
cout<<"Size of file is 5"<<endl<<endl;
int choice;
while(1)
{
cout<<"Mutex:"<<m<<endl;
cout<<"\n\n1.Reader"<<endl;
cout<<"2.Writer"<<endl;
cout<<"3.Exit"<<endl;
cout<<"Enter your choice"<<endl;
cin>>choice;
switch(choice)
{
case 1:reader();
break;
case 2:writer();
break;
case 3: cout<<"Exiting..."<<endl;

exit(0);
break;
default:cout<<"Invalid Input";

}
print();
}
return 0;
}