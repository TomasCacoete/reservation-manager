#include "../include/main.h"
#include "../include/security.h"

void printAllReservations(lista* l1, lista* l2){
    printf("---------------------------------------------------\n");
    imprime_lista(l1);
    imprime_lista(l2);
    printf("---------------------------------------------------\n");
}

void cria_reserva(lista* l1, lista* l2, Data data_atual){
    Intervalo interv;
    //pede-se o tipo de serviço(lavagem/manutenção)
    printf("Escolha um serviço: 1-Lavagem(meia hora) 2-Manutencao(uma hora) ");
    inputUmDigito(&interv.serviço, '1', '2');
    //pede-se a data inicial do serviço
    printf("Dia:(DD/MM/AAAA) ");
    diaValido(&interv.h_inicial.dia,&interv.h_inicial.mes,&interv.h_inicial.ano);
    printf("Horas:(HH:MM) ");
    validHour(&interv.h_inicial.horas, &interv.h_inicial.minutos, interv.serviço);
    //verificamos se a data introduzida para a reserva é maior que a atual
    while(compare_date(data_atual,interv.h_inicial) == 1){
        printf("Não podes fazer uma reserva para o passado :)\n");
        printf("Dia:(DD/MM/AAAA) ");
        diaValido(&interv.h_inicial.dia,&interv.h_inicial.mes,&interv.h_inicial.ano);
        printf("Horas:(HH:MM) ");
        validHour(&interv.h_inicial.horas, &interv.h_inicial.minutos, interv.serviço);
    }
    //calcula-se a data final com base na data inicial e no serviço
    interv.h_final = soma_data(interv.h_inicial,interv.serviço);
    //pede-se o número do cc
    printf("Número de Cartão de Cidadão: ");
    ccValido(&interv.cc);
    //verifica-se a disponibilidade consoante a data que o cliente inseriu
    int disponibilidade = data_in_lista(l1, interv);
    if(disponibilidade == 0){
        //caso haja, encontra-se um id único e insere-se na lista das reservas
        insere_lista(l1,interv);
    }
    else{
        //caso não haja então assume-se o id da reserva que está a interferir e coloca-se na lista das pre-reservas
        insere_lista(l2,interv);
    }
    printAllReservations(l1,l2);
}

void cancela_reserva(lista* l1, lista* l2){
    //pede-se informação ao cliente sobre a reserva para cancelar
    Intervalo cancela;
    printf("Qual era o serviço?: 1-Lavagem 2-Manutencao ");
    inputUmDigito(&cancela.serviço, '1', '2');
    printf("Dia da reserva para cancelar:(DD/MM/AAAA) ");
    diaValido(&cancela.h_inicial.dia, &cancela.h_inicial.mes, &cancela.h_inicial.ano);
    printf("A que horas era a reserva:(HH:MM) ");
    validHour(&cancela.h_inicial.horas, &cancela.h_inicial.minutos, cancela.serviço);
    printf("Número de CC: ");
    ccValido(&cancela.cc);
    cancela.h_final = soma_data(cancela.h_inicial,cancela.serviço);
    //procura-se na lista das reservas se há alguma com a informação igual
    for(no *atual = l1->inicio; atual!=NULL; atual=atual->prox){
        //se encontrarmos retira-se e insere-se as pre-reservas que fiquem com disponibilidade
        if(checkTimeIntervalEquality(atual->valor,cancela) && atual->valor.cc == cancela.cc){
            retira_intervalo(l1,cancela);
            if(l2->inicio != NULL) passa_preReservas_livres(l1,l2);
            printAllReservations(l1,l2);
            return;
        }
    }
    //caso não se encontre nas reservas procuramos nas pre-reservas e retiramos de lá
    for(no *atual = l2->inicio; atual!=NULL; atual=atual->prox){
        if(checkTimeIntervalEquality(atual->valor,cancela) && atual->valor.cc == cancela.cc){
            retira_intervalo(l2,cancela);
            printAllReservations(l1,l2);
            return;
        }
    }
    printf("Não foram encontradas reservas\n");
}

