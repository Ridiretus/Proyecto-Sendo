#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "Lista.h"
#include "HashMap.h"
#ifdef _WIN32
#define clear system("cls")
#else
#define clear system("clear")
#endif

typedef struct{

  char nombre[60];
  int flag_lose;
  int lose_turn;

}jugador;

typedef struct{
  char nombre[30];
  char descripcion[400];
  int nivel;
}reto;

//Prototipacion de funciones
void cargar_jugadores(List*);// carga los jugadores ingresados por el ususario en una lista
//void retos_txt(List*);// carga todos los retos desde un txt hacia una lista
void recorrer_lista(List*);
jugador* create_jugador();//crea y inicializa los campos de un dato de tipo jugador
reto* create_reto();//crea y inicializa los campos de un dato de tipo reto.
//HashMap* cargar_retos_motivado(List*);
//HashMap* cargar_retos_previa(List*);//saca de la lista de retos cargados previamente
                                    //,todos los retos asociados al modo de juego actual
//HashMap* cargar_retos_retador(List*);
void menu_modos(List*,List*);
void glosario();
void about();
void menu_jugadores(List*,List*);
void menu_retos(List*,List*);

void Main_menu(List*,List*);
void modo_previa(List*,List*);//funcion que cordina todo el resto de funciones necesarias para correr un juego
                              //en modo previa, cargando jugadores, retos y cordinando estos.
void modo_motivados(List*,List*);
//void modo_retador();
long string_to_int(char*);//transforma una palabra en un numero para ser usado como clave en el hashmap

int main(){
    List* jugadores=create_list();
    List* retos=create_list();
  printf("|Bienvenido a nuestro querido proyecto 'Sendo'\n");
  printf("|Instrucciones:\n");
  printf("|  Este juego involucra la ingesta de alcohol etilico en cantidad altas asi que \n");
  printf("|se pide a los jugadores mantener el control durante el juego, le advertimos que en ningun\n");
  printf("|momento se le exige cumplir con lo pedido en el juego y que el unico que se pone un tope \n");
  printf("|sobre cuanto puede beber es usted dicho esto empecemos.\n\n");
  cargar_jugadores(jugadores);
  //retos_txt(retos);
  Main_menu(jugadores,retos);
  return 0;
}

void Main_menu(List* players,List* retos){
  clear;
  int eleccion;
  printf("Elige una de estas opciones escribiendo su numero\n");
  printf("|y a continuacion oprimiendo <ENTER>.\n");
  printf("|-.1 Jugar.\n");
  printf("|-.2 Editar los jugadores.\n");
  printf("|-.3 Editar retos.\n");
  printf("|-.4 Reglas y glosario de terminos.\n");
  printf("|-.5 acerda de.\n");
  printf("|-.6 Salida.\n");
  scanf("%d",&eleccion);

  if(eleccion==1){
    menu_modos(players,retos);

  }else{
    if(eleccion==2){
      menu_jugadores(players,retos);

    }else{
      if(eleccion==3){
        menu_retos(players,retos);

      }else{
        if(eleccion==4){
          glosario();

        }else{
          if(eleccion==5){
            about();

          }
        }
      }
    }
  }
}

