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

PicnicTable* arrayToLinked(PicnicTable *array, int arrSize){
    int i;

    PicnicTable* head = NULL;
    //Db->size doesn't need to be adjusted since the array and linkedList should have the same number of elements
    for (i=0; i < arrSize; i++){
        printf("%d, %d, %s\n", array[i].tableID, array[i].tableTypeID,array[i].neighName);
        PicnicTable *newNode = malloc(sizeof(PicnicTable)); //make a new node
        //copy everything from the array struct into node struct
        newNode->tableID = array[i].tableID;                
        newNode->siteID = array[i].siteID;
        newNode->tableTypeID = array[i].tableTypeID;
        newNode->surfaceID = array[i].surfaceID;
        newNode->structuralID = array[i].structuralID;
        strcpy(newNode->streetave,array[i].streetave); 
        newNode->hoodID = array[i].hoodID;
        strcpy(newNode->ward, array[i].ward);
        strcpy(newNode->latitude, array[i].latitude);
        strcpy(newNode->longitude, array[i].longitude);
        strcpy(newNode->neighName,array[i].neighName);
        strcpy(newNode->location,array[i].location);
        strcpy(newNode->geoPoint,array[i].geoPoint);

        //insert node
        if (head == NULL){
            head = newNode;
        }
        else{
            PicnicTable *p = head;
            while (p->next != NULL){
                p = p->next;
            }
            p->next = newNode;
        }
    }
    free(array);    //free original array
    return head;
}

*/