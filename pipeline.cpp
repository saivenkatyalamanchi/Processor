#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bits/stdc++.h>
#include <string>
using namespace std;
class interpreter {
    public:
    void interpreting(vector<string>&sort,vector<int>& store){
    for(int h=0;h<sort.size();h++)
    {
      string instructionfetch=sort[h];
      int i=0;
      while(true)
      {
          if(instructionfetch[i]== ':' || instructionfetch[i]==' ')
          {
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
            int sR1 = stoi(v[2].substr(1));
            int sR2 = stoi(v[3].substr(1));
            int start=1;
            start=start+rd*pow(2,7)+0*pow(2,12)+sR1*pow(2,15)+sR2*pow(2,20)+0*pow(2,25);
            store.push_back(start);
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
            int sR1 = stoi(v[2].substr(1));
            int sR2 = stoi(v[3].substr(1));
            int start=2;
            start=start+rd*pow(2,7)+0*pow(2,12)+sR1*pow(2,15)+sR2*pow(2,20)+0*pow(2,25);
            store.push_back(start);
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
               int start=3;
              start=start+rd*pow(2,7)+0*pow(2,12)+rs*pow(2,15)+value*pow(2,20);
                store.push_back(start);          
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
      int st=find(sort.begin(),sort.end(),v[3]) - sort.begin();
      int start=4;  // here src1 and src2 may be change need
      start=start+src1*pow(2,7)+src2*pow(2,12)+st*pow(2,17); 
     // sort.push_back(start);  error showing why i don't
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
      // offset=offset/4;
      int start=5;
      start=start+rd*pow(2,7)+0*pow(2,12)+rs1*pow(2,15)+((offset)/4)*pow(2,20);
      store.push_back(start);
           
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
      int srADD=stoi(v[2]);// actually it is a value
      string s=v[3];
      s.erase(0,2);
      s.pop_back();
      int rd=stoi(s); // i changed something new see 
      
        int start=6;
        start=start+sr1*pow(2,20)+0*pow(2,12)+srADD*pow(2,15)+(rd)*pow(2,7);
        store.push_back(start);
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
     int st = find(sort.begin(),sort.end(),v[1])-sort.begin();
     int start=7;
     start=start+st*pow(2,7);
     store.push_back(start);
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
      int st=find(sort.begin(),sort.end(),v[3])-sort.begin();
      int start=8;
      start=start+src1*pow(2,7)+src2*pow(2,12)+st*pow(2,17);
      store.push_back(start);
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
      int start=9;
      start=start+rd*pow(2,7)+0*pow(2,12)+src1*pow(2,15)+src2*pow(2,20);
      store.push_back(start);
    }
    // else if(opcode=="la")
    // {
    //   string str=instructionfetch.substr(i+1);
    //   string term;
    //   stringstream sExp(str);
    //   while(getline(sExp,term,' ')){
    //     v.push_back(term);
    //   }
    //   if(v.size()>=2){
    //     int sd=stoi(v[1].substr(1));
    //     registers[sd]=long(&(memory[0])); 
    //   }
    // }
    else if(opcode=="li")
    {  
      string str=instructionfetch.substr(i+1);
      string term;
      stringstream sExp(str);
      while(getline(sExp,term,' ')){
           v.push_back(term);
      }
      int sd=stoi(v[1].substr(1));
      int st=stoi(v[2]);//li a7 5   5=st
      int start=10;
      start=start+sd*pow(2,7)+st*pow(2,12);
                store.push_back(start);
    }
  
   }
  }
};
class core{
    
public:
    std::vector<long> registers;
    int pc;
    int stall;
    insfetch i1;
    insdecode i2;
    execute i3;
    memore i4;
    writ i5;
    Core() :registers(32,0),pc(0){}
    bool executeWholeProgram(vector<int> memory,vector<int> programone)
    {
        //pipeline should be executed here
        return true;
    }
};
class processor {
  public:
  vector<int>memory;
  
};
int main(){
    processor PROCESSORS;
  //   PROCESSORS.memory[0]=10;
  //   PROCESSORS.memory[1]=9;
  //   PROCESSORS.memory[2]=8;
  //   PROCESSORS.memory[3]=7;
  //   PROCESSORS.memory[4]=6;
  //   PROCESSORS.memory[5]=5;
  //   PROCESSORS.memory[6]=4;
  //   PROCESSORS.memory[7]=3;
  //   PROCESSORS.memory[8]=2;
  //   PROCESSORS.memory[9]=1;

  //   PROCESSORS.core1.registers[1]=long(&(PROCESSORS.memory[0]));
  //   PROCESSORS.core1.registers[8]=long(&(PROCESSORS.memory[0]));
  //   cout<<"before bubble sort:"<<endl;
  //   PROCESSORS.print();
  //  cout<<"after bubblesort "<<endl;
   vector<string>bubblesort;
   vector<string>selectionsort;
   vector<int>store;
   interpreter obj;
   
    bubblesort={
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

obj.interpreting(bubblesort,store);

selectionsort={
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
for(int i=0;i<store.size();i++){
  cout<<store[i]<<" ";
}
return 0;
}

class wb{
public:
    bool flag=true;
    void writeback(int a,int b,int c,int d,vector<long> &registers,int &pc,int &stall)
    {
        if(flag==true)
        {
            if(a==1)
            {
                registers[b]=c;
            }
            else if(a==2)
            {
                registers[b]=c;
            }
            else if(a==3)
            {
                registers[b]=c;
            }
            else if(a==4||a==5)
            {
                //continue;
            }
            else if(a==6)
            {
                registers[b]=c;
            }
            else if(a==7)
            {
                registers[b]=d;
            }
            else if(a==9)
            {
                registers[b]=c;
            }
        }
    }
};

class mem{
        public:
    bool flag=true;
    void memoryoperation(int a,int b,long c,long d,vector<long> &registers,int &pc,int &stall)
    {
        if(flag==true)
        {
            if(a==7)
            {
                d=*((int*)c);
            }
            if(a==8)
            {
                *((int*)c)=registers[b];
            }
        }
    }
};

class execute{
    public:
    int a=0,b=0,c=0,d=0;
    bool flag=true;
    void instructionexecute(int ins,int rd, int rs1,int rs2,vector<long> &registers,int &pc,int &stall)
    {
        if(flag==true)
        {
            if(ins==1)
            {
                a=1;
                b=rd;
                c=registers[rs1]+registers[rs2];
            }
            else if(ins==2)
            {
                a=2;
                b=rd;
                c=registers[rs1]-registers[rs2];
            }
            else if(ins==3)
            {
                a=3;
                b=rd;
                c=registers[rs1]+rs2;
            }
            else if(ins==4)
            {
                a=4;
                b=pc;
                if(registers[rd]<registers[z])
                {
                    b=rs2;
                }
            }
            else if(ins==5)
            {
                a=5;
                pc=rs2;
            }
            else if(ins==6)
            {
                a=6;
                b=rd;
                c=rs2;
            }
            else if(ins==7)
            {
                a=7;
                b=rd;
                c=rs2+registers[rs1];
            }
            else if(ins==8)
            {
                a=8;
                b=rd;
                c=rs2+registers[rs1];
            }
            else if(ins==9)
            {
                a=9;
                b=rd;
                c=rs1>>rs2;
            }
            flag=false;
        }
    } 
};

class IF{
  public:
  boolean flag = true;
  int varvalue = 0;

  void instructionFetch(vector<int> &store, int pc){
    if(flag){
      varvalue = store[pc];
      flag = false;
    }
    else{
      stall++;
    }
  }

};

class ID_RF{
    public:
    int rd=0,rs1=0,rs2=0,ins=0;
    bool flag = true;
    void instructiondecode(vector<int> store,int varvalue,int &stall){
      if(flag == true){
        if(varvalue%128 == 1){
            ins = 1;
            rd = (varvalue >> 7) % 32;
            rs1 = (varvalue >> 15) % 32;
            rs2 = (varvalue >> 20) % 32;
        }
        else if(varvalue%128 == 2){
          ins = 2;
          rd = (varvalue >> 7) % 32;
          rs1 = (varvalue >> 15) % 32;
          rs2 = (varvalue >> 10) % 32;
        }
        
        else if(varvalue%128 == 3){
            ins = 3;
            rd = (varvalue >> 7) % 32;
            rs1 = (varvalue >> 15) % 32;
            rs2 = (varvalue >> 20) % 32;
        }
        else if(varvalue%128 == 4){
          ins = 4;
          rs1 = (varvalue >> 7) % 32;
          rs2 = (varvalue >> 12) % 32;
          rd = (varvalue >> 17) % 32;
        }

        else if(varvalue%128 == 5){
          //lw
          ins = 5;
          rs1 = (varvalue >> 15) % 32;
          rd = (varvalue >> 7) % 32;
          rs2 = (varvalue >> 20) % 32;
        }

        else if(varvalue%128 == 6){
          ins = 6;
          rd = (varvalue >> 7) % 32;
          rs2 = (varvalue >> 15) % 32;
          rs1 = (varvalue >> 20)%32;
        }
        else if(varvalue % 128 == 7){
            ins = 7;
            rs1 = 0;
            rs2  = 0;
            rd = (varvalue >> 7) % 32;
        }
        else if(varvalue % 128 == 8){
          ins = 8;
          rd = (varvalue >> 17) % 32;
          rs2 = (varvalue >> 7) % 32;
          rs1 = (varvalue >> 12)%32;
        }

        else if(varvalue % 128 == 9){
          ins = 9;
        rd = (varvalue >> 7) % 32;
        rs1 = (varvalue >> 15) % 32;
         rs2 = (varvalue >> 20) % 32;
         
        }

        else if(varvalue % 128 == 10){
      start=start+sd*pow(2,7)+st*pow(2,12);
        ins = 10;
        rd = (varvalue >> 7) % 32;
        rs1 = 0;
        rs2 = (varvalue >> 12) % 32;
        }

        flag = false;
      }

      if(flag == false){
        stall++;
      }
    }
};