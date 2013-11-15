#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include "f.h"

using namespace std;
int main(int argc, char **argv)
{
  system("./first");
  //wait til all tasks end
  while(system("condor_wait hostlog") != 0){}//system("clear");
  
  
  FILE *fin;
  FILE *inp;
  fin = fopen("var.txt", "r");
  
  int amount, num;
  double min, max, step, cur = 0;
  char *input = new char[100];
  char *buf = new char[1024];
  char *shell_command = new char[20];
  fscanf(fin, "%s", input);
  fscanf(fin, "%d", &amount);
  fscanf(fin, "%d", &num);
  fscanf(fin, "%lf", &min);
  fscanf(fin, "%lf", &max);
  fscanf(fin, "%lf", &step);
  
  int i = 0;
  inp = fopen(input, "r");
  
  instr *in_struct = new instr[amount]; 
      
  while(fscanf(inp, "%s", buf)==1)
  {
      fscanf(inp, "%d", &in_struct[i].value);
      strcpy(in_struct[i].name, buf);
      //cout<<i+1<<")"<<in_struct[i].name<<"  "<<in_struct[i].value<<endl;
      i++;
   }
  
  system("mkdir hostout");
  for(in_struct[num].value = min; in_struct[num].value <= max; in_struct[num].value += step)
  {
    sprintf(shell_command, "cp sub%d/hostout%d hostout", in_struct[num].value, in_struct[num].value);
    system(shell_command); 
  }
  in_struct[num].value-=step;
  system("sh clean.sh");
  int out_num;
  ifstream inf;
  chdir("hostout");
  sprintf(buf, "hostout%d", in_struct[num].value);
  cout<<buf<<endl;
  inf.open(buf);
  while(inf.getline(buf, 1024, '\n')) out_num++;
  chdir("..");
  cout<<out_num<<endl;
  
  
   
  
  
  //cout<<"end"<<endl;

  
  return 0;
}
