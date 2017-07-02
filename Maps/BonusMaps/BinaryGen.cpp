#include<fstream>
#include<iostream>
#include<cstdlib>
using namespace std;

int main()
{
    fstream f1,f2;
    f1.open("bonusmap3.txt",ios::in);
    f2.open("bonusmap3.bin",ios::in|ios::out|ios::binary);
   if(!f1)
   {
          exit(0);
   }

    int l[14][13];


    char x;
    int y;



    for(int i=0;i<14;i++)
    for(int j=0; j<13;j++)
    {
        f1>>x;
        l[i][j]=int(x-'0');
        f2.write((char*)&l[i][j],sizeof(l[i][j]));
        cout<<l[i][j];


    }
    f2.seekp(ios::beg);
    cout<<endl;

    for(int i=0;i<14;i++)
    for(int j=0; j<13;j++)
    {
        f2.read((char*)&y,sizeof(y));
        cout<<y;

    }


f2.close();
cin.get();
cin.ignore();
return 0;
}

