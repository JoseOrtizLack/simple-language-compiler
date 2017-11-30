/**
 * syntaxTree.h
 * Definition of the structure to build a syntax tree
 * @author Jose Pablo Ortiz Lack
 */
#ifndef __SYNTAX_TREE_H__
#define __SYNTAX_TREE_H__

/**
 * @brief The node type
 */
typedef enum tagNodeType {
    nEXPR,
    nTERM,
    nFACTOR,
    nEXPRESION,
    nSEMICOLON,
    nDECLARATION,
    nASSIGNMENT,
    nIF,
    nWHILE,
    nFOR
} NodeType;

/**
 * @brief The operation type
 */
typedef enum tagOperationType {

    eINTEGER,
    eFLOAT,
    eID,
    eSUM,
    eSUB,
    eDIV,
    eMULT,
    ePOW,
    eMOD,
    eGREATER_THAN,
    eLESS_THAN,
    eEQUAL_TO

} OperationType;

/**
 * @brief The symbol type
 */
typedef enum tagSymbolType {
    INTEGER,
    FLOAT
} SymbolType;

/**
 * @brief The syntax tree structure
 */
typedef struct tagNode {
  
    NodeType type; //Type of node (see NodeType ENUM)

    /********** EXPR | TERM | FACTOR | EXPRESION components **********/
    OperationType operationType; //Type of operation (see OperationType ENUM)
    SymbolType valueType; //type of value (see SymbolType ENUM)
    union {

        int iValue; //integer value
        float fValue; //float value
        char *sValue; //symbol value

    } value; //value (if Operand)
    struct tagNode *leftOperand; //left operand of the operation
    struct tagNode *rightOperand; //right operand of the operation

    /********** SEMICOLON components **********/
    struct tagNode *leftStatement; //left statement of the semicolon
    struct tagNode *rightStatement; //right statement of the semicolon

    /********** DEC Components **********/
    SymbolType symbolType; //type of the simbol
    char *identifier; //identifier of the symbol

    /********** ASSIGNMENT STMT Components **********/
    char *identifier; //Identifier of the symbol to be assigned
    struct tagNode *expr; //operation to assign

    /********** IF STMT Components **********/
    struct tagNode *expresion; //expresion to be evaluated
    struct tagNode *then_opt_stmts; //optional statements to be executed if expresion is true

    /********** WHILE STMT Components **********/
    //conditional_expresion reused from IF STMT components
    struct tagNode *do_opt_stmts; //optional statements to be executed in a loop while a condition is met

    /********** FOR STMT Components **********/
    struct tagNode *assignment_stmt; //assignment statement (View ASSIGNMENT STMT components)
    struct tagNode *step_expr; //Step expresion to be executed in each loop (view EXPR components)
    struct tagNode *until_expr; //Stop expr to be met (e.g 7, 14.5, x where x := 10) (view EXPR components)
    //do_opt_stmts reused from WHILE STMT components

} Node;

/**
 * @brief calculates the result of of an integer Operation
 * @param operation operation to be calculated
 * @returns integer value result of the operation
 */
int evaluateIntegerOperation( Node *operation );

/**
 * @brief calculates the result of a float operation
 * @param operation operation to be calculated
 * @returns float value result of the operation
 */
float evaluateFloatOperation( Node *operation );

/**
 * @brief evaluates an Expresion
 * @param expresion expresion to be evaluated
 * @returns 1 if the expresion is true, 0 if the expresion is false
 */
int evaluateExpresion(Node *expresion);

/**
 * @brief declares a symbol in the Symbol Table
 * @param declaration components of the symbol to be declared
 * @returns 0 if there was an error declaring the symbol, 1 if the declaration was sucessful, 2 if the symbol already exists
 */
int declareSymbol( Node *declaration );

/**
 * @brief assigns a value to a symbol in the table
 * @param declaration components of the symbol to be declared
 * @returns 0 if there was an error declaring the symbol, 1 if the declaration was sucessful, 2 if the symbol already exists
 */
int assignSymbol( Node *assignment );

/**
 * @brief resolves an if statement
 * @param statement if statement with condition and optional statements
 */
void ifStatement( Node *statement );

/**
 * @brief resolves a while loop statement
 * @param statement while statement with condition and optional statements loop
 */
void whileStatement( Node *statement );

/**
 * @brief resolves a for loop statement
 * @param statement for statement with initialization assignment, step operation, stop condition and optional statements loop
 */
void forStatement( Node *statement );

#endif