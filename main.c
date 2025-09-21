//Main.c
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "animal.h"
#include "veterinario.h"

//MAIN.C
//Alunos: Ketlin Gonçalves Oliveira e Inácio dourado
typedef struct{
    int codigo_vet;
    char nomePet[20], nomeVet[20];
    int cod_pet;
    char data[11];
} Atendimento;

void CadastrarAtendimento(Atendimento **atend, int *cod_atend, Animais *pet, int *posicao_pet, Veterinario *vet, int *cod_vet);
void listagemAtendimento(Atendimento *atend, int cod_atend);
void MenuAtend(Atendimento **atend, int *cod_atend, Animais *pet, int *posicao_pet, Veterinario *vet, int *cod_vet);
void Relatorio(Atendimento *atend, int *cod_atend, Animais *pet, int *posicao_pet, Veterinario *vet, int *cod_vet);
void ExcluirAtendimento(Atendimento **atend, int *cod_atend);
void EditarAtendimento(Atendimento *atend, int *cod_atend);

int main (void){
    Animais *pet = NULL;
    Veterinario *vet = NULL;
    Atendimento *atend = NULL;

    int posicao_pet=0;
    int opcao =1;
    int cod_vet = 0;
    int cod_atend =0;

    do{
        printf("____________Menu____________\nSelecione uma das opcoes:\n");
        printf("1- Pets\n");
        printf("2- Veterinario\n");
        printf("3- Atendimento\n");
        printf("4- Gerar Relatorio\n");
        printf("________________________________\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

         switch(opcao){
            case 1:
            MenuPet(&pet, &posicao_pet);
            break;
            case 2: 
            MenuVet(&vet, &cod_vet);
            break;
            case 3:
            MenuAtend(&atend,&cod_atend, pet, &posicao_pet, vet, &cod_vet);
            break;
            case 4:
            Relatorio(atend, &cod_atend, pet, &posicao_pet, vet, &cod_vet);
            break;
            case 0:
            printf("Encerrando o programa!\n");
            break;
            default:
            printf("Valor invalido!\n");
        }
    }while(opcao !=0);
    free(pet);
    free(vet);
    return 0;
}

void CadastrarAtendimento(Atendimento **atend, int *cod_atend, Animais *pet, int *posicao_pet, Veterinario * vet, int *cod_vet){
   
    if(*posicao_pet == 0 || *cod_vet == 0) {
        printf("Cadastre ao menos um Pet e um Veterinario antes de registrar um atendimento!\n");
        return;
    }

    *atend = realloc(*atend, (*cod_atend + 1) * sizeof(Atendimento));

    if (*atend == NULL){
        printf("Memoria não alocada!\n");
        exit(1);
    }
    Atendimento *novo = &(*atend)[*cod_atend];
    
    printf("Informe o codigo do Pet: ");
    scanf("%d", &novo -> cod_pet);

    int enc_pet = 0;

    for (int i = 0; i < *posicao_pet; i++){
        if(pet[i].id == novo -> cod_pet){
            enc_pet = 1;
       printf("Pet encontrado com nome: %s\n", pet[i].nomePet);
       strcpy(novo->nomePet, pet[i].nomePet);
            break;
        }
    }
    if (!enc_pet) {
        printf("Pet nao encontrado!\n");
        return;
    }

    printf("Informe o codigo do Veterinario: ");
    scanf("%d", &novo -> codigo_vet);

    int enc_vet = 0;

    for (int i = 0; i < *cod_vet; i++){
        if(vet[i].id_vet == novo -> codigo_vet){
            enc_vet = 1;
            printf("Veterinario encontrado com nome: %s\n", vet[i].profissional);
            strcpy(novo->nomeVet, vet[i].profissional);
            break;
        }
    }
    if (!enc_vet) {
        printf("Veterinario nao encontrado!\n");
        return;
    }

    printf("Informe a data do atendimento (DD/MM/AAAA): ");
    scanf(" %[^\n]", novo->data);

    system("cls");
    printf("Atendimento registrado com sucesso!\n");

    (*cod_atend)++;
}
void listagemAtendimento(Atendimento *atend, int cod_atend){

    int i;
    if(cod_atend == 0){
        printf("\nNenhum atendimento cadastrado");
        return;
    } 
    for(int i = 0; i < cod_atend; i++){
        printf("---------------------------------");
        printf("\nAtendimento %d: \n", i + 1);
        printf("Código do Pet: %d |", atend[i].cod_pet);
        printf("Nome do Pet: %s\n", atend[i].nomePet);
        printf("Código do Veterinario: %d |", atend[i].codigo_vet);
        printf(" Veterinario: %s\n", atend[i].nomeVet);
        printf("Data da consulta: %s\n", atend[i].data);
        printf("-----------------------------\n");
    }
    printf("\n1-Retornar ao Menu\n");
    printf("2-Encerrar programa\n");
    scanf("%d", &i);

    if(i== 1){
         system("cls");
        printf("Retornando ao menu...\n");
    }if(i== 2){
        exit(0);
    }
}
void MenuAtend(Atendimento **atend, int *cod_atend, Animais *pet, int *posicao_pet, Veterinario *vet, int *cod_vet){
    int opcao=1;

    do{
        printf("\n___________Menu Atendimento__________\n");
        printf("1 - Registrar Atendimento\n");
        printf("2 - Listar Atendimento\n");
        printf("3-  Editar\n");
        printf("4-  Deletar\n");
        printf("0 - Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        switch(opcao){
            case 1: 
                CadastrarAtendimento(atend, cod_atend, pet, posicao_pet, vet, cod_vet);
                break;
            case 2:
                listagemAtendimento(*atend, *cod_atend);
                break;
            case 3:
                EditarAtendimento(*atend, cod_atend);
            break;
            case 4:
                ExcluirAtendimento(atend, cod_atend);
            break;
            case 0:
                break;
                default:
                printf("Opção Invalida\n");
        }
    }while (opcao!= 0);
}
void Relatorio(Atendimento *atend, int *cod_atend, Animais *pet, int *posicao_pet, Veterinario *vet, int *cod_vet){

    int op;

    printf("_____________________________________\n");
    printf("          RELATORIO           \n");
    printf("\n");
    printf("         Atendimentos cadastrados:         \n");
    for(int i=0; i< *cod_atend; i++){
        printf("N %d\n ", i +1);
        printf("Código do Pet: %d\n", atend[i].cod_pet);
        printf("Nome do Pet: %s\n", atend[i].nomePet);
        printf("Código do Veterinário: %d\n", atend[i].codigo_vet);
        printf("Nome Veterinário: %s\n", atend[i].nomeVet);
        printf("Data: %s\n", atend[i].data);
        printf("________________________________\n");
    }
  printf("            Animais Cadastrados:             \n");
   for(int i=0;  i< *posicao_pet; i++){
        printf("Cadastro N %d\n", i+1);
        printf("Id: %d\n", pet[i].id);
        printf("Nome: %s\n", pet[i].nomePet);
        printf("Raca: %s\n", pet[i].raca);
        printf("_______________________________\n");
   }
   printf("          Veterinarios Cadastrados:             \n");
   for(int i=0; i<*cod_vet; i++){
       printf("Profissional: %s\n", vet[i].profissional);
        printf("Especialidade: %s\n", vet[i].especialidade);
        printf("Codigo: %d\n", vet[i].id_vet);
        printf("____________________________________\n");

   }
    printf("\n\n1-Retornar ao menu\n2-Encerrar Programa\n");
    scanf("%d", &op);

    if(op== 2){
        exit(0);
    }else{
        system("cls");
    }
}

void ExcluirAtendimento(Atendimento **atend, int *cod_atend) {
    int codigo;
    int encontrado=0;

    if(*cod_atend==0){
        printf("Nenhum atendimento registrado!\n");
        return;
    }
    printf("Informe o codigo do Pet do atendimento que deseja excluir: ");
    scanf("%d", &codigo);

    for (int i=0; i<*cod_atend; i++) {
        if ((*atend)[i].cod_pet==codigo) {
            encontrado = 1;

            for (int j=i; j<(*cod_atend-1); j++) {
                (*atend)[j]=(*atend)[j + 1];
            }
            (*cod_atend)--;
            *atend = realloc(*atend,(*cod_atend)*sizeof(Atendimento));
            
            if (*atend == NULL && *cod_atend > 0) {
                printf("Erro ao realocar!\n");
                 exit(1);
 }
      system("cls");
         printf("Atendimento excluido com sucesso.\n");
         return;
        }
    }
    if(!encontrado) {
           system("cls");
        printf("Atendimento com esse código de Pet nao encontrado.\n");
    }
}
void EditarAtendimento(Atendimento *atend, int *cod_atend) {
    int codigo;
    char confirmar;

    if (*cod_atend == 0) {
        printf("Nenhum atendimento registrado!\n");
        return;
    }
    printf("Informe o codigo do Pet do atendimento que deseja editar: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *cod_atend; i++) {
        if (atend[i].cod_pet == codigo) {
            printf("\nAtendimento encontrado:\n");
            printf("Código do Pet: %d\n", atend[i].cod_pet);
            printf("Nome do Pet: %s\n", atend[i].nomePet);
            printf("Código do Veterinário: %d\n", atend[i].codigo_vet);
            printf("Nome do Veterinário: %s\n", atend[i].nomeVet);
            printf("Data: %s\n", atend[i].data);

            printf("Deseja editar esse atendimento? (s/n): ");
            scanf(" %c", &confirmar);
            if (confirmar == 's' || confirmar == 'S') {
                printf("Novo nome do Pet: ");
                scanf(" %[^\n]", atend[i].nomePet);
                printf("Novo nome do Veterinario: ");
                scanf(" %[^\n]", atend[i].nomeVet);
                printf("Nova data: ");
                scanf(" %[^\n]", atend[i].data);

                system("cls");
                printf("Atendimento editado com sucesso.\n");
            } else {
                printf("Edicao cancelada.\n");
            }
            return;
        }
    }
    system("cls");
    printf("Atendimento com esse codigo de Pet não encontrado.\n");
}



