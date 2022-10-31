#ifndef __EVALUATOR__

#include <iostream>
#include "evaluator.h"
#include "fstream"
#endif

TEvaluator::TEvaluator()
{
    fEdgeDis = NULL;
    fNearCity = NULL;
    Ncity = 0;
    fNearNumMax = 50;
}

TEvaluator::~TEvaluator(){
    for ( int i = 0; i < Ncity; ++i ) delete[] fEdgeDis[ i ];
    delete[] fEdgeDis;

    for ( int i = 0; i < Ncity; ++i ) delete[] fNearCity[ i ];
    delete[] fNearCity;

    delete [] x;
    delete [] y;
}

void TEvaluator::setInstance( char filename[] )//似乎是读取文件的函数
{
    FILE* fp;

    int n;
    char word[ 80 ], type[ 80 ];
    printf("Start reading the data from %s\n", filename);
    fp = fopen( filename, "r" );

    /* read instance */
    for(int i=0;1<1000;i++){
        if( fscanf( fp, "%s", word ) == EOF ) break;
//        printf("Current Word is %s\n", word);
        if( strcmp( word, "DIMENSION" ) == 0 ){
//            printf("Position 0\n");
            fscanf( fp, "%s", word );
            fscanf( fp, "%d", &Ncity );
        }
        if( strcmp( word, "EDGE_WEIGHT_TYPE" ) == 0 ){
            fscanf( fp, "%s", word );
            fscanf( fp, "%s", type );
        }
        if( strcmp( word, "NODE_COORD_SECTION" ) == 0 ) break;
    }
    if( strcmp( word, "NODE_COORD_SECTION" ) != 0 ){
        printf( "Error in reading the instance\n" );
        exit(0);
    }
    printf("Start reading coordinate\n");
    x = new double [ Ncity ];
    y = new double [ Ncity ]; //节点的xy坐标
    int *checkedN = new int[Ncity];

    for( int i = 0; i < Ncity; ++i ){
        fscanf( fp, "%d", &n );
        fscanf( fp, "%s", word );
        x[ i ] = atof( word );
        fscanf( fp, "%s", word );
        y[ i ] = atof( word );
    }
    fclose(fp);
    printf("Total City number is %d\n" , Ncity);
    fEdgeDis = new int* [ Ncity ];
    for( int i = 0; i < Ncity; ++i ) fEdgeDis[ i ] = new int [ Ncity ];
    fNearCity = new int* [ Ncity ];
    for( int i = 0; i < Ncity; ++i ) fNearCity[ i ] = new int [ fNearNumMax+1 ];

    if( strcmp( type, "EUC_2D" ) == 0  ) {
        for( int i = 0; i < Ncity ; ++i )
            for( int j = 0; j < Ncity ; ++j )
                fEdgeDis[ i ][ j ]=(int)(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))+0.5); //为什么要加上0.5
    }
    else if( strcmp( type, "ATT" ) == 0  ) {
        for( int i = 0; i < Ncity; ++i ){
            for( int j = 0; j < Ncity; ++j ) {
                double r = (sqrt(((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))/10.0));
                int t = (int)r;
                if( (double)t < r ) fEdgeDis[ i ][ j ] = t+1;
                else fEdgeDis[ i ][ j ] = t;
            }
        }
    }
    else if( strcmp( type, "CEIL_2D" ) == 0  ){
    for( int i = 0; i < Ncity ; ++i )
        for( int j = 0; j < Ncity ; ++j )
            fEdgeDis[ i ][ j ]=(int)ceil(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])));
    }
    else{
        printf( "EDGE_WEIGHT_TYPE is not supported\n" );
        exit( 1 );
    }
    int ci, j1, j2, j3;
    int cityNum = 0;
    int minDis;
    for( ci = 0; ci < Ncity; ++ci ){
        for( j3 = 0; j3 < Ncity; ++j3 ) checkedN[ j3 ] = 0;
        checkedN[ ci ] = 1;
        fNearCity[ ci ][ 0 ] = ci;
        for( j1 = 1; j1 <= fNearNumMax; ++j1 ) {
            minDis = 100000000;
            for( j2 = 0; j2 < Ncity; ++j2 ){
                if( fEdgeDis[ ci ][ j2 ] <= minDis && checkedN[ j2 ] == 0 ){
                    cityNum = j2;
                    minDis = fEdgeDis[ ci ][ j2 ];
                }
            }
            fNearCity[ ci ][ j1 ] = cityNum;
            checkedN[ cityNum ] = 1;
        }
    }
    //fNearCity这个矩阵存折每个city最近的 fNearNumMax 个City
}


