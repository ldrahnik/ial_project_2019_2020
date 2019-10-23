# Ukázka spuštění (manuálně z příkazové řádky)

- `./hpac -h` # nápověda
- `./hpac 'A B '$'\n'' B D '$'\n'' D E' -s A -e E` # inline zápis malého grafu
- `./hpac ./tests/graphs_in/2.in -e B -s H` # spuštění na grafu načteného ze souboru
- `./hpac ./tests/graphs_in/2.in -e B -s H -d -i` # s debugovacími zprávami posílanými na stderr [ -d] a informacemi o algoritmu po provedení (např. počet rekurzivního zavolání) [ -i]

# Ukázka spuštění (zautomatizované testy)

 - `make test` # provedení všech testů s předpřipravenými grafy

# Zautomatizované testy

- Jeden vstupní graf odpovídá jednomu vstupnímu souboru ve složce `tests/graphs_in`.
- Každý soubor ve složce `tests/params_in` odpovídá jednomu grafu a obsahuje oděleně po řádcích různé sady spouštěcích parametrů.
- Referenční výstup je ve složce `tests/ref_paths_out`. V referenčním výstupu se vždy nachází právě jedna Hamiltonova cesta / cyklus. Pokud se nachází i ve výstupu programu, test prošel.
- Příkazem `make test` v kořenovém adresáři dojde ke spuštění programu se všemi dostupnými grafy (`tests/graphs_in`) a postupně se všemi jejich parametry (`tests/params_in`) a uložení jejich výstupu do `tests/output`.
- Pokud je očekávaný návratový kód u testovací varianty grafu (tedy např. graf 1 s 2. sadou parametrů -> 1.2) různý od nuly, je vytvořen referenční soubor s návratovým kódem ve složce (`./tests/ref_paths_out`) ve tvaru `graf.číslo_řádku_sady_parametrů.rc` (tedy např. `1.2.rc` kde se použije sada parametrů z druhého řádku) a s obsahem souboru bude na prvním řádku očekávaný návratový kód.

# Ukázka vygenerování obrázků s grafy pomocí knihovny (graphviz)[https://graphviz.gitlab.io/]

Převedení vstupního souboru programu s grafem `*.in` pomocí jednoduchého python scriptu na požadovaný formát `.dot` (graph description language) a poté jeho převedení na obrázek `*.png`.

```
python3 ./graphviz/convert_script.py ./time_coplexity/graphs/5v.in # dojde k vytvoření souboru 5v.dot na stejném místě
dot -Tpng ./time_coplexity/graphs/5v.dot > ./../time_coplexity/graphs/5v.png
```
