#ifndef MAIN_H
#define MAIN_H

#include "lista.h"

void cria_reserva(lista* l1, lista* l2, Data data_atual);
void cancela_reserva(lista* l1, lista* l2);
void imprime_reservas_cliente(lista* l1, lista* l2);
void printAllReservations(lista* l1, lista* l2);
void guarda_informacao_ficheiro(lista* l1, lista* l2, Data d);
void carrega_informacao_ficheiro(lista* l1, lista* l2, Data* d);
void avancar_tempo(lista* l1, lista* l2, Data* d);

#endif