/*
    Strategy design pattern is behavioral pattern. It can support user to define a serial of algorithms and put the algorithms into different objects seperately.

    Then one object can be changed with others during runtime.

    Context: (original object)
	1. Save reference of strategy
	2. As center between strategies and concrete algorithm
	3. Select the designated algorithm rather than execute any algorithm
	4. Does not know the details of the algorithm.
	5. Use the same interface to call difference algorithms --> so abstract strategy class should be defined.

    Strategy:
	Abstract strategy class to provide interface

    Conctrete Strategy:
	Strategy variants.

    Simple realization scenario,
	client code creates strategy 1 -> set strategy via context  -> calling generic algorithm interface
	client code creates strategy 2 -> set strategy via context  -> calling generic algorithm interface
*/
#include <iostream>
#include <string>

using namespace std;

class strategy
{
public:
    virtual ~strategy() {}
    virtual int demoAlgorithm(int a, int b) const = 0;
};

class context
{
public:
    context(strategy *strgy = nullptr) : _strategy(strgy)
    {
    }

    ~context()
    {
	delete _strategy;
    }

    void setStrategy(strategy *str)
    {
	delete this->_strategy;
	_strategy = str;
    }

    void doSomething()
    {
	cout << "Call algorithms to do something, but I don't know what they will do." << endl;
	cout << "As context, I also don't care what they will do, just pass the action." << endl;
	int res = this->_strategy->demoAlgorithm(10, 20);
	cout << "The result is " << res << endl;
    }
private:
    strategy *_strategy;
};

class strategy1 : public strategy
{
public:
    int demoAlgorithm(int a, int b) const override
    {
	// add
	return a + b;
    }
};

class strategy2 : public strategy
{
public:
    int demoAlgorithm(int a, int b) const override
    {
	// multiply
	return a * b;
    }
};

int main()
{
    context *ctx = new context(new strategy1);
    cout << "Strategy 1 is to add numbers: " << endl;
    ctx->doSomething();

    ctx->setStrategy(new strategy2);
    cout << "Strategy 2 is to multiply numbers: " << endl;
    ctx->doSomething();
    delete ctx;

    return 0;
}
