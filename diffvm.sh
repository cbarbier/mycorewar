./corewar $1 -v 31 | head -n $2 > dino.txt
../corewar.zaz/corewar $1 -v 31 | head -n $2 > zaz.txt
diff -C 6 dino.txt zaz.txt
