#include "Stack.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Calculator Calculator;
typedef enum InputType InputType;

//calculator struct definition
struct Calculator {
    Stack* stack;
};

//Enumaration of input types for stdin stream handling
enum InputType{Number, Operator, Invalid, Space, END};

/*
    CALCULATOR FUNCTIONS
*/

Calculator newCalculator();

/*
 * Analyses the input char and returns a corresponding input type.
 */
InputType Calculator_inputTypeOf(int input);

/*
 * Container function for dealign with operator inputs.
 * Deals with negative sign before number, operators & bad expressions.
 * Returns true on success and false when operation on
 * less that 2 operands (bad expression).
 */
bool Calculator_handleOperatorInput(Calculator* this, 
                                    char operator, 
                                    FILE* file);

/*
 * Returns the number of numbers on the stack.
 */
int Calculator_countStoredNumbers(Calculator* this);

/*
 * Pushes the number on to the stack for further operations.
 */
void Calculator_storeNumber(Calculator* this, float number);

/*
 * Pops the last stored number in the calcator and returns it.
 */
float Calculator_getLastNumber(Calculator* this);

/*
 * Performs an arithmetic operation on last two numbers in
 * the calculator, based on the operator.
 * Returns the result.
 */
float Calculator_compute(Calculator* this, char operator);

/*
 * Function that handles the completion of the program, and
 * deals with checking for bad expressions, as well as printing
 * result if expression was correct.
 */
void Calculator_endProgram(Calculator* this, 
                            InputType inputType);

/*
    HELPER FUNCTIONS
*/

/*
 * Checks the int representation of input char against the 
 * supported operators.
 * Returns 1 if there is a match, 0 if operator is not supported.
 */
int isSupportedOperator(int c);

/*
 * Reads a float from standard input.
 */
float readFloat(FILE* file);

/*
 * Reads a char from standard input.
 */
char readChar(FILE* file);

/*
 * Peeks at the standard input char, without removing it from
 * standard input stream.
 * Returns false if at EOF
 */
bool peekInput(FILE* file, int* input);

/*
 * Retrieves a single char from the stream without using the value,
 * for the purpose of skipping it.
 */
void skipChar(FILE* file);

/*
 * Checks if a char is a negative sign.
 */
bool isNegativeSign(char operator);

/*
 * Peeks at the standard input to check if the 
 * next char is a digit.
 */
bool checkIfDigitNext(FILE* file);
