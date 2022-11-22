#include <iostream>
#include <string>

/* Custom class Car which inherits the base class */
class Car
{
    public:
        /* Default Constructor */
        Car() : theName("inexisting_car"), theColor("inexisting_color"), numberOfSeats(0), totalHorsePower(0) {}

        /* Custom Constructor */
        Car(const std::string& name, const std::string& color, const int seats, const int hp);

        /* Custom Copy Constructor, commented due to Item 6 */
        Car(const Car& givenCar) :theName(givenCar.theName), theColor(givenCar.theColor), numberOfSeats(givenCar.numberOfSeats), totalHorsePower(givenCar.totalHorsePower)
        {}

        /* Item 11 */
        Car& operator=(const Car& rhs)
        {
            //int *pOriginalHp = totalHorsePower;
            //totalHorsePower = new int(*rhs.totalHorsePower);
            //delete pOriginalHp;
            if(this == &rhs)
            {
                std::cout<<"Objects are identical!\n";
                return *this;
            }
            this->theColor = rhs.theColor;
            this->theName = rhs.theName;
            this->numberOfSeats = rhs.numberOfSeats;
            this->totalHorsePower = rhs.totalHorsePower;
            return *this;
        }

        /* Custom Destructor */
        ~Car()
        {
            /* to not have memory leaks */
            //delete totalHorsePower;
            std::cout<<"Object has been completely removed from memory!\n";
        }

        void printCar()
        {
            std::cout<<"Car: " << this->theName << "\nColor: " << this->theColor << "\n" << this->numberOfSeats << " seats\nHorse Power: " << this->totalHorsePower << " HP\n";
        }

    private:
        std::string theName;
        std::string theColor;
        int numberOfSeats;
        int totalHorsePower;
};

class Mercedes : public Car
{
    public:
        Mercedes() : Car(), leatherSeats(false) {}

        Mercedes(const std::string& name, const std::string& color, const int seats, const int hp, bool hasleatherseats) : Car(name, color, seats, hp), leatherSeats(hasleatherseats) {}

        /* Copy Constructor */
        Mercedes(const Mercedes& givenCar) : Car(givenCar), leatherSeats(givenCar.leatherSeats) {}

        /* Assignment Operator */
        Mercedes& operator=(const Mercedes& rhs)
        {
            if(this == &rhs)
            {
                std::cout<<"Objects are identical!\n";
                return *this;
            }
            Car::operator=(rhs);
            leatherSeats = rhs.leatherSeats;
            return *this;
        }

        std::string getLeatherSeatsInfo()
        {
            return this->leatherSeats ? "Yes" : "No";
        }

    private:
        bool leatherSeats;
};

/*Constructor for cars with only 2 doors, such as sport cars, super cars or hyper cars*/
Car::Car(const std::string& name, const std::string& color, const int seats, const int hp) :theName(name), theColor(color), numberOfSeats(seats), totalHorsePower(hp)
{}

int main()
{
    Car car1("Lamborghini Urus", "Black", 4, 641);
    car1.printCar();
    std::cout<<"\n\n\n";

    Car car2("Ferrari 488 GTB", "Red", 2, 660);
    car2.printCar();
    std::cout<<"\n\n";

    Car car3(car1);
    car3.printCar();
    std::cout<<"\n\n";

    Car car4 = car2;
    car4.printCar();
    std::cout<<"\n\n";

    Mercedes car5("Mercedes-AMG One", "Siver", 2, 1049, true);
    car5.printCar();
    std::cout<<"Leather seats: " << car5.getLeatherSeatsInfo();
    std::cout<<"\n\n\n";

    Mercedes car6;
    car6 = car5;
    car6.printCar();
    std::cout<<"Leather seats: " << car6.getLeatherSeatsInfo();
    std::cout<<"\n\n\n";

    Mercedes car7;
    car7.printCar();
    std::cout<<"Leather seats: " << car7.getLeatherSeatsInfo();
    std::cout<<"\n\n\n";
    return 0;
}