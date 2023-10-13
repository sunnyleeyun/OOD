// Implement a Load Balancer. The Load Balancer serves incoming requests. For each Request, we know how much work they require, characterized by a weight. The Load Balancer manages a fleet of servers. The goal is to balance the amount of work that each server does. Example:
// Create Load Balancer with servers "a", "b", "c"
// A request with weight = 4 comes in, it is assigned to server "a"
// A request with weight = 2 comes in, it is assigned to server "b"
// A request with weight = 2 comes in, it is assigned to server "c"
// A request with weight = 1 comes in, it is assigned to server "b" ... and so on

#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

class Request
{
private:
    string id;
    int weight;

public:
    Request(string id, int weight) : id(id), weight(weight) {}

    string getId()
    {
        return id;
    }

    int getWeight()
    {
        return weight;
    }
};

class Server
{
private:
    string id;
    int load;

public:
    Server(string id) : id(id), load(0) {}

    int getLoad() const
    {
        return load;
    }

    void addLoad(int weight)
    {
        load += weight;
    }

    void removeLoad(int weight)
    {
        load -= weight;
    }
};

struct GreaterThanByLoad
{
    bool operator()(const Server &lhs, const Server &rhs) const
    {
        return lhs.getLoad() > rhs.getLoad();
    }
};

class LoadBalancerSystem
{
private:
    unordered_map<string, pair<Request, Server>> requestMp;
    priority_queue<Server, vector<Server>, GreaterThanByLoad>
        serverPq; // min heap

public:
    LoadBalancerSystem() {}

    /**
     * @brief add server to the system
     * @throw exception if unsuccessful
     */
    void addServer(Server server)
    {
        serverPq.push(server);
    }

    /**
     * @brief digest request from the system and assign to servers
     * @throw exception if unsuccessful
     */
    void digestRequest(Request request)
    {
        // get the smallest load server
        Server top = serverPq.top();
        serverPq.pop();
        // add load
        top.addLoad(request.getWeight());
        requestMp[request.getId()] = {request, top};
        // put back
        serverPq.push(top);
    }

    void finishDigestRequest(Request request)
    {
        auto server = requestMp[request.getId()].second;
        server.removeLoad(request.getWeight());
        requestMp.erase(request.getId());
    }
};

int main()
{
    LoadBalancerSystem lb; // priority_queue -> min heap servers
    Server server1("a");   // id, load ; method: addLoad
    lb.addServer(server1);
    //...

    Request req1("req1", 4); // weight, id
    lb.digestRequest(req1);  // pop from the pq. and addLoad(weight) and put back it pq

    // Request->LoadBalancerSystem <|- servers
    return 0;
}
