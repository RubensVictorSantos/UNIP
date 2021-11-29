#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void titulo(char texto[256], char caractere){
    int x;
    int tam;
    tam=strlen(texto);

    printf(" ");
    for(x=1; x<=tam+4; x++)
        printf("%c", caractere);
    printf("\n");

    printf("  %s  \n",texto);

    printf(" ");
    for(x=1; x<=tam+4; x++)
        printf("%c",caractere);
    printf("\n");
}

struct dados_cliente {
    char nome[100];
    char cpf[100];
    char telefone[100];
    char endereco[255];
    char rua[100];
    char numero[4];
    char bairro[100];
    char cidade[100];
    char estado[100];
    char cep[8];
    char email[100];
    char dtDiag[100];
    char comorbidade[100];
    int dtNasc;
    int idade;
};

FILE* AbreArquivo(char modo, char caminho[30]){
    FILE *arquivo;
    switch(modo){
        case 'g':
            arquivo = fopen(caminho,"wt"); // Gravaço
            break;
        case 'l':
            arquivo = fopen(caminho,"rt"); // leitura
            break;
        case 'a':
            arquivo = fopen(caminho,"a"); // anexar
            break;
    }
    if(arquivo==NULL){
        printf("\nNao foi possivel abrir. \n Arquivo Inexistente");
        exit(0);
    }
    return arquivo;
}

void gravarLogin(){
    char email[100];
    char senha[100];
    char confsenha[100];
    FILE *arq;

    do{
        printf("\n Digite seu e-mail: ");
        scanf("%s",&email);
        printf("\n Digite uma senha: ");
        scanf("%s",&senha);
        printf(" Confirmar senha: ");
        scanf("%s",&confsenha);

        if(strcmp(senha,confsenha)!=0){
            printf("\n Erro ao confirmar senha, digite novamente.\n");
        }
    }
    while(strcmp(senha,confsenha)!=0);

    arq = AbreArquivo('a', "login.txt");

    fprintf(arq, "1;%s;%s\n", email, senha);

    fclose(arq);

    printf("\n");
    system("pause");
}

int validarLogin(){
    char email[100];
    char senha[100];

    FILE *arquivo;

    printf("\n *Login*\n");
    printf("\n Digite seu e-mail: ");
    scanf("%s", &email);
    printf(" Digite sua senha: ");
    scanf("%s", &senha);

    return 1;
}

void formularioCliente(){
    struct dados_cliente cliente;
    FILE *arq;

    char respComo;
    int indexComo;
    int dtNasc;
    char arrComorbidade[][13]={"","diabetes"
        ,"obesidade"
        ,"hipertensao"
        ,"tuberculose"
        ,"outros"};

    titulo("INFORMACOES PESSOAIS", '*');

    printf(" Digite o nome e o sobrenome: ");
    gets(cliente.nome);
    printf(" Digite o seu CPF ___.___.___-__: ");
    gets(cliente.cpf);
    printf(" Digite o seu telefone (__)____-____: ");
    gets(cliente.telefone);
    printf(" Digite ANO em que voce nasceu: ");
    scanf("%d", &cliente.dtNasc);
    printf(" Digite a data que voce foi diagnosticado __/__/____: ");
    scanf("%s", &cliente.dtDiag);

    printf("\n Possui alguma comorbidade?(s/n): ");
    scanf("%s", &respComo);

    if(respComo == 's'){
        for(int i = 1; i <= 5; i++){
            printf(" [%d] %s.\n", i, arrComorbidade[i]);
        }

        printf("\n Digite um numero correspondente: ");
        scanf("%d", &indexComo);
        strcpy(cliente.comorbidade,arrComorbidade[indexComo]);

        printf(" Voce selecionou: %s", cliente.comorbidade);
    }

    printf("\n");

    titulo("FORMULARIO ENDERECO", '*');

    printf("\n Digite o endereco (Rua, numero, bairro): ");
    gets(cliente.endereco);
    printf("\n Digite sua cidade: ");
    gets(cliente.cidade);
    printf(" Digite o seu estado: ");
    gets(cliente.estado);
    printf(" Digite seu o CEP _____-___: ");
    gets(cliente.cep);

    dtNasc = cliente.dtNasc;
    cliente.idade = calIdade(dtNasc);

    arq = AbreArquivo('a', "grupoderisco.txt");

    fprintf(arq,"1;%s;%s;%s;%d;%d;%s;%s;%s;%s;%s;%s\n",
            cliente.nome,
            cliente.cpf,
            cliente.telefone,
            cliente.dtNasc,
            cliente.idade,
            cliente.dtDiag,
            cliente.comorbidade,
            cliente.endereco,
            cliente.cidade,
            cliente.estado,
            cliente.cep);

    fclose(arq);

}

void calIdade(int dtNasc){
    int idade;
    struct tm *ano;
    time_t segundos;
    time(&segundos);

    ano=localtime(&segundos);

    idade = (ano->tm_year+1900) - dtNasc;

    return idade;
}
void buscarLogin(){
    FILE *arq;
    char Linha[255];
    int i = 1;
    char *result;
    char cod[2];

    arq = AbreArquivo('l',"login.txt");

    if (arq == NULL)  // Se houve erro na abertura
    {
        printf("Problemas na abertura do arquivo\n");
        return;
    }

    while (!feof(arq)){
        if(fgets(Linha, 255, arq))
            for(int l=0;l<=strlen(Linha);l++){
                cod[l] = Linha[l];

                if(Linha[l]==';'){

                    break;
                }
            }
        i++;
    }

    printf("%s", cod);

    fclose(arq);
}
void main(){
    struct dados_cliente cliente;
    char resp;

    titulo("Bem vindo ao sistema de cadastro", '*');

    printf("\n Voce possui um login?(s/n):");
    scanf("%c",&resp);
    if(resp != 's'){
        printf("\n *Criar login*\n");
        gravarLogin();
        system("CLS");
        titulo("Bem vindo ao sistema de cadastro", '*');

    }
    int clienteAutenticado = validarLogin();

    if(clienteAutenticado == 1){
        system("CLS");

        formularioCliente();
    }

    //buscarLogin();
}
