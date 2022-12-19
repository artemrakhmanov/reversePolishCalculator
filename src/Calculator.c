#include "Stack.h"
#include "Calculator.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

//make stack stay in memory beyond calc constructor scope
static Stack stack; 

/*
    CALCULATOR FUNCTIONS
*/

Calculator newCalculator() {
    Calculator this;
    stack = new_Stack();
    this.stack = &stack;
    return this;
}

/*
 * Container function for dealign with operator inputs.
 * Deals with negative sign before number, operators & bad expressions.
 * Returns true on success and false when operation on
 * less that 2 operands (bad expression).
 */
bool Calculator_handleOperatorInput(Calculator* this, 
                                    char operator, 
                                    FILE* file) {
    //reuse either for storing negarive or saving computation result
    float resultNumber;                   
    
    /*
    if the operator is a negative sign before a digit, 
    treat like negative float input
    */
    if (isNegativeSign(operator) && checkIfDigitNext(file)) {
        resultNumber = -1 * readFloat(file);
        Calculator_storeNumber(this, resultNumber);
        return true;
    }

    // To perform an operation, there has to be 2+ numbers in calculator
    if (Calculator_countStoredNumbers(this) >= 2) {
        resultNumber = Calculator_compute(this, operator);
        Calculator_storeNumber(this, resultNumber);
        return true;
    } else {
        //bad expression
        return false;
    }
}

/*
 * Analyses the input char and returns a corresponding input type.
 */
InputType Calculator_inputTypeOf(int input) {
    if (isdigit(input)) {
        return Number;
    }

    //checks if input is a letter
    if (isalpha(input)) {
        return Invalid;
    }

    //checks if input is a supported operator
    if (isSupportedOperator(input)) {
        return Operator;
    }

    //checks if input is a space separator
    if ((char) input == ' ') {
        return Space;
    }

    //checks if input is a control char, either eof or else bad expression
    if (iscntrl(input)) {
        return END;
    }

    return Invalid;
}

/*
 * Returns the number of numbers on the stack.
 */
int Calculator_countStoredNumbers(Calculator* this) {
    return Stack_size(this->stack);
}

/*
 * Pushes the number on to the stack for further operations.
 */
void Calculator_storeNumber(Calculator* this, float number) {
    Stack_push(this->stack, number);
}

/*
 * Pops the last stored number in the calcator and returns it.
 */
float Calculator_getLastNumber(Calculator* this) {
    float lastNumber;
    Stack_pop(this->stack, &lastNumber);
    return lastNumber;
}

/*
 * Performs an arithmetic operation on last two numbers in
 * the calculator, based on the operator.
 * returns the result.
 */
float Calculator_compute(Calculator* this, char operator) {
    float operand2 = Calculator_getLastNumber(this);
    float operand1 = Calculator_getLastNumber(this);
    float result;

    switch(operator) {
        case '*': 
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
    }   

    return result;
}

/*
 * Function that handles the completion of the program, and
 * deals with checking for bad expressions, as well as printing
 * result if expression was correct.
 */
void Calculator_endProgram(Calculator* this, enum InputType inputType) {

    //EOF with one number left in calc -> correct expression, print answer
    if (inputType == END 
        && 
        Calculator_countStoredNumbers(this) == 1) {
        
        //print result
        printf("%.2f\n", Calculator_getLastNumber(this));

    } else {   
        //either > 1 number with EOF or Invalid inputs result in bad expression
        printf("Bad expression\n");
    }

    exit(0);
}



/*
    HELPER FUNCTIONS
*/

/*
 * Checks the int representation of input char against the 
 * supported operators.
 * Returns 1 if there is a match, 0 if operator is not supported.
 */
int isSupportedOperator(int c) {
    char operator = (char) c;

    if (operator == '+' || operator == '-' ||
        operator == '*' || operator == '/') {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Reads a float from standard input.
 */
float readFloat(FILE* file) {
    float inputFloat;
    fscanf(file, "%f", &inputFloat);
    return inputFloat;
}

/*
 * Reads a char from standard input.
 */
char readChar(FILE* file) {
    return (char) fgetc(file);
}

/*
 * Peeks at the standard input char, without removing it from
 * standard input stream.
 * Returns false if at EOF
 */
bool peekInput(FILE* file, int* input) {
    //check that peeking not at eof * get char
    bool notEnd = ((*input = fgetc(file)) != EOF);

    if (notEnd) {
        //put the char back, because we are peeking
        ungetc(*input, file);   
    }

    return notEnd;
}

/*
 * Retrieves a single char from the stream without using the value,
 * for the purpose of skipping it.
 */
void skipChar(FILE* file) {
    fgetc(file);
}

/*
 * Checks if a char is a negative sign.
 */
bool isNegativeSign(char operator) {
    return operator == '-';
}

/*
 * Peeks at the standard input to check if the 
 * next char is a digit.
 */
bool checkIfDigitNext(FILE* file) {
    int peekValue;
    if (!peekInput(file, &peekValue)) {
        return false;   //EOF not digit
    };

    return isdigit(peekValue);
}