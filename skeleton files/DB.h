/* DB.h
 *
 * Public interface to the specification for your database implementation
 *
 * Please do not modify any code in this file!  We will be testing your code
 * under the assumption that the public interface matches this interface.
 *
 * Author: Joaquin Carbonell, Jigarjeet Mannan
 * Lab instructor: Dr. Philip Mees
 * Lecture instructor: Dr. Philip Mees
 */

#ifndef DB_H
#define DB_H

/*
 * If you are using arrays for your DataBase tables, they must use dynamic memory,
 * and the initial size of each table must be set to INIT_SIZE.
 * INIT_SIZE is not needed if you are using linked lists.
 */
#define INIT_SIZE 5

/*
 * DECLARE HERE THE TYPEDEFS OF THE STRUCTS called LookupTable,
 * NeighbourhoodTable, AND PicnicTable, WHICH ARE MEMBERS IN THE TYPEDEF STRUCT
 * DataBase BELOW.
 * Comments list suggested members. You may change the internal
 * details of these structs, but don't change how they are typedef'ed.
 * YOU MAY DECLARE ADDITIONAL STRUCTS AS NEEDED.
 */

typedef struct {
    // This struct has members for an ID and for a table type, or
    // surface material, or structural material

} LookupTable; // used in DataBase struct

typedef struct {
    // This struct has members for a neighbourhood ID and for a neighbourhood name.

} NeighbourhoodTable; // used in DataBase struct

typedef struct {
    // This struct has a total of 10 members, one for each of
    // table ID, site ID, table type ID, surface material ID,
    // structural material ID, street / avenue,  neighbourhood ID, ward,
    // latitude, longitude, see the assignment specs.

} PicnicTable; // used in DataBase struct

typedef struct {
    // This struct has members for each of the five database tables, and for the
    // current capacity and the current size (number of records) of each of
    // these five tables. You can add anything you see fit here.

    LookupTable *tableTypeTable;
    LookupTable *surfaceMaterialTable;
    LookupTable *structuralMaterialTable;
    NeighbourhoodTable *neighbourhoodTable;
    PicnicTable *picnicTableTable;
} DataBase; // main database


/* -----------------------------------------------------------------------------
 * YOU ARE NOT ALLOWED TO CHANGE OR ADD TO THE DECLARATIONS BELOW THIS LINE
 * ---------------------------------------------------------------------------*/
/*
 * Declare a global DataBase variable. This is the only allowed global variable.
 * DB.c must contain the definition of this variable.
 */
extern DataBase *Db;

/*
 * Takes the name of a .csv file as parameter and creates and populates the
 * DataBase with the corresponding dataset information. All five DataBase tables
 * must be populated after a call to this function. All strings stored in the
 * DataBase must use dynamic memory. Each line of the .csv file can only be read
 * once, in other words, the four lookup tables must be created at the same time
 * as the main picnicTableTable.
 */
void importDB(char *fileName);

/*
 * Takes the name of a .csv file as parameter and creates a .csv file containing
 * the information of the DataBase. The exported .csv file must be EXACTLY the
 * same as the original .csv file from which the DataBase was created (diff
 * command should find no differences).
 */
void exportDB(char *fileName);

/*
 * Takes the name of a member of the picnicTableTable variable and a value for
 * that member as parameters and returns the number of entries in the
 * picnicTableTable variable which have that value for the memberName.
 *
 * This function must be implemented for the following members:
 *  1- Table Type
 *  2- Surface Material
 *  3- Structural Material
 *  4- Neighbourhood ID
 *  5- Neighbourhood Name
 *  6- Ward
 */
int countEntries(char *memberName, char *value);

/*
 * Takes the name of a member of the picnicTableTable variable as an argument
 * and uses qsort to sort the table in ascending order of the values of that
 * sorting member. After sorting, this function writes the DataBase to a .csv
 * file, named after the sorting member. This function must be implemented for
 * the following members:
 *  1- Table Type
 *  2- Surface Material
 *  3- Structural Material
 *  4- Neighbourhood ID
 *  5- Neighbourhood Name
 *  6- Ward
 */
void sortByMember(char *memberName);

/*
 * Takes the name of a file as a parameter, and creates a binary file named
 * filename containing a compressed version of the DataBase. The binary file
 * must contain all five DataBase tables. More details are given in the
 * assignment specifications. Clearly describe in the design document how the
 * DataBase compression is implemented.
 */
void compressDB(char *filename);

/*
 * Takes the name of an existing file as a parameter. This file must contain a
 * compressed DataBase, obtained by calling compressDB(filename). The function
 * recreates the DataBase which was compressed in the filename. Unlike
 * importDB(), this function does not create the four lookup tables from
 * scratch. When this function is completed, the program should be in the same
 * state as after calling importDB().
 */
void unCompressDB(char *filename);

/*
 * Frees all dynamic memory associated with the DataBase.
 */
void freeDB(void);

#endif //DB_H
