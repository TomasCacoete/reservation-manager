#include "../include/main.h"
#include "../include/security.h"

int main(){
    //criamos a lista1 onde vao estar todas as reservas e a lista2 onde irão estar todas as pré-reservas
    lista* l1 = cria_lista();
    lista* l2 = cria_lista();
    if(l1 == NULL || l2 == NULL){
        perror("Erro ao criar a lista");
        return 1;
    }
    //estabecemos a hora atual
    Data dia_hora_atual;
    getCurrentTime(&dia_hora_atual);
    //menu com um switch que possui cada opção do programa
    int option = -1;
    while(option != 8){
        printf("Menu - Data Atual: %02d:%02d %02d/%02d/%d\n", dia_hora_atual.horas, dia_hora_atual.minutos, dia_hora_atual.dia, dia_hora_atual.mes, dia_hora_atual.ano);
        printf("[1]-Criar uma nova reserva\n[2]-Cancelar uma reserva\n[3]-Mostrar reservas do cliente\n[4]-Mostrar todas as reservas\n[5]-Guardar informação atual no ficheiro\n[6]-Carregar informação do ficheiro\n[7]-Avançar tempo\n[8]-Sair\n");
        printf("Selecione uma opção: ");
        inputUmDigito(&option, '0', '8');
        
        switch(option){
            case 1:
                cria_reserva(l1,l2,dia_hora_atual);
                break;
            case 2:
                cancela_reserva(l1,l2,dia_hora_atual);
                break;
            case 3:
                imprime_reservas_cliente(l1,l2);
                break;
            case 4:
                printAllReservations(l1,l2);
                break;
            case 5:
                guarda_informacao_ficheiro(l1,l2,dia_hora_atual);
                break;
            case 6:
                carrega_informacao_ficheiro(l1,l2,&dia_hora_atual);
                break;
            case 7:
                avancar_tempo(l1,l2,&dia_hora_atual);
                break;
        }
    }
    //no final da utilização libertamos a memoria utilizada nas duas listas para garantir que não acontecem leaks
    destroi_lista(l1);
    destroi_lista(l2);
    return 0;
}
/*
gcc *.c -o main -g
valgrind --track-origins=yes ./main

problemas:
o mesmo utilizador consegue fazer uma reserva para uma hora que ele mesmo já tenha marcado

todo list:
    dizer ao utilizador as horas disponíveis com base no serviço e dia
    implementar base de dados
    implementar utilização pela internet
*/