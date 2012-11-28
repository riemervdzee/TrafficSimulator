#ifndef INTERFACE_ABSTRACTVIEW_H
#define INTERFACE_ABSTRACTVIEW_H

class cTrafficController;

/*
 * Interface for every view
 */
class iAbstractView
{
public:
    // Virtual deconstructor for inheritance
    virtual ~iAbstractView() {};

    // Setter of the current Controller
    inline void SetController( cTrafficController *TrafficController) { _TrafficController = TrafficController;}

protected:
    // Protected ref to controller NOTICE: CURRENT OBJECT IS _NOT_ OWNER OF THIS OBJECT
    cTrafficController *_TrafficController;
};

#endif // INTERFACE_ABSTRACTVIEW_H
