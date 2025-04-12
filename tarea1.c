#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct ticket {
    int id;
    char prioridad[10];
    char problema[1000];
    char hora[100];
} ticket;

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
    puts("5) Buscar ticket por ID");
    puts("6) Salir");
}

void registrar_ticket(List *ticketpersona, List *bajo) {
    printf("Registrar nuevo ID\n");
    ticket *tic = (ticket*)malloc(sizeof(ticket));
    if (tic == NULL) {
        return;
    }

    // Solicitar ID y verificar si ya existe
    int id;
    scanf("%d", &id) ;
    ticket *ticketactual = list_first(ticketpersona);
    int encontrado = 0;
    while(ticketactual != NULL){
        if(ticketactual->id == id){
            encontrado = 1;
        }
        ticketactual = list_next(ticketpersona);
    }
    if(encontrado){
        printf("Ya se encuentra el ticket\n");
        return;
    }

    tic->id = id;
    getchar(); // Para consumir el salto de línea residual
    strcpy(tic->prioridad, "Bajo"); // Prioridad por defecto
    printf("Ingrese descripcion del problema: ");
    scanf("%1000[^\n]s", tic->problema);
    getchar(); // Para consumir el salto de línea residual

    // Asignar la hora actual
    time_t ahora = time(NULL);
    struct tm *infoTiempo = localtime(&ahora);
    strftime(tic->hora, sizeof(tic->hora), "%d/%m/%Y %H:%M:%S", infoTiempo);
    
    list_pushBack(bajo, tic) ;
    list_pushBack(ticketpersona, tic);
}

// Reasignar prioridad al ticket
void reasignarprioridad(List *listatickets, List *bajo, List *media, List *alto) {
    int id;
    char nuevaprioridad[10];
    printf("Ingrese ID del ticket a reasignar: ");
    scanf("%d", &id);
    printf("Ingrese nueva prioridad (Alto, Medio, Bajo): ");
    scanf(" %10[^\n]s", nuevaprioridad);

    // Validar la prioridad
    if (strcmp(nuevaprioridad, "Alto") != 0 && strcmp(nuevaprioridad, "Medio") != 0 && strcmp(nuevaprioridad, "Bajo") != 0) {
        printf("ERROR: Prioridad no valida. Debe ser 'Alto', 'Medio' o 'Bajo'.\n");
        return;
    }

    ticket *ticketactual = list_first(listatickets);
    int encontrado = 0;
    while (ticketactual != NULL) {
        if (ticketactual->id == id) {
            strcpy(ticketactual->prioridad, nuevaprioridad);
            encontrado = 1;
            break;
        }
        ticketactual = list_next(listatickets);
    }

    if (!encontrado) {
        printf("ERROR: No se encontro el ticket con ID %d.\n", id);
    }
    list_clean(bajo);
    list_clean(media);
    list_clean(alto);

    ticketactual = list_first(listatickets);
    while (ticketactual != NULL) {
        if (strcmp(ticketactual->prioridad, "Alto") == 0) {
            list_pushBack(alto, ticketactual);
        }
        if (strcmp(ticketactual->prioridad, "Medio") == 0) {
            list_pushBack(media, ticketactual);
        }
        if (strcmp(ticketactual->prioridad, "Bajo") == 0) {
            list_pushBack(bajo, ticketactual);
        }
        ticketactual = list_next(listatickets);
    }
}

// Mostrar lista de tickets por prioridad
void mostrartickets(List *L) {
    ticket *actual = list_first(L);
    while (actual != NULL) {
        printf("ID: %d\n", actual->id);
        printf("Hora: %s\n", actual->hora);
        printf("Prioridad: %s\n", actual->prioridad);
        printf("Problema: %s\n", actual->problema);
        printf("--------------------\n");
        actual = list_next(L);
    }
}

// Mostrar tickets por prioridad (Alto, Medio, Bajo)
void mostrar_lista_ticket(List *ticketpersona, List *bajo, List *media, List *alto) {
    printf("Pacientes en espera:\n");

    printf("\nTickets con prioridad Alta:\n");
    mostrartickets(alto);

    printf("\nTickets con prioridad Media:\n");
    mostrartickets(media);

    printf("\nTickets con prioridad Baja:\n");
    mostrartickets(bajo);
}

/*- Selecciona el ticket con mayor prioridad (y más antiguo dentro de su nivel) para ser atendido.
- Elimina el ticket de la lista y muestra sus datos (ID, descripción, prioridad y hora de registro).
- Si no hay tickets pendientes, muestra un aviso.*/
void eliminarTicketDeLista(List *lista, ticket *tic) {
    ticket *actual = list_first(lista);
    while (actual != NULL) {
        if (actual == tic) {
            list_popCurrent(lista);  // Eliminar el ticket de la lista
            break;
        }
        actual = list_next(lista);
    }
}

