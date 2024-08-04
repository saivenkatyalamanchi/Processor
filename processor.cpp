#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include<bits/stdc++.h>
#include<string>
using namespace std;
class core {
    public:
    vector<long> registers;
    int pc;
    core(){
    registers=vector<long>(32,0);
    pc=0;
    }

    bool execute(vector<string>&sorting,vector<int>& memory){
        
        if(pc >= sorting.size())
        {
            return false;
        }
        string instructionfetch=sorting[pc];
        
        int i=0;
      while(true)
      {
          if(instructionfetch[i]== ':' || instructionfetch[i]==' '){
                break;    
          } 
         i++;
      }
        
    string opcode =instructionfetch.substr(0,i);
    
    vector<string>v;
    v.push_back(opcode);

    if (opcode == "add")
    {
        if (i < instructionfetch.size()){
        string str = instructionfetch.substr(i+1);
        stringstream sExp(str);
        string term = "";
        while (getline(sExp, term, ' ')){
            v.push_back(term);
        }
        if(v.size() >= 4){
            int rd = stoi(v[1].substr(1));
            int sourceR1 = stoi(v[2].substr(1));
            int sourceR2 = stoi(v[3].substr(1));
            registers[rd] = long(registers[sourceR1] + registers[sourceR2]);
          }
       }
    }

    else if(opcode == "sub" )
    {
          string str=instructionfetch.substr(i+1);
            stringstream sExp(str);
            string term;
            while(getline(sExp, term, ' ')){
                v.push_back(term);
            }
             if (v.size() >= 4){
            int rd = stoi(v[1].substr(1));
            int sourceR1 = stoi(v[2].substr(1));
            int sourceR2 = stoi(v[3].substr(1));
            registers[rd] = long(registers[sourceR1]-registers[sourceR2]);
           }
    }
    else if(opcode == "addi")
    {
      string str=instructionfetch.substr(i+1);
            stringstream sExp(str);
            string term;
            while(getline(sExp, term, ' ')){
                v.push_back(term);
            }
               int rd = stoi(v[1].substr(1));
               int rs= stoi(v[2].substr(1));
               int value=stoi(v[3]);
             registers[rd]=registers[rs]+value;             
    }
    else if(opcode=="beq")
    {
      string str=instructionfetch.substr(i+1);
      stringstream sExp(str);
      string term;
      while(getline(sExp, term, ' ')){
      v.push_back(term);
      }
      v[3].push_back(':');
      int src1=stoi(v[1].substr(1));
      int src2=stoi(v[2].substr(1));
      if(registers[src1]==registers[src2]){
        int line = find(sorting.begin(),sorting.end(),v[3])-sorting.begin();
        pc=line;
        }  
    }
    else if (opcode == "lw") 
    {
      int offset=0;
      string str= instructionfetch.substr(i+1);
      for(int j=0;j<str.size();j++){
        if(str[j]=='x')
        {
         string ss;
         ss.push_back('x');
        if(isdigit(str[j+1]))
        {
        ss.push_back(str[j+1]);
        j++;
        if(isdigit(str[j+1]))
        {  ss.push_back(str[j+1]);
          j++;
        }
        }
                   
        v.push_back(ss);
       }
       else if(isdigit(str[j])){
       offset= stoi(str.substr(j,1));
       }
      }
      int rs1= stoi(v[2].substr(1));
      int rd= stoi(v[1].substr(1));
      offset=offset/4;
      registers[rd]=*(offset+(int *)registers[rs1]);
           
    }
    else if(opcode == "sw")
    {
      string str=instructionfetch.substr(i+1);
      stringstream sExp(str);
      string term;
      while(getline(sExp, term, ' ')){
      v.push_back(term);
      }
      int sr1=stoi(v[1].substr(1));
      int srADD=stoi(v[2]);
      string s=v[3];
      s.erase(0,2);
      s.pop_back();
      int rd=stoi(s);
      *(srADD/4+(int*)registers[rd])=registers[sr1];
    }
    else if(opcode == "j")
    {
      string s;
      string str=instructionfetch.substr(i+1);
      for(int k=0;k<str.size();k++){
      if(isalpha(str[k]) ||isdigit(str[k])){
      s.push_back(str[k]); 
        }
      }
      v.push_back(s);
      v[1].push_back(':');
      int line = find(sorting.begin(),sorting.end(),v[1])-sorting.begin();
      pc=line;
    }
    else if(opcode=="blt")
    {
     string str=instructionfetch.substr(i+1);
     stringstream sExp(str);
     string term;
      while(getline(sExp, term, ' ')){
       v.push_back(term);
      }
        v[3].push_back(':');
        int src1=stoi(v[1].substr(1));
        int src2=stoi(v[2].substr(1));
      if(registers[src1]<registers[src2]){
       int line = find(sorting.begin(),sorting.end(),v[3])-sorting.begin();
         pc=line;
        }
    }
    else if(opcode=="slli")
    {
      string str=instructionfetch.substr(i+1);
      string term;
      stringstream sExp(str);
      while(getline(sExp,term,' ')){
      v.push_back(term);
      }
      int rd=stoi(v[1].substr(1));
      int src1=stoi(v[2].substr(1));
      long src2=stoi(v[3].substr(1));
      registers[rd]=registers[src1]*long(pow(2,src2));
    }
    else if(opcode=="la")
    {
      string str=instructionfetch.substr(i+1);
      string term;
      stringstream sExp(str);
      while(getline(sExp,term,' ')){
        v.push_back(term);
      }
      if(v.size()>=2){
        int sd=stoi(v[1].substr(1));
        registers[sd]=long(&(memory[0])); 
      }
    }
    else if(opcode=="li")
    {  
      string str=instructionfetch.substr(i+1);
      string term;
      stringstream sExp(str);
      while(getline(sExp,term,' ')){
           v.push_back(term);
      }
      int sd=stoi(v[1].substr(1));
      registers[sd]=stoi(v[2].substr(1));
    }
    pc=pc+1;
    return true;
  }
};

