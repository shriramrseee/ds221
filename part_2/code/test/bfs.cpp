#include <iostream>

using namespace std;

bool mat[300][300];

int main(int argc, char *argv[])
{
  string s;
  int a, b, c;

  for(int i=0; i<7; i++)
  {
    getline(cin, s);
  }
  for(int i=0; i<stoi(argv[1]); i++)
  {
   for(int j=0; j<stoi(argv[1]); j++)
   {
    mat[i][j]=0;
   }
  }
  for(int i=0; i<stoi(argv[2]); i++)
  {
   cin>>s;
   cin>>a>>b>>c;
   mat[a-1][b-1] = 1;
   mat[b-1][a-1] = 1;
  }
  cout<<stoi(argv[1])<<"\t"<<stoi(argv[1])<<"\n";
  for(int i=0; i<stoi(argv[1]); i++)
  {
   for(int j=0; j<stoi(argv[1]); j++)
   {
    cout<<mat[i][j];
    if(j != stoi(argv[1])-1)
      cout<<"\t";
   }
   cout<<"\n";
  }
  return 0;
} 

   

