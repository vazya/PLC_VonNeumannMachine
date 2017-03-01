mov eax, ebx
mov eax, 3
label:
	ret
jmp label + 2
call label
in eax // код команды ввода eax
out eax // код команды вывода eax
out [eax] // код команды вывода значения по адресу eax
add eax, ebx // eax = eax + ebx
sub eax, ebx // eax = eax - ebx
inc eax // eax = eax + 1
dec eax // eax = eax - 1
ip 3 // перейти на строчку 3
stop // конец
[00] : IP = 12 // указатель на текущую команду
[04] : AX = 0  // переменная
[08] : INP = 12 // пользовательская переменная ввода	