void imprime_reservas_cliente(lista* l1, lista* l2){
    //pede-se o cc do cliente
    int n_cc;
    printf("Qual é o seu cc?: ");
    ccValido(&n_cc);
    //corre-se a lista das reservas até ao fim de modo a poder dar print em ordem decrescente(as listas estão em ordem crescente)
    no* aux = l1->inicio;
    while(aux != NULL && aux->prox != NULL) aux = aux->prox;
    while(aux != NULL){
        if(aux->valor.cc == n_cc){
            printf("%d ", aux->valor.cc);
            printf("%02d/%02d/%02d ",aux->valor.h_inicial.dia,aux->valor.h_inicial.mes,aux->valor.h_inicial.ano);
            printf("(%02d:%02d-%02d:%02d)-> ",aux->valor.h_inicial.horas,
                                            aux->valor.h_inicial.minutos,
                                            aux->valor.h_final.horas, 
                                            aux->valor.h_final.minutos);
        }
        aux = aux->prev;
    }
    printf("\n");
    //faz-se o mesmo mas para a lista das pre-reservas
    aux = l2->inicio;
    while(aux != NULL && aux->prox != NULL) aux = aux->prox;
    while(aux != NULL){
        if(aux->valor.cc == n_cc){
            printf("%d ", aux->valor.cc);
            printf("%02d/%02d/%02d ",aux->valor.h_inicial.dia,aux->valor.h_inicial.mes,aux->valor.h_inicial.ano);
            printf("(%02d:%02d-%02d:%02d)-> ",aux->valor.h_inicial.horas,
                                            aux->valor.h_inicial.minutos,
                                            aux->valor.h_final.horas, 
                                            aux->valor.h_final.minutos);
        }
        aux = aux->prev;
    }
    printf("\n");
}

void guarda_informacao_ficheiro(lista* l1, lista* l2, Data d){
    //abre-se o ficheiro
    FILE* f = fopen("reservas_info.txt", "w");
    if(f == NULL){
        perror("Erro ao abrir o ficheiro");
        return;
    }
    //guarda-se informação sobre a data
    fprintf(f, "%02d:%02d %02d/%02d/%d\n", d.horas, d.minutos, d.dia, d.mes, d.ano);
    //guarda-se o tamanho da lista das reservas e das pre-reservas
    fprintf(f, "%d %d\n", tamanho_lista(l1), tamanho_lista(l2));
    //guarda-se a informação de cada reserva e pre-reserva
    for(no *atual = l1->inicio; atual!=NULL; atual=atual->prox){
        fprintf(f, "%02d/%02d/%d %02d:%02d-%02d:%02d %d %08d %08d\n",atual->valor.h_inicial.dia,atual->valor.h_inicial.mes,atual->valor.h_inicial.ano,
                                                                 atual->valor.h_inicial.horas, atual->valor.h_inicial.minutos, atual->valor.h_final.horas, atual->valor.h_final.minutos,
                                                                 atual->valor.serviço, atual->valor.cc, atual->valor.priority);
    }
    for(no *atual = l2->inicio; atual!=NULL; atual=atual->prox){
        fprintf(f, "%02d/%02d/%d %02d:%02d-%02d:%02d %d %08d %08d\n",atual->valor.h_inicial.dia,atual->valor.h_inicial.mes,atual->valor.h_inicial.ano,
                                                                 atual->valor.h_inicial.horas, atual->valor.h_inicial.minutos, atual->valor.h_final.horas, atual->valor.h_final.minutos,
                                                                 atual->valor.serviço, atual->valor.cc, atual->valor.priority);
    }
    fclose(f);
    printAllReservations(l1,l2);
}

