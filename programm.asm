ip 5
set 5 0
set 6 1
set 7 2
set 12 0
outc 110
outc 32
outc 61
outc 32
in 13
cmp 13 5
shd 3
out 5
shd 28
cmp 13 6
shd 3
out 6
shd 24
cmp 13 7
shd 3
out 6
shd 20
dec 13
dec 13
set 14 1
set 15 1
set 16 0
add 16 14
add 16 15
mov 14 15
mov 15 16
dec 13
cmp 12 13
shu 7
outc 114
outc 101
outc 115
outc 32
outc 61
outc 32
out 16
stop
