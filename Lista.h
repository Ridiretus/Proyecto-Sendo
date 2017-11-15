#ifndef LISTA_H
#define LISTA_H

typedef struct nodo{

    struct nodo* prev;
    struct nodo* next;
    void* dato;

}Nodo;

typedef struct{

    Nodo* first;
    Nodo* current;
    Nodo* last;
    int cont;

}List;
//Crea y inicializa un nuevo dato de tipo Lista(work).
List* create_list();

//Crea y incializa un nuevo dato de tipo Nodo(work).
Nodo* create_nodo(void*);

//Inserta un nuevo nodo al inicio de la lista(work).
void push_front(List*,void*);

//Inserta un nuevo nodo al final de la lista(work).
void push_back(List*,void*);

//Inserta un nuevo nodo en la posicion actual de la lista.
void push_current(List*,void*);

//Elimina un nodo al final de la lista(work).
void pop_back(List*);

//Elimina un nodo al principio de la lista(work).
void pop_front(List*);

//Elimina el nodo actual de la lista.
void pop_current(List*);

//retorna un puntero hacia el primer dato de la lista y hace que el nodo actual sea igual al primer nodo(work).
void* first(List*);

//Hace que el nodo actual avance hacia el siguiente nodo(work);
void* next(List*);

//Hace que el nodo actual sea igual al ultimo dato de la lista tambien retorna un puntero a este dato(work);
void* last(List*);

//Hace que el nodo actual sea igual a su nodo previo(work).
void* prev(List*);

//Esta funcion limpia la lista, elimina todos los nodos menos uno y ese lo deja vacio.
void clean(List*);

#endif
