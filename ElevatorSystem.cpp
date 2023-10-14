// The elevator will first process UP requests where request floor is greater than current floor and then process Down requests where request floor is lower than current floor

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum ElevatorStatus
{
    IDLE,
    UP,
    DOWN
};

enum Direction
{
    UP,
    DOWN
};

class Request
{
private:
    int currentFloor;
    int desiredFloor;
    Direction direction;

public:
    Request(int currentFloor, int desiredFloor, Direction direction) : currentFloor(currentFloor), desiredFloor(desiredFloor), direction(direction) {}

    int getDesiredFloor() const
    {
        return desiredFloor;
    }

    int getDirection() const
    {
        return direction;
    }
};

struct MinDesiredFloor
{
    bool operator()(const Request &lhs, const Request &rhs) const
    {
        return lhs.getDesiredFloor() > rhs.getDesiredFloor();
    }
};

struct MaxDesiredFloor
{
    bool operator()(const Request &lhs, const Request &rhs) const
    {
        return lhs.getDesiredFloor() < rhs.getDesiredFloor();
    }
};
class Elevator
{
private:
    int floor;
    ElevatorStatus status;
    priority_queue<Request, vector<Request>, MinDesiredFloor> upRequestPq;   // min heap
    priority_queue<Request, vector<Request>, MaxDesiredFloor> downRequestPq; // max heap

    void processRequests()
    {
        if (this->status == UP || this->status == IDLE)
        {
            // up
            processUpRequests();
        }
        else
        {
            // down
            processDownRequests();
        }
    }

    void processUpRequests()
    {
        while (!upRequestPq.empty())
        {
            Request req = upRequestPq.top();
            floor = req.getDesiredFloor();
            // elevator at desired floor
        }
        status = (downRequestPq.empty() ? UP : DOWN);
    }
    void processDownRequests()
    {
        while (!downRequestPq.empty())
        {
            Request req = upRequestPq.top();
            floor = req.getDesiredFloor();
            // elevator at desired floor
        }
        status = (upRequestPq.empty() ? IDLE : UP);
    }

public:
    Elevator(int floor) : floor(floor)
    {
        status = IDLE;
    }

    void receiveRequest(Request request)
    {
        switch (request.getDirection())
        {
        case UP:
            upRequestPq.push(request);
            break;
        case DOWN:
            downRequestPq.push(request);
            break;
        default:
            break;
        }
    }

    void on()
    {
        while (!upRequestPq.empty() || !downRequestPq.empty())
        {
            processRequests();
        }
    }
};

int main()
{

    Elevator elevator(1);
    int cur1 = 3, des1 = 5;
    Request req1(cur1, des1, cur1 > des1 ? DOWN : UP);

    // store the state of all elevators
    elevator.receiveRequest(req1); // find the optimal elevator for this request

    elevator.on(); // void method and start processing requests

    return 0;
}