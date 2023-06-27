#include "../include/main.h"
#include "../include/security.h"

int main(){
    //criamos a lista1 onde vao estar todas as reservas e a lista2 onde irão estar todas as pré-reservas
    lista* l1 = initialize_list();
    lista* l2 = initialize_list();
    if(l1 == NULL || l2 == NULL){
        perror("Error creating list");
        return 1;
    }
    //estabecemos a hora atual
    Data current_day_hour;
    //menu com um switch que possui cada opção do programa
    int option = -1;
    while(option != 8){
        getCurrentTime(&current_day_hour);
        printf("Menu - Current Date: %02d:%02d %02d/%02d/%d\n", current_day_hour.horas, current_day_hour.minutos, current_day_hour.dia, current_day_hour.mes, current_day_hour.ano);
        printf("[1]-Create a new reservation\n[2]-Cancel a reservation\n[3]-Show client reservations\n[4]-Show all reservations\n[5]-Save current information to a file\n[6]-Load information file\n[7]-Forward time\n[8]-Exit\n");
        printf("Select an option: ");
        inputUmDigito(&option, '0', '8');
        
        switch(option){
            case 1:
                cria_reserva(l1,l2,current_day_hour);
                break;
            case 2:
                cancela_reserva(l1,l2,current_day_hour);
                break;
            case 3:
                imprime_reservas_cliente(l1,l2);
                break;
            case 4:
                printAllReservations(l1,l2);
                break;
            case 5:
                guarda_informacao_ficheiro(l1,l2,current_day_hour);
                break;
            case 6:
                carrega_informacao_ficheiro(l1,l2,&current_day_hour);
                break;
            case 7:
                avancar_tempo(l1,l2,&current_day_hour);
                break;
        }
    }
    //no final da utilização libertamos a memoria utilizada nas duas listas para garantir que não acontecem leaks
    free_list_memory(l1);
    free_list_memory(l2);
    return 0;
}
/*

problemas:

novas features:
    implementar base de dados
    implementar utilização pela internet
*/