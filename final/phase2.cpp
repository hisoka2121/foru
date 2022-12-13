#include<bits/stdc++.h>


using namespace std;


fstream infile ;
fstream outfile ;

char buffer[40] ;
char IR[4] , M[300][4] , R[4];
int PTR , PTE , RA  ,LLC ,TLC ,TI = 0 ,SI=0 , PI=0 ,visited_page[40] ,IC ;
bool c = false  ;
int page_table_entry = -1 ;
//LLC LINE LIMIT COUNTER TLC TIME LIMIT COUNTER
class PCB{

public :
int job ,TTL = 0, TLL = 0;

};
PCB pcb;
//functions
void executeProgram();
void load();
//UTILS
int char_to_int(char c )
{
    return (c - 48);
}
char int_to_char(int i)
{
  return i + 48;
}
bool is_num(char c )
{
    int i =  char_to_int(c) ;
    if( i < 0 || i > 9 )
    {
        return false ;
    }
    return true ;
}
//
void check_TTL()
{
    if(TLC > pcb.TTL )
        {
                TI = 2 ;
        }
   else{
        TI = 0 ;
        }
}
void check_TLL()
{

}
void terminate_code(string s)
{
    outfile << "\n\n " <<s ;
    outfile << "\nTerminate At : " << IR[0]<<IR[1]<<IR[2]<<IR[3] ;

    cout << "\nJob ID : "<<pcb.job <<" TTL: "<<pcb.TTL<<" TLC " << TLC<<"TLL: "<<pcb.TLL<<" LLC: " << LLC << " SI: " << SI  << " PI: " << PI<< " TI : "<< TI ;
    outfile << "\nJob ID : "<<pcb.job <<" TTL: "<<pcb.TTL<<" TLC " << TLC<<"TLL: "<<pcb.TLL<<" LLC: " << LLC << " SI: " << SI  << " PI: " << PI<< " TI : "<< TI ;
    //cout << "load" ;
    load();
    //exit(1);
}
void allocate()
{
    // storing in pages in memory

    int new_address = rand()%30 ;  // ADDRESS FOR FRAME
    page_table_entry++;
    cout << "address of control card frame is : "<< new_address ;
    while(visited_page[new_address] == 1 )
    {
        new_address = rand()%30 ;
    }
    visited_page[new_address] = 1 ;
    M[PTR + page_table_entry][2] = (new_address / 10) +48 ;
    M[PTR + page_table_entry][3] = ( new_address%10) + 48 ;
    cout << "address of control card frame is : "<< M[PTR][2] <<M[PTR][3];

    // fetch program card and store it in frame with new_address
    for(int i = 0 ; i < 40 ;i++)
    {
        buffer[i]='_';
    }
    infile.getline(buffer , 41 ) ;
    cout << "\nBuffer is : \ n  " ;
    for(int i = 0 ; i < 40 ; i++ )
    {
        cout << buffer[i];
    }
    int k = 0 ;
    int frame_starts_at = new_address*10 ;
    for(int i = 0 ;  i <10 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            M[frame_starts_at + i][j] = buffer[k];
            k++ ;
          cout << k ;

        }
        if(buffer[k]=='H')
            {
                M[frame_starts_at+i+1][0] ='H';
                M[frame_starts_at+i+1][1] ='0';
                M[frame_starts_at+i+1][2] ='0';
                M[frame_starts_at+i+1][3] ='0';
                k++;
                break ;
            }
        if(k==40  && buffer[k]!='H')
            {
                cout << "Second Program Card";
                M[frame_starts_at + i][39] = buffer[k];
                allocate();
                break ;
            }

        }

return ;
}


