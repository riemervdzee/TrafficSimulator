#ifndef CTRAFFICLANE_H
#define CTRAFFICLANE_H

#include "TrafficDefs.h"
#include "CTrafficLaneGroup.h"
#include "CTrafficLight.h"
#include "CParticipant.h"
#include "Math/WildMath.h"

#include <queue>
#include <list>

// iteratable queue
template<typename T, typename Container=std::deque<T> >
class iterable_queue : public std::queue<T,Container>
{
public:
    typedef typename Container::iterator iterator;
    typedef typename Container::const_iterator const_iterator;

    iterator begin() { return this->c.begin(); }
    iterator end() { return this->c.end(); }
    const_iterator begin() const { return this->c.begin(); }
    const_iterator end() const { return this->c.end(); }
};

class CTrafficLane
{
public:
    CTrafficLane() : lightID(-1) {}
    virtual ~CTrafficLane(){}

    // basic waypoint stuff
    void SetWayStart(const wmath::Vec3& start){wayStart = start;}
    void SetWayEnd(const wmath::Vec3& end){wayEnd = end;}
    wmath::Vec3 GetWayStart() {return wayStart;}
    wmath::Vec3 GetWayEnd() {return wayEnd;}

    // traffic light
    void SetTrafficlight(int light){lightID = light;}
    int GetLightID(){ return lightID;}

    // virtual methods
    virtual void AddParticipant(std::list<CParticipant>& parList,const TRADEFS::SimulationQueueParticipant_t& info) = 0;
    virtual void UpdateParticipants(std::list<CParticipant>& parList,
                                    std::vector<CTrafficLight>& lightList,
                                    CTrafficLaneGroup* groups, float dt) = 0;

    // static helpers
    static float GetParticipantSize(TRADEFS::PARTICIPANTS type);
    static float GetParticipantSpeed(TRADEFS::PARTICIPANTS type);

protected:
    wmath::Vec3     wayStart;
    wmath::Vec3     wayEnd;
    int             lightID; // ID representing the trafficlight that belongs to this lane
};

class CCommonTrafficLane : public CTrafficLane
{
public:
    CCommonTrafficLane(){}
    ~CCommonTrafficLane() {}

    void AddParticipant(std::list<CParticipant>& parList,const TRADEFS::SimulationQueueParticipant_t& info);
    void UpdateParticipants(std::list<CParticipant>& parList,
                            std::vector<CTrafficLight>& lightList,
                            CTrafficLaneGroup* groups, float dt);

    void GoToStoplight(CParticipant& par, float dt);
    void WaitStoplight(CParticipant& par,std::vector<CTrafficLight>& lightList, float dt);
    void OnCrossroad(CParticipant& par, CTrafficLaneGroup* groups, float dt);
    void GoToExit(CParticipant& par, CTrafficLaneGroup* groups, float dt);

private:
    iterable_queue<CParticipant*> incomingQueue;
    iterable_queue<CParticipant*> participantQueue;
};

class CPedestrianTrafficLane: public CTrafficLane
{
public:
    CPedestrianTrafficLane(){}
    ~CPedestrianTrafficLane(){}

    void AddParticipant(std::list<CParticipant>& parList,const TRADEFS::SimulationQueueParticipant_t& info){};
    void UpdateParticipants(std::list<CParticipant>& parList,
                            std::vector<CTrafficLight>& lightList,
                            CTrafficLaneGroup* groups, float dt){};

    // traffic light
    void SetMidTrafficlight(int light){midLightID = light;}
    int GetMidLightID(){ return midLightID;}

private:
    int midLightID;
};

#endif // CTRAFFICLANE_H
