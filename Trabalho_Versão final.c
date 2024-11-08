#include <stdio.h>  
#include <stdlib.h>
#include <string.h>


typedef struct {
    int id; /* id único do evento */
    char nome[50]; 
    char data[11];  
    char local[50];
    char tipo[30];
} Evento;

void adicionar_evento(); 
void remover_evento();
void buscar_evento();
void exibir_eventos();
void salvar_eventos();
void carregar_eventos();

Evento eventos[100];
int total_eventos = 0;
int ultimo_id = 0; // Armazena o último ID usado

int main() {
    
    int opcao;

    carregar_eventos();  

    do {
        printf("\n--- Sistema de Cadastro de Eventos - Prefeitura de Fortaleza ---\n");
        printf("1. Adicionar Evento\n");
        printf("2. Remover Evento\n");
        printf("3. Buscar Evento\n");
        printf("4. Exibir Todos os Eventos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionar_evento(); break;
            case 2: remover_evento(); break;
            case 3: buscar_evento(); break;
            case 4: exibir_eventos(); break;
            case 5: salvar_eventos(); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    return 0;
}

void adicionar_evento() {
    if (total_eventos >= 100) { // verifica se há espaço para mais eventos
        printf("Limite de eventos atingido!\n");
        return;
    }
    Evento novo_evento; 
    novo_evento.id = ++ultimo_id; // atribui o próximo ID único

    printf("Nome do Evento: "); 
    scanf(" %[^\n]%*c", novo_evento.nome); 
    printf("Data (DD/MM/AAAA): ");
    scanf("%s", novo_evento.data);
    printf("Local: ");
    scanf(" %[^\n]%*c", novo_evento.local);
    printf("Tipo (Cultural, Educacional, Esportivo, Saude, etc.): ");
    scanf(" %[^\n]%*c", novo_evento.tipo);
   
    eventos[total_eventos++] = novo_evento;
    printf("Evento adicionado com sucesso!\n");
}

void remover_evento() {
    int id;
    printf("Digite o ID do evento a ser removido: ");
    scanf("%d", &id);

    for (int i = 0; i < total_eventos; i++) {
        if (eventos[i].id == id) {
            for (int j = i; j < total_eventos - 1; j++) {
                eventos[j] = eventos[j + 1];
            }
            total_eventos--;
            printf("Evento removido com sucesso!\n");
            return;
        }
    }
    printf("Evento não encontrado.\n");
}

void buscar_evento() {
    int id;
    printf("Digite o ID do evento a ser encontrado: ");
    scanf("%d", &id);

    for (int i = 0; i < total_eventos; i++) {
        if (eventos[i].id == id) {
            printf("ID: %d\n", eventos[i].id);
            printf("Nome: %s\n", eventos[i].nome);
            printf("Data: %s\n", eventos[i].data);
            printf("Local: %s\n", eventos[i].local);
            printf("Tipo: %s\n", eventos[i].tipo);
            return;
        }
    }
    printf("Evento não encontrado.\n");
}

void exibir_eventos() {
    printf("\n--- Lista de Eventos ---\n");
    for (int i = 0; i < total_eventos; i++) {
        printf("ID: %d, Nome: %s, Data: %s, Local: %s, Tipo: %s\n",
               eventos[i].id, eventos[i].nome, eventos[i].data, eventos[i].local, eventos[i].tipo);
    }
}

/*função para Salvar Eventos no Arquivo CSV*/
void salvar_eventos() {
    FILE *arquivo = fopen("eventos_fortaleza2.csv", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < total_eventos; i++) {
        fprintf(arquivo, "%d,%s,%s,%s,%s\n",
                eventos[i].id, eventos[i].nome, eventos[i].data,
                eventos[i].local, eventos[i].tipo);
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

/*função para carregar o arquivo*/
void carregar_eventos() {
    FILE *arquivo = fopen("eventos_fortaleza2.csv", "r");

    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado para carregar dados.\n");
        return;
    }

    while (fscanf(arquivo, "%d,%49[^,],%10[^,],%49[^,],%29[^\n]\n",
                  &eventos[total_eventos].id, // Corrigido: adicionando '&'
                  eventos[total_eventos].nome,
                  eventos[total_eventos].data,
                  eventos[total_eventos].local,
                  eventos[total_eventos].tipo) != EOF) {
        if (eventos[total_eventos].id > ultimo_id) {
            ultimo_id = eventos[total_eventos].id; // Atualiza o último ID
        }
        total_eventos++;
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}