int map_address(int VA) // VA TO RA
{
    /*if(VA > 99  || VA < 0 )
        {   cout << "operand error as RA : "<< RA <<endl ;
            PI = 2 ;
        }*/

    PTE = PTR + VA/10 ;



    if(M[PTE][0]=='_' || M[PTE][3]=='*')
    {
       // cout << "This is a valid page fault at :" << RA <<endl ;
         PI = 3 ;
        int new_address = (rand()%30) ;
        while(visited_page[new_address]!=0)
        {
            new_address = (rand()%30) ;

        }

            visited_page[new_address] = 1 ;
            M[PTE][2]=(new_address / 10 )+48;
            M[PTE][3]= (new_address % 10 )+48;
    }

    int frame_number = char_to_int(M[PTE][2])*10 + char_to_int(M[PTE][3]);
    RA = frame_number*10 + VA%10;
    cout << "in map_address " << RA << "PTR " << PTR << "VA "<< VA <<" frame_number "<< frame_number <<endl ;

return RA;
}


void read()
{
    for(int i = 0 ; i < 40 ; i++)
    {
        buffer[i]='_' ;
    }
    infile.getline(buffer , 40) ;
    cout << "buffer data from read \n" ;
     for(int i = 0 ; i < 40 ; i++)
    {
        cout << buffer[i] ;
    }

    if(buffer[0]=='$'&& buffer[1]=='E' &&  buffer[2]=='N' && buffer[3]=='D')
        {
            terminate_code("Out of data error ");

        }

    cout << "Read(): RA at : "<<RA <<endl ;
    //int frame_starts_at = (M[RA][2]-48)+M[RA][3]-48 ;
    int frame_starts_at = RA ;
    int k = 0 ;
     for(int i = 0 ;  i <10 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
        M[frame_starts_at + i][j] = buffer[k];
        k++ ;

        if(k==39 )
            {
                M[frame_starts_at][39]='_';
            }

        }


        }
        for(int i = 0 ; i < 300 ; i++)
        {   cout << i<<" " ;
            for(int j = 0 ; j < 4 ; j++)
            {
                cout << M[i][j];
            }
            cout << endl ;
        }
     executeProgram();
}

void write()
{   //int frames_starts_at = (M[RA][2]-48)+M[RA][3]-48 ;
    int frames_starts_at = RA ;
    LLC+=1 ;

    for(int i =0 ; i<40 ; i++ )
    {
        buffer[i] = '\0';
    }

    for(int i = 0 ,k=0 ; i<10  ; i++ )
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            buffer[k] = M[frames_starts_at+i][j];
            k++;
        }
    }
    int  k = 0 ;
    cout <<  "buffer from write : " ;
    while(buffer[k]!='\0')
    {
        cout << buffer[k];
        k++;
    }
    outfile << buffer ;

    if(LLC > pcb. TLL )
            {
                TI = 2 ;
                //outfile << "Abnormally: ";
               /* for( int i = 0 ; i < 4 ;i++)
                {
                    outfile <<IR[i];
                }*/
                terminate_code("1 Line Limit Exceeded");

            }
            executeProgram();

}

