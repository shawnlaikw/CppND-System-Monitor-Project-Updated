#include "processor.h"
#include <vector>
#include <string>
#include <istream>
#include <iostream>
#include <fstream>
#include "linux_parser.h"
#include <regex>
#include <bits/stdc++.h> 

using std::string;
using namespace LinuxParser;
using std::vector;
using std::cout;
using std::endl;
using namespace LinuxParser;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    get_cpu_data();//retrieve data from cpu 
    float sum=0;
    for(unsigned int i=1;i<cpu_buffer.size();i++)
    sum=sum+std::stof(cpu_buffer[i]);
    float cpu_perc=1-(std::stof(cpu_buffer[4])/sum);

     return cpu_perc; 
}

void Processor::get_cpu_data()
{
     string os;
  string line;
  vector<string > perc;
  int max_length=11;
  cpu_buffer.clear();
  std::ifstream stream(kProcDirectory + kStatFilename);
  int counter=0;
  if (stream.is_open()) {
//cout<<"file opened"<<endl;
std::getline(stream, line) ;
std::istringstream linestream(line)  ; 
while(counter<max_length)
    {
        //std::getline(stream, line);
        linestream >> os;
        //cout<<os<<" ";
        cpu_buffer.push_back(os);
        counter++;
    }
  }
//cout<<"end of test"<<endl;

    
}