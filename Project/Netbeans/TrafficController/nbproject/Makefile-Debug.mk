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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/1329216428/jsoncpp.o \
	${OBJECTDIR}/_ext/178741075/BaseSocket.o \
	${OBJECTDIR}/_ext/1329216428/main.o \
	${OBJECTDIR}/_ext/178741075/RuneSocketUtil.o \
	${OBJECTDIR}/_ext/1329216428/cConsoleView.o \
	${OBJECTDIR}/_ext/1329216428/cSimulationModel.o \
	${OBJECTDIR}/_ext/1329216428/cNetworkView.o \
	${OBJECTDIR}/_ext/1329216428/cTrafficController.o \
	${OBJECTDIR}/_ext/178741075/RuneSocketError.o \
	${OBJECTDIR}/_ext/1329216428/PacketMaster.o \
	${OBJECTDIR}/_ext/178741075/RuneListenSocket.o \
	${OBJECTDIR}/_ext/178741075/RuneSocketSet.o \
	${OBJECTDIR}/_ext/178741075/RuneDataSocket.o


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
LDLIBSOPTIONS=-lconio

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficcontroller

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficcontroller: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficcontroller ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/1329216428/jsoncpp.o: ../../../Source/TrafficController/jsoncpp.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1329216428
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1329216428/jsoncpp.o ../../../Source/TrafficController/jsoncpp.cpp

${OBJECTDIR}/_ext/178741075/BaseSocket.o: ../../../Source/TrafficController/Network/BaseSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/178741075
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/178741075/BaseSocket.o ../../../Source/TrafficController/Network/BaseSocket.cpp

${OBJECTDIR}/_ext/1329216428/main.o: ../../../Source/TrafficController/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1329216428
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1329216428/main.o ../../../Source/TrafficController/main.cpp

${OBJECTDIR}/_ext/178741075/RuneSocketUtil.o: ../../../Source/TrafficController/Network/RuneSocketUtil.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/178741075
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/178741075/RuneSocketUtil.o ../../../Source/TrafficController/Network/RuneSocketUtil.cpp

${OBJECTDIR}/_ext/1329216428/cConsoleView.o: ../../../Source/TrafficController/cConsoleView.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1329216428
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1329216428/cConsoleView.o ../../../Source/TrafficController/cConsoleView.cpp

${OBJECTDIR}/_ext/1329216428/cSimulationModel.o: ../../../Source/TrafficController/cSimulationModel.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1329216428
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1329216428/cSimulationModel.o ../../../Source/TrafficController/cSimulationModel.cpp

${OBJECTDIR}/_ext/1329216428/cNetworkView.o: ../../../Source/TrafficController/cNetworkView.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1329216428
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1329216428/cNetworkView.o ../../../Source/TrafficController/cNetworkView.cpp

${OBJECTDIR}/_ext/1329216428/cTrafficController.o: ../../../Source/TrafficController/cTrafficController.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1329216428
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1329216428/cTrafficController.o ../../../Source/TrafficController/cTrafficController.cpp

${OBJECTDIR}/_ext/178741075/RuneSocketError.o: ../../../Source/TrafficController/Network/RuneSocketError.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/178741075
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/178741075/RuneSocketError.o ../../../Source/TrafficController/Network/RuneSocketError.cpp

${OBJECTDIR}/_ext/1329216428/PacketMaster.o: ../../../Source/TrafficController/PacketMaster.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1329216428
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1329216428/PacketMaster.o ../../../Source/TrafficController/PacketMaster.cpp

${OBJECTDIR}/_ext/178741075/RuneListenSocket.o: ../../../Source/TrafficController/Network/RuneListenSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/178741075
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/178741075/RuneListenSocket.o ../../../Source/TrafficController/Network/RuneListenSocket.cpp

${OBJECTDIR}/_ext/178741075/RuneSocketSet.o: ../../../Source/TrafficController/Network/RuneSocketSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/178741075
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/178741075/RuneSocketSet.o ../../../Source/TrafficController/Network/RuneSocketSet.cpp

${OBJECTDIR}/_ext/178741075/RuneDataSocket.o: ../../../Source/TrafficController/Network/RuneDataSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/178741075
	${RM} $@.d
	$(COMPILE.cc) -g -DJSON_IS_AMALGAMATION -I../../../Source/Libs/JSoncpp-0.6 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/178741075/RuneDataSocket.o ../../../Source/TrafficController/Network/RuneDataSocket.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/trafficcontroller

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
