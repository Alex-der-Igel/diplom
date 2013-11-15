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
  char *file_in = new char[100];
  char *file_out = new char [100];
  //char *variation = new char[100];
  char *exec = new char[100];
  char *shell_command = new char [20];
 
  FILE *fin;
  FILE *fout;
  FILE *finput;
  FILE *var;
  FILE *outstr;
 
  //char *out_str = new char [1024];
 
  char *file_sub = new char[100];
  ifstream inf;
  int in_num = 0; 
  int out_num = 0; 
  /*if (argc != 2)
    {
      cout<<"Incorrect request"<<endl;
      return -1;
    }
  
  else if (argc == 2)
    {
      strcpy(file_in, argv[1]);
    }*/
  char *buff = new char[1024];
 
  cout << "Enter exec file"<<endl;
  cin >> exec;
  cout << "Enter input file" << endl; 
  cin >> file_in; 
  cout << "Enter output file" <<endl;
  cin >> file_out;
  
  sprintf(shell_command, "./%s %s > %s", exec, file_in, file_out);
  system (shell_command);
  
  inf.open(file_out);
  while(inf.getline(buff, 1024, '\n')) out_num++;
  cout << out_num << endl;
  inf.close();
  //sprintf(out_str, "struct out_str\n{\ndouble *var = new double[%d];\nchar *name = new char [20];\n}\n;", out_num);
  /*outstr = fopen("out_str.h", "w");
  fprintf (outstr, "struct out_str\n{\ndouble *var = new double[%d];\nchar *name = new char [20];\n}\n;", out_num);
  fclose(outstr);*/
  inf.open(file_in);
  while(inf.getline(buff, 1024, '\n')) in_num++;
  inf.close();
  //cout<<"!"<<in_num<<endl;
  fin = fopen(file_in, "r");
  if(!fin){ cout<<"Error occured while opening file"<<endl; return -2;}
  int i = 0, amount = 0;
  amount = in_num;
  //char name[100][10];
  char *buf = new char[10];
  char *input = new char[20];
  //char *shell_command = new char[20];
  //double *value = new double[100];
  instr *in_struct = new instr[amount]; 
  //strcpy(exec, "task1_8sem");
  
  //system(com);
  
  while(fscanf(fin, "%s", buf)==1)
  {
      fscanf(fin, "%d", &in_struct[i].value);
      strcpy(in_struct[i].name, buf);
      cout<<i+1<<")"<<in_struct[i].name<<"  "<<in_struct[i].value<<endl;
      i++;
   }
  
  //amount = i;
  cout << "Enter parametr # min max step" << endl;
  double min = 0, max = 10, step = 1;
  int num = 0;
  
  cin >> num;
  cin >> min;
  cin >> max;
  cin >> step;
  num--;
 // strcpy(variation, "var.txt");
  var = fopen("var.txt", "w");
  fprintf(var, "%s %d %d %lf %lf %lf", file_in, amount, num, min, max, step);
  fclose(var);
  
  in_struct[num].value = min;
  int var_num = 0;
  cout<<"!"<<endl;
  while (in_struct[num].value <= max)
  {
    cout<<"12"<<endl;
    var_num++;
    sprintf(file_sub, "condor.sub");//, value[num]);
    //cout<<file_sub<<endl;
    sprintf(shell_command, "mkdir sub%d", in_struct[num].value);
    system(shell_command);
    
    sprintf(shell_command, "cp %s sub%d", exec, in_struct[num].value);
    system(shell_command);
    
    sprintf(shell_command, "cp in sub%d/in%d", in_struct[num].value, in_struct[num].value);
    system(shell_command);
    
    sprintf(shell_command, "sub%d", in_struct[num].value);
    chdir(shell_command);
    sprintf(input, "in%d", in_struct[num].value);
    finput = fopen(input, "w");
    for(i = 0; i < amount; i++)
      {
        fprintf(finput, "%s %d\n", in_struct[i].name, in_struct[i].value);
      }
    
    
    //generate input file
    
    
    
    fout = fopen(file_sub, "w");
    fprintf(fout, "should_transfer_files = Yes\r\nwhen_to_transfer_output = ON_EXIT_OR_EVICT\r\nuniverse = vanilla\r\nexecutable = %s\r\narguments =  in%d\r\ntransfer_input_files =  %s, in%d\r\nlog        = ../hostlog\r\nOutput     = hostout%d\r\nError      = hosterr\r\nqueue", exec, in_struct[num].value, exec, in_struct[num].value, in_struct[num].value);
    fclose(fout);
    
    system("condor_submit condor.sub");
    
    chdir("..");   
    in_struct[num].value += step;
  }
  
  //generate out structure
  
  outstr = fopen("out_str.h", "w");
  fprintf (outstr, "struct out_str\n{\ndouble *var = new double[%d];\nchar *name = new char [20];\n}\n;", var_num);
  fclose(outstr);
  
  
   

  
  return 0;
}
