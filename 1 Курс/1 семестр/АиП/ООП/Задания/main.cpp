#include <iostream>

class Pet
{
public:
    // Два чисто виртуальных метода
    virtual std::string name() = 0;
    virtual std::string voice() = 0;
    virtual std::string get_type() {return "Pet";}
    virtual std::size_t weight() {return 0;}

    friend std::ostream &operator<<(std::ostream &stream, Pet &pet)
    {
        std::cout << pet.get_type() << " " << pet.name() << " " << pet.voice() << " " << pet.weight() << std::endl;
        return stream;
    }
    virtual ~Pet(){}
};

class Cat : public Pet
{
public:
    // Конструктор
    Cat(std::string name, std::string voice, int weight) : name_(name),
                                                           voice_(voice),
                                                           weight_(weight) {}

    // Имя
    std::string name() override
    {
        return name_;
    }
    // Голос
    std::string voice() override
    {
        return voice_;
    }
    // Вес
    std::size_t weight() override
    {
        return weight_;
    }
    // Тип (если нужен)
    std::string get_type() override
    {
        return type;
    }

private:
    std::string name_, voice_;
    std::string type = "Cat";
    std::size_t weight_;
};

// Скопировали кошку и назвали собакой, хоть по логике они одинаковы
class Dog : public Pet
{
public:
    // Конструктор
    Dog(std::string name, std::string voice, int weight, std::string character = "pass") : name_(name),
                                                                                           voice_(voice),
                                                                                           weight_(weight),
                                                                                           character_(character) {}

    // Имя
    std::string name() override
    {
        return name_;
    }
    // Голос
    std::string voice() override
    {
        return voice_;
    }
    // Вес
    std::size_t weight() override
    {
        return weight_;
    }
    // Тип (если нужен)
    std::string get_type() override
    {
        return type;
    }

private:
    std::string name_, voice_;
    std::string type = "Dog";
    std::size_t weight_;
    std::string character_;
};

// Задание
class FamilyPets
{
public:
    FamilyPets() {}

    void operator+(Pet *pet)
    {
        if (curretnt_lenght < max_capacity)
        {
            family[curretnt_lenght] = pet;
            curretnt_lenght++;
        }
        else
        {
            std::cerr << "ERROR: Maximum capacity reached" << std::endl;
        }
    }

    void voice()
    {
        for (std::size_t i = 0; i < curretnt_lenght; i++)
        {
            std::cout << family[i]->name() << ": " << family[i]->voice() << std::endl;
        }
    }

    void name()
    {
        for (std::size_t i = 0; i < curretnt_lenght; i++)
        {
            std::cout << family[i]->name() << std::endl;
        }
    }

    std::size_t getNumberRepetitionsName(std::string name)
    {
        std::size_t count = 0;
        for (std::size_t i = 0; i < curretnt_lenght; i++)
        {
            if (name == family[i]->name())
            {
                count++;
            }
        }
        return count;
    }
    std::string findTheEasiest()
    {
        std::size_t ind = 0;
        std::size_t easy_weight = family[ind]->weight();
        for (std::size_t i = 0; i < curretnt_lenght; i++)
        {
            if (easy_weight > family[i]->weight())
            {
                ind = i;
            }
        }
        return family[ind]->name();
    }

    friend std::ostream &operator<<(std::ostream &stream, FamilyPets &fml)
    {
        for (std::size_t i = 0; i < fml.curretnt_lenght; i++)
        {
            stream << *fml.family[i];
        }
        return stream;
    }

    // Чистим память
    ~FamilyPets()
    {
        for (std::size_t i = 0; i < curretnt_lenght; i++)
        {
            delete family[i]; // Освобождаем память
        }
    }

private:
    std::size_t max_capacity{10};
    std::size_t curretnt_lenght{0};
    Pet *family[10];
};

int main()
{
    int count_pet;
    std::cin >> count_pet;
    FamilyPets family;
    if (count_pet > 7 || count_pet < 1)
    {
        std::cerr << "ERROR: Incorrect number of pets specified";
        return 1;
    }
    int counter = 0;
    while (true)
    {
        std::string type;
        std::cin >> type;
        if (type == "<END>")
            break;
        counter++;
        if (counter > count_pet)
        {
            std::cerr << "ERROR: The number of pets exceeds the maximum";
            return 1;
        }
        std::string name, voice;
        std::size_t weight;
        std::cin >> name >> voice >> weight; // Считываем данные для питомца

        if (type == "Cat")
        {
            Cat *cat = new Cat(name, voice, weight);
            family + cat;
        }
        else if (type == "Dog")
        {
            Dog *dog = new Dog(name, voice, weight);
            family + dog;
        }
    }
    family.name();
    family.voice();
    std::string name;
    std::cin >> name;
    std::cout << name << ": " << family.getNumberRepetitionsName(name) << std::endl;
    std::cout << family.findTheEasiest() << std::endl;
    std::cout << family;
}