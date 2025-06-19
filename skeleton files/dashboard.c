/*
 * dashboard.c
 *
 * Description: Implement a public interface to use the DB module to interact with the Database
 *
 * Author: Joaquin Carbonell, Jigarjeet Mannan
 * Lab instructor: Dr. Philip Mees
 * Lecture instructor: Dr. Philip Mees
*/

#include <getopt.h>
#include "DB.h"      /* Only import the public database header. */
                     /* dashboard.c is not allowed access to the DB_impl.h private header */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//You may include other system and custom headers as you see fit


//print menu

int main(int argc, char *argv[]){   //-c, "PicnicTableSmall.csv"
    int option;
    importDB(argv);

    printf("\n1. Export Database\n2. Count Entries\n3. Sort By\n4. Compress database\n5. Exit\n");
    printf("option: ");
    scanf("%d", &option);


    return 0;
}
