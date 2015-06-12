#include "util.h"

/* Main Function */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s 'input_file'\n", argv[0]);
        return -1;
    }
    FILE * fp = fopen(argv[1], "r"), * ft = fopen("DFA.txt", "w");
    if (!fp) {
        perror(argv[1]);
        return -1;
    }
    char * sourceString, stackString[numSymbols * numSymbols][10], search[1000];
    char * helper = malloc(20);
    int i, j, top = 0, n, k, l, bottom = 0, x, check = 0;
    Trie * head = NULL;
    numStates = 3;
    numSymbols = 2;
    fscanf(fp, "%d %d", &numStates, &numSymbols);
    fscanf(fp, "%s", nfaFinal);
    fscanf(fp, "%s", nfaStart);
    
    for (i = 0; i < numStates; i++)
        for (j = 0; j < numSymbols; j++)
            fscanf(fp, "%s", nfaTable[i][j]);
    fscanf(fp, "%s", search);
    n = numSymbols * numSymbols;
    sourceString = malloc(50);
    
    for (i = 0; i < numStates; i++) {
        sprintf(sourceString, "%d", i);
        TrieInsert(&head, sourceString);
        for (j = 0; j < numSymbols; j++)
            if(TrieInsert(&head, nfaTable[i][j])) {
                *stackString[top % n] = 0;
                sprintf(stackString[(top++) % n], "%s", nfaTable[i][j]);
            }
        while (bottom != top) {
            for (l = 0; l < numSymbols; l++) {
                *sourceString = 0;
                for (k = 0; k < strlen(stackString[bottom % n]); k++) {
                    if (k != 0) strcat(sourceString, ",");
                    x = 0;
                    check = 0;
                    while (stackString[bottom % n][k] > 47 &&
                        stackString[bottom % n][k] < 58) {
                        check = 1;
                        x = x * 10 + stackString[bottom % n][k++] - '0';
                    }
                    if (check) strcat(sourceString, nfaTable[x][l]);
                }
                sort(sourceString);
                if (TrieInsert(&head, sourceString))
                    strcpy(stackString[(top++) % n], sourceString);
            }
            ++bottom;
            bottom %= n;
        }
    }
    *helper = 0;
    TriePrint(head, helper);
    Update(ft, head);
    dfaAcceptance(dfaFinal);
    fprintf(ft, "%d %d\n", definite, numSymbols);
    
    for (i = 0; i < strlen(dfaFinal); i++) {
        n = check = 0;
        while (dfaFinal[i] > 47 && dfaFinal[i] < 58) {
            check = 1;
            n = n * 10 + dfaFinal[i++] - '0';
        }
        fprintf(ft, "%c", n + 'A');
        if (i != strlen(dfaFinal))
            fprintf(ft, ",");
    }
    nfaSearch(search, nfaTable);
    dfaSearch(search, head);
    printf("Output File : DFA.txt\n");
    return 0;
}