//-----------------------------------------------------------------------------
//        Asignatura INFORMATICA INDUSTRIAL
//        Grado en Ingenieria Electronica Industrial y Automatica
//        Escuela de Ingenierias Industriales. Universidad de Valladolid
//-----------------------------------------------------------------------------
//     Aponte Rengifo oscar emilio
//
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Compilar: g++  sensor.cpp colamsg.cpp memocomp.cpp semaforo.cpp  -o sensor -lpthread -lrt
//-----------------------------------------------------------------------------



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include "semaforo.hpp"
#include "memocomp.hpp"
#include "colamsg.hpp"

#define TAMCAD 10


using namespace std;

int main()
{

 int k;
 char cadsensor[TAMCAD];
///////////////////////-------------------MEMOCOMPARTIDA:DEPOSITO/SENSOR------------

    int *nivel;    // puntero a la nivel en memo compartida
    semaforo s("Nivel"); // abrimos s
    memocomp memoNivel("memoNivel", OPEN, RDWR, sizeof(int));
    nivel = (int *)memoNivel.getPointer(); //vinculamos esta memo a un puntero

///////////////////////--------------------------------------------------------------

////////////////////////-----------------GETPID SENSOR:ENVIA PID A CONTROL------------------

  int pids;
  pids=getpid();


  cout<<"el pid es "<<pids<<endl;
  sprintf(cadsensor,"%d",pids);

  colamsg colasens("colaS",OPEN,WRONLY);
  colasens.send(cadsensor,TAMCAD*sizeof(char));
/*  cout<<"el pid enviado es en cadena es: "<<cadsensor<<endl; */
  colasens.close();
//////////////////////////-------------------------------------------


    while(true)
    {
        ///////////////--------------MEMOCOMP/SENSOR: lee nivel - vizualiza nivel------------

        s.down();//espera a que deposito escriba nivel
        cout << "ha llegado: " << *nivel << endl;

        k=*nivel;
        //////////////------------------------------------------------------------------------

        //////////////--------------CONTROL/SENSOR---------------------------------------------

        colamsg colasensor("colaS", OPEN , WRONLY);

          sprintf(cadsensor,"%d",k);

          colasensor.send(cadsensor,TAMCAD*sizeof(char));

       ////////////////////////////////////////////////------------------------------------------

    }

}


