#ifndef _CLIENT_H_
#define _CLIENT_H_

#include"./others.h"
#include"./headers.h"

extern int gSocket;

void SetIntData2DataBlock(void *data,int intData,int *dataSize);
int SetUpClient(char *hostName,int *clientID,int *num,char clientNames[][MAX_NAME_SIZE]);
int SendRecvManager(void);

int thread(void* args);
//void SendDataC(void *data, int *datasize);
int RecvIntData(int *intData);
int ExecuteCommand(char command, int num);

void Send_R_Command();
void Send_L_Command();
void Send_J_Command();
void Send_END_Command();
void Send_N_Command();
void SendDataW(void *data,int dataSize);
void SetCharData2DataBlock(void *data,char charData,int *dataSize);

#endif
