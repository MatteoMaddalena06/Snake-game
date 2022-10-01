build:
	gcc -c src/main.c -g
	gcc -c src/snake.c -g
	gcc -c src/utils.c -g
	gcc -c src/queue.c -g
	gcc -c src/field.c -g
	gcc -o snake field.o queue.o utils.o snake.o main.o -lpthread 
	
	if [ ! -d obj ];then mkdir obj; fi
	
	for i in *.o;do mv $$i obj ;done 
	
clean:
	rm obj/*o
	rm snake
	rm -d obj
	
