# Vstupní soubory & testování

- jeden vstupní graf odpovídá jednomu vstupnímu souboru
- každý soubor ve složce tests/params_in odpovídá jednomu grafu a obsahuje po řádcích různé sady spouštěcích parametrů
- pro zjednodušení práce jsou hrany ve vstupním souboru jsou řazeny VŽDY podle abecedy, podle abecedy jsou i řazeny vrcholy jednotlivých hran. Totéž samozřejmě platí u referenčního výstupu a tedy i očekávaného výstupu programu.
- všechny testovací grafy jsou umístěny ve složce tests/graphs_in, jejich referenční výstup ve složce tests/ref_paths_out
- příkazem "make test" v kořenovém adresáři dojde ke spuštění programu se všemi dostupnými grafy (tests/graphs_in) a postupně se všemi jejich parametry (tests/params_in), uložení jejich výstupu do tests/output. V referenčním výstupu se vždy nachází právě jedna Hamiltonova cesta. Pokud je tato cesta nalezena v množině identifikovaných Hamiltonových cest ve výstupu programu, test končí úspěchem.
- pokud je očekávaný návratový kód u dané varianty grafu (tedy např. graf 1 s 2. sadou parametrů -> 1.2) různý od nuly, je třeba vytvořit referenční soubor s návratovým kódem ve složce (./tests/ref_paths_out) ve tvaru graf.parametry.rc (tedy např. 1.2.rc), kde obsahem souboru bude na prvním řádku očekávaný návratový kód

# Vstupní podmínky (základní)

1. graf musí mít větší počet uzlů než 2

2. graf musí mít počet hran pro každý uzel

      1. pro cestu alespoň 1 hranu

      2. pro kruh alespoň 2 hrany

# Vstupní podmínky (rozšířené)

1. pokud platí Diracova podmínka nebo Oreho podmínka nebo Pósova podmínka tak je graf Hamiltonovský
      1. Každý uzel má stupeň alespoň ½ u. (Diracova podmínka)
      2. Každá dvojice uzlů nespojených hranou má součet stupňů alespoň u. (Oreho podmínka)
      3.  Pro každé přirozené číslo k < ½ u je počet uzlů, jejichž stupeň nepřevyšuje k, menší než k. (Pósova podmínka)
      
# Ukázka spuštění (manuálně z příkazové řádky)

- `./hpac -h` # nápověda
- `./hpac 'A B '$'\n'' B D '$'\n'' D E' -s A -e E` # inline zápis malého grafu
- `./hpac ./tests/graphs_in/2.in -e B -s H` # spuštění na grafu načteného ze souboru
- `./hpac ./tests/graphs_in/2.in -e B -s H -d -i` # s debugovacími zprávami posílanými na stderr [ -d] a informacemi o algoritmu po provedení (např. počet rekurzivního zavolání) [ -i]

# Ukázka spuštění (zautomatizované testy)

 - `make test` # provedení všech testů na předpřipravených grafech viz. `Automatizované testy`

# Zautomatizované testy

- Jeden vstupní graf odpovídá jednomu vstupnímu souboru ve složce `tests/graphs_in`.
- Každý soubor ve složce `tests/params_in` odpovídá jednomu grafu a obsahuje oděleně po řádcích různé sady spouštěcích parametrů.
- Referenční výstup je ve složce `tests/ref_paths_out`. V referenčním výstupu se vždy nachází právě jedna Hamiltonova cesta / cyklus. Pokud se nachází i ve výstupu programu, test prošel.
- Příkazem `make test` v kořenovém adresáři dojde ke spuštění programu se všemi dostupnými grafy (`tests/graphs_in`) a postupně se všemi jejich parametry (`tests/params_in`) a uložení jejich výstupu do `tests/output`.
- Pokud je očekávaný návratový kód u dané varianty grafu (tedy např. graf 1 s 2. sadou parametrů -> 1.2) různý od nuly, je vytvořen referenční soubor s návratovým kódem ve složce (`./tests/ref_paths_out`) ve tvaru `graf.číslo_řádku_s_parametry.rc` (tedy např. `1.2.rc`), kde obsahem souboru bude na prvním řádku očekávaný návratový kód.
