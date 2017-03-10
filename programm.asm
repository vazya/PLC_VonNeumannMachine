ip 5
set 12 777
@printRes:
	outc 114
	outc 101
	outc 115
	outc 32
	outc 61
	outc 32
	out 12
	ret
call @printRes	
set 12 666
call @printRes
stop
