//-----------------------------------------------------------------------------
//        Asignatura INFORMATICA INDUSTRIAL
//        Grado en Ingenieria Electronica Industrial y Automatica
//        Escuela de Ingenierias Industriales. Universidad de Valladolid
//-----------------------------------------------------------------------------
//  Aponte Rengifo oscar emilio
//
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Compilar:    g++  valvula.cpp colamsg.cpp memocomp.cpp semaforo.cpp  -o valvula -lpthread -lrt
//-----------------------------------------------------------------------------


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include "colamsg.hpp"
#include "semaforo.hpp"
#include "memocomp.hpp"

#define TAMCADVALV 10
#define CADB 2
///////////--------------------------------

using namespace std;

int main(void)
{
    int valv_num;
    char cadvalv[TAMCADVALV];

    ///////////////////////-----------------MEMOCOMPARTIDA:DEPOSITO/VALVULA--------------

    int *estado;    // puntero a estado en memo compartida
    semaforo s2("Estado"); // abrimos semaforo
    memocomp memoEstado("memoEstado", OPEN, RDWR, sizeof(int));
    estado = (int *)memoEstado.getPointer(); //vinculamos esta memo a un puntero

   ///////////////////////-----------------------------------------------------------------

   ////-------------------GETPID VALVULA: ENVIA PID A CONTROL--------------------------------------

   int pidv;
   pidv=getpid();

   cout<<"el pid de valvula es: "<<pidv<<endl;

   colamsg colavalvula("colaV",OPEN,WRONLY);

   sprintf(cadvalv,"%d",pidv);

   colavalvula.send(cadvalv,TAMCADVALV*sizeof(char));
   colavalvula.close();
   cout<<"el valor de pid enviado"<<cadvalv<<endl;

////////////////////////---------------------------------------------------------------------

    while(true)
    {

///////////-------------COLA:CONTROL/VALVULA-----------------------------------------------

      colamsg colavalvula("colaV",OPEN,RDONLY); // abrimos cola de lectura

      colavalvula.receive(cadvalv,TAMCADVALV*sizeof(char)); // cola recivida desde control

      valv_num=atoi(cadvalv);


/////////////------MEMOCOMPORATIDA:DEPOSITO/VALVULA-----------------------------------------
            *estado=valv_num;
            if (*estado==1)
                cout<<"Valvula abierta"<<endl;
            else
                cout<<"Valvula cerrada"<<endl;
           s2.up();    //da paso al estado. Ya está disponible el estado en memo

    }

}
