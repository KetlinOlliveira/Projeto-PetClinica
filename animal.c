
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "animal.h"

void MenuPet(Animais **pet, int *posicao_pet){
    int opcao = 1;
    do{
        printf("------Menu-------\n");
        printf("1-Cadastrar pet\n");
        printf("2-Consultar cadastros\n");
        printf("3-Listagem de Pets\n");
        printf("4-Salvar arquivos\n");
        printf("5-Carregar Arquivos\n");
        printf("0-Retornar\n");
        printf("\nEscolha uma opcao:\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
            CadastrarPet(pet, posicao_pet);
            break;
            case 2:
            ConsultarPet(*pet, posicao_pet);
            break;
            case 3:
            Listarpets(*pet, posicao_pet);
            break;
            case 4:
            SalvarArquivosPets(*pet, posicao_pet);
            break;
            case 5:
            CarregarArquivosPets(pet, posicao_pet);
            break;
            case 0:
            printf("Retornando...\n");
            break;
            default:
            printf("Valor invalido!\n");
        }
    }while(opcao!=0);
}

void CadastrarPet(Animais **pet, int *posicao_pet){

    *pet = realloc(*pet, (*posicao_pet +1)*sizeof (Animais));
   
      if(*pet ==NULL){
        printf("Erro ao alocar memoria!");
        exit(1);
      }

    Animais *novo_pet = &(*pet)[*posicao_pet];
    novo_pet->id =*posicao_pet +1;
 

    printf("Informe o nome do Pet: ");
     scanf(" %19[^\n]", novo_pet->nomePet);
    printf("Raca: ");
     scanf( " %[^\n]", novo_pet->raca);

      system("cls");
     printf("Pet cadastrado com sucesso!\n");
     (*posicao_pet)++;
    
}
void ConsultarPet(Animais *pet, int *posicao_pet){
    if(*posicao_pet == 0){
        printf("Nenhum cadastro feito!");
        return;
    }
    int opcao, opcao2;

    printf("\nInfome o codigo do cadastro: ");
    scanf("%d", &opcao);

      for(int i=0; i<*posicao_pet; i++){
        if(pet[i].id == opcao){
            printf("--------------------\n");
            printf("Nome: %s\n", pet[i].nomePet);
            printf("Raca: %s\n", pet[i].raca);
            printf("Codigo: %d\n", pet[i].id);
              printf("------------------\n");
              printf("1-Excluir Cadastro\n");
              printf("2-Editar\n");
              printf("0-Voltar\n");
              printf("O que deseja fazer?\n");
              scanf("%d", &opcao2);

              switch(opcao2){
                case 1:
                ExcluirPets(&pet, posicao_pet);
                break;
                case 2:
                EditarPet(pet, posicao_pet);
                break;
                case 0:
                break;
                default:
                printf("Numero invalido!\n");
        }
      }
 } 
}

void Listarpets(Animais *pet, int *posicao_pet){
    if(*posicao_pet== 0){
        printf("Nenhum pet cadastrado!");
        return;
    } 
    for(int i=0; i<*posicao_pet; i++){
        
        printf("Cadastro N %d\n", i+1);
         printf("Id: %d\n", pet[i].id);
        printf("Nome: %s\n", pet[i].nomePet);
        printf("Raca: %s\n", pet[i].raca);
       
        printf("\n_______________________________\n");
    }
    return;
}

void ExcluirPets(Animais **pet, int *posicao_pet){
    int id;
    int encontrado =0;
    printf("Informe o id do pet que deseja excluir:\n");
    scanf(" %d", &id);

    for(int i=0; i<*posicao_pet; i++){
        if((*pet)[i].id == id){
            encontrado =1;

            for(int j=i; j<*posicao_pet -1;j++){
                (*pet)[j]= (*pet)[j+1];
            }
            (*posicao_pet) --;
            *pet = realloc(*pet, (*posicao_pet) *sizeof(Animais));

            printf("Pet removido com sucesso!");
        }
}
if(!encontrado){
    printf("pet não encontrado!");
    return;
}
}
void EditarPet(Animais *pet, int *posicao_pet){
    int id;
    char escolha;

    printf("Informe o id do Pet buscado:\n");
    scanf("%d", &id);

    for(int i=0; i<*posicao_pet; i++){
        if(pet[i].id == id){
            printf("Registro %d\n", i);
            printf("Nome: %s\n", pet[i].nomePet);
            printf("ID: %d\n", pet[i].id);
            printf("Raca: %s\n", pet[i].raca);

            printf("Deseja editar este cadastro? (s/n)\n");
            scanf(" %c", &escolha);

            if(escolha == 's' || escolha == 'S'){
                printf("Editando Registro %d", pet[i].id);
                printf("\nNovo nome: ");
                scanf(" %[^\n]", pet[i].nomePet);
                printf("\nRaca:");
                scanf(" %[^\n]", pet[i].raca);               

            }else{
                printf("Cancelando edicao, retornando ao menu...\n");
                return;
            }

        }else{
            printf("Animal não encontrado!\n");
            return;
        }
    }
     system("cls");
    printf("Edição concluída com sucesso!\n");
}
void SalvarArquivosPets(Animais *pet, int *posicao_pet){
    FILE *arquivo = fopen( "pets.txt", "w");

    if(arquivo == NULL){
        printf("Erro ao criar arquivo!\n");
        return;
    }
    for(int i =0; i< *posicao_pet; i++){
        fprintf(arquivo, "Id:%d|Nome: %s|Raça: %s\n", pet[i].id, pet[i].nomePet, pet[i].raca);
    }

fclose(arquivo);
printf("Arquivo Salvo com sucesso!");
 }

 void CarregarArquivosPets(Animais **pet, int *posicao_pet){
    FILE *arquivo = fopen("pets.txt", "r");
    if(arquivo == NULL){
        printf("falha ao encontrar arquivo!");
        return;
    }

    char linha[100];
    while(fgets(linha, sizeof(linha), arquivo)){
        Animais temp;
 
        if(sscanf(linha, "Id:%d|Nome: %19[^|]|Raça: %19[^\n]", &temp.id, temp.nomePet, temp.raca) == 3) {
        *pet = realloc (*pet,(*posicao_pet + 1) *sizeof(Animais));
        if(*pet ==NULL){
            printf("Falha ao carregar arquivos!...");
            exit(1);
        }
        (*pet)[*posicao_pet] = temp;
        (*posicao_pet) ++;
        } else{
            printf("linha %s invalida!\n", linha);
          }
    printf("Carregado: %d - %s - %s\n", temp.id, temp.nomePet, temp.raca);
    }

    fclose(arquivo);
 }
