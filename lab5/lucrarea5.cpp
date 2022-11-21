#include <iostream>
#include <string>

/* Custom class Car which inherits the base class */
class Car
{
    public:
        /* Default Constructor */
        Car() {}

        /* Custom Constructor */
        Car(const std::string& name, const std::string& color, const int seats, const int hp);

        /* Custom Copy Constructor, commented due to Item 6 */
        Car(const Car& givenCar) :theName(givenCar.theName), theColor(givenCar.theColor), numberOfSeats(givenCar.numberOfSeats), totalHorsePower(new int(*givenCar.totalHorsePower))
        {}

        /* Custom Assignment Operator, commented due to Item 10 */
        /* Car& operator=(const Car& rhs)
        {
            this->theColor = rhs.theColor;
            this->theName = rhs.theName;
            this->numberOfSeats = rhs.numberOfSeats;
            this->totalHorsePower = rhs.totalHorsePower;
            return *this;
        } */

        /* Item 11 */
        Car& operator=(const Car& rhs)
        {
            int *pOriginalHp = totalHorsePower;
            totalHorsePower = new int(*rhs.totalHorsePower);
            delete pOriginalHp;
            return *this;
        }

        /* Custom Destructor */
        ~Car()
        {
            /* to not have memory leaks */
            delete totalHorsePower;
            std::cout<<"Object has been completely removed from memory!\n";
        }

        void printCar()
        {
            std::cout<<"------------------------\nCar: " + this->theName + "\nColor: " + this->theColor + "\n" + std::to_string(this->numberOfSeats) + " seats\nHorse Power: " + std::to_string(*this->totalHorsePower) + " HP\n------------------------\n\n";
        }

    private:
        std::string theName;
        std::string theColor;
        int numberOfSeats;
        int* totalHorsePower;
};

/*Constructor for cars with only 2 doors, such as sport cars, super cars or hyper cars*/
Car::Car(const std::string& name, const std::string& color, const int seats, const int hp) :theName(name), theColor(color), numberOfSeats(seats), totalHorsePower(new int(hp))
{}

int main()
{
    Car car1("Lamborghini Urus", "Black", 4, 641);
    car1.printCar();

    Car car2("Ferrari 488 GTB", "Red", 2, 660);
    car2.printCar();

    Car car3(car1);
    car3.printCar();

    Car car4 = car2;
    car4.printCar();

    return 0;
}