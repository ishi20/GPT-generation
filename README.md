# GPT-generation

Input menu.dat
one
	oneone
	onetwo
		onetwothree
	onethree
two
	aaa
		xxx
			zzz
		yyy
	bbb
	ccc
three
	abc
	pqr
		ppp
			qqq
	rrr
four
five

Run commands
gcc A1_PES1201701142.c -o codegen
./codegen <menu.dat >outputprog.c

Which will generate c code based on the input given

Run the generated code which is in the form of nested switch cases 
It will give you the output based on the menu options you specify
