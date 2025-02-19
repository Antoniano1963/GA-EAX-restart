#ifndef __Cross__
#define __Cross__

#ifndef __RAND__
#include "randomize.h"
#endif

#ifndef __Sort__
#include "sort.h"
#endif

#ifndef __INDI__
#include "indi.h"
#endif

#ifndef __EVALUATOR__
#include "evaluator.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>
#include <tuple>

class TCross
{
public:
    TCross( int N );
    TCross( int N, double** edge_scores);
    ~TCross();
    void doIt(TIndi &tKid, TIndi &tPa2, int numOfKids, int flagP, int flagC[10], int **fEdgeFreq);/* Main procedure of EAX */
    void setParents(const TIndi &tPa1, const TIndi &tPa2, int flagC[10], int numOfKids);/* Set information of the parent tours */
    void setABcycle(const TIndi &parent1, const TIndi &parent2, int flagC[10], int numOfKids); /* Step 2 of EAX */

    void swap(int &x, int &y); /* Swap */
    void formABcycle();        /* Store an AB-cycle found */
    void changeSol(TIndi &tKid, int ABnum, int type); /* Apply an AB-cycle to an intermediate solution */

    void makeCompleteSol(TIndi &tKid); /* Step 5 of EAX */
    void makeUnit();                   /* Step 5-1 of EAX */
    void backToPa1(TIndi &tKid);       /* Undo the parent p_A */
    void goToBest(TIndi &tKid);        /* Modify tKid to the best offspring solution */

    void incrementEdgeFreq(int **fEdgeFreq); /* Increment fEdgeFreq[][] */
    int calAdpLoss(int **fEdgeFreq);         /* Compute the difference in the averate distance */
    double calEntLoss(int **fEdgeFreq);      /* Compute the difference in the edge entropy */

    /* Block2 */
    void setWeight(const TIndi &parent1, const TIndi &parent2);
    int calCNaive();
    void searchEset( int num );
    void addAB( int num );
    void deleteAB( int num );

    int fNumOfGeneratedCh;
    TEvaluator* eval;
    int Npop;

private:
    TIndi tBestTmp;
    int fFlagImp;
    int fN;
    int r;
    int exam;
    int examFlag;
    int flagSt;
    int flagCycle;
    int prType;
    int chDis;
    int koritsuMany;
    int bunkiMany;
    int st;
    int ci;
    int pr;
    int stock;
    int stAppear;
    int fEvalType;
    int fEsetType;
    int fNumOfABcycleInESet;
    int fNumOfABcycle; //AB cycles的总数
    int fPosiCurr;
    int fMaxNumOfABcycle; // AB cycles的最大生成数量

    int *koritsu;
    int *bunki;
    int *koriInv;
    int *bunInv;
    int *checkKoritsu;
    int *fRoute;
    int *fPermu;
    int *fC;
    int *fJun;
    int *fOrd1;
    int *fOrd2;

    int **nearData;
    int **fABcycle;

    // Speed Up Start
    int fNumOfUnit;
    int fNumOfSeg;
    int fNumOfSPL;
    int fNumOfElementInCU;
    int fNumOfSegForCenter;
    int fGainModi;
    int fNumOfModiEdge;
    int fNumOfBestModiEdge;
    int fNumOfAppliedCycle;
    int fNumOfBestAppliedCycle;

    int *fOrder;
    int *fInv;
    int *fSegUnit;
    int *fSegPosiList;
    int *LinkAPosi;
    int *fPosiSeg;
    int *fNumOfElementInUnit;
    int *fCenterUnit;
    int *fListOfCenterUnit;
    int *fSegForCenter;
    int *fGainAB;
    int *fAppliedCylce;
    int *fBestAppliedCylce;

    int **fSegment;
    int **LinkBPosi;
    int **fModiEdge;
    int **fBestModiEdge;
    // Speed Up End

    // Block2
    int fNumOfUsedAB;
    int fNumC;
    int fNumE;
    int fTmax;
    int fMaxStag;
    int fNumOfABcycleInEset;
    int fDisAB;
    int fBestNumC;
    int fBestNumE;

    int *fNumOfElementINAB;
    int *fWeightSR;
    int *fWeightC;
    int *fUsedAB;
    int *fMovedAB;
    int *fABcycleInEset;

    int **fInEffectNode;
    int **fWeightRR;
    double **edge_scores;
    std::vector<tuple<double, int>> sort_score_index;
};

#endif
