//-----------------------------------------------------------------------------
//        Asignatura INFORMATICA INDUSTRIAL
//        Grado en Ingenieria Electronica Industrial y Automatica
//        Escuela de Ingenierias Industriales. Universidad de Valladolid
//-----------------------------------------------------------------------------
//   Aponte Reengifo oscar emilio
//
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Compilar:    g++  deposito.cpp colamsg.cpp memocomp.cpp semaforo.cpp  -o deposito -lpthread -lrt
//-----------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "semaforo.hpp"
#include "memocomp.hpp"
#include "colamsg.hpp"
#define  DEP 10
using namespace std;

int main(int argc,char *argv[])
{
//////////-------------GET PID DEP:ENVIA PID A CONTROL---------------
  char caddep[DEP];
  int pidd;
  pidd=getpid();


  cout<<"el pid  del deposito es "<<pidd<<endl;
  sprintf(caddep,"%d",pidd);

  colamsg coladep("colaD",OPEN,WRONLY);
  coladep.send(caddep,DEP*sizeof(char));
  cout<<"el pid enviado  en cadena es: "<<caddep<<endl;
  coladep.close();

////////--------------------------------------------------------------

///////-----------------ARGUMENTOS-----------------------------------

   int abierto1,abierto2,cerrado;

   abierto1=atoi(argv[1]);
   cerrado=atoi(argv[2]);

   abierto2=abierto1-cerrado;

   if (argc!=3)
   {
   cout<<"error al introducir valores"<<endl;
   return(-1);
   }
   if (argc==1)
   {
       abierto2=300;
       cerrado=100;
   }

/*   cout<<"valor de abierto y cerrado "<<abierto2<<"  "<<cerrado<<endl;
*/



    /////////////------------------------MEMOCOMP:DEPOSITO/SENSOR--------------------------------
    int *nivel;    // puntero a la nivel en memo compartida

    semaforo s1("Nivel", 0); // Creamos s1 inicializado a 0
    //creamos una zona de memo compartida de lect escrit y tamaño (sizeof int)
    memocomp memoNivel("memoNivel", CREAT, RDWR, sizeof(int));
    nivel = (int *)memoNivel.getPointer(); //vinculamos esta memo a un puntero

    ////////////---------------------------------------------------------------------------------

    ///////////--------------------------MEMOCOMP:DEPOSITO/VALVULA--------------------------------
    int *estado;

    semaforo s3("Estado",1); // se crea semaforo en 1
    //creamos una zona de memo compartida de lect escrit y tamaño (sizeof int)
    memocomp memoEstado("memoEstado", CREAT, RDWR, sizeof(int));
    estado = (int *)memoEstado.getPointer(); //vinculamos esta memo a un puntero


    ////////////////-------------------WHILE------------------------------------------


    *nivel=0;// Condición inicial: nivel a cero

    while(true)
    {



    ///////---------------MEMOCOMP---------------------------
        s3.down();//espera a que valvula escriba estado
        cout << "ha llegado: " << *estado << endl;

    //////---------------------------------------------------

    /////-----------FUNCIONAMIETO DEL DEPOSITO:LLENADO-VACIADO

        if(*estado==1)
        {
            *nivel+=abierto2;

        }
         else
         {
            *nivel-=cerrado;

         }

      /////-----memocomp

         cout << "El nivel es de: " << *nivel <<" Litros"<< endl;
         s1.up();

sleep(1);


    }
memoEstado.cerrar();
memoEstado.unlink();

s1.close();
s1.unlink();


}



