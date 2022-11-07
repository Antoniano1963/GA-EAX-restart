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


void signalHandler(int signum);
int EAX( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName);
int EAX2( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName, int N_city, double* X_position, double* Y_position);
int EAX3(int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  int N_city, double* input_vector);

#endif //GA_EAX_RESTART_EAX_H