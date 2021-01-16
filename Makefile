
compile:
	gcc test.c -o test.out

run: compile
	./test.out

clean:
	rm *.out 
