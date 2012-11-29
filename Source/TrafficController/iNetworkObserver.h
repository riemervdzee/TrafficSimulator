#ifndef INTERFACE_NETWORKOBSERVER_H
#define INTERFACE_NETWORKOBSERVER_H


/*
 * Main controller class of the TrafficControl server
 */
class iNetworkObserver
{
public:
    // Virtual deconstructor for inheritance
    virtual ~iNetworkObserver() {};

    // Send function
    virtual void Send(std::string TrafficLightMessage) = 0;

    // Update
    virtual void Update() = 0;
};

#endif // INTERFACE_NETWORKOBSERVER_H
