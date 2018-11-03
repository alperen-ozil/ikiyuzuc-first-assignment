#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    
    char * sizeOfMap=argv[1];
    char * sizeOfKey=argv[2];
    FILE * fptrMap = fopen(argv[3],"r");
    FILE * fptrKey = fopen(argv[4],"r");
    FILE * fptrWrite = fopen(argv[5],"w");
    char * outputFileName=argv[5];
    char * mapToken;
    char * line = NULL;
    int ** my2DMapArray;
    int ** my2DKeyArray;
    int findMulOfArray(int ** , int ** , int , int , int , int , int , char * );
    size_t length = 0;
    ssize_t reading;
    int keySize=atoi(sizeOfKey);//getting row and column size of key matrix.
    int mapRowSize,mapColumnSize;
    int mapSizeIndex=0;//when map size splitted by x first value will be row. second value will be column.
    //getting row and column size of map matrix.
    //printf("output file name: %s\n",outputFileName);
    for (mapToken = strtok(sizeOfMap, "x"); mapToken; mapToken = strtok(NULL, "x"))
    {
        if(mapSizeIndex==0){
            mapRowSize=atoi(mapToken);
        }
        if(mapSizeIndex==1){
            mapColumnSize=atoi(mapToken);
        }
        mapSizeIndex++;
    }
    //creates 2DMapArray by using malloc.
    my2DMapArray = malloc(mapRowSize*sizeof(int * ));
    int mapArrayIndex;
    for(mapArrayIndex=0;mapArrayIndex<mapRowSize;mapArrayIndex++){
        my2DMapArray[mapArrayIndex]=malloc(mapColumnSize*sizeof(int));
    }
    //creates 2DKeyArray by using malloc.
    my2DKeyArray = malloc(keySize*sizeof(int * ));
    int mapKeyIndex;
    for(mapKeyIndex=0;mapKeyIndex<keySize;mapKeyIndex++){
        my2DKeyArray[mapKeyIndex]=malloc(keySize*sizeof(int));
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
    findMulOfArray(my2DMapArray,my2DKeyArray,keySize,0,0,mapRowSize,mapColumnSize,outputFileName);
    fclose(fptrMap);
    fclose(fptrKey);
    fclose(fptrWrite);
    //frees the allocated memory
    int freeMap;
    for(freeMap = 0; freeMap < mapRowSize; freeMap++){
        free(my2DMapArray[freeMap]);
    }
    free(my2DMapArray);
    return 0;
}
//findMulOfArray function multiplies key matrix with map matrix
int findMulOfArray(int ** array1, int ** array2, int sizeOfArray, int startRow, int startColumn, int mapRowSize, int mapColumnSize, char * outputName){
    int newRow=0;//we need new startRow value for recursive function
    int newColumn=0;//we need new startColumn value for recursive function
    int midRow=startRow+sizeOfArray/2;
    int midCol=startColumn+sizeOfArray/2;
    int mul=0;
    int startRowIndex;
    int startColumnIndex;
    for(startRowIndex=startRow;startRowIndex<startRow+sizeOfArray;startRowIndex++){
        for(startColumnIndex=startColumn;startColumnIndex<startColumn+sizeOfArray;startColumnIndex++){
                mul+=array1[startRowIndex][startColumnIndex]*array2[startRowIndex%sizeOfArray][startColumnIndex%sizeOfArray];
        }
    }
    FILE * fptrWrite=fopen(outputName,"a+");
    fprintf(fptrWrite,"%d,%d:%d\n",midRow,midCol,mul);
    if(mul%5==0){
        return 0;
    }

    if(mul%5==1){
        newRow=startRow-sizeOfArray;
        newColumn=startColumn;
        if(newRow>=0){
        }
        if(newRow<0){
            newRow=startRow+sizeOfArray;
        }
    }
    if(mul%5==2){
        newRow=startRow+sizeOfArray;
        newColumn=startColumn;
        if(newRow<mapRowSize){
        }
        if(newRow>=mapRowSize){
            newRow=startRow-sizeOfArray;
        }
    }
    if(mul%5==3){
        newColumn=startColumn+sizeOfArray;
        newRow=startRow;
        if(newColumn<mapColumnSize){
        }
        if(newColumn>=mapColumnSize){
            newColumn=startColumn-sizeOfArray;
        }
    }
    if(mul%5==4){
        newColumn=startColumn-sizeOfArray;
        newRow=startRow;
        if(newColumn>=0){
        }
        if(newColumn<0){
            newColumn=startColumn+sizeOfArray;
        }
    }
    fclose(fptrWrite);
    return findMulOfArray(array1,array2,sizeOfArray,newRow,newColumn,mapRowSize,mapColumnSize,outputName);
}

