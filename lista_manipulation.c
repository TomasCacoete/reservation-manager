#include "lista.h"

lista* cria_lista(){
    lista* l = malloc(sizeof(lista));
    if(l != NULL) l->inicio = NULL;
    return l;
}
//função parecida à que usamos nas aulas que ordena os elementos verificando se o fim de uma reserva é antes do início da que queremos inserir
//além disso também trabalha com ponteiros que apontam para o elemento anterior
no* insere_lista(lista* l, Intervalo interv){
    no* aux = malloc(sizeof(no));
    if(aux == NULL) return NULL;

    aux->valor = interv;
    aux->prox = NULL;
    aux->prev = NULL;

    if(l->inicio == NULL){
        l->inicio = aux;
    } else if(compare_date(l->inicio->valor.h_final,interv.h_inicial) == 1){
        aux->prox = l->inicio;
        l->inicio->prev = aux;
        l->inicio = aux;
    } else{
        no* ant = l->inicio;
        no* atual = l->inicio->prox;
        while(atual != NULL && compare_date(atual->valor.h_final, interv.h_inicial) == 0){
            ant = atual;
            atual = atual->prox;
        }
        if(atual != NULL) atual->prev = aux;
        aux->prev = ant;
        ant->prox = aux;
        aux->prox = atual;
    }
    return aux;
}
//bastante parecida à anterior porém esta tem em conta os ids, é usada na das pré-reservas. Caso o id seja igual a ordenação por data é interrompida e o nó é inserido
no* insere_lista2(lista* l, Intervalo interv){
    no* aux = malloc(sizeof(no));
    if(aux == NULL) return NULL;

    aux->valor = interv;
    aux->prox = NULL;
    aux->prev = NULL;

    if(l->inicio == NULL){
        l->inicio = aux;
    } else if(l->inicio->valor.id == interv.id || (l->inicio->valor.id != interv.id && compare_date(l->inicio->valor.h_final,interv.h_inicial) == 1)){
        aux->prox = l->inicio;
        l->inicio->prev = aux;
        l->inicio = aux;
    } else{
        no* ant = l->inicio;
        no* atual = l->inicio->prox;
        while(atual != NULL && compare_date(atual->valor.h_final, interv.h_inicial) == 0 && atual->valor.id != interv.id){
            ant = atual;
            atual = atual->prox;
        }
        if(atual != NULL) atual->prev = aux;
        aux->prev = ant;
        ant->prox = aux;
        aux->prox = atual;
    }
    return aux;
}

no* insere_lista_fim(lista* l, Intervalo interv){
    no* aux = malloc(sizeof(no));
    if(aux == NULL){
        return NULL;
    }

    aux->valor = interv;
    aux->prox = NULL;
    aux->prev = NULL;

    if(l->inicio == NULL){
        l->inicio = aux;
    } else{
        no* atual = l->inicio;
        while(atual->prox != NULL){
            atual = atual->prox;
        }
        aux->prev = atual;
        atual->prox = aux;
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
    if (l->inicio!=NULL){
        for(no *atual = l->inicio; atual!=NULL; atual=atual->prox){
            printf("%d ", atual->valor.id);
            printf("%d ", atual->valor.cc);
            printf("%02d/%02d/%02d ",atual->valor.h_inicial.dia,atual->valor.h_inicial.mes,atual->valor.h_inicial.ano);
            printf("(%02d:%02d-%02d:%02d)-> ",atual->valor.h_inicial.horas,
                                             atual->valor.h_inicial.minutos,
                                             atual->valor.h_final.horas, 
                                             atual->valor.h_final.minutos);
    }
        printf("\n");
    }
}
//função que percorre a lista das pre-reservas e adiciona todas as que conseguir à lista das reservas
void passa_preReservas_livres(lista* l1,lista* l2){
    no* atual = l2->inicio;
    Intervalo sub = {0};
    int id_aux = l2->inicio->valor.id;
    int flag = 0;
    while(atual != NULL){
        //guardamos o id atual
        id_aux = atual->valor.id;
        while(atual != NULL && id_aux == atual->valor.id){
            if(data_in_lista(l1, atual->valor) == 0){
                sub = atual->valor;
                flag = 1;
                //enquanto o id for igual ao guardado anteriormente descobrimos qual das pre-reservas é que já tem disponibilidade
            }
            atual = atual->prox;
        }
        //quando este loop acabar iremos ter percorrido todas as pre-reservas de um certo id e descoberto a que irá entrar na das reservas
        if(flag){
            retira_intervalo(l2, sub);
            insere_lista(l1, sub);
        }
        //passa-se para o inicio do loop principal com um novo id e assim iremos descobrir outras possíveis pre-reservas que caibam
    }
}
//função simples que verifica se já existe alguma reserva com um id introduzido, usado para na lista de reservas ter ids únicos para não dar conflito nas pre-reservas
int id_in_lista(lista* l, Intervalo i){
    if(l->inicio == NULL) return 0;
    for(no* atual = l->inicio; atual!=NULL; atual=atual->prox){
        if(atual->valor.id == i.id){
            return 1;
        }
    }
    return 0;
}