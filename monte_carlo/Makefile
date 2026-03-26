main: main.c Quaternion.c Particle.c sim.c
	gcc -o main.out main.c Quaternion.c Particle.c sim.c -lm
run: main
	./main.out
plot: main
	./main.out > out.txt & python3 plot.py
plot.show: plot
	open fig.png