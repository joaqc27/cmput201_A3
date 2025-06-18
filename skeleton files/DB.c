/* DB.c
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

DataBase *Db; /* definition of the main database variable */ //is a global variable

void importDB(char *fileName){
    FILE *fp;
    char testBuffer[1000];  
    
    int i=0, colCount, uID=0;
    
    //initialize database
    Db = malloc(sizeof(DataBase));

    Db->tableTypeTable = malloc(sizeof(LookupTable));
    Db->surfaceMaterialTable = malloc(sizeof(LookupTable));
    Db->structuralMaterialTable = malloc(sizeof(LookupTable));
    Db->neighbourhoodTable = malloc(sizeof(NeighbourhoodTable));

    Db->linkedSize = 0;
    Db->tableTypeTable->capacity = 3;
    Db->surfaceMaterialTable->capacity = 6;
    Db->structuralMaterialTable->capacity = 5;
    Db->neighbourhoodTable->capacity = 20;      //assumes there's 20 neighbourhoods for now

    //--NOTE: NODES HAVE NOW BEEN IMPLEMENTED--

    printf("database: %p\nfile: %s\n", Db, fileName);

    //read csv and input them into database
    fp = fopen(fileName,"r");
    if (fp == NULL){
        printf("Can't open %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    fgets(Db->headBuffer,200,fp);                   //skip reading the header columns

    while(fgets(testBuffer,1000,fp)){           //read line by line (this is where a new node starts)
        char *token = strtok(testBuffer, ",");
        colCount = 0;
        //printf("\n");
        
        PicnicTable *node = malloc(sizeof(PicnicTable));
        
        while (token != NULL & colCount < 10){     //ensures only reads from headers "Id" to "Longitude" in the csv

            //change to switch statement?
            if(colCount == 0){                       //assign tableID and siteID
                node->tableID = uID;
                node->siteID = atoi(token);
            }   

            else if(colCount == 1){                  //assign tableTypeID and add to tableTypeTable
                //add to tableTypeTable
                for(i=0; i < Db->tableTypeTable->capacity; i++){            //check array
                    if (Db->tableTypeTable->entries[i] == NULL || strcmp(Db->tableTypeTable->entries[i], token) == 0){ //if this table type is not in the table yet
                        if  (Db->tableTypeTable->entries[i] == NULL){   //only statements that occur if this condition is true
                            Db->tableTypeTable->size++;
                        }
                        Db->tableTypeTable->ids[i] = i;
                        Db->tableTypeTable->entries[i] = malloc(sizeof(char) * 50); //50 to equal neighbourhood table?
                        node->tableTypeID = Db->tableTypeTable->ids[i];     //assign tableTypeID
                        strcpy(Db->tableTypeTable->entries[i], token);
                        break;
                    }
                }
            }
            
            else if(colCount == 2){                  //assign surfaceID and add to surfaceMaterialTable
                //add to surfaceMaterialTable
                for(i=0; i < 6; i++){
                    if(Db->surfaceMaterialTable->entries[i] == NULL || strcmp(Db->surfaceMaterialTable->entries[i],token) == 0){
                        if  (Db->surfaceMaterialTable->entries[i] == NULL){   //only statements that occur if this condition is true
                            Db->surfaceMaterialTable->size++;
                        }
                        Db->surfaceMaterialTable->ids[i] = i;
                        Db->surfaceMaterialTable->entries[i] = malloc(sizeof(char) * 10); //10 since the longest word is "composite"
                        node->surfaceID = Db->surfaceMaterialTable->ids[i];     //assign surfaceID
                        strcpy(Db->surfaceMaterialTable->entries[i], token);
                        break;
                    }
                }
            }
            
            else if(colCount == 3){                  //assign structualID and add to structuralMaterialTable
                //add to structualMaterialTable
                for(i=0; i<5; i++){
                    if(Db->structuralMaterialTable->entries[i] == NULL || strcmp(Db->structuralMaterialTable->entries[i],token) == 0){
                        if  (Db->structuralMaterialTable->entries[i] == NULL){   //only statements that occur if this condition is true
                            Db->structuralMaterialTable->size++;
                        }
                        Db->structuralMaterialTable->ids[i] = i;
                        Db->structuralMaterialTable->entries[i] = malloc(sizeof(char) * 10); //10 since the longest word is "composite" 
                        node->structuralID = Db->structuralMaterialTable->ids[i];   //assign surfaceID
                        strcpy(Db->structuralMaterialTable->entries[i], token);
                        break;
                    }
                }

            }
            
            else if(colCount == 4){                  //assign streetave
                strcpy(node->streetave, token);
            }
            
            else if(colCount == 5){                  //assign hoodID and add to neighbourhoodTable
                for(i=0; i<100; i++){
                    if(Db->neighbourhoodTable->nID[i] == 0 || Db->neighbourhoodTable->nID[i] == atoi(token)){
                        node->hoodID = atoi(token);                        //assign hoodID
                        Db->neighbourhoodTable->nID[i] = atoi(token);      //add to neighbourhoodTable
                        Db->neighbourhoodTable->size++;
                        break;
                    }
                }
            }

            else if(colCount == 6){                  //add neighbourhood name
                for(i=0; i<100; i++){
                    if(Db->neighbourhoodTable->nName[i] == NULL || strcmp(Db->neighbourhoodTable->nName[i],token) == 0){
                        Db->neighbourhoodTable->nName[i] = malloc(sizeof(char) * 50);
                        strcpy(Db->neighbourhoodTable->nName[i],token);
                        strcpy(node->neighName,token);
                        break;
                    }
                }
            }
            
            else if(colCount == 7){                  //assign ward
                strcpy(node->ward, token);
            }
            
            else if(colCount == 8){                  //assign latitude
                strcpy(node->latitude, token);
            }
            
            else if(colCount == 9){                  //assign longitude
                strcpy(node->longitude, token);
                //then assign location and geometry point for exportDB(), but just don't print it anywhere
                sprintf(node->location, "\"(%s, %s)\"", node->latitude, node->longitude);
                sprintf(node->geoPoint, "POINT (%s %s)", node->longitude, node->latitude);
            }

            token = strtok(NULL, ",");
            colCount++;
        }
        //here is when a node is finished being made
        uID++;
        Db->linkedSize++;
        //no resizing is necessary since its a linked list, just update capacity as you go
        if (Db->linkedSize >= Db->currCapacity){
            Db->currCapacity = Db->linkedSize;
        }
        node->next = NULL;

        //insert node into linked list
        if (Db->picnicTableTable == NULL){      //if the list is empty, this node is the first one
            //printf("---first!---\n");
            Db->picnicTableTable = node;
        }
        else{                                   //otherwise, probe to the end of the linked list 
            PicnicTable *p = Db->picnicTableTable;
            //printf("--next!--\n");
            while(p->next != NULL){
                p = p->next;
            }
            p->next = node;
            //printf("---end---\n");
        }

        //check nodes
        /*
        printf("%d\n",node->tableID);
        printf("capacity:   %d\n",node->capacity);
        printf("size:       %d\n",node->size);
        printf("siteID:     %d\n",node->siteID);
        printf("tableTypeID:%d\n",node->tableTypeID);
        printf("surfaceID:  %d\n",node->surfaceID);
        printf("structuralID%d\n",node->structuralID);
        printf("street/ave: %s\n",node->streetave);
        printf("hoodID:     %d\n",node->hoodID);
        printf("ward:       %s\n",node->ward);
        printf("latitude:   %s\n",node->latitude);
        printf("longitude:  %s\n",node->longitude);
        printf("next:       %p\n",node->next);
        printf("successfully added line!\n");                           //everything works
        */
    }

    //print lookup tables (place in testing?)
    printf("\n---tableTypeLookupTable---\ncapacity = %d, size = %d\n",Db->tableTypeTable->capacity, Db->tableTypeTable->size);
    for (i=0; i < Db->tableTypeTable->capacity; i++){
        printf("%d ",Db->tableTypeTable->ids[i]);
        printf("%s\n",Db->tableTypeTable->entries[i]);
    }

    printf("\n---surfaceMaterialLookupTable---\ncapacity = %d, size = %d\n",Db->surfaceMaterialTable->capacity, Db->surfaceMaterialTable->size);
    for (i=0; i < Db->surfaceMaterialTable->capacity; i++){
        printf("%d ",Db->surfaceMaterialTable->ids[i]);
        printf("%s\n",Db->surfaceMaterialTable->entries[i]);
    }

    printf("\n---structuralMaterialLookupTable---\ncapacity = %d, size = %d\n",Db->structuralMaterialTable->capacity, Db->structuralMaterialTable->size);
    for (i=0; i < Db->structuralMaterialTable->capacity; i++){
        printf("%d ",Db->structuralMaterialTable->ids[i]);
        printf("%s\n",Db->structuralMaterialTable->entries[i]);
    }

    printf("\n---neighbourhoodLookupTable---\ncapacity = %d, size = %d\n",Db->neighbourhoodTable->capacity, Db->neighbourhoodTable->size);
    for (i=0; i < Db->neighbourhoodTable->capacity; i++){
        printf("%d ",Db->neighbourhoodTable->nID[i]);
        printf("%s\n",Db->neighbourhoodTable->nName[i]);
    }

    //print all nodes in order (also place in testing)
    PicnicTable *curr = Db->picnicTableTable;
    while (curr->next != NULL){
        //printf("[%d] %d %s\n",Db->linkedSize,curr->tableID, curr->streetave);
        curr = curr->next;
    }
    //printf("%d %s\n",curr->tableID, curr->streetave);
    fclose(fp);
    printf("---end importDB()---\n");
}


//--NOTE: move these function definition to DB_impl.c when submitting / testing on student server, linking doesn't work properly for vscode so for now its just here
char* fetchNeighbourhood(NeighbourhoodTable *tablep, int hoodID){
    int i;
    char *error = NULL;
    for(i=0; i < tablep->size; i++){
        if(hoodID == tablep->nID[i]){
            return tablep->nName[i];
        }
    }
    return error;
}

int fetchTable(LookupTable *tablep, char *tabletype){
    for (int i=0; i < tablep->size; i++){
        if(strcmp(tabletype,tablep->entries[i]) == 0){
            return tablep->ids[i];
        }
    }
    return 0;
}

PicnicTable* linkedToArray(DataBase *Db, int linkedSize){
    int i;
    PicnicTable *p = Db->picnicTableTable;    
    PicnicTable* newArray = malloc(sizeof(PicnicTable) * linkedSize);

    for (i=0; i < linkedSize; i++){
        newArray[i] = *p;
        newArray[i].next = NULL;
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

//--NOTE: move these function definition to DB_impl.c when submitting / testing on student server, linking doesn't work properly for vscode so for now its just here


void exportDB(char *fileName){          //takes database and turns back into a csv file
    FILE *fp;
    PicnicTable *curr = Db->picnicTableTable;
    //int i;
    fp = fopen(fileName, "w+");

    //write header to file
    fprintf(fp,"%s",Db->headBuffer);

    //write every entry to file
    while(curr->next != NULL){
        //binary write
        fprintf(fp,"%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s,%s\n",curr->siteID,
        Db->tableTypeTable->entries[curr->tableTypeID],
        Db->surfaceMaterialTable->entries[curr->surfaceID], 
        Db->structuralMaterialTable->entries[curr->structuralID],
        curr->streetave,
        curr->hoodID,
        fetchNeighbourhood(Db->neighbourhoodTable, curr->hoodID),
        curr->ward,
        curr->latitude,
        curr->longitude,
        curr->location,
        curr->geoPoint);
        
        curr = curr->next;
    }
    //write last line
    fprintf(fp,"%d,%s,%s,%s,%s,%d,%s,%s,%s,%s,%s,%s\n",curr->siteID,Db->tableTypeTable->entries[curr->tableTypeID],Db->surfaceMaterialTable->entries[curr->surfaceID], Db->structuralMaterialTable->entries[curr->structuralID],curr->streetave,curr->hoodID,fetchNeighbourhood(Db->neighbourhoodTable, curr->hoodID),curr->ward,curr->latitude,curr->longitude,curr->location,curr->geoPoint);
    fclose(fp);
    printf("---successfully exported %s---\n",fileName);
    return;
}

int countEntries(char *memberName, char *value){
    PicnicTable *p = Db->picnicTableTable;
    int count = 0;
    int translatedVal;
    if (p == NULL){     //check if the list is empty 
        printf("Database empty.\n");
        exit(EXIT_FAILURE);
    }

    //membernames: Table Type (works)
    if (strcmp(memberName,"Table Type") == 0){
        translatedVal = fetchTable(Db->tableTypeTable,value);
        //printf("translated val: %d\n", translatedVal);
        while(p->next != NULL){
            if (p->tableTypeID == translatedVal){count++;}
            p = p->next;
        }
        if (p->tableTypeID == translatedVal){count++;}  //check last line
        return count;

    }
    //Surface Material (works)
    if (strcmp(memberName, "Surface Material") == 0){
        translatedVal = fetchTable(Db->surfaceMaterialTable,value);
        printf("translated val: %d\n", translatedVal);
        while (p->next != NULL){
            if (p->surfaceID == translatedVal){count++;}
            p = p->next;
        }
        if (p->surfaceID == translatedVal){count++;}  //check last line
        return count;
    }
    //Structural Material (works)
    if (strcmp(memberName, "Structural Material") == 0){
        translatedVal = fetchTable(Db->structuralMaterialTable,value);
        printf("translated val: %d\n", translatedVal);
        while (p->next != NULL){
            if(p->structuralID == translatedVal){count++;}
            p = p->next;
        }
        if (p->structuralID == translatedVal){count++;}
        return count;
    }

    //Neighbourhood ID  (works)
    if (strcmp(memberName, "Neighbourhood Id") == 0){
        printf("translated val: %d\n", atoi(value));
        while(p->next != NULL){
            if(p->hoodID == atoi(value)){count++;}
            p = p->next;
        }
        if(p->hoodID == atoi(value)){count++;}
        return count;
    }

    //Neighbourhood Name (works)
    if (strcmp(memberName, "Neighbourhood Name") == 0){
        printf("translated val: %s\n", value);
        while(p->next != NULL){
            if(strcmp(p->neighName,value) == 0){count++;}
            p = p->next;
        }
        if(strcmp(p->neighName,value) == 0){count++;}
        return count;
    }

    //Ward (works)
    if (strcmp(memberName, "Ward") == 0){
        printf("translated val: %s\n", value);
        while(p->next != NULL){
            if(strcmp(p->ward,value) == 0){count++;}
            p = p->next;
        }
        if(strcmp(p->ward,value) == 0){count++;}
        return count;
    }
    else{
        return count;
    }
}

void sortByMember(char *memberName){
    int linkedSize;
    
    //to use qsort, make linked list into an array (helper function?), sort it, then turn back into linked list
    PicnicTable *newArray = linkedToArray(Db, Db->linkedSize);

    linkedSize = Db->linkedSize;
    printf("linked size: %d\n", linkedSize);

    //Table Type (works)
    if (strcmp(memberName, "Table Type") == 0){
        printf("sorting: %s\n", memberName);
        qsort(newArray,linkedSize,sizeof(PicnicTable),compareTableType);
    }

    //Surface Material (works)
    else if (strcmp(memberName, "Surface Material") == 0){
        printf("sorting: %s\n", memberName);
        qsort(newArray,linkedSize,sizeof(PicnicTable), compareSurfaceMat);
    }

    //Structural Material (works)
    else if (strcmp(memberName, "Structural Material") == 0){
        printf("sorting: %s\n", memberName);
        qsort(newArray,linkedSize,sizeof(PicnicTable), compareStructMat);
    }

    //Neighbourhood ID (works)
    else if (strcmp(memberName, "Neighbourhood Id") == 0){
        printf("sorting: %s\n", memberName);
        qsort(newArray,linkedSize,sizeof(PicnicTable), compareHoodID);
    }

    //Neighbourhood Name (works)
    else if (strcmp(memberName, "Neighbourhood Name") == 0){
        printf("sorting: %s\n", memberName);
        qsort(newArray,linkedSize,sizeof(PicnicTable), compareNeighName);
    }

    //Ward
    else if (strcmp(memberName, "Ward") == 0){
        printf("sorting: %s\n", memberName);
        qsort(newArray,linkedSize,sizeof(PicnicTable), compareWard);
    }

    //turn back into linked list
    PicnicTable *np = Db->picnicTableTable;
    PicnicTable *firstNode = arrayToLinked(newArray,linkedSize);

    //free the whole old linked list, then link Db to thew new list
    while (np != NULL){
        np = np->next;
        free(np);
    }
    Db->picnicTableTable = firstNode;

    //write the database to a .csv named after sorting member 
    exportDB(memberName);
}

void compressDB(char *filename){
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("Failed");
        exit(EXIT_FAILURE);
    }

    // Table
    fwrite(&Db->tableTypeTable->size, sizeof(int), 1, fp);
    for (int i = 0; i < Db->tableTypeTable->size; i++) {
        int len = strlen(Db->tableTypeTable->entries[i]) + 1;
        fwrite(&Db->tableTypeTable->ids[i], sizeof(int), 1, fp);
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(Db->tableTypeTable->entries[i], sizeof(char), len, fp);
    }

    // Surface Table
    fwrite(&Db->surfaceMaterialTable->size, sizeof(int), 1, fp);
    for (int i = 0; i < Db->surfaceMaterialTable->size; i++) {
        int len = strlen(Db->surfaceMaterialTable->entries[i]) + 1;
        fwrite(&Db->surfaceMaterialTable->ids[i], sizeof(int), 1, fp);
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(Db->surfaceMaterialTable->entries[i], sizeof(char), len, fp);
    }

    // Structural Table
    fwrite(&Db->structuralMaterialTable->size, sizeof(int), 1, fp);
    for (int i = 0; i < Db->structuralMaterialTable->size; i++) {
        int len = strlen(Db->structuralMaterialTable->entries[i]) + 1;
        fwrite(&Db->structuralMaterialTable->ids[i], sizeof(int), 1, fp);
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(Db->structuralMaterialTable->entries[i], sizeof(char), len, fp);
    }

    // Neighbourhood Table
    fwrite(&Db->neighbourhoodTable->size, sizeof(int), 1, fp);
    for (int i = 0; i < Db->neighbourhoodTable->size; i++) {
        int len = strlen(Db->neighbourhoodTable->nName[i]) + 1;
        fwrite(&Db->neighbourhoodTable->nID[i], sizeof(int), 1, fp);
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(Db->neighbourhoodTable->nName[i], sizeof(char), len, fp);
    }

    // Write PicnicTable (linked list)
    int count = 0;
    PicnicTable *curr = Db->picnicTableTable;
    while (curr != NULL) {
        count++;
        curr = curr->next;
    }
    fwrite(&count, sizeof(int), 1, fp);

    curr = Db->picnicTableTable;
    while (curr != NULL) {
        // Write fixed-size members
        fwrite(&curr->tableID, sizeof(int), 1, fp);
        fwrite(&curr->siteID, sizeof(int), 1, fp);
        fwrite(&curr->tableTypeID, sizeof(int), 1, fp);
        fwrite(&curr->surfaceID, sizeof(int), 1, fp);
        fwrite(&curr->structuralID, sizeof(int), 1, fp);
        fwrite(&curr->hoodID, sizeof(int), 1, fp);

        // Write strings with lengths
        int len = strlen(curr->streetave) + 1;
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(curr->streetave, sizeof(char), len, fp);

        len = strlen(curr->ward) + 1;
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(curr->ward, sizeof(char), len, fp);

        len = strlen(curr->latitude) + 1;
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(curr->latitude, sizeof(char), len, fp);

        len = strlen(curr->longitude) + 1;
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(curr->longitude, sizeof(char), len, fp);

        len = strlen(curr->neighName) + 1;
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(curr->neighName, sizeof(char), len, fp);

        len = strlen(curr->location) + 1;
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(curr->location, sizeof(char), len, fp);

        len = strlen(curr->geoPoint) + 1;
        fwrite(&len, sizeof(int), 1, fp);
        fwrite(curr->geoPoint, sizeof(char), len, fp);

        curr = curr->next;
    }

    fclose(fp);
    printf("Database compressed to %s\n", filename);

    //freeDB()?
}

void unCompressDB(char *filename){
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Failed");
        exit(EXIT_FAILURE);
    }

    // Initialize database
    Db = malloc(sizeof(DataBase));
    Db->tableTypeTable = malloc(sizeof(LookupTable));
    Db->surfaceMaterialTable = malloc(sizeof(LookupTable));
    Db->structuralMaterialTable = malloc(sizeof(LookupTable));
    Db->neighbourhoodTable = malloc(sizeof(NeighbourhoodTable));
    Db->picnicTableTable = NULL;

    // Read lookup tables
    int size;
    fread(&size, sizeof(int), 1, fp);
    Db->tableTypeTable->size = size;
    Db->tableTypeTable->capacity = size;

    for (int i = 0; i < size; i++) {
        fread(&Db->tableTypeTable->ids[i], sizeof(int), 1, fp);
        int len;
        fread(&len, sizeof(int), 1, fp);
        Db->tableTypeTable->entries[i] = malloc(len);
        fread(Db->tableTypeTable->entries[i], sizeof(char), len, fp);
    }

    // Surface Table
    fread(&size, sizeof(int), 1, fp);
    Db->surfaceMaterialTable->size = size;
    Db->surfaceMaterialTable->capacity = size;

    for (int i = 0; i < size; i++) {
        fread(&Db->surfaceMaterialTable->ids[i], sizeof(int), 1, fp);
        int len;
        fread(&len, sizeof(int), 1, fp);
        Db->surfaceMaterialTable->entries[i] = malloc(len);
        fread(Db->surfaceMaterialTable->entries[i], sizeof(char), len, fp);
    }

    // Structural Table
    fread(&size, sizeof(int), 1, fp);
    Db->structuralMaterialTable->size = size;
    Db->structuralMaterialTable->capacity = size;

    for (int i = 0; i < size; i++) {
        fread(&Db->structuralMaterialTable->ids[i], sizeof(int), 1, fp);
        int len;
        fread(&len, sizeof(int), 1, fp);
        Db->structuralMaterialTable->entries[i] = malloc(len);
        fread(Db->structuralMaterialTable->entries[i], sizeof(char), len, fp);
    }

    // Neighbourhood Table
    fread(&size, sizeof(int), 1, fp);
    Db->neighbourhoodTable->size = size;
    Db->neighbourhoodTable->capacity = size;

    for (int i = 0; i < size; i++) {
        fread(&Db->neighbourhoodTable->nID[i], sizeof(int), 1, fp);
        int len;
        fread(&len, sizeof(int), 1, fp);
        Db->neighbourhoodTable->nName[i] = malloc(len);
        fread(Db->neighbourhoodTable->nName[i], sizeof(char), len, fp);
    }

    // Read PicnicTable (linked list)
    int count;
    fread(&count, sizeof(int), 1, fp);

    PicnicTable *prev = NULL;
    for (int i = 0; i < count; i++) {
        PicnicTable *node = malloc(sizeof(PicnicTable));

        // Read fixed members
        fread(&node->tableID, sizeof(int), 1, fp);
        fread(&node->siteID, sizeof(int), 1, fp);
        fread(&node->tableTypeID, sizeof(int), 1, fp);
        fread(&node->surfaceID, sizeof(int), 1, fp);
        fread(&node->structuralID, sizeof(int), 1, fp);
        fread(&node->hoodID, sizeof(int), 1, fp);

        // Read strings with their lengths
        int len;

        fread(&len, sizeof(int), 1, fp);
        fread(node->streetave, sizeof(char), len, fp);

        fread(&len, sizeof(int), 1, fp);
        fread(node->ward, sizeof(char), len, fp);

        fread(&len, sizeof(int), 1, fp);
        fread(node->latitude, sizeof(char), len, fp);

        fread(&len, sizeof(int), 1, fp);
        fread(node->longitude, sizeof(char), len, fp);

        fread(&len, sizeof(int), 1, fp);
        fread(node->neighName, sizeof(char), len, fp);

        fread(&len, sizeof(int), 1, fp);
        fread(node->location, sizeof(char), len, fp);

        fread(&len, sizeof(int), 1, fp);
        fread(node->geoPoint, sizeof(char), len, fp);

        node->next = NULL;
        Db->linkedSize = 1;
        Db->currCapacity = 100;

        if (prev == NULL) {
            Db->picnicTableTable = node;
        } else {
            prev->next = node;
        }
        prev = node;
    }

    fclose(fp);
    printf("Database uncompressed from %s\n", filename);
}

void freeDB(void){
    int i;
    //int e;
    PicnicTable *p = Db->picnicTableTable;
    for (i=0; i < 6; i++){
        free(Db->tableTypeTable->entries[i]);
        free(Db->surfaceMaterialTable->entries[i]);
        free(Db->structuralMaterialTable->entries[i]);
    }
    free(Db->tableTypeTable);
    free(Db->surfaceMaterialTable);
    free(Db->structuralMaterialTable);

    for (i=0; i < 100; i++){
        free(Db->neighbourhoodTable->nName[i]);
    }
    free(Db->neighbourhoodTable);

    //free PicnicTable nodes
    while(p->next != NULL){
        PicnicTable *next = p->next;
        free(p->streetave);
        free(p->ward);
        free(p->latitude);
        free(p->longitude);
        free(p->neighName);
        free(p->location);
        free(p->geoPoint);
        free(p);
        p = next;
    }
    //free(Db->headBuffer);       //free headBuffer
    //free(Db);                   //free Db
}

//test main function (for vsCode, delete later)
int main (void){
    importDB("/Users/Joaquin/Downloads/cs/cmpt201/CMPT201/labs/cmput201_A3/skeleton files/PicnicTableSmall.csv");
    //importDB("PicnicTableSmall.csv");                                this doesn't work for some reason, the whole file path needs to be written in my case
    exportDB("test.csv");

    //all testing here will be added to testing folder
    //testing countEntries()
    //int count = countEntries("Table Type","Square Picnic Table");
    //int count = countEntries("Surface Material","Composite");
    //int count = countEntries("Structural Material", "Metal");
    //int count = countEntries("Neighbourhood Id", "2630");
    //int count = countEntries("Neighbourhood Name", "RIVER VALLEY HERMITAGE");
    //int count = countEntries("Ward","Ward Karhiio");
    //printf("count: %d\n",count);

    //testing sortByMember() - all works
    //sortByMember("Table Type"); 
    //sortByMember("Surface Material"); 
    //sortByMember("Structural Material");
    //sortByMember("Neighbourhood Id");
    //sortByMember("Neighbourhood Name");
    //sortByMember("Ward");

    return 0;
}