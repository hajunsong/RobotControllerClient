#include "datacontrol.h"

DataControl::DataControl()
{
    memset(&ClientToServerInitParam, 0, sizeof(StructClientToServerInitParam));
    memset(&ClientToServer, 0, sizeof(StructClientToServer));
    memset(&ServerToClient, 0, sizeof(StructClientToServer));
    opMode = -1;
}

DataControl::~DataControl()
{
    if (ClientToServer.desiredJoint != nullptr){
        delete[] ClientToServer.desiredJoint;
    }
    if (ClientToServer.desiredCartesian != nullptr){
        delete[] ClientToServer.desiredCartesian;
    }
}

void DataControl::DataReset()
{
    memset(&ClientToServerInitParam, 0, sizeof(StructClientToServerInitParam));
    memset(&ClientToServer, 0, sizeof(StructClientToServer));
    memset(&ServerToClient, 0, sizeof(StructClientToServer));
}

