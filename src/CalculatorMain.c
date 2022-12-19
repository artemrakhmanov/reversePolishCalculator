#include <stdio.h>
#include <stdlib.h>
#include "Calculator.h"


int main() {

    Calculator calc = newCalculator();

    int inputChar;  
    //updated in case of bad expressions to Invalid
    InputType lastInputType = END;
    
    //while not at EOF, read input
    while(peekInput(stdin, &inputChar)) {

        //based on input type, apply respective logic
        switch(Calculator_inputTypeOf(inputChar)) {
        //input is a digit, proceed to read as float & store number
        case Number:    
            Calculator_storeNumber(&calc, readFloat(stdin));
            break;
        //input is an operator, deal with operations / negative float / bad expr
        case Operator:
            if (Calculator_handleOperatorInput(&calc, 
                                            readChar(stdin), 
                                            stdin)) {
                break;
            } else {
                //computation failed due to bad expression
                lastInputType = Invalid;
                //terminate
                goto termination;
            }
        //input identified as invalid
        case Invalid:
            lastInputType = Invalid;
            //terminate
            goto termination;
        //separation between inputs, ignore
        case Space:
            skipChar(stdin);
            break;
        //input is EOF, terminate
        case END:
            goto termination;
        }

    }

    termination:

    //terminated accordingly to the expression state / last input type
    Calculator_endProgram(&calc, lastInputType);

    return 0;
}
