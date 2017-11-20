#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "Lista.h"
#include <conio.h>
#include <time.h>
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
  char nombre[60];
  char descripcion[400];
  int nivel;
}reto;

//Prototipacion de funciones
jugador* create_jugador();//crea y inicializa los campos de un dato de tipo jugador.
reto* create_reto();//crea y inicializa los campos de un dato de tipo reto.

void comparar_lista(List*,reto*);//ve si el reto ingresado a la lista ya existe bajo el mismo nombre.
void cargar_retadores(List*);//carga los jugadores para un juego en modo retador
void cargar_jugadores(List*);// carga los jugadores ingresados por el ususario en una lista.
void retos_txt(List*);// carga todos los retos desde un txt hacia una lista.

void glosario(List*,List*);//tiene los significados de algunos terminos poco conocidos dentro del juego.
void about(List*,List*);//tiene los creditos de la aplicacion.

void menu_modos(List*,List*);//para organizar las opciones de los modos del juego.
void menu_jugadores(List*,List*);//organiza las opciones de los jugadores tales como agregar y eliminar.
void menu_retos(List*,List*);//organiza las opciones de los retos tales como eliminar y agregar.
void Main_menu(List*,List*);//organiza el programa completo y cuenta como punto de retorno de todo.

void modo_previa(List*,List*);//cordina todas las funciones necesarias para correr una juego en modo previa.
void modo_motivados(List*,List*);//cordina todas las funciones necesarias para correr una juego en modo motivados.
void modo_retador(List*,List*);//cordina todas las funciones necesarias para correr un juego en modo retador.

//Estos retos son casos especiales en el modo motivados que cambian alguna caracteristicas del juego.
void retos_SS_1(List*,List*);//reto especial del modo motivados el que hace es un secreto
/*void retos_SS_2(List*,List*);//reto especial del modo motivados el que hace es un secreto
void retos_SS_3(List*,List*)://reto especial del modo motivados el que hace es un misterio
*/
int random_n(int);//para tirar numeros al azar.

int main(){
    List* jugadores=create_list();
    List* retos=create_list();
  printf("|Bienvenido a nuestro querido proyecto 'Sendo'\n");
  printf("|Instrucciones:\n");
  printf("|  Este juego involucra la ingesta de alcohol etilico en cantidad altas asi que \n");
  printf("|se pide a los jugadores mantener el control durante el juego, le advertimos que en ningun\n");
  printf("|momento se le exige cumplir con lo pedido en el juego y que el unico que se pone un tope \n");
  printf("|sobre cuanto puede beber es usted dicho esto empecemos.\n\n");

  printf("\n| Para jugar correctamente es necesario que tengan dados, o algun metodo de azar\n");
  printf("| ya que la cantidad de tragos se decidira segun ustedes (pueden usar cuantos dados quieran).\n| \n");

  cargar_jugadores(jugadores);
  retos_txt(retos);
  Main_menu(jugadores,retos);
  return 0;
}

jugador* create_jugador(){
  jugador* nuevo=(jugador*)malloc(sizeof(jugador));
  nuevo->flag_lose=0;
  nuevo->lose_turn=0;
  return nuevo;
}//work

reto* create_reto(){
  reto* nuevo=(reto*)malloc(sizeof(reto));
  nuevo->nivel=0;
  return nuevo;
}//work

void cargar_retadores(List* retadores){

  printf("| Empecemos de una vez\n");
  printf("| Ingresa a tus dos retadores:\n");

    jugador* nuevo=create_jugador();
    printf("| Ingresa el nombre del primero:\n");
    scanf("%s",nuevo->nombre);
    push_front(retadores,nuevo);

    nuevo=create_jugador();
    printf("| Ingresa el nombre del segundo:\n");
    scanf("%s",nuevo->nombre);
    push_front(retadores,nuevo);
    clear;
  printf("\n\n|\t\t\t Todo esta listo\n");
  system("pause");

}//work

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
}//work

