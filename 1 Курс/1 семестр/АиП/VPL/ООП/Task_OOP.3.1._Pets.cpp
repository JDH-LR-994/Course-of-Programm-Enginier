#include <iostream>
#include <string>
#include <sstream>
#include <limits>


class Animal {
protected:
    const std::string type_;
    const std::string klichka_;
    const std::string voice_;
    const double weight_;
public:
    Animal(const std::string& type, const std::string& klichka, const std::string& voice, const double& weight)
        : type_(type), klichka_(klichka), voice_(voice), weight_(weight) {}
    std::string GetName() {
        return this->klichka_;
    }
    std::string GetVoice() {
        return this->voice_;
    }
    double GetWeight() {
        return this->weight_;
    }
    std::string GetType() {
        return this->type_;
    }
};

class Dog : public Animal {
public:
    Dog(const std::string& klichka, const std::string& voice, const double& weight)
        : Animal("Dog", klichka, voice, weight) {}
};

class Cat : public Animal {
public:
    Cat(const std::string& klichka, const std::string& voice, const double& weight)
        : Animal("Cat", klichka, voice, weight) {}
};

class FamilyPets {
private:
    const int maxNPets_;
    Animal** pets;
public:
    FamilyPets(const int& maxNPets) : maxNPets_(maxNPets) {
        pets = new Animal * [maxNPets];
        for (int i = 0; i < maxNPets_; ++i) {
            pets[i] = nullptr;
        }
    }

    ~FamilyPets() {
        for (int i = 0; i < maxNPets_; ++i) {
            delete pets[i];
        }
        delete[] pets;
    }

    void addPet(Animal* pet) {
        for (int i = 0; i < maxNPets_; ++i) {
            if (pets[i] == nullptr) {
                pets[i] = pet;
                break;
            }
        }
    }
    void Names() {
        for (int i = 0; i < maxNPets_; ++i) {
            std::cout << ((*pets[i]).GetName()) << std::endl;
        }
    }
    void Voice() {
        for (int i = 0; i < maxNPets_; ++i) {
            std::cout << ((*pets[i]).GetVoice()) << std::endl;
        }
    }
    int getNumberRepetitionsName(std::string& name) {
        int count = 0;
        for (int i = 0; i < maxNPets_; ++i) {
            if (((*pets[i]).GetName()) == name) {
                count++;
            }
        }
        return count;
    }
    std::string findTheEasiest() {
        double easiest = std::numeric_limits<double>::max();
        std::string easiestName;
        for (int i = 0; i < maxNPets_; ++i) {
            if (((*pets[i]).GetWeight()) < easiest) {
                easiest = (*pets[i]).GetWeight();
                easiestName = (*pets[i]).GetName();
            }
        }
        return easiestName;
    }
    friend std::ostream& operator<<(std::ostream& os, const FamilyPets& family) {
        for (int i = 0; i < family.maxNPets_; ++i) {
            if (family.pets[i] != nullptr) {
                os << "Type: " << family.pets[i]->GetType() << ", "
                    << "Name: " << family.pets[i]->GetName() << ", "
                    << "Voice: " << family.pets[i]->GetVoice() << ", "
                    << "Weight: " << family.pets[i]->GetWeight() << std::endl;
            }
        }
        return os;
    }
};

int main() {
    int maxNPets;
    std::cin >> maxNPets;
    if ((maxNPets < 0) || (maxNPets > 7)) {
        std::cout << "ERROR: Incorrect number of pets specified";
        exit(1);
    }

    FamilyPets family(maxNPets);

    std::string line;
    int nSource = 0;
    while (std::getline(std::cin, line)) {
        if (line == "<END>") {
            break;
        }
        if (nSource >= maxNPets) {
            std::cout << "ERROR: The number of pets exceeds the maximum" << std::endl;
            exit(1);
        }
        std::istringstream iss(line);
        std::string type;
        iss >> type;
        if (type == "Dog" || type == "Cat") {
            std::string klichka, voice;
            double weight;
            if (iss >> klichka >> voice >> weight) {
                if (type == "Dog") {
                    Dog* dog = new Dog(klichka, voice, weight);
                    family.addPet(dog);
                }
                else if (type == "Cat") {
                    Cat* cat = new Cat(klichka, voice, weight);
                    family.addPet(cat);
                }
                nSource++;
            }
            else {
                std::cout << "ERROR: Invalid pet data for type: " << type << std::endl;
                exit(1);
            }
        }
        else if (type.empty()) {
            continue;
        }
        else {
            std::cout << "ERROR: Unknown pet type: " << type << std::endl;
            exit(1);
        }
    }
    family.Names();
    family.Voice();

    std::string name;
    std::cin >> name;

    std::cout << family.getNumberRepetitionsName(name) << std::endl;
    std::cout << family.findTheEasiest() << std::endl;

    std::cout << family;
    return 0;
}