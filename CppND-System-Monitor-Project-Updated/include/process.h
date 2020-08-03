#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
using std::string;
using std::vector;
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/

class Process {
 public:
    
    int Pid();                               // TODO: See src/process.cpp
    string User();                      // TODO: See src/process.cpp
    string Command();                   // TODO: See src/process.cpp
    float CpuUtilization();// TODO: See src/process.cpp

    void update_id(int id1);
    string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const& a) const;  // TODO: See src/process.cpp
    float get_cpu_usage();
    void get_status();//from stat
    string get_name(string num);
    bool is_number(const std::string& s);
  // TODO: Declare any necessary private members
 private:
    int id;
    float cpu_usage;
    long int proc_starttime;
    vector<string>  get_proc_buffer();
    string proc_ram;
    string usr;//user

};

#endif