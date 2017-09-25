./difftotal.sh ../corewar.zaz/champs/Gagnant.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/examples/zork.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/examples/bigzork.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/examples/turtle.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/examples/fluttershy.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/jumper.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/maxidef.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/ex.cor | wc -l >> res
./difftotal.sh ../corewar.zaz/champs/mortel.cor | wc -l >> res
./diffeasy.sh ../corewar.zaz/champs/examples/bee_gees.cor 500000 | wc -l >> res
./diffeasy.sh ../corewar.zaz/champs/car.cor 500000 | wc -l >> res
cat res
rm res
