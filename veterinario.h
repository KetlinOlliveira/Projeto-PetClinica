//Veterinario.h
#ifndef VETERINARIO_H
#define VETERINARIO_H

typedef struct{
    char profissional[20], especialidade[20];
    int id_vet;
}Veterinario;

void MenuVet(Veterinario **vet, int *cod_vet);
void CadastrarVet(Veterinario **vet, int *cod_vet);
void ConsultarVet(Veterinario *vet, int *cod_vet);
void listarVet(Veterinario *vet, int*cod_vet);
void SalvarArquivo(Veterinario *vet, int *cod_vet);
void EditarVet(Veterinario **vet, int *cod_vet);
void ExcluirVet(Veterinario **vet, int *cod_vet);
void CarregarArquivosVets(Veterinario **vet, int *cod_vet);

#endif