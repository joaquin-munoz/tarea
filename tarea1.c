#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ticket{
  int id;
  char prioridad[10];
  char problema[1000];
  char hora[100];
}ticket;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión tickets");
  puts("========================================");

  puts("1) Registrar ticket");
  puts("2) Asignar prioridad a ticket");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente ticket");
  puts("5) Mostrar ticket por prioridad");
  puts("6) Salir");
}

void registrar_ticket(List *ticketpersona) {
  printf("Registrar nuevo ticket\n");
  ticket *tic = (ticket*)malloc(sizeof(ticket));
  if (tic == NULL) {
    return;
  }
  scanf("%d", &tic->id);
  getchar();
  strcpy(tic->prioridad,"Baja");
  scanf("%1000[^\n]s",tic->problema);
  getchar();
  time_t ahora = time(NULL);  // obtiene el tiempo actual (en segundos)
  struct tm* infoTiempo = localtime(&ahora);  // convierte a tiempo local

  // Formatea la hora y la guarda en el campo
  strftime(tic->hora, sizeof(tic->hora), "%d/%m/%Y %H:%M:%S", infoTiempo);
  list_pushBack(ticketpersona, tic);
}
void reasignarprioridad(List *listatickets){
  int id;
  scanf("%d",&id);
  char nuevaprioridad[10];
  scanf(" %10[^\n]s",nuevaprioridad);
  getchar();
  if(strlen(nuevaprioridad) > 5){
    printf("prioridad no valida\n");
    return;
  }
  ticket *ticketactual = list_first(listatickets);
  int encontrado = 0;
  while(ticketactual != NULL){
    if(ticketactual->id == id){
      strcpy(ticketactual->prioridad,nuevaprioridad);
      encontrado = 1;
    }
    ticketactual = list_next(listatickets);
  }
  if(!encontrado){
    printf("ERROR, no se escuentra el id\n");
  }

}
void mostrartickets(List *L){
  ticket *actual = list_first(L);
  while(actual != NULL){
    printf("hora = %s\n",actual->hora);
    printf("prioridad = %s\n",actual->prioridad);
    actual = list_next(L);
  }
}
void mostrar_lista_ticket(List *ticketpersona,List *bajo,List *media,List *alto) {
  list_clean(bajo);
  list_clean(media);
  list_clean(alto);

  printf("Pacientes en espera: \n");
  ticket *ticketactual = list_first(ticketpersona);
  while(ticketactual != NULL){
    if(strcmp(ticketactual->prioridad,"Alto") == 0){
      list_pushBack(alto, ticketactual);
    }
    if(strcmp(ticketactual->prioridad,"Medio") == 0){
      list_pushBack(media, ticketactual);
    }
    if(strcmp(ticketactual->prioridad,"Bajo") == 0){
      list_pushBack(bajo, ticketactual);
    }
    ticketactual = list_next(ticketpersona);
  }
  printf("\nTickets con prioridad Alta:\n");
  mostrartickets(alto);

  printf("\nTickets con prioridad Media:\n");
  mostrartickets(media);

  printf("\nTickets con prioridad Baja:\n");
  mostrartickets(bajo);
}

int main() {
  char opcion;
  List *ticket = list_create(); // puedes usar una lista para gestionar los pacientes
  List *bajo = list_create();
  List *media = list_create();
  List *alto = list_create();
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_ticket(ticket);
      break;
    case '2':
      reasignarprioridad(ticket);
      break;
    case '3':
      mostrar_lista_ticket(ticket,bajo,media,alto);
      break;
    case '4':
      // Lógica para atender al siguiente paciente
      break;
    case '5':
      // Lógica para mostrar pacientes por prioridad
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(ticket);

  return 0;
}
