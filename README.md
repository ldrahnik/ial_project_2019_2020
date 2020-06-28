ASSESSMENT 
==========

12.7/15b (no assessment report, -1b defense)

HPAC - Hamilton path and cycle
==============================

## Příklad spuštění:

```
./hpac -h
HPAC - Hamilton paths and cirtuits

Example of usage:

./hpac [-s <start>] [-e <end>] [-d] [-i] <inline graph|file contains graph>

Options:
-s start vertex [ OPTIONAL ], default is first vertex in file
-e end vertex [ OPTIONAL ], default is first vertex in file
-d debug [ OPTIONAL ], show debug messages
-i info [ OPTIONAL ], show info about executed algorithm
```

```
./hpac -s A -e E 'A B '$'\n'' B D '$'\n'' D E' # inline zápis malého grafu
A B
B D
D E

Results: 1
```

```
./hpac -e B -s H ./tests/graphs_in/2.in # spuštění na grafu načteného ze souboru
H I
I F
F E
E D
D C
C J
J G
G A
A B

Results: 1
```

## Omezení programu:

## Rozšíření programu:

Přidaný volitelný debugovací parametr `[-d]`.

Přidaný volitelný informační parametr `[-i]`, který např. ukazuje splnitelnost rozšířených vstupních podmínek (Diracova, Oreho, Pósova).

## Testování programu:

```
make test
bash ./tests/tests.sh "./hpac"
*** TEST 0.1 ***PASSED***! Launch params: -s A -e A, Expected return error code: 0
*** TEST 0.2 ***PASSED***! Launch params: -s E, Expected return error code: 1
*** TEST 1.1 ***PASSED***! Launch params: -s B -e H, Expected return error code: 0
*** TEST 1.2 ***PASSED***! Launch params: -s F -e O, Expected return error code: 0
*** TEST 1.3 ***PASSED***! Launch params: -s M -e L, Expected return error code: 0
*** TEST 2.1 ***PASSED***! Launch params: -s G -e H, Expected return error code: 0
*** TEST 2.2 ***PASSED***! Launch params: -s B -e A, Expected return error code: 0
*** TEST 2.3 ***PASSED***! Launch params: -s C -e B, Expected return error code: 0
```

## Odevzdané soubory:

```
xdrahn00
├── complexity
│   ├── brute_force_info.txt
│   └── theoretical_complexity.txt
├── doc
│   ├── hamilton_path_doc.pdf
│   └── Makefile
├── graphviz
│   ├── convert_script.py
│   └── README.md
├── Makefile
├── README.md
├── src
│   ├── error.h
│   ├── graph.c
│   ├── graph.h
│   ├── hpac.c
│   ├── hpac.h
│   ├── params.c
│   └── params.h
└── tests
    ├── graphs_in
    │   ├── 0.in
    │   ├── 1.in
    │   └── 2.in
    ├── params_in
    │   ├── 0.par
    │   ├── 1.par
    │   └── 2.par
    ├── ref_paths_out
    │   ├── 0.1.out
    │   ├── 0.2.rc
    │   ├── 1.1.out
    │   ├── 1.2.out
    │   ├── 1.3.out
    │   ├── 2.1.out
    │   ├── 2.2.out
    │   └── 2.3.out
    └── tests.sh

8 directories, 30 files
```
