#include <iostream>
#include <string>
#include <memory>

/* Custom class Car which inherits the base class */
class Car 
{
    public:
        /* Default Constructor */
        Car() : theName("inexisting_car"), theColor("inexisting_color"), numberOfSeats(0) {}

        /* Custom Constructor */
        Car(const std::string& name, const std::string& color, const int seats);

        /* Custom Copy Constructor, commented due to Item 6 */
        Car(const Car& givenCar) :theName(givenCar.theName), theColor(givenCar.theColor), numberOfSeats(givenCar.numberOfSeats)
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

        // set functions for private fields
        // void setName(const std::string& newName)
        // {
        //     this->theName = newName;
        // }
        // void setColor(const std::string& newColor)
        // {
        //     this->theColor = newColor;
        // }
        // void setNumberOfSeats(const int newNumberOfSeats)
        // {
        //     this->numberOfSeats = newNumberOfSeats;
        // }

    private:
        std::string theName;
        std::string theColor;
        int numberOfSeats;
};

/* Constructor */
Car::Car(const std::string& name, const std::string& color, const int seats) :theName(name), theColor(color), numberOfSeats(seats)
{}

Car* createCustomCarObject(const std::string& name, const std::string& color, const int seats)
{
    return new Car(name, color, seats);
}

void printNewCustomCar(const std::string& name, const std::string& color, const int seats)
{
    std::auto_ptr<Car> pCar(createCustomCarObject(name, color, seats));
    // pCar -> setName(name);
    // pCar -> setColor(color);
    // pCar -> setNumberOfSeats(seats);
    pCar -> printCar();
}

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
    std::shared_ptr<Car> pCar3(createCustomCarObject("Custom Audi A4 2010", "Grey", 4));
    pCar3 -> printCar();
    std::cout<<"\n";

    std::shared_ptr<Car> pCar4(pCar3);  // now, both pCar3 and pCar4 point towards the Audi A4 object, a scenario which does not work with auto pointers
    pCar4 -> printCar();
    std::cout<<"\n";

    return 0;
}