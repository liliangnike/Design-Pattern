/*
    Builder pattern is different from other creational patterns (factory method, .etc). Builder does not require products have same interface functions.

    Sometimes, user derived class to create different objects is a good way, but there might be many class.

    Or you can use different parameter flags in constructor to control differ steps, this is not good.

    You can defined a builder class that contains all steps to build different products. 
    Client code can select necessary steps to build their specific product.

    It applied to below:
	1. Difference products creation steps are similar, only have minor differ steps.
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// can define various products
class product
{
public:
    void printParts() const
    {
	for (auto p : _parts)
	{
	    cout << p << endl;
	}

	cout << "\n\n";
    }

    vector<string> _parts;
};

/*Builder interface specifies methods to create difference part of product.*/
class builder
{
public:
    virtual ~builder() {}
    
    virtual void createPartA() const = 0;
    virtual void createPartB() const = 0;
    virtual void createPartC() const = 0;
};

class concreteBuilder : public builder
{
public:
    concreteBuilder()
    {
    }

    ~concreteBuilder()
    {
	//if (_prod) delete _prod;
    }

    void create()
    {
	_prod = new product();
    }

    void createPartA() const override
    {
	_prod->_parts.push_back("Part A");
    }
    
    void createPartB() const override
    {
	_prod->_parts.push_back("Part B");
    }
    void createPartC() const override
    {
	_prod->_parts.push_back("Part C");
    }

    product *getProduct()
    {
	return this->_prod;
    }

private:
    product *_prod;
};

/*
    The class director is optional. It is responsible for calling the building steps according to specific order.

    Client code can control builder directly, but if we have set up the fixed steps to build a specific product, then client code can call director easily.

    And client code does not know the creation details.
*/
class director
{
public:
    void setBuilder(builder *blder) { _blder = blder; }

    void buildPartA()
    {
	_blder->createPartA();
    }

    void buildCompleteProduct()
    {
	_blder->createPartA();
	_blder->createPartB();
	_blder->createPartC();
    }

private:
    builder *_blder;
};

void clientAction(director &dirct)
{
    concreteBuilder *builder1 = new concreteBuilder();

    dirct.setBuilder(builder1);

    builder1->create();
    cout << "Build basic part of product, only build part A:" << endl;
    dirct.buildPartA();
    product *p = builder1->getProduct();
    if (p) 
    {
	p->printParts();
	delete p;
	p = nullptr;
    }


    builder1->create();
    cout << "Build a complete product:" << endl;
    dirct.buildCompleteProduct();
    p = builder1->getProduct();
    if (p) 
    {
	p->printParts();
	delete p;
	p = nullptr;
    }

    // customerize to create product without using director class
    cout << "Customer to build product:" << endl;
    builder1->create();
    builder1->createPartB();
    builder1->createPartC();
    p = builder1->getProduct();
    if (p) 
    {
	p->printParts();
	delete p;
	p = nullptr;
    }
   
    delete builder1;
};

int main()
{
    director *dt = new director();
    clientAction(*dt);
    delete dt;

    return 0;
}