void retos_txt(List* retos){

  FILE* retos_file;
  reto* nuevo_reto;
  char* linea=(char*)malloc(300*sizeof(char));
  retos_file=fopen("retos.txt","r");

  while(fgets(linea,300,retos_file)){
      nuevo_reto=create_reto();

        char* aux=(char*)malloc(30*sizeof(char));
        char* token=(char*)malloc(100*sizeof(char));

      token=strtok(linea,",");
      if(token!=NULL){
          strcpy(nuevo_reto->nombre,token);
      }

      token=strtok(NULL,",");
      if(token!=NULL){
        strcpy(nuevo_reto->descripcion,token);
      }

      token=strtok(NULL,",");
      if(token!=NULL){
          strcpy(aux,token);
          nuevo_reto->nivel=atoi(aux);
      }

    comparar_lista(retos,nuevo_reto);
  }
  fclose(retos_file);
}//work

void glosario(List* players,List* retos){
  printf("| Aqui estan los terminos mas usados durante el juego \n|que posiblemente no conoscan.");
  printf("|\n| Nunca nunca:\n| Es un juego el cual consiste e decir una frase en negativo agregando\n| antes la frase nunca nunca (ej: yo nunca nunca eh mentido) \n| aquellos que no cumplan con esa frase (osea que si hayan mentido en este caso)\n| deberan beber lo indicado.\n");
  printf("|\n");
  printf("| La culturachupistica: Es otro juego el cual consiste en que el anfitrio\n| pedira algo (nombres o palabras generalmente, ej: la cultura chupistica pide nombres de marcas de autos)\n| y los participantes en orden le diran lo que pide \n| el que se equivoque o repita algo ya dicho paga la penitencia.\n|");
  printf("\n");
  printf("| ");
  system("pause");
  Main_menu(players,retos);
}//work

void about(List* players, List* retos){
  printf("Este programa fue desarrollado por 'Team Sendo', derechos reservados");
  printf("Team sendo esta conformado por las siguientes personas:\n| Nicolas Lopez. \n| Patricio Mardonez. \n| Gonzalo Rojas.\n");
  printf("\n Version: 1.04 ");
  printf("Cantidad de retos base actuales: %d.",retos->cont);
  system("pause");
  Main_menu(players,retos);
}//work

void menu_modos(List* players,List* retos){
  clear;
  printf("| Ahora para empezar solo queda elegir el modo de juego\n");
  printf("|-.1 Previa: \n|\tEste modo consiste en retos basicos\n|\tsin necesidad de mucho valor o personalidad\n|\tse recomienda a jugadores poco experimentados al beber\n|\ten este caso el juego dura 15 turnos\n\n");
  printf("|-.2 Motivados: \n|\tSi ya sabes de que va el juego\n|\ty quieres repasar la experiencia\n|\to si simplemente crees tener un minimo de experiencia\n|\teste es tu modo\n|\taqui no hay limite de turnos esto dura\n|\thasta que ustedes decidan\n\n");
  printf("|-.3 Retador: \n|\tBueno si has llegado hasta aqui\n|\tes que a lo menos algo tienes de curiosidad\n|\tbueno este modo es solo de 2 jugadores\n|\ty es un modo de muerte subita\n|\tsi quieres competir\n|\tentra bajo tu propio riesgo\n\n");
  printf("|-.4 Volver al menu anterior.\n");
  char eleccion[10];
  scanf("%s",eleccion);
  clear;
  if(strcmp(eleccion,"1")==0){
    modo_previa(players,retos);
  }else{
    if(strcmp(eleccion,"2")==0){
      modo_motivados(players,retos);
    }else{
      if(strcmp(eleccion,"3")==0){
        modo_retador(players,retos);
      }else{
        if(strcmp(eleccion,"4")==0){
          Main_menu(players,retos);
        }else{
          printf("| Opcion no valida, por favor intente de nuevo.\n\n");
          clear;
          menu_modos(players,retos);
        }
      }
    }
  }
}//work

void menu_jugadores(List* players,List* retos){
  char eleccion[10];
  clear;
  printf("| ¿Que deseas hacer?\n");
  printf("|-.1 Agregar un nuevo jugador.\n");
  printf("|-.2 Eliminar un jugador.\n");
  printf("|-.3 Volver al menu anterior (se guardan los cambios hechos).\n");
  scanf("%s",eleccion);
  if(strcmp(eleccion,"1")==0){
    jugador* nuevo=create_jugador();
    printf("| Ingrese el nombre:\n");
    scanf("%s",nuevo->nombre);

    push_front(players,nuevo);

    menu_jugadores(players,retos);
  }else{
    if(strcmp(eleccion,"2")==0){
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
        if(strcmp(eleccion,"3")==0){
            Main_menu(players,retos);
        }else{
            printf("| Opcion no valida, por favor intente de nuevo.\n\n");
            system("pause");
            menu_jugadores(players,retos);
        }
      }
    }
  }//work

