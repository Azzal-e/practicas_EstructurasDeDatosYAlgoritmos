/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 4
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 11-11-2023
 * Resumen: Fichero de encabezado con la declaración del TAD periodo.
\*********************************************************************************************/

#ifndef PERIODOSTAD_HPP
#define PERIODOSTAD_HPP

#include "instantesTAD.hpp"

// Predeclaración del TAD periodo

/* Los valores del TAD representan periodos de tiempo
   cronológicamente correctos y finalizados. Es decir, valores que incluyen siempre un instante de
   tiempo como inicio del periodo y un instante de tiempo final del periodo cronológicamente válido,
   es decir, igual o posterior al instante de inicio del periodo. Las fechas de los instantes de
  inicio y final podrán ser distintas, pero deberán corresponder al mismo año y mes.
*/
struct periodo;

/* Si los instantes i y f no pueden constituir un periodo cronológicamente correcto, es decir, el instante f es anterior 
*  al instante i, o bien no pertenecen al mismo año y mes, se devuelve falso.
*  En caso contrario, se devuelve verdadero y se crea un tipo de dato periodo p inicializándolo con i como
*  instante inicial y f como instante final.
*/
bool crearPeriodo(const instante& i, const instante& f, periodo& p);

/* Dado un periodo p, devuelve el instante de tiempo inicial del periodo.
*/
instante obtenerInicio(const periodo& p);

/* Dado un periodo p, devuelve el instante de tiempo final del periodo.
*/
instante obtenerFinal(const periodo& p);

/* Dado un periodo p, devuelve el número de minutos transcurridos desde el instante de tiempo inicio
   del periodo, hasta su instante final.
*/
unsigned obtenerDuracion(const periodo& p);

/* Dado un periodo p1 y un periodo p2, devuelve verdad si y solo si ambos periodos tienen instantes
   de inicio iguales, y también tienen instantes de final iguales.
*/
bool operator==(const periodo& p1, const periodo& p2);

/* Dado un periodo p1 y un periodo p2, devuelve verdad si y solo si el instante de inicio del
   periodo p1 es estricta y cronológicamente anterior al instante de inicio del periodo p2, o si
   sus instantes de inicio son iguales pero el instante de final del periodo p1 es estricta y
   cronológicamente anterior al instante de final del periodo p2.
*/
bool anterior(const periodo& p1, const periodo& p2);

/* Dado un periodo p1 y un periodo p2, devuelve verdad si y solo si ambos periodos de tiempo se
   solapan: ambos periodos son iguales o, incluyen instantes de tiempo en común distintos de los
   respectivos inicio y final (es decir, la intersección de los periodos como intervalos abiertos
   no es vacía, si el inicio de un periodo es igual al final del otro periodo no hay solape).
*/
bool solapados(const periodo& p1, const periodo& p2);


// Declaración del TAD periodo

struct periodo{
    friend bool crearPeriodo(const instante& i, const instante& f, periodo& p);
    friend instante obtenerInicio(const periodo& p);
    friend instante obtenerFinal(const periodo& p);
    friend unsigned obtenerDuracion(const periodo& p);
    friend bool operator==(const periodo& p1, const periodo& p2);
    friend bool anterior(const periodo& p1, const periodo& p2);
    friend bool solapados(const periodo& p1, const periodo& p2);

    private:
    /* Internamente, un periodo se define por la agrupación de dos datos de tipo
       instante, uno representando el inicio y otro el final del periodo.
    */
     instante inicio, final;

};

#endif