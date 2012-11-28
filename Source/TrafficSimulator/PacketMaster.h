/* 
 * File:   PacketMaster.cpp
 * Author: Mark van der Wal
 * 
 * Handles creation of network packages
 * 
 * Created on November 28, 2012, 9:53 AM
 */

#ifndef PACKETMASTER_H
#define	PACKETMASTER_H

#include <string>

class PacketMaster 
{
public:
    static std::string GetInitPackage(int startTime, int multiplier = 1);
    static std::string GetTraLightPackage(int dir, int lane, int state);
    static std::string GetLoopPackage(int lightDir, int lightLane, int type, int loopType, bool empty, int toDir, int toLane);
};

#endif	/* PACKETMASTER_H */

