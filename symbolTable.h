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
    INTEGER,
    FLOAT
} SymbolType;

/**
 * @brief the symbol table structure
 */
typedef struct tagSymbol {

    SymbolType type; //type of symbol
    
    char* identifier; //name of the symbol
    
    union {

        int iValue; //integer value
        float fValue; //float value

    } value; //value of the symbol

    struct tagSymbol *next; //next element of the symbol table

} Symbol;

/**
 * @brief inserts a new integer symbol at the end of the list
 * @param head reference to the head of the table
 * @param type type of symbol to be added
 * @param identifier identifier of the symbol to be added
  * @return  0 if there was an error adding the symbol, 1 if the symbol was added successfully, or 2 if the symbol already exists
 */
int insertIntegerSymbol( Symbol **head, char *identifier, int value );

/**
 * @brief inserts a new float symbol at the end of the list
 * @param head reference to the head of the table
 * @param type type of symbol to be added
 * @param identifier identifier of the symbol to be added
 * @param value float value of the symbol to be added
 * @return  0 if there was an error adding the symbol, 1 if the symbol was added successfully, or 2 if the symbol already exists
 */
int insertFloatSymbol( Symbol **head, char *identifier, float value );

/**
 * @brief finds the last symbol in the list
 * @param head reference to the head of the table
 * @return the last symbol or NULL if there is no symbols in the table
 */
Symbol *getLastSymbol( Symbol **head );

/**
 * @brief searches a symbol by identifier
 * @param head reference to the head of the table
 * @param identifier identifier of the symbol
 * @return the searched symbol or NULL if there is no symbol with this identifier
 */
Symbol *findSymbol( Symbol **head, char *identifier );


/**
 * @brief updates the value of an integer symbol
 * @param head reference to the head of the table
 * @param identifier identifier of the symbol
 * @param newValue updated value of the symbol
 * @return 0 if the symbol was not found, 1 if the update was sucessful
 */
int updateIntegerSymbol( Symbol **head, char *identifier, int newValue );

/**
 * @brief updates the value of an integer symbol
 * @param head reference to the head of the table
 * @param identifier identifier of the symbol
 * @param newValue updated value of the symbol
 * @return 0 if the symbol was not found, 1 if the update was sucessful
 */
int updateFloatSymbol( Symbol **head, char *identifier, float newValue );

#endif //__SYMBOL_TABLE_H__