void menu_modos(List* players,List* retos){
  clear;
  printf("| Ahora para empezar solo queda elegir el modo de juego\n");
  printf("|-.1 Previa: \n|\tEste modo consiste en retos basicos\n|\tsin necesidad de mucho valor o personalidad\n|\tse recomienda a jugadores poco experimentados al beber\n|\ten este caso el juego dura 15 turnos\n\n");
  printf("|-.2 Motivados: \n|\tSi ya sabes de que va el juego\n|\ty quieres repasar la experiencia\n|\to si simplemente crees tener un minimo de experiencia\n|\teste es tu modo\n|\taqui no hay limite de turnos esto dura\n|\thasta que ustedes decidan\n\n");
  printf("|-.3 Retador: \n|\tBueno si has llegado hasta aqui\n|\tes que a lo menos algo tienes de curiosidad\n|\tbueno este modo es solo de 2 jugadores\n|\ty es un modo de muerte subita\n|\tsi quieres competir\n|\tentra bajo tu propio riesgo\n\n");
  printf("|-.4 Volver al menu anterior.\n");
  int eleccion;
  scanf("%d",&eleccion);
  clear;
  if(eleccion==1){
    modo_previa(players,retos);
  }else{
    if(eleccion==2){
      modo_motivados(players,retos);
    }else{
      if(eleccion==3){
        //modo_retador();
      }else{
        if(eleccion==4){
          Main_menu(players,retos);
        }else{
          printf("| Opcion no valida, por favor intente de nuevo.\n\n");
          clear;
          menu_modos(players,retos);
        }
      }
    }
  }
}

void menu_jugadores(List* players,List* retos){
  int eleccion;
  clear;
  printf("| ¿Que deseas hacer?\n");
  printf("|-.1 Agregar un nuevo jugador.\n");
  printf("|-.2 Eliminar un jugador.\n");
  printf("|-.3 Descalificar un jugador(cuando un jugador pierde).\n");
  printf("|-.4 Volver al menu anterior (se guardan los cambios hechos).\n");
  scanf("%d",&eleccion);
  if(eleccion==1){
    jugador* nuevo=create_jugador();
    printf("| Ingrese el nombre:\n");
    scanf("%s",nuevo->nombre);

    push_front(players,nuevo);

    menu_jugadores(players,retos);
  }else{
    if(eleccion==2){
      int cont=players->cont;
      char nombre[60];
      jugador* jugador_buscado;
      printf("| Ingrese el nombre del jugador:\n");
      scanf("%s",nombre);

      jugador_buscado=first(players);
      while(strcmp(jugador_buscado->nombre, nombre) != 0 ){
        if(cont==0){
          printf("| El jugador que busca no se encuentra ingresado.\n");
          printf("| Volviendo al menu anterior oprima.\n");
          system("pause");
          menu_jugadores(players,retos);
        }
        jugador_buscado=next(players);
        cont--;
      }
      pop_current(players);

      menu_jugadores(players,retos);
    }else{
      if(eleccion==3){
        int cont=players->cont;
        char nombre[60];
        jugador* jugador_buscado;
        printf("| Ingrese el nombre del jugador:\n");
        scanf("%s",nombre);

        jugador_buscado=first(players);
        while(strcmp(jugador_buscado->nombre, nombre) != 0 ){
          if(cont==0){
            printf("| El jugador que busca no se encuentra ingresado.\n");
            printf("| Volviendo al menu anterior oprima.\n");
            system("pause");
            menu_jugadores(players,retos);
          }
          jugador_buscado=next(players);
          cont--;
        }
        jugador_buscado->flag_lose=1;

      }else{
          if(eleccion==4){
            Main_menu(players,retos);
          }else{
            printf("| Opcion no valida, por favor intente de nuevo.\n\n");
            system("pause");
            menu_jugadores(players,retos);
          }
        }
      }
    }
  }

