c
array
pointer to arra
char
string


тип данных char
он обозначается через 'A'

char a='A';

а вот сунуть нескльько букв в одну переенменную уже недает. 
тоесть вот это неработает
char a = 'BBBaAAA' <==== НЕРАБОТАЕТ!
почему?
потому что тип char означает что под переменную выделяется ячейка размером 1 байт.
соотвествнно в 1 байт нельзя засунуть много байт!
Как же нам тогда создать multicharacter literal. А что такое multicharacter literal?
А вот что:

'a' is a character literal.
"abcd" is a string literal.
'abcd' is a multicharacter literal.

'a' is a char literal
"abcd" is a string literal
"a" is a string literal

ISO C90 вводит wide character type  wchar_t
чтобы он зараотал надо #include<wchar.h>

ISO C11 : wide character
value representable by an object of type wchar_t, capable of representing any character
in the current locale


		- что такое нахрен locale на практике?
		- рассмотреть что такое стринги