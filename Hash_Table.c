#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 349

typedef struct {
	int valor;
	char chave[20];
} tipoRegistro; 


void inicia(tipoRegistro *registros);
void linear(tipoRegistro *tabelahash, char *palavra, int *colisoes);
void quadratica(tipoRegistro *tabelahash, char *palavra, int *colisoes);
void dispersaoDulpa(tipoRegistro *tabelahash, char *palavra, int *colisoes);
int hash2(char palavra[20]);
int inserir(tipoRegistro *tabelahash, char *palavra, int *colisoes, int posicao);
void busca(tipoRegistro *tabelahash, char chave[20], int opcao);
void printar(tipoRegistro *tabelahash);

int main(){

    char texto[2216] = "Lorem ipsum dolor sit amet consectetur adipiscing elit Nulla maximus congue libero vel egestas Fusce sapien odio placerat in dictum in pulvinar quis sapien Nam suscipit ex justo laoreet vulputate velit ultricies sit amet Vivamus hendrerit nisl ac mauris gravida gravida Donec varius tincidunt aliquet Nam id iaculis urna Quisque commodo accumsan aliquet Aliquam erat volutpat Sed eget neque metus Nam eu molestie enim Vivamus mollis blandit sapien Fusce et quam ac arcu eleifend aliquet sit amet quis nisl Sed lobortis malesuada mi in placerat nisi auctor sit amet Fusce at placerat arcu Donec at sollicitudin eros rutrum consectetur turpis Vivamus rhoncus eget libero nec consectetur Nam et auctor mauris sit amet viverra nulla Nam auctor cursus sem sit amet sodales leo molestie vitae Phasellus sit amet metus at leo sodales imperdiet quis at arcu Donec arcu leo feugiat at lacus ut hendrerit dignissim dolor Nulla facilisi Cras elementum sapien rhoncus augue interdum a blandit felis tristique Maecenas semper scelerisque risus at eleifend augue scelerisque a Donec quis ligula sapien Etiam ornare pretium velit vel blandit arcu dictum non Fusce a viverra leo ut fringilla libero Nam in nunc sed lorem venenatis vestibulum In pellentesque pharetra urna sit amet scelerisque Phasellus sed mauris eget quam placerat laoreet a eu eros In eget venenatis nunc Sed laoreet leo leo sit amet interdum urna mattis non Praesent fringilla nunc in sapien placerat ultrices Cras cursus lectus in massa bibendum convallis Duis et elementum orci In molestie nunc leo vitae pulvinar augue dictum vitae Maecenas nec aliquam est eget porttitor risus Proin enim ante hendrerit ut suscipit vitae aliquet id sem Morbi dignissim eu enim quis malesuada Nam cursus mauris eget consequat malesuada enim erat malesuada lorem non bibendum orci metus eget ex Phasellus non accumsan urna Pellentesque mattis tortor nec placerat tincidunt Ut vulputate sem ut imperdiet molestie augue nisi sollicitudin nisi sed laoreet risus est ut diam Donec ut vestibulum magna Curabitur feugiat est nec consequat tristique purus dui tincidunt ex at pulvinar ante nibh at magna Sed a imperdiet nisl Phasellus dignissim odio sit amet eros condimentum feugiat";
    char separador[2] = " ";

    int opcao;
    printf("Escolha o metodo de lidar com as colisoes:\n");
    printf("1 -Linear:\n");
    printf("2 -Quadratica:\n");
    printf("3 -Dispersao Multipla:\n");
    scanf("%d", &opcao);

    tipoRegistro *tabelahash = malloc(SIZE * sizeof(tipoRegistro));
    inicia(tabelahash);
    int *colisoes = malloc(sizeof(int));
    *colisoes = 0;

    char* palavra = strtok(texto, separador);
    switch (opcao){
    case 1:
        while (palavra != NULL) {

            linear(tabelahash, palavra, colisoes);
            palavra = strtok(NULL, separador);

        }

        break;
    case 2:

        while (palavra != NULL) {

            quadratica(tabelahash, palavra, colisoes);
            palavra = strtok(NULL, separador);

        }

        break;
    case 3:

        while (palavra != NULL) {

            dispersaoDulpa(tabelahash, palavra, colisoes);
            palavra = strtok(NULL, separador);

        }

        break;
    
    default:
        break;
    }

    int opcaoLis;
    while (1){
        system("cls");
        printf("Escolha uma das opcoes abaixo:\n");
        printf("1 - Buscar valor\n");
        printf("2 - Printar tabela\n");
        printf("0 - Sair\n");
        scanf("%d", &opcaoLis);

        char chave[20];

        switch (opcaoLis){
            case 1:
                system("cls");
                printf("Digite a chave a ser procurada:\n");
                scanf("%s", chave);
                busca(tabelahash, chave, opcao);

                break;
            case 2:
                
                printar(tabelahash);

                break;

            default:

                break;
        }
        if(opcaoLis == 0){
            break;
        }
    }

    printf("the number of collisions that occurred when inserting the hash table was: %d\n", *colisoes);
    free(colisoes);
    free(palavra);
    free(tabelahash);
}