void menu_retos(List* jugadores, List* retos){
  char eleccion[10];
  clear;
  printf("| ¿Que desea hacer?\n");
  printf("|-.1 Agregar un reto\n");
  printf("|-.2 Eliminar un reto\n");
  printf("|-.3 Volver al menu anterior (se guardan los cambios hechos)\n");
  scanf("%s",eleccion);
  if(strcmp(eleccion,"1")==0){
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
    if(strcmp(eleccion,"2")==0){
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
        if(strcmp(eleccion,"3")==0){
          Main_menu(jugadores,retos);
        }else{
          printf("| Opcion no valida, por favor intente de nuevo.\n\n");
          menu_retos(jugadores,retos);
      }
    }
  }
}//work

void Main_menu(List* players,List* retos){
  clear;
  char eleccion[10];
  printf("Elige una de estas opciones escribiendo su numero\n");
  printf("|y a continuacion oprimiendo <ENTER>.\n");
  printf("|-.1 Jugar.\n");
  printf("|-.2 Editar los jugadores.\n");
  printf("|-.3 Editar retos.\n");
  printf("|-.4 Reglas y glosario de terminos.\n");
  printf("|-.5 acerda de.\n");
  printf("|-.6 Salida.\n");
  scanf("%s",eleccion);

  if(strcmp(eleccion,"1")==0){
    menu_modos(players,retos);

  }else{
    if(strcmp(eleccion,"2")==0){
      menu_jugadores(players,retos);

    }else{
      if(strcmp(eleccion,"3")==0){
        menu_retos(players,retos);

      }else{
        if(strcmp(eleccion,"4")==0){
          glosario(players,retos);

        }else{
          if(strcmp(eleccion,"5")==0){
            about(players,retos);

          }else{
              if(strcmp(eleccion,"6")!=0){
                printf("| Opcion no valida pruebe de nuevo.");
                Main_menu(players,retos);
              }
          }
        }
      }
    }
  }
}//work

void modo_previa(List* players, List* retos){
    clear;
    jugador* current_pj;
    current_pj=first(players);
    reto* current_reto;

        reto* current_r= first(retos);
        int cont_=0,cont3=retos->cont;
        while(cont3>0){
            if((current_r->nivel >= 1) &&(current_r->nivel <= 3)){
            cont_++;
            }
        current_r=next(retos);
        cont3--;
        }
        void** retos_previa=(void**)malloc(cont_*sizeof(void*));

        cont_=0;
        current_r=first(retos);
        cont3=retos->cont;
        while(cont3>0){
            if((current_r->nivel >= 1) &&(current_r->nivel <= 3)){
            retos_previa[cont_]=current_r;
            cont_++;
            }
            current_r=next(retos);
            cont3--;
        }

    int cont=players->cont;
    int n_reto;
    cont=cont*10;
    current_pj=first(players);
    while(cont>0){
      n_reto=random_n(cont_);

      current_reto=retos_previa[n_reto];
      if(current_reto){
        printf("|\n|\n|\n");
        printf("| \t\t\t%s\n",current_pj->nombre);
        printf("| %s\n| %s\n",current_reto->nombre,current_reto->descripcion);
        Sleep(2000);
        system("pause");

        cont--;
        current_pj=next(players);
      }
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
}//work

void modo_motivados(List* players,List* retos){
  //aca se cargan los retos.
  clear;
  jugador* current_pj;
  current_pj=first(players);
  reto* current_reto;

      reto* current_r= first(retos);
      int cont_=0,cont3=retos->cont;
      while(cont3>0){
          if((current_r->nivel >= 3) &&(current_r->nivel <= 6)){
          cont_++;
          }
      current_r=next(retos);
      cont3--;
      }
      void** retos_motivados=(void**)malloc((cont_+3)*sizeof(void*));

      cont_=0;
      current_r=first(retos);
      cont3=retos->cont;
      while(cont3>0){
          if((current_r->nivel >= 1) &&(current_r->nivel <= 3)){
          retos_motivados[cont_]=current_r;
          cont_++;
          }
          current_r=next(retos);
          cont3--;
      }

  int cont=players->cont;
  int n_reto;
  cont=cont*30;
  current_pj=first(players);

  while(cont>0){
    n_reto=random_n(cont_);

    current_reto=retos_motivados[n_reto];
      if(current_reto){
        printf("|\n|\n|\n");
        printf("| \t\t\t%s\n",current_pj->nombre);
        printf("| %s\n| %s\n",current_reto->nombre,current_reto->descripcion);

        Sleep(3000);
        system("pause");

        cont--;
        current_pj=next(players);
      }

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
                modo_retador(players,retos);
                printf("modo retador en construccion :3");
                system("pause");
                Main_menu(players,retos);
            }
        }
    }
}//work

