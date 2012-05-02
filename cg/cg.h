// header file of cg.cpp
// for cgtst1.ccp without dynamic alloations.

/* ----------------------- DECLARATIONS cg.h ------------------------ */

//#define  SIZE  25            /* maximum size of system ...............*/
//#define  REAL  double        /* real numbers (here double) ...........*/

//typedef  REAL  MAT[SIZE][SIZE]; /* square matrix type */
//typedef  REAL  VEC[SIZE];       /* vector type */

#include "../cg/tnt_array1d.h"
#include "../cg/tnt_array2d.h"
#include "../cg/tnt_array1d_utils.h"
#include "../cg/tnt_array2d_utils.h"

typedef double REAL;
typedef TNT::Array2D<double> MAT;
typedef TNT::Array1D<double> VEC;


int cg_method                /* Conjugate Gradient Method ............*/
                (
                 int  n,     /* Size of the linear system ............*/
                 MAT  a,     /* System matrix ........................*/
                 VEC  y,     /* right hand side ......................*/
                 VEC  x      /* solution vector ......................*/
                );           /* Error code ...........................*/

/* ---------------------------- END cg.h ---------------------------- */
