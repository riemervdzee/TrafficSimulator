#include "CTrafficLane.h"
#include <cstdio>

float CTrafficLane::GetParticipantSpeed(TRADEFS::PARTICIPANTS type)
{
    switch(type)
    {
        case TRADEFS::CAR:
            return TRADEFS::CARSPEED;
        case TRADEFS::BIKE:
            return TRADEFS::BIKESPEED;
        case TRADEFS::BUS:
            return TRADEFS::BUSSPEED;
        case TRADEFS::PEDESTRIAN:
            return TRADEFS::PEDSPEED;
        default: return 0.0f;
    }
}

float CTrafficLane::GetParticipantSize(TRADEFS::PARTICIPANTS type)
 {
    switch(type)
    {
        case TRADEFS::CAR:
            return TRADEFS::CARSIZE;
        case TRADEFS::BIKE:
            return TRADEFS::BIKESIZE;
        case TRADEFS::BUS:
            return TRADEFS::BUSSIZE;
        case TRADEFS::PEDESTRIAN:
            return TRADEFS::PEDSIZE;
        default: return 0.0f;
    }
 }

float GetRotAngle(int dir)
{
    switch(dir)
    {
        case TRADEFS::NORTH:
            return 180.0f;
        case TRADEFS::EAST:
            return 270.0f;
        case TRADEFS::WEST:
            return 90.0f;
        default: 
            return 0.0f;
    }
}

// HACKY SHIT MAN POINTERS TO LIST ELEMENT
// BUT IT WORKS FOR NOW!
void CCommonTrafficLane::AddParticipant(std::list<CParticipant>& parList,const TRADEFS::SimulationQueueParticipant_t& info)
{
    wmath::Vec3 startPos = (wayStart - wayEnd); startPos.Norm();
    float parSize = CTrafficLane::GetParticipantSize(info.type);
    startPos *= (parSize / 2.0f);
    startPos = wayStart + startPos;
    
    // create participant
    CParticipant par = CParticipant(info.type, info.fromDirection, info.toDirection, info.fromLane, startPos, GetRotAngle(info.fromDirection));
    par.SetState(TRADEFS::GOTOSTOPLIGHT);

    // add participant to pocessing list!
    parList.push_front(par);

    // add to the incoming queue
    incomingQueue.push_back( &parList.front() );
}

// clear this lane
void CCommonTrafficLane::Clear()
{
    incomingQueue.clear();
    participantQueue.clear();
}

void CCommonTrafficLane::UpdateParticipants(std::vector<CTrafficLight>& lightList,
                                            CTrafficLaneGroup* groups, float dt)
{
    // process incoming qeueu, trying to process as many as possible
    while(!incomingQueue.empty())
    {
        CParticipant* par = incomingQueue.front();

        // check if the participant queue is empty
        if(participantQueue.empty())
        {
            par->SetHidden(false);

            // we can just add this par to the queue
            participantQueue.push_back(par);
            incomingQueue.erase(incomingQueue.begin());
        }
        else
        {
            // let's get the participant in the back
            CParticipant* last = participantQueue.back();

            // start,end & participant positions
            wmath::Vec3 parPos = last->GetPosition();
            wmath::Vec3 traDis = (parPos - wayStart);

            float parSize = CTrafficLane::GetParticipantSize(last->GetType());
            float traLen = traDis.Length();

            // if the participant in the back has traveled a bigger distance than it's size
            // we can add a the participant from the incoming queue to the participant queue
            //if( traLen > parSize)
            if( traLen > (TRADEFS::BUMPDIST + parSize))
            {
                par->SetHidden(false);
                participantQueue.push_back(par);
                incomingQueue.erase(incomingQueue.begin());
            }
            else // we break out of the loop
                break;
        }
    }

    // process all participants in this lane
    int counter = 0;
    for( std::vector<CParticipant*>::iterator i(participantQueue.begin()), end(participantQueue.end()); i != end; ++i )
    {
        CParticipant* par = (*i);

        // do stuff based on the par state
        switch(par->GetState())
        {
            case TRADEFS::GOTOSTOPLIGHT:
                GoToStoplight(*par, counter++, dt);
            break;
            case TRADEFS::WAITATSTOPLIGHT:
                WaitStoplight(*par, lightList, dt); counter++;
            break;
            case TRADEFS::ONCROSSROAD:
                OnCrossroad(*par, groups, dt);
            break;
            case TRADEFS::GOTOEXIT:
            {
                GoToExit(*par, groups, dt);
                if(par->Remove())
                {
                    i = participantQueue.erase( i );
                }
            }

            break;
        }
    }
}

