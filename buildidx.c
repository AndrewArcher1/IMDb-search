#include "util.h"
#include "hashfn.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]){
   
   if( argc != 3 ) {
      fprintf( stderr, "Usage: %s filename.kv capacity\n", argv[0]);
      exit(1);
   }
   
   int k=0;
   int i =0;
   int j=0;
   long capacity = atoi(argv[2]);
   int hashV =0;
   int hashK = 0;
   
   char fileName1[30];
   char fileName2[30];
   char key[STRLEN];
   char val[STRLEN];

   FILE* fp_kv;
   FILE* fp_khs;
   FILE* fp_vhs;

   
   strncpy(fileName1, argv[1], strlen(argv[1])-3);
   strcpy(fileName2, fileName1);
  

   fp_kv = fopen(argv[1], "r");
   fp_khs = fopen(strcat(fileName1,".khs"),"wb+");
   fp_vhs = fopen(strcat(fileName2,".vhs"),"wb+");
   
   write_empty(fp_khs,capacity);
   write_empty(fp_vhs,capacity);

   int index =0;
   
   do{

      i = read_keyval(fp_kv, key, val);
      read_val(fp_kv,j,val);
      read_key(fp_kv,k,key);
      
      hashV = hashfn(val, capacity);
      hashK = hashfn(key, capacity);

      read_index(fp_vhs, hashV,&index);
      while(index!=-1){
        
        if(hashV == capacity){
           hashV =0; 
        }else{
           hashV++;
        }
         read_index(fp_vhs,hashV,&index);
      }

      if(index == -1){
      write_index(fp_vhs,j,hashV);
      j++;
      }
      
      read_index(fp_khs, hashK,&index);
      while(index != -1){
        
        if(hashK == capacity){
           hashK =0; 
        }else{
           hashK++;
        }
         read_index(fp_khs,hashK,&index);
      }

      if(index == -1){
      write_index(fp_khs,k,hashV);
      k++;
      }

   }while( i == 2 );

   fclose(fp_kv);
   fclose(fp_khs);
   fclose(fp_vhs);
   
   return(0);
}

