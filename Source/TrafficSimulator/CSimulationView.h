#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include "../../Source/TrafficSimulator/CAbstractView.h"

class CSimulationView : public CAbstractView
{
    public:
        CSimulationView();
        virtual ~CSimulationView(){};

        void UpdatePull();
};

#endif // CSIMULATIONVIEW_H
