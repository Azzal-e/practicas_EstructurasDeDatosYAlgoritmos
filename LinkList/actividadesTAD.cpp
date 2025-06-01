/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 3
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 11-11-2023
 * Resumen: Fichero con la implementación de las operaciones del TAD actividad.
\*********************************************************************************************/

#include <iostream>
#include "actividadesTAD.hpp"
using namespace std;

// IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD ACTIVIDAD

/* Crea un dato actividad a inicializándolo con el nombre y descripción dados, y con el número
   indicado tEst como el número de minutos estimado a dedicar a la actividad.
*/
void crearActividad(const string nom,const string des ,const unsigned tEst, actividad& a){
    a.nombre = nom;
    a.descripcion = des;
    a.tEstimado = tEst;
}

/* Devuelve el nombre de la actividad a.
*/
string obtenerNombre(const actividad& a){
    return a.nombre;
}

/* Devuelve la descripción de la actividad a.
*/
string obtenerDescripcion(const actividad& a){
    return a.descripcion;
}

/* Devuelve el número de minutos estimado para la realización de la actividad a.
*/
unsigned obtenerTiempoEstimado(const actividad& a){
    return a.tEstimado;
}