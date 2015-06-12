#include "util.h"

/* Removing duplicates and arrange the string in lexicographical order */
void sort(char * string) {
    char * helper = malloc(20);          /// to help creating strings from integer
    int hashTable[50] = {0}, n = 0, i, check;   /// store the presence of strings
    *helper = 0;
    /// store which variables are present in string pointer
    for (i = 0; string[i]; i++) {
        check = n = 0;
        /// Extract out single number from string
        while (string[i] > 47 && string[i] < 58) {
            n = n * 10 + string[i++] - '0';
            check = 1;
        }
        if (check == 0) continue;
        hashTable[n] = 1;
    }
    *string = 0;
    /// Modif y the string in lexicographical non-repetitive manner
    for (i = 0; i < 50; i++) {
        if (!hashTable[i]) continue;
        sprintf(helper, "%d", i);
        if (*string) strcat(string, ",");
        strcat(string, helper);
    }
}

/* Update dfatable with output on corresponding input symbol */
void Update(FILE *ft, Trie *head) {
    Trie *node;
    int i, j, n, c = 0, k;
    char helper[30];
    /// Initialising dfatable to zero
    for (i = 0; i < 100; i++) for (j = 0; j < 20; j++)
        *dfaTable[i][j] = 0;
    for (i = 0; i < definite; i++) for (j = 0; j < strlen(dfaList[i]); j++) {
        n = c = 0;
        /// Extracting one number at a time from dfaList
        while (dfaList[i][j] > 47 && dfaList[i][j] < 58) {
            c = 1;
            n = n * 10 + dfaList[i][j++] - '0';
        }
        *helper = 0;
        if (c == 0) continue;    /// check if  value stored in n is valid
        for (k = 0; k < numSymbols; k++) {
            if (*dfaTable[i][k] != 0) strcat(dfaTable[i][k], ",");
            strcat(dfaTable[i][k], nfaTable[n][k]);
        }
    }
    /// writing dfatable to the output file
    for (i = 0; i < definite; i++) {
        fprintf(ft, "%c:- ", i + 'A');
        for (j = 0; j < numSymbols; j++) {
            sort(dfaTable[i][j]);
            node = head;
            for (k = 0; k < strlen(dfaTable[i][j]); k++) {
                n = c = 0;
                while (dfaTable[i][j][k] > 47 && dfaTable[i][j][k] < 58) {
                    n = n * 10 + dfaTable[i][j][k++] - '0';
                    c = 1;
                }
                if (c == 1 && node)
                    node = node->child[n];
            }
            if (node)    fprintf(ft, "%c ", node->leaf + 'A');
        }
        fprintf(ft, "\n");
    }
}

void nfaSearch(char *search, char nfaTable[numStates][numSymbols][9]) {
    int i = 0, j, x = 0, y = 0, check, n, curState = 0;
    /// change to integer the starting state of nfa from string
    while (nfaStart[i]) curState = curState * 10 + nfaStart[i++] - '0';
    char helper[1000] = {0};
    /// Calculate the final state on parsing search string
    for (i = 0; i < strlen(search); i++) {
        check = n = 0;
        if (*helper != 0) strcat(helper, ",");
        while (search[i] > 47 && search[i] < 58) {
            n = n * 10 + search[i++] - '0';
            check = 1;
        }
        if (check == 0) continue;
        strcat(helper, nfaTable[curState][n]);
        curState = n;
    }
    sort(helper);   /// Raemove duplicates and sort lexicographically
    sort(nfaFinal);
    /// Check if  state on parsing search string reaches any of the final states
    for (i = 0, j = 0; i < strlen(helper) && j < strlen(nfaFinal);) {
        check = 0;
        if (x == 0) while (helper[i] > 47 && helper[i] < 58) {
            x = x * 10 + helper[i++] - '0';
            check = 1;
        }
        if (check == 1) i++;
        check = 0;
        if (y == 0) while (nfaFinal[j] > 47 && nfaFinal[j] < 58) {
            y = y * 10 + nfaFinal[j++] - '0';
            check = 1;
        }
        if (check == 1) j++;
        if (x == y) {
            printf("String accepted by NFA\n");
            return;
        }
        else if (x < y) x = 0;
        else y = 0;
    }
    printf("String not accepted by NFA\n");
}

