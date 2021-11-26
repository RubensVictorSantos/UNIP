#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char titulo(char texto[256], char caractere){
    int x;
    int tam;
    tam=strlen(texto);

    for(x=1; x<=tam+4; x++)
        printf("%c", caractere);
    printf("\n");

    printf("  %s  \n",texto);

    for(x=1; x<=tam+4; x++)
        printf("%c",caractere);
    printf("\n");
}
/**
int calIdade(int){

}
**/

struct dados_cliente {
    char nome[100];
    char sobrenome[100];
    int cpf;
    int telefone;
    char endereco[100];
    char rua[100];
    char numero[4];
    char bairro[100];
    char cidade[100];
    char estado[100];
    char cep[8];
    char dtNasc[100];
    char email[100];
    char dtDiag[100];
    char comorbidade[100];
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

void FecharArquivo(FILE *arquivo){
    fclose(arquivo);
}

void gravarLogin(){
    char email[100];
    char senha[100];
    char confsenha[100];
    FILE *arquivo;

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

    arquivo = AbreArquivo('a', "login.txt");
    fprintf(arquivo, "%s %s\n", email, senha);
    FecharArquivo(arquivo);

    printf("\n");
    system("pause");
}

int validarLogin(){
    char email[100];
    char senha[100];

    printf("\n *Login*\n");
    printf("\n Digite seu e-mail: ");
    scanf("%s", &email);
    printf(" Digite sua senha: ");
    scanf("%s", &senha);

    //Buscar e-mail e senha em um arquivo que contém todos os login.
    //Se existir o e-mail e senha então vai retornar 1

    return 1;
}

void formularioCliente(){
    struct dados_cliente cliente;
    char arrComorbidade[][13]={"","diabetes"
        ,"obesidade"
        ,"hipertensao"
        ,"tuberculose"
        ,"outros"};

    char respComo;
    int indexComo;

    titulo("INFORMACOES PESSOAIS", '*');

    printf("\n Digite o nome e o sobrenome: ");
    scanf("%s %s", &cliente.nome, &cliente.sobrenome);

    printf(" Digite o seu CPF: ");
    scanf("%d", &cliente.cpf);

    printf(" Digite o seu telefone: ");
    scanf("%d", &cliente.telefone);

    printf(" Digite sua data de nascimento: ");
    scanf("%s", &cliente.dtNasc);

    printf(" Digite a data que voce foi diagnosticado: ");
    scanf("%s", &cliente.dtDiag);

    printf("\n Possui alguma comorbidade?(s/n): ");
    scanf("%s", &respComo);

    if(respComo == 's'){
        for(int i = 1; i <= 5; i++){
            printf(" [%d] %s.\n", i, arrComorbidade[i]);
        }
    }

    printf("\n Digite um numero correspondente: ");
    scanf("%d", &indexComo);
    strcpy(cliente.comorbidade,arrComorbidade[indexComo]);

    printf("\n");

    titulo("FORMULARIO ENDERECO", '*');

    printf("\n Digite sua rua: ");
    scanf("%s", &cliente.rua);

    printf("\n Digite o numero: ");
    scanf("%s", &cliente.numero);

    printf("\n Digite seu bairro: ");
    scanf("%s", &cliente.bairro);

    printf("\n Digite sua cidade: ");
    scanf("%s", &cliente.cidade);

    printf("\n Digite o seu estado: ");
    scanf("%s", &cliente.estado);

    printf("\n Digite seu o CEP: ");
    scanf("%s", &cliente.cep);
}

void calIdade(){
    struct tm *data_hora_atual;
    time_t segundos;
    time(&segundos);

    data_hora_atual=localtime(&segundos);

    printf("\n Ano atual: %d", data_hora_atual->tm_year+1900);

    /**
        Calcular idade
    **/


}

void main(){

    /**calIdade();
/**
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
**/

    char str[11];
    int len;
    char dia[10];
    char mes[10];
    char ano[10];
    char teste;

    strcpy(str,"05/03/1998\0");
    len = strlen(str);

    for(int i=0;i<=len;i++){
        if(str[i]!='/'){
            if(i<2){
                char cpy[2];
                printf("%c",str[i]);
                strcpy(cpy,str[i]);

                printf("%c",cpy);

                strncat(dia,&cpy,1);
                printf("> %s\n", dia);
            }else if(i>2&&i<5){
                strncat(mes,&str[i],1);
                printf(">> %d\n",str);
            }
            else{
                strncat(ano,&str[i],1);
                printf(">>> %d\n",str);
            }
        }
    }

    //for(int i=0;i<=strlen(mes);i++){
    //  printf("%c\n",mes[i]);
    //}

    //printf(" %d\n",strlen(str));
    //printf(" dia: %s\n",dia);
    //printf(" mes: %s\n",mes);
    //printf(" ano: %s\n",ano);
    //formularioCliente();
}
