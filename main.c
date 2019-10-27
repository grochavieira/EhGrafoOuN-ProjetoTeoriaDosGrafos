#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void DFS(int);
int G[100][100], visited[100];
int matrizB[100][100];
int n;
int V = 3;
int contadorzinho = 0;
int arvore = 0;
int conexo = 0;
int completo = 0;
int simples = 0;
int arestinhas = 0;

struct Grafo
{
    int **matriz;
    int num_nos;
};

int **criaMatriz(int linhas, int colunas)
{
    int **m = malloc(sizeof(int *) * linhas);
    int i;
    for (i = 0; i < linhas; i++)
    {
        m[i] = malloc(sizeof(int) * colunas);
    }
    return m;
}

void destroiMatriz(int **m, int linhas)
{
    int i;
    for (i = 0; i < linhas; i++)
    {
        free(m[i]);
    }
    free(m);
}

void imprimeMatriz(int **m, int linhas, int colunas)
{
    int i;
    int j;
    printf("Matriz adjacencia:\n");
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            printf("%-3d ", m[i][j]);
        }
        puts("");
    }
}

struct Grafo leiaGrafo()
{
    int i;
    FILE *fr = fopen("A.txt", "r");

    int nums = 0;
    while (fscanf(fr, "%d", &i) == 1)
    {
        nums++;
    }

    rewind(fr);
    int num_nos = sqrt(nums);
    int **m = criaMatriz(num_nos, num_nos);

    struct Grafo g;
    g.num_nos = num_nos;
    g.matriz = m;

    int linha = 0;
    int coluna = 0;
    while (fscanf(fr, "%d", &i) != EOF)
    {
        m[linha][coluna] = i;
        coluna++;
        if (coluna >= num_nos)
        {
            coluna = 0;
            linha++;
        }
    }
    //imprimeMatriz(m, num_nos, num_nos);
    fclose(fr);
    return g;
}

void grafoSimples(struct Grafo g)
{
    int cont = 0, i, j;
    for (i = 0; i < g.num_nos; i++)
    {
        for (j = 0; j < g.num_nos; j++)
        {
            if (g.matriz[i][j] >= 1 && cont == 0)
            {
                cont++;
                printf("O grafo nao eh simples, pois os vertices:\n");
                simples = 1;
            }
        }
    }
    if (cont == 0)
    {
        printf("O grafo eh simples, pois nao ha arestas multiplas ou lacos\n");
    }
    else
    {
        for (i = 1; i <= g.num_nos; i++)
        {
            for (j = 1; j <= g.num_nos; j++)
            {
                if (i == j)
                {
                    if (g.matriz[i - 1][j - 1] > 0)
                    {
                        printf("V%d tem um laco\n", i);
                    }
                }
                if (g.matriz[i - 1][j - 1] > 1)
                {
                    printf("V%d e V%d tem arestas multiplas entre eles.\n", i, j);
                }
            }
        }
    }
    puts("");
}

