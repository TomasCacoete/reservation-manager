#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "date.h"

typedef struct no{
    Intervalo valor;
    struct no* prox;
    struct no* prev;
}no;

typedef struct{
    no* inicio;
    int q_priority;
} lista;

lista* initialize_list();
no* insere_lista(lista* l, Intervalo interv);
void free_list_memory(lista *l);
void imprime_lista(lista *l);
void retira_intervalo(lista *l,Intervalo interv);
int tamanho_lista(lista* l);
int data_in_lista(lista* l, Intervalo i);
void passa_preReservas_livres(lista* l1,lista* l2);
void printAvailableHours(lista* l, Data chosen_day, int chosen_service);

#endif