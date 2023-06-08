#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int ano;
    int mes;
    int dia;
    int horas;
    int minutos;
} Data;

typedef struct{
    Data h_inicial;
    Data h_final;
    int serviço;
    int cc;
    int priority;
} Intervalo;

typedef struct no{
    Intervalo valor;
    struct no* prox;
    struct no* prev;
}no;

typedef struct{
    no* inicio;
    int q_priority;
} lista;

lista* cria_lista();
no* insere_lista(lista* l, Intervalo interv);
void destroi_lista(lista *l);
void imprime_lista(lista *l);
void retira_intervalo(lista *l,Intervalo interv);
int tamanho_lista(lista* l);
void passa_preReservas_livres(lista* l1,lista* l2);

int intervalo_igual(Intervalo I1, Intervalo I2);
int compare_date(Data d1, Data d2);
Data soma_data(Data d, int service);
int data_in_lista(lista* l, Intervalo i);
int data_in_intervalo(Intervalo quer_entrar, Intervalo ja_feito);

void inputUmDigito(int* value, char c1, char c2);
void ccValido(int* cc);
void horaValida(int* horas, int* minutos);
void diaValido(int* dia, int* mes, int* ano);

void cria_reserva(lista* l1, lista* l2, Data data_atual);
void cancela_reserva(lista* l1, lista* l2);
void imprime_reservas_cliente(lista* l1, lista* l2);
void printAllReservations(lista* l1, lista* l2);
void guarda_informacao_ficheiro(lista* l1, lista* l2, Data d);
void carrega_informacao_ficheiro(lista* l1, lista* l2, Data* d);
void avancar_tempo(lista* l1, lista* l2, Data* d);

#endif