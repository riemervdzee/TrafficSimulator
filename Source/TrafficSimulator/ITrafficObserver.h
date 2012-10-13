#ifndef ITRAFFICOBSERVER_H
#define ITRAFFICOBSERVER_H

// Observer for the simulation
class ITrafficObserver
{
public:
    virtual void UpdatePul() = 0;
};

#endif // ITRAFFICOBSERVER_H
