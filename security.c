#include "lista.h"
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
void horaValida(int* horas, int* minutos){
    char input[100];
    do{
        fgets(input, sizeof(input), stdin);
        //evita que o usuário escreva algo do género ":1430" ou "1430:"
        if(input[0] == ':' || input[strlen(input)-2] == ':'){
            printf("Input inválido - Garanta que está a utilizar o formato (HH:MM)\n");
            continue;
        }

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
        if(n_doispontos != 1){
            printf("Input inválido - Garanta que está a utilizar o formato (HH:MM)\n");
            flag = 1;
        }
        if(flag) continue;

        sscanf(input,"%d:%d",horas,minutos);
        //evita que o usuário tente marcar para uma hora que não coincida com o funcionamento da oficina
        if((*horas < 8 || *horas >= 18) || (*minutos != 30 && *minutos != 0)){
            printf("Input inválido - O horário de funcionamento é das 08:00 às 18:00\n");
            continue;
        } else{
            break;
        }
    } while(1);
}
//função que valida o input do dia
void diaValido(int* dia, int* mes, int* ano){
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
        if(n_barra != 2){
            printf("Input inválido - Garanta que está a utilizar o formato (DD/MM/AAAA)\n");
            flag = 1;
        }
        if(flag) continue;
        
        sscanf(input,"%d/%d/%d",dia,mes,ano);
        //evita que o usuário coloque um dia que não existe
        if(*dia < 1 || *dia > 31 || *mes < 1 || *mes > 12 || *ano < 1){
            printf("Input inválido\n");
            continue;
        } else if((*mes == 2 && *dia > 28) || (*mes == 4 && *dia > 30) || (*mes == 6 && *dia > 30) || (*mes == 9 && *dia > 30) || (*mes == 11 && *dia > 30)){
            printf("Input inválido\n");
            continue;
        } else{
            break;
        }
    } while(1);
}