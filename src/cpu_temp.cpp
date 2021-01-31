#include "CPUTemperature.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    // int n = 0;
    auto cpu_t = CPUTemperature("/sys/class/thermal/thermal_zone0/temp");

    while (true)
    {
        std::cout << cpu_t.getTemperature() << std::endl;
        /*std::cout << "Iteration: " << ++n << std::endl;
        std::cout << CPUTemperature("/sys/class/hwmon/hwmon1/device/temp");
        std::cout << CPUTemperature("/sys/class/hwmon/hwmon3/device/temp");
        std::cout << CPUTemperature("/sys/class/hwmon/hwmon4/device/temp");
        std::cout << CPUTemperature("/sys/class/thermal/thermal_zone0/temp");
        std::cout << CPUTemperature("/sys/class/thermal/thermal_zone1/temp");
        std::cout << CPUTemperature("/sys/class/thermal/thermal_zone2/temp");
        std::cout << CPUTemperature("/sys/class/thermal/thermal_zone3/temp");*/
        usleep(1e6);
    }

    return 0;
}