void TEvaluator::setInstanceDirectFromInput(double* X_position, double* Y_position, int N_city)//似乎是读取文件的函数
{
    FILE* fp;

    int n;
    char word[ 80 ], type[ 80 ];
    printf("Set Instance Direct From Input by Python Program\n");
    Ncity = N_city;

    /* read instance */
//    for(int i=0;1<1000;i++){
//        if( fscanf( fp, "%s", word ) == EOF ) break;
////        printf("Current Word is %s\n", word);
//        if( strcmp( word, "DIMENSION" ) == 0 ){
////            printf("Position 0\n");
//            fscanf( fp, "%s", word );
//            fscanf( fp, "%d", &Ncity );
//        }
//        if( strcmp( word, "EDGE_WEIGHT_TYPE" ) == 0 ){
//            fscanf( fp, "%s", word );
//            fscanf( fp, "%s", type );
//        }
//        if( strcmp( word, "NODE_COORD_SECTION" ) == 0 ) break;
//    }
//    if( strcmp( word, "NODE_COORD_SECTION" ) != 0 ){
//        printf( "Error in reading the instance\n" );
//        exit(0);
//    }
    printf("Start reading coordinate\n");
    x = new double [ Ncity ];
    y = new double [ Ncity ]; //节点的xy坐标

    int *checkedN = new int[Ncity];

    for( int i = 0; i < Ncity; ++i ){
        x[ i ] = X_position[i];
        y[ i ] = Y_position[i];
    }
    printf("Total City number is %d\n" , Ncity);
    fEdgeDis = new int* [ Ncity ];
    for( int i = 0; i < Ncity; ++i ) fEdgeDis[ i ] = new int [ Ncity ];
    fNearCity = new int* [ Ncity ];
    for( int i = 0; i < Ncity; ++i ) fNearCity[ i ] = new int [ fNearNumMax+1 ];

//    if( strcmp( type, "EUC_2D" ) == 0  ) {
//        for( int i = 0; i < Ncity ; ++i )
//            for( int j = 0; j < Ncity ; ++j )
//                fEdgeDis[ i ][ j ]=(int)(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))+0.5); //为什么要加上0.5
//    }
//    else if( strcmp( type, "ATT" ) == 0  ) {
//        for( int i = 0; i < Ncity; ++i ){
//            for( int j = 0; j < Ncity; ++j ) {
//                double r = (sqrt(((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))/10.0));
//                int t = (int)r;
//                if( (double)t < r ) fEdgeDis[ i ][ j ] = t+1;
//                else fEdgeDis[ i ][ j ] = t;
//            }
//        }
//    }
//    else if( strcmp( type, "CEIL_2D" ) == 0  ){
//        for( int i = 0; i < Ncity ; ++i )
//            for( int j = 0; j < Ncity ; ++j )
//                fEdgeDis[ i ][ j ]=(int)ceil(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])));
//    }
//    else{
//        printf( "EDGE_WEIGHT_TYPE is not supported\n" );
//        exit( 1 );
//    }
    for( int i = 0; i < Ncity ; ++i )
        for( int j = 0; j < Ncity ; ++j )
            fEdgeDis[ i ][ j ]=(int)(sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]))+0.5); //为什么要加上0.5
    int ci, j1, j2, j3;
    int cityNum = 0;
    int minDis;
    for( ci = 0; ci < Ncity; ++ci ){
        for( j3 = 0; j3 < Ncity; ++j3 ) checkedN[ j3 ] = 0;
        checkedN[ ci ] = 1;
        fNearCity[ ci ][ 0 ] = ci;
        for( j1 = 1; j1 <= fNearNumMax; ++j1 ) {
            minDis = 100000000;
            for( j2 = 0; j2 < Ncity; ++j2 ){
                if( fEdgeDis[ ci ][ j2 ] <= minDis && checkedN[ j2 ] == 0 ){
                    cityNum = j2;
                    minDis = fEdgeDis[ ci ][ j2 ];
                }
            }
            fNearCity[ ci ][ j1 ] = cityNum;
            checkedN[ cityNum ] = 1;
        }
    }
    //fNearCity这个矩阵存折每个city最近的 fNearNumMax 个City
}



