/* dbTest.c
 *
 * Description: Contains a variety of function calls to functions defined in the DB module
 *
 * Author: Joaquin Carbonell, Jigarjeet Mannan
 * Lab instructor: Dr. Philip Mees
 * Lecture instructor: Dr. Philip Mees
*/

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */
#include <stdio.h>

int main(void){
    int count;

    //test DB module functions on smaller csv file

    //1. importDB()
    importDB("/Users/Joaquin/Downloads/cs/cmpt201/CMPT201/labs/cmput201_A3/skeleton files/PicnicTableSmall.csv");
    //importDB("PicnicTableSmall.csv");

    //2. exportDB()
    exportDB("testexport.csv");
    //diff PicnicTableSmall.csv out.txt

    //3. countEntries()
    count = countEntries("Table Type","Square Picnic Table");       
    printf("count: %d\n",count);    //expects 8
    count = countEntries("Surface Material", "Composite");         
    printf("count: %d\n",count);    //expects 1
    count = countEntries("Structural Material","Metal");           
    printf("count: %d\n",count);    //expects 6
    count = countEntries("Neighbourhood Id", "2630");              
    printf("count: %d\n",count);    //expects 2
    count = countEntries("Neighbourhood Name", "RIVER VALLEY HERMITAGE");
    printf("count: %d\n",count);    //expects 2
    count = countEntries("Ward", "Ward Karhiio");
    printf("count: %d\n",count);    //expects 1

    //4. sortByMember() -> check the exported membername files
    sortByMember("Table Type"); 
    sortByMember("Surface Material"); 
    sortByMember("Structural Material");
    sortByMember("Neighbourhood Id");
    sortByMember("Neighbourhood Name");
    sortByMember("Ward");

    //5. compressDB()

    //6. uncompressDB()

    //7. freeDB()
    
    //test on full csv file



    //test dashboard

    return 0;
}
