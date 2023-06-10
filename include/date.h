#ifndef DATE_H
#define DATE_H

#include <time.h>

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

void getCurrentTime(Data* d);
int checkTimeIntervalEquality(Intervalo I1, Intervalo I2);
int compare_date(Data d1, Data d2);
Data soma_data(Data d, int service);
int data_in_intervalo(Intervalo quer_entrar, Intervalo ja_feito);

#endif