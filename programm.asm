ip 101
var a 41
set a 0
var b 42
set b 1
var c 43
set c 0
var n 44
outc 110
outc 32
outc 61
outc 32
in n
var cur 45
set cur 0
push a
push b
shd 17	
@fib:
	cmp n cur
	jmp 134 122
	var t 23
	pop t
	add c t
	pop t
	add c t
	mov a b
	mov b c
	set c 0
	inc cur
	push a
	push b
	call @fib
	ret
call @fib
outc 114
outc 101
outc 115
outc 32
outc 61
outc 32
out a
stop
