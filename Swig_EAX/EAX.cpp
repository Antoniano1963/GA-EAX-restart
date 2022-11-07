//
// Created by Ada on 2022/10/30.
//

#include "EAX.h"

using namespace std;
int gBestValue = -1; // global best value
TIndi gBest; // global best solution
int optimum; // optimum cost
int duration; // used time

void signalHandler(int signum)
{
    cout << endl
         << "Signal (" << signum << ") received.\n";
    cout << endl;

    printf("Total time: %d\n", duration);
    printf("bestval = %d, optimum = %d \n", gBestValue, optimum);

    int Ncity = gBest.fN;
    int *Array = new int[Ncity];
    int curr = 0, st = 0, count = 0, pre = -1, next;
    while (1)
    {
        Array[count++] = curr + 1;
        if (count > Ncity)
        {
            printf("Invalid\n");
            return;
        }
        if (gBest.fLink[curr][0] == pre)
            next = gBest.fLink[curr][1];
        else
            next = gBest.fLink[curr][0];

        pre = curr;
        curr = next;
        if (curr == st)
            break;
    }
    printf("%d %d\n", gBest.fN, gBest.fEvaluationValue);
    for (int i = 0; i < gBest.fN; ++i)
        printf("%d ", Array[i]);
    printf("\n");

    if (gBestValue != -1 && gBestValue <= optimum)
        printf("Successful\n");
    else
        printf("Unsuccessful\n");
    fflush(stdout);

    exit(signum);
}

int EAX( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName)
{
    char *cwd = get_current_dir_name();
    cout << "Current working directory: " << cwd << endl;
    free(cwd);
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    TEnvironment* gEnv = new TEnvironment();
    gEnv->fFileNameTSP=(char*)malloc(100);

    // ./GA-EAX-restart tsp_file NPOP NCH optimum tmax
    // default: 100, 30, -1(unknown optimum), 3600
//    if(argc != 7)
//    {
//        cout << "./GA-EAX-restart tsp_file NPOP NCH optimum tmax seed";
//        exit(-1);
//    }
    gEnv->fFileNameTSP = FileName;
    gEnv->Npop = Npop_num;
    gEnv->Nch = Nch_num;
    optimum = gEnv->optimum = best_solution;
    gEnv->tmax = tmax_num;
    InitURandom(random_num);
    gEnv->terminate = false;

    cout<<"Initialization ..."<<endl;
    gEnv->define();
    //初始化问题
    for (int n = 0; n < 1000000; ++n)
    {
        printf("Run %d\n", n);
        gEnv->doIt();//主函数
        if (gEnv->terminate) break;
    }
    gEnv->printOn();
    int bestVal = gEnv->getBestVal();

    return bestVal;
}

//int EAX2( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName, int N_city, double* X_position, double* Y_position)
//{
//    char *cwd = get_current_dir_name();
//    cout << "Current working directory: " << cwd << endl;
//    free(cwd);
//    signal(SIGTERM, signalHandler);
//    signal(SIGINT, signalHandler);
//
//    TEnvironment* gEnv = new TEnvironment();
//    gEnv->fFileNameTSP=(char*)malloc(100);
//
//    // ./GA-EAX-restart tsp_file NPOP NCH optimum tmax
//    // default: 100, 30, -1(unknown optimum), 3600
////    if(argc != 7)
////    {
////        cout << "./GA-EAX-restart tsp_file NPOP NCH optimum tmax seed";
////        exit(-1);
////    }
//    gEnv->fFileNameTSP = FileName;
//    gEnv->Npop = Npop_num;
//    gEnv->Nch = Nch_num;
//    optimum = gEnv->optimum = best_solution;
//    gEnv->tmax = tmax_num;
//    InitURandom(random_num);
//    gEnv->terminate = false;
//
//    cout<<"Initialization ..."<<endl;
////    gEnv->define();
//    gEnv->defineDirectFromInput(X_position, Y_position, N_city, );
//    //初始化问题
//    for (int n = 0; n < 1000000; ++n)
//    {
//        printf("Run %d\n", n);
//        gEnv->doIt();//主函数
//        if (gEnv->terminate) break;
//    }
//    gEnv->printOn();
//    int bestVal = gEnv->getBestVal();
////    printf("X_position is: [");
////    for(int i=0;i<N_city;i++) {
////        printf("%d, ", int(X_position[i]));
////    }
////    printf("]\n");
////    printf("Y_position is: [");
////    for(int i=0;i<N_city;i++) {
////        printf("%d, ", int(Y_position[i]));
////    }
////    printf("]\n");
//
//    return bestVal;
//}

int EAX3(int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  int N_city, double* input_vector)
{
    char *cwd = get_current_dir_name();
    cout << "Current working directory: " << cwd << endl;
    free(cwd);
    signal(SIGTERM, signalHandler);
    signal(SIGINT, signalHandler);

    TEnvironment* gEnv = new TEnvironment();
    gEnv->fFileNameTSP=(char*)malloc(100);
    double* X_position = new double[N_city];
    double* Y_position = new double[N_city];
    double** Edge_Score = new double* [N_city];
    for(int i=0;i<N_city; i++){
        Edge_Score[i] = new double [N_city];
        X_position[i] = input_vector[i];
        Y_position[i] = input_vector[N_city+i];
    }
    for(int i=0;i<N_city;i++){
        for(int j=0;j<N_city;j++){
            Edge_Score[i][j] = input_vector[(2+i)*N_city + j];
        }
    }

    cout << "Test Number is" <<endl;
    cout << Edge_Score[N_city-1][N_city-2] << endl;

    // ./GA-EAX-restart tsp_file NPOP NCH optimum tmax
    // default: 100, 30, -1(unknown optimum), 3600
//    if(argc != 7)
//    {
//        cout << "./GA-EAX-restart tsp_file NPOP NCH optimum tmax seed";
//        exit(-1);
//    }
//    gEnv->fFileNameTSP = FileName;
    gEnv->Npop = Npop_num;
    gEnv->Nch = Nch_num;
    optimum = gEnv->optimum = best_solution;
    gEnv->tmax = tmax_num;
    InitURandom(random_num);
    gEnv->terminate = false;

    cout<<"Initialization ..."<<endl;
//    gEnv->define();
    gEnv->defineDirectFromInput(X_position, Y_position, N_city, Edge_Score);
    //初始化问题
    for (int n = 0; n < 1000000; ++n)
    {
        printf("Run %d\n", n);
        gEnv->doIt();//主函数
        if (gEnv->terminate) break;
    }
    gEnv->printOn();
    int bestVal = gEnv->getBestVal();
//    printf("X_position is: [");
//    for(int i=0;i<N_city;i++) {
//        printf("%d, ", int(X_position[i]));
//    }
//    printf("]\n");
//    printf("Y_position is: [");
//    for(int i=0;i<N_city;i++) {
//        printf("%d, ", int(Y_position[i]));
//    }
//    printf("]\n");

    return bestVal;
}
