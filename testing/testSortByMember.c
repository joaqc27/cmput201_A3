/* testImport.c
 *
 * Description: 
 *
 * Author: Joaquin Carbonell, Jigarjeet Mannan
 * Lab instructor: Dr. Philip Mees
 * Lecture instructor: Dr. Philip Mees
*/

#include "../DB.h"       /* Import the public database header. */
#include "../DB_impl.h"  /* Import the private database header */
#include <stdio.h>

int main(void){
    importDB("testing/PicnicTableSmall.csv");

    //4. sortByMember() -> check the exported membername files
    sortByMember("Table Type"); 
    sortByMember("Surface Material"); 
    sortByMember("Structural Material");
    sortByMember("Neighbourhood Id");
    sortByMember("Neighbourhood Name");
    sortByMember("Ward");

    return 0;
}