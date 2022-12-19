/*
 * TestStack.c
 *
 * Very simple unit test file for Stack functionality.
 *
 */

#include <stdio.h>
#include "Stack.h"
#include "myassert.h"



/*
 * The stack to use during tests
 */
static Stack* stack;

#ifndef DYNAMIC // if we're not using dynamic memory allocation in our stack implementation, we need an actual stack struct in addition to the pointer to the stack
static Stack stack_s;
#endif


/*
 * The number of tests that succeeded
 */
static int success_count = 0;

/*
 * The total number of tests run
 */
static int total_count = 0;


/*
 * Setup function to run prior to each test
 */
#ifdef DYNAMIC // if we are using dynamic memory allocation in our Stack implementation

void setup() {
    stack = new_Stack();
}

#else // we are not using dynamic memory allocation so initialise "Stack* stack" to contain the pointer to the stack struct

void setup() {
    stack_s = new_Stack();
    stack = &stack_s;
}

#endif


/*
 * Teardown function to run after each test
 */
void teardown(){
    Stack_destroy(stack);
}

/*
 * This function is called multiple times from main for each user-defined test function
 */
void runTest(int (*testFunction)()) {
    total_count++;
    setup();

    if (testFunction()) success_count++;

    teardown();
}


//////// Test Helper Functions ////////


//////// TESTS ///////////


/*
 * Checks that the Stack constructor returns a non-NULL pointer.
 */
int newStackIsNotNull() {
    assert(stack != NULL);
    return TEST_SUCCESS;
}


/*
 * Checks that the size of an empty stack is 0.
 */
int newStackSizeZero() {
    assert(Stack_size(stack) == 0);
    return TEST_SUCCESS;
}

/*
 * Checks that n elements added results in an n size of a stack.
 */
int sizeReflectsPushedElements() {

    float startElement = 1;
    float nthElement = 15;

    while(startElement != nthElement) {
        Stack_push(stack, startElement);
        assert(Stack_size(stack) == startElement);
        startElement++;
    }

    return TEST_SUCCESS;
}

/*
 * Checks that subtracting n elements results in a size-n stack size
 */
 int sizeReflectsPoppedElements() {
    
    float startElement = 1;
    float nthElement = 15;

    //populating stack
    while(startElement != nthElement) {
        Stack_push(stack, startElement);
        startElement++;
    }

    startElement--; //loop terminated at nth + 1;

    //poping
    while(startElement > 0) {
        Stack_pop(stack, &nthElement);
        assert(Stack_size(stack) == --startElement);
    }

    return TEST_SUCCESS;
 }

/*
 * Checks that values pushed correspond, by popping them & getting the retval
 */
int pushAndPopValuesCorrespond() {

    float testArray[10] = {0.0, 2.0, 6.0, 2.0, 4.0, 10.0, 89.0, 22.0, 50.0, -34.0};
    int index = 0;
    float retval;

    //populate the stack
    while(index < 10) {
        Stack_push(stack, testArray[index++]);
    }

    index--;    //loop terminated at 9 + 1;

    //start popping
    while(index >= 0) {
        Stack_pop(stack, &retval);
        assert(retval == testArray[index--]);
    }

    return TEST_SUCCESS;
}

/*
 * Checks that the value is not pushed, when the stack is full.
 */
int pushFailsWhenStackFull() {
    float startElement = 0;
    float stackCapacity = 50;

    //populating stack
    while(startElement != stackCapacity) {
        Stack_push(stack, startElement);
        startElement++;
    }

    assert(!Stack_push(stack, startElement));

    return TEST_SUCCESS;
}

/*
 * Checks that the popping fails when stack is empty.
 */
int popFailsWhenStackEmpty() {
    float retval;
    assert(!Stack_pop(stack, &retval));
    return TEST_SUCCESS;
}




/*
 * Main function for the Stack tests which will run each user-defined test in turn.
 */

int main() {
    //provided
    runTest(newStackIsNotNull);
    runTest(newStackSizeZero);
    //custom
    runTest(sizeReflectsPushedElements);
    runTest(sizeReflectsPoppedElements);
    runTest(pushAndPopValuesCorrespond);
    runTest(pushFailsWhenStackFull);
    runTest(popFailsWhenStackEmpty);


    printf("Stack Tests complete: %d / %d tests successful.\n----------------\n", success_count, total_count);

}
