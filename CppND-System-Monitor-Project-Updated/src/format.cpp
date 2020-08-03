#include <string>
#include <stdlib.h>
#include "format.h"

using std::string;
using std::to_string;
// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
     int hour=seconds/3600;
     int min=(seconds-(hour*3600))/60;
     int sec=seconds-((hour*3600)+(min*60));
     string hour_s=to_string(hour);//.append(2-hour_s.length(),'0');
     string min_s=to_string(min);//.append(2-min_s.length(),'0');
     string sec_s=to_string(sec);//.append(2-sec_s.length(),'0');
     //padding zeros
     hour_s.insert(hour_s.begin(),2-hour_s.length(),'0');
    min_s.insert(min_s.begin(),2-min_s.length(),'0');
    sec_s.insert(sec_s.begin(),2-sec_s.length(),'0');
     string combined=hour_s+":"+min_s+":"+sec_s;
     return combined; 
     
     }