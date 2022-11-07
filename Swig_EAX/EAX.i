%module EAX

%{
#define SWIG_FILE_WITH_INIT
#include "cross.h"
#include "EAX.h"
#include "environment.h"
#include "evaluator.h"
#include "indi.h"
#include "kopt.h"
#include "randomize.h"
#include "sort.h"
%}

/*  include the numpy typemaps */
%include "numpy.i"
/*  need this for correct module initialization */
%init %{
import_array();
%}

/*  typemaps for the two arrays, the second will be modified in-place */
%apply (double* IN_ARRAY1, int DIM1) {(double * input_vector, int size_in1)}
//%apply (double* IN_ARRAY1, int DIM1) {(double * Y_position, int size_in22)}
//%apply (double* IN_ARRAY2, int DIM1, int DIM2) {(double** Edge_Scores, int size_int231, int size_int232)}

int EAX( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName);
%inline %{
int EAX3( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  int N_city, double* input_vector, int size_in1){
    /*  calls the original funcion, providing only the size of the first */
    EAX3(Npop_num, Nch_num, best_solution, tmax_num, random_num, N_city, input_vector);
}
%}
//
//%inline %{
//int EAX2( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName,int N_city, double* X_position, int size_in1, double* Y_position, int size_in2){
//    /*  calls the original funcion, providing only the size of the first */
//    EAX2(Npop_num, Nch_num, best_solution, tmax_num, random_num,  FileName, N_city, X_position, Y_position);
//}
//%}
#include "cross.h"
#include "EAX.h"
#include "environment.h"
#include "evaluator.h"
#include "indi.h"
#include "kopt.h"
#include "randomize.h"
#include "sort.h"