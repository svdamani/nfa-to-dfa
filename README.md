# nfa-to-dfa
Convert Non-deterministic Finite Automaton to Deterministic Finite Automaton

generate_dfa - Generate DFA constructed from input NFA
 - DFA = Deterministic Finite Automaton
 - NFA = Non-deterministic Finite Automaton

Build it with `make`, and get DFA

    make
    ./generate_dfa NFA.txt

 - DFA.txt :: DFA constructed from the user's NFA

## Dependencies

    sudo apt-get install gcc make

## Overview
'generate_dfa' converts a given NFA to the corresponding DFA. It reads in
the NFA from "NFA.txt" and writes out the corresponding DFA to "DFA.txt".

"NFA.txt" must have the following format:

    N M
    a1 a2 ... af
    startState
    t1 t2 ... tm
    t1 t2 ... tm
     :
     :
Here,

    N -> No. of states in the NFA (numbered 0 ... N-1), 0 is the start state
    M -> Size of input alphabet
        (input symbols are numbered 1 ... M and 0 is reserved for epsilon)
    af -> Total of final states, followed by F states ( 0 <= ai <= N-1)
    startState :- for nfa, startstate of the machine
    N lines follow, for ith row, and jth column,
        value will be state from state i on symbol j
    Ti -> No. of states the NFA moves from si on input yi, followed by Ti states

"DFA.txt" will have the following format:

    s1:- y11 y12
    s2:- y21 y22
    :
    :
    N M
    
    a1,a2,...,af

Here,

    si -> ith state
    yij -> state on reading jth symbol from sith state
    N -> No. of states in the DFA (numbered 0 ... N-1), 0 is the start state
    M -> Size of input alphabet (input symbols are numbered 1 ... M)
    a1, a2....:- acceptable states

Each line until the end of file contains one transition ( si yi ti )