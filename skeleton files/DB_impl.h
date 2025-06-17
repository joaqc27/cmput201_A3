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

//does the above but with the actual name
int findNeighbourhoodName(NeighbourhoodTable *tablep, char *neighname);

/*
    Purpose:    Looks for the corresponding tableID in the tableType lookup table given the table type given 
    Parameters: tablep (LookupTable pointer): to reference the LookupTable being searched in, tableType (string): to target the tableID to be returned
    Pre:        Requires LookupTable struct to exist
    Post:       None
    Returns:    The tableID of the given table type
*/
int fetchTable(LookupTable *tablep, char *tableType);

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
