spreader.out : spreader.o spreaderRunner.o  
	g++ -ansi -Wall -g -o spreader.out spreader.o spreaderRunner.o  

spreader.o : spreader.cpp spreader.h
	g++ -ansi -Wall -c -g spreader.cpp

spreaderRunner.o : spreaderRunner.cpp CPUTimer.h spreaderRunner.h spreader.h Person.h
	g++ -ansi -Wall -c -g spreaderRunner.cpp

clean : 
	rm -f spreader.out spreader.o  spreaderRunner.o   
