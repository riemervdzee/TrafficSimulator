/* 
 * File:   PacketMaster.cpp
 * Author: Mark van der Wal
 * 
 * Handles creation of network packages
 * 
 * Created on November 28, 2012, 9:53 AM
 */

#include "PacketMaster.h"

std::string  PacketMaster::GetInitPackage(int startTime, int multiplier)
{
    return std::string("Init");
}

std::string  PacketMaster::GetTraLightPackage(int dir, int lane, int state)
{
   return std::string("TrafficLight"); 
}

std::string  PacketMaster::GetLoopPackage(int lightDir, int lightLane, 
        int type, int loopType, bool empty, int toDir, int toLane)
{
    return std::string("Deelnemer");
}