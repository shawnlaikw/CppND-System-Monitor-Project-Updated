#include <unistd.h>
#include <cctype>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"
#include <bits/stdc++.h> 

using std::string;
using std::to_string;
using std::vector;
using std::cout;
using std::endl;
using std::stof;
using namespace LinuxParser;

// TODO: Return this process's ID
int Process::Pid() { 
    return id; 
    }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    vector<string> buffer1 =get_proc_buffer();
//-------------compute cpu-------------//
    if(buffer1.size()>14)
    {    
    float total_time=stof(buffer1[13])+stof(buffer1[14])+stof(buffer1[15])+stof(buffer1[16]);
    float sys_uptime=cpu_UpTime();
    float hertz =(float)sysconf(_SC_CLK_TCK );
    float second=sys_uptime-(stof(buffer1[21])/hertz);
    cpu_usage = (total_time / hertz) / second;
    return cpu_usage; 
    }
    else
    return 0;
}

void Process::update_id(int id1)
{
    id=id1;

}


// TODO: Return the command that generated this process
string Process::Command() { 
 string os;
  string line;
  vector<string > buffer1;
  std::ifstream stream(kProcDirectory +to_string(id)+ kCmdlineFilename);
  if (stream.is_open()) 
  {   
    //cout<<"file opened"<<endl;
    std::getline(stream, line) ;//get total mem first
    std::istringstream linestream(line)  ; 
    return line;
    }
    return "";
}


// TODO: Return this process's memory utilization
string Process::Ram() { 


    return proc_ram; 
    }

// TODO: Return the user (name) that generated this process
string Process::User()
 { 
    return usr;
     }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
vector<string> buffer1 =get_proc_buffer();
    //cout<<buffer1[21]<<endl;
    long int output =0;
    if(buffer1.size()>20)
    {
    float hertz =(float)sysconf(_SC_CLK_TCK );
    float starttime=stof(buffer1[21])/hertz;
    output=cpu_UpTime()-(int)starttime;
    }
    //cout<<"cpu is "<<cpu_UpTime()<<endl;
    //cout<<"output is "<<output<<endl;
    return output;//-stol(buffer1[21]) ;
    }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    float cpu1 =this->cpu_usage;
    float cpu2 =a.cpu_usage;
    if(cpu1<cpu2)
        return true;
    else
        return false;
}

vector<string> Process::get_proc_buffer()//from stat
{
 string os;
  string line;
  vector<string > buffer1;
  //int max_length=11;
  std::ifstream stream(kProcDirectory +to_string(id)+ kStatFilename);
  if (stream.is_open()) 
  {
    //
  int counter=0;    
    //cout<<"file opened"<<endl;
    std::getline(stream, line) ;//get total mem first
    std::istringstream linestream(line)  ; 
    while(counter<22)
        {
            //std::getline(stream, line);
            linestream >> os;
            //cout<<os<<" ";
            buffer1.push_back(os);
            counter++;
        }
        return buffer1;
    }
    return buffer1;
}

float Process::get_cpu_usage()
{
return cpu_usage;
}

void Process::get_status()//from stat of process
{
 string os;
  string line;
  vector<string > buffer1;
  vector<string > buffer2;
  int length=0;
  std::ifstream stream(kProcDirectory +to_string(id)+ kStatusFilename);
  if (stream.is_open()) 
  {
    //
  int counter=0;    
    //cout<<"file opened"<<endl;
    while(counter<9)
    {
        std::getline(stream, line) ;//get total mem first
        counter++;
    }
    std::istringstream linestream(line)  ; 

    while(length<2)
    {
        //std::getline(stream, line);
        linestream >> os;
        //cout<<os<<" ";
        buffer1.push_back(os);
        length++;
    }
    counter=0; 
    //cout<<endl;
    while(counter<9)
    {
        std::getline(stream, line) ;//get total mem first
        counter++;
    }
    std::istringstream linestream2(line)  ;     
    length=0;
        while(length<2)

    {
        //std::getline(stream, line);
        linestream2 >> os;
        //cout<<os<<" ";
        buffer2.push_back(os);
        length++;
    }
    proc_ram="0";
    //extract  ram
    if(buffer2.size()!=0)
    {
        if(is_number( buffer2[1])&&buffer2[1].size()>4&&buffer2[1].size()<9)
        {
            buffer2[1].resize(buffer2[1].size()-3);
        proc_ram=buffer2[1];
        }
    }
    /*
    if(is_number( buffer2[1]))
    proc_ram=to_string(stoi(buffer2[1]));
    else
    {
        cout<<"size is zero"<<endl;
    }
    */
    //extract name
    usr=get_name(buffer1[1]);
    }
}

string Process::get_name(string num)//x:x format
{

    string os;
  string target = "x:"+num;
  vector<string> buffer1;
  string line;    
  int length=0;
  int counter=0;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) 
  {
      //cout<<"file opened"<<endl;  
         
         std::istringstream ss;          
  while(getline(stream, line))
    {
        std::replace(line.begin(), line.end(), ':', ' ');
        ss.clear();
        ss.str(line);
        //cout<<line<<endl;
        length=0;
        buffer1.clear();
        counter++;
        while(length<3)
        {
        ss >> os;
        buffer1.push_back(os);
        //cout<<buffer1[length]<<" "<<endl;;
        length++;
        }
   
        //cout<<endl;
        if(buffer1[2] == num)
        {
        //cout<<buffer1[0]<<endl;            
            return buffer1[0];       
        }
    }     
  }
    return "";
}

bool Process::is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}