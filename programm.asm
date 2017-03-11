ip 7
var a 18
var b 19
set a 7
set b 6
push a
push b
shd 15
@sum:
	outc 114
	outc 101
	outc 115
	outc 32
	outc 61
	outc 32
	var c 20
	var d 21
	pop c
	pop d
	add c d
	out c
	ret
call @sum
stop
