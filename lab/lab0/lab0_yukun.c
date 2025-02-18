/*
  *** CSE 351 Lab 0 ***
  https://courses.cs.washington.edu/courses/cse351/20sp/labs/lab0.php
  Familiarize yourself with the workflow to modify, compile,
  and execute source files on a Linux environment.
  This lab also will preview some of the major concepts we
  will cover later in this course!
  - Part 1: Data (Pointers, Numbers, and Bits)
  - Part 2: Arrays
  - Part 3: Structs
  - Part 4: Performance
  - Part 5: Memory Allocation
*/


// These #includes tell the compiler to include the named
// header files, similar to imports in Java.  The functions
// mentioned below are used in our code.  Functions are
// like Java static methods that are not in a class.
//   assert.h - contains declaration of assert()
//   stdio.h  - contains declaration of printf()
//   stdlib.h - contains declaration of malloc() and free()
//   time.h   - contains declaration of clock()
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// This #define tells the C preprocessor to do a straight
// substitution of instances of the text "SIZE" in the code
// below with the text "500". This example acts like a
// global variable without actually allocating memory for
// a variable.
#define SIZE 500


/**** LOOK AT MAIN() AT THE BOTTOM OF THIS FILE FIRST ****/


// PART 1 - Data (Pointers, Numbers, and Bits)
//
// All data are internally stored as bits (binary digits).
// Data stored in memory (RAM) are associated with addresses.
// Addresses can be stored in variables called pointers.
void part1() {
    printf("*** LAB 0 PART 1 ***\n");

    // C has different integer datatypes, which determine
    // the bit width of the binary representation. Here we
    // use 'int', which is usually 32 bits wide, depending
    // on the system and programming language.
    int x = 351, y = 410;

    // Printf is a library function to print formatted
    // output to the console. It will interpret stored bits
    // based on the format specifiers you provide it:
    //  - http://www.cplusplus.com/reference/cstdio/printf/
    printf("x = %i\ny = %i\n", x, y);

    // The following line creates integer pointers p and q
    // and stores the addresses of x and y, respectively,
    // into them.
    int *p = &x, *q = &y;
    printf("p = %p\nq = %p\n", p, q);

    // Q1: The following line is an example. Feel free to
    // copy and/or modify it as needed for part 1 of this lab.
    printf("x = %i, &x = %p\n", x, & x);
}



// HELPER FUNCTION - fillArray()
//
// Fill a given array with values according to a formula.
// C doesn't keep track of the length of arrays, so we have
// to specify it as an explicit parameter (len), rather than
// looking it up from the array as in Java.
// The type of the array parameter here is int*, a pointer
// to an int. We'll learn more about why int* is used here,
// but for now it is enough to understand that "array" is an
// array of ints.
void fillArray(int* array, int len) {
    printf("Filling an array at address %p with %d "
        "values\n", array, len);
    for (int i = 0; i < len; ++i) {
        array[i] = i * 3 + 2;
        // assert() verifies that the given condition is true
        // and exits the program otherwise. This is just a
        // "sanity check" to make sure that the line of code
        // above is doing what we intend.
        assert(array[i] == i * 3 + 2);
    }
    printf("Done!\n");
}


// PART 2 - Arrays
//
// Create an array and fill it with values using the
// fillArray() function defined above. Learn about array
// representation in memory and (lack of) boundaries.
void part2() {
    printf("*** LAB 0 PART 2 ***\n");

    // This is a block of memory big enough to store 10
    // ints. The name "array" here actually refers to the
    // address of this block of memory.
    // array[0] is the first int in this block of memory,
    // array[1] is the second, and so on. C does not track
    // or check array lengths, so it is up to us to know how
    // many elements the array contains.
    int array[10];

    // Q2.1: What happens if the second argument is greater
    // than the size of the array (10)?
    // Answer: It works fine, but it is dangerous(array out of bound alougth c don't check array bound, 
    //         we will wirte data to unsafe address, this may crash the program). 
    fillArray(array, 10);
    // fillArray(array, 11);
    // assert(array[10] == 32);

    int value = 351;

    // In C, we can take the address of something using the
    // & operator. &value is of the type int*, meaning that
    // it is a pointer to an integer (it stores the address
    // in memory of where the actual int is located).

    // Q2.2: Here we use the address of the variable "value"
    // as if it were an array of a single element. What data
    // is stored in value after the following code executes?
    // Think about why the result is what it is.
    fillArray(&value, 1);
    // &value is the addr of array value, or the first element
    // of value, which is itself, value[0] = 2
    // assert(value == 2);
}



