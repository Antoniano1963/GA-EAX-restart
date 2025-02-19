#ifndef __ENVIRONMENT__
#include "environment.h"
#endif

#include <math.h> 

extern int gBestValue;
extern TIndi gBest;
extern int duration;

void MakeRandSol(TEvaluator* eval, TIndi& indi);
void Make2optSol(TEvaluator* eval, TIndi& indi);

TEnvironment::TEnvironment()
{
    fEvaluator = new TEvaluator();
}

TEnvironment::~TEnvironment()
{
    delete [] fIndexForMating;
    delete [] tCurPop;
    delete fEvaluator;
    delete tCross;

    int N = fEvaluator->Ncity;
    for( int i = 0; i < N; ++i ) delete [] fEdgeFreq[ i ];
    delete [] fEdgeFreq;
}

void TEnvironment::define()
{
    fEvaluator->setInstance( fFileNameTSP );
    int N = fEvaluator->Ncity;
    fIndexForMating = new int [ Npop + 1 ];  
    tCurPop = new TIndi [ Npop ];
    for ( int i = 0; i < Npop; ++i ) tCurPop[i].define( N );

    gBestValue = -1;
    gBest.define(N);

    tBest.define( N );
    tCross = new TCross( N );
    tCross->eval = fEvaluator;                 
    tCross->Npop = Npop;             

    tKopt = new TKopt( N );
    tKopt->eval = fEvaluator;
    tKopt->setInvNearList();
    fEdgeFreq = new int* [ N ]; 
    for( int i = 0; i < N; ++i ) fEdgeFreq[ i ] = new int [ N ];
    this->fTimeStart = clock();
}

void TEnvironment::doIt()
{
    this->initPop(); //初始化种群，使用2-opt方法生成基础的解
    this->init(); //初始化一些统计信息，如多少代之类的
    this->getEdgeFreq(); //应该是用来计算熵的
    this->fTimeEnd = clock();
    duration = (int)((double)(this->fTimeEnd - this->fTimeStart) / (double)CLOCKS_PER_SEC); //计算时间？ fTimeStart是代码最开始生成子代的时间，因此计算的是当前代已经总共运行了多长时间了

    while (duration < tmax) //判断会不会超时
    {
        this->setAverageBest(); //更新一些统计信息，如有多少代没有提升
        if (gBestValue == -1 || fBestValue < gBestValue)
        {
            gBestValue = fBestValue;
            gBest = tBest;
            // printf("find better solution %d\n", gBestValue);
            if (gBestValue <= this->optimum)
            {
                printf("Find optimal solution %d, exit\n", gBestValue);
                this->terminate = true;
                break;
            }
        }
        if (fCurNumOfGen % 50 == 0)
        {
            printf("%d:\t%d\t%lf\n", fCurNumOfGen, fBestValue, fAverageValue); //判断时间和打印信息
            // record time every 50 gens
            this->fTimeEnd = clock();
            duration = (int)((double)(this->fTimeEnd - this->fTimeStart) / (double)CLOCKS_PER_SEC);
            if (duration >= tmax)
                break;
        }

        if (this->terminationCondition())
            break;

        this->selectForMating();
        for (int s = 0; s < Npop; ++s)
            this->generateKids(s); //EAX所有的流程都在generateKids这个函数中

        ++fCurNumOfGen;
    }

    if (duration >= tmax)
        this->terminate = true;
}

void TEnvironment::init()
{
    fAccumurateNumCh = 0; //累计的子代数量嘛？
    fCurNumOfGen = 0;  //应该是多少代把
    fStagBest = 0;   //？
    fMaxStagBest = 0;   //？
    fStage = 1;             /* Stage I */
    fFlagC[0] = 4;          /* Diversity preservation: 1:Greedy, 2:--- , 3:Distance, 4:Entropy (see Section 4) */
    fFlagC[1] = 1;          /* Eset Type: 1:Single-AB, 2:Block2 (see Section 3) */
} 

