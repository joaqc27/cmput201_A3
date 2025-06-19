/* testImport.c
 *
 * Description: Testing file for importDB()
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
    return 0;
}