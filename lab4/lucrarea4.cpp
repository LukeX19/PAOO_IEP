#include <iostream>
#include <string>

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
class Car: private Uncopyable
{
    public:
        /* Default Constructor */
        Car() {}

        /* Custom Constructors*/
        Car(const std::string& name, const std::string& color);
        Car(const std::string& name, const std::string& color, const int seats);

        /* Custom Copy Constructor, commented due to Item 6 */
        /*Car(const Car& givenCar) :theName(givenCar.theName), theColor(givenCar.theColor), numberOfSeats(givenCar.numberOfSeats)
        {}*/

        /* Custom Copy Operator, commented due to Item 6 */
        /*Car& operator=(const Car& rhs)
        {
            this->theColor = rhs.theColor;
            this->theName = rhs.theName;
            this->numberOfSeats = rhs.numberOfSeats;
            return *this;
        }*/

        /* Custom Destructor */
        ~Car()
        {
            std::cout<<"Object has been completely removed from memory!\n";
        }

        void printCar()
        {
            std::cout<<"--------------------------------\nCar: " + this->theName + "\nColor: " + this->theColor + "\n" + std::to_string(this->numberOfSeats) + " seats\n--------------------------------\n\n";
        }

    private:
        std::string theName;
        std::string theColor;
        int numberOfSeats;
};

/* Constructor for usual cars*/
Car::Car(const std::string& name, const std::string& color) :theName(name), theColor(color), numberOfSeats(4)
{}

/*Constructor for cars with only 2 doors, such as sport cars, super cars or hyper cars*/
Car::Car(const std::string& name, const std::string& color, const int seats) :theName(name), theColor(color), numberOfSeats(seats)
{}

int main()
{
    std::cout<<"Hello World, today we will buy a car!\n";

    std::string name, color;
    int seats;

    std::cout<<"Which car would you like to have?\n"; std::getline(std::cin, name);
    std::cout<<"What color shall the car have?\n"; std::getline(std::cin, color);
    std::cout<<"Should the car have 2 or 4 seats?\n"; std::cin>>seats;

    Car car1(name, color, seats);
    car1.printCar();

    Car car2("Lamborghini Urus", "Black", 4);
    car2.printCar();

    Car car3(car2);
    car3.printCar();

    Car car4;
    car4 = car1;
    car4.printCar();
    return 0;
}