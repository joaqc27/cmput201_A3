/* testImport.c
 *
 * Description: Testing file for countEntries(), requires importDB() to be ran
 *
 * Author: Joaquin Carbonell, Jigarjeet Mannan
 * Lab instructor: Dr. Philip Mees
 * Lecture instructor: Dr. Philip Mees
*/

#include "../DB.h"       /* Import the public database header. */
#include "../DB_impl.h"  /* Import the private database header */
#include <stdio.h>

int main(void){
    int count;
    importDB("testing/PicnicTableSmall.csv");

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

    return 0;
}