/* float.c
 * For use in CSE351 Lec 6 on Floating Point
 */
#include <stdio.h>
#include <math.h>


/* Print the bits of an int (spaces between each nibble and byte).
 * Included for reference (compare to print_binary_fp).
 */
void print_binary(int x) {
  int i;
  // start at MSB and go backwards (decrement)
  for (i = 31; i >= 0; i--) {
    // print the i-th bit (0 or 1)
    printf("%d", (x >> i) & 0x1);
    // add spaces to make more human-readable
    if (i%8 == 0) printf(" ");
    if (i%4 == 0) printf(" ");
  }
  printf("\n");
}


/* Print the bits of a float, with spaces to distinguish 
 * sign, exponent, and mantissa fields.
 */
void print_binary_fp(float x) {
  int i;
  unsigned u = *(unsigned*)&x;
  // start at MSB and go backwards (decrement)
  for (i = 31; i >= 0; i--) {
    // print the i-th bit (0 or 1)
    printf("%d", (u >> i) & 0x1);
    // add space after sign and exponent
    if (i == 32-1) printf(" ");
    if (i == 32-9) printf(" ");
  }
}


/* Print float in 3 different ways:
 *    - in decimal (%g)
 *    - hexadecimal (must force printf to think it's an int first)
 *    - binary
 */
void print_float(float x) {
  printf("%4gf: 0x%08x (", x, *(int*)&x);
  print_binary_fp(x);
  printf(")\n");
}


/* Try running this to see the representations of different 
 * float values in binary, and some instances showing that
 * floats don't always abide by the rules of math!
 */
int main(int argc, char const *argv[]) {
  printf("\n# Integer representation\n");
  printf("%d (int) in binary:\n", 1);
  print_binary(1);

  printf("\n# Float representation\n");
  print_float(-0.0f);
  print_float(1.0f);  // 1.0 * 2^0 -> Exp=0, E=0+127
  // constants INFINITY and NAN found in math.h
  print_float(INFINITY);
  print_float(-NAN);

  printf("\n# Exploring math\n");
  printf("%g\n", 3.14 +  1e100 - 1e100);
  printf("%g\n", 3.14 + (1e100 - 1e100));
  printf("Not associative!\n");

  printf("%.20g\n", 100 * (0.1 + 0.2) );
  printf("%.20g\n", (0.1 + 0.2) );
  printf("%.20g\n", (0.1) );
  printf("%.20g\n", (0.2) );
  printf("%.20g\n", (100 * 0.1) + (100 * 0.2) );
  printf("Not distributive!\n");

  return 0;
}
