#include <iostream>
#include <cstring>
#include <limits>
#include <string>

class Pet {
public:
    virtual std::string name() = 0;
    virtual std::string voice() = 0;
    virtual double weight() = 0;
    virtual std::string character() { return ""; }
    virtual ~Pet() = default;

protected:
    std::string name_, voice_;
    double weight_;
};

class Cat : public Pet {
public:
    Cat() = default;
    Cat(std::string name, std::string voice, double weight) {
        this->name_ = name;
        this->voice_ = voice;
        this->weight_ = weight;
    }
    std::string name() override { return name_; }
    std::string voice() override { return voice_; }
    double weight() override { return weight_; }
};

class Dog : public Pet {
public:
    Dog(std::string name, std::string voice, double weight, std::string character = " ") {
        this->name_ = name;
        this->voice_ = voice;
        this->weight_ = weight;
        this->character_ = character;
    }
    std::string name() override { return name_; }
    std::string voice() override { return voice_; }
    double weight() override { return weight_; }
    std::string character() override { return character_; }

private:
    std::string character_;
};

class FamilyPets {
public:
    FamilyPets() = default;
    void voice() {
        for (int i = 0; i < current_length; i++) {
            std::cout << family[i]->voice() << std::endl;
        }
    }
    void names() {
        for (int i = 0; i < current_length; i++) {
            std::cout << family[i]->name() << std::endl;
        }
    }
    int getNumberRepetitionsName(std::string str) {
        int counter = 0;
        for (int i = 0; i < current_length; i++) {
            if (family[i]->name() == str) {
                counter++;
            }
        }
        return counter;
    }
    FamilyPets& operator+=(Pet* pet) {
        if (current_length < max_capacity) {
            family[current_length++] = pet;
        }
        return *this;
    }
    std::string findTheEasiest() {
        if (current_length == 0) return "";
        double min_weight = std::numeric_limits<double>::max();
        std::size_t ind = 0;
        for (int i = 0; i < current_length; i++) {
            if (family[i]->weight() < min_weight) {
                ind = i;
                min_weight = family[i]->weight();
            }
        }
        return family[ind]->name();
    }
    friend std::ostream& operator<<(std::ostream& stream, FamilyPets& famPet) {
        for (int i = 0; i < famPet.current_length; i++) {
            stream << "Name: " << famPet.family[i]->name() << ", Voice: " << famPet.family[i]->voice() << ", Weight: " << famPet.family[i]->weight();
            if (dynamic_cast<Dog*>(famPet.family[i])) {
                stream << ", Character: " << famPet.family[i]->character();
            }
            stream << std::endl;
        }
        return stream;
    }
    ~FamilyPets() {
        for (int i = 0; i < current_length; i++) {
            delete family[i];
        }
    }

private:
    std::size_t max_capacity{10};
    std::size_t current_length{0};
    Pet* family[10];
};

int main() {
    int maxNPets;
    std::cout << "Enter the maximum number of pets: ";
    std::cin >> maxNPets;
    if (maxNPets < 0 || maxNPets > 7) {
        std::cerr << "ERROR: Incorrect number of pets specified" << std::endl;
        return 1;
    }

    FamilyPets pets;
    int inner_counter = 0;
    std::string input{"\0"};
    std::string type, name, voice, character;
    double weight;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        inner_counter++;
        if (inner_counter > maxNPets) {
            std::cerr << "ERROR: The number of pets exceeds the maximum" << std::endl;
            return 1;
        }

        std::getline(std::cin, type);
        if (type == "END") break;

        std::getline(std::cin, name);
        std::getline(std::cin, voice);
        std::cin >> weight;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (type == "Cat" || type == "cat") {
            pets += new Cat{name, voice, weight};
        } else if (type == "Dog" || type == "dog") {
            std::getline(std::cin, character);
            pets += new Dog{name, voice, weight, character};
        }
    }

    std::cout << "Names of all pets:" << std::endl;
    pets.names();

    std::cout << "Voices of all pets:" << std::endl;
    pets.voice();

    std::cout << "Enter the name to search: ";
    std::getline(std::cin, input);
    std::cout << "Number of pets with name " << input << ": " << pets.getNumberRepetitionsName(input) << std::endl;

    std::cout << "The easiest pet: " << pets.findTheEasiest() << std::endl;

    std::cout << "Information about all pets:" << std::endl;
    std::cout << pets;

    return 0;
}