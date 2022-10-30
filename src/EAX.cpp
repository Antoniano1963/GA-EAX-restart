//
// Created by Ada on 2022/10/30.
//

#include "EAX.h"


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
    gEnv->tmax = random_num;
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

    return 0;
}
