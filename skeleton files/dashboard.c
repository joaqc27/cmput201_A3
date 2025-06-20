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
void printMenu() {
    printf("\n1. Export Database\n");
    printf("2. Count Entries\n");
    printf("3. Sort By\n");
    printf("4. Compress database\n");
    printf("5. Exit\n");
    printf("option: ");
}

void handleExport() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%99s", filename);
    exportDB(filename);
}

void handleCount() {
    int choice;
    char value[100];

    printf("Enter member code (1.TT 2.SuM 3.StM 4.NID 5.NN 6.W): ");
    scanf("%d", &choice);

    printf("Enter Value: ");
    scanf("%99s", value);

    char *memberName;
    switch(choice) {
        case 1: memberName = "Table Type"; break;
        case 2: memberName = "Surface Material"; break;
        case 3: memberName = "Structural Material"; break;
        case 4: memberName = "Neighbourhood Id"; break;
        case 5: memberName = "Neighbourhood Name"; break;
        case 6: memberName = "Ward"; break;
        default: 
            printf("Invalid choice\n");
            return;
    }

    int count = countEntries(memberName, value);
    printf("%s <%s> appeared in the table %d time(s)\n", memberName, value, count);
}


void handleSort() {
    int choice;

    printf("Enter criteria to sort by (1.TT 2.SuM 3.StM 4.NID 5.NN 6.W): ");
    scanf("%d", &choice);

    char *memberName;
    switch(choice) {
        case 1: memberName = "Table Type"; break;
        case 2: memberName = "Surface Material"; break;
        case 3: memberName = "Structural Material"; break;
        case 4: memberName = "Neighbourhood Id"; break;
        case 5: memberName = "Neighbourhood Name"; break;
        case 6: memberName = "Ward"; break;
        default: 
            printf("Invalid choice\n");
            return;
    }

    sortByMember(memberName);
    printf("The sorted database was exported to %s.csv\n", memberName);
}

void handleCompress() {
    char filename[100];
    printf("Enter filename: ");
    scanf("%99s", filename);
    compressDB(filename);
}




int main(int argc, char *argv[]) {
    int opt;
    char *filename = NULL;
    int use_csv = 0;

    // Parse command line arguments
    while ((opt = getopt(argc, argv, "b:c:"))){
        if (opt == -1) break;

        switch (opt) {
            case 'c':
                use_csv = 1;
                filename = optarg;
                break;
            case 'b':
                use_csv = 0;
                filename = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-c csvfile] [-b binfile]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!filename) {
        fprintf(stderr, "No input file specified\n");
        exit(EXIT_FAILURE);
    }

    // Load database
    if (use_csv) {
        importDB(filename);
    } else {
        unCompressDB(filename);
    }

    // Main menu loop
    int option;
    do {
        printMenu();
        scanf("%d", &option);

        switch(option) {
            case 1: handleExport(); break;
            case 2: handleCount(); break;
            case 3: handleSort(); break;
            case 4: handleCompress(); break;
            case 5: break;
            default: printf("Invalid option\n");
        }
    } while (option != 5);

    freeDB();
    return 0;
}