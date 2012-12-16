#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=DebugNix
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1557457996/PacketMaster.o \
	${OBJECTDIR}/_ext/1010192629/Mat3.o \
	${OBJECTDIR}/_ext/725317724/TDWFile.o \
	${OBJECTDIR}/_ext/1189809995/RuneSocketUtil.o \
	${OBJECTDIR}/_ext/1010192629/WildMath.o \
	${OBJECTDIR}/_ext/716058438/Imgutil.o \
	${OBJECTDIR}/_ext/1189809995/BaseSocket.o \
	${OBJECTDIR}/_ext/1189809995/RuneDataSocket.o \
	${OBJECTDIR}/_ext/725317724/TDWLoader.o \
	${OBJECTDIR}/_ext/1010192629/Vec2.o \
	${OBJECTDIR}/_ext/1557457996/main.o \
	${OBJECTDIR}/_ext/1100166017/Texture2D.o \
	${OBJECTDIR}/_ext/1557457996/CSimulationController.o \
	${OBJECTDIR}/_ext/1557457996/jsoncpp.o \
	${OBJECTDIR}/_ext/1010192629/Mat4.o \
	${OBJECTDIR}/_ext/1557457996/CSimulationModel.o \
	${OBJECTDIR}/_ext/1010192629/Quat.o \
	${OBJECTDIR}/_ext/1557457996/CTrafficLaneGroup.o \
	${OBJECTDIR}/_ext/1557457996/CSimulationView.o \
	${OBJECTDIR}/_ext/1557457996/CApplication.o \
	${OBJECTDIR}/_ext/1557457996/Util.o \
	${OBJECTDIR}/_ext/1557457996/CParticipant.o \
	${OBJECTDIR}/_ext/1189809995/RuneSocketSet.o \
	${OBJECTDIR}/_ext/1557457996/glew.o \
	${OBJECTDIR}/_ext/1189809995/RuneListenSocket.o \
	${OBJECTDIR}/_ext/1557457996/CTrafficLane.o \
	${OBJECTDIR}/_ext/1010192629/Vec3.o \
	${OBJECTDIR}/_ext/1557457996/Timer.o \
	${OBJECTDIR}/_ext/1557457996/CNetworkView.o \
	${OBJECTDIR}/_ext/1557457996/Camera.o \
	${OBJECTDIR}/_ext/1557457996/CTrafficLight.o \
	${OBJECTDIR}/_ext/1100166017/TexturesCube.o \
	${OBJECTDIR}/_ext/1189809995/RuneSocketError.o \
	${OBJECTDIR}/_ext/1557457996/CStaticScene.o \
	${OBJECTDIR}/_ext/716058438/Shader.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lglfw -lGLEW

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficsimulator

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficsimulator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficsimulator ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1557457996/PacketMaster.o: ../../../Source/TrafficSimulator/PacketMaster.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/PacketMaster.o ../../../Source/TrafficSimulator/PacketMaster.cpp

${OBJECTDIR}/_ext/1010192629/Mat3.o: ../../../Source/TrafficSimulator/Math/Mat3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1010192629
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1010192629/Mat3.o ../../../Source/TrafficSimulator/Math/Mat3.cpp

${OBJECTDIR}/_ext/725317724/TDWFile.o: ../../../Source/TrafficSimulator/TDW/TDWFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/725317724
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/725317724/TDWFile.o ../../../Source/TrafficSimulator/TDW/TDWFile.cpp

${OBJECTDIR}/_ext/1189809995/RuneSocketUtil.o: ../../../Source/TrafficSimulator/Network/RuneSocketUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1189809995
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1189809995/RuneSocketUtil.o ../../../Source/TrafficSimulator/Network/RuneSocketUtil.cpp

${OBJECTDIR}/_ext/1010192629/WildMath.o: ../../../Source/TrafficSimulator/Math/WildMath.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1010192629
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1010192629/WildMath.o ../../../Source/TrafficSimulator/Math/WildMath.cpp

${OBJECTDIR}/_ext/716058438/Imgutil.o: ../../../Source/TrafficSimulator/Renderer/Imgutil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/716058438
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/716058438/Imgutil.o ../../../Source/TrafficSimulator/Renderer/Imgutil.cpp

${OBJECTDIR}/_ext/1189809995/BaseSocket.o: ../../../Source/TrafficSimulator/Network/BaseSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1189809995
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1189809995/BaseSocket.o ../../../Source/TrafficSimulator/Network/BaseSocket.cpp

${OBJECTDIR}/_ext/1189809995/RuneDataSocket.o: ../../../Source/TrafficSimulator/Network/RuneDataSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1189809995
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1189809995/RuneDataSocket.o ../../../Source/TrafficSimulator/Network/RuneDataSocket.cpp

${OBJECTDIR}/_ext/725317724/TDWLoader.o: ../../../Source/TrafficSimulator/TDW/TDWLoader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/725317724
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/725317724/TDWLoader.o ../../../Source/TrafficSimulator/TDW/TDWLoader.cpp

${OBJECTDIR}/_ext/1010192629/Vec2.o: ../../../Source/TrafficSimulator/Math/Vec2.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1010192629
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1010192629/Vec2.o ../../../Source/TrafficSimulator/Math/Vec2.cpp

${OBJECTDIR}/_ext/1557457996/main.o: ../../../Source/TrafficSimulator/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/main.o ../../../Source/TrafficSimulator/main.cpp

