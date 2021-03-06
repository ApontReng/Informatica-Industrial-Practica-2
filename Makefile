#Makefile para la compilacion de los prog control deposito sensor valvula con colas,memocomp y semaforos
#Limpia tambien los semaforos 
#Makefile para la compilacion de los prog control deposito sensor valvula con colas,memocomp y semaforos
#Limpia tambien los semaforos 

todo: control deposito sensor valvula

control: control.o colamsg.o 
	g++ control.o colamsg.o -o control -lrt 
     
deposito: deposito.o colamsg.o memocomp.o semaforo.o
	g++ deposito.o colamsg.o memocomp.o semaforo.o -o deposito -lrt -lpthread
        
sensor: sensor.o colamsg.o memocomp.o semaforo.o
	g++ sensor.o colamsg.o memocomp.o semaforo.o -o sensor -lrt -lpthread
           
valvula: valvula.o colamsg.o memocomp.o semaforo.o
	g++ valvula.o colamsg.o memocomp.o semaforo.o -o valvula -lrt -lpthread
              
control.o: control.cpp colamsg.hpp
	g++ -c control.cpp
                   
deposito.o: deposito.cpp colamsg.hpp memocomp.hpp semaforo.hpp
	g++ -c deposito.cpp
                        
valvula.o: valvula.cpp colamsg.hpp memocomp.hpp semaforo.hpp
	g++ -c valvula.cpp
                             
sensor.o: sensor.cpp colamsg.hpp memocomp.hpp semaforo.hpp
	g++ -c sensor.cpp
                                  
colamsg.o: colamsg.cpp colamsg.hpp
	g++ -c colamsg.cpp
                                            
memocomp.o: memocomp.cpp memocomp.hpp
	g++ -c memocomp.cpp
                                                      
semaforo.o: semaforo.cpp semaforo.hpp
	g++ -c semaforo.cpp