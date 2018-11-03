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
    int i=0;//when map size splitted by x first value will be row. second value will be column.
    //getting row and column size of map matrix.
    printf("output file name: %s\n",outputFileName);
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

//    printf("map:\n");
//    for(int i=0;i<mapRowSize;i++){
//        for(int j=0;j<mapColumnSize;j++){
//            printf("%d",my2DMapArray[i][j]);
//        }
//        printf("\n");
//    }
//    printf("key:\n");
//    for(int i=0;i<keySize;i++){
//        for(int j=0;j<keySize;j++){
//            printf("%d",my2DKeyArray[i][j]);
//        }
//        printf("\n");
//    }
    findMulOfArray(my2DMapArray,my2DKeyArray,keySize,0,0,mapRowSize,mapColumnSize,outputFileName);
    fclose(fptrMap);
    fclose(fptrKey);
    fclose(fptrWrite);
    printf("\n");
    //frees the allocated memory
    for(int i = 0; i < mapRowSize; i++){
        free(my2DMapArray[i]);
    }
    free(my2DMapArray);
    return 0;
}
//findMulOfArray function multiplies key matrix with map matrix
int findMulOfArray(int ** array1, int ** array2, int sizeOfArray, int startRow, int startColumn, int mapRowSize, int mapColumnSize, char * outputName){
    int newRow=0;//we need new startRow value for recursive function
    int newColumn=0;//we need new startColumn value for recursive function
    int midRow=startRow+1;
    int midCol=startColumn+1;
    int mul=0;
    for(int i=startRow;i<startRow+sizeOfArray;i++){
        for(int j=startColumn;j<startColumn+sizeOfArray;j++){
                mul+=array1[i][j]*array2[i%sizeOfArray][j%sizeOfArray];
//                printf("array[%d][%d] : %d",i,j,array1[i][j]);
//                printf(" carpi key[%d][%d] : %d ",i%sizeOfArray,j%sizeOfArray,array2[i%sizeOfArray][j%sizeOfArray]);
//                printf("esittir mul: %d\n",mul);
        }
    }
    FILE * fptrWrite=fopen(outputName,"r");
    fprintf(fptrWrite,"%d,%d:%d\n",midRow,midCol,mul);
    printf("%d,%d:%d\n",midRow,midCol,mul);
    if(mul%5==0){
        //printf("found treasure");
        return 0;
    }
    //findMulOfArray(array1,array2,sizeOfArray,newRow,startColumn,mapRowSize,mapColumnSize);

    if(mul%5==1){
        newRow=startRow-sizeOfArray;
        newColumn=startColumn;
        if(newRow>=0){
//            printf("go up\n");
//            printf("go up new row: %d\n",newRow);
        }
        if(newRow<0){
            newRow=startRow+sizeOfArray;
//            printf("we cant move up.moving down\n");
//            printf("go down new row: %d\n",newRow);
        }
    }
    if(mul%5==2){
        newRow=startRow+sizeOfArray;
        newColumn=startColumn;
        if(newRow<mapRowSize){
//            printf("go down\n");
//            printf("go down new row: %d\n",newRow);
        }
        if(newRow>=mapRowSize){
            newRow=startRow-sizeOfArray;
//            printf("we cant move down.moving up\n");
//            printf("go up new row: %d\n",newRow);
        }
    }
    if(mul%5==3){
        newColumn=startColumn+sizeOfArray;
        newRow=startRow;
        if(newColumn<mapColumnSize){
//            printf("go right new col: %d\n",newColumn);
        }
        if(newColumn>=mapColumnSize){
            newColumn=startColumn-sizeOfArray;
//            printf("we cant move right.moving left\n");
//            printf("go left new col: %d\n",newColumn);
        }
    }
    if(mul%5==4){
        newColumn=startColumn-sizeOfArray;
        newRow=startRow;
        if(newColumn>=0){
//            printf("go left\n");
//            printf("go left new col: %d\n",newColumn);
        }
        if(newColumn<0){
            newColumn=startColumn+sizeOfArray;
//            printf("we cant move left.moving right\n");
//            printf("go right new col: %d\n",newColumn);
        }
    }
    return findMulOfArray(array1,array2,sizeOfArray,newRow,newColumn,mapRowSize,mapColumnSize,outputName);
}
/*
 printf("Enter num: ");
 scanf("%d",&num);
 fprintf(fptr,"%d",num);
 */
