./corewar $1 -v 31 > dino.txt
../corewar.zaz/corewar $1 -v 31 > zaz.txt
diff dino.txt zaz.txt
rm dino.txt
rm zaz.txt
