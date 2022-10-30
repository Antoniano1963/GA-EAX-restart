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

//%include "numpy.i"

//%init %{
//    import_array();
//%}
//
//%apply (double* INPLACE_ARRAY1, int DIM1) {(double* invec, int n)}

int EAX( int Npop_num, int Nch_num, int best_solution, int tmax_num, int random_num,  char* FileName);

#include "cross.h"
#include "EAX.h"
#include "environment.h"
#include "evaluator.h"
#include "indi.h"
#include "kopt.h"
#include "randomize.h"
#include "sort.h"
