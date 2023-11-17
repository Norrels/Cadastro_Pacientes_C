#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>

//Variavel para validar o login
int verifUser = 0;
char usuario[15];

typedef struct endereco ENDERECO;
struct endereco{
    char estado[10];
    char bairro[20];
    char cidade[20];
	char rua[30];
	char numero[10];
	char cep[10];
};

typedef struct data DATA;
struct data {
	int dia;
	int mes;
	int ano;
};

typedef struct paciente PACIENTE;
struct paciente{
	char nome[40];
	char cpf[20];
	char telefone[20];
    ENDERECO local;
	char email[40];
    DATA data_nasc;
    DATA diagnostico;
	char comorbidades[60];
};

int main(){

//Declaração das variaveis
    int opcao = 0;
    int opcao1 = 0;
    char user[15];
    char senhaCorreta[15];
    int cadastrado = 0;
    char pacientes[1000];
    char comorbidades[1000];

//Criando os arquivos txts
    if (verifArquivo("usuarios.txt") == 0){
		FILE * usuarios;
		usuarios = fopen("usuarios.txt", "w");
		fclose(usuarios);
	}
	if (verifArquivo("listaPacientes.txt") == 0){
        FILE * listaPacientes;
		listaPacientes = fopen("listaPacientes.txt", "w");
		fclose(listaPacientes);
    }
    if (verifArquivo("grupoDeRisco.txt") == 0){
        FILE * grupoDeRisco;
        grupoDeRisco = fopen("grupoDeRisco.txt", "w");
        fclose(grupoDeRisco);
    }
//---------------------------------------------------
    do{
        pagInicial();
        scanf("%i", &opcao);

        switch(opcao) {
            case 1:{
                 do{
                    char senha[15];
                    login();
                    SetCursorPosition(16, 9);
                    scanf("%s", &usuario);
                    SetCursorPosition(14, 11);
                    scanf("%s", &senha);

                    FILE * usuarios;
                    usuarios = fopen("usuarios.txt", "r");

                    while (fgets(user, sizeof(user), usuarios) != NULL){
                        if (strstr(user, usuario) != NULL){
                            cadastrado = 1;
                            fscanf(usuarios, "%[^\n]", senhaCorreta);
                        }
                    }
                    fclose(usuarios);

                    SetCursorPosition(0, 15);
                    if (cadastrado == 1){

                        if (strstr(senha, senhaCorreta) != NULL){
                        verifUser = 1;

                        } else {
                        printf(" Ops sua senha esta incorreta!"
                        "\n Pressione ENTER para digitar novamente");
                        verifUser = 0;
                        getch();
                        }

                    } else {
                        printf("Ops esse usuario usuario nao esta cadastrado!"
                        "\n Pressione ENTER para digitar novamente...");
                        verifUser = 0;
                        getch();
                    }
                }while (verifUser != 1);

                do{
                    menu();
                    scanf("%i", &opcao1);

                    switch(opcao1) {

                        case 1: {

                            system("cls");
                            system("cls");
                            printf("\n-------------------------PACIENTES CADASTRADOS---------------------------");
                            printf("\n");
                            printf("\n");


                            FILE * listaPacientes;
                            listaPacientes = fopen("listaPacientes.txt", "r");

                            if (get_size("listaPacientes.txt") == 0){
                            printf("\n > Nao ha pacientes cadastrados!");
                            printf("\n > Pressione ENTER para continuar...");
                            }

                            while (fgets(pacientes, 1000, listaPacientes) != NULL){
                            printf("%s", pacientes);
                            }
                            fclose(listaPacientes);
                            getch();

                            break;
                            }

                        case 2:{

                            system("cls");
                            printf("\n-----------------  CONSULTA DE PACIENTES (GRUPO DE RISCO)  --------------------");
                            printf("\n");
                            printf("\n");

                            FILE * grupoDeRisco;
                            grupoDeRisco = fopen("grupoDeRisco.txt", "r");

                            if (get_size("grupoDeRisco.txt") == 0){
                                printf("\n > Nao ha pacientes com comorbidades!");
                                printf("\n > Pressione ENTER para continuar...");
                            }

                            while (fgets(comorbidades, 1000, grupoDeRisco) != NULL){
                                printf("%s", comorbidades);
                            }
                            fclose(grupoDeRisco);
                            getch();

                            break;
                            }

                        case 3: {
                            novoPacient();
                        } break;

                        default:{
                            printf("\n Digite uma opcao valida");
                            printf("\n Pressione enter e tente novamente");
                            getch();
                        }
                    }
                }while(opcao1 != 0);
            break;
            }

            case 2:{
                cadastrarUser();;
            break;
            }

            case 0:{
                break;
            }

            default:{
            printf("\n Opcao invalida");
            getch();
            break;
            }
        }
        }while(opcao != 0);
    }

