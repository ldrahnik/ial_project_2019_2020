## Vygenerování obrázků s grafy (pomocí knihovny [graphviz](https://graphviz.gitlab.io/))

Převedení vstupního souboru programu s grafem `*.in` pomocí jednoduchého python scriptu na požadovaný formát `.dot` (graph description language) a poté jeho převedení na obrázek `*.png`.

```
python3 ./graphviz/convert_script.py ./complexity/graphs/5v.in # dojde k vytvoření souboru 5v.dot na stejném místě
dot -Tpng ./complexity/graphs/5v.dot > ./../complexity/graphs/5v.png
```
