#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

#define TAM 50
#define COR_LAYOUT system("COLOR A"); // EXIBE O DISPLAY NA COR VERDE
#define PT_BR setlocale(LC_CTYPE, "Portuguese")
#define LIMPA_TECLADO _flushall()
#define LIMPA_TELA system("CLS")

/**
 * ESTRUTURA FUNCIONÁRIO
 */
typedef struct Funcionario {
    int id;
    char nome[TAM];
    char cargo[TAM];
    float salario;
    struct Funcionario *prox;
} Funcionario;

/*
 * VARIÁVEIS GLOBAIS (TODAS AS FUNÇÕES E PROCEDIMENTOS PODEM VISUALIZÁ-LAS
 */
struct Funcionario *fInicio = NULL; // CONTROLA O FUNCIONÁRIO INICIAL
struct Funcionario *fAtual = NULL; // CONTROLA O FUNCIONÁRIO ATUAL
struct Funcionario *fAuxiliar = NULL; // MANIPULA SEMPRE REGISTROS ANTERIORES PARA AUXILIAR OS ATUAIS
struct Funcionario *varredor = NULL; // PONTEIRO QUE SERÁ UTILIZADO PELAS DEMAIS FUNÇÕES
int geradorID = 0; // GERA UM ID PARA CADA FUNCIONÁRIO

/*
 * PROTÓTIPO DE FUNÇÕES
 */
Funcionario* alocarMemoria();
void exibeisplay();
void criaRegistro();
void inserirDados(Funcionario *funcionario);
void exibirFuncionarios();
void pesquisarFuncionario(int id);
void adicionaBonus(int id);
void gravarEmArquivo();
int excluirFuncionario(int id);
int quantidadeDeFuncionarios();

/**
 * INÍCIO DO PROGRAMA
 */
int main() {

    PT_BR;
    COR_LAYOUT;
    exibeDisplay();

    getch();

    return 0;

}

/**
 * EXIBE O MENU DE OPÇÕES
 */
void exibeDisplay() {
    int regBusca;
    while(1) {
        LIMPA_TELA;
        printf("--------------------------------------------------\n");
        printf("Bem vindo ao sistema de cadastro de funcionários !\n");
        printf("--------------------------------------------------\n");
        printf("[1] - Cadastrar funcionário\n");
        printf("[2] - Exibir todos os cadastros\n");
        printf("[3] - Pesquisar funcionário por id\n");
        printf("[4] - Quantidade de funcionários cadastrados\n");
        printf("[5] - Excluir funcionário\n");
        printf("[6] - Adicionar bônus ao funcionário\n");
        printf("[7] - Gravar todos os dados em arquivo texto\n");
        printf("[8] - Sobre\n");
        printf("[9] - Sair\n");
        printf("--------------------------------------------------\n");
        printf("Digite sua opção: ");
        scanf("%d", &regBusca);
        printf("\n");
        switch (regBusca) {
            case 1:
                criaRegistro();
                break;
            case 2:
                exibirFuncionarios();
                break;
            case 3:
                printf("Informe o id do funcionário: ");
                scanf("%d", &regBusca);
                pesquisarFuncionario(regBusca);
                break;
            case 4:
                printf("Funcionários cadastrados: %d", quantidadeDeFuncionarios());
                getch();
                break;
            case 5:
                printf("\nInforme o funcionário (id) a ser eliminado: ");
                scanf("%d", &regBusca);
                if(excluirFuncionario(regBusca))
                    printf("\nRegistro excluído com sucesso !");
                else
                    printf("\nErro !");
                getch();
                break;
            case 6:
                printf("Informe o funcionário (id) a ser inserido um bônus: ");
                scanf("%d", &regBusca);
                adicionaBonus(regBusca);
                break;
            case 7:
                gravarEmArquivo();
                break;
            case 8:
                printf("\nDesenvolvido por: Guilherme França (C) - Copyright");
                getch();
                break;
            case 9:
                exit(0);
        }
    }
}

/**
 * ALOCA UM BLOCO DE MEMÓRIA PARA ARMAZENAR UM FUNCIONÁRIO
 *
 * @return UM PONTEIRO PARA ACESSAR O BLOCO DE MEMÓRIA
 */
Funcionario* alocarMemoria() {
    struct Funcionario *pFuncionario;
    pFuncionario = (Funcionario*) malloc(sizeof(Funcionario));

    return pFuncionario;
}

/**
 * CRIA UM REGISTRO DE FUNCIONÁRIO
 */
void criaRegistro() {
    if (fInicio == NULL) {
        fInicio = alocarMemoria(); // ALOCANDO MEMÓRIA
        fInicio->prox = NULL; // NÃO POSSUI PRÓXIMO REGISTRO
        fAuxiliar = fInicio;
        inserirDados(fInicio);
    } else {
        fAtual = alocarMemoria(); // ALOCANDO MEMÓRIA
        fAtual->prox = NULL; // NÃO POSSUI PRÓXIMO REGISTRO
        fAuxiliar->prox = fAtual; // LIGANDO O REGISTRO ATUAL AO ANTERIOR
        fAuxiliar = fAtual; // PASSANDO O AUXILIAR PARA O ATUAL (FUTUROS CADASTROS)
        inserirDados(fAtual);
    }
}

