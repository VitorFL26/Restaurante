#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A struct prato guarda informações sobre os pratos disponíveis no restaurante.
struct prato
{
    int id;
    char nome[30];
    float preco;
};
typedef struct prato Prato;

//A struct prato guarda informações sobre os chocolates empilhados.
struct chocolate
{
    int id;
    char sabor[30];
};
typedef struct chocolate Chocolate;

//Essa função está atribuindo os chocolates na pilha.
Chocolate pilhaChocolates[5] =
{
    {0, "Ao Leite"},
    {1, "Meio Amargo"},
    {2, "Amargo"},
    {3, "Chocomenta"},
    {4, "Morango"}
    };
int topo = 4;


//A struct cliente contém informações do cliente na fila, como os pratos da comanda, quantidades de cada prato, o valor total da compra e o chocolate que o cliente recebeu.
struct cliente
{
    int comanda[5];
    int qtd[5];
    float valorCompra;
    Chocolate chocolate;
};
typedef struct cliente Cliente;

//Essa função está atribuindo o id, os pratos e os valores na lista de pratos
Prato itens_prato[5] =
{
    {0, "Picanha", 60.00},
    {1, "Bife", 40.00},
    {2, "Feijoada", 20.00},
    {3, "Strogonoff", 15.00},
    {4, "Macarrao", 17.00}
};


//A função "atribuirChocolate" é usada para dar um chocolate para um cliente específico. Ela verifica se ainda há chocolates na pilha antes de atribuir um.
void atribuirChocolate(Cliente *cliente)
{
    if (topo < 0)
    {
        printf("Não há mais chocolates na pilha!\n");
        return;
    }

    cliente->chocolate = pilhaChocolates[topo--];
    printf("Chocolate de sabor %s atribuido ao cliente.\n", cliente->chocolate.sabor);
}

// A struct infim é uma estrutura de dados linear no qual as operações de inserção e remoção são realizadas em pontos diferentes, chamados de início e fim.
struct infim
{
    Cliente clientes[5];
    int inicio;
    int fim;
};
typedef struct infim Fila;

Fila fila = { { {-1}, {-1}, 0.0 }, 0, 0};

// A função "addCliente" é usada para adicionar um cliente à fila.
void addCliente(Cliente cliente)
{
    fila.clientes[fila.fim++] = cliente;
}

//A função "chocolates" verifica se ainda há chocolates na pilha, se houver chocolates na pilha, ela atribui o chocolate no topo da pilha para o campo "chocolate" do struct "Cliente" passado como parâmetro e imprime o sabor desse chocolate.
void chocolates(Cliente *cliente)
{
    if (topo < 0)
    {
        printf("Não há mais chocolates na pilha!\n");
        return;
    }

    cliente->chocolate = pilhaChocolates[topo--];
    printf("Chocolate de sabor %s.\n", cliente->chocolate.sabor);
}

//A função "desenfileirar" é usada para remover o cliente no início da fila e mostrar a comanda dele. Antes de desenfileirar, essa função também usa a função "chocolates" para atribuir um chocolate para o cliente antes dele sair da fila.
void desenfileirar()
{
    int i = 0;
    if (fila.inicio == fila.fim)
    {
        printf("A fila esta vazia!\n");
        return;

    }
    printf("O cliente %d pagou a comanda saiu da fila e recebeu um chocolate\n", fila.inicio+1);
     // atribuir chocolate antes de desenfileirar
    chocolates(&fila.clientes[fila.inicio]);
    mostrarItensPedido(fila.clientes[fila.inicio]);
    fila.inicio++;
    printf("=============================================================\n");
}

//A função "desenfi" é usada para remover o cliente no início da fila sem mostrar a comanda dele.
void desenfi()
{
    int i = 0;
    if (fila.inicio == fila.fim)
    {
        printf("A fila esta vazia!\n");
        return;
    }
    fila.inicio++;
}

//A função "imprimirFila" é usada para mostrar todos os clientes na fila e suas respectivas comandas.
void imprimirFila()
{
    if(fila.inicio == 0 && fila.fim == 0){
        printf("Fila vazia.");
    }
    int i;
    for (i = fila.inicio; i < fila.fim; i++)
    {
        printf("Cliente %d:\n", i + 1);
        int j;
        for (j = 0; j < 5; j++)
        {
            if (fila.clientes[i].comanda[j] != -1 && fila.clientes[i].qtd[j] != 0)
            {
                printf("%d x %s (R$%.2f)\n", fila.clientes[i].qtd[j], itens_prato[fila.clientes[i].comanda[j]].nome, itens_prato[fila.clientes[i].comanda[j]].preco * fila.clientes[i].qtd[j]);
            }
        }
        printf("Valor total: R$%.2f\n\n", fila.clientes[i].valorCompra);
    }
}

