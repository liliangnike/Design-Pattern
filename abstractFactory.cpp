/*
    Factory method design pattern is used factory method to create different type products (chair, soft,...).

    Abstract factory design pattern is also user different factory methods to create concrete products (modernChair, classicChair, modernSofa, classicSofa), but the created types are
    
    abstract product types (chair, sofa,...).



*/
#include <iostream>
#include <string>

using namespace std;

class abstractProductA
{
public:
    virtual ~abstractProductA() {};

    virtual string funcA() const = 0;
};

class concreteProductA1 : public abstractProductA
{
public:
    string funcA() const override
    {
	return "Product A1";
    }
};

class concreteProductA2 : public abstractProductA
{
public:
    string funcA() const override
    {
	return "Product A2";
    }
};

class abstractProductB
{
public:
    virtual ~abstractProductB() {};
 
    virtual string funcB() const = 0;
    virtual string demoB(const abstractProductA &prodA) const = 0;
};

class concreteProductB1 : public abstractProductB
{
public:
    string funcB() const override
    {
	return "Product B1";
    }

    string demoB(const abstractProductA &prodA) const override
    {
	string str = prodA.funcA();
	return "Procduct B1 meets " + str + " in demo function.";
    }

};

class concreteProductB2 : public abstractProductB
{
public:
    string funcB() const override
    {
	return "Product B2";
    }

    string demoB(const abstractProductA &prodA) const override
    {
	string str = prodA.funcA();
	return "Procduct B2 meets " + str + " in demo function.";
    }
};

class abstractFactory
{
public:
    virtual abstractProductA * createProductA() const = 0;
    virtual abstractProductB * createProductB() const = 0;
};

class concreteFactory1 : public abstractFactory
{
public:
    abstractProductA * createProductA() const override
    {
	return new concreteProductA1();
    }

    abstractProductB * createProductB() const override
    {
	return new concreteProductB1();
    }

};

class concreteFactory2 : public abstractFactory
{
public:
    abstractProductA * createProductA() const override
    {
	return new concreteProductA2();
    }

    abstractProductB * createProductB() const override
    {
	return new concreteProductB2();
    }

};

void clientDemo(const abstractFactory *fact)
{
    abstractProductA *prodA = fact->createProductA();
    abstractProductB *prodB = fact->createProductB();

    cout << prodB->funcB() << endl;
    cout << prodB->demoB(*prodA) << endl;

    delete prodA;
    delete prodB;
};

int main()
{
    cout << "Run factory 1......" << endl;
    concreteFactory1 *factory1 = new concreteFactory1();
    clientDemo(factory1);
    delete factory1;
    cout << endl;


    cout << "Run factory 2......" << endl;
    concreteFactory2 *factory2 = new concreteFactory2();
    clientDemo(factory2);
    delete factory2;
    cout << endl;

    return 0;
}
