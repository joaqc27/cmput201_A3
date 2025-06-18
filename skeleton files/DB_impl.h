/* DB_impl.h
 *
 * For any "private"  declarations that should not be visible to the public
 * users of the database, but might want to be shared across various source
 * files in database implementation.
 *
 * It is a common convention to append "_impl" to a private implementation of
 * some public interface, so we do so here.
 *
 * Author: Joaquin Carbonell, Jigarjeet Mannan
 * Lab instructor: Dr. Philip Mees
 * Lecture instructor: Dr. Philip Mees
 */


#ifndef DB_IMPL_H
#define DB_IMPL_H
/*
    Purpose:    Looks for the corresponding neighbourhood name in the neighbourhood lookup table given the ID 
    Parameters: tablep (LookupTable pointer): to reference the LookupTable being searched in, hoodID (int): to target the neighbourhood name to be found
    Pre:        Requires LookupTable struct to exist
    Post:       None
    Returns:    A pointer to the corresponding neighbourhood name 
*/
char* fetchNeighbourhood(NeighbourhoodTable *tablep, int hoodID);

/*
    Purpose:    Looks for the corresponding tableID in the tableType lookup table given the table type given 
    Parameters: tablep (LookupTable pointer): to reference the LookupTable being searched in, tableType (string): to target the tableID to be returned
    Pre:        Requires LookupTable struct to exist
    Post:       None
    Returns:    The tableID of the given table type
*/
int fetchTable(LookupTable *tablep, char *tableType);


/*
    Purpose:    Turn the Database's Linked List of PicnicTable structs into an array for qsort
    Parameters: Db (Database pointer): to reference the global variable Db (isn't really necessary?), 
    Pre:        Requires all structs Database requires and requires the Database to exist
    Post:       Changes the linked list to an array
    Returns:    A pointer to the first element of the array of PicnicTable Structs
*/
PicnicTable* linkedToArray(DataBase *Db, int linkedSize);

/*
    Purpose:    Comparison function that returns values based on TableTypeID
    Parameters: *a and *b, generic pointers that are supposed to point to two values
    Pre:        Requires stdlib.h and PicnicTable struct to exist
    Post:       None
    Returns:    -1 if a < b, 0 if a = b, 1 if a > b, -2 if neither
*/
int compareTableType(const void *a, const void *b);

/*
    Purpose:    Comparison function that returns values based on surfaceID
    Parameters: *a and *b, generic pointers that are supposed to point to two values
    Pre:        Requires stdlib.h and PicnicTable struct to exist
    Post:       None
    Returns:    -1 if a < b, 0 if a = b, 1 if a > b, -2 if neither
*/
int compareSurfaceMat(const void *a, const void *b);

/*
    Purpose:    Comparison function that returns values based on structuralID
    Parameters: *a and *b, generic pointers that are supposed to point to two values
    Pre:        Requires stdlib.h and PicnicTable struct to exist
    Post:       None
    Returns:    -1 if a < b, 0 if a = b, 1 if a > b, -2 if neither
*/
int compareStructMat(const void *a, const void *b);

/*
    Purpose:    Comparison function that returns values based on hoodID
    Parameters: *a and *b, generic pointers that are supposed to point to two values
    Pre:        Requires stdlib.h and PicnicTable struct to exist
    Post:       None
    Returns:    -1 if a < b, 0 if a = b, 1 if a > b, -2 if neither
*/
int compareHoodID(const void *a, const void *b);

/*
    Purpose:    Comparison function that returns values based on neighName
    Parameters: *a and *b, generic pointers that are supposed to point to two values
    Pre:        Requires stdlib.h and PicnicTable struct to exist
    Post:       None
    Returns:    -1 if a < b, 0 if a = b, 1 if a > b, -2 if neither
*/
int compareNeighName(const void *a, const void *b);

/*
    Purpose:    Comparison function that returns values based on ward
    Parameters: *a and *b, generic pointers that are supposed to point to two values
    Pre:        Requires stdlib.h and PicnicTable struct to exist
    Post:       None
    Returns:    -1 if a < b, 0 if a = b, 1 if a > b, -2 if neither
*/
int compareWard(const void *a, const void *b);

/*
    Purpose:    Turn the inserted array (should be sorted by some member) back into a linked list to be implemented back into the database
    Parameters: array, (pointer to an array of PicnicTable structs) to indicate the array being converted back, arrSize (int) to specify how many elements are in the to be converted array
    Pre:        Requires stdlib.h and PicnicTable struct to exist
    Post:       Deletes inserted array and creates linked list
    Returns:    A pointer to the first node in the linked list
*/
PicnicTable* arrayToLinked(PicnicTable *array, int arrSize);

/*
 * You may consider helper functions for the following tasks. Additional helper
 * functions may be needed.
 * - Initialize Db
 * - Look for an item in a LookupTable or NeighbourhoodTable, and return its index
 * - Increase the size of any of the five tables, if capacity is reached.
 * - Print an entry in the format of a line of the .csv file
 * - Count entries for each of the 6 choices in menu option 2
 * - qsort sorting functions for each of the 6 choices in menu option 3
 * - Edit table entry for each of the three choices in menu option 4
 */


#endif //DB_IMPL_H
