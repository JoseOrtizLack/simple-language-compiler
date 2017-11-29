/**
 * symbolTable.h
 * Definition of the structure to build a symbol table
 * @author Jose Pablo Ortiz Lack
 */

#ifndef __SYMBOL_TABLE_H__
#define __SYMBOL_TABLE_H__
/**
 * @brief The symbol type
 */
typedef enum tagSymbolType {
    tInt,
    tFloat
} SymbolType;

/**
 * @brief the symbol table structure
 */
typedef struct tagSymbol {

    tagSymbolType type; //type of symbol
    
    char* identifier; //name of the symbol
    
    union {

        int iValue; //integer value
        float fValue; //float value

    } value; //value of the symbol

    struct tagSymbol *next; //next element of the symbol table

} Symbol;

/**
 * @brief inserts a new integer symbol at the end of the list
 * @param headRef reference to the head of the table
 * @param type type of symbol to be added
 * @param identifier identifier of the symbol to be added
 * @param value integer value of the symbol to be added
 */
int insertIntegerSymbol(Symbol *headRef, SymbolType type, char *identifier, int value);

/**
 * @brief inserts a new float symbol at the end of the list
 * @param headRef reference to the head of the table
 * @param type type of symbol to be added
 * @param identifier identifier of the symbol to be added
 * @param value float value of the symbol to be added
 * @return 1 if the symbol was added successfully, 0 if there was an error adding the symbol
 */
int insertFloatSymbol(Symbol *headRef, SymbolType type, char *identifier, int value);

/**
 * @brief finds the last symbol in the list
 * @param headRef reference to the head of the table
 * @return the last symbol or NULL if there is no symbols in the table
 */
Symbol *getLastSymbol(Symbol *headRef);

/**
 * @brief searches a symbol by identifier
 * @param headRef reference to the head of the table
 * @param identifier identifier of the symbol
 * @return the searched symbol or NULL if there is no symbol with this identifier
 */
Symbol *findSymbol(Symbol *headRef, char *identifier);

#endif //__SYMBOL_TABLE_H__