void carrega_informacao_ficheiro(lista* l1, lista* l2, Data* d){
    //limpa-se as listas de reservas e pre-reservas pois ao carregar do ficheiro não queremos guardar informação anterior
    while(l1->inicio != NULL){
        no *aux1 = l1->inicio;
        l1->inicio = l1->inicio->prox;
        free(aux1);
    }
    while(l2->inicio != NULL){
        no *aux2 = l2->inicio;
        l2->inicio = l2->inicio->prox;
        free(aux2);
    }
    FILE* f = fopen("reservas_info.txt", "r");
    if(f == NULL){
        perror("Erro ao abrir o ficheiro");
        return;
    }
    //carrega-se a informação sobre a data
    fscanf(f, "%02d:%02d %02d/%02d/%d\n", &(d->horas), &(d->minutos), &(d->dia), &(d->mes), &(d->ano));
    //carrega-se a informação das linhas em que começam e acabam as pre-reservas
    int start, end;
    fscanf(f, "%d %d", &start, &end);
    start++;
    end += start;
    //percorre-se as linhas do ficheiro, se o indice da linha for menor que o tamanho da l1 então adiciona-se às reservas, caso contrário adiciona-se às pré-reservas
    for(int i=1; i<end; i++){
        Intervalo interv = {0};
        if(i<start){
            fscanf(f, "%02d/%02d/%d %02d:%02d-%02d:%02d %d %08d %08d", &interv.h_inicial.dia, &interv.h_inicial.mes, &interv.h_inicial.ano,
                                                                   &interv.h_inicial.horas, &interv.h_inicial.minutos,
                                                                   &interv.h_final.horas, &interv.h_final.minutos,
                                                                   &interv.serviço, &interv.cc, &interv.priority);
            interv.h_final.ano = interv.h_inicial.ano;
            interv.h_final.mes = interv.h_inicial.mes;
            interv.h_final.dia = interv.h_inicial.dia;
            insere_lista(l1, interv);
        } else{
            fscanf(f, "%02d/%02d/%d %02d:%02d-%02d:%02d %d %08d %08d", &interv.h_inicial.dia, &interv.h_inicial.mes, &interv.h_inicial.ano,
                                                                   &interv.h_inicial.horas, &interv.h_inicial.minutos,
                                                                   &interv.h_final.horas, &interv.h_final.minutos,
                                                                   &interv.serviço, &interv.cc, &interv.priority);
            interv.h_final.ano = interv.h_inicial.ano;
            interv.h_final.mes = interv.h_inicial.mes;
            interv.h_final.dia = interv.h_inicial.dia;
            insere_lista(l2, interv);
        }
    }
    fclose(f);
    printAllReservations(l1,l2);
}

void avancar_tempo(lista* l1, lista* l2, Data* d){
    Data aux = *d;
    //pede-se a data para a qual avançar garantindo que ela é maior que a atual
    while(1){
        printf("Para que dia pretende avançar?:(DD/MM/AAAA) ");
        diaValido(&(d->dia), &(d->mes), &(d->ano));
        printf("Para que horas pretende avançar?:(HH:MM) ");
        validHour(&(d->horas), &(d->minutos), 1);
        if(compare_date(*d, aux) == 1){
            break;
        } else{
            printf("Não podes avançar para uma data menor que a atual\n");
        }
    }
    //retiramos as reservas e pre-reservas cujas datas tenham expirado, ou seja, os serviços tenham ocorrido
    no* atual = l1->inicio;
    no* proximo;
    while(atual != NULL){
        proximo = atual->prox;
        if(compare_date(*d,atual->valor.h_final) == 1 || compare_date(*d,atual->valor.h_final) == -1){
            retira_intervalo(l1, atual->valor);
        }
        atual = proximo;
    }

    atual = l2->inicio;
    while(atual != NULL){
        proximo = atual->prox;
        if(compare_date(*d,atual->valor.h_final) == 1 || compare_date(*d,atual->valor.h_final) == -1){
            retira_intervalo(l2, atual->valor);
        }
        atual = proximo;
    }
    printAllReservations(l1,l2);
}