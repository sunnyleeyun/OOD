#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Subscriber
{
public:
    virtual void update(string &eventData) = 0;
};

class ActualSubscriber : public Subscriber
{
private:
    string id;

public:
    ActualSubscriber(string id) : id(id) {}

    void update(string &eventData)
    {
        cout << id << " receive data: " << eventData << endl;
    }
};
class Publisher
{
private:
    vector<Subscriber *> subscribers;
    string eventData;

public:
    Publisher() {}

    void attach(Subscriber *subscriber)
    {
        subscribers.push_back(subscriber);
    }

    void detach(Subscriber *subscriber)
    {
        subscribers.erase(remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
    }

    void notify()
    {
        for (Subscriber *subscriber : subscribers)
        {
            subscriber->update(eventData);
        }
    }

    void createEvent(string data)
    {
        eventData = data;
        notify();
    }
};

int main()
{
    Publisher publisher;
    ActualSubscriber subscriber1("subscriber1");
    ActualSubscriber subscriber2("subscriber2");
    publisher.attach(&subscriber1);
    publisher.attach(&subscriber2);

    publisher.createEvent("Event 1 Data");
    publisher.detach(&subscriber1);

    publisher.createEvent("Event 2 Data");

    return 0;
}