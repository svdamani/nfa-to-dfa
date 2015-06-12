#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* Trie Data Type Declaration */
typedef struct Trie {
    int leaf;                   /// data
    struct Trie *child[20];     /// At max 20 childs, each initialised to zero
} Trie;

char dfaTable[100][20][30];
char dfaList[100][20];      /// dfalist will contain the list of states of dfa
int numStates, numSymbols, definite;

/// numStates store the states of nfa, numSymbols stores the common input symbols
char nfaStart[50], dfaStart[50];    /// starting states of nfa and dfa
char nfaFinal[100], dfaFinal[100];  /// final states of nfa and dfa
char nfaTable[100][100][9];

int TrieInsert(Trie**, char*);
void TriePrint(Trie*, char*);
void sort(char*);
void Update(FILE*, Trie *);
void nfaSearch(char*, char nfaTable[numStates][numSymbols][9]);
void dfaSearch(char*, Trie*);
void dfaAcceptance(char*);