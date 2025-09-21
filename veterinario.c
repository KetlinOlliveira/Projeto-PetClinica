//Entidade 2 Veteterinario.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "veterinario.h"

void MenuVet(Veterinario **vet, int *cod_vet){
    int opcao = 1;
    do{
        printf("------Menu-------\n");
        printf("1-Cadastrar profissional\n");
        printf("2-Consultar cadastros\n");
        printf("3-Listagem dos profissionais\n");
        printf("4-Salvar arquivos\n");
        printf("5-Carregar Arquivos\n");
        printf("0-Retornar\n");
        printf("\nEscolha uma opcao:");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                CadastrarVet(vet, cod_vet);
                break;
            case 2:
                ConsultarVet(*vet, cod_vet);
                break;
            case 3:
                listarVet(*vet, cod_vet);
                 break;
            case 4:
                SalvarArquivo(*vet, cod_vet);
                break;
            case 5:
               CarregarArquivosVets(vet, cod_vet);
                break;
            case 0:
                printf("Retornando...\n");
                break;
            default:
                printf("Valor invalido!\n");
        }
    }while(opcao!=0);
}

void CadastrarVet(Veterinario **vet, int *cod_vet){
    *vet = realloc(*vet, (*cod_vet + 1) * sizeof(Veterinario));
    if (*vet == NULL){
        printf("Memoria não alocada");
        exit(1);
    }

    Veterinario *novo = &(*vet)[*cod_vet];
    novo -> id_vet = *cod_vet + 1;
    printf("Informe o nome do profissional: ");
    scanf(" %19[^\n]", novo -> profissional);

    printf("Informe a especialidade: ");
    scanf(" %[^\n]", novo -> especialidade);

    printf("Veterinario cadastrado com sucesso\n");
    (*cod_vet)++;
}
void ConsultarVet(Veterinario *vet, int *cod_vet){
    if (*cod_vet == 0){
        printf("Nenhum veterinário cadastrado");
        return;
    }

    int codigo, opc;
    int encontrado = 0;

    printf("Informe o codigo do cadastro: ");
    scanf("%d", &codigo);

    for (int i = 0; i < *cod_vet; i++){
        if (vet[i].id_vet == codigo){
            encontrado = 1;
            printf("\nProfissional: %s", vet[i].profissional);
            printf("\nEspecialidade: %s", vet[i].especialidade);
            printf("\nCodigo: %d", vet[i].id_vet);

            printf("------------------\n");
            printf("1-Excluir Cadastro\n");
            printf("2-Editar\n");
            printf("0-Voltar\n");
            printf("O que deseja fazer?\n");
            scanf("%d", &opc);

            switch(opc){
                case 1:
                ExcluirVet(&vet, cod_vet);
                break;
                case 2:
                EditarVet(&vet, cod_vet);
                break;
                case 0:
                break;
                default:
                printf("Numero invalido!\n");

        }
        break;
        }
    }
    if (!encontrado){
        printf("Veterinário não encontrado.");
    }
}
void listarVet(Veterinario *vet, int*cod_vet){
    if (*cod_vet == 0){
        printf("\nNenhum veterinário cadastrado");
        return;
    }

    for (int i = 0; i < *cod_vet; i++){
        printf("------------------------");
        printf("\nProfissional: %s\n", vet[i].profissional);
        printf("\nEspecialidade: %s\n", vet[i].especialidade);
        printf("\nCodigo: %d\n", vet[i].id_vet);
        printf("------------------------\n");
    }

    return;
}
void SalvarArquivo(Veterinario *vet, int*cod_vet){
    if (*cod_vet == 0){
        printf("Nenhum veterinario cadastrado");
        return;
    }

    FILE *dados = fopen("dados.txt", "w");
    if (dados == NULL){
        printf("Erro");
        exit(0);
    }
    for (int i = 0; i < *cod_vet; i++){
      fprintf(dados, "Id:%d|Nome: %s|Especialidade: %s\n", vet[i].id_vet, vet[i].profissional, vet[i].especialidade);
    }
    printf("Arquivo Salvo");
    
    fclose(dados);

}
void EditarVet(Veterinario **vet, int *cod_vet){
    if (*cod_vet == 0){
        printf("Nenhum veterinario cadastrado");
        return;
    }

    int presente = 0;
    char nome[50];

    printf("\nDigite o nome que quer alterar: ");
    scanf(" %[^\n]", nome);

    for (int i = 0; i < *cod_vet; i++){
        if (strcmp(vet[i]->profissional, nome) == 0){

        printf("Informe o nome do profissional: ");
        scanf(" %[^\n]", vet[i]->profissional);

        printf("Informe a especialidade: ");
        scanf(" %[^\n]", vet[i]->especialidade);

        printf("Veterinario cadastrado com sucesso\n");
        
        presente = 1;

        }
    }
    if (presente != 1){
        printf("Não encontrado");
    }
}
void ExcluirVet(Veterinario **vet, int *cod_vet){
     if (*cod_vet == 0){
        printf("Nenhum veterinario cadastrado");
        return;
    }
    int codigo;
    int presente =0;

    printf("\nInforme o id que quer excluir: ");
    scanf("%d", &codigo);

    for (int i=0; i <*cod_vet; i++){
        if ((*vet)[i].id_vet == codigo){
        presente = 1;

        for(int j = i; j < *cod_vet; j++){
                (*vet)[j]= (*vet)[j + 1];
            }
            (*cod_vet)--;

            *vet = realloc(*vet, (*cod_vet) *sizeof(Veterinario));
            printf("Veterinario removido com sucesso!");
        }
    }
        if(!presente){
            printf("Veterinario não encontrado!");
        return;
}
}
void CarregarArquivosVets(Veterinario **vet, int *cod_vet){

    FILE *arquivo = fopen("dados.txt", "r");
    if(arquivo == NULL){
        printf("Falha ao encontrar arquivo!");
        return;
    }
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo)){
        Veterinario enter;
          if(sscanf(linha, "Id:%d|Nome: %19[^|]|Especialidade: %19[^\n]", &enter.id_vet, enter.profissional, enter.especialidade) == 3){
           *vet = realloc (*vet,(*cod_vet + 1) *sizeof(Veterinario));

        if(*vet ==NULL){
            printf("Falha ao carregar arquivos!...");
            exit(1);
        }
        (*vet)[*cod_vet] = enter;
        (*cod_vet) ++;
        
    }
     printf("Carregado: %d - %s - %s\n",  enter.id_vet, enter.profissional, enter.especialidade);
    }
    fclose(arquivo);
}
