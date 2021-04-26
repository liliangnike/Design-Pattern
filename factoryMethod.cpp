/*
    What is factory method?

    Parent class provides a factory method. Derived class can overwrite the factory method to create (new operator) different objects.

    1. In parent class (creator), factory method is defined.

    2. Derived class of creator includes overwrite factory method.

    3. Differ concrete product is new-ed in the factory methods.

    4. When need to add new product to current system, 1) add derived class of creator; 2) add new product class
       No need new a product class object in client code.

       Client code only need minor changes.

*/

#include <iostream>

using namespace std;

// parent class of product
// Abstract class, defines product common interface
class product
{
public:
    virtual ~product() {};
    virtual string identifier() const = 0;
};

// product 1
class product1 : public product
{
public:
    string identifier() const override
    {
	return "I am product 1.";
    }
};

// product 2
class product2 : public product
{
public:
    string identifier() const override
    {
	return "I am product 2.";
    }
};
// Parent class definition -- creator
// Abstract class, is responsible to define interface of factory method
class creator
{
public:
    creator() {};
    virtual ~creator() {};

    // pure virtual function, must realize in derived class.
    virtual product *factoryMethod() const = 0;

    string demo() const
    {
	product *pdt = this->factoryMethod();
 	string re = pdt->identifier();
	delete pdt;

	return re;
    }
};

// 1 derived class of creator
// Responsible for concrete product creation
class creator1 : public creator
{
public:
    //overwrite factory method
    // use abstract class 'product' so that creator can be independent with product1... 
    product *factoryMethod() const override
    {
	return new product1();
    }
};


// 2 derived class of creator
// Responsible for concrete product creation
class creator2 : public creator
{
public:
    //overwrite factory method
    // use abstract class 'product' so that creator can be independent with product2... 
    product *factoryMethod() const override
    {
	return new product2();
    }
};

// client code for demo
void clientCode(const creator & crt)
{
    cout << crt.demo() << endl;
}

int main()
{
    cout << "create create1 " << endl;
    creator *crt1 = new creator1();
    clientCode(*crt1);

    cout << endl;

    cout << "create create2 " << endl;
    creator *crt2 = new creator2();
    clientCode(*crt2);

    delete crt1;
    delete crt2;

    return 0;
}

