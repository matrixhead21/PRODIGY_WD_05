#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NON_TERMINALS 10
#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 10

char non_terminals[MAX_NON_TERMINALS];
char productions[MAX_NON_TERMINALS][MAX_PRODUCTIONS][MAX_SYMBOLS];

int num_non_terminals = 0;
int num_productions[MAX_NON_TERMINALS] = {0};

void eliminate_left_recursion() {
    int i, j, k;
    char new_non_terminal[MAX_SYMBOLS];

    for (i = 0; i < num_non_terminals; i++) {
        for (j = 0; j < i; j++) {
            for (k = 0; k < num_productions[i]; k++) {
                if (productions[i][k][0] == non_terminals[j]) {
                    sprintf(new_non_terminal, "%s'", non_terminals[i]);
                    strcpy(productions[i][k], &productions[i][k][1]);
                    strcat(productions[i][k], new_non_terminal);

                    strcpy(productions[num_non_terminals][num_productions[num_non_terminals]], &productions[i][k][1]);
                    strcat(productions[num_non_terminals][num_productions[num_non_terminals]], new_non_terminal);
                    num_productions[num_non_terminals]++;
                }
            }
        }

        for (j = 0; j < num_productions[i]; j++) {
            if (productions[i][j][0] == non_terminals[i]) {
                sprintf(new_non_terminal, "%s'", non_terminals[i]);
                strcpy(productions[i][j], new_non_terminal);

                strcpy(productions[num_non_terminals][num_productions[num_non_terminals]], "ε");
                num_productions[num_non_terminals]++;
            }
        }
    }

    for (i = 0; i < num_non_terminals; i++) {
        printf("%c -> ", non_terminals[i]);
        for (j = 0; j < num_productions[i]; j++) {
            printf("%s | ", productions[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int i, j;

    printf("Enter the number of non-terminals: ");
    scanf("%d", &num_non_terminals);

    printf("Enter the non-terminals: ");
    for (i = 0; i < num_non_terminals; i++) {
        scanf(" %c", &non_terminals[i]);
    }

    for (i = 0; i < num_non_terminals; i++) {
        printf("Enter the number of productions for %c: ", non_terminals[i]);
        scanf("%d", &num_productions[i]);
        printf("Enter the productions for %c:\n", non_terminals[i]);
        for (j = 0; j < num_productions[i]; j++) {
            scanf("%s", productions[i][j]);
        }
    }

    printf("\nGrammar after left recursion elimination:\n");
    eliminate_left_recursion();

    return 0;
}
