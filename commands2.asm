// код команды вида 01 23 34 56 78
// 01 - код в ячейка для кода команды
// 23 34 - номер ячейки для приемника
// 56 78 - номер ячейки для источника
// арифметика в аргументах запрещены
0 nothing  	// пустая строчка
			// в строчках 00 00 00 00 00 первые две ячейки
			// означают что в остальные 4 ячейки можно сохранить значение

1 ip 12		// сдвинуться на 12 строчек создает одну строчку 01 00 00 12
			// и 12 строчек 00 00 00 00 

2 mov 3 5	// положить в третью ячейку значение из пятой ячейки
			
3 set 3 5	// положить в третью ячейку значение равное пяти

4 in 7		// предложить пользователю ввести значение
			// сохранить значение в седьмую ячейку 
			// вид команды : 04 00 00 00 07
			
5 out 7		// вывести значение на экран
			// из седьмой ячейки
			// вид команды : 05 00 00 00 07
			
6 inc 3		// инкрементировать значение в третьей ячейке
			// вид команды : 06 00 00 00 03
			
7 dec 4		// декрементировать значение в четвертой ячейке
			// вид команды : 07 00 00 00 04

	
[00] 0 nothing  // пустая строчка
[01] 1 ip 12// сдвинуться на 12 строчек создает одну строчку 01 00 00 12
			// и 12 строчек 00 00 00 00 
			// арифметика в аргументе запрещена
[02] 2 mov 3 5 // положить в 3 строчку на стеке значение 5
	   mov 
[03] 3 in // код команды ввода eax
[04] 4 out // код команды вывода eax
[05] 5 inc eax // eax = eax + 1
[06] 6 dec eax // eax = eax - 1
[07] 7 jmp
[08] 8 call
[09] 9 ret
[0A] 10 label
[0B] 11
[0C] 12
[0D] 13
[0E] 14
[0F] 15 stop  // конец программы
 
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

[01] ip x- перейти на строку с номером x
[02] inp x - считать число с клавиатуры записать по адресу х
[03] dec a - из числа по адресу а - вычесть 1
[04] push a - положить на вершину стеку значение по адресу а
[05] pop a - снять с вершины стека значение, записать его в а
[06] cmp a b - сравнить a и b по значению
[07] cjump х - если пред сравнение true то прыгнуть на х иначе ничего не делать
[08] add a b - сложить значения а и b результат записать в а
[09] move x - перейти по адресу х
[0a] ret - снять с вершины стека значение и перейти в ячейку с таким адресом
[0b] copy a b - записать по адресу а значение из b
[0c] out x - вывести значение по адресу х на экран
[0d] stop - завершить исполнение работы