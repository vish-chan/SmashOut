#include<fstream>
#include<iostream>
using namespace std;

struct LevelInfo
{
    int Level;
    int Points;
    int Open;
};    
    

int main()
{
    LevelInfo S[30],A;
    for(int i=0; i<30 ;i++)
    {
        S[i].Level=i+1;
        S[i].Points=0;
        S[i].Open=0;
    }
    S[0].Open=1; 
    
    
       
    fstream f1,f2;
   
    char x;
   int y;
   f2.open("levelsinfo_allopen.bin",ios::out|ios::binary);
   for(int i=0;i<30;i++)
   f2.write(reinterpret_cast<char*>(&S[i]),sizeof(S[i]));

   
   f2.close();
    

    
    f1.open("levelsinfo_allopen.bin",ios::in|ios::binary);
    f1.read(reinterpret_cast<char*>(&A),sizeof(A));
    cout<<A.Level<<"   "<<A.Points<<"   "<<A.Open;
    
    
    for(int j = 1;j<30;j++)
    {
        cout<<endl;
        f1.read(reinterpret_cast<char*>(&A),sizeof(A));
        cout<<A.Level<<"   "<<A.Points<<"   "<<A.Open;
        
        
    }

f1.close();

cin.get();
cin.ignore();
return 0;
}    
    
