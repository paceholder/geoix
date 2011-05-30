/* -------------------------- MODULE cg.cpp -------------------------- */

/***********************************************************************
*                                                                      *
* Conjugate Gradient Method (CG Method)                                *
* -------------------------------------                                *
*                                                                      *
* Programming language: ANSI C                                         *
* Compiler:             Turbo C 2.0                                    *
* Computer:             IBM PS/2 70 with 80387                         *
* Sources:              [BUNS85], [SCHW], [MAES84], [BIBLI 11].        *
* Author:               Juergen Dietel, Computer Center, RWTH Aachen   *
* Date:                 7.31.1992                                      *
*                                                                      *
*             C++ version by J-P Moreau (without dynamic allocations). *
***********************************************************************/
#include "cg.h"              /* for REAL, MAT, VEC ...................*/

#define  ZERO      0
#define  MACH_EPS  2e-16     /* convenient for double type on a PC    */

int cg_method                /* Conjugate Gradient Method ............*/
                (
                 int  n,     /* Size of the linear system ............*/
                 MAT  a,     /* System matrix ........................*/
                 VEC  y,     /* right hand side ......................*/
                 VEC  x      /* solution vector ......................*/
                )            /* Error code ...........................*/
/* original name: cg_verfahren()                                      */
/***********************************************************************
* CG solves the linear system                                          *
*                         A * X = Y                                    *
* for a symmetric, positive definite matrix A via the conjugate        *
* gradient method.                                                     *
*                                                                      *
* Input parameters:                                                    *
* =================                                                    *
* n  Size of the linear system                                         *
* a  [0..n-1,0..n-1] system matrix A. Only the upper triangle of A is  *
*    used.                                                             *
* y  [0..n-1] vector of the right hand side                            *
*                                                                      *
* Output parameters:                                                   *
* ==================                                                   *
* x  [0..n-1] vector giving the solution                               *
*                                                                      *
* Return value:                                                        *
* =============                                                        *
* = 0: all is ok                                                       *
* = 1: n < 2 or other disallowed input parameters                      *
* = 2: memory exceeded                                                 *
*                                                                      *
* global names used:                                                   *
* ==================                                                   *
* ZERO, MACH_EPS, MAT, REAL, VEC.                                      *
***********************************************************************/
{
  VEC  d(n),            /* [0..n-1] auxiliary vectors d and g            */
       g(n),            /*                                               */
       AmalD(n);        /* [0..n-1] auxiliary vector A * d               */
  REAL alpha,        /* coefficient                                   */
       beta,         /* coefficient                                   */
       dividend,     /* numerator and denominator of a fraction,      */
       divisor,      /* respectively, used to compute alpha, beta     */
       hilf,         /* auxiliary variables                           */
       hilf2,        /*                                               */
       abstand,      /* distance of two successive approximations     */
                     /* for the solution vector x (taken in the       */
                     /* euclidean norm)                               */
       xnorm;        /* euklidean norm of x                           */
  int  k, i, j;      /* loop variables                                */


  if (n < 2)                              /* invalid parameter?       */
    return 1;

  for (i = n - 1; i >= 0; i--)            /* Matrix A empty ?         */
    if (a[i] == NULL)                     /* disallowed  !            */
      return 1;

  /*------------------------------------------------------------------*/
  /* start with x at the origin                                       */
  /*------------------------------------------------------------------*/

  for (i = n - 1; i >= 0; i--)
    x[i] = ZERO;


  /*------------------------------------------------------------------*/
  /* initialize  d and g :                                            */
  /* d = -g = -(a*x - y) = y (since x = 0)                            */
  /*------------------------------------------------------------------*/

  for (i = n - 1; i >= 0; i--)
    hilf = y[i],
    d[i] = hilf,
    g[i] = -hilf;



  /*------------------------------------------------------------------*/
  /* perform at most n steps of the CG Method                         */
  /*------------------------------------------------------------------*/

  for (k = n; k > 0; k--)
  {


    /*----------------------------------------------------------------*/
    /* compute new alpha:                                             */
    /* alpha = -(d(transp) * g) / (d(transp) * (a * d))               */
    /*----------------------------------------------------------------*/


    dividend = ZERO;
    divisor  = ZERO;

    for (i = n - 1; i >= 0; i--)
    {
      dividend += d[i] * g[i];
      for (j = 0, hilf = ZERO; j < i; j++)
        hilf += a[j][i] * d[j];
      for (j = i; j < n; j++)
        hilf += a[i][j] * d[j];
      AmalD[i] = hilf;
      divisor += d[i] * hilf;
    }

    if (divisor == ZERO)
    {
      return 0;
    }

    alpha = -dividend / divisor;


    /*----------------------------------------------------------------*/
    /* compute the norm of x und  alpha * d  and find a new x:        */
    /* x  =  x + alpha * d, then check whether x is close enough,     */
    /* in order to stop the process before n complete steps           */
    /*----------------------------------------------------------------*/

    xnorm   = ZERO;
    abstand = ZERO;

    for (i = n - 1; i >= 0; i--)
      hilf    =  x[i],
      xnorm   += hilf*hilf,
      hilf2   =  alpha * d[i],
      abstand += hilf2*hilf2,
      x[i]    =  hilf + hilf2;

    if (abstand < MACH_EPS * xnorm)
    {
      return 0;
    }


    /*----------------------------------------------------------------*/
    /* compute new g:   g  =  g + alpha * (a * d)                     */
    /*----------------------------------------------------------------*/

    for (i = n - 1; i >= 0; i--)
      g[i] += alpha * AmalD[i];


    /*----------------------------------------------------------------*/
    /* compute new beta :                                             */
    /* beta = (g(transp) * (a * d)) / (d(transp) * (a * d))           */
    /*----------------------------------------------------------------*/

    dividend = ZERO;

    for (i = n - 1; i >= 0; i--)
      dividend += g[i] * AmalD[i];

    beta = dividend / divisor;


    /*----------------------------------------------------------------*/
    /* compute new d :   d  =  - g + beta * d                         */
    /*----------------------------------------------------------------*/

    for (i = n - 1; i >= 0; i--)
      d[i] = -g[i] + beta * d[i];


  }

  return 0;
}

/* ---------------------------- END cg.cpp -------------------------- */