class processor {
  public:
  vector<int>memory;
  vector<string>bubblesort;
  vector<string>selectionsort;
  core core1;
  core core2;
  int clock;
  processor(){
    memory=vector<int>(4096,0);
    clock=0;
  }
void print(){
  for(int i=0;i<32;i++){
  cout<<core1.registers[i]<<" ";
  }
  cout<<endl;
  for(int j=0;j<10;j++){
    cout<<memory[j]<<" ";
  }
  cout<<endl;
    for(int i=0;i<32;i++){
  cout<<core2.registers[i]<<" ";
  }
  cout<<endl;
  for(int j=0;j<10;j++){
    cout<<memory[j]<<" ";
  }
  cout<<endl;
  }
  void output()
  {
   bool flag=true;
   bool flags=true;
   while(flag)
   { 
    flag=core1.execute(bubblesort,memory);
   }
   while(flags){
      flags=core2.execute(selectionsort,memory);
  }
  }
};
int main(){
    processor PROCESSORS;
    PROCESSORS.memory[0]=10;
    PROCESSORS.memory[1]=9;
    PROCESSORS.memory[2]=8;
    PROCESSORS.memory[3]=7;
    PROCESSORS.memory[4]=6;
    PROCESSORS.memory[5]=5;
    PROCESSORS.memory[6]=4;
    PROCESSORS.memory[7]=3;
    PROCESSORS.memory[8]=2;
    PROCESSORS.memory[9]=1;

    PROCESSORS.core1.registers[1]=long(&(PROCESSORS.memory[0]));
    PROCESSORS.core1.registers[8]=long(&(PROCESSORS.memory[0]));
    cout<<"before bubble sort:"<<endl;
    PROCESSORS.print();
   cout<<"after bubblesort "<<endl;
    PROCESSORS.bubblesort={
    //"la x1 array",
    // "la x8 array",
    "addi x2 x0 0",  // x2==i=0 
    "addi x4 x0 10", // x4==n=20 size of the array
    "addi x5 x4 -1", // x5==size -1 
    "outerloop:",
    "beq x2 x4 exit1", // i==N
    "addi x3 x0 0",    // j=0
    "add x1 x0 x8",
    "innerloop:",
    "beq x3 x5 exit2", // j==n-1
    "lw x6 0(x1)",
    "lw x7 4(x1)",
    "blt x6 x7 NOswap", // branch if less than
    "sw x6 4 (x1)",
    "sw x7 0 (x1)",
    "NOswap:",
    "addi x1 x1 4",
    "addi x3 x3 1",
    "j innerloop",
    "exit2:",
    "addi x2 x2 1",
    "addi x5 x5 -1",
    "j outerloop",
    "exit1: j print",
    "print:",
    "lw x10 0(x8)",
    "add a0 x0 x10",
    "li a7 1",
    "ecall",
    "addi x8 x8 4",
    "addi x4 x4 -1",
    "bne x4 x0 print",
     };

PROCESSORS.output();
PROCESSORS.print();
cout<<"selectionsort code:"<<endl;
PROCESSORS.selectionsort={
"outerloop:",
"beq x1, x5, print", 
"addi x3, x1, 0",   
"addi x2, x1, 1",  

"innerloop:",
"beq x2, x4, swap", 
"slli x6, x2, 2",  
"add x7, x23, x6",
"lw x8, 0(x7)",     

"slli x9, x3, 2",  
"add x10, x23, x9", 
"lw x11, 0(x10)",    

"blt x11, x8, change", 
"addi x3,x2,0",   
"change:",

"addi x2, x2, 1", 
"beq x0, x0, innerloop",
"swap:",

"slli x12, x3, 2",    
"add x13, x23, x12",   
"lw x14, 0(x13)",      

"slli x6, x1, 2",    
"add x7,x23,x6",   
"lw x8, 0(x7)",      

"sw x14, 0(x7)",
"sw x8, 0(x13)",    

"addi x1, x1, 1",  
"beq x0, x0, outerloop",
"print:",
     "li x27,10",
    "ecall",
};

PROCESSORS.output();
PROCESSORS.print();
return 0;
}