void graus(struct Grafo g)
{
    int i, j, aux;
    int vetor[g.num_nos], vetor2[g.num_nos];
    for (i = 0; i < g.num_nos; i++)
    {
        vetor[i] = 0;
        vetor2[i] = 0;
    }
    for (i = 0; i < g.num_nos; i++)
    {
        for (j = 0; j < g.num_nos; j++)
        {
            if (i == j)
            {
                vetor[i] += (g.matriz[i][j] * 2);
                vetor2[i] += (g.matriz[i][j] * 2);
            }
            else
            {
                vetor[i] += g.matriz[i][j];
                vetor2[i] += g.matriz[i][j];
            }
        }
    }
    for (i = 0; i < g.num_nos; i++)
    {
        for (j = 0; j < g.num_nos - 1; j++)
        {
            if (vetor[j] < vetor[j + 1])
            {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
    for (i = 0; i < g.num_nos; i++)
    {
        for (j = 0; j < g.num_nos; j++)
        {
            if (vetor2[j] == vetor[i])
            {
                printf("V%d tem %d graus.\n", j + 1, vetor[i]);
                vetor2[j] = -1;
                vetor[i] = -2;
            }
        }
    }
    puts("");
}

void numeroArestas(struct Grafo g)
{
    int i, j, total = 0;
    for (i = 0; i < g.num_nos; i++)
    {
        for (j = 0; j < g.num_nos; j++)
        {
            if (i == j)
            {
                total += (g.matriz[i][j] * 2);
            }
            else
            {
                total += g.matriz[i][j];
            }
        }
    }
    arestinhas = total / 2;
    printf("Este grafo tem um total de %d arestas.\n", total / 2);
    puts("");
}

void grafoCompleto(struct Grafo g)
{
    int i, j, cont = 0;
    if (g.num_nos == 1)
    {
    }
    else
    {

        for (i = 0; i < g.num_nos; i++)
        {
            for (j = 0; j < g.num_nos; j++)
            {
                if (i != j && cont == 0)
                {
                    if (g.matriz[i][j] != 1)
                    {
                        printf("Este grafo nao eh completo\n");
                        cont = 1;
                    }
                }
                else
                {
                    if (cont == 0)
                    {
                        if (g.matriz[i][j] >= 1)
                        {
                            printf("Este grafo nao eh completo\n");
                            cont = 1;
                        }
                    }
                }
            }
        }
    }
    if (cont == 0)
    {
        printf("Este grafo eh completo\n");
        completo = 1;
    }
    puts("");
}

void DFS(int i)
{
    int j;
    visited[i] = 1;

    for (j = 0; j < n; j++)
        if (!visited[j] && G[i][j] == 1)
            DFS(j);
}

int grafoConexo(struct Grafo g)
{
    int i, j;

    n = g.num_nos;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            G[i][j] = g.matriz[i][j];
        }
    }

    for (i = 0; i < n; i++)
    {
        visited[i] = 0;
    }

    DFS(0);

    int contador = 0;
    for (i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            printf("Este grafo nao eh conexo\n");
            conexo = 1;
            contador = 1;
            break;
        }
    }
    if (contador == 0)
    {
        printf("Este grafo eh conexo\n");
    }
    puts("");

    return contador;
}

int contemImpar(struct Grafo g, int src)
{
    int V = g.num_nos;
    int colorArr[V];
    for (int i = 0; i < V; ++i)
    {
        colorArr[i] = -1;
    }

    colorArr[src] = 1;
    int q[100];
    contadorzinho++;
    q[contadorzinho] = src;
    while (contadorzinho != 0)
    {
        int u = q[contadorzinho];
        contadorzinho--;
        if (g.matriz[u][u] == 1)
        {
            return 1;
        }

        for (int v = 0; v < V; ++v)
        {
            if (g.matriz[u][v] && colorArr[v] == -1)
            {
                colorArr[v] = 1 - colorArr[u];
                contadorzinho++;
                q[contadorzinho] = v;
            }
            else if (g.matriz[u][v] && colorArr[v] == colorArr[u])
                return 1;
        }
    }
    return 0;
}

void grafoBipartido(struct Grafo g)
{

    arvore = -1;
    if (g.num_nos == 1 && arestinhas >= 1)
    {
        arvore = 0;
    }
    else
    {
        arvore = contemImpar(g, 0);
    }
    if (arvore == 1)
    {
        printf("Este grafo nao eh bipartido, pois:\n");
        printf("-Ele tem ciclo de grau impar\n");
    }
    else if (arvore == 0)
    {
        printf("Este grafo eh bipartido\n");
    }
    printf("\n");
}