void CCommonTrafficLane::GoToStoplight(CParticipant& par, int index, float dt)
{
    // participant positions
    wmath::Vec3 parPos = par.GetPosition();

    // directions
    wmath::Vec3 laneDir = wayEnd - wayStart;
    wmath::Vec3 moveDir = (wayEnd - parPos); moveDir.Norm();
    float parSize = CTrafficLane::GetParticipantSize(par.GetType());

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Norm() - (TRADEFS::BUMPDIST + TRADEFS::CHEATLEN);
    laneLength -= parSize *  index;
    
    if( index != 0)
    {
        laneLength -= TRADEFS::BUMPDIST;
    }

    // get length between par pos and end waypoint
    float parLength = (parPos - wayStart).Length() + parSize / 2.0f;

    // check if we have reached our destination
    if(parLength > laneLength)
    {
        // this means this is the first participant
        if( index == 0)
        {
            // change state
            par.SetState(TRADEFS::WAITATSTOPLIGHT);
        }
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * CTrafficLane::GetParticipantSpeed( par.GetType()) * dt);
    }
}

void CCommonTrafficLane::WaitStoplight(CParticipant& par,std::vector<CTrafficLight>& lightList, float dt)
{
    if(lightID != -1)
    {
        // we need to check if it can proceed
        CTrafficLight& light = lightList[lightID];

        if(light.GetState() != TRADEFS::STOP)
        {
            //light.SetState(TRADEFS::STOP);
            par.SetState(TRADEFS::ONCROSSROAD);
        }

        // TODO TRAFFICLIGHT LOGIC BASED ON PARTICIPANT TYPE, LANE
    }
}

void CCommonTrafficLane::OnCrossroad(CParticipant& par, CTrafficLaneGroup* groups, float dt)
{
    // Vectors
    wmath::Vec3 parPos = par.GetPosition();
    wmath::Vec3 laneDir = wayEnd - wayStart;
    wmath::Vec3 moveDir = (wayEnd - parPos); moveDir.Norm();
    float parSize = CTrafficLane::GetParticipantSize(par.GetType());

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length();// + parSize + TRADEFS::CHEATLEN;

    // get length between par pos and end waypoint
    float parLength = (parPos - wayStart).Length();

    // check if we have reached our destination
    if(parLength > laneLength)
    {
        wmath::Vec3 end = groups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayStart();
        laneDir = end - wayStart;
        moveDir = (end - parPos);

        // get length between 2 lane waypoints, from start to end
        laneLength = laneDir.Length();

        // get length between par pos and end waypoint
        parLength = (parPos - wayStart).Length();

        // check if we have reached our destination
        laneDir.Norm();
        moveDir.Norm();

        // get new rot
        float wantRot = atan2(laneDir.x, laneDir.z);
        float curRot = par.GetRotation() * wmath::DEG2RAD;
        float difRot = wmath::ShortestAngleBetween(curRot, wantRot);
        curRot *= wmath::RAD2DEG;
        difRot *= wmath::RAD2DEG;

        if( !(difRot >= -0.1f && difRot <= 0.1f))
        {
            par.SetRotation( curRot + difRot * dt );
        }

        if(parLength > laneLength)
        {
            // change state
            par.SetState(TRADEFS::GOTOEXIT);
        }
        else
        {
            // set it's new position
            par.SetPosition(parPos + moveDir * CTrafficLane::GetParticipantSpeed( par.GetType()) * dt);
        }
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * CTrafficLane::GetParticipantSpeed( par.GetType()) * dt);
    }
}

void CCommonTrafficLane::GoToExit(CParticipant& par, CTrafficLaneGroup* groups, float dt)
{
    wmath::Vec3 start = groups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayStart();
    wmath::Vec3 end = groups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayEnd();
    wmath::Vec3 laneDir = end - start;
    wmath::Vec3 parPos = par.GetPosition();
    wmath::Vec3 moveDir = (end - parPos);

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length();

    // get length between par pos and end waypoint
    float parLength = (parPos - start).Length();

    // check if we have reached our destination
    laneDir.Norm();
    moveDir.Norm();
    
    // get new rot
    float wantRot = atan2(laneDir.x, laneDir.z);
    float curRot = par.GetRotation() * wmath::DEG2RAD;
    float difRot = wmath::ShortestAngleBetween(curRot, wantRot);
    curRot *= wmath::RAD2DEG;
    difRot *= wmath::RAD2DEG;
    
    if( !(difRot >= -0.1f && difRot <= 0.1f))
    {
        par.SetRotation( curRot + difRot * dt );
    }
    
    if(parLength > laneLength)
    {
        par.FlagForRemoval();
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * GetParticipantSpeed( par.GetType()) * dt);
    }
}

