#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINESZ 250

// Remove o '\n' do fim da linha
void remove_newline(char *ptr) {
    while (*ptr) {
        if (*ptr == '\n')
            *ptr = 0;
        else
            ptr++;
    }
}

typedef struct no{
    char valor[5];
    struct no *proximo;
}No;

typedef struct{
    No *topo;
    int tam;
}Pilha;

// operação push
void empilhar(Pilha *p, char x[5]){
    No *no = malloc(sizeof(No));
    strcpy(no->valor, x);
    no->proximo = p->topo;
    p->topo = no;
}

No* desempilhar(Pilha *p){
    No *no = NULL;
    if(p->topo){
        no = p->topo;
        p->topo = no->proximo;
    }
    return no;
}

void imprimir(No *no){
    if(no){
        printf(" # %s\n", no->valor);
        imprimir(no->proximo);
    }
}

void buscar_variavel(char line[], int l, Pilha *p) {
    int i = 0;
    char s[5], x[5];
    while (i == l || fgets(line, LINESZ, stdin) != NULL) {
        remove_newline(line);
        if (i + 1 == l) {
            if (sscanf(line, "var %s", s)) {
                empilhar(p, s);
            } else if (sscanf(line, "vet %s size %s", s, x)) {
                empilhar(p, s);
            }
            if (strncmp(line, "enddef", 6) == 0) {
                i++;
                if (i == l) { return; }
            }
        }

    }
}

int main() {

    char v1, parm1[5], parm2[5], parm3[5], var[5], conts[5], funcao;
    int r, i1, i2, l1 = 0;
    int inicio, fim, passo;
    char line[LINESZ];
    int count = 0;
    No *no;
    Pilha p;
    p.tam = 0;
    p.topo = NULL;

    // Lê uma linha por vez
    while (fgets(line, LINESZ, stdin) != NULL) {
        count++;
        remove_newline(line);

        // Verifica se line começa com 'end' (3 letras)
        if (strncmp(line, "end\n", 4) == 0) {
            printf(" leave\n ret\n");
            continue;
        }
        if (sscanf(line, "var %s", var)) {
            empilhar(&p, var);
            continue;
        } else if (sscanf(line, "vet %s size %s", var, conts)) {
            empilhar(&p, var);
            continue;
        }

        if (strncmp(line, "enddef", 6) == 0){
            imprimir(p.topo);
            p.topo = NULL;
        }

        // Verifica se é 'function' e quanto elementos possui
        r = sscanf(line, "function f%c %s %s %s", &funcao, parm1, parm2, parm3);
        if (r == 4) {
            printf(".globl f%c:\n", funcao);
            printf("f%c:\n", funcao);
            printf(" pushq %% rbp\n movq %%rsp, %%rbp\n");
            l1++;
            empilhar(&p, parm1);
            empilhar(&p, parm2);
            empilhar(&p, parm3);
            continue;
        }

        if (r == 3) {
            printf(".globl f%c:\n", funcao);
            printf("f%c:\n", funcao);
            printf(" pushq %% rbp\n movq %%rsp, %%rbp\n");
            l1++;
            empilhar(&p, parm1);
            empilhar(&p, parm2);
            continue;
        }

        if (r == 2) {
            printf(".globl f%c:\n", funcao);
            printf("f%c:\n", funcao);
            printf(" pushq %% rbp\n movq %%rsp, %%rbp\n");
            l1++;
            empilhar(&p, parm1);
            continue;
        }

        if (r == 1){
            printf(".globl f%c:\n", funcao);
            printf("f%c:\n", funcao);
            printf(" pushq %% rbp\n movq %%rsp, %%rbp\n");
            l1++;
            continue;
        }

        // Verifica se é 'for' e quanto elementos possui
        r = sscanf(line, "for %c = %d, %d, %d", &v1, &inicio, &fim, &passo);
        if (r == 4) {
            printf("Linha %d: %s\n", count, line);
            printf("Lido '%c' valores: %d, %d, %d\n", v1, inicio, fim, passo);
            printf("---\n");
            continue;
        }
        if (r == 3) {
            printf("Linha %d: %s\n", count, line);
            printf("Lido '%c' valores: %d, %d\n", v1, inicio, fim);
            printf("---\n");
            continue;
        }
        if (r == 2) {
            printf("Linha %d: %s\n", count, line);
            printf("Lido '%c' valor: %d\n", v1, inicio);
            printf("---\n");
            continue;
        }

        // Verifica se é um 'if'
        r = sscanf(line, "if v%d > v%d", &i1, &i2);
        if (r == 2) {
            printf("Linha %d: %s\n", count, line);
            printf("Indices: %d e %d\n", i1, i2);
            printf("---\n");
            continue;
        }
    }

    return 0;
}