/* Check if on parsing search string, we do reach the final states */
void dfaSearch(char *search, Trie *head) {
    Trie *node = head;
    int i = 0, j, cur = node->leaf, n = 0, x = 0, y = 0, check = 0;
    char helper[1000] = {0};
    strcpy(dfaStart, nfaStart);
    /// Calculate the index of start state of input
    for (j = 0; j < strlen(dfaStart); j++) {
        check = n = 0;
        while (dfaStart[j] > 47 && dfaStart[j] < 58) {
            check = 1;
            n = n * 10 + dfaStart[j++] - '0';
        }
        if (check) node = node->child[n];
        if (!node) {
            fprintf(stderr, "No DFA with %s as start state\n", search);
            return;
        }
    }
    /// Calculate the final state on parsing search string
    for (i = 0; i < strlen(search); i++) {
        node = head;
        check = n = 0;
        /// Extract one number at a time
        while (search[i] > 47 && search[i] < 58) {
            n = n * 10 + search[i++] - '0';
            check = 1;
        }
        if (!check) continue;
        if (*helper) strcat(helper, ",");
        for (y = 0; y < strlen(dfaTable[cur][n]); y++) {
            check = x = 0;
            while (dfaTable[cur][n][y] > 47 && dfaTable[cur][n][y] < 58) {
                x = x * 10 + dfaTable[cur][n][y++] - '0';
                check = 1;
            }
            if (!check) continue;
            node = node->child[x];
            /// if  there is no state in dfa as dfastart state, return
            if (!node) {
                fprintf(stderr, "No start state in DFA\n");
                return;
            }
        }
        strcat(helper, dfaTable[cur][n]);
        cur = node->leaf;
    }
    x = y = 0;
    sort(helper);   ///remove duplicates and sort lexicographically
    sort(dfaFinal);
    /// Check if  string is accepted by dfa
    for (i = 0, j = 0; i < strlen(helper) && j < strlen(dfaFinal);) {
        check = 0;
        if (x == 0) while (helper[i] > 47 && helper[i] < 58) {
            x = x * 10 + helper[i++] - '0';
            check = 1;
        }
        if (check) i++;
        check = 0;
        if (y == 0) while (dfaFinal[j] > 47 && dfaFinal[j] < 58) {
            y = y * 10 + dfaFinal[j++] - '0';
            check = 1;
        }
        if (check) j++;
        if (x == y) {
            printf("String accepted by DFA\n");
            return;
        }
        if (x < y) x = 0;
        else y = 0;
    }
    printf("String not accepted by DFA\n");
}

/* Check if on parsing search string, we do reach the final states */
void dfaAcceptance(char *dfaFinal) {
    int i, j, n, x, k;
    char helper[50];
    *dfaFinal = 0;
    for (i = 0; i < strlen(nfaFinal); i++) {
        n = 0;
        while (nfaFinal[i] > 47 && nfaFinal[i] < 58)
            n = n * 10 + nfaFinal[i++] - '0';
        for (j = 0; j < definite; j++) {
            x = -1;
            for (k = 0; k < strlen(dfaList[j]); k++) {
                x = 0;
                while (dfaList[j][k] > 47 && dfaList[j][k] < 58)
                    x = x * 10 + dfaList[j][k++] - '0';
                if (x == n) break;
            }
            if (x == n) {
                if (*dfaFinal != 0) strcat(dfaFinal, ",");
                sprintf(helper, "%d", j);
                strcat(dfaFinal, helper);
            }
        }
    }
    sort(dfaFinal);
}