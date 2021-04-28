/*
    Observer design pattern is a behavior design pattern. 

    In this design pattern, user can define a subscription mechanisiam that
when a certain object have changes, it can notify all the objects that "observing" the certain object.

    The typical example is that customer who want to buy the latest iPhone in Appls store.
    1. Buyers want to know when the latest type can be reached.
    2. They don't want to go to Apple store repeatedly for check.
    3. Apple store can save their email or buyers subscribe the news
    4. When the latest phone is being sold in Apple store, buyers who are subscribing will be noticed
    5. The notification will not be sent to the buyers who did not subscribe.


    How to realize?

    1. Publisher has to maintain a list for all subscribers.

    2. Publisher has method to add/delete subscribers.

    3. Publisher has method to notify subscribers

    4. When observers receive the notice, they need to do related update.
*/

#include <iostream>
#include <list>
#include <string>

using namespace std;

// subscriber abstract base class
class subscriberBase
{
public:
    subscriberBase() = default;
    ~subscriberBase() {};

    // each subscriber should have method 'update'
    virtual void update(const string &fromPublisher) = 0;
};

// publisher abstract base class
class pulisherBase
{
public:
    pulisherBase() = default;
    virtual ~pulisherBase() {};

    virtual void add(subscriberBase *subscriber) = 0;
    virtual void remove(subscriberBase *subscriber) = 0;
    // concrete publisher can notify each subscriber
    virtual void notify() = 0;
};

// concrete derived publisher class
class publisher : public pulisherBase
{
public:
    ~publisher() 
    {
	cout << "Publisher is destroyed, Bye-bye!" << endl;
    };

    void add(subscriberBase *subscriber) override
    {
	_subscriberList.push_back(subscriber);
    };

    void remove(subscriberBase *subscriber) override
    {
	_subscriberList.remove(subscriber);
    };

    void notify() override
    {
	cout << "Current numbers of subscriber is: " << _subscriberList.size() << endl;
	for (auto sub : _subscriberList)
	{
	    sub->update(_msg);
	}
    };

    void createMsg(string msgStr)
    {
	_msg = msgStr;
	notify();
    };

    void someChanges()
    {
	_msg = "Some change action!";
	notify();
    };
private:
    // publisher should maintained a subscriber list
    list<subscriberBase *> _subscriberList;
    string _msg;
};


// concrete derived subscriber class
class subscriber : public subscriberBase
{
public:
    subscriber(publisher &pub) : _publisher(pub)
    {
	_publisher.add(this);
	cout << "New subscriber is created, its index is: " << ++subscriber::_overallIdx << endl;
	_idx = subscriber::_overallIdx;
    };

    ~subscriber() 
    {
    };

    void update(const string &fromPublisher) override
    {
	_msgFromPublisher = fromPublisher;
	cout << "A new message for subscriber: " << _idx << ", msg is " << _msgFromPublisher << endl;
    };

    void removeSubscriber()
    {
	_publisher.remove(this);
	cout << "Removed subscriber index is: " << _idx << endl;
    }

private:
    string _msgFromPublisher;
    publisher &_publisher;
    int _idx;
    static int _overallIdx;
};

int subscriber::_overallIdx = 0;

void demo()
{
    publisher *publish = new publisher;

    subscriber *subs1 = new subscriber(*publish);
    subscriber *subs2 = new subscriber(*publish);
    subscriber *subs3 = new subscriber(*publish);
    subscriber *subs4;
    subscriber *subs5;

    publish->createMsg("Hello, hello, hello.......");
    subs3->removeSubscriber();

    publish->createMsg("Are you happy??");
    subs2->removeSubscriber();

    subs4 = new subscriber(*publish);
    subs5 = new subscriber(*publish);

    publish->createMsg("My car is toyota.......");
    subs5->removeSubscriber();
    subs4->removeSubscriber();
    subs1->removeSubscriber();

    delete subs5;
    delete subs4;
    delete subs3;
    delete subs2;
    delete subs1;
};

int main()
{
    demo();
    return 0;
}
