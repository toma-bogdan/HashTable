build: 
	gcc lista.c f-thash.c tema1.c -o tema1 -Wall
run:
	./tema1 10 hash.in hash.out
clean:
	rm -rf tema1