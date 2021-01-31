#include <CPUTemperature.h>


CPUTemperature::CPUTemperature(const std::string &_cpu_temp_path)
{
    if (openFile(_cpu_temp_path))
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
    if (getline(temperature_file_, temp_string))
        return atof(temp_string.c_str()) / scale_factor_;

    return -1;
}
bool CPUTemperature::openFile(const std::string &_file)
{
    temperature_file_.open(_file);
    if (temperature_file_.is_open())
        return true;

    return false;
}

