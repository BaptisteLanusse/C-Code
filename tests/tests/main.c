//
//  main.c
//  tests
//
//  Created by Lanusse Baptiste on 05/10/2015.
//  Copyright © 2015 BPACA. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    
    char* pointeurSurChar = NULL;
    
    int* pointeurSurInt = NULL;
    
    int theInt = 0;
    
    pointeurSurInt = &theInt;
    
    pointeurSurChar = pointeurSurInt;
    
    printf("Adresse pointeur sur int : %d\nAdresse pointeur sur int + 1 :%d\n\nAdresse pointeur sur char : %d\nAdresse pointeur sur char + 1 : %d\n\n", pointeurSurInt, pointeurSurInt + 1, pointeurSurChar, pointeurSurChar + 1);
    
    printf("Nombre d'octets entre une adresse int* et sa suivante: %d\n\nNombre d'octets entre une adresse char* et sa suivante: %d\n\n", ((int)(pointeurSurInt + 1) - (int)pointeurSurInt), ((int)(pointeurSurChar + 1) - (int)pointeurSurChar));
    
    return 0;
}
