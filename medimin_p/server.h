#ifndef _SERVER_H_
#define _SERVER_H_
#include"./headers.h"
#include"./others.h"

#define ALL_CLIENTS   -1

int SetUpServer(int num);
void Ending(void);
int RecvIntData(int pos,int *intData);
void SendData(int pos,void *data,int dataSize);
int SendRecvManager(void);

int ExecuteCommand(char command,int pos);
void SetIntData2DataBlock(void *data,int Data,int *dataSize);
void SetCharData2DataBlock(void *data,char charData,int *dataSize);

#endif