void modo_retador(List* players,List* retos){
  int cont=0;
  List* retadores=create_list();
  printf("| Oh");
  while(cont<=3){
    Sleep(1000);
    printf(".");
    cont++;
  }


  printf("\n| Wow siendo sincero no espere que alguien llegara hasta aqui.\n");
  system("pause");
  printf("| Dejame felicitarte a ti y a tu grupo por llegar tan lejos\n");
  system("pause");
  printf("| * Iran tomando tragos en orden creciente\n");
  printf("| * Cada 5 rondas se le dara la oportunidad de rendirse\n");
  printf("| * tienes 10 seg para cumplir el reto si no lo haces, pierdes\n");
  printf("| Dicho esto llego la hora, elige a los dos competidores.\n");
  cargar_retadores(retadores);
  cont=1;
  int flag_die=0;
  int eleccion;
  jugador* current_challenger=first(retadores);
  jugador* ganador;
  while(flag_die==0){
    printf("|%s\n\n",current_challenger->nombre);
    if(cont%5==0){
        printf("| ¿Alguno desea rendirse? \n");
        printf("| Oprime '1' si es el primer jugador.\n");
        printf("| Oprime '2' si es el segundo jugador.\n");
        printf("| Oprime '3' si no es ninguno.\n");
        scanf("%d",&eleccion);
        if(eleccion==1){
          ganador=first(retadores);
          printf("Felicidades %s has sobrevivido.\n",ganador->nombre);
          printf("Volviendo al menu principal.\n");
          system("pause");
          Main_menu(players,retos);
        }else{
            if(eleccion==2){
              ganador=last(retadores);
              printf("Felicidades %s has sobrevivido.\n",ganador->nombre);
              printf("Volviendo al menu principal.\n");
              system("pause");
              Main_menu(players,retos);
            }
        }
    }
    cont++;
    printf("| Bebe %d tragos. \n",cont );
    Sleep(5000);
    clear;
    current_challenger=next(retadores);
  }
}//work

void retos_SS_1(List* players,List* retos){
  int cont=200,cont2=0;
  while(cont>0){
    if(cont2==20){
      printf("\n");
      cont2=0;
    }
    cont2++;
    printf("¡ALERTA!");
    cont++;
  }

  printf("| Felicidades tuvieron la mala suerte de toparse con un reto especial\n");
  printf("| En este caso el reto consiste en tomar a los dos mas ebrios del grupo\n");
  printf("| y pasaran a modo retador por hasta que uno caiga :3\n");
  modo_retador(players,retos);

}

int random_n(int max){
  int numero;
  int hora=time(NULL);

  srand(hora);

     numero = rand()%max;
    return numero;
}
/*void retos_SS_2(List* players,List* retos){

}
void retos_SS_3(List* players,List* retos){

}
*/

void comparar_lista(List* lista,reto* nuevo){

    reto* p_from_list;
    if(lista->cont>0){
        first(lista);
        int cont=lista->cont;
        int aux=0;
        while(cont>=0){
            p_from_list=lista->current->dato;
            if(strstr(nuevo->nombre,p_from_list->nombre)){
                aux=1;
            }
            next(lista);
            cont--;
        }
        if(aux==0){
            push_back(lista,nuevo);
        }
    }else{
        push_back(lista,nuevo);
    }
}