// PART 3 Definition - Scores
//
// Structs are blocks of memory composed of smaller parts,
// each of which has a name and is called a field. The
// following struct definition has four int fields named
// hw, lab, midterm, and final.
// In this case, we use typedef to give structs of this
// type a name, Scores, which can be used like we use
// other types such as int or char.
typedef struct {
    int hw;
    int lab;
    int midterm;
    int final;
} Scores;


// PART 3 - Structs
void part3() {
    printf("*** LAB 0 PART 3 ***\n");

    // The following creates an instance of Scores. The
    // space taken up in memory by student is equivalent
    // to an array of four ints, although we can refer to
    // the ints stored in it by name as well.
    Scores student;

    // Set the first int to have a value of 0 and verify
    // that the value changed.
    student.hw = 0;
    assert(student.hw == 0);

    // Depending on whether or not you like to live
    // dangerously, the following is either exciting or
    // terrifying. Though &student is of type Scores* (a
    // pointer to a Scores struct), we can use a cast to
    // pretend that it is actually an array of integers
    // instead.  It's all just memory after all!
    // The "(int*)" tells the C compiler that we want to
    // treat "&student" as an address of an int (in this
    // case, the start of an array) rather than an address
    // of a Scores struct.
    fillArray((int*) &student, 4);

    // We can confirm that fillArray updated the values
    // in the Scores struct:
    assert(student.hw == 2);
    assert(student.lab == 5);
    assert(student.midterm == 8);
    assert(student.final == 11);


    // Q3.1: Given that we were able to get our program to
    // treat &student as an int array, we should be able
    // to use array indexing syntax to access the struct
    // values as well (this is possible, but not practical).
    // Uncomment and modify the left-hand side of the assert
    // statement below to use array indexing ([#]) so that
    // the condition passes.
    // Order of operations can be confusing, so parentheses
    // generally improve readability.

    // midterm in theory is 2nd element
    assert(((int*) &student)[2] == 8);
}



// HELPER FUNCTION - bigArrayIndex()
//
// To create a sufficiently large array, it must be created
// in the Heap using malloc(). We will use this array like
// a 3D array, so this function mimics multi-level array
// syntax: bigArray[bigArrayIndex(i,j,k)] is equivalent to
// bigArray[i][j][k] if bigArray[] were a 3D array.
int bigArrayIndex(int i, int j, int k) {
    return SIZE * SIZE * i + SIZE * j + k;
}


// PART 4 - Performance
//
// It turns out that "Big O" is not the only important thing
// in determining how quickly a program executes.
// Here we will see that even without altering results,
// changing the order of memory accesses can alter execution
// speed.
void part4() {
    printf("*** LAB 0 PART 4 ***\n");

    // Raw execution times are often poor metrics due to
    // inconsistencies and dependence on system, but they
    // can still be used to show general trends.
    clock_t timer;
    // allocate space in the Heap for a "3D array"
    int* bigArray = (int*) malloc(SIZE * SIZE * SIZE * sizeof(int));
    // start timer
    timer = clock();


    // Q4.1: Try changing the order of the loops (switch the
    // "for" lines). The original ordering below is
    // considered "ijk".  Which loop orderings are fastest?
    // ANS: after comparing the ijk seems fastest
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                bigArray[bigArrayIndex(i, j, k)] = i + j + k;
            }
        }
    }
    // stop timer and print result
    printf("Approximate runtime for i, j, k = %d\n", (int)(clock() - timer));

    // bigArray = (int*) malloc(SIZE * SIZE * SIZE * sizeof(int));
    // // start timer
    // timer = clock();


    // // Q4.1: Try changing the order of the loops (switch the
    // // "for" lines). The original ordering below is
    // // considered "ijk".  Which loop orderings are fastest?
    // for (int j = 0; j < SIZE; j++) {
    //     for (int k = 0; k < SIZE; k++) {
    //         for (int i = 0; i < SIZE; i++) {
    //             bigArray[bigArrayIndex(i, j, k)] = i + j + k;
    //         }
    //     }
    // }
    // // stop timer and print result
    // printf("Approximate runtime for k, j, i = %d\n", (int)(clock() - timer));
}



