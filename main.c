#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    
    char * sizeOfMap=argv[1];
    char * sizeOfKey=argv[2];
    FILE * fptrMap = fopen(argv[3],"r");;
    FILE * fptrKey = fopen(argv[4],"r");;
    char * mapToken;
    char * line = NULL;
    int ** my2DMapArray;
    int ** my2DKeyArray;
    size_t length = 0;
    ssize_t reading;
    int keySize=atoi(sizeOfKey);//getting row and column size of key matrix.
    int mapRowSize,mapColumnSize;
    int i=0;
    if(fptrMap == NULL){
        printf("Please provide a map\n");
        exit(1);
    }
    if(fptrKey == NULL){
        printf("Please provide a key\n");
        exit(1);
    }
    //getting row and column size of map matrix.
    for (mapToken = strtok(sizeOfMap, "x"); mapToken; mapToken = strtok(NULL, "x"))
    {
        if(i==0){
            mapRowSize=atoi(mapToken);
        }
        if(i==1){
            mapColumnSize=atoi(mapToken);
        }
        i++;
    }
    printf("key row size: %d\n",keySize);
    printf("key column size: %d\n",keySize);
    printf("map row size=%d\n", mapRowSize);
    printf("map column size=%d\n", mapColumnSize);
    //creates 2DMapArray by using malloc.
    my2DMapArray = malloc(mapRowSize*sizeof(int*));
    for(int i=0;i<mapRowSize;i++){
        my2DMapArray[i]=malloc(mapColumnSize*sizeof(int));
    }
    //creates 2DKeyArray by using malloc.
    my2DKeyArray = malloc(keySize*sizeof(int*));
    for(int i=0;i<keySize;i++){
        my2DKeyArray[i]=malloc(keySize*sizeof(int));
    }
    //fills 2DMapArray with map values.
    int tempRow=0;
    while ((reading = getline(&line, &length, fptrMap)) != -1) {
        //printf("length : %zu", length);
        int tempColumn=0;
        char * token;
        char * str=line;
        tempRow++;
        for (token = strtok(str, " "); token; token = strtok(NULL, " ")) {
            //printf("satir: %d",tempRow-1);
            //printf("sutun: %d\n",tempColumn);
            //printf("\n")
            //printf("%d . satir %d . sutun =%d\n",tempRow-1,tempColumn, atoi(token));
            my2DMapArray[tempRow-1][tempColumn]=atoi(token);
            tempColumn++;
        }
    }
    //fills 2DKeyArray with key values.
    int tempRow1=0;
    while ((reading = getline(&line, &length, fptrKey)) != -1) {
        //printf("length : %zu", length);
        int tempColumn=0;
        char * token;
        char * str=line;
        tempRow1++;
        for (token = strtok(str, " "); token; token = strtok(NULL, " ")) {
            //printf("satir: %d",tempRow-1);
            //printf("sutun: %d\n",tempColumn);
            //printf("\n")
            //printf("%d . satir %d . sutun =%d\n",tempRow-1,tempColumn, atoi(token));
            my2DKeyArray[tempRow1-1][tempColumn]=atoi(token);
            tempColumn++;
        }
    }

    printf("map:\n");
    for(int i=0;i<mapRowSize;i++){
        for(int j=0;j<mapColumnSize;j++){
            printf("%d",my2DMapArray[i][j]);
        }
        printf("\n");
    }
    printf("key:\n");
    for(int i=0;i<keySize;i++){
        for(int j=0;j<keySize;j++){
            printf("%d",my2DKeyArray[i][j]);
        }
        printf("\n");
    }
    
    fclose(fptrMap);
    fclose(fptrKey);
    printf("\n");
    for(int i = 0; i < mapRowSize; i++){
        free(my2DMapArray[i]);
    }
    free(my2DMapArray);
    return 0;
    
}
/*
 printf("Enter num: ");
 scanf("%d",&num);
 fprintf(fptr,"%d",num);
 */
