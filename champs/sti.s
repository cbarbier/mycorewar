.name "sti"
.comment "just a basic store sti"
ld %10, r2
ld -4, r3
ld %3, r4
st r2, 1
st r3, 1
st r4, 1
sti r2, %3, r4
