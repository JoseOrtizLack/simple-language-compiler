/**
 * symbolTable.c
 * Implementation of functions used to build the symbol table
 * @author Jose Pablo Ortiz Lack
 */
#include "symbolTable.h"

#include <stdlib.h>
#include <string.h>

/**
 * @brief Allocates space for the Symbol
 * @return The Symbol or NULL if there is not enough memory
 */
static Symbol *allocateSymbol() {

    Symbol *symbol = malloc( sizeof( Symbol ) );

    //if there was not enough memory, malloc returns null
    if ( symbol == NULL ) {

        return NULL;
    }

    return symbol;

}

int insertIntegerSymbol( Symbol *headRef, SymbolType type, char *identifier, int value ) {

    if( findSymbol( headRef, identifier ) != NULL ) {

        Symbol *last = getLastSymbol( headRef ); //We search for the last symbol in the table

        Symbol *new = allocateSymbol();

        if ( new != NULL ) {

            if ( last == NULL ) { //The table is empty

                //Make the new symbol head of the table
                headRef = new;

            } else { //The table has at least one symbol
                last->next = new;
            }

            new->type = type;
            
            //reserve memory for the identifier and copy the identifier to the new symbol
            new->identifier = malloc((strlen(identifier)+1)*sizeof(char));
            strcpy(new->identifier,identifier);

            new->value.iValue = value;

            new->next = NULL;

            return 1;

        } else { //There was an error assigning memory to the new symbol

            return 0;
        }

    } else {

        return 2; //A symbol with the same identifier was found
    }

}

int insertFloatSymbol( Symbol *headRef, SymbolType type, char *identifier, int value ) {

    if( findSymbol( headRef, identifier ) != NULL ) {

        Symbol *last = getLastSymbol( headRef ); //We search for the last symbol in the table

        Symbol *new = allocateSymbol();

        if ( new != NULL ) {

            if ( last == NULL ) { //The table is empty

                //Make the new symbol head of the table
                headRef = new;

            } else { //The table has at least one symbol
                last->next = new;
            }

            new->type = type;
            
            //reserve memory for the identifier and copy the identifier to the new symbol
            new->identifier = malloc((strlen(identifier)+1)*sizeof(char));
            strcpy(new->identifier,identifier);

            new->value.fValue = value;

            new->next = NULL;

            return 1;

        } else { //There was an error assigning memory to the new symbol

            return 0;
        }

    } else {

        return 2; //A symbol with the same identifier was found
    }

}

Symbol *getLastSymbol( Symbol *headRef ) {

    Symbol *last; //we declare the last symbol to be returned

    last = headRef; //We start at the head of the symbol table

    while ( last != NULL ) { //We traverse the table until the end

        if ( last->next == NULL ) { //We have reached the last symbol in the table

            return last; //Return the last symbol

        }

        last = last->next; //Move on to the next symbol

    }

    return NULL; //The table is empty

}

Symbol *findSymbol( Symbol *headRef, char *identifier ) {

    Symbol *result = headRef; //We start searching at the beginning of the table
    
    while ( result != NULL ) { //Traverse the complete table

        if(strcmp(result->identifier, identifier) == 0) { //If the identifier of the current node matches the search criteria
         
            return result;

        }
    }

    return NULL; //If the search criteria is not met, return NULL
}

