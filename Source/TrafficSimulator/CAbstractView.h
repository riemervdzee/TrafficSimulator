#ifndef CABSTRACTVIEW_H
#define CABSTRACTVIEW_H

class CSimulationController;
class CSimulationModel;

// abstract view class
class CAbstractView
{
public:
    CAbstractView()
    {
        mController = 0;
        mModel = 0;
    }
    virtual ~CAbstractView(){};

    void SetController(CSimulationController* contr) { mController = contr; }
    void SetModel(CSimulationModel* model) { mModel = model; }

    virtual void UpdatePull() = 0;

protected:
    CSimulationController   *mController; // VIEWS ARE NOT OWNERS OF THESE POINTERS!
    CSimulationModel        *mModel; // VIEWS ARE NOT OWNERS OF THESE POINTERS!
};

#endif // CABSTRACTVIEW_H
