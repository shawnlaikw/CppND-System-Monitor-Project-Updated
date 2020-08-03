#include <unistd.h>
#include <cctype>
#include <cstddef>
#include <set>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include <bits/stdc++.h> 


using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using namespace LinuxParser;

// Return the system's CPU
Processor& System::Cpu() { 
   
   
    return cpu_; 
    
    }

// Return a container composed of the system's processes
vector<Process>& System::Processes() {


//process_display.clear();
  update_proc();

     return process_display; 
     }

// Return the system's kernel identifier (string)
std::string System::Kernel() { 
  string line;
  string key;
  string n1,n2,n3;
  std::ifstream filestream(kProcDirectory+kVersionFilename);
  if (filestream.is_open()) {

    while (std::getline(filestream, line)) 
    {
      std::istringstream linestream(line);
      linestream >> n1 >> n2>>n3;
      return n3;

    }
  }
  return "";
}
  


// Return the system's memory utilization
float System::MemoryUtilization() 
{ 
       string os;
  string line;
  vector<string > buffer1;
  vector<string > buffer2;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) 
  {
    //
  int counter=0;    
    //cout<<"file opened"<<endl;
    std::getline(stream, line) ;//get total mem first
    std::istringstream linestream(line)  ; 
    while(counter<3)
        {
            //std::getline(stream, line);
            linestream >> os;
            //cout<<os<<" ";
            buffer1.push_back(os);
            counter++;
        }

    std::getline(stream, line) ;//get avail mem first
     std::getline(stream, line) ;//get avail mem first   
    std::istringstream linestream2(line);

    counter=0;
    while(counter<3)
        {
            //std::getline(stream, line);
            linestream2 >> os;
            //cout<<os<<" ";
            buffer2.push_back(os);
            counter++;
        }
        
  }

 float perc=1-(std::stof(buffer2[1])/std::stof(buffer1[1]));



   // cout<<"end of test"<<endl;

    return perc;
}

//Return the operating system name
std::string System::OperatingSystem() { 
      string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// Return the number of processes actively running on the system
int System::RunningProcesses() { 
  string os;
  string line;
  vector<string > buffer1;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) 
  {
    //
  int counter=0;    
   // cout<<"file opened"<<endl;
    while(counter<14)
        {
        std::getline(stream, line);
        counter++;
        }
    std::istringstream linestream(line)  ; 
    std::getline(stream, line) ;
  int length=0;
    while(length<2)
        {
            //std::getline(stream, line);
            linestream >> os;
            //cout<<os<<" ";
            buffer1.push_back(os);
            length++;
        }
        
  }
   // cout<<"end of test"<<endl;

    if (std::all_of(buffer1[1].begin(), buffer1[1].end(), isdigit)&&buffer1[1]!="")
    return stoi(buffer1[1]);
    else
    return 0;

    
     }

// Return the total number of processes on the system
int System::TotalProcesses() {
    string os;
  string line;
  vector<string > buffer1;

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) 
  {
    //
  int counter=0;    
    //cout<<"file opened"<<endl;
    while(counter<13)
        {
        std::getline(stream, line);
        counter++;
        }
    std::istringstream linestream(line)  ; 
    std::getline(stream, line) ;
  int length=0;
    while(length<2)
        {
            //std::getline(stream, line);
            linestream >> os;
            //cout<<os<<" ";
            buffer1.push_back(os);
            length++;
        }
        
  }
    //cout<<"end of test"<<endl;
    //vector<int> all_id =Pids();
    //return update_proc();//
    //if(buffer1[1]!="")
    //return stoi(buffer1[1]);
    //else
    if (std::all_of(buffer1[1].begin(), buffer1[1].end(), isdigit)&&buffer1[1]!="")
    return stoi(buffer1[1]);
    else
    return 0;
    
}

// Return the number of seconds since the system started running
long int System::UpTime() { 
       string os;
  string line;
  vector<string > buffer1;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) 
  {
    //  
    //cout<<"file opened"<<endl;
     std::getline(stream, line) ;   
    std::istringstream linestream(line)  ; 
  int length=0;
    while(length<2)
        {
            //std::getline(stream, line);
            linestream >> os;
            //cout<<os<<" ";
            buffer1.push_back(os);
            length++;
        }
        
  }
    //cout<<"end of test"<<endl;
    if (buffer1[0]!="")
    return std::stol(buffer1[0]);
    else return 0;
 }

 int System::update_proc()
 {
   vector<int> all_id =Pids();

   if(all_id.size()<10)
   {
     cout<<"all_id size "<<all_id.size();
   return 0;
   }
   processes_.clear();
   process_display.clear();
   processes_.resize(all_id.size());
   for(unsigned int i=0;i<processes_.size();i++)
    {processes_[i].update_id(all_id[i]);
    //compute proc ultilisation
    processes_[i].CpuUtilization();
    }
    //sort and transfer top 10 to process_display
    int display_size=0;
    if(processes_.size()>10)
    display_size=10;
    else
    {
      display_size=processes_.size();
    }
    

    for(int j=0;j<display_size;j++)
    {
          int heaviest_idx=0;//
      for(unsigned int i=0;i<processes_.size();i++)
      {
          if(processes_[heaviest_idx]<processes_[i])
          heaviest_idx=i;
      }
      processes_[heaviest_idx].get_status();          
      process_display.push_back(processes_[heaviest_idx]);
      //cout<<processes_[heaviest_idx].Pid()<<" cpu usage "<<processes_[heaviest_idx].get_cpu_usage()<<" "<<processes_[heaviest_idx].Command()<<endl;
      //cout<<processes_[heaviest_idx].User()<<" ram usage "<<processes_[heaviest_idx].Ram()<<" Usr "<<processes_[heaviest_idx].User()<<endl;
      processes_.erase(processes_.begin()+heaviest_idx);
    }
  return all_id.size();
       
 }