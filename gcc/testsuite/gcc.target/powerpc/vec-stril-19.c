/* { dg-do run } */
/* { dg-require-effective-target powerpc_future_hw } */
/* { dg-options "-O2 -mdejagnu-cpu=future" } */

#include <altivec.h>

extern void abort (void);

vector signed char
doString(vector signed char *vp)
{
  /* Tail recursion replaced with iteration with -O2.  */
  vector signed char result = vec_stril (*vp);
  if (vec_stril_p (*vp))
    return result;
  else
    return doString (vp + 1);
}

int main (int argc, char *argv [])
{
  vector signed char composed_string [4] = {
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x11 },
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 },
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 },
    { 0x1, 0x2, 0x0, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0xf, 0x11 }
  };

  vector signed char expected0 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x11 };
  vector signed char expected1 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 00, 0x0 };
  vector signed char expected2 =
    { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
      0x9, 0xa, 0xb, 0xc, 0xd, 0x0, 0x0, 0x0 };
  vector signed char expected3 =
    { 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
      0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

  if (!vec_all_eq (doString (&composed_string[0]), expected1))
    abort ();
  if (!vec_all_eq (doString (&composed_string[1]), expected1))
    abort ();
  if (!vec_all_eq (doString (&composed_string[2]), expected2))
    abort ();
  if (!vec_all_eq (doString (&composed_string[3]), expected3))
    abort ();
}