void inicia(tipoRegistro *registros){
    /*
        Start the table by putting 0 for valor and "" for chave
    */
    int i;
    
    for(i = 0; i < SIZE; i++){
        registros[i].valor = 0;
        strcpy(registros[i].chave, "");
    }
}

int inserir(tipoRegistro *tabelahash, char *palavra, int *colisoes, int posicao){
    /*
        Tries to insert a word (palavra) into position (posicao)
        of the hash table. Returns 1 if successful and returns 0 otherwise.
    */

    if((tabelahash[posicao].valor == 0) && (strcmp(tabelahash[posicao].chave, "") == 0)){
        strcpy(tabelahash[posicao].chave, palavra);
        tabelahash[posicao].valor += 1;
        return 1;
    }

    if(strcmp(tabelahash[posicao].chave, palavra) != 0){
        (*colisoes)++;
        return 0;
    }

    tabelahash[posicao].valor += 1;
    return 1;

}

void linear(tipoRegistro *tabelahash, char *palavra, int *colisoes){
    /*
        Handles collisions linearly
    */

    int k;
    long int cont = 0;
    int constante = 3;
    int inseriu = 0, posicao = 0;


    cont = 0;
    int tamanho_palavra = strlen(palavra);
    for(k = 0; k < tamanho_palavra; k++){
        cont += palavra[k] * (pow(constante, k));
    }

    k = 0;
    while(inseriu != 1){
        posicao = (cont + k) % SIZE;
        inseriu = inserir(tabelahash, palavra, colisoes, posicao);
        k++;
    }

}

void quadratica(tipoRegistro *tabelahash, char *palavra, int *colisoes){
    /*
        Handles collisions quadratically
    */

    int k;
    long int cont = 0;
    int constante = 3;
    int inseriu = 0, posicao = 0;


    cont = 0;
    int tamanho_palavra = strlen(palavra);
    for(k = 0; k < tamanho_palavra; k++){
        cont += palavra[k] * (pow(constante, k));
    }

    k = 0;
    while(inseriu != 1){
        posicao = (cont + k*k) % SIZE;
        inseriu = inserir(tabelahash, palavra, colisoes, posicao);
        k++;
    }

}

void dispersaoDulpa(tipoRegistro *tabelahash, char *palavra, int *colisoes){
    /*
        Handles collisions in a double scatter manner
    */
    
    int k;
    long int cont = 0;
    int constante = 3;
    int inseriu = 0, posicao = 0;

    cont = 0;
    int tamanho_palavra = strlen(palavra);
    for(k = 0; tamanho_palavra; k++){
        cont += palavra[k] * (pow(constante, k));
    }

    k = 0;
    while(inseriu != 1){
        posicao = (cont + k*hash2(palavra)) % SIZE;
        inseriu = inserir(tabelahash, palavra, colisoes, posicao);
        k++;
    }

}

