/* show_bytes.c
 * For use in CSE351 Lec 3 on Memory, Data, and Addressing
 */


// needed for library function printf()
#include <stdio.h>


/* Normally you would put function prototypes here:

  void show_bytes(char *start, int len);
  void show_int(int x);

  Except that in this case the function declarations
  come before their first calls in the file, so they
  are not necessary.
*/


/* Takes start address of data and prints out len bytes in hex.  */
void show_bytes(char *start, int len) {
  int i;
  // for loop doesn't need curly braces {} because single-line body
  for (i = 0; i < len; i++)
    // printf symbols:
    //  %p - print as pointer
    //  \t - tab character
    //  %x - print in hex (.2 means pad to 2 digits)
    //  \n - newline character
    printf("%p, %ld\t0x%.2x\n", start+i, start+i, *(start+i));
//   printf("%p\t%p\n", start+4, start);
  printf("\n");
}


/* Uses show_bytes() to print hex representation of integer.
   Use of sizeof() means this code will work even if int isn't 4B. */
void show_int(int x) {
  show_bytes((char *) &x, sizeof(int));
}

// int withinArray(int * intArray, int size, int * ptr) {
//   // Your code here
//   return (int)ptr < ((int)intArray + size*4);
// }

void swapInts(int *ptr1, int *ptr2) {
  // Your code here
  int temp;
  temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}

int stringLength(char * s) {
  // Your code here
  int length = 0;
  while (*s != '\0') {
    s += 1;
    length += 1;
  }
  return length;
}

int endianExperiment(int* ptr) {
  char *bytePtr;
  // Your code here
  bytePtr = (char *)ptr;
  *bytePtr = 0x77;
  *(bytePtr + 1)= 0x5c;
  *(bytePtr + 2)= 0x5;
  return *ptr;
}

void selectionSort(int arr[], int arrLength) {
  int i, j, min_index;
  // Your code here
  for (i = 0; i < arrLength; i++) {
    min_index = i;
    for (j = i + 1; j < arrLength; j++) {
      if (*(arr + min_index) > *(arr + j)) {
        min_index = j;
      }
    }
    swapInts(arr + i, arr + min_index);
  }
  for (i = 0; i < arrLength; i++) {
    printf("arr[%d] = %d\n", i, arr[i]);
  }
}

/* Example usage of show_int(). */
int main() {
  int x = 12345;  // 12345 = 0x3039
  printf("int x = %d;\n", x);
  show_int(x);

  // x = endianExperiment(&x);
  // printf("int x = %d;\n", x);

  int arr[5] = {5,4,3,2,1};
  selectionSort(arr, 5);




  // int intArray = 0x100;
  // int ptr = 0x18C;

  // int ptr1 = 0x0;
  // int ptr2 = 0x40;
  // int mask = (1<<31)>>25;
  // printf("mask = %2x", (int)mask);
  // printf("Res = %d", ((int)ptr1 & mask) == ((int)ptr2 & mask));
  // printf("ptr = %ld", (int)ptr);
  // printf("intArray = %ld", (int)intArray + 30*sizeof(int));
  // printf("res = %d", (int)ptr < (int)intArray + 30*4);
  // if ((int)ptr < (int)intArray + 4*4) {
  //   printf("1");
  // } else {
  //   printf("0");
  // }
  // char res = (int)ptr < (int)intArray + 4*4 ? "1" : "0";
  // printf("res = %s", res);

  // char s[6] = "1234";
  // char* start = s;
  // int len = stringLength(start);
  // printf("length is %d", len);
  return 0;
}