// clear this lane
void CPedestrianTrafficLane::Clear()
{
    incomingQueue.clear();
    participantQueue.clear();
    pedStart = wmath::Vec3();
    midLightID = -1;
}

void CPedestrianTrafficLane::AddParticipant(std::list<CParticipant>& parList,const TRADEFS::SimulationQueueParticipant_t& info)
{
    // create participant
    CParticipant par = CParticipant(info.type, info.fromDirection, info.toDirection, info.fromLane, pedStart, GetRotAngle(info.fromDirection));
    par.SetState(TRADEFS::GOTOSTOPLIGHT);
    par.SetHidden(false);

    // add participant to the head list
    parList.push_front( par );

    // add to this lane's queue
    incomingQueue.push_back( &parList.front() );
}

void CPedestrianTrafficLane::UpdateParticipants( std::vector<CTrafficLight>& lightList,
                        CTrafficLaneGroup* groups, float dt)
{
    // process incoming qeueu, trying to process as many as possible
    while(!incomingQueue.empty())
    {
        CParticipant* par = incomingQueue.front();

        // check if the participant queue is empty
        if(participantQueue.empty())
        {
            par->SetHidden(false);

            // we can just add this par to the queue
            participantQueue.push_back(par);
            incomingQueue.erase(incomingQueue.begin());
        }
        else
        {
//            // let's get the participant in the back
//            CParticipant* last = participantQueue.back();
//
//            // start,end & participant positions
//            wmath::Vec3 parPos = last->GetPosition();
//            wmath::Vec3 traDis = (parPos - pedStart);
//            float traLen = traDis.Length();
//            float parSize = CTrafficLane::GetParticipantSize(last->GetType());
//
//            // if the participant in the back has traveled a bigger distance than it's size
//            // we can add a the participant from the incoming queue to the participant queue
//            if( traLen > parSize)
//            {
//                par->SetHidden(false);
//                participantQueue.push_back(par);
//                incomingQueue.erase(incomingQueue.begin());
//            }
//            else // we break out of the loop
//                break;
        }
    }


    // process all pedestrians in this lane
    int counter = 0;
    for( std::vector<CParticipant*>::iterator i(participantQueue.begin()), end(participantQueue.end()); i != end; ++i )
    {
        CParticipant* par = (*i);

        // do stuff based on the par state
        switch(par->GetState())
        {
            case TRADEFS::GOTOSTOPLIGHT:
                GoToStoplight(*par, groups, counter++, dt);
            break;
            case TRADEFS::WAITATSTOPLIGHT:
                //WaitStoplight(*par, lightList, dt); counter++;
            break;
            case TRADEFS::ONCROSSROAD:
                //OnCrossroad(*par, groups, dt);
            break;
            case TRADEFS::GOTOEXIT:
            {
//                GoToExit(*par, groups, dt);
//                if(par->Remove())
//                {
//                    i = participantQueue.erase( i );
//                }
            }

            break;
        }
    }
}

