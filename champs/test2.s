.name "zork"
.comment "just a basic living prog"
ld %1023, r5
l2: sti r1,%:live,%1
and r1,%0,r1
live: live %1
sti r5, %20, %10
zjmp %:live