//Função "imprimirPilhaChocolates" é usada para mostrar todos os chocolates disponíveis na pilha, começando pelo último adicionado.
void imprimirPilhaChocolates()
{
    int i;
    for (i = topo; i >= 0; i--)
    {
        printf("%d - %s\n", pilhaChocolates[i].id, pilhaChocolates[i].sabor);
    }
}

// Função imprimir consumidos é chamado quando o cliente quer relembrar o que ele já pediu.
void mostrarItensPedido(Cliente cliente) {
    printf("\n\n Itens do pedido do cliente: \n");
    for (int i = 0; i < 5; i++) {
        if (cliente.comanda[i]) {
            printf("%s - Quantidade: %d - Preco: %.2f\n", itens_prato[cliente.comanda[i]].nome, cliente.qtd[i], itens_prato[cliente.comanda[i]].preco * cliente.qtd[i]);
        }
    }
    printf("Valor total da compra: %.2f\n", cliente.valorCompra);
}


//A função "cardapio" é uma função que exibe um cardápio de itens disponíveis para o cliente escolher e adicionar à sua compra, e realiza as operações de adição de itens ao pedido do cliente, calcular o valor total da compra, e adicionar o cliente à fila de clientes que já finalizaram suas compras, ela também tem opções para imprimir fila de clientes, imprimir os itens consumidos e pilha de chocolates. Além disso, a função contém um loop que permite ao cliente escolher vários itens até que ele escolha sair do cardápio.
void cardapio(Cliente *cliente)
{
    int op;
    int qtd;
    int j = 0;


    do
    {
        printf("\nDigite o numero do item que desejar:\n");
        printf("0. Picanha\t\t\t|Preco: R$60,00\n");
        printf("1. Bife\t\t\t\t|Preco: R$40,00\n");
        printf("2. Feijoada\t\t\t|Preco: R$20,00\n");
        printf("3. Strogonoff\t\t\t|Preco: R$15,00\n");
        printf("4. Macarrao \t\t\t|Preco: R$17,00\n");
        printf("5. Para finalizar.\n");
        printf("6. Imprimir fila.\n");
        printf("7. Itens consumidos.\n");
        printf("8. Pilha de Chocolates.\n");
        scanf("%d", &op);
        // Limpar a tela
        system("cls");

        switch(op)
        {
        case 0:
            printf("Picanha!\nDigite a quantidade:");
            scanf("%d", &qtd);
            cliente->valorCompra += qtd * 60.00;
            cliente->comanda[j] = 0;
            cliente->qtd[j] = qtd;
            j++;
            break;

        case 1:
            printf("Bife!\nDigite a quantidade:");
            scanf("%d", &qtd);
            cliente->valorCompra += qtd * 40.00;
            cliente->comanda[j] = 1;
            cliente->qtd[j] = qtd;
            j++;
            break;
        case 2:
            printf("Feijoada!\nDigite a quantidade:");
            scanf("%d", &qtd);
            cliente->valorCompra += qtd * 20.00;
            cliente->comanda[j] = 2;
            cliente->qtd[j] = qtd;
            j++;
            break;
        case 3:
            printf("Strogonoff!\nDigite a quantidade:");
            scanf("%d", &qtd);
            cliente->valorCompra += qtd * 15.00;
            cliente->comanda[j] = 3;
            cliente->qtd[j] = qtd;
            j++;
            break;
        case 4:
            printf("Macarrao!\nDigite a quantidade:");
            scanf("%d", &qtd);
            cliente->valorCompra += qtd * 17.00;
            cliente->comanda[j] = 4;
            cliente->qtd[j] = qtd;
            j++;
            break;

        case 6:
            imprimirFila();
            break;

        case 7:
            mostrarItensPedido(*cliente);
            break;

        case 8:
            imprimirPilhaChocolates();
        }
    }
    while(op != 5);
    addCliente(*cliente);
}

int main()
{
    int i;
    for (i = 0; i < 5; i++)
    {
        Cliente cliente = {{-1}, {-1}, 0.0};
        cardapio(&cliente);
    }
    imprimirFila();
    desenfileirar();
    imprimirFila();
    desenfileirar();
    imprimirFila();
    desenfileirar();
    imprimirFila();
    desenfileirar();
    imprimirFila();
    desenfileirar();
    imprimirFila();
    return 0;

}
