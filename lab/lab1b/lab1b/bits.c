/*
 * CS:APP Data Lab
 *
 * @author: Yukun Cao
 * @results: 30/34  floatInt2Float has issue with rounding
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#ifndef COMMON_H
#include "common.h"
#endif

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
     not allowed to use big constants such as 0xffffffff.
     However, you are allowed to combine constants to values greater
     than 255 or less than 0. e.g. 250 + 250 = 500, so long as
     the operator you are using to combine the constants is listed as
     "legal" at the top of the method you are writing.
  2. Function arguments and local variables (no global variables).
  3. Any operators listed as "legal" at the top of the method you are writing.
  4. Shorthand versions of "legal" operators (ex. you can use ++ and += if + is legal)

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
  5. Write comments for your functions! These won't be graded, but it's good
     practice to write comments and may help you debug your code. See the
     above example to see what the comments should look like.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 */
#endif

/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  // De Morgan's laws ~(a & b) = ~a | ~b
  return ~(~x | ~y);
}
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  // x^y = (~x&y)|(x&~y) = ~(~((~x&y)) & ~((x&~y)))
  return ~(~((~x&y)) & ~((x&~y)));
}
/*
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
// Desired output: 0100 1001 0010 0100 1001 0010 0100 1001 
// Step 1:         0000 0000 0000 0000 0000 0000 0100 1001  0x49
// Step 2:         0000 0000 0000 0000 1001 0010 0000 0000  Shift << 9
// Step 3:         0000 0000 0000 0000 1001 0010 0100 1001  Add 0x49
// Step 4:         0100 1001 0010 0100 0000 0000 0000 0000  Shift << 18
// Step 5:         0100 1001 0010 0100 1001 0010 0100 1001  Add result from step 3
  int x, y, z;
  x = 0x49;
  y = x << 9;
  y +=x;
  z = y << 18;
  return y + z;
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // mask is 1111 1111, only preserve wanted 8 bits
  int mask = 0xff;
  return (x >> (n*8)) & mask;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  // by default is arthemetic shift for int
  // goal is to create mask 0000 1111 ex. n=4 then &AND with x
  // handle situation that MSB=1 ex. 0x80000000:
  // 1. when n=0, mask is all 1
  // 2. when n!=0, we shift right by n-1 bits and use
  // n + ~shift + 1==n-1
  int shift = !!n;
  int mask = ~((shift << 31) >> (n + ~shift + 1));
  int res = (x >> n) & mask;
  // printf("n = %d, x = %.2x, mask = %.2x, res = %.2x\n", n, x, mask, res);
  return res;
}
/*
 * invert - Return x with the n bits that begin at position p inverted
 *          (i.e., turn 0 into 1 and vice versa) and the rest left
 *          unchanged. Consider the indices of x to begin with the low-order
 *          bit numbered as 0.
 *   Can assume that 0 <= n <= 31 and 0 <= p <= 31
 *   Example: invert(0x80000000, 0, 1) = 0x80000001,
 *            invert(0x0000008e, 3, 3) = 0x000000b6,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
*/
int invert(int x, int p, int n) {
  // we need to extract 2 parts from x, the one without
  // changes and the part inverts, via 2 masks
  // 1100 and 0011
  // we should make use of logical shift of all 1
  int y_helper = 32 + ~n + 1;
  // int res = logicalShift(~0, 32 - n) << p;
  int shift_helper = !!y_helper;
  int mask_helper = ~((shift_helper << 31) >> (y_helper + ~shift_helper + 1));
  int res = (~0 >> y_helper) & mask_helper;

  int mask = res << p;
  return x ^ mask;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  // we have the property, for all x<0, x>>31=all 1 > 0
  // so we check
  // 1. if x >> 31 = all 1, meaning x < 0
  // 2. if -x >> 31 = all 1, meaning x > 0
  int neg = x >> 31;
  int pos = (~x + 1) >> 31;
  // res is 0x1 if x is not 0
  int res = ~(neg | pos) & 0x1;
  return res;
}
/*
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  // if x<0, x>>31=all 1, that's enough
  // but if x>0, x>>31=0, we need 1, so OR !!x
  int res = (x >> 31) | (!!x);
  // printf("x = %.2x res = %.2x, x >> 31 = %.2x, !!x = %.2x\n", x, res, x>>31, !!x);
  return res;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  // if it's ok, x << 32 -n then >>32-n, result is same
  int y, m, res;
  //m=32-n
  m = 32 + (~n) + 1;
  //带符号扩展
  y = (x << m) >> m;
  //判断是否相同
  res =  !(x ^ y);
  return res;
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  // lecture shows that arthmetic overflow means
  // if x and y have same sign but result sign is
  // different
  int operand_sign = (x >> 31)^(y >> 31);
  int res_sign = (x + y) >> 31;
  // if x,y diff sign, operand_sign = 1
  // if x,y same, operand_sign=0->check res_sign^x_sign
  int same_sign = res_sign^(x>>31);
  // the failure case is operand_sign ==0 && same_sign==1
  return !((!operand_sign)&same_sign);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  // power2 x has property that x&(-x)==x due to struct 0001
  // so that (x&(-x))^x = all 1
  // we first exclude x <=0, res == 0 if x<=0
  int res1 = !(x >> 31) & !!x;
  // res = all 0 is is power of 2
  int res2 = (x &(~x + 1))^x;
  return res1 & (!res2);
}

#if 0
FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.
#endif

/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *     Comparison operations incl ==, < ,>, >=, <=
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  unsigned exp = (uf >> 23) & 0xff;
  unsigned M = uf & 0x7fffff;
  if (!(exp == 0xff && M != 0x0)) {
    uf += 0x80000000;
  }
 return uf;
}
/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Comparison operations incl ==, < ,>, >=, <=
 *   Legal constants: arbitrary integer and unsigned integer constants
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
  // consider edge cases 1. nan 2. 0 3. others
  unsigned Ef = (uf >> 23) & 0xff;
  unsigned Mf = uf & 0x7fffff;
  unsigned Sf = (uf >> 31) & 0x1;

  unsigned Eg = (ug >> 23) & 0xff;
  unsigned Mg = ug & 0x7fffff;
  unsigned Sg = (ug >> 31) & 0x1;
  // nan
  if ((Ef == 0xff && Mf != 0x0) || (Eg == 0xff && Mg != 0x0)) {
  return 0;
  } else if ((uf & 0x7fffffff) == 0 && (ug & 0x7fffffff) == 0) {
    // 0
    return 1;
  } else {
    if (Ef == Eg && Mf == Mg && Sf == Sg) {
      return 1;
    }
  }
  return 0;
}
/*
 * floatInt2Float - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *     Comparison operations incl ==, < ,>, >=, <=
 *   Max ops: 30
 *   Rating: 4
 */
 // yukun: has some issue with rounding
