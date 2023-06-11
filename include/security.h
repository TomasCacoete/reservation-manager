#ifndef SECURITY_H
#define SECURITY_H

void inputUmDigito(int* value, char c1, char c2);
void ccValido(int* cc);
void validHour(Data* new_hour, int service, Data data_atual);
void diaValido(Data* d, Data data_atual);

#endif