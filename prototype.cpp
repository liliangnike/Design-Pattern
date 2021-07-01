/*
    Prototype design pattern support to clone objects (including very big and complicated objects).

    And with this pattern, it will not depend on the class of those objects.
*/

#include <iostream>
#include <map>

using namespace std;

enum type 
{
    PROTOTYPE_1,
    PROTOTYPE_2
};

// prototype class interface that support clone method
class protoType
{
public:
    protoType() {}
    protoType(string name) : _name(name) {}

    virtual ~protoType() {}

    virtual protoType *clone() const = 0;
    virtual void method (int id)
    {
	_idx = id;
	cout << "Call method from prototype: " << _name << ", index: " << _idx << endl;
    }

protected:
    string _name;
    int _idx;
};

class concreteProtoType1 : public protoType
{
public:
    // initialize the data members of both base class and derived class
    concreteProtoType1(string name, int id) : protoType(name), _idx1(id) {}

    protoType *clone() const override { return new concreteProtoType1(*this); }

private:
    int _idx1;
};

class concreteProtoType2 : public protoType
{
public:
    // initialize the data members of both base class and derived class
    concreteProtoType2(string name, int id) : protoType(name), _idx2(id) {}

    protoType *clone() const override { return new concreteProtoType2(*this); }

private:
    int _idx2;
};

class prototypeFactory
{
public:
    prototypeFactory()
    {
	_protoMap[type::PROTOTYPE_1] = new concreteProtoType1("PROTOTYPE_1", 50);
	_protoMap[type::PROTOTYPE_2] = new concreteProtoType2("PROTOTYPE_2", 60);
    }

    ~prototypeFactory()
    {
	delete _protoMap[type::PROTOTYPE_1];
	delete _protoMap[type::PROTOTYPE_2];
    }

    protoType *createProtoType(type typ)
    {
	return _protoMap[typ]->clone();
    }

private:
    map<type, protoType *> _protoMap;
};

void demo(prototypeFactory *prototypeFact)
{
    cout << "Let's create prototype 1: " << endl;
    protoType * typ = prototypeFact->createProtoType(type::PROTOTYPE_1);
    typ->method(90);
    delete typ;

    cout << "Let's create prototype 2: " << endl;
    typ = prototypeFact->createProtoType(type::PROTOTYPE_2);
    typ->method(10);
    delete typ;

    return;
};

int main()
{
    prototypeFactory *fact = new prototypeFactory();
    demo(fact);
    delete fact;
    fact = nullptr;

    return 0;
}
