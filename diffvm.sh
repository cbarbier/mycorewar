./corewar $1 -v 29 | head -n $2 > dino.txt
../cw/zaz/corewar $1 -v 29 | head -n $2 > zaz.txt
diff -C 3 dino.txt zaz.txt
