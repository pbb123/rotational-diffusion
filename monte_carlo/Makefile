main: main.c Quaternion.c
	gcc -o main.out main.c Quaternion.c -lm
run: main.c Quaternion.c
	gcc -o main.out main.c Quaternion.c -lm & ./main.out
plot: main
	./main.out > out.txt & python3 plot.py
plot.show: plot
	open fig.png