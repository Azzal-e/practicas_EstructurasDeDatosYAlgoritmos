/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 4
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 27-11-2023
 * Resumen: Fichero de implementación de las operaciones del TAD periodo.
\*********************************************************************************************/

#include <iostream>
#include "periodosTAD.hpp"
using namespace std;

//IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD PERIODO

/* Si los instantes i y f no pueden constituir un periodo cronológicamente correcto, es decir, el instante f es anterior 
*  al instante i, o bien no pertenecen al mismo año y mes, se devuelve falso.
*  En caso contrario, se devuelve verdadero y se crea un tipo de dato periodo p inicializándolo con i como
*  instante inicial y f como instante final.
*/
bool crearPeriodo(const instante& i, const instante& f, periodo& p){
    if(!posterior(i, f) && agno(i) == agno(f) && mes(i) == mes(f)){
        p.inicio = i;
        p.final = f;
        return true;
    }
    else{
        return false;
    }
}

/* Dado un periodo p, devuelve el instante de tiempo inicial del periodo.
*/
instante obtenerInicio(const periodo& p){
    return p.inicio;
}

/* Dado un periodo p, devuelve el instante de tiempo final del periodo.
*/
instante obtenerFinal(const periodo& p){
    return p.final;
}

/* Dado un periodo p, devuelve el número de minutos transcurridos desde el instante de tiempo inicio
   del periodo, hasta su instante final.
*/
unsigned obtenerDuracion(const periodo& p){
    return unsigned(diferencia(p.inicio, p.final));
}

/* Dado un periodo p1 y un periodo p2, devuelve verdad si y solo si ambos periodos tienen instantes
   de inicio iguales, y también tienen instantes de final iguales.
*/
bool operator==(const periodo& p1, const periodo& p2){
    return iguales(p1.inicio, p2.inicio) && iguales(p1.final, p2.final);
}

/* Dado un periodo p1 y un periodo p2, devuelve verdad si y solo si el instante de inicio del
   periodo p1 es estricta y cronológicamente anterior al instante de inicio del periodo p2, o si
   sus instantes de inicio son iguales pero el instante de final del periodo p1 es estricta y
   cronológicamente anterior al instante de final del periodo p2.
*/
bool anterior(const periodo& p1, const periodo& p2){
    return anterior(p1.inicio, p2.inicio) || (iguales(p1.inicio, p2.inicio) && anterior(p1.final, p2.final));
}

/* Dado un periodo p1 y un periodo p2, devuelve verdad si y solo si ambos periodos de tiempo se
   solapan: ambos periodos son iguales o, incluyen instantes de tiempo en común distintos de los
   respectivos inicio y final (es decir, la intersección de los periodos como intervalos abiertos
   no es vacía, si el inicio de un periodo es igual al final del otro periodo no hay solape).
*/
bool solapados(const periodo& p1, const periodo& p2){
    return (p1 == p2) || (anterior(p1.inicio, p2.inicio) &&  posterior(p1.final, p2.inicio)) || (posterior(p1.inicio, p2.inicio) && anterior(p1.inicio, p2.final)) || (iguales(p1.inicio, p2.inicio) && posterior(p1.final,p2.inicio));
}
