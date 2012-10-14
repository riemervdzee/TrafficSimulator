#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include "../../Source/TrafficSimulator/CAbstractView.h"

class CSimulationView : public CAbstractView
{
public:
    CSimulationView(int width, int height);
    ~CSimulationView(){}

    void UpdatePull();
    void Update(float dt);
    void Draw();
};

#endif // CSIMULATIONVIEW_H
