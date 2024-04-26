#include <iostream>

// * meaning: value at address
// & meaning: address of variable
class Pointer_example {
    public:
        int a = 10;
        int *p = &a;
        int **q = &p;
        void print() {
            std::cout << "Value at address (*p): " << *p << std::endl;
            std::cout << "Address of variable (p): " << p << std::endl;
            std::cout << "Value at address (**q): " << **q << std::endl;
            std::cout << "Address of variable (*q): " << *q << std::endl;
            std::cout << "Address of variable (&a): " << &a << std::endl;
        }
        void change() {
            *p = 20;
            std::cout << "Value at address (a) when *p = 20: " << a << std::endl;
            **q = 30;
            std::cout << "Value at address (a) when **q = 20: " << a << std::endl;
        }
        void add() {
            p += 1;
            std::cout << "Value at address (*p) when p += 1: " << *p << std::endl;
            std::cout << "Address of variable (p) when p += 1: " << p << std::endl;
        }

        void run() {
            std::cout << "Running on the pointer example" << std::endl;
            std::cout << "printing the value at address \n" << std::endl;
            print();
            std::cout << "changing the value at address \n" << std::endl;
            change();
            std::cout << "adding the value at address \n" << std::endl;
            add();
        }
};

class example_Polymorphism {
public:
    struct Base {
        virtual void print() {
            std::cout << "Base class" << std::endl;
        }
        virtual ~Base() {}  // A virtual destructor to ensure proper cleanup
    };

    struct ObjectB: Base {
        void print() override {
            std::cout << "Derived class B" << std::endl;
        }
    };

    struct ObjectC: Base {
        void print() override {
            std::cout << "Derived class C" << std::endl;
        }
    };

    void run() {
        // Create a derived class object and call the print function
        Base *b = new ObjectB();
        // Create another derived class object and call the print function
        Base *c = new ObjectC();
        // Call the print function of the derived class object
        b->print();
        // Call the print function of the derived class object
        c->print();
        // Delete the objects
        delete b;
        // Delete the objects
        delete c;
    }
};

int main() {
    std::cout << "Running on the pointer example \n" << std::endl;
    Pointer_example p;
    p.run();

    std::cout << "\n Running on the polymorphism example \n" << std::endl;
    example_Polymorphism e;
    e.run();
    return 0;
}
