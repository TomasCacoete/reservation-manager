#include <stdio.h>
#include <string.h>
#include "../include/date.h"
//função que verifica se o input é um número num certo intervalo
void inputUmDigito(int* value, char c1, char c2){
    char input[100];
    do{
        fgets(input, sizeof(input), stdin);
        if(input[0] < c1 || input[0] > c2 || strlen(input) > 2){
            printf("Input inválido\n");
        } else break;
    } while(1);
    *value = input[0] - '0';
}
//função que verifica se um input do número do cc é válido vendo se algum dos caracteres não é um número ou se o número tem mais de 8 dígitos
void ccValido(int* cc){
    char input[100];
    int flag;
    do{
        flag = 0;
        fgets(input, sizeof(input), stdin);
        for(int i=0; input[i]!='\n'; i++){
            if(input[i]<'0' || input[i]>'9' || i>8){
                printf("Input inválido\n");
                flag = 1;
                break;
            }
        }
    } while(flag);
    sscanf(input,"%d",cc);
}
//função que valida o input de horas
void validHour(Data* new_hour, int service, Data data_atual){
    char input[100];
    do{
        fgets(input, sizeof(input), stdin);
        int flag = 0;
        int n_doispontos = 0;
        for(int i=0; input[i]!='\n'; i++){
            //evita que o usuário escreva um caracter que não seja um número ou ":"
            if((input[i]<'0' || input[i]>'9') && input[i] != ':'){
                printf("Input inválido - Garanta que está a utilizar o formato (HH:MM)\n");
                flag = 1;
                break;
            //evita que o usuário escreva mais do que 1 ":"
            } else if(input[i] == ':'){
                n_doispontos++;
            }
        }
        if(flag != 1 && n_doispontos != 1){
            printf("Input inválido - Garanta que está a utilizar o formato (HH:MM)\n");
            flag = 1;
        }
        if(flag) continue;

        //evita que o usuário escreva algo do género ":1430" ou "1430:"
        if(input[0] == ':' || input[strlen(input)-2] == ':'){
            printf("Input inválido - Garanta que está a utilizar o formato (HH:MM)\n");
            continue;
        }

        sscanf(input,"%d:%d",&(new_hour->horas),&(new_hour->minutos));
        //evita que o usuário tente marcar para uma hora que não coincida com o funcionamento da oficina
        if((new_hour->horas < 8 || new_hour->horas >= 18) || (new_hour->minutos != 30 && new_hour->minutos != 0) || (service == 2 && new_hour->horas == 17 && new_hour->minutos == 30)){
            printf("Input inválido - O horário de funcionamento é das 08:00 às 18:00\n");
            continue;
        } else if(compare_date(data_atual,*new_hour) == 1){
            printf("Input inválido - A hora atual é maior que a que tentou inserir\n");
            continue;
        } else{
            break;
        }
    } while(1);
}
//função que valida o input do dia
void diaValido(Data* d, Data data_atual){
    char input[100];
    do{
        fgets(input, sizeof(input), stdin);
        //evita que o usuário coloque '/' no inicio ou no fim do input
        if(input[0] == '/' || input[strlen(input)-2] == '/'){
            printf("Input inválido - Garanta que está a utilizar o formato (DD/MM/AAAA)\n");
            continue;
        }

        int flag = 0;
        int n_barra = 0;
        //mesma lógica que a função anterior porém com mais uma condição
        for(int i=0; input[i]!='\n'; i++){
            if((input[i]<'0' || input[i]>'9') && input[i] != '/'){
                printf("Input inválido - Garanta que está a utilizar o formato (DD/MM/AAAA)\n");
                flag = 1;
                break;
            } else if(input[i] == '/'){
                n_barra++;
            }
            //evita que o usuário coloque duas barras seguidas
            if(input[i] == '/' && input[i+1] == '/'){
                printf("Input inválido - Garanta que está a utilizar o formato (DD/MM/AAAA)\n");
                flag = 1;
                break;
            }
        }
        if(flag != 1 && n_barra != 2){
            printf("Input inválido - Garanta que está a utilizar o formato (DD/MM/AAAA)\n");
            flag = 1;
        }
        if(flag) continue;
        
        sscanf(input,"%d/%d/%d",&(d->dia),&(d->mes),&(d->ano));
        //evita que o usuário coloque um dia que não existe
        if(d->dia < 1 || d->dia > 31 || d->mes < 1 || d->mes > 12 || d->ano < 1){
            printf("Input inválido - Esse dia não existe\n");
            continue;
        } else if((d->mes == 2 && d->dia > 28) || (d->mes == 4 && d->dia > 30) || (d->mes == 6 && d->dia > 30) || (d->mes == 9 && d->dia > 30) || (d->mes == 11 && d->dia > 30)){
            printf("Input inválido - Esse dia não existe\n");
            continue;
        }
        Data aux = {d->ano,d->mes,d->dia,99,99};
        if(compare_date(data_atual,aux) == 1){
            printf("Input Inválido - Não podes fazer uma reserva no passado\n");
        } else{
            break;
        }
    } while(1);
}