void MOS()
{
    /*if(TI==1)
    {
        cout << "Line Limit Exceed !!! "<<endl ;
        outfile << "Line Limit Exceed !!!" << endl ;
       outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code();
    }*/
    if(TI==0)
    {
        if(SI==1)
        {
            cout << "Read data\n" <<endl;

            read() ;
        }
        else if(SI==2)
        {
            cout << "Write Data\n" << endl ;
            write();
        }
        else if (SI==3){
            //outfile << "\nTerminated normally !!!";
            cout << "\nTerminated normally-- !!!";
            terminate_code("0 No ERROR");
        }
        else if(PI==1)
        {
            cout << "OPCODE ERROR !!!" <<endl;
            //outfile << "OPCODE ERROR !!!"<<endl;

             //outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code("4 OPERATION CODE ERROR");

        }
        else if(PI==2)
        {
            cout << "OPERAND !!!"<<endl;
            outfile << "OPERAND ERROR !!!"<<endl;
             outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code("5 OPERAND ERROR");
        }
        else if (PI==3){
                cout << "PAGE FAULT !!!" <<endl ;

                    cout << "INVALID PAGE FAULT GENERATED EITHER FROM LR OR SR !!!" << endl ;
                    //outfile << "INVALID PAGE FAULT GENERATED EITHER FROM LR OR SR !!!" << endl ;
                    terminate_code("6 INVALID PAGE FAULT");


        }

    }
    // when TI = 2
        if(TI==2)
    {
        cout << "Time Limit Exceed !!! "<<endl ;
        outfile << "Time Limit Exceed !!!" << endl ;

        if(SI==1)
        {
             //outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code("3 TIME LIMIT EXCEED ");
        }
        else if(SI==2)
        {
            cout << "Write Data" ;
             //outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code("3 TIME LIMIT EXCEED");
        }
        else if(SI==3){
            outfile << "Halt " ;
            terminate_code("3 NO ERROR");
        }
        else if(PI==1 )
        {
             //outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code("3 TIME LIMIT EXCEED \n 4 OPCODE ERROR");
        }
                else if(PI==2 )
        {
             //outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code("3 TIME LIMIT EXCEED \n 5 OPERAND ERROR");
        }
                else if(PI==3 )
        {
             //outfile << "Terminated abnormally !!!";
            cout << "Terminated abnormally !!!";
            terminate_code("3 TIME LIMIT EXCEED \n 6 PAGE FAULT ERROR");
        }

    }


}

void examine()
{
    cout << "Examining instruction : " <<IR[0] << IR[1] << IR[2] <<IR[3] <<endl;

    PI = 0 , SI=0,TI=0;
    char c  =  IR[0] ;
    int address = (IR[2]-48)*10 +(IR[3]-48);
    if(address>100 || address < 0 )
    {
           PI=2;
           MOS();
    }
    switch(c)
    {
    case 'G' :
        if(IR[1]!='D')
        {

            PI = 1 ;
            MOS();
        }
        else
            {
            TLC+=2;
            cout << "TLC : "<< TLC << " LLC: "<< LLC << endl ;
            check_TTL();
            SI = 1 ;
            MOS();
        }
        break ;
case 'P' :
        if(IR[1]!='D')
        {
            PI = 1 ;
            MOS();
        }
        else
            {
            TLC+=1;

            cout << "TLC : "<< TLC << endl ;
            check_TTL();
            SI = 2 ;

            MOS();
        }
        break ;
    case 'L' :
        if(IR[1]!='R')
        {
            PI = 1 ;
        }
        else{
            TLC+=1;
            check_TTL;

        }


        for(int i = 0 ; i<4 ;i++)
        {
             R[i] =  M[RA][i];

        }

        MOS();

        break ;
case 'S' :
        if(IR[1]!='R')
        {
            PI = 1 ;

        }
        else
            {
            TLC+=2;

            cout << "TLC : "<< TLC << endl ;
            check_TTL();

            for(int i = 0 ; i<4 ;i++)
            {
                M[RA][i] = R[i];
            }

        }

        MOS();
        break ;
case 'H' : TLC+= 1 ;
           SI = 3 ;
           MOS() ;
           break ;


case 'C' :
            for(int i = 0 ; i<3 ;i++)
            {    c = true ;
                if(M[RA][i] != R[i])
                {
                    c = false ;
                    break ;
                }
            }
            break ;
case  'B' :
        if(IR[1]!='T')
        {
            PI = 1 ;

        }
            if(c){
            IC = char_to_int(IR[2])*10 + char_to_int(IR[3]);
            }
            c=false ;
            break ;
default :
          PI = 1 ;
          MOS() ;

    }
}

