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
    iAbstractView():_TrafficController(0) {}
    virtual ~iAbstractView() {};

    // Setter of the current Controller
    inline void SetController( cTrafficController *TrafficController) { _TrafficController = TrafficController;}

protected:
    // Protected ref to controller NOTICE: CURRENT OBJECT IS _NOT_ THE OWNER OF THIS OBJECT
    cTrafficController *_TrafficController;
};

#endif // INTERFACE_ABSTRACTVIEW_H