void TEvaluator::doIt( TIndi& indi ){
    int d = 0;
    for( int i = 0; i < Ncity; ++i ) d += fEdgeDis[ i ][ indi.fLink[i][0] ] + fEdgeDis[ i ][ indi.fLink[i][1] ];
    indi.fEvaluationValue = d/2;
}

void TEvaluator::writeTo( FILE* fp, TIndi& indi )
{
    Array=new int[Ncity];
    int curr=0, st=0, count=0, pre=-1, next;
    while( 1 ){
        Array[ count++ ] = curr + 1;
        if( count > Ncity ){
            printf( "Invalid\n" );
            return;
        }
        if( indi.fLink[ curr ][ 0 ] == pre ) next = indi.fLink[ curr ][ 1 ];
        else next = indi.fLink[ curr ][ 0 ];

        pre = curr;
        curr = next;
        if( curr == st ) break;
    }
    if( this->checkValid( Array, indi.fEvaluationValue ) == false )
        printf( "Individual is invalid \n" );

    fprintf( fp, "%d %d\n", indi.fN, indi.fEvaluationValue );
    for( int i = 0; i < indi.fN; ++i )
        fprintf( fp, "%d ", Array[ i ] );
    fprintf( fp, "\n" );
}

void TEvaluator::writeToStdout(TIndi &indi)
{
    Array = new int[Ncity];
    int curr = 0, st = 0, count = 0, pre = -1, next;
    while (1)
    {
        Array[count++] = curr + 1;
        if (count > Ncity)
        {
            printf("Invalid\n");
            return;
        }
        if (indi.fLink[curr][0] == pre)
            next = indi.fLink[curr][1];
        else
            next = indi.fLink[curr][0];

        pre = curr;
        curr = next;
        if (curr == st)
            break;
    }
    if (this->checkValid(Array, indi.fEvaluationValue) == false)
        printf("Individual is invalid \n");

    printf("%d %d\n", indi.fN, indi.fEvaluationValue);
    for (int i = 0; i < indi.fN; ++i)
        printf("%d ", Array[i]);
    printf("\n");
}

bool TEvaluator::checkValid( int* array, int value ){
    int *check=new int[Ncity];
    for( int i = 0; i < Ncity; ++i ) check[ i ] = 0;
    for( int i = 0; i < Ncity; ++i ) ++check[ array[ i ]-1 ];
    for( int i = 0; i < Ncity; ++i )
        if( check[ i ] != 1 ) return false;
    int distance = 0;
    for( int i = 0; i < Ncity-1; ++i )
        distance += fEdgeDis[ array[ i ]-1 ][ array[ i+1 ]-1 ];

    distance += fEdgeDis[ array[ Ncity-1 ]-1 ][ array[ 0 ]-1 ];

    delete [] check;
    if( distance != value ) return false;
    return true;
}