${OBJECTDIR}/_ext/1100166017/Texture2D.o: ../../../Source/TrafficSimulator/Renderer/Textures/Texture2D.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1100166017
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1100166017/Texture2D.o ../../../Source/TrafficSimulator/Renderer/Textures/Texture2D.cpp

${OBJECTDIR}/_ext/1557457996/CSimulationController.o: ../../../Source/TrafficSimulator/CSimulationController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CSimulationController.o ../../../Source/TrafficSimulator/CSimulationController.cpp

${OBJECTDIR}/_ext/1557457996/jsoncpp.o: ../../../Source/TrafficSimulator/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/jsoncpp.o ../../../Source/TrafficSimulator/jsoncpp.cpp

${OBJECTDIR}/_ext/1010192629/Mat4.o: ../../../Source/TrafficSimulator/Math/Mat4.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1010192629
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1010192629/Mat4.o ../../../Source/TrafficSimulator/Math/Mat4.cpp

${OBJECTDIR}/_ext/1557457996/CSimulationModel.o: ../../../Source/TrafficSimulator/CSimulationModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CSimulationModel.o ../../../Source/TrafficSimulator/CSimulationModel.cpp

${OBJECTDIR}/_ext/1010192629/Quat.o: ../../../Source/TrafficSimulator/Math/Quat.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1010192629
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1010192629/Quat.o ../../../Source/TrafficSimulator/Math/Quat.cpp

${OBJECTDIR}/_ext/1557457996/CTrafficLaneGroup.o: ../../../Source/TrafficSimulator/CTrafficLaneGroup.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CTrafficLaneGroup.o ../../../Source/TrafficSimulator/CTrafficLaneGroup.cpp

${OBJECTDIR}/_ext/1557457996/CSimulationView.o: ../../../Source/TrafficSimulator/CSimulationView.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CSimulationView.o ../../../Source/TrafficSimulator/CSimulationView.cpp

${OBJECTDIR}/_ext/1557457996/CApplication.o: ../../../Source/TrafficSimulator/CApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CApplication.o ../../../Source/TrafficSimulator/CApplication.cpp

${OBJECTDIR}/_ext/1557457996/Util.o: ../../../Source/TrafficSimulator/Util.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/Util.o ../../../Source/TrafficSimulator/Util.cpp

${OBJECTDIR}/_ext/1557457996/CParticipant.o: ../../../Source/TrafficSimulator/CParticipant.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CParticipant.o ../../../Source/TrafficSimulator/CParticipant.cpp

${OBJECTDIR}/_ext/1189809995/RuneSocketSet.o: ../../../Source/TrafficSimulator/Network/RuneSocketSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1189809995
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1189809995/RuneSocketSet.o ../../../Source/TrafficSimulator/Network/RuneSocketSet.cpp

${OBJECTDIR}/_ext/1557457996/glew.o: ../../../Source/TrafficSimulator/glew.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/glew.o ../../../Source/TrafficSimulator/glew.cpp

${OBJECTDIR}/_ext/1189809995/RuneListenSocket.o: ../../../Source/TrafficSimulator/Network/RuneListenSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1189809995
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1189809995/RuneListenSocket.o ../../../Source/TrafficSimulator/Network/RuneListenSocket.cpp

${OBJECTDIR}/_ext/1557457996/CTrafficLane.o: ../../../Source/TrafficSimulator/CTrafficLane.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CTrafficLane.o ../../../Source/TrafficSimulator/CTrafficLane.cpp

${OBJECTDIR}/_ext/1010192629/Vec3.o: ../../../Source/TrafficSimulator/Math/Vec3.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1010192629
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1010192629/Vec3.o ../../../Source/TrafficSimulator/Math/Vec3.cpp

${OBJECTDIR}/_ext/1557457996/Timer.o: ../../../Source/TrafficSimulator/Timer.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/Timer.o ../../../Source/TrafficSimulator/Timer.cpp

${OBJECTDIR}/_ext/1557457996/CNetworkView.o: ../../../Source/TrafficSimulator/CNetworkView.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CNetworkView.o ../../../Source/TrafficSimulator/CNetworkView.cpp

${OBJECTDIR}/_ext/1557457996/Camera.o: ../../../Source/TrafficSimulator/Camera.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/Camera.o ../../../Source/TrafficSimulator/Camera.cpp

${OBJECTDIR}/_ext/1557457996/CTrafficLight.o: ../../../Source/TrafficSimulator/CTrafficLight.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CTrafficLight.o ../../../Source/TrafficSimulator/CTrafficLight.cpp

${OBJECTDIR}/_ext/1100166017/TexturesCube.o: ../../../Source/TrafficSimulator/Renderer/Textures/TexturesCube.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1100166017
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1100166017/TexturesCube.o ../../../Source/TrafficSimulator/Renderer/Textures/TexturesCube.cpp

${OBJECTDIR}/_ext/1189809995/RuneSocketError.o: ../../../Source/TrafficSimulator/Network/RuneSocketError.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1189809995
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1189809995/RuneSocketError.o ../../../Source/TrafficSimulator/Network/RuneSocketError.cpp

${OBJECTDIR}/_ext/1557457996/CStaticScene.o: ../../../Source/TrafficSimulator/CStaticScene.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1557457996
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1557457996/CStaticScene.o ../../../Source/TrafficSimulator/CStaticScene.cpp

${OBJECTDIR}/_ext/716058438/Shader.o: ../../../Source/TrafficSimulator/Renderer/Shader.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/716058438
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -I../../../Source/Libs/include -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/716058438/Shader.o ../../../Source/TrafficSimulator/Renderer/Shader.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficsimulator

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
