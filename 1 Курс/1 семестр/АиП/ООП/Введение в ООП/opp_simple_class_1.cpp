#include <iostream>
#include <string>

const double CPU_RATING = 0.4;
const double RAM_RATING = 0.3;
const double SSD_RATING = 0.2;
const double GPU_RATING = 0.1;

struct Computer
{
    //функция для рассёта метода внутри стурктуры
    double rating()
    {
        return (cpu_ * CPU_RATING + gpu_ * GPU_RATING + ram_ * RAM_RATING + ssd_ * SSD_RATING);
    }
    std::string name_;
    unsigned int cpu_; // core
    unsigned int ram_; // gb
    unsigned int ssd_; // gb
    unsigned int gpu_; // gb
};

int main()
{
    std::cout << "opp_simple_class!\n";

    Computer hp_elite{ "hp_elite", 4, 16, 512, 2 };
    Computer yarik_comp{ "yarik_comp", 8, 64, 2048, 8 };

    double r_hp_elite = hp_elite.rating();
    double r_yarik_comp = yarik_comp.rating();

    std::size_t s = sizeof(Computer);
    std::size_t s_string = sizeof(std::string);

}
