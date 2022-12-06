#include <iostream>
#include <string>
#include <memory>

/* Base class */
class Uncopyable
{
    protected:
        Uncopyable() {}
        ~Uncopyable() {}

    private:
        Uncopyable(const Uncopyable&);
        Uncopyable& operator=(const Uncopyable&);
};

/* Custom class Car which inherits the base class */
class Car 
{
    public:
        /* Default Constructor */
        Car() : theName("inexisting_car"), theColor("inexisting_color"), numberOfSeats(0), isCarLocked(false) {}

        /* Custom Constructor */
        Car(const std::string& name, const std::string& color, const int seats);

        /* Custom Copy Constructor, commented due to Item 6 */
        Car(const Car& givenCar) :theName(givenCar.theName), theColor(givenCar.theColor), numberOfSeats(givenCar.numberOfSeats), isCarLocked(givenCar.isCarLocked)
        {}

        /* Custom assignment operator */
        Car& operator=(const Car& rhs)
        {
            if(this == &rhs)
            {
                std::cout<<"Objects are identical!\n";
                return *this;
            }
            this->theColor = rhs.theColor;
            this->theName = rhs.theName;
            this->numberOfSeats = rhs.numberOfSeats;
            this->isCarLocked = rhs.isCarLocked;
            return *this;
        }

        /* Custom Destructor */
        ~Car()
        {
            std::cout<<"Object has been completely removed from memory!\n";
        }

        void printCar()
        {
            std::cout<<"Car: " << this->theName << "\nColor: " << this->theColor << "\n" << this->numberOfSeats << " seats\n";
        }

        //let's presume this is a critical operation done on an expensive car, as there are high risks of doing it incorrectly
        void changeCarColor(const std::string& newColor)
        {
            this->theColor = newColor;
        }

        bool getIsCarLocked()
        {
            return this->isCarLocked;
        }

        void setIsCarLocked(bool value)
        {
            this->isCarLocked = value;
        }

    private:
        std::string theName;
        std::string theColor;
        int numberOfSeats;
        bool isCarLocked;
};

/* Constructor */
Car::Car(const std::string& name, const std::string& color, const int seats) :theName(name), theColor(color), numberOfSeats(seats), isCarLocked(false)
{}

Car* createCustomCarObject(const std::string& name, const std::string& color, const int seats)
{
    return new Car(name, color, seats);
}

void printNewCustomCar(const std::string& name, const std::string& color, const int seats)
{
    std::auto_ptr<Car> pCar(createCustomCarObject(name, color, seats));
    pCar -> printCar();
}

//item14 features
void lockObject(Car& car)
{
    car.setIsCarLocked(true);
    //std::cout<<"Car is LOCKED now.\n";
};

void unlockObject(Car& car)
{
    car.setIsCarLocked(false);
    //std::cout<<"Car is UNLOCKED now.\n";
};

class LockedCar: private Uncopyable
{
    public:
        explicit LockedCar(Car& givenCar): pCar(givenCar)
        {
            //lock the car
            lockObject(pCar);
        }
        ~LockedCar()
        {
            //unlock the car automatically by destructor
            unlockObject(pCar);
            std::cout<<"Object has been completely removed from memory!\n";
        }
    private:
        Car& pCar;
};

int main()
{
    //item 13 with "auto_ptr"
    printNewCustomCar("Custom Ford GT 2017", "Blue", 2);
    std::cout<<"\n";

    std::auto_ptr<Car> pCar1(new Car);
    pCar1 -> printCar();
    std::cout<<"\n";

    std::auto_ptr<Car> pCar2(pCar1);    // now, pCar1 becomes null because pCar2 points to the empty car
    pCar2 -> printCar();
    std::cout<<"\n";
    
    pCar1 = pCar2;                      // now, pCar2 becomes null because pCar1 points to the empty car again
    pCar1 -> printCar();
    std::cout<<"\n";

    //item 13 with "shared_ptr"
    std::shared_ptr<Car> pCar3(createCustomCarObject("Custom Audi A4 2010", "Silver", 4));
    pCar3 -> printCar();
    std::cout<<"\n";

    std::shared_ptr<Car> pCar4(pCar3);  // now, both pCar3 and pCar4 point towards the Audi A4 object, a scenario which does not work with auto pointers
    pCar4 -> printCar();
    std::cout<<"\n";

    //item 14
    Car specialCar("Bugatti Chiron", "Black", 2);
    specialCar.printCar();
    std::cout<<"Car locked: "<<specialCar.getIsCarLocked()<<"\n";
    std::cout<<"\n";
    //let's say we want to change the color of the Bugatti, which is a critical operation
    //therefore, we create a block to define a critical section
    {
        LockedCar lc(specialCar);                            //lock the car object
        std::cout<<"Car locked: "<<specialCar.getIsCarLocked()<<"\n";
        
        specialCar.changeCarColor("Red and White");          //we now change the color
    }

    std::cout<<"\n";
    specialCar.printCar();
    std::cout<<"Car locked: "<<specialCar.getIsCarLocked()<<"\n";
    std::cout<<"\n";
    return 0;
}