dirstat: dirstat.c
	gcc dirstat.c -o dirstat.out
clean:
	rm *~
	rm dirstat.out
run: dirstat
	./dirstat.out