void grafoArvore(struct Grafo g)
{
    if (g.num_nos == 1 && arestinhas == 0)
    {
        printf("O grafo eh arvore\n");
    }
    else if (g.num_nos == 1 && arestinhas >= 1)
    {
        printf("O grafo nao eh arvore, pois ele:\n");
        printf("-Tem ciclo\n");
    }
    else
    {
        if (arvore == 1 || simples == 1 || completo == 1 || conexo == 1 || arestinhas >= g.num_nos)
        {
            printf("O grafo nao eh arvore, pois ele:\n");
            if (simples == 1)
            {
                printf("-Nao eh simples\n");
            }
            if (completo == 1)
            {
                printf("-Eh completo\n");
            }
            if (conexo == 1)
            {
                printf("-Nao eh conexo\n");
            }
            if (arestinhas >= g.num_nos)
            {
                printf("-Tem ciclo\n");
            }
            if (arvore == 1)
            {
                printf("-Nao eh bipartido\n");
            }
        }
        else
        {
            printf("O grafo eh arvore");
        }
    }
}

void passeios(struct Grafo g)
{
    int i, j, m;
    if (arestinhas == 0 || conexo == 1)
    {
        printf("Nao existe passeios ja que:\n");
        if (arestinhas == 0)
        {
            printf("-Nao tem arestas\n");
        }
        if (conexo == 1)
        {
            printf("-O grafo eh desconexo\n");
        }
    }
    else
    {
        int temp[g.num_nos][g.num_nos];
        for (i = 0; i < g.num_nos; i++)
        {
            int l = 0;
            for (m = 0; m < g.num_nos; m++)
            {
                int k = 0, soma = 0;
                for (j = 0; j < g.num_nos; j++)
                {
                    soma += g.matriz[i][k] * g.matriz[j][m];
                    k++;
                }
                temp[i][l] = soma;
                l++;
            }
        }
        int temp2[g.num_nos][g.num_nos];
        for (i = 0; i < g.num_nos; i++)
        {
            int l = 0;
            for (m = 0; m < g.num_nos; m++)
            {
                int k = 0, soma = 0;
                for (j = 0; j < g.num_nos; j++)
                {
                    soma += temp[i][k] * g.matriz[j][m];
                    k++;
                }
                temp2[i][l] = soma;
                l++;
            }
        }

        int aux = 0;
        for (i = 0; i < g.num_nos; i++)
        {
            for (j = 0; j < g.num_nos; j++)
            {
                if (aux < temp2[i][j])
                {
                    aux = temp2[i][j];
                }
            }
        }

        printf("O maior numero de passeios eh: %d\n", aux);

        printf("Que ocorre entre os vertices:\n");
        for (i = 0; i < g.num_nos; i++)
        {
            for (j = 0; j < g.num_nos; j++)
            {
                if (aux == temp2[i][j])
                {
                    printf("V%d e V%d\n", i + 1, j + 1);
                }
            }
        }
    }
    puts("");
}

int main(int argc, char *argv[])
{
    int bipartido;
    struct Grafo g = leiaGrafo();
    imprimeMatriz(g.matriz, g.num_nos, g.num_nos);
    puts("");

    printf("1 - O grafo eh simples?\n");
    grafoSimples(g);

    printf("2 - Numero de graus dos vertices do grafo:\n");
    graus(g);

    printf("3 - Qual o numero de arestas do grafo?\n");
    numeroArestas(g);

    printf("4 - Este grafo eh completo?\n");
    grafoCompleto(g);

    printf("5 - O grafo eh conexo?\n");
    bipartido = grafoConexo(g);

    printf("6 - O grafo eh bipartido?\n");
    if (bipartido == 1)
    {
        printf("Este grafo nao eh bipartido, pois ele nao eh conexo\n");
    }
    else
    {
        grafoBipartido(g);
    }

    printf("7 - O grafo eh uma arvore?\n");
    grafoArvore(g);
    printf("\n");

    printf("8 - Qual eh o maior numero de passeios de tamanho 3?\n");
    passeios(g);

    destroiMatriz(g.matriz, g.num_nos);
    system("pause");
    return 0;
}
