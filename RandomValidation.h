#ifndef K_CA_RANDOMVALIDATION_H
#define K_CA_RANDOMVALIDATION_H

#include <iostream>
#include <mutex>
#include <math.h>
#define NUMOFTRANS 400 //交易数
#define NUMOFMEMBERS 4
//委员会成员个数


typedef int network_address_t; //网络地址

// static  int Fault_Node =5;
// static  int Num_Node = 3 * Fault_Node + 3;
static  int Fault_Node =4;
static  int Num_Node = 4 * Fault_Node ;
const int k_value = 2;
// 节点数量，k值
extern std::mutex console_mutex; //互斥

#endif