unsigned floatInt2Float(int x) {
  int S, E, M;
  int nfBit = 1;
  unsigned xmove;
  unsigned temp;
  // printf("x= %.2x\n", x);
  if (x == 0) {
    return 0x0;
  }
  if (x < 0 ) {
    S = 0x1;
  } else {
    S = 0x0;
  }
 
  // negative is consider the same representation as pos in fp.
  // only S is different
  if (x < 0) {
    x = ~x + 1;
  }
  // xmove = x < 0 ? -x : x;
  xmove = x;
  // printf("x=%.2x xmove=%.2x\n", x, xmove);
   // we needs >> to decide how many bits in x
  while ((xmove >> 1) != 0x0) {
    // printf("nfBit = %d, xmove = %.2x\n", nfBit, xmove);
    nfBit += 1;
    xmove = xmove >> 1;
  }
  E = nfBit -1 + 127;
  // printf("nfBit = %d, xmove = %.2x\n", nfBit, xmove);

  // if the nfBit<=23, all fit into M, otherwise take first 23
  if (nfBit <= 23) {
    M = x & 0x7fffff;
    unsigned temp1 = M;
    // printf("temp1= %.2x ls= %.2x rs= %.2x\n", temp1, temp1 << (33 - nfBit), (temp1 << (33 - nfBit)) >> (32-nfBit));
    temp1 = (temp1 << (33 - nfBit)) >> (32-nfBit);
    M = temp1;
  } else {
    temp = x;
    M = (temp >> (nfBit - 24)) & 0x7fffff;
    // printf("S= %.2x E= %.2x M= %.2x\n", S, E, M);
    // if M = all 1 overflow, we increase E by 1 and M is all 0
    if (M == 0x7fffff) {
    E +=1;
    M = (M + 1)&0x7fffff;
  } else if ((M & 0x1)) {
      M = M & ~(0x1);
  }
  }
  
  // printf("x= %.2x S= %.2x E= %.2x M= %.2x\n", x, S, E, M);
  return (S<<31)|(E<<23)|M;
}
