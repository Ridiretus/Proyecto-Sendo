#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HashMap.h"


/********************** HashMap.c **************************/

void enlarge(HashMap* map);
long hash (long key, long capac);

//pregunta 1: crear HashMap
HashMap* createHashMap(int capac){
    int i;
    HashMap* map=(HashMap*) malloc(sizeof(HashMap));
    map->capac=capac;
    map->size=0;
    map->hashArray = malloc(sizeof(hashElem*)*map->capac);
    for(i=0;i<map->capac;i++) map->hashArray[i]=NULL;
    return map;
}

//pregunta 2: función Hash
long hash (long key, long capac){
    float r=0.2;
            float d;
            long h,n=capac;
                d=(r*key)-floor(r*key);
                h= (n*d);
            return h;
}

//pregunta 3: función de búsqueda
void* search(HashMap* map, long key){
    int i;
    int hvalue=hash(key,map->capac);
    for(i=0;i<map->capac;i++){
        int new_hvalue=(hvalue+i)%map->capac;
        if(!map->hashArray[new_hvalue]) return NULL;
        else if(map->hashArray[new_hvalue]->key == key){
           return map->hashArray[new_hvalue]->data;
        }
    }
    return NULL;
}

//pregunta 4: inserción
void insert(HashMap* map, long key, void* data){
   int hvalue=hash(key,map->capac);
   if(map->hashArray[hvalue]){ //se busca una casilla disponible a partir de hvalue
       int new_hvalue=-1, i;
       for(i=1;i<map->capac;i++){
          new_hvalue=(hvalue+i)%map->capac;
          if(!map->hashArray[new_hvalue] || !map->hashArray[new_hvalue]->data){
             hvalue=new_hvalue;
             break;
          }
       }
   }

   if(!map->hashArray[hvalue]) map->hashArray[hvalue]=(hashElem*) malloc(sizeof(hashElem));
   map->hashArray[hvalue]->data=data;
   map->hashArray[hvalue]->key=key;
   map->size++;
   if((double)map->size/(double)map->capac > 0.7) enlarge(map); //agranda la tabla
}

//pregunta 5: eliminación
void erase(HashMap* map, long key){
    int i;
    int hvalue=hash(key,map->capac);
    for(i=0;i<map->capac;i++){
        int new_hvalue=(hvalue+i)%map->capac;
        if(!map->hashArray[new_hvalue]) return;
        else if(map->hashArray[new_hvalue]->key == key){
           map->hashArray[new_hvalue]->data=NULL;
        }
    }
}

//pregunta 6: enlarge
void enlarge(HashMap* map){
    hashElem **old_array=map->hashArray;
    int old_capac=map->capac;

    //se reinicializan las variables de la tabla con el nuevo tamaño
    int i;
    map->capac*=2;
    map->size=0;
    map->hashArray = malloc(sizeof(hashElem*)*map->capac);
    for(i=0;i<map->capac;i++) map->hashArray[i]=NULL;

    //se reasingnan los elementos de la tabla antigua a la nueva
    for(i=0;i<old_capac;i++){
       if(old_array[i]){
           if(old_array[i]->data)
              insert(map, old_array[i]->key, old_array[i]->data);
           free(old_array[i]);
       }

    }

    free(old_array);
}

//pregunta 7: first y next
void* First(HashMap* map){
    int i=0;
    for(i=0;i<map->capac;i++)
        if(map->hashArray[i] && map->hashArray[i]->data) {
            map->current=i;
            return map->hashArray[i]->data;
        }
    return NULL;
}

void* Next(HashMap* map){
    int i;
    for(i=map->current+1;i<map->capac;i++){
        if(map->hashArray[i] && map->hashArray[i]->data) {
            map->current=i;
            return map->hashArray[i]->data;
        }
    }
    return NULL;
}

/**************************************************************/



/********************** main.c *****************************/



/**************************************************************/
