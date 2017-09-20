./corewar ../cw/zaz/champs/Gagnant.cor -v 29 | head -n $1 > dino.txt
../cw/zaz/corewar ../cw/zaz/champs/Gagnant.cor -v 29 | head -n $1 > zaz.txt
diff dino.txt zaz.txt
