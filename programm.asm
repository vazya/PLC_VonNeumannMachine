ip 5
var a 18
set a 777
shd 10
@printRes:
	outc 114
	outc 101
	outc 115
	outc 32
	outc 61
	outc 32
	out a
	ret
call @printRes	
set a 666
call @printRes
stop
