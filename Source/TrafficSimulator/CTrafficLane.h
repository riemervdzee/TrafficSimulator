#ifndef CTRAFFICLANE_H
#define CTRAFFICLANE_H

#include "TrafficDefs.h"
#include "CTrafficLaneGroup.h"
#include "CTrafficLight.h"
#include "CParticipant.h"
#include "Math/WildMath.h"

#include <vector>
#include <list>

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
    virtual void UpdateParticipants(std::vector<CTrafficLight>& lightList,
                                    CTrafficLaneGroup* groups, float dt) = 0;
    virtual void Clear() = 0;

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
    CCommonTrafficLane()
    {
        incomingQueue.reserve(128);
        participantQueue.reserve(32);
    }
    ~CCommonTrafficLane() {}
    void Clear();

    void AddParticipant(std::list<CParticipant>& parList,const TRADEFS::SimulationQueueParticipant_t& info);
    void UpdateParticipants(std::vector<CTrafficLight>& lightList,
                            CTrafficLaneGroup* groups, float dt);

    void GoToStoplight(CParticipant& par, int index, float dt);
    void WaitStoplight(CParticipant& par,std::vector<CTrafficLight>& lightList, float dt);
    void OnCrossroad(CParticipant& par, CTrafficLaneGroup* groups, float dt);
    void GoToExit(CParticipant& par, CTrafficLaneGroup* groups, float dt);

private:
    std::vector<CParticipant*> incomingQueue;
    std::vector<CParticipant*> participantQueue;
};

class CPedestrianTrafficLane: public CTrafficLane
{
public:
    CPedestrianTrafficLane(){}
    ~CPedestrianTrafficLane(){}
    void Clear();

    void AddParticipant(std::list<CParticipant>& parList,const TRADEFS::SimulationQueueParticipant_t& info);
    void UpdateParticipants( std::vector<CTrafficLight>& lightList,
                            CTrafficLaneGroup* groups, float dt);

    // traffic light
    void SetMidTrafficlight(int light){midLightID = light;}
    int GetMidLightID(){ return midLightID;}

    void SetPedStart(const wmath::Vec3& start){pedStart = start;}
    wmath::Vec3 GetPedTo(int group, int lane, CTrafficLaneGroup* groups);

    void GoToStoplight(CParticipant& par, CTrafficLaneGroup* groups, int index, float dt);
    void WaitStoplight(CParticipant& par, std::vector<CTrafficLight>& lightList, float dt);
    void OnCrossroad(CParticipant& par, CTrafficLaneGroup* groups, float dt);
    void GoToExit(CParticipant& par, CTrafficLaneGroup* groups, float dt);

private:
    int midLightID;
    wmath::Vec3                 pedStart;
    std::vector<CParticipant*> incomingQueue;
    std::vector<CParticipant*> participantQueue;
};

#endif // CTRAFFICLANE_H