// PART 5 - Memory Allocation
//
// In the case that the size of an array is not known until
// runtime, the malloc function can be used to allocate
// memory dynamically. C is unlike Java, however, in that
// dynamically-allocated memory must be freed explicitly
// when the program is done using it via the free function.
// This can affect not only the performance of your program,
// but the performance of your overall system.
void part5() {
    printf("*** LAB 0 PART 5 ***\n");

    // malloc takes a single argument, the number of bytes
    // to allocate, and returns the address of a newly
    // allocated chunk of memory whose size is the given
    // argument.
    // sizeof(Scores) gives the size of the Scores struct in
    // bytes (which is 16), so sizeof(Scores) * 5 is 80.
    Scores* class_grades = (Scores*) malloc(sizeof(Scores) * 5);
    fillArray((int*)class_grades, 5*4);

    // Q5: Once we are finished with malloc-ed memory, we
    // need to free the memory associated with it.
    // Run "valgrind ./lab0 5" after compiling the program,
    // both with (Q5.1) and without (Q5.2) the free statement below.
    // Valgrind is a tool for analyzing how programs
    // use memory, which is often invaluable for C and
    // C++ programming.
    free(class_grades);

    // ANS
    //     HEAP SUMMARY:                                                                                                   
    // ==416==     in use at exit: 0 bytes in 0 blocks                                                                         
    // ==416==   total heap usage: 1 allocs, 1 frees, 512 bytes allocated
    // Without free:
    //     HEAP SUMMARY:                                                                                                   
    // ==409==     in use at exit: 80 bytes in 1 blocks                                                                        
    // ==409==   total heap usage: 2 allocs, 1 frees, 592 bytes allocated                                                      
    // ==409==                                                                                                                 
    // ==409== LEAK SUMMARY:                                                                                                   
    // ==409==    definitely lost: 80 bytes in 1 blocks

    // TODO(4): Now it's your turn to write some code.
    // Using malloc(), allocate a FourInts struct
    // dynamically (on the heap) and use fillArray to
    // populate it with values. Make sure to free the
    // memory when you are done, and use the valgrind
    // tool mentioned above to check that there aren't
    // any errors. As a "sanity check," add four assert
    // statements to verify that the a, b, c, and d
    // fields of the FourInts struct are set to what
    // you would expect. (Hint, you'll need to use the
    // -> operator to access fields of a FourInts*
    // variable instead of the . operator).
    typedef struct {
    int a, b, c, d;
    } FourInts;
    FourInts* four_ints = (FourInts*) malloc(sizeof(FourInts));
    fillArray((int*)four_ints, 4);
    assert(four_ints->a == 2);
    assert(four_ints->b == 5);
    assert(four_ints->c == 8);
    assert(four_ints->d == 11);
    free(four_ints);
}



// main() is the entry point of the program. It has two
// parameters: argc is the number of arguments that were
// passed on the command line; argv is an array of those
// arguments as strings.
// Strings in C are arrays of chars.
int main(int argc, char* argv[]) {
    // input checking - note that the executable name is
    // included in the argument count
    if ( argc != 2 || !atoi(argv[1]) ) {
        printf("Usage: %s <num>\n", argv[0]);
        exit(0);
    }

    // atoi() is a library function that converts a String
    // to an integer
    switch ( atoi(argv[1]) ) {
        case 1:   part1();  break;
        case 2:   part2();  break;
        case 3:   part3();  break;
        case 4:   part4();  break;
        case 5:   part5();  break;
        default:  printf("No part %s in this lab!\n", argv[1]);
                  exit(0);
    }

    return 0;
}