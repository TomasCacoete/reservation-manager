#include "lista.h"

int data_igual(Data d1, Data d2){
    return d1.ano == d2.ano
        && d1.mes == d2.mes
        && d1.dia == d2.dia
        && d1.horas == d2.horas 
        && d1.minutos == d2.minutos;
}

int data_maior(Data d1, Data d2){
    if (d1.ano > d2.ano) return 1;
    else if (d1.ano < d2.ano) return 0;
    else if (d1.mes > d2.mes) return 1;
    else if (d1.mes < d2.mes) return 0;
    else if (d1.dia > d2.dia) return 1;
    else if (d1.dia < d2.dia) return 0;
    else if (d1.horas > d2.horas) return 1;
    else if (d1.horas < d2.horas) return 0;
    else if (d1.minutos > d2.minutos) return 1;
    else return 0;
}
//intervalos iguais se as datas iniciais e finais forem iguais
int intervalo_igual(Intervalo i1, Intervalo i2){
    return data_igual(i1.h_inicial,i2.h_inicial) && data_igual(i1.h_final,i2.h_final);
}
//função utilizada para calcular a hora final com base no serviço
Data soma_data(Data d, int service){
    Data final;
    final.horas = d.horas;
    final.minutos = d.minutos;
    final.ano = d.ano;
    final.mes = d.mes;
    final.dia = d.dia;
    //caso o serviço seja lavagem(30 min) se os minutos forem 30 soma-se um à hora e iguala-se os minutos a zero, caso não sejam(quando é 0) somamos apenas 30 min
    switch(service){
        case 1:
            //lavagem
            if(d.minutos == 30){
                final.horas += 1;
                final.minutos = 0;
            }
            else final.minutos += 30;
            break;
        //caso seja manutenção(1h) apenas somamos um à hora
        case 2:
            //manutenção
            final.horas += 1;
            break;
    }
    return final;
}

int data_in_intervalo(Intervalo quer_entrar, Intervalo ja_feito){
    if(ja_feito.serviço == 2) return data_igual(quer_entrar.h_final, soma_data(ja_feito.h_inicial,1))
                                  || data_igual(quer_entrar.h_inicial, soma_data(ja_feito.h_inicial,1));
    else return data_igual(quer_entrar.h_final, ja_feito.h_final)
             || data_igual(quer_entrar.h_inicial, ja_feito.h_inicial);
}

int data_in_lista(lista* l, Intervalo i){
    for(no *atual = l->inicio; atual!=NULL; atual=atual->prox){
        if(data_in_intervalo(i,atual->valor) || intervalo_igual(i,atual->valor)) return atual->valor.id;
    }
    return 0;
}