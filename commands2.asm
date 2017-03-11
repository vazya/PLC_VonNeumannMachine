// код команды вида 01 23 34 56 78
// ячейки в моем контексте это строчки
// 01 - код команды
// 03 - номер ячейки для приемника
// 05 - номер ячейки для источника
// арифметика в аргументах запрещена
// первые 8 ячеек зарезервированы
// обратиться к ним можно но не стоит
// все на совести программиста
// затем идет выделение памяти с помощью ip
0 nothing  	// пустая строчка
			// в строчках 00 00 00 первые две ячейки
			// означают что в остальные 4 ячейки можно сохранить значение

1 ip 12		// сдвинуться на 12 строчек создает одну строчку 01 00 12
			// и 12 строчек 00 00 00
			// вид команды : 01 00 12

2 mov 3 5	// положить в третью ячейку значение из пятой ячейки
			// вид команды : 02 03 05
			
3 set 3 5	// положить в третью ячейку значение равное пяти
			// вид команды : 03 03 05

4 in 7		// предложить пользователю ввести значение
			// сохранить значение в седьмую ячейку 
			// вид команды : 04 00 07
			
5 out 7		// вывести значение на экран
			// из седьмой ячейки
			// вид команды : 05 00 07
			
6 inc 3		// инкрементировать значение в третьей ячейке
			// вид команды : 06 00 03
			
7 dec 4		// декрементировать значение в четвертой ячейке
			// вид команды : 07 00 04

8 add 3 2	// сложить значения из третьей и второй ячейки
			// и положить значение в третью ячейку
			// т.е. прибавить к третьей ячейке значение из второй
			// вид команды : 08 03 02
		
9 sub 3 4	// вычесть из третьей четвертое значение ячейкм
			// и положить значение в третью ячейку
			// вид команды : 09 03 04		
			
10 cmp 1 2	// сравнивает значения в первой и второй ячейке
			// если значения НЕравны переходит к выполнению строчки после cmp
			// иначе пропускает следующую строчку и выполняет 
			
11 jmp 7	// перескакивает на 7 строчку выполнения
			// нужно учитывать начальное смещение
			// вид команды : 11 00 07	

12 shu 3 	// shift up сдвинуться на три позиции вверх 
			// относительно текущей			
			// вид команды : 12 00 07	
			
13 shd 3 	// shift down сдвинуться на три позиции вниз 
			// относительно текущей						
			// вид команды : 13 00 07		

14 outc 5 	// вывести на экран пятый символ таблицы 
			// // вид команды : 14 00 05	
			
15 stop		//  конец программы - должен быть один на программу
			// вид команды : 15 00 00			
			
			
12 je 7	// перескакивает на 7 строчку выполнения
			// при выполненном условии
			// проверяет зарезервированное значение
			// вид команды : 12 00 07
			
13 jne 7	// перескакивает на 7 строчку выполнения
			// при невыполненном условии
			// проверяет зарезервированное значение
			// вид команды : 13 00 07
			
14 shu
15 shd
			
15 stop		// конец программы - должен быть один на программу
			// вид команды : 15 00 00

16 var a 7 	// выделить переменную а по адресу 7
			// в интерпретаторе везде а заменится на 7
			// нельзя использовать переменную до объявления
			// вид команды : 16 00 07
			
17			// в итоге в id** будет лежать строка в бинарнике
@label: ...	// указать что есть лейбл всегда с @
		...	// нельзя создать две функции с одним именем	
			// вид команды : 18 00 id** - где id - будет известен интерпретатору
18		ret	// после интерпретации все лейблы 
			// вид команды : 18 00 id** - где id - будет известен интерпретатору
			
		
19 call @label 	// после интерпретации все лейблы
				// превратятся в набор команд вызова некоторой функции
				// нельзя позвать функцию до ее объявления
				// перед использованием функции нужно сложить на стек все ее аргументы
				// вид команды : 19 ** id** 
				
20 push 16	// на вершину стека кладется значение из 16 строчки
			// вид команды : 20 00 16 
	
21 pop	17	// убирает верхнее значение и складывает его в ячейку 17
			// вид команды : 21 00 17
ip 8
set 1 1
set 2 2
mov 3 2
in 7
out 3
inc 4
dec 1
add 3 2
sub 3 4
stop

ip 8
set 1 1
set 2 1
set 3 0
add 3 1
add 3 2
mov 1 2
mov 2 3
set 3 0
add 3 1
add 3 2
mov 1 2
mov 2 3
out 3
stop
		
			
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

8 var a 7	// переменная значение которой хранится в седьмой ячейке
			// интерпретатор заменит везде переменную на ее номер ячейки
			// вид команды : 08 00 00 00 07
			
			
			
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
