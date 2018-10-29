#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    
    FILE * fptr = fopen(argv[1],"r");;
    char * sizeOfMap=argv[2];
    char * sizeOfKey=argv[3];
    char * mapToken;
    char * line = NULL;
    int ** my2DArray;
    size_t length = 0;
    ssize_t reading;
    int keySize=atoi(sizeOfKey);//getting row and column size of key matrix.
    int mapRowSize,mapColumnSize;
    int i=0;
    if(fptr == NULL){
        printf("Please provide an argument\n");
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
    //creates 2D array by using malloc.
    my2DArray = malloc(mapRowSize*sizeof(int));
    for(int i=0;i<mapRowSize;i++){
        my2DArray[i]=malloc(mapColumnSize*sizeof(int));
    }
    //fills 2D array with map values.
    int tempRow=0,tempColumn=0;
    while ((reading = getline(&line, &length, fptr)) != -1) {
        //printf("line : %s", line);
        char * token;
        char * str=line;
        tempRow++;
        for (token = strtok(str, " "); token; token = strtok(NULL, " ")) {
            printf("satir: %d",tempRow-1);
            int a=tempRow-1;
            int b=tempColumn;
            printf("sutun: %d\n",tempColumn);
            //printf("\n")
            //my2DArray[a][b]=atoi(token);
            tempColumn++;
            //printf("token=%d\n", atoi(token));
        }
        tempColumn=0;
    }
    printf("3ebes: %d\n",my2DArray[3][5]);
    fclose(fptr);
    printf("\n");
    free(my2DArray);
    return 0;
    
}
/*
 printf("Enter num: ");
 scanf("%d",&num);
 fprintf(fptr,"%d",num);
 */
