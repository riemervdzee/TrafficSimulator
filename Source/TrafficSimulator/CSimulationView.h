#ifndef CSIMULATIONVIEW_H
#define CSIMULATIONVIEW_H

#include <GL/glfw.h>
#include "../../Source/TrafficSimulator/CAbstractView.h"

class CSimulationView : public CAbstractView
{
public:
    CSimulationView()
    {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    }
    ~CSimulationView(){}

    void UpdatePull();
    void Update(float dt);
    void Draw();
};

#endif // CSIMULATIONVIEW_H