void atenderSiguienteTicket(List *ticketpersona, List *bajo, List *media, List *alto) {
    // Primero, verificar si hay tickets en la lista principal (ticketpersona)
    if (list_size(alto) == 0 && list_size(media) == 0 && list_size(bajo) == 0) {
        printf("No hay tickets pendientes.\n");
        return;
    }

    // Verificar si hay tickets en la lista de "Alto"
    if (list_size(alto) > 0) {
        ticket *ticketAtendido = list_popFront(alto); // Tomar el ticket más antiguo (primer ticket en la lista)
        printf("Atendiendo ticket con alta prioridad:\n");
        printf("ID: %d\n", ticketAtendido->id);
        printf("Hora: %s\n", ticketAtendido->hora);
        printf("Prioridad: %s\n", ticketAtendido->prioridad);
        printf("Problema: %s\n", ticketAtendido->problema);

        // Eliminar de la lista principal
        eliminarTicketDeLista(ticketpersona, ticketAtendido);

        // Liberar la memoria ocupada por el ticket atendido
        free(ticketAtendido);  
        return;
    }

    // Si no hay tickets "Alto", verificar en "Medio"
    if (list_size(media) > 0) {
        ticket *ticketAtendido = list_popFront(media);  // Tomar el ticket más antiguo
        printf("Atendiendo ticket con prioridad media:\n");
        printf("ID: %d\n", ticketAtendido->id);
        printf("Hora: %s\n", ticketAtendido->hora);
        printf("Prioridad: %s\n", ticketAtendido->prioridad);
        printf("Problema: %s\n", ticketAtendido->problema);

        // Eliminar de la lista principal
        eliminarTicketDeLista(ticketpersona, ticketAtendido);

        // Liberar la memoria ocupada por el ticket atendido
        free(ticketAtendido);  
        return;
    }

    // Si no hay tickets "Alto" ni "Medio", verificar en "Bajo"
    if (list_size(bajo) > 0) {
        ticket *ticketAtendido = list_popFront(bajo);  // Tomar el ticket más antiguo
        printf("Atendiendo ticket con baja prioridad:\n");
        printf("ID: %d\n", ticketAtendido->id);
        printf("Hora: %s\n", ticketAtendido->hora);
        printf("Prioridad: %s\n", ticketAtendido->prioridad);
        printf("Problema: %s\n", ticketAtendido->problema);

        // Eliminar de la lista principal
        eliminarTicketDeLista(ticketpersona, ticketAtendido);

        // Liberar la memoria ocupada por el ticket atendido
        free(ticketAtendido);  
        return;
    }

    // Si no hay tickets en ninguna lista (aunque ya se verifica arriba)
    printf("No hay tickets pendientes.\n");
}



// Buscar ticket por ID
void buscarTicketPorID(List *ticketpersona) {
    int id;
    printf("Ingrese ID del ticket a buscar: ");
    scanf("%d", &id);

    ticket *ticketactual = list_first(ticketpersona);
    while (ticketactual != NULL) {
        if (ticketactual->id == id) {
            printf("Ticket encontrado:\n");
            printf("ID: %d\n", ticketactual->id);
            printf("Hora: %s\n", ticketactual->hora);
            printf("Prioridad: %s\n", ticketactual->prioridad);
            printf("Problema: %s\n", ticketactual->problema);
            return;
        }
        ticketactual = list_next(ticketpersona);
    }

    printf("ERROR: No se encontro el ticket con ID %d.\n", id);
}

int main() {
    char opcion;
    List *ticket = list_create();
    List *bajo = list_create();
    List *media = list_create();
    List *alto = list_create();

    do {
        mostrarMenuPrincipal();
        printf("Ingrese su opcion: ");
        scanf(" %c", &opcion);

        switch (opcion) {
        case '1':
            registrar_ticket(ticket, bajo);
            break;
        case '2':
            reasignarprioridad(ticket, bajo, media, alto);
            break;
        case '3':
            mostrar_lista_ticket(ticket, bajo, media, alto);
            break;
        case '4':
            atenderSiguienteTicket(ticket, bajo, media, alto);
            break;
        case '5':
            buscarTicketPorID(ticket);
            break;
        case '6':
            puts("Saliendo del sistema de gestion...");
            break;
        default:
            puts("Opción no válida. Intente nuevamente.");
        }

        presioneTeclaParaContinuar();
    } while (opcion != '6');

    list_clean(ticket);
  return 0;
}  