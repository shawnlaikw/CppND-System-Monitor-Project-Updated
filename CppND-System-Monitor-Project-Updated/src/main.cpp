#include "ncurses_display.h"
#include "system.h"
#include "iostream"
#include "linux_parser.h"

using std::string ;

using namespace LinuxParser;
using std::cout;
using std::endl;

int main() {
  System system;  
  Process p1;
  //p1.update_id(1010);
  //float msg =
  //system.update_proc();
  //p1.get_status();
  //p1.get_name("10");

  //cout<<msg<<endl;
  NCursesDisplay::Display(system,10);
}