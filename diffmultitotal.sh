./corewar $1 $2 -v 31 > dino.txt
../corewar.zaz/corewar $1 $2 -v 31 > zaz.txt
diff -C 5 dino.txt zaz.txt
rm dino.txt
rm zaz.txt
