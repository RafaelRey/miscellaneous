#include "CPUTemperature.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    int n = 0;
    while (true)
    {
        std::cout << "Iteration: " << ++n << std::endl;
        std::cout << CPUTemperature("/sys/class/hwmon/hwmon1/device/temp");
        std::cout << CPUTemperature("/sys/class/hwmon/hwmon3/device/temp");
        std::cout << CPUTemperature("/sys/class/hwmon/hwmon4/device/temp");
        usleep(1e6);
    }

    return 0;
}