wmath::Vec3 CPedestrianTrafficLane::GetPedTo(int group, int lane, CTrafficLaneGroup* groups)
{
    switch(group)
    {
        case TRADEFS::NORTH:
        {
            if( lane == TRADEFS::LANE_PEDESTRIAN_ONE)
                return groups[TRADEFS::WEST][TRADEFS::LANE_PEDESTRIAN_TWO]->GetWayStart();
            else if ( lane == TRADEFS::LANE_PEDESTRIAN_TWO)
                return groups[TRADEFS::EAST][TRADEFS::LANE_PEDESTRIAN_ONE]->GetWayStart();
        }
            break;
        case TRADEFS::SOUTH:
        {
            if( lane == TRADEFS::LANE_PEDESTRIAN_ONE)
                return groups[TRADEFS::EAST][TRADEFS::LANE_PEDESTRIAN_TWO]->GetWayStart();
            else if ( lane == TRADEFS::LANE_PEDESTRIAN_TWO)
                return groups[TRADEFS::WEST][TRADEFS::LANE_PEDESTRIAN_ONE]->GetWayStart();
        }
            break;
        case TRADEFS::EAST:
        {
            if( lane == TRADEFS::LANE_PEDESTRIAN_ONE)
                return groups[TRADEFS::NORTH][TRADEFS::LANE_PEDESTRIAN_TWO]->GetWayStart();
            else if ( lane == TRADEFS::LANE_PEDESTRIAN_TWO)
                return groups[TRADEFS::SOUTH][TRADEFS::LANE_PEDESTRIAN_ONE]->GetWayStart();
        }
            break;
        case TRADEFS::WEST:
        {
            if( lane == TRADEFS::LANE_PEDESTRIAN_ONE)
                return groups[TRADEFS::SOUTH][TRADEFS::LANE_PEDESTRIAN_TWO]->GetWayStart();
            else if ( lane == TRADEFS::LANE_PEDESTRIAN_TWO)
                return groups[TRADEFS::NORTH][TRADEFS::LANE_PEDESTRIAN_ONE]->GetWayStart();
        }
            break;
    }

    return wmath::Vec3();
}

void CPedestrianTrafficLane::GoToStoplight(CParticipant& par,
                        CTrafficLaneGroup* groups, int index, float dt)
{
    // participant positions
    wmath::Vec3 parPos = par.GetPosition();

    // get correct to position
    wmath::Vec3 wayTo = GetPedTo(par.GetFrom(), par.GetLaneFrom(), groups);

    // directions
    wmath::Vec3 laneDir = wayTo - pedStart;
    wmath::Vec3 moveDir = (wayTo - parPos); moveDir.Norm();

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length(); laneDir.Norm();
    laneLength -= (CTrafficLane::GetParticipantSize( par.GetType() ) *  index);

    // get length between par pos and start waypoint
    float parLength = (parPos - pedStart).Length();

    // check if we have reached our destination
    if(parLength > laneLength)
    {
        // this means this is the first participant
        if( index == 0)
        {
            // change state
            par.SetState(TRADEFS::WAITATSTOPLIGHT);
        }
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * CTrafficLane::GetParticipantSpeed( par.GetType()) * dt);
    }
}

void CPedestrianTrafficLane::WaitStoplight(CParticipant& par,std::vector<CTrafficLight>& lightList, float dt)
{
    if(lightID != -1)
    {
        // we need to check if it can proceed
        CTrafficLight& light = lightList[lightID];

        if(light.GetState() != TRADEFS::OFF)
        {
            light.SetState(TRADEFS::OFF);
            par.SetState(TRADEFS::ONCROSSROAD);
        }

        // TODO TRAFFICLIGHT LOGIC BASED ON PARTICIPANT TYPE, LANE
    }
}

void CPedestrianTrafficLane::OnCrossroad(CParticipant& par, CTrafficLaneGroup* groups, float dt)
{
    wmath::Vec3 end = groups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayStart();
    wmath::Vec3 laneDir = end - wayStart;
    wmath::Vec3 parPos = par.GetPosition();
    wmath::Vec3 moveDir = (end - parPos);

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length();

    // get length between par pos and end waypoint
    float parLength = (parPos - wayStart).Length();

    // check if we have reached our destination
    laneDir.Norm();
    moveDir.Norm();
    if(parLength > laneLength)
    {
        // change state
        par.SetState(TRADEFS::GOTOEXIT);
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * CTrafficLane::GetParticipantSpeed( par.GetType()) * dt);
    }
}

void CPedestrianTrafficLane::GoToExit(CParticipant& par, CTrafficLaneGroup* groups, float dt)
{
    wmath::Vec3 start = groups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayStart();
    wmath::Vec3 end = groups[par.GetTo()][TRADEFS::LANE_EXIT]->GetWayEnd();
    wmath::Vec3 laneDir = end - start;
    wmath::Vec3 parPos = par.GetPosition();
    wmath::Vec3 moveDir = (end - parPos);

    // get length between 2 lane waypoints, from start to end
    float laneLength = laneDir.Length();

    // get length between par pos and end waypoint
    float parLength = (parPos - start).Length();

    // check if we have reached our destination
    laneDir.Norm();
    moveDir.Norm();
    if(parLength > laneLength)
    {
        par.FlagForRemoval();
    }
    else
    {
        // set it's new position
        par.SetPosition(parPos + moveDir * GetParticipantSpeed( par.GetType()) * dt);
    }
}
