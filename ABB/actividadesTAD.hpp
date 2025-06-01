/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 4
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 11-11-2023
 * Resumen: Fichero de encabezado con la declaración del TAD actividad.
\*********************************************************************************************/

#ifndef ACTIVIDADESTAD_HPP
#define ACTIVIDADESTAD_HPP

#include <iostream>
using namespace std;

// PREDECLARACIÓN DEL TAD ACTIVIDAD

/* Los valores del TAD representan actividades, tales que tendrán
  un nombre, una descripción y una cantidad de minutos que se estima que será necesario dedicar para
  su realización.
*/
struct actividad;

/* Crea un dato actividad a inicializándolo con el nombre y descripción dados, y con el número
   indicado tEst como el número de minutos estimado a dedicar a la actividad.
*/
void crearActividad(const string nom,const string des ,const unsigned tEst, actividad& a);

/* Devuelve el nombre de la actividad a.
*/
string obtenerNombre(const actividad& a);

/* Devuelve la descripción de la actividad a.
*/
string obtenerDescripcion(const actividad& a);

/* Devuelve el número de minutos estimado para la realización de la actividad a.
*/
unsigned obtenerTiempoEstimado(const actividad& a);

// DECLARACIÓN DEL TAD ACTIVIDAD

struct actividad{
    friend void crearActividad(const string nom,const string des ,const unsigned tEst, actividad& a);
    friend string obtenerNombre(const actividad& a);
    friend string obtenerDescripcion(const actividad& a);
    friend unsigned obtenerTiempoEstimado(const actividad& a);

    private: 
    /* Internamente una actividad se declará como una agrupación de tres componentes:
      dos cadenas de carácteres representando el nombre y descripción de la actividad y un
      natural simbolizando su tiempo estimado de ejecución
    */
     string nombre, descripcion;
     unsigned tEstimado;
};

#endif