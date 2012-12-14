/*
 * File:   PacketMaster.cpp
 * Author: Mark van der Wal
 *
 * Handles creation of network packages
 *
 * Created on November 28, 2012, 9:53 AM
 */

#include "PacketMaster.h"
#include "TrafficDefs.h"
#include <sstream>

// TODO change starttime to correct representation
std::string  PacketMaster::GetInitPackage(int startTime, int multiplier)
{
    std::stringstream strStream;

    int hours = (startTime / 3600) % 24;
    int min = startTime % 60;

    // create message
    strStream << "[{ \"starttime\": \"" << hours << ":" << min << "\"}, \n";
    strStream << "{ \"multiplier\": "  << multiplier << "}]";

    return strStream.str();
}

std::string  PacketMaster::GetTraLightPackage(int dir, int lane, int state)
{
    std::stringstream strStream;

    // light
    strStream << "[{\"light\": \"" << GetDir(dir) << lane << "\", ";

    //state
    strStream << "\"state\": \"" << GetLightState(state) << "\"}]\n";

   return strStream.str();
}

std::string  PacketMaster::GetLoopPackage(int lightDir, int lightLane,
        int type, int loopType, int empty, int toDir, int toLane)
{
    std::stringstream strStream;

    strStream << "[{\n"
    // light
            << "\"light\": " << "\"" << GetDir(lightDir) << lightLane << "\",\n"
    //type
            << "\"type\": " << "\"" << GetType(type) << "\",\n"
    // loop
            << "\"loop\": " << "\"" << GetLoop(loopType) << "\",\n"
    // empty
            << "\"empty\": " << GetEmpty(empty) << ",\n"
    // to
            << "\"to\": " << "\"" << GetDir(toDir) << toLane << "\"\n";

    strStream << "}]";

    return strStream.str();
}

std::string PacketMaster::GetEmpty(int e)
{
    switch(e)
    {
        case 0:
            return "false";
        case 1:
            return "true";
        default:
            return "null";
    }
}

std::string PacketMaster::GetLoop(int l)
{
    switch(l)
    {
        case 0:
            return "close";
        case 1:
            return "far";
        default:
            return "null";
    }
}

std::string PacketMaster::GetType(int type)
{
    switch(type)
    {
        case TRADEFS::CAR:
            return "car";
        case TRADEFS::BUS:
            return "bus";
        case TRADEFS::PEDESTRIAN:
            return "pedestrian";
        case TRADEFS::BIKE:
            return "bicycle";
        case -1:
            return "other";
        default:
            return "null";
    }
}

std::string PacketMaster::GetDir(int dir)
{
    switch(dir)
    {
        case TRADEFS::NORTH:
            return "N";
        case TRADEFS::SOUTH:
            return "S";
        case TRADEFS::WEST:
            return "W";
        case TRADEFS::EAST:
            return "E";
        default:
            return "null";
    }
}

std::string PacketMaster::GetLightState(int state)
{
    switch(state)
    {
        case TRADEFS::PROCEED:
            return "green";
        case TRADEFS::STOP:
            return "red";
        case TRADEFS::STOP_ALMOST:
            return "yellow";
        case TRADEFS::BLINKING:
            return "blink";
        case TRADEFS::OFF:
            return "off";
        default:
            return "null";
    }
}