void executeProgram(){

while(true)
{   PI = 0 ;
    map_address(IC);
    /*if(PI!=0)
    {
              if(PI == 2 )
           {
               terminate_code("OPCODE ERROR ");
           }

    }*/
   for(int k = 0 ; k < 4 ; k++)
    {
                IR[k] = M[RA][k];
    }
    IC = IC+1;

    if( !(is_num(IR[2]) && is_num(IR[3])))
           {   //outfile << "from if " << IR[2] << IR[3];
               terminate_code("OPERAND ERROR ");
           }

    int va = (IR[2]-48)*10 + (IR[3]-48);
    map_address(va);
    if(PI!=0)
    {
            if(PI == 3 && (IR[0] == 'L' || R[0] == 'P')  )
           {
               terminate_code(" PAGE FAULT ");
           }

    }


    cout << "\n FOR "<<IR[0]<< IR[1]<<"ENDL RA IS : " << RA ;
    examine();


}

}
void start_execution()
{
   IC = 0 ;
   executeProgram();
}

void init()
{
   TI = 0 ,SI=0 , PI=0 ,page_table_entry = -1 ;;

   for(int i = 0 ; i < 30 ; i++)
   {
       visited_page[i]=0;
   }

   for(int i = 0; i < 300 ; i++)
   {
      for(int j = 0 ; j< 4 ; j++)
      {
           M[i][j]='_';
      }
   }
   // setting up page table
    PTR = ((rand())%30)*10 ;
    visited_page[PTR/10] = 1 ;

    for(int i = PTR ; i < PTR+10 ; i++)
    { for(int  j = 0 ; j < 4 ; j++)
        M[i][j]='*';
    }
    cout << "Page table stored at: "<<PTR<<endl;


}

void load(){



while(!infile.eof())
{
    for(int i = 0 ; i < 40 ; i++)
        buffer[i] = '\0' ;

    infile.getline(buffer , 40 ) ;

   for(int i = 0 ; i < 40 ; i++)
        cout << buffer[i] ;
    for(int i = 0 ; i < 40 ; i++)
    {
        if(buffer[i] == '\0' || buffer[i] ==' ')
        {
            break ;
        }
        else if(buffer[0] == '$' && buffer[1] == 'A' && buffer[2]=='M' && buffer[3]=='J')
        {
            // pcb load
            // load program card
            //$AMJ 0000 0000 0000
            init() ;
            pcb.job = (buffer[4]-48)*1000 + (buffer[5]-48)*100 + (buffer[6]-48)*10 + (buffer[7]-48);
            pcb.TTL = (buffer[8]-48)*1000 + (buffer[9]-48)*100 + (buffer[10]-48)*10 + (buffer[11]-48);
            pcb.TLL = (buffer[12]-48)*1000 + (buffer[13]-48)*100 + (buffer[14]-48)*10 + (buffer[15]-48);

            cout << endl << "Job: "<< pcb.job << " TTL: " <<pcb.TTL << " TLL: "<<pcb.TLL << endl;
            i=15;
            TLC = 0 ;
            LLC = 0 ;
            // allocate program card
            allocate();
                    cout << endl ;
        for(int i = 0 ; i < 300 ; i++)
        {   cout << i<<" " ;
            for(int j = 0 ; j < 4 ; j++)
            {
                cout << M[i][j];
            }
            cout << endl ;
        }


        }
        else if(buffer[0]=='$' && buffer[1]=='D'&& buffer[2]=='T'&& buffer[3]=='A')
        {
            //load data card
            cout << "\n IN dta ";
            start_execution() ;



        }
        else if(buffer[0]=='$'&& buffer[1]=='E' &&  buffer[2]=='N' && buffer[3]=='D')
        {
            cout << "in end" ;

                    for(int i = 0 ; i < 300 ; i++)
        {   cout << i<<" " ;
            for(int j = 0 ; j < 4 ; j++)
            {
                cout << M[i][j];
            }
            cout << endl ;
        }

            break;
            //terminate_code();

        }



    }


}
exit(1);


}

int main()
{


    infile.open("input2.txt" , ios::in) ;
    outfile.open("output.txt", ios::out) ;

     load();




    return 0 ;
}




