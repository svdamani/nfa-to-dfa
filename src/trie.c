#include "util.h"

/* Insert the string in Trie data structure if  not already present */
int TrieInsert(Trie **head, char *sourceString) {
    int check = 0, n, c;
    Trie *iter;
    if (*head == NULL) *head = calloc(21, sizeof(Trie));
    iter = *head;
    for (int i = 0; i < strlen(sourceString); i++) {
        n = c = 0;
        ///extract one number at a time
        while (sourceString[i] > 47 && sourceString[i] < 58) {
            n = n * 10 + sourceString[i++] - '0';
            c = 1;
        }
        if (!c) continue;
        /// insert if  not already present
        if (iter->child[n] == NULL) {
            iter->child[n] = calloc(21, sizeof(Trie));
            check = 1;
        }
        iter = iter->child[n];
    }
    iter->leaf = 1;
    return check;
}

/* Extract valid dfa states from Trie data structure */
void TriePrint(Trie *head, char *helper) {
    if (head == NULL) return;
    /// check if  head is a legal state
    if (head->leaf == 1) {
        head->leaf = definite + 1;
        strcpy(dfaList[definite++], helper);
    }
    char *side = malloc(sizeof(char)* 20);
    /// consecutively check on childs and recursively call itself
    for (int i = 0; i < 20; i++) if (head->child[i]) {
        if ((*helper) != 0 && helper[strlen(helper) - 1] != ',')
            strcat(helper, ",");
        *side = 0;
        sprintf(side, "%d", i);
        strcat(helper, side);
        TriePrint(head->child[i], helper);  /// recursively call its child
        for (int j = strlen(helper) - 1; j >= 0; j--) {
            helper[j] = 0;
            if (helper[j] == ',') break;
        }
    }
}