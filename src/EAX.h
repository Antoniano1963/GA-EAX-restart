//
// Created by Ada on 2022/10/30.
//

#ifndef GA_EAX_RESTART_EAX_H
#define GA_EAX_RESTART_EAX_H
#ifndef __ENVIRONMENT__
#include "environment.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <csignal>
#include <iostream>
#include <unistd.h>
using namespace std;
int gBestValue = -1; // global best value
TIndi gBest; // global best solution
int optimum; // optimum cost
int duration; // used time

void signalHandler(int signum);
int EAX( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName);


#endif //GA_EAX_RESTART_EAX_H