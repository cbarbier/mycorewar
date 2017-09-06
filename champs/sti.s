.name "sti"
.comment "just a basic store sti"
ld 1, r1
sti 3, %5, r1
fork %5
ld %10, r2
ld %-4, r3
ld %3, r4
st r2, 1
st r3, 1
st r4, 1
and -4, 2, r5
st r5, 10
live %-1
live %-2
