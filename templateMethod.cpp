/*
    Template Method Design Pattern is behavior design pattern that permits derived class to overwrite algorithm in condition of not change system structure.

    It is based on C++ inheritance feature.

    Sometimes, we find that algorithms are same in different situation.
 
    For example, we have file reader that can handle file format pdf, word, excel.

    Function methods such as, openfile, closefile, getline, analyzeline are silimar.

    -> For the similar methods, we can eliminate the duplcated algorithm code by design pattern - template method.
  
    -> For other methods, realize by abstract class.

    In template method design pattern,

    1. For common methods, it can be abstracted into base class and overwrite them in derived class.

    2. For other default methods, it can be realized within abstract base class.

    3. Also can add some hooks -> ?? Not understand so far.


    
    Factory Method is one special pattern of Template Method.
*/

#include <iostream>

using namespace std;

class abstractClass
{
public:
    void templateMethod() const
    {
	this->common1();
	this->specific1();
	this->common2();
	this->specific2();
	this->common3();
    }

    // common algorithms are implemented in abstract class
    void common1() const
    {
	cout << "Common method 1 is called." << endl;
    }

    void common2() const
    {
	cout << "Common method 2 is called." << endl;
    }

    void common3() const
    {
	cout << "Common method 3 is called." << endl;
    }

    // other methods will be implemented in derived classes specially
    virtual void specific1() const = 0;
    virtual void specific2() const = 0;

    // some example also have hook function
    // still not understand this, so I will not add hook member function.
};

class concrete1 : public abstractClass
{
public:
    void specific1() const override
    {
	cout << "Concrete product 1 implements specific method 1." << endl;
    }

    void specific2() const override
    {
	cout << "Concrete product 1 implements specific method 2." << endl;
    }

};

class concrete2 : public abstractClass
{
public:
    void specific1() const override
    {
	cout << "Concrete product 2 implements specific method 1." << endl;
    }

    void specific2() const override
    {
	cout << "Concrete product 2 implements specific method 2." << endl;
    }
};

void demoClient(abstractClass *abstr)
{
    abstr->templateMethod();
};

int main()
{
    cout << "Running common methods and product 1's specific method." << endl;
    concrete1 *product1 = new concrete1;
    demoClient(product1);


    cout << "Running common methods and product 2's specific method." << endl;
    concrete2 *product2 = new concrete2;
    demoClient(product2);

    delete product1;
    delete product2;
    return 0;
}