int hash2(char *palavra){
    int i = 0, cont = 0;

    int tamanho_palavra = strlen(palavra);
    for(i = 0; i < tamanho_palavra; i++){
        cont += palavra[i] * (pow(3, i));
    }
    
    cont = 277 - (cont % 277);
    return cont;
}

// ---------------------------------- LISTAGEM ------------------------------------------------

void busca(tipoRegistro *tabelahash, char chave[20], int opcao){
    /*
        This function receives a word (palara) to be looked 
        for in the hash table and shows on the screen the number of times
        the word appeared in the table, if the word is found.
    */

    int k;
    long int cont = 0;
    int constante = 3;
    int posicao = 0;
   
    int tamanho_palavra = strlen(chave);
    for(k = 0; k < tamanho_palavra; k++){
        cont += chave[k] * (pow(constante, k));
    }

    k = 0;
    char aux[20];

    switch (opcao){
        case 1:

            posicao = (cont + k) % SIZE;
            strcpy(aux, tabelahash[posicao].chave);
        
            while(1){

                if(strcmp(chave, tabelahash[posicao].chave) == 0){
                    system("cls");
                    printf("chave: %s\n", tabelahash[posicao].chave);
                    printf("valor: %d\n", tabelahash[posicao].valor);
                    system("pause");
                    return;

                }

                k++;


                /*
                    if you have searched the entire table and not found it,
                    the key does not exist
                */
                posicao = (cont + k) % SIZE;
                if(strcmp(aux, tabelahash[posicao].chave) == 0){
                    system("cls");
                    printf("Chave nao encontrada!\n");
                    system("pause");
                    break;
                }
            }

            break;
        
        case 2:
            
            posicao = (cont + k*k) % SIZE;
            strcpy(aux, tabelahash[posicao].chave);

            while(1){

                if(strcmp(chave, tabelahash[posicao].chave) == 0){
                    system("cls");
                    printf("chave: %s\n", tabelahash[posicao].chave);
                    printf("valor: %d\n", tabelahash[posicao].valor);
                    system("pause");
                    return;

                }

                k++;

                /*
                    if you have searched the entire table and not found it,
                    the key does not exist
                */
                posicao = (cont + k*k) % SIZE;
                if(strcmp(aux, tabelahash[posicao].chave) == 0){
                    system("cls");
                    printf("Chave nao encontrada!\n");
                    system("pause");
                    break;
                }
            }

            break;

        case 3:
            
            posicao = (cont + k*hash2(chave)) % SIZE;
            strcpy(aux, tabelahash[posicao].chave);

            while(1){

                if(strcmp(chave, tabelahash[posicao].chave) == 0){
                    system("cls");
                    printf("chave: %s\n", tabelahash[posicao].chave);
                    printf("valor: %d\n", tabelahash[posicao].valor);
                    system("pause");
                    return;

                }

                k++;
                
                /*
                    if you have searched the entire table and not found it,
                    the key does not exist
                */
                posicao = (cont + k*hash2(chave)) % SIZE;
                if(strcmp(aux, tabelahash[posicao].chave) == 0){
                    system("cls");
                    printf("Chave nao encontrada!\n");
                    system("pause");
                    break;
                }
            }

            break;



        default:
            break;
    }

}

void printar(tipoRegistro *tabelahash){
    /*
        This function prints the table
    */

    int i;

    for(i = 0; i < SIZE; i++){
        if((tabelahash[i].valor == 0) && (strcmp(tabelahash[i].chave, "") == 0)){
            printf("Chave: | Valor:\n");
        }else{
            printf("Chave: %s | Valor: %d\n", tabelahash[i].chave, tabelahash[i].valor);
        }
    }
    system("pause");
}