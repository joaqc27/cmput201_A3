/* testImport.c
 *
 * Description: testing file for exportDB(), requires importDB to be ran
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
    exportDB("testing/testexport.csv");
    return 0;
}