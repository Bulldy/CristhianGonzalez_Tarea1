ek_1proc.pdf:data.py proc1.txt proc2.txt proc4.txt
	python data.py
t_proc.pdf:time.py time1.txt time2.txt time4.txt
	python time.py
proc1.txt:a.out
	./a.out 1
proc2.txt:a.out
	./a.out 2
proc4.txt:a.out
	./a.out 4
a.out:fput.c
	gcc fopenmp fput.c -lm
clean:
	rm -f a.out time1.txt time2.txt time4.txt proc1.txt proc2.txt proc4.txt

