/*
 * Stack.c
 *
 * Array-based Stack implementation.
 *
 */

#include "Stack.h"
#include <stdlib.h>

#define STACK_SIZE 50

#ifdef DYNAMIC

Stack *new_Stack() {
    Stack* this = NULL;
    return this;
}

#else

/*
 * Creates/initialises an array-based Stack with some suitable default size.
 * Returns a valid Stack struct by value.
 */
Stack new_Stack() {
    Stack this;
    this.capacity = STACK_SIZE;
    this.top = -1;

    return this;
}

#endif

/*
 * Pushes the given element onto this Stack.
 * Returns true on success and false on push failure when stack is full.
 */
bool Stack_push(Stack* this, float element) {

    if (Stack_size(this) != (int) this->capacity) {  //if stack is not full, proceed
        this->array[++this->top] = element; //put element at top + 1, and update top
        return true;
    } else {
        return false;
    }

}

/*
 * Pops the top element from this Stack.
 * Returns false if stack is empty and true otherwise, storing the popped value at *retval.
 */
bool Stack_pop(Stack* this, float* retval) {

    if (!Stack_isEmpty(this)) {
        //saves the value to the value at retval pointer, and moves top down
        *retval = this->array[this->top--];
        this->array[this->top + 1] = 0; //remove the value at popped array position
        return true;
    } else {
        return false;
    }

}

/*
 * Returns the number of elements currently on this Stack.
 */
int Stack_size(Stack* this) {
    return this->top + 1;
}

/*
 * Returns true is this Stack is empty, false otherwise.
 */
bool Stack_isEmpty(Stack* this) {
	return this->top == -1;
}

/*
 * Clears this Stack returning it to an empty state.
 */
void Stack_clear(Stack* this) {
    this->capacity = STACK_SIZE;
    this->top = -1;
    //reset array to default (all zeros)
    for(int i = 0; i < this->capacity; i++) {
        this->array[i++] = 0;
    }
}

/*
 * Destroys this Stack by clearing any stack data (and freeing the memory if you are using dynamic memory allocation).
 */
void Stack_destroy(Stack* this) {
    Stack_clear(this);
}
