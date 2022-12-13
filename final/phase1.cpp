#include<iostream>
#include<fstream> 
#include<string>

using namespace std;

class OS{
    private:
    char IR[4];
    char R[4];
    char M[100][4];
    char buffer[44];
    bool C;
    int SI;
    int IC;

    public:
    void init();
    void MOS();
    void load();
    void execute();
    void print_mem();
    fstream infile;
    fstream outfile;
};


void OS::print_mem(){
    for(int i=0;i<100;i++){
        cout<<"M["<<i<<"]  :: ";
        for(int j=0;j<4;j++){
            cout<<M[i][j];
        }
        cout<<endl;
    }
}

void OS::init(){
    for(int i=0;i<100;i++){
        for(int j=0;j<4;j++){
            M[i][j] = '*';
        }
    }

    for(int i=0;i<4;i++){
        IR[i]=' ';
        R[i]=' ';
    }
    C=false;
}

void OS::MOS(){
    if(SI==1){
        cout<<"reading"<<endl;
        for(int i=0;i<44;i++){
            buffer[i]='\0';
        }

        infile.getline(buffer,44);
        int k=(IR[2]-48)*10;
        int i=0;
        for(int l=0;l<10;l++){
            for(int j=0;j<4;j++){
                M[k][j]=buffer[i];
                i++;
            }
            if(buffer[i]=='\0'){
                break; 
            }
            k++;
        }

    }else if(SI==2){
        for(int i=0;i<=40;i++)
           buffer[i]='\0';

        int k = 0;
        int i = IR[2]-48;
        i = i*10;


        for( int l=0 ; l<10 ;  ++l)
        {
            for(int j = 0 ; j<4; ++j)
            {
                buffer[k]=M[i][j];
                if(buffer[k]=='*'){
                    break;
                }
                outfile<<buffer[k];

                k++;
            }
            if(k == 40 )
            {
                break;
            }
            i++;
        }
        // outfile<<"\n";

    }else if(SI==3){
        outfile<<"\n";
        outfile<<"\n";
    }
}

void OS::execute(){
    while(true){
        for(int i=0;i<4;i++){
            IR[i]=M[IC][i];
        }
        IC++;
        if(IR[0]=='G' && IR[1]=='D'){
            SI=1;
            MOS();
        }else if(IR[0]=='P' && IR[1]=='D'){
            SI=2;
            MOS();
        }else if(IR[0]=='H'){
            SI=3;
            MOS();
            break;
        }else if(IR[0]=='L' && IR[1]=='R'){
            int i=(IR[2]-48)*10;
            i+=(IR[3]-48);
            for(int j=0;j<4;j++){
                R[j]=M[i][j];
            }
        }else if(IR[0]=='S' && IR[1]=='R'){
            int i=(IR[2]-48)*10;
            i+=(IR[3]-48);
            for(int j=0;j<4;j++){
                M[i][j]=R[j];
            }
            cout<<"After SR"<<endl;
            print_mem();
        }else if(IR[0]=='C' && IR[1]=='R'){
            int i=(IR[2]-48)*10;
            i+=(IR[3]-48);
            int count=0;
            for(int j=0;j<4;j++){
                if(R[j]==M[i][j]){
                    count++;
                }
            }

            if(count==4){
                C=true;
            }
        }else if(IR[0]=='B' && IR[1]=='T'){
            if(C){
                int i=(IR[2]-48)*10;
                i+=(IR[3]-48);
                IC=i;
            }
        }
    }
}

void OS::load(){
    int x=0;
    do{
        for(int i=0;i<44;i++){
            buffer[i]='\0';
        }
        infile.getline(buffer,44);
        cout<<buffer<<endl;
        if(buffer[0]=='$' && buffer[1]=='A' && buffer[2]=='M' && buffer[3]=='J'){
            init();
            
        }else if(buffer[0]=='$' && buffer[1]=='D' && buffer[2]=='T' && buffer[3]=='A'){
            IC=0;
            execute();
        }else if(buffer[0]=='$' && buffer[1]=='E' && buffer[2]=='N' && buffer[3]=='D'){
            x=0;
            continue;
        }else{
            cout<<"X::"<<x<<endl;
            int k=0;
            for(;x<100;x++){
                for(int j=0;j<4;j++){
                    M[x][j]=buffer[k];
                    k++;
                }
                if(k==40 || buffer[k]=='\0'){
                    x++;
                    break;
                }
            }
            print_mem();
            cout<<"X::After:: "<<x<<endl;
        }
    }while(!infile.eof());
}

int main(){
    // printf("Hello World!\n");
    OS os;
    os.infile.open("input.txt",ios::in);
    os.outfile.open("output1.txt",ios::out);
    if(!os.infile){
        cout<<"F"<<endl;
    }else{
        cout<<"SS"<<endl;
        os.load();
    }
    
    return 0;
}