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
    char headBuffer[200];
    int i=0, colCount, uID=0;
    
    //initialize database
    Db = malloc(sizeof(DataBase));

    Db->tableTypeTable = malloc(sizeof(LookupTable));
    Db->surfaceMaterialTable = malloc(sizeof(LookupTable));
    Db->structuralMaterialTable = malloc(sizeof(LookupTable));
    Db->neighbourhoodTable = malloc(sizeof(NeighbourhoodTable));
    

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

    fgets(headBuffer,200,fp);                   //skip reading the header columns

    while(fgets(testBuffer,1000,fp)){           //read line by line (this is where a new node starts)
        char *token = strtok(testBuffer, ",");
        colCount = 0;
        printf("\n");
        
        PicnicTable *node = malloc(sizeof(PicnicTable));
        node->capacity = 100;
        
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
            }

            token = strtok(NULL, ",");
            colCount++;
        }
        //here is when a node is finished being made
        uID++;
        node->size++;
        node->next = NULL;

        //insert node into linked list
        if (Db->picnicTableTable == NULL){      //if the list is empty, this node is the first one
            printf("---first!---\n");
            Db->picnicTableTable = node;
        }
        else{                                   //otherwise, probe to the end of the linked list 
            PicnicTable *p = Db->picnicTableTable;
            printf("--next!--\n");
            while(p->next != NULL){
                p = p->next;
            }
            p->next = node;
            printf("---end---\n");
        }

        //check nodes
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
    }

    //print lookup tables
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

    //print all nodes in order
    PicnicTable *curr = Db->picnicTableTable;
    while (curr->next != NULL){
        printf("%d %s\n",curr->tableID, curr->streetave);
        curr = curr->next;
    }
    printf("%d %s\n",curr->tableID, curr->streetave);
    printf("---end importDB()---\n");
}

void exportDB(char *fileName){
    printf("exporting: %s", fileName);
}

//int countEntries(char *memberName, char *value){}

//void sortByMember(char *memberName){}

//void compressDB(char *filename){}

//void unCompressDB(char *filename){}

//void freeDB(void);

//test main function (for vsCode, delete later)
int main (void){
    importDB("/Users/Joaquin/Downloads/cs/cmpt201/CMPT201/labs/cmput201_A3/skeleton files/PicnicTableSmall.csv");
    //importDB("PicnicTableSmall.csv");                                this doesn't work for some reason, the whole file path needs to be written in my case
    exportDB("test.csv");

    return 0;
}