void  menu_retos(List* jugadores, List* retos){
  int eleccion;
  clear;
  printf("| ¿Que desea hacer?\n");
  printf("|-.1 Agregar un reto\n");
  printf("|-.2 Eliminar un reto\n");
  printf("|-.3 Volver al menu anterior (se guardan los cambios hechos)\n");
  scanf("%d",&eleccion);
  if(eleccion==1){
    reto* nuevo_reto=create_reto();
    printf("| Ingrese un nombre para el reto:(minimo una palabra)\n");
    scanf("%s",nuevo_reto->nombre);
    printf("| Descripcion:(en una sola linea)\n");
    scanf("%s",nuevo_reto->descripcion);
    printf("| Nivel del reto:(numero del 1 al 5)\n");
    scanf("%d",&nuevo_reto->nivel);
    push_front(retos,nuevo_reto);
    menu_retos(jugadores,retos);

  }else{
    if(eleccion==2){
      int cont=retos->cont;
      char nombre[60];
      reto* reto_buscado=first(retos);
      printf("| Nombre del reto:\n");
      scanf("%s",nombre);

      while(strcmp(reto_buscado->nombre,nombre)!=0){
        if(cont==0){
          printf("| El nombre del reto que se ingreso no se encuentra en el registro\n");
          printf("| Volviendo al menu anterior.\n");
          system("pause");
          menu_retos(jugadores,retos);
        }
        reto_buscado=next(retos);
        cont--;
      }
      pop_current(retos);
      menu_retos(jugadores,retos);

      }else{
      if(eleccion==3){
        Main_menu(jugadores,retos);
      }else{
          printf("| Opcion no valida, por favor intente de nuevo.\n\n");
          menu_retos(jugadores,retos);
      }
    }
  }
}
void glosario(){
  printf("aqui van las descripciones");
}
void about(){
  printf("aqui van datos sobre el programa");
}
jugador* create_jugador(){
  jugador* nuevo=(jugador*)malloc(sizeof(jugador));
  nuevo->flag_lose=0;
  nuevo->lose_turn=0;
  return nuevo;
}
reto* create_reto(){
  reto* nuevo=(reto*)malloc(sizeof(reto));
  nuevo->nivel=0;
  return nuevo;
}
void cargar_jugadores(List* players){

  char resp[2];
  char si[2];
  strcpy(si,"s");
  strcpy(resp,"s");
  printf("| Primero lo primero\n");
  printf("| Ingrese empezando por usted y hacia su derecha a todos los participantes 1 por 1:\n");

  while(strcmp(resp,si) == 0){
    jugador* nuevo=create_jugador();
    printf("| Ingrese el nombre:\n");
    scanf("%s",nuevo->nombre);

    push_front(players,nuevo);
    printf("\n| Desea ingresar otro jugador? [s/n]  \n");
    scanf("%s",resp);
    nuevo=create_jugador();
    clear;
  }
  printf("\n\n|\t\t\t Cargada lista de jugadores\n");
  system("pause");
}
void modo_previa(List* players, List* retos){
    clear;
  jugador* current_pj;
  current_pj=first(players);
    int cont=players->cont;
    cont=cont*10;
    current_pj=players->first->dato;
    while(cont>0){
      current_pj=players->current->dato;
      printf("| \n\n\t\t\t\t%s\n",current_pj->nombre);
      printf("| \t\tesperando a que puri haga los retos ;-.\n");
      system("pause");
      current_pj=next(players);
      cont--;
      clear;
    }
    printf("|Las rondas han acabado, si deseas subir el nivel y seguir difrutando\n");
    printf("|Te recomendamos seguir con el 'modo motivados' \n | ¿seguir? [s/n] \n ");
    char resp[2];
    char rep_2[2];
    char si[2];
    strcpy(si,"s");
    scanf("%s",resp);
    if(strcmp(resp,si)==0){
      printf("| Deseas editar los jugadores (en caso de que alguno haya perdido)[s/n]:\n ");
      scanf("%s",rep_2);
      if(strcmp(rep_2,si)==0 ){
        menu_jugadores(players,retos);
      }
      modo_motivados(players,retos);
    }
      Main_menu(players,retos);
}
void modo_motivados(List* players,List* retos){
  //aca se cargan los retos.
  clear;
  jugador* current_pj;
  current_pj=first(players);
  printf("%s\n",current_pj->nombre);
    int cont=players->cont;
    cont=cont*20;
    current_pj=players->first->dato;
    while(cont>0){
      current_pj=players->current->dato;
      printf("| \n\n\t\t%s\n",current_pj->nombre);
      printf("| esperando a que puri haga los retos ;-.\n");
      system("pause");
      //if (n_reto==1 || n_reto==2 || n_reto==3){
      //retos_SS;
      //}
      current_pj=next(players);
      cont--;
      clear;
    }
    printf("|Confirmemos que siguen vivos: \n");
    system("pause");
    printf("|Ahh excelente bueno felicidades terminaron el modo intermedio\n");
    printf("|Tienen un par de opciones para elegir:\n");
    printf("|-.1 Pueden continuar el juego en la misma modalidad si es que les llamo la atencion.\n");
    printf("|-.2 Pueden terminar el juego y volver al menu principal (BUUUUUU)\n");
    printf("|-.3 Pueden tomar a los dos mas imbeciles... ");
    Sleep(1500);
    printf("digo");
    Sleep(1000);
    printf(" valientes de su grupo\n");
    Sleep(1000);
    printf("y ");
    Sleep(1000);
    printf(" hacerlos");
    Sleep(1000);
    printf(" usar el ");
    Sleep(1000);
    printf("modo retador ");
    Sleep(1000);
    printf(" (YEAHHH)\n");
    Sleep(1000);
    for(cont=0;cont<=5;cont++){
        Sleep(1000);
        printf(".");
    }
    Sleep(1500);
    printf("\n| ¿ Que decides hacer ? \n");
    int eleccion;
    scanf("%d",&eleccion);
    if(eleccion==1){
        char rep_2[2];
        char si[2];
        strcpy(si,"s");
        printf("Deseas editar los jugadores (en caso de que alguno haya perdido)[s/n]:\n ");
        scanf("%s",rep_2);
        if(strcmp(rep_2,si)==0 ){
            menu_jugadores(players,retos);
        }
        modo_motivados(players,retos);
    }else{
        if(eleccion==2){
            char rep_2[2],rep_3[2];
            char si[2];
            strcpy(si,"s");
            printf("| ¿ Estas seguro ? [s/n]:\n ");
            scanf("%s",rep_2);
            if(strcmp(rep_2,si)!=0 ){
                printf("| ¿ Estas totalmente seguro ? [s/n]: \n ");
                scanf("%s",rep_3);
                if(strcmp(rep_3,si)!=0){
                    printf("|Demonios como quieras tu te lo pierdes ;-; \n");
                    clear;
                    Main_menu(players,retos);
                }
            }
        }else{
            if(eleccion==3){
                printf("|Me agrada su actitud por favor elijan a sus concursantes: ");
                //Modo_retador();
                printf("modo retador en construccion :3");
                system("pause");
                Main_menu(players,retos);
            }

        }
    }
}

