ip 5
var a 1
var b 2
var c 3
set a 11
set b 22
set c 33
out a
out b
out c
mov c b
out a
out b
out c
stop

@label:
	set 1 22
	ret
	
	
	
call label	