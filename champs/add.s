.name "add"
.comment "just a basic add"
ldi 3, %4, r3
ld %2147483647, r5
ld %65, r4
add r4, r5, r5
st r5, 13
live %-1
live %-1
live %-2
live %-5
live %-2
live %-1
