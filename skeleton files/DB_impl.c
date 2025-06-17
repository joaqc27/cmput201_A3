/* DB_impl.c
 *
 * TODO: Provide a high-level description of what is contained
 * in this file.
 *
 * Author: Joaquin Carbonell, Jigarjeet Mannan
 * Lab instructor: Dr. Philip Mees
 * Lecture instructor: Dr. Philip Mees
 */

#include "DB.h"       /* Import the public database header. */
#include "DB_impl.h"  /* Import the private database header */

//full function definition being developed/tested in DB.c, but for full submission, this should be uncommented and the one in DB.c should be deleted

/*
char* fetchNeighbourhood(NeighbourhoodTable *tablep, int hoodID){
    int i;
    for(i=0; i < tablep->size; i++){
        if(hoodID == tablep->nID[i]){
            return tablep->nName[i];
        }
    }
}

int fetchTable(LookupTable *tablep, char *tabletype){
    for (int i=0; i < tablep->size; i++){
        if(strcmp(tabletype,tablep->entries[i]) == 0){
            return tablep->ids[i];
        }
    }
}

PicnicTable* linkedToArray(DataBase *Db, int linkedSize){
    int i;
    PicnicTable *p = Db->picnicTableTable;    
    PicnicTable* newArray = malloc(sizeof(PicnicTable) * linkedSize);

    for (i=0; i < linkedSize; i++){
        newArray[i] = *p;
        p = p->next;
    }
    return newArray;
}

int compareTableType(const void *a, const void *b){
    const PicnicTable *valA = (PicnicTable*) a;
    const PicnicTable *valB = (PicnicTable*) b;
    
    if (valA->tableTypeID > valB->tableTypeID){return 1;}
    else if (valA->tableTypeID == valB->tableTypeID){return 0;}
    else if (valA->tableTypeID < valB->tableTypeID) {return -1;}
    else {return -2;}
}

int compareSurfaceMat(const void *a, const void *b){
    const PicnicTable *valA = (PicnicTable*) a;
    const PicnicTable *valB = (PicnicTable*) b;
    
    if (valA->surfaceID > valB->surfaceID){return 1;}
    else if (valA->surfaceID == valB->surfaceID){return 0;}
    else if (valA->surfaceID < valB->surfaceID) {return -1;}
    else {return -2;}
}

int compareStructMat(const void *a, const void *b){
    const PicnicTable *valA = (PicnicTable*) a;
    const PicnicTable *valB = (PicnicTable*) b;
    
    if (valA->structuralID > valB->structuralID){return 1;}
    else if (valA->structuralID == valB->structuralID){return 0;}
    else if (valA->structuralID < valB->structuralID) {return -1;}
    else {return -2;}
}

int compareHoodID(const void *a, const void *b){
    const PicnicTable *valA = (PicnicTable*) a;
    const PicnicTable *valB = (PicnicTable*) b;
    
    if (valA->hoodID > valB->hoodID){return 1;}
    else if (valA->hoodID == valB->hoodID){return 0;}
    else if (valA->hoodID < valB->hoodID) {return -1;}
    else {return -2;}
}

int compareNeighName(const void *a, const void *b){
    const PicnicTable *valA = (PicnicTable*) a;
    const PicnicTable *valB = (PicnicTable*) b;
    int verdict;

    verdict = strcmp(valA->neighName,valB->neighName);
    if (verdict > 0){return 1;}
    else if (verdict == 0){return 0;}
    else if (verdict < 0){return -1;}
    else{return -2;}
}

int compareWard(const void *a, const void *b){
    const PicnicTable *valA = (PicnicTable*) a;
    const PicnicTable *valB = (PicnicTable*) b;
    int verdict;

    verdict = strcmp(valA->ward,valB->ward);
    if (verdict > 0){return 1;}
    else if (verdict == 0){return 0;}
    else if (verdict < 0){return -1;}
    else{return -2;}
}

*/