//void modo_retador(List* players,List* retos){
//}

/*void retos_txt(List* retos){

  FILE* retos_file;
  reto* nuevo_reto=create_reto();
  char* line=(char*)malloc(100*sizeof(char));
  retos_file=fopen("retos.txt","r");
  while(fgets(line,100,retos_file)){

    strcpy(nuevo_reto->nombre,line);

    fgets(line,100,retos_file);
    strcpy(nuevo_reto->descripcion,line);

    fgets(line,100,retos_file);
    nuevo_reto->nivel=atoi(line);

    push_front(retos,nuevo_reto);
  }
}*/

/*HashMap* cargar_retos_previa(List* retos){
  int cont=retos->cont;
  int key;
  reto* new_challenge=first(retos);
  HashMap* retos_previa=createHashMap(100);
  while(cont!=0){
    if((new_challenge->nivel==1) || (new_challenge->nivel==2) || (new_challenge->nivel==3)){
      key=string_to_int(new_challenge->nombre);
      insert(retos_previa,key,new_challenge);
    }
      cont--;
  }
  return retos_previa;
}*/

/*long string_to_int(char* key_c){
  long key=0;
  int i;

  for(i=0;i < strlen(key_c) ; i++){
    key=key + (long)key_c[i];
  }

  return key;
}*/
