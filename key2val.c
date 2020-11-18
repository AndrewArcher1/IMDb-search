#include "util.h"
#include "hashfn.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

    if(argc != 3){
        fprintf( stderr, "Usage: %s filename.kv ‘search term’\n", argv[0]);
        exit(1);
    }
    // makes the file pointers
    FILE* fp_kv;
    FILE* fp_khs;

    char key[STRLEN];
    char val[STRLEN];
    char fileName[30];
    char find[30];
    
    strcpy(find,argv[2]);

    strncpy(fileName, argv[1], strlen(argv[1])-3);

    //opens the files
    fp_kv = fopen(argv[1], "r");
    fp_khs = fopen(strcat(fileName,".khs"),"wb+");

    int capacity = get_capacity(fp_kv);

    int hash = hashfn(find, capacity);
    int buff = hash;

    int index = 0;
    int i =0;
    
    do
    {
        read_keyval(fp_kv,key , val);
        read_index(fp_khs,hash, &index);
        read_key(fp_kv, hash, key);

	//checks if at the end of file
        if(capacity == hash){
            hash=0;
        }else{
            hash++;
        }

        read_index(fp_khs,hash,&index);
        read_key(fp_kv,hash,key);
        
	//prints the value if found
        if(strcmp(find, key)==0){
            read_val(fp_kv, hash, val);
            printf("%s\n",val );
            i=1;
        }
        if(capacity == hash){
            hash=0;
        }else{
            hash ++;
        }
        
    } while (hash != buff);
	
    //prints if the is not found
    if(i ==0){
        printf("NOT FOUND\n");
    }
    fclose(fp_khs);
    fclose(fp_kv);
    return(0);
}
