#include <CPUTemperature.h>

CPUTemperature::CPUTemperature(const std::string &_cpu_temp_path) : cpu_temp_path_(_cpu_temp_path)
{
    last_temperature_ = getTemperature();
}

std::ostream &operator<<(std::ostream &out, const CPUTemperature &cput)
{
    out << "CPU Temperature: ";
    out << cput.last_temperature_;
    out << std::endl;
    return out;
}

double CPUTemperature::getTemperature()
{
    std::string temp_string;
    if (openFile(cpu_temp_path_))
    {
        if (getline(temperature_file_, temp_string)){
            last_temperature_ =  atof(temp_string.c_str()) / scale_factor_;
            return last_temperature_;
        }
        temperature_file_.close();
    }

    return -1;
}
bool CPUTemperature::openFile(const std::string &_file)
{
    temperature_file_ =  std::ifstream(_file);
    if (temperature_file_.is_open())
        return true;

    return false;
}
