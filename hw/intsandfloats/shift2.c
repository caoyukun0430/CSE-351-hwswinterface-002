/* shift2.c
 * For use in CSE351 Lec 5 on Integers
 *
 * Inputs:
 *   - direction:  shift left (0) or right (else)
 *   - number:     shift amount (number of bits)
 */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int dir, num, x = 100;

  // Want two arguments, but executable name is always argv[0]
  if (argc != 3) {
    printf("Usage:  ./shift2 <direction> <number>\n");
    printf("        direction: shift left (0) or right (else)\n");
    printf("        number:    shift amount (number of bits)\n");
    return 1;
  }

  // atoi() converts strings to integers
  dir = atoi(argv[1]);
  num = atoi(argv[2]);

  if (dir)  // shift left
    printf("100 >> %d = %d\n", num, x >> num);
  else      // shift right
    printf("100 << %d = %d\n", num, x << num);

  return 0;
}