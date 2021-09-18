/* shift.c
 * For use in CSE351 Lec 5 on Integers
 *
 * Demonstrates the different effects of right and left shifting
 * in combination with signed and unsigned "8-bit" data.
 */
#include <stdio.h>


int main() {
  unsigned char x = 0x19;
  // shifts are bitwise operators,
  //   so data type doesn't matter until you interpret the data
  unsigned char L1 = x<<2;
  unsigned char L2 = x<<3;
  unsigned char L3 = x<<4;

  printf("\n");
  /* Note: printf statements can be hard to work with to view
     small data.  The %d, %u, and %x specifiers extend
     to 32 bits and %c displays characters instead of 
     values.
  */
  printf("** Left Shift (<<) **\n");
  // %.2X prints at least 2 capital hex digits (padding with 0),
  //   using capital hex digits.
  printf("*      Hex: x = 0x%.2X, L1 = 0x%.2X, L2 = 0x%.2X, L3 = 0x%.2X\n",
         x, L1, L2, L3);
  // cast to signed char to get sign extension
  // %4 just means to pad to 4 characters in length
  printf("*   Signed: x = %4d, L1 = %4d, L2 = %4d, L3 = %4d\n",
         (char)x, (char)L1, (char)L2, (char)L3);
  printf("* Unsigned: x = %4u, L1 = %4u, L2 = %4u, L3 = %4u\n",
         x, L1, L2, L3);
  printf("*********************\n\n");


  unsigned char xu = 0xF0;
  char          xs = 0xF0;
  unsigned char R1u = xu>>3;
  char          R1s = xs>>3;
  unsigned char R2u = xu>>5;
  char          R2s = xs>>5;
  printf("** Right Shift (>>) **\n");
  printf("*    Logical: xu  = 0x%.2X = %4u\n", xu, xu);
  printf("*             R1u = 0x%.2X = %4u\n", R1u, R1u);
  printf("*             R2u = 0x%.2X = %4u\n", R2u, R2u);
  // cast to unsigned char to avoid sign extension for hex
  printf("* Arithmetic: xs  = 0x%.2X = %4d\n", (unsigned char)xs, xs);
  printf("*             R1s = 0x%.2X = %4d\n", (unsigned char)R1s, R1s);
  printf("*             R2s = 0x%.2X = %4d\n", (unsigned char)R2s, R2s);
  printf("**********************\n\n");


  // main function in C supposed to return an int
  //   (used to signal to OS)
  return 0;
}