void SetCursorPosition(int eixoX, int eixoY){
	COORD coord;
	coord.X = eixoX;
	coord.Y = eixoY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int get_size(const char* file_name)
{
    FILE *file = fopen(file_name, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

//Metodo para verificar se exite os arquivos .txt
int verifArquivo(const char *filename){
	FILE * file;

	if (file = fopen(filename, "r")){
		fclose(file);
		return 1;
	}
        return 0;
}

//-------------------INTERFACES----------------
void pagInicial (){
	system("cls");
printf("\n------------------ CADASTRO DE PACIENTES ------------------");
printf("\n|                          COVID-19                       |");
printf("\n|                                                         |");
printf("\n|                                                         |");
printf("\n|                      Seja bem vindo                     |");
printf("\n|                                                         |");
printf("\n|                   O que deseja fazer?                   |");
printf("\n|                                                         |");
printf("\n|                     1 - Logar-se                        |");
printf("\n|                     2 - Cadastrar-se                    |");
printf("\n|                     0 - Sair                            |");
printf("\n|                                                         |");
printf("\n-----------------------------------------------------------");
printf("\n\n  > Digite o numero correspondente a acao desejada");
printf("\n\n  > Escolha uma opcao: ");

}


void login (){
system("cls");
printf("\n------------------ CADASTRO DE PACIENTES ------------------");
printf("\n|                          COVID-19                       |");
printf("\n|                                                         |");
printf("\n|                                                         |");
printf("\n|                          LOGIN                          |");
printf("\n|                                                         |");
printf("\n|               Informe os seguintes campos               |");
printf("\n|                                                         |");
printf("\n|      Usuario:                                           |");
printf("\n|                                                         |");
printf("\n|      Senha:                                             |");
printf("\n|                                                         |");
printf("\n-----------------------------------------------------------");
}


void cadastrarUser (){
    //Variaveis da função
    char newLogin[15];
    char newSenha[15];
    int salvarUsuario = 1;

	system("cls");
    printf("\n------------------ CADASTRO DE PACIENTES ------------------");
    printf("\n|                          COVID-19                       |");
    printf("\n|                                                         |");
    printf("\n|                       NOVO USUARIO                      |");
    printf("\n|                                                         |");
    printf("\n|               Informe os seguintes campos:              |");
    printf("\n|                                                         |");
    printf("\n|  Nome de usuario:                                       |");
    printf("\n|                                                         |");
    printf("\n|  Senha de acesso:                                       |");
    printf("\n|                                                         |");
    printf("\n|                                                         |");
    printf("\n-----------------------------------------------------------");

    SetCursorPosition(20, 8);
    scanf("%s", &newLogin);
    SetCursorPosition(20, 10);
    scanf("%s", &newSenha);

//-------------------Verificando os usuarios-----------------------
    FILE * usuarios;

    usuarios = fopen("usuarios.txt", "r");
    char usuario[15];

    while (fgets(usuario, sizeof(usuario), usuarios) != NULL){

        if (strstr(usuario, newLogin) != NULL){
            salvarUsuario = 0;
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\n > Ops, para que esse usuario ja foi cadastrado!");
            printf("\n");
            printf("\n > Pressione ENTER para continuar...");
            getch();
        }
    } fclose(usuarios);
//-----------------------------------------------------------------

    if (salvarUsuario == 1) {

        FILE * usuarios;
        usuarios = fopen("usuarios.txt", "a");
        fprintf(usuarios, "%s\n", newLogin);
        fprintf(usuarios, "%s\n", newSenha);
        fclose(usuarios);
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n  > Usuario criado com sucesso!");
        printf("\n");
        printf("\n  > Pressione ENTER para continuar...");
        getch();
        }
}


void menu (){
    	system("cls");
printf("\n  ------------------  CADASTRO DE PACIENTES (COVID 19)  ----------------------");
printf("\n  |                                                                          |");
printf("\n  |                                                                          |");
printf("\n  |                             MENU PRINCIPAL                               |");
printf("\n  |                                                                          |");
printf("\n  |                  Digite um numero refetente ao desejado...               |");
printf("\n  |                                                                          |");
printf("\n  |          1 - Consulte a lista de pacientes cadastrados                   |");
printf("\n  |          2 - Consulte a lista de pacientes do grupo de risco             |");
printf("\n  |          3 - Cadastre um novo paciente                                   |");
printf("\n  |                                                                          |");
printf("\n  |                                                                          |");
printf("\n  |                   Digite 0 para realizar o logout                        |");
printf("\n  |                                                                          |");
printf("\n  ----------------------------------------------------------------------------");
printf("\n > Escolha uma opcao ");
}


void novoPacient(){
    PACIENTE novoPaciente;
	int salvarCadastro = 0;
	int idade;
    	char temp;
	system("cls");
		printf("\n > Caso houver comormidade a digite, caso contrario digite nao");
		printf("\n");
		printf("\n  -------------------  CADASTRO DE PACIENTES (COVID 19)  ---------------------");
		printf("\n  |                                                                          |");
		printf("\n  |                       CADASTRO DE NOVO PACIENTE                          |");
		printf("\n  |                                                                          |");
		printf("\n  |  DADOS PESSOAIS                                                          |");
		printf("\n  |                                                                          |");
		printf("\n  |  Nome:                                                                   |");
		printf("\n  |                                                                          |");

		SetCursorPosition(11, 9);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.nome);

		printf("\n  |       CPF:                                                               |");
		printf("\n  |                                                                          |");
		SetCursorPosition(15, 11);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.cpf);
		printf("\n  |           Telefone:                                                      |");
		printf("\n  |                                                                          |");
		SetCursorPosition(24, 13);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.telefone);
		printf("\n  |                   E-mail:                                                |");
		printf("\n  |                                                                          |");
		SetCursorPosition(30, 15);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.email);
		printf("\n  |                           Nascimento: __ / __ / ____                     |");
		printf("\n  |                                                                          |");
		SetCursorPosition(42, 17);
		scanf("%i", &novoPaciente.data_nasc.dia);
		SetCursorPosition(47, 17);
		scanf("%i", &novoPaciente.data_nasc.mes);
		SetCursorPosition(52, 17);
		scanf("%i",&novoPaciente.data_nasc.ano);

		printf("\n  |  ENDERECO                                                                |");
		printf("\n  |                                                                          |");
        printf("\n  |  Estado:                                                                 |");
		printf("\n  |                                                                          |");
		SetCursorPosition(13, 21);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.local.estado);
        printf("\n  |       Cidade:                                                            |");
		printf("\n  |                                                                          |");
		SetCursorPosition(18, 23);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.local.cidade);
		printf("\n  |           Bairro:                                                        |");
		printf("\n  |                                                                          |");
		SetCursorPosition(22, 25);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.local.bairro);
        printf("\n  |                   Rua:                                                   |");
		printf("\n  |                                                                          |");
		SetCursorPosition(27, 27);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.local.rua);
		printf("\n  |                         Numero:                                          |");
		printf("\n  |                                                                          |");
		SetCursorPosition(36, 29);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.local.numero);
		printf("\n  |                                 CEP:                                     |");
		printf("\n  |                                                                          |");
		SetCursorPosition(41, 31);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.local.cep);
		printf("\n  |  Data do Diagnostico: __ / __ / ____                                     |");
		printf("\n  |                                                                          |");
		SetCursorPosition(26, 33);
		scanf("%i", &novoPaciente.diagnostico.dia);
		SetCursorPosition(31, 33);
		scanf("%i", &novoPaciente.diagnostico.mes);
		SetCursorPosition(36, 33);
		scanf("%i", &novoPaciente.diagnostico.ano);
		printf("\n  |  Comorbidades:                                                           |");
		printf("\n  |                                                                          |");
		SetCursorPosition(19, 35);
		scanf("%c", &temp);
		scanf("%[^\n]", &novoPaciente.comorbidades);

        printf("\n  ----------------------------------------------------------------------------");
		printf("\n");
		printf("\n");
		printf("\n > Deseja salvar este cadastro? Digite 1 para sim ou 2 para nao");
		SetCursorPosition(64, 40);
		scanf("%i", &salvarCadastro);

