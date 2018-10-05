#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  string s;
  int a, b, c;
  int rows = stoi(argv[1]);
  int cols = stoi(argv[1]);

  bool** mat = new bool*[rows];
  for (int i = 0; i < rows; ++i)
    mat[i] = new bool[cols];

  for(int i=0; i<7; i++)
  {
    getline(cin, s);
  }

  for(int i=0; i<rows; i++)
  {
   for(int j=0; j<cols; j++)
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

  cout<<rows<<"\t"<<cols<<"\n";

  for(int i=0; i<rows; i++)
  {
   for(int j=0; j<cols; j++)
   {
    cout<<mat[i][j];
    if(j != rows-1)
      cout<<"\t";
   }
   cout<<"\n";
  }

  return 0;
} 

   

