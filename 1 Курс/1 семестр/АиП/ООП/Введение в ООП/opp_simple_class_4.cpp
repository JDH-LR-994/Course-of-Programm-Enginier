#include <iostream>
#include <string>
#include <fstream>

const double CPU_RATING = 0.4;
const double RAM_RATING = 0.3;
const double SSD_RATING = 0.2;
const double GPU_RATING = 0.1;

class Computer
{
public:
    //конструктор
    Computer() = default;
    Computer(const std::string name, unsigned int cpu, unsigned int ram, unsigned int ssd, unsigned int gpu) :
        name_(name), cpu_(cpu), ram_(ram), ssd_(ssd), gpu_(gpu)
    {
    }

    //метод класса для определения рейтинга
    double rating()
    {
        return (cpu_ * CPU_RATING + gpu_ * GPU_RATING + ram_ * RAM_RATING + ssd_ * SSD_RATING);
    }

    //сетаперы
    void SetSPU(unsigned int cpu) { cpu_ = cpu; }
    void SetRAM(unsigned int ram) { ram_ = ram; }
    void SetSSD(unsigned int ssd) { ssd_ = ssd; }
    void SetGPU(unsigned int gpu) { gpu_ = gpu; }

    //переопределение оператора вывода
    friend std::ostream& operator << (std::ostream& out, const Computer& comp) {
        out << "name: " << comp.name_ << "\n";
        out << "cpu: " << comp.cpu_ << "\n";
        out << "ram: " << comp.ram_ << "\n";
        out << "ssd: " << comp.ssd_ << "\n";
        out << "gpu: " << comp.gpu_ << "\n";
        return out;
    }
    //переопределение оператора ввода
    friend std::istream& operator >> (std::istream& in, Computer& comp) {
        in >> comp.name_;
        in >> comp.cpu_;
        in >> comp.ram_;
        in >> comp.ram_;
        in >> comp.ram_;
        return in;
    }

private:
    //поля класса
    std::string name_;
    unsigned int cpu_; // core
    unsigned int ram_; // gb
    unsigned int ssd_; // gb
    unsigned int gpu_; // gb
};

int main()
{
    std::cout << "opp_simple_class!\n";

    //экземпляры класса

    //определяется в main
    Computer hp_elite{ "hp_elite", 4, 16, 512, 2 };
    Computer yarik_comp{ "yarik_comp", 8, 64, 2048, 8 };

    //определяется в системной памяти (heap), эту память потом нужно освободить
    Computer* mac_mini = new Computer{ "mac_mini", 8, 16, 512, 4 };

    double r_hp_elite = hp_elite.rating();
    double r_yarik_comp = yarik_comp.rating();
    double t_mac_mini = mac_mini->rating();

    std::size_t s = sizeof(Computer);
    std::size_t s_string = sizeof(std::string);

    //ввыдоим объект класса в файл
    std::ofstream output("output.txt");
    output << hp_elite;
    output.close();

    Computer my_comp;

    //вводим значения полей класса из файла
    std::ifstream input("input.txt");
    input >> my_comp;
    input.close();

    //освобождение памяти из heap
    delete mac_mini;

    return 0;
}