bool TEnvironment::terminationCondition()
{
    if ( fAverageValue - fBestValue < 0.001 )  return true;
    if (fStage == 1) /* Stage I */
    {
        /* 1500/N_ch (See Section 2.2) */
        if( fStagBest == int(1500/Nch) && fMaxStagBest == 0)
        {
            /* fMaxStagBest = G/10 (See Section 2.2) */
            fMaxStagBest = int(fCurNumOfGen / 10);
        }
        /* Terminate Stage I (proceed to Stage II) */
        else if( fMaxStagBest != 0 && fMaxStagBest <= fStagBest ){ 
            fStagBest = 0;
            fMaxStagBest = 0;
            fCurNumOfGen1 = fCurNumOfGen;
            fFlagC[ 1 ] = 2;
            fStage = 2;
        }
        return false;
    }
    if (fStage == 2) /* Stage II */
    {
        /* 1500/N_ch */
        if( fStagBest == int(1500/Nch) && fMaxStagBest == 0 )
        {
            /* fMaxStagBest = G/10 (See Section 2.2) */
            fMaxStagBest = int( (fCurNumOfGen - fCurNumOfGen1) / 10 );
        }
        /* Terminate Stage II and GA */
        else if( fMaxStagBest != 0 && fMaxStagBest <= fStagBest )
        {
            return true;
        }
        return false;
    }

    return true;
}

void TEnvironment::setAverageBest()
{
    int stockBest = tBest.fEvaluationValue;
    fAverageValue = 0.0;
    fBestIndex = 0;
    fBestValue = tCurPop[0].fEvaluationValue; //难道已经排过序了吗？
    for(int i = 0; i < Npop; ++i )
    {
        fAverageValue += tCurPop[i].fEvaluationValue;
        if( tCurPop[i].fEvaluationValue < fBestValue )
        {
            fBestIndex = i; //记录最优解是哪一个？和tBest有啥区别
            fBestValue = tCurPop[i].fEvaluationValue;
        }
    }
    //
    tBest = tCurPop[ fBestIndex ]; //更新tBest?
    fAverageValue /= (double)Npop; //种群平均路由长度
    if( tBest.fEvaluationValue < stockBest )
    {
        fStagBest = 0;
        fBestNumOfGen = fCurNumOfGen;
        fBestAccumeratedNumCh = fAccumurateNumCh;
    }
    else ++fStagBest;
}

void TEnvironment::initPop(){
    for ( int i = 0; i < Npop; ++i )
    {
        tKopt->makeRandSol(tCurPop[i]); /* Make a random tour */
        tKopt->doIt(tCurPop[i]);        /* Apply the local search with the 2-opt neighborhood */
    }
}

void TEnvironment::selectForMating()
{
    /* fIndexForMating[] <-- a random permutation of 0, ..., fNumOfPop-1 */
    tRand->permutation( fIndexForMating, Npop, Npop ); 
    fIndexForMating[ Npop ] = fIndexForMating[ 0 ];
}

void TEnvironment::generateKids( int s ) //
{
    /* Note: tCurPop[fIndexForMating[s]] is replaced with a best offspring solutions in tCorss->DoIt(). 
     fEegeFreq[][] is also updated there. */
    // 这里s就已经确定了当前的两个父代
    tCross->setParents( tCurPop[fIndexForMating[s]], tCurPop[fIndexForMating[s+1]], fFlagC, Nch );  
    tCross->doIt( tCurPop[fIndexForMating[s]], tCurPop[fIndexForMating[s+1]], Nch, 1, fFlagC, fEdgeFreq );
    fAccumurateNumCh += tCross->fNumOfGeneratedCh;
}

void TEnvironment::getEdgeFreq() //应该是用来计算熵的
{
    int  k0, k1, N = fEvaluator->Ncity;
    for( int j1 = 0; j1 < N; ++j1 )
        for( int j2 = 0; j2 < N; ++j2 )
            fEdgeFreq[ j1 ][ j2 ] = 0;

    for( int i = 0; i < Npop; ++i )
        for(int j = 0; j < N; ++j ){
            k0 = tCurPop[ i ].fLink[ j ][ 0 ];
            k1 = tCurPop[ i ].fLink[ j ][ 1 ];
            ++fEdgeFreq[ j ][ k0 ];
            ++fEdgeFreq[ j ][ k1 ];
        }
}

void TEnvironment::printOn()
{
    printf("Total time: %d\n", duration);
    printf("bestval = %d, optimum = %d \n", gBestValue, this->optimum);
    fEvaluator->writeToStdout(gBest);
    if (gBestValue != -1 && gBestValue <= this->optimum)
        printf("Successful\n");
    else
        printf("Unsuccessful\n");
    fflush(stdout);
}

void TEnvironment::writeBest()
{
    FILE *fp;
    char filename[ 80 ];

    sprintf( filename, "bestSolution.txt" );
    fp = fopen( filename, "a");
    fEvaluator->writeTo( fp, gBest );
    fclose( fp );
}
