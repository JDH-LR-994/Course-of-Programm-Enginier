#include <iostream>
#include <string>

const double CPU_RATING = 0.4;
const double RAM_RATING = 0.3;
const double SSD_RATING = 0.2;
const double GPU_RATING = 0.1;

//создаём класс
class Computer
{
public:
    //конструктор
    Computer() = default;
    Computer(const std::string name, unsigned int cpu, unsigned int ram, unsigned int ssd, unsigned int gpu) :
        name_(name), cpu_(cpu), ram_(ram), ssd_(ssd), gpu_(gpu)
    {
    }

    //метод класса для рассчёта рейтинга
    double rating()
    {
        return (cpu_ * CPU_RATING + gpu_ * GPU_RATING + ram_ * RAM_RATING + ssd_ * SSD_RATING);
    }

    //сетаперы
    void SetSPU(unsigned int cpu) { cpu_ = cpu; }
    void SetRAM(unsigned int ram) { ram_ = ram; }
    void SetSSD(unsigned int ssd) { ssd_ = ssd; }
    void SetGPU(unsigned int gpu) { gpu_ = gpu; }

private:
    //поля класса определём в привате
    std::string name_;
    unsigned int cpu_; // core
    unsigned int ram_; // gb
    unsigned int ssd_; // gb
    unsigned int gpu_; // gb
};

int main()
{
    std::cout << "opp_simple_class!\n";

    //объекты класса
    Computer hp_elite{ "hp_elite", 4, 16, 512, 2 };
    Computer yarik_comp{ "yarik_comp", 8, 64, 2048, 8 };

    //находим рейтинг компьютеров
    double r_hp_elite = hp_elite.rating();
    double r_yarik_comp = yarik_comp.rating();


    std::size_t s = sizeof(Computer); //вы видим что метод класса не хранится к классе
    std::size_t s_string = sizeof(std::string);

    hp_elite.SetRAM(100);
}
