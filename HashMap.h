#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <stdlib.h>

typedef struct{
   long key;
   void* data;
}hashElem;


typedef struct{
   hashElem** hashArray;
   int size; //cant. elementos no nulos
   int capac; //tamanno tabla

   int current; //indice al elemento actual
}HashMap;

HashMap* createHashMap(int capac);

void insert(HashMap* map, long key, void* data);

void erase(HashMap* map, long key);

void* search(HashMap* map, long key);

void* First(HashMap* map);

void* Next(HashMap* map);

#endif