/**
 * INSERE OS DADOS DO FUNCIONÁRIO
 *
 * @par *FUNCIONARIO - FUNCIONÁRIO A SER INSERIDO OS DADOS
 */
void inserirDados(Funcionario *funcionario) {
    LIMPA_TECLADO;
    printf("Digite o nome do funcionário: ");
    gets(funcionario->nome);
    printf("Digite o cargo do funcionário: ");
    gets(funcionario->cargo);
    printf("Digite o salário do funcionário: ");
    scanf("%f", &funcionario->salario);
    funcionario->id = ++geradorID;
    printf("Cadastrado com sucesso !");
    getch();
}

/**
 * EXIBE TODOS OS REGISTROS DOS FUNCIONÁRIOS
 */
void exibirFuncionarios() {
    varredor = fInicio;
    while (varredor != NULL) {
        printf("Funcionário: %s\n", varredor->nome);
        printf("Cargo: %s\n", varredor->cargo);
        printf("Salário: R$%.2f\n", varredor->salario);
        varredor = varredor->prox;
    }
    getch();
}

/**
 * PESQUISA UM FUNCIONÁRIO POR ID
 *
 * @par ID - REGISTRO ÚNICO QUE SERÁ O FILTRO DA PESQUISA
 */
void pesquisarFuncionario(int id) {
    varredor = fInicio;
    while ((varredor != NULL) && (varredor->id != id))
        varredor = varredor->prox;
    if (varredor != NULL) {
        printf("\nFuncionário encontrado !\n\n");
        printf("Nome: %s\n", varredor->nome);
        printf("Cargo: %s\n", varredor->cargo);
        printf("Salário: R$%.2f", varredor->salario);
    } else
        printf("\nFuncionário não encontrado !\n");
    getch();
}

/**
 * MOSTRA QUANTOS FUNCIONÁRIOS FORAM CADASTRADOS
 *
 * @return A QUANTIDADE DE CADASTROS
 */
int quantidadeDeFuncionarios() {
    int quantidade = 0;
    varredor = fInicio;
    while (varredor != NULL) {
        quantidade++;
        varredor = varredor->prox;
    }
    return quantidade;
}

/**
 * EXCLUI UM FUNCIONÁRIO
 *
 * @var ID - INFORMA QUAL O ID DO FUNCIONÁRIO A SER EXCLUÍDO
 * @return 1 = EXCLUIU / 0 = NÃO EXCLUIU
 */
int excluirFuncionario(int id) {
    struct Funcionario *fAuxiliar2;
    varredor = fInicio;
    while ((varredor != NULL) && (varredor->id != id)) {
        fAuxiliar2 = varredor;
        varredor= varredor->prox;
    }
    if (varredor == NULL) {
        printf("\nNão foi encontrado o registro !");
        return 0;
    }
    else if (varredor == fInicio) { // REMOVE O PRIMEIRO CADASTRO
        fInicio = fInicio->prox;
        free(varredor);
    } else if (varredor == fAuxiliar){ // REMOVE O ÚLTIMO CADASTRO
        fAuxiliar = fAuxiliar2;
        fAuxiliar->prox = NULL;
        free(varredor);
    } else { // REMOVE UM CADSTRO QUALQUER
        fAuxiliar2->prox = varredor->prox;
        free(varredor);
    }
    return 1;
}

/**
 * ADICIONA UM BÔNUS SALARIAL EM % PARA UM FUNCIONÁRIO
 *
 * @par ID - REGISTRO DO FUNCIONÁRIO A SER ADICIOADO
 */
void adicionaBonus(int id) {
    float porcentagem;
    varredor = fInicio;
    while ((varredor != NULL) && (varredor->id != id))
        varredor = varredor->prox;
    if (varredor != NULL) {
        printf("Informe o percentual a ser adicionado para %s: ", varredor->nome);
        scanf("%f", &porcentagem);
        varredor->salario += varredor->salario * porcentagem / 100; // REGRA PARA ADICIONAR BÔNUS
        printf("\nAdicionado %.1f%% ao funcionário %s", porcentagem, varredor->nome);
    } else {
        printf("Funcionário não localizado !");
    }
    getch();
}
/**
 * GRAVA TODOS OS CADASTROS DENTRO DE UM ARQUIVO TXT
 */
void gravarEmArquivo() {
    FILE *arquivo;
    varredor = fInicio;
    char nomeArquivo[TAM];
    printf("Informe o nome do arquivo a ser criado: ");
    gets(nomeArquivo);
    strcat(nomeArquivo, ".txt");
    if ((arquivo = fopen(nomeArquivo, "a")) == NULL)
        printf("\nErro ao criar o arquivo ! Contate o desenvolvedor !");
    else {
        while (varredor != NULL) {
            fprintf(arquivo, "ID: %d", varredor->id);
            fprintf(arquivo, "Funcionário: %s\n",varredor->nome);
            fprintf(arquivo, "Cargo: %s\n",varredor->cargo);
            fprintf(arquivo, "Salário: R$%.2f\n",varredor->salario);
            fprintf(arquivo, "-------\n");
            varredor = varredor->prox;
        }
        printf("\nCadastros gravados com sucesso !");
        fclose(arquivo);
    }
    getch();
}
