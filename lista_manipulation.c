#include "lista.h"

lista* cria_lista(){
    lista* l = malloc(sizeof(lista));
    if(l != NULL){
        l->inicio = NULL;
        l->q_priority = 0;
    }
    return l;
}
//função parecida à que usamos nas aulas que ordena os elementos verificando se o fim de uma reserva é antes do início da que queremos inserir
//além disso também trabalha com ponteiros que apontam para o elemento anterior
/*no* insere_lista(lista* l, Intervalo interv){
    no* aux = malloc(sizeof(no));
    if(aux == NULL) return NULL;

    l->q_priority += 1;
    interv.priority = l->q_priority;

    aux->valor = interv;
    aux->prox = NULL;
    aux->prev = NULL;

    if(l->inicio == NULL){
        l->inicio = aux;
    } else if(compare_date(l->inicio->valor.h_final,interv.h_final) == 1){
        aux->prox = l->inicio;
        l->inicio->prev = aux;
        l->inicio = aux;
    } else{
        no* ant = l->inicio;
        no* atual = l->inicio->prox;
        while(atual != NULL && compare_date(atual->valor.h_final, interv.h_final) == 0){
            ant = atual;
            atual = atual->prox;
        }
        if(atual != NULL) atual->prev = aux;
        aux->prev = ant;
        ant->prox = aux;
        aux->prox = atual;
    }
    return aux;
}*/

no* insere_lista(lista* l, Intervalo interv) {
    no* aux = malloc(sizeof(no));
    if (aux == NULL)
        return NULL;

    l->q_priority += 1;
    interv.priority = l->q_priority;

    aux->valor = interv;
    aux->prox = NULL;
    aux->prev = NULL;

    if (l->inicio == NULL) {
        l->inicio = aux;
    } else {
        no* atual = l->inicio;
        while (atual != NULL) {
            if (compare_date(atual->valor.h_inicial, interv.h_inicial) == 1 ||
                (compare_date(atual->valor.h_inicial, interv.h_inicial) == 0 &&
                 compare_date(atual->valor.h_final, interv.h_final) == 1)) {
                break;
            }
            atual = atual->prox;
        }
        if (atual == l->inicio) {
            aux->prox = l->inicio;
            l->inicio->prev = aux;
            l->inicio = aux;
        } else if (atual == NULL) {
            no* last = l->inicio;
            while (last->prox != NULL) {
                last = last->prox;
            }
            last->prox = aux;
            aux->prev = last;
        } else {
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
        if(intervalo_igual(interv, atual->valor) && interv.cc == atual->valor.cc){
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

void destroi_lista(lista *l){
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