while (salvarCadastro != 1);

FILE * listaPacientes;
listaPacientes = fopen("listaPacientes.txt", "a");

fprintf(listaPacientes, "Nome: %s\n", novoPaciente.nome);
fprintf(listaPacientes, "CPF: %s\n", novoPaciente.cpf);
fprintf(listaPacientes, "Telefone: %s\n", novoPaciente.telefone);
fprintf(listaPacientes, "Estado: %s\n", novoPaciente.local.estado);
fprintf(listaPacientes, "Cidade: %s\n", novoPaciente.local.cidade);
fprintf(listaPacientes, "Bairro: %s\n", novoPaciente.local.bairro);
fprintf(listaPacientes, "Endereco: %s, Numero %s\n", novoPaciente.local.rua, novoPaciente.local.numero);
fprintf(listaPacientes, "CEP: %s\n", novoPaciente.local.cep);
fprintf(listaPacientes, "Data De Nascimento: %i / %i / %i\n", novoPaciente.data_nasc.dia, novoPaciente.data_nasc.mes, novoPaciente.data_nasc.ano);
fprintf(listaPacientes, "E-mail: %s\n", novoPaciente.email);
fprintf(listaPacientes, "Data Do Diagnostico: %i / %i / %i\n", novoPaciente.diagnostico.dia, novoPaciente.diagnostico.mes, novoPaciente.diagnostico.ano);
fprintf(listaPacientes, "Diagnosticado por: %s\n", usuario);

if (!strcmp(novoPaciente.comorbidades, "")){
	fprintf(listaPacientes, "Comorbidades: nao possui\n\n\n");

    } else {
        fprintf(listaPacientes, "Comorbidades: %s\n\n\n", novoPaciente.comorbidades);
    }
        idade = 2021 - novoPaciente.data_nasc.ano;

        fclose(listaPacientes);

        FILE * grupoDeRisco;
            grupoDeRisco = fopen("grupoDeRisco.txt", "a");

            if (idade > 65 || strcmp(novoPaciente.comorbidades, "")){
                fprintf(grupoDeRisco, "IDADE: %i\n", idade);
                fprintf(grupoDeRisco, "CEP: %s\n\n\n", novoPaciente.local.cep);
            }

        fclose(grupoDeRisco);

}
