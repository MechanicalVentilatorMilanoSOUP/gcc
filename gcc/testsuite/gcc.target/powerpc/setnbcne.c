/* { dg-do compile } */
/* { dg-options "-O2 -mdejagnu-cpu=future" } */

#define NAME ne
#define CODE !=

#include "setnbc.h"

/* { dg-final { scan-assembler-times {\msetnbcr\M} 20 } } */
