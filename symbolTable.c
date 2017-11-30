/**
 * symbolTable.c
 * Implementation of functions used to build the symbol table
 * @author Jose Pablo Ortiz Lack
 */
#include "symbolTable.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

int insertIntegerSymbol( Symbol **head, char *identifier, int value ) {

    if( findSymbol( head, identifier ) == NULL ) {

        Symbol *new = allocateSymbol();

        if ( new != NULL ) {

            if ( *head == NULL ) { //The table is empty

                //Make the new symbol head of the table
                ( *head ) = new;
                new->next = NULL;

            } else { //The table has at least one symbol
               
                new->next = (*head);

                (*head) = new;
            }

            new->type = INTEGER;
            
            //reserve memory for the identifier and copy the identifier to the new symbol
            new->identifier = malloc((strlen(identifier)+1)*sizeof(char));
            strcpy(new->identifier,identifier);

            new->value.iValue = value;

            return 1;

        } else { //There was an error assigning memory to the new symbol

            return 0;
        }

    } else {

        return 2; //A symbol with the same identifier was found
    }

}

int insertFloatSymbol( Symbol **head, char *identifier, float value ) {

    if( findSymbol( head, identifier ) == NULL ) {

        Symbol *new = allocateSymbol();

        if ( new != NULL ) {

            if ( *head == NULL ) { //The table is empty

                //Make the new symbol head of the table
                (*head) = new;

            } else { //The table has at least one symbol
                
                new->next = (*head);
                
                (*head) = new;
            }

            new->type = FLOAT;
            
            //reserve memory for the identifier and copy the identifier to the new symbol
            new->identifier = malloc((strlen(identifier)+1)*sizeof(char));
            strcpy(new->identifier,identifier);

            new->value.fValue = value;

            return 1;

        } else { //There was an error assigning memory to the new symbol

            return 0;
        }

    } else {

        return 2; //A symbol with the same identifier was found
    }

}

Symbol *findSymbol( Symbol **head, char *identifier ) {

    Symbol *result =  *head; //We start searching at the beginning of the table
    
    while ( result != NULL ) { //Traverse the complete table
    
        if(strcmp(result->identifier, identifier) == 0) { //If the identifier of the current node matches the search criteria
            return result;

        }
        result = result->next;
    }
    return result; //If the search criteria is not met, return NULL
}

int updateIntegerSymbol( Symbol **head, char *identifier, int newValue ) {

    //verify the table is not empty
    if( *head == NULL ) {

        return 0;
    }

    Symbol *updateSymbol = findSymbol( head, identifier ); //Search the symbol to be updated

    if( updateSymbol == NULL ) { //The symbol was not found

        return 0;
    }

    updateSymbol->value.iValue = newValue;

    return 1;

}

int updateFloatSymbol( Symbol **head, char *identifier, float newValue ) {

    //verify the table is not empty
    if( *head == NULL ) {

        return 0;
    }

    Symbol *updateSymbol = findSymbol( head, identifier ); //Search the symbol to be updated

    if( updateSymbol == NULL ) { //The symbol was not found

        return 0;
    }

    updateSymbol->value.fValue = newValue;

    return 1;

}

