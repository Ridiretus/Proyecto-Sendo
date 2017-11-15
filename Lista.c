#include "Lista.h"
#include <stdlib.h>
#include <stdio.h>

List* create_list(){
    List* nuevo=(List*)malloc(sizeof(List));
    nuevo->current = nuevo->first;
    nuevo->first = NULL;
    nuevo->last  = NULL;
    nuevo->cont  = 0;

    return nuevo;
}

Nodo* create_nodo( void* dato ){
    Nodo* nuevo=(Nodo*)malloc(sizeof(Nodo));
    nuevo->dato = dato;
    nuevo->next = NULL;
    nuevo->prev = NULL;

    return nuevo;
}

void push_front( List* lista, void* dato ){
    Nodo* nuevo = create_nodo(dato);

    if( lista->cont>0 ){
        nuevo->next = lista->first;
        nuevo->prev = lista->last;
        lista->first->prev = nuevo;
        lista->last->next = nuevo;
        lista->last = lista->first;
        lista->first = nuevo;
    }else{
        nuevo->next = nuevo;
        nuevo->prev = nuevo;
        lista->first = nuevo;
        lista->last = nuevo;
    }

    lista->cont++;
}

void push_back( List* lista, void* dato ){
    Nodo* nuevo = create_nodo(dato);

    if( lista->cont>0 ){
        lista->last->next = nuevo;
        lista->first->prev = nuevo;
        nuevo->next = lista->first;
        nuevo->prev = lista->last;
        lista->last = nuevo;
    }else{
        nuevo->next = nuevo;
        nuevo->prev = nuevo;
        lista->first = nuevo;
        lista->last = nuevo;
    }

    lista->cont++;
}
void push_current( List* lista, void* dato ){
    Nodo* nuevo = create_nodo(dato);

    if( lista->cont > 0 ){
        lista->current->next->next->prev = nuevo;
        nuevo->next = lista->current->next->next;
        lista->current->next = nuevo;
        nuevo->prev = lista->current;
    }else{
        nuevo->next = nuevo;
        nuevo->prev = nuevo;
        lista->first = nuevo;
        lista->last = nuevo;
    }
}

void pop_current( List* lista ){
    if( lista->cont > 0 ){
        lista->current->prev->next = lista->current->next;
        lista->current->next->prev = lista->current->prev;
        lista->current = lista->current->next;
        lista->cont--;
    }
}

void pop_back( List* lista ){
    if( lista->cont > 0 ){
        lista->first->prev = lista->last->prev;
        lista->last->prev->next = lista->first;
        lista->last = lista->first->prev;
        lista->cont--;
    }
}

void pop_front( List* lista ){
    if( lista->cont > 0 ){
        lista->last->next = lista->first->next;
        lista->first->next->prev = lista->last;
        lista->first = lista->last->next;
        lista->cont--;
    }
}


void* first( List* list ){
    list->current = list->first;

    return list->first->dato;
}

void* next( List *list ){
    list->current = list->current->next;

    return list->current->dato;
}

void* last( List* lista ){
    return lista->last->dato;
}

void* prev( List* lista ){
    lista->current = lista->current->prev;

    return lista->current->dato;
}

void clean( List* L ){
    while( L->first != NULL ){
        pop_front(L);
    }
}
