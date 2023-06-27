#include "../include/lista.h"

lista* initialize_list(){
    lista* l = malloc(sizeof(lista));
    if(l != NULL){
        l->inicio = NULL;
        l->q_priority = 0;
    }
    return l;
}
//função parecida à que usamos nas aulas que ordena os elementos verificando se o fim de uma reserva é antes do início da que queremos inserir
//além disso também trabalha com ponteiros que apontam para o elemento anterior

no* insere_lista(lista* l, Intervalo interv) {
    no* aux = malloc(sizeof(no));
    if(aux == NULL)
        return NULL;

    l->q_priority += 1;
    interv.priority = l->q_priority;

    aux->valor = interv;
    aux->prox = NULL;
    aux->prev = NULL;

    if(l->inicio == NULL)
        l->inicio = aux;
    else{
        no* atual = l->inicio;
        while(atual != NULL){
            if(compare_date(atual->valor.h_inicial, interv.h_inicial) == 1
            ||(compare_date(atual->valor.h_inicial, interv.h_inicial) == 0 && compare_date(atual->valor.h_final, interv.h_final) == 1)){
                break;
            }
            atual = atual->prox;
        }
        if(atual == l->inicio){
            aux->prox = l->inicio;
            l->inicio->prev = aux;
            l->inicio = aux;
        } else if(atual == NULL){
            no* last = l->inicio;
            while(last->prox != NULL){
                last = last->prox;
            }
            last->prox = aux;
            aux->prev = last;
        } else{
            aux->prox = atual;
            aux->prev = atual->prev;
            atual->prev->prox = aux;
            atual->prev = aux;
        }
    }
    return aux;
}

//função parecida à utilizada nas aulas, única diferença é a atualização dos ponteiros para trás
void retira_intervalo(lista *l, Intervalo interv){
    no* atual = l->inicio;
    no* ant = NULL;
    while(atual != NULL){
        if(checkTimeIntervalEquality(interv, atual->valor) && interv.cc == atual->valor.cc){
            if(ant == NULL) {
                l->inicio = atual->prox;
                if (l->inicio != NULL) l->inicio->prev = NULL;
            } else {
                ant->prox = atual->prox;
                if(atual->prox != NULL) atual->prox->prev = ant;
            }
            free(atual);
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
}

void free_list_memory(lista *l){
    while(l->inicio != NULL){
        no *aux = l->inicio;
        l->inicio = l->inicio->prox;
        free(aux);
    }
    free(l);
}
//função simples que devolve o tamanho de uma lista
int tamanho_lista(lista* l){
    int tam = 0;
    for(no* atual = l->inicio; atual != NULL; atual = atual->prox) tam++;
    return tam;
}
//função simples que imprime a lista
void imprime_lista(lista *l){
    //if (l->inicio!=NULL){
        for(no *atual = l->inicio; atual!=NULL; atual=atual->prox){
            printf("%d ", atual->valor.priority);
            printf("%d ", atual->valor.cc);
            printf("%02d/%02d/%02d ",atual->valor.h_inicial.dia,atual->valor.h_inicial.mes,atual->valor.h_inicial.ano);
            printf("(%02d:%02d-%02d:%02d)-> ",atual->valor.h_inicial.horas,
                                             atual->valor.h_inicial.minutos,
                                             atual->valor.h_final.horas, 
                                             atual->valor.h_final.minutos);
    }
        printf("\n");
    //}
}

int data_in_lista(lista* l, Intervalo i){
    for(no *atual = l->inicio; atual!=NULL; atual=atual->prox){
        if((data_in_intervalo(i,atual->valor) || checkTimeIntervalEquality(i,atual->valor)) && i.cc == atual->valor.cc) return -1;
        if(data_in_intervalo(i,atual->valor) || checkTimeIntervalEquality(i,atual->valor)) return 1;
    }
    return 0;
}

void passa_preReservas_livres(lista* l1,lista* l2){
    no* atual = l2->inicio;
    while (atual != NULL && data_in_lista(l1, atual->valor) != 0) atual = atual->prox;
    if(atual == NULL) return;
    Intervalo sub = atual->valor;
    atual = atual->prox;
    while(atual != NULL){
        if(data_in_lista(l1, atual->valor) == 0){
            if(data_in_intervalo(atual->valor,sub) == 1){
                if(atual->valor.priority < sub.priority){
                    sub = atual->valor;
                }
            } else{
                Intervalo aux = atual->valor;
                retira_intervalo(l2,sub);
                insere_lista(l1,sub);
                sub = aux;
            }
        }
        atual = atual->prox;
    }
    retira_intervalo(l2,sub);
    insere_lista(l1,sub);
}

void printAvailableHours(lista* l, Data chosen_day, int chosen_service){
    if(l->inicio == NULL) return;
    int NUMBER_OF_AVAILABLE_HOURS;
    if(chosen_service == 1) NUMBER_OF_AVAILABLE_HOURS = 20;
    else NUMBER_OF_AVAILABLE_HOURS = 19;
    int hours[][2] = {{8,0},{8,30},{9,0},{9,30},{10,0},{10,30},{11,0},{11,30},{12,0},{12,30},{13,0},{13,30},{14,0},{14,30},{15,0},{15,30},{16,0},{16,30},{17,0},{17,30}};
    no* start = l->inicio;

    while(chosen_day.ano != start->valor.h_inicial.ano && chosen_day.mes != start->valor.h_inicial.mes && chosen_day.dia != start->valor.h_inicial.dia)
        start = start->prox;
    
    int** available_hours = NULL;
    int size = 0;
    int i=0;
    while(i<NUMBER_OF_AVAILABLE_HOURS){
        no* atual = start;
        int is_occupied = 0;
        while(atual != NULL && chosen_day.ano == atual->valor.h_inicial.ano && chosen_day.mes == atual->valor.h_inicial.mes && chosen_day.dia == atual->valor.h_inicial.dia){
            if(hours[i][0] == atual->valor.h_inicial.horas && hours[i][1] == atual->valor.h_inicial.minutos && atual->valor.serviço == 2){
                is_occupied = 2;
                i++;
                break;
            } else if(hours[i][0] == atual->valor.h_inicial.horas && hours[i][1] == atual->valor.h_inicial.minutos){
                is_occupied = 1;
                break;
            }
            atual = atual->prox;
        }
        if(is_occupied == 0){
            size++;
            available_hours = (int**)realloc(available_hours, sizeof(int*)*size);
            available_hours[size-1] = (int*)malloc(sizeof(int) * 2);
            available_hours[size-1][0] = hours[i][0];
            available_hours[size-1][1] = hours[i][1];
        }
        i++;
    }

    for(int i=0; i<size; i++){
        printf("%d:%d ",available_hours[i][0],available_hours[i][1]);
        free(available_hours[i]);
    }
    printf("\n");
    free(available_hours);
}