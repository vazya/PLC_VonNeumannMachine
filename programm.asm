ip 5
set 5 0
set 6 1
set 7 2
set 12 0
in 13
cmp 13 5
jmp 25
out 5
cmp 13 6
jmp 28
out 6
cmp 13 7
jmp 31
out 6
set 14 1
set 15 1
set 16 0
add 16 14
add 16 15
mov 14 15
mov 15 16
dec 13
cmp 12 13
jmp 33
out 16
stop
