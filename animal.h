//Animal.h
#ifndef ANIMAIS_H
#define ANIMAIS_H


typedef struct{
    int id;
    char nomePet[20], raca[20];
}Animais;
void ConsultarPet(Animais *pet, int *posicao_pet);
void Listarpets(Animais *pet, int *posicao_pet);
void ExcluirPets(Animais **pet, int *posicao_pet);
void EditarPet(Animais *pet, int *posicao_pet);
void SalvarArquivosPets(Animais *pet, int *posicao_pet);
void CarregarArquivosPets(Animais **pet, int *posicao_pet);
void MenuPet(Animais **pet, int *posicao_pet);



#endif