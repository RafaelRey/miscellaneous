#ifndef __CPUTEMPERATURE_H_
#define __CPUTEMPERATURE_H_

#include <iostream>
#include <fstream>

class CPUTemperature
{

public:

    CPUTemperature(const std::string &_cpu_temp_path);
    friend std::ostream &operator<<(std::ostream &out, const CPUTemperature &cput);
private:

    double getTemperature();
    bool openFile(const std::string &_file);
    
    std::ifstream temperature_file_;
    double last_temperature_ = -1;
    double scale_factor_ = 1000;
};

#endif