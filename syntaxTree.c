/**
 * syntaxTree.c
 * Implementation of the methods to build, manage and resolve a syntax tree
 * @author Jose Pablo Ortiz Lack
 */
#include "syntaxTree.h"
#include "symbolTable.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief Allocates space for the Node
 * @return The Node or NULL if there is not enough memory
 */
static Node *allocateNode() {

    Node *node = malloc( sizeof( Node ) );

    if(node == NULL) {

        return NULL;
    }

    return node;
}

Node * createInteger( int value ) {

    Node *nInteger = allocateNode();

    if (nInteger == NULL) {
    
        return NULL;

    }
    nInteger->type = nVALUE;
    nInteger->operationType = oINTEGER;
    nInteger->symbolType = INTEGER;
    nInteger->value.iValue = value;
    
    return nInteger;

}

Node * createFloat( float value ) {

    Node *nFloat = allocateNode();

    if (nFloat == NULL) {
    
        return NULL;

    }
    nFloat->type = nVALUE;
    nFloat->operationType = oFLOAT;
    nFloat->symbolType = FLOAT;
    nFloat->value.fValue = value;
    
    return nFloat;

}

Node * createSymbol( char  *value , Symbol **symbolTable) {

    Node *nSymbol = allocateNode();

    if (nSymbol == NULL) {
    
        return NULL;

    }

    nSymbol->type = nVALUE;
    nSymbol->operationType = oID;
    nSymbol->symbolType = getSymbolType( symbolTable , value );
    nSymbol->value.idValue = value;
    
    return nSymbol;

}

SymbolType assertSymbolType( SymbolType leftOperand , SymbolType rightOperand ) {

    if( leftOperand == rightOperand ) { //both operand symbol types match

        return leftOperand;

    } else { //operands do not match, print error and exit program

        printf("Error: types do not match\n");

        exit(1); //We exit the program as there was an error
    }
}

Node *createOperation( OperationType operationType , Node *leftOperand , Node *rightOperand) {

    Node *nOperation = allocateNode();

    if (nOperation == NULL) {
    
        return NULL;

    }

    nOperation->type = nOPERATION;

    nOperation->symbolType = assertSymbolType( leftOperand->symbolType , rightOperand->symbolType ); //if assert fails compiler will terminate

    nOperation->operationType = operationType;

    nOperation->leftOperand = leftOperand;

    nOperation->rightOperand = rightOperand;

    return nOperation;

}

Node *createExpresion( ExpresionType expresionType , Node *leftOperand , Node *rightOperand) {

    Node *nExpresion = allocateNode();

    if (nExpresion == NULL) {
    
        return NULL;

    }

    nExpresion->type = nEXPRESION;
    
    nExpresion->symbolType = assertSymbolType( leftOperand->symbolType , rightOperand->symbolType ); //if assert fails compiler will terminate

    nExpresion->expresionType = expresionType;

    nExpresion->leftOperand = leftOperand;

    nExpresion->rightOperand = rightOperand;

    return nExpresion;

}

Node *createSemiColon( Node *leftStatement, Node *rightStatement ) {

    Node *nSemicolon = allocateNode();

    if (nSemicolon == NULL) {
    
        return NULL;

    }

    nSemicolon->type = nSEMICOLON;

    nSemicolon->leftStatement = leftStatement;

    nSemicolon->rightStatement = rightStatement;

    return nSemicolon;

}

Node *createAssignment( char *identifier , Node *expr , Symbol **symbolTable ) {

    Node *nAssignment = allocateNode();

    if (nAssignment == NULL) {
    
        return NULL;

    }

    nAssignment->type = nASSIGNMENT;
    nAssignment->symbolType = assertSymbolType( expr->symbolType , getSymbolType( symbolTable , identifier ) );
    nAssignment->expr = expr;
    nAssignment->value.idValue = identifier;

    return nAssignment;

}

Node *createIfStatement( Node *expresion , Node *thenOptStmts ) {

    Node *nIfStatement = allocateNode();

    if (nIfStatement == NULL) {
    
        return NULL;

    }

    nIfStatement->type = nIF;

    nIfStatement->expresion = expresion;
    nIfStatement->thenOptStmts = thenOptStmts;

    return nIfStatement;

}

Node *createWhileStatement( Node *expresion, Node *doOptStmts ) {

    Node *nWhileStatement = allocateNode();

    if (nWhileStatement == NULL) {
    
        return NULL;

    }

    nWhileStatement->type = nWHILE;

    nWhileStatement->expresion = expresion;
    nWhileStatement->doOptStmts = doOptStmts;

    return nWhileStatement;

}

Node *createForStatement( char *identifier , Node *expr , Node *stepExpr , Node *untilExpr , Node *doOptStmts ) {

    Node *nForStatement = allocateNode();

    if (nForStatement == NULL) {
    
        return NULL;

    }

    nForStatement->type = nFOR;

    nForStatement->value.idValue = identifier;
    nForStatement->expr = expr;
    nForStatement->stepExpr = stepExpr;
    nForStatement->untilExpr = untilExpr;
    nForStatement->doOptStmts = doOptStmts;

    return nForStatement;

}

Node *createReadStatement( char *identifier ) {

    Node *nReadStatement = allocateNode();

    if (nReadStatement == NULL) {
    
        return NULL;

    }

    nReadStatement->type = nREAD;

    nReadStatement->value.idValue = identifier;

    return nReadStatement;
}

Node *createPrintStatement( Node *expr ) {

    Node *nPrintStatement = allocateNode();

    if (nPrintStatement == NULL) {
    
        return NULL;

    }

    nPrintStatement->type = nPRINT;

    nPrintStatement->expr = expr;

    return nPrintStatement;

}

int evaluateIntegerOperation( Node *operation , Symbol **symbolTable) {

    switch ( operation->operationType ) {
        
        case oINTEGER:
            return operation->value.iValue;

        case oID:
            return getIntegerSymbolValue( symbolTable , operation->value.idValue);
        
        case oSUM:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) + evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        case oSUB:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) - evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        case oMULT:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) * evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        case oDIV:
            return evaluateIntegerOperation( operation->leftOperand , symbolTable ) / evaluateIntegerOperation( operation->rightOperand , symbolTable );
        
        default:
            // should not be here
            return 0;
    
    }

}

float evaluateFloatOperation( Node *operation , Symbol **symbolTable) {

    switch (operation->operationType) {
        
        case oFLOAT:
            return operation->value.fValue;

        case oID:
            return getFloatSymbolValue( symbolTable , operation->value.idValue);
        
        case oSUM:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) + evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        case oSUB:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) - evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        case oMULT:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) * evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        case oDIV:
            return evaluateFloatOperation( operation->leftOperand , symbolTable ) / evaluateFloatOperation( operation->rightOperand , symbolTable );
        
        default:
            // should not be here
            return 0;
    
    }

}

int evaluateExpresion(Node *expresion , Symbol **symbolTable ) {

    switch( expresion->expresionType ) {

        case eGREATER_THAN:

            switch( expresion->symbolType ) {

                case INTEGER:

                    return evaluateIntegerOperation(expresion->leftOperand , symbolTable ) > evaluateIntegerOperation(expresion->rightOperand  , symbolTable );

                case FLOAT:

                    return evaluateFloatOperation(expresion->leftOperand , symbolTable ) > evaluateFloatOperation(expresion->rightOperand  , symbolTable );

                default:
                    // should not be here
                    return 0;

            }

        case eLESS_THAN:

            switch( expresion->symbolType ) {

                case INTEGER:

                    return evaluateIntegerOperation(expresion->leftOperand , symbolTable ) < evaluateIntegerOperation(expresion->rightOperand  , symbolTable );

                case FLOAT:

                    return evaluateFloatOperation(expresion->leftOperand , symbolTable ) < evaluateFloatOperation(expresion->rightOperand  , symbolTable );

                default:
                    // should not be here
                    return 0;

            }

        case eEQUAL_TO:

            switch( expresion->symbolType ) {

                case INTEGER:

                    return evaluateIntegerOperation(expresion->leftOperand , symbolTable ) == evaluateIntegerOperation(expresion->rightOperand  , symbolTable );

                case FLOAT:

                    return evaluateFloatOperation(expresion->leftOperand , symbolTable ) == evaluateFloatOperation(expresion->rightOperand  , symbolTable );

                default:
                    // should not be here
                    return 0;

            }

        default:
            // should not be here
            return 0;

    }
}

int resolveTree( Node *tree, Symbol **symbolTable) {

    switch( tree->type ) {

        case nSEMICOLON:

            resolveTree( tree->leftStatement, symbolTable );
            resolveTree( tree->rightStatement, symbolTable );

        break;

        case nASSIGNMENT:

            switch( tree->symbolType ) {

                case INTEGER:
                    
                    setIntegerSymbolValue( symbolTable , tree->value.idValue , evaluateIntegerOperation( tree->expr , symbolTable ) );
                
                break;
                
                case FLOAT:
                    
                    setFloatSymbolValue( symbolTable , tree->value.idValue , evaluateIntegerOperation( tree->expr , symbolTable ) );
                
                break;

                default:

                    //should not be here
                    return 0;

                break;
            
            }

        break;

        case nIF:

            if( evaluateExpresion( tree->expresion , symbolTable ) ) {

                resolveTree( tree->thenOptStmts, symbolTable );

            }
        
        break;

        case nWHILE:

            while( evaluateExpresion( tree->expresion , symbolTable ) ) {

                resolveTree( tree->doOptStmts , symbolTable );

            }
        
        break;

        case nFOR: {
            
            //Check that the symbol and the expr have the same type
            SymbolType symbolType = assertSymbolType( getSymbolType( symbolTable , tree->value.idValue) , tree->expr->symbolType );
            
            //assert that the stepExpr and unitlExpr have the same symbol type as the symbol
            assertSymbolType( symbolType , tree->stepExpr->symbolType );
            assertSymbolType( symbolType , tree->untilExpr->symbolType );

            switch(symbolType) {

                case INTEGER: {

                    //resolve expr and assign to symbol
                    int integerIterator = evaluateIntegerOperation( tree->expr , symbolTable );
                    int integerStep = evaluateIntegerOperation( tree->stepExpr , symbolTable );
                    int integerUntil = evaluateIntegerOperation( tree->stepExpr , symbolTable );
                    
                    setIntegerSymbolValue( symbolTable, tree->value.idValue , integerIterator );

                    do {

                        resolveTree( tree-> doOptStmts , symbolTable );
                        integerIterator += integerStep;
                        setIntegerSymbolValue( symbolTable, tree->value.idValue , integerIterator ); //updates the symbol value with the step value
                    } while( integerIterator <= integerUntil);

                    break;
                }

                case FLOAT: {

                    //resolve expr and assign to symbol
                    float floatIterator = evaluateFloatOperation( tree->expr , symbolTable );
                    float floatStep = evaluateFloatOperation( tree->stepExpr , symbolTable );
                    float floatUntil = evaluateFloatOperation( tree->stepExpr , symbolTable );
                    
                    setIntegerSymbolValue( symbolTable, tree->value.idValue , floatIterator );

                    do {

                        resolveTree( tree-> doOptStmts , symbolTable );

                        floatIterator += floatStep;
                        setFloatSymbolValue( symbolTable, tree->value.idValue , floatIterator ); //updates the symbol value with the step value
                    } while( floatIterator <= floatUntil);

                    break;
                }

            }

            break;
        }

        case nREAD:

            switch( getSymbolType( symbolTable , tree->value.idValue ) ) {

                case INTEGER: {

                    int value;
                    scanf( "%d" , &value );
                    setIntegerSymbolValue( symbolTable, tree->value.idValue , value );

                    break;
                }

                case FLOAT: {

                    float value;
                    scanf( "%f" , &value );
                    setFloatSymbolValue( symbolTable, tree->value.idValue , value );

                    break;
                }
            }

        break;

        case nPRINT:

            switch( getSymbolType( symbolTable , tree->expr->value.idValue ) ) {

                case INTEGER:

                    printf ( "%d\n" , evaluateIntegerOperation( tree->expr , symbolTable ) );

                break;

                case FLOAT:

                    printf ( "%f\n" , evaluateFloatOperation( tree->expr , symbolTable ) );

                break;
            }

        break;

        default: //no statements

            return 1;

        break;

    }

    
    return 1;

}