#pragma once

#include <string.h>
#include <stdio.h>

class DataControl{
public:
    typedef struct _StructClientToServerInitParam{
        char numJoint, numDof, module;
    }StructClientToServerInitParam;

    typedef struct _StructClientToServer{
        char opMode, subMode, ctrlMode;
        double *desiredJoint, *desiredCartesian;
    }StructClientToServer;
    typedef struct _StructServerToClient{
        unsigned char data_index;
        int *presentJoint;//, *presentCartesian;
    }StructServerToClient;

    int opMode, numJoint, numDof, module;

    DataControl();
    ~DataControl();
    void DataReset();
    StructClientToServerInitParam ClientToServerInitParam;
    StructClientToServer ClientToServer;
    StructServerToClient ServerToClient;
};
