//-----------------------------------------------------------------------------
//        Asignatura INFORMATICA INDUSTRIAL
//        Grado en Ingenieria Electronica Industrial y Automatica
//        Escuela de Ingenierias Industriales. Universidad de Valladolid
//-----------------------------------------------------------------------------
//   Aponte Rengifo oscar emilio
//
//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
//Compilar:    g++  control.cpp colamsg.cpp -o control -lrt
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include "colamsg.hpp"
#define TAMCADSENS 10
#define TAMCADVALV 10
#define CADB 2
#define DEP 10
#include <signal.h>

using namespace std;

////////////////-------Función : TERMINA PROCESOS

void senial_limp(int);

////////////////--------------Declaración de Colas-----------------------

colamsg colasens("colaS",CREAT,RDONLY,TAMCADSENS*sizeof(char));

colamsg colavalv("colaV",CREAT,RDWR,TAMCADVALV*sizeof(char));

colamsg coladeposito("colaD",CREAT,RDONLY,DEP*sizeof(char));

////----COLA que recibe PID de Depósito
 char caddeposito[DEP];

 int pidv;

 int pids;

 int pidd;

///////////////------------------------------------------


int main (int argc,char *argv[])
{


   int sensor_num; // entero que almacenar los los caracteres convertidos con el atoi
   char cadenavalv[TAMCADVALV];// Cadena de Cola valvula
   char cadsensor[TAMCADSENS];// Cadena de Cola sensor
///////////////////////////////////////-----------RECIBE PIDS:-------------

////---------PID'S VALVULA
  colavalv.receive(cadenavalv,TAMCADVALV*sizeof(char));
   pidv=atoi(cadenavalv);
   cout<<"el pid de valvula: "<<pidv<<endl;

////----------PID'S SENSOR
  colasens.receive(cadsensor,TAMCADSENS*sizeof(char));
  pids=atoi(cadsensor);
    cout<<"el pid de sensor: "<<pids<<endl;

////----------PID'S DEPOSITO
coladeposito.receive(caddeposito,DEP*sizeof(char));
   pidd=atoi(caddeposito);
   cout<<"el pid de deposito: "<<pidd<<endl;


///////////////////////////////////////----------ARGUMENTOS-----------------
int MAX,MIN;

MIN=atoi(argv[1]);
MAX=atoi(argv[2]);

if (argc!=3)
{
cout<<"error al introducir valores"<<endl;
return(-1);
}
if (argc==1)
{
    MIN=1500;
    MAX=4500;
}
cout<<"valor maximo - minimo"<<MIN<<"  "<<MAX<<endl;

////----------------------------------------------------------------------



while (true)

{

///////////--------------------COLA:CONTROL/SENSOR------------------------

                  colamsg colasens("colaS",OPEN,RDONLY);

                  colasens.receive(cadsensor,TAMCADSENS*sizeof(char));// cola recivida desde el sensor

                  sensor_num=atoi(cadsensor);

                  cout<<"Lectura del sensor " << sensor_num << endl;


///////////////////--------------------------------------------



    if (sensor_num<MIN)
       {

         cadenavalv[0]='1';
         cadenavalv[1]=0;

       }

    else if(sensor_num>MAX)
     {

         cadenavalv[0]='0';
         cadenavalv[1]=0;

     }

       cout<<"el valor del estado enviado es:  "<<endl;
      colavalv.send(cadenavalv,TAMCADVALV*sizeof(char));

////////////------------------------SEÑAL:TERMINA PROCESOS/IPCS

    signal(SIGINT,senial_limp);

  }

}


void senial_limp(int senial)


{


cout<<"senial cola sensor: borra ipc\n";
colasens.close();
colasens.unlink();

cout<<"senial cola valvula:borra ipc\n";
colavalv.close();
colavalv.unlink();

cout<<"senial cola deposito:borra ipc\n ";
coladeposito.close();
coladeposito.unlink();

sleep(3);

kill(pids,SIGINT);
kill(pidv,SIGINT);
kill(pidd,SIGINT);





exit(0);

}

