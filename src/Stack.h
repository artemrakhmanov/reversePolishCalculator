/*
 * Stack.h
 *
 * Module interface for Stack implementation.
 *
 *      Author: jonl
 */

#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>

// Un-comment this line if you want to use dynamic memory allocation for your Stack implementation.
//#define DYNAMIC

typedef struct Stack Stack;

/* You should define your struct Stack here */
struct Stack {
    int top;
    unsigned char capacity;
    float array[50];
};


#ifdef DYNAMIC // if you want to use dynamic memory allocation for your Stack

/*
 * Creates/initialises an array-based Stack with some suitable default size.
 * Returns a pointer to valid Stack* on success and NULL on failure.
 */
Stack* new_Stack();

#else // if you don't want to use dynamic memory allocation for your Stack

/*
 * Creates/initialises an array-based Stack with some suitable default size.
 * Returns a valid Stack struct by value.
 */
Stack new_Stack();

#endif

/*
 * Pushes the given element onto this Stack.
 * Returns true on success and false on push failure when stack is full.
 */
bool Stack_push(Stack* this, float element);

/*
 * Pops the top element from this Stack.
 * Returns false if stack is empty and true otherwise, storing the popped value at *retval.
 */
bool Stack_pop(Stack* this, float* retval);

/*
 * Returns the number of elements currently on this Stack.
 */
int Stack_size(Stack* this);

/*
 * Returns true is this Stack is empty, false otherwise.
 */
bool Stack_isEmpty(Stack* this);

/*
 * Clears this Stack returning it to an empty state.
 */
void Stack_clear(Stack* this);

/*
 * Destroys this Stack by clearing any stack data (and freeing the memory if you are using dynamic memory allocation).
 */
void Stack_destroy(Stack* this);

#endif /* STACK_H_ */
