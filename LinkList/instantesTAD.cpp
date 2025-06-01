/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 3
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 11-11-2023
 * Resumen: Fichero con la implementación de la operaciones del TAD instante.
\*********************************************************************************************/

#include <iostream>
#include <cmath>
#include "instantesTAD.hpp"
using namespace std;

//IMPLEMENTACIÓN DE OPERACIONES AUXILIARES

/*
*   Dados cinco enteros representando los minutos, horas, dias, mes y agnos de un instante determinado,
*   devuelve verdadero si forman un instante válido respecto al calendario gregoriano. Devuelve falso
*   en caso contrario.
*/
bool valido(const int minuto, const int hora, const int dia, const int mes, const int agno){
    // Comprueba que se cumplen ciertas propiedades globales para cualquier instante.
    bool sx_correcta = minuto >= 0 && hora >= 0 && dia > 0 && mes > 0 && minuto < 60
                     && hora < 24 && agno >= 1582 && mes <= 12;; 
    if(sx_correcta){ // Relación entre el mes y su número de días.
        if(mes == 2){
            if(agno % 400 == 0 || (agno % 100 == 0 && agno % 4 == 0)){ // año bisiesto
                return 29 >= dia;
            }
            else{
                return 28 >= dia;
            }
        }
        else if(mes == 4 || mes == 6 || mes == 9 || mes == 11){
                return 30 >= dia;
            }
        else{
            return 31 >= dia;
        }
    }
    else{
        return sx_correcta;
    }
}
//-----------------------------------------------------------------------

// IMPLEMENTACIÓN DE OPERACIONES DEL TAD

/* 
*  Si los enteros que representan un dia, un mes, un año, una hora y un minuto forman
*  un instante válido acorde al calendario gregoriano, se procede a crear un dato de
*  tipo instante i iniciándolo con dichos valores como componentes y se devuelve verdadero.
*  En caso contrario, no se crea el dato i y se devuelve falso.
*/
bool crearInstante(const int d,const int m, const int a, const int h, const int min, instante& i){
    bool exito = valido(min,h,d,m,a);
    if(exito){
        i.dia = d;
        i.mes = m;
        i.agno = a;
        i.hora = h;
        i.minuto = min; 
    }
    return exito;// Si devuelve no válido se informa al proceso de escritura para que escriba "INSTANTE NO VALIDO"    
}

/* Dado un instante i, devuelve el entero correspondiente al día en ese instante i.
*/
int dia(const instante&  i){
    return i.dia;
}

/* Dado un instante i, devuelve el entero correspondiente al mes en ese instante i.
*/
int mes(const instante&  i){
    return i.mes;
}

/* Dado un instante i, devuelve el entero correspondiente al agno en ese instante i.
*/
int agno(const instante&  i){
    return i.agno;
}

/* Dado un instante i, devuelve el entero correspondiente a la hora en ese instante i.
*/
int hora(const instante&  i){
    return i.hora;
}

/* Dado un instante i, devuelve el entero correspondiente al minuto en ese instante i.
*/
int minuto(const instante&  i){
    return i.minuto;
}

/* Dados dos instantes i1 e i2, devuelve verdadero si ambos instantes son iguales, es decir,
   corresponden al mismo día, mes, año, hora y minuto. Devuelve falso en caso contrario.
*/
bool iguales(const instante& i1, const instante& i2){
    return i1.agno == i2.agno && i1.mes == i2.mes && i1.dia == i2.dia 
            && i1.minuto == i2.minuto && i1.hora == i2.hora;
}

/* Dados dos instantes i1 e i2, devuelve verdadero si y solo si el instante i1 es estricta
   y cronológicamente anterior al instante i2.
*/
bool anterior(const instante& i1, const instante& i2){
    bool comparacion = false;
    if(i1.agno < i2.agno){
        comparacion = true;
    }
    else if(i1.agno == i2.agno){
        if(i1.mes < i2.mes){
            comparacion = true;
        }
        else if(i1.mes == i2.mes){
            if(i1.dia < i2.dia){
                comparacion = true;
            }
            else if(i1.dia == i2.dia){
                if(i1.hora < i2.hora){
                    comparacion = true;
                }
                else if(i1.hora == i2.hora && i1.minuto < i2.minuto){
                    comparacion = true;
                }
            }
        }
    }
    return comparacion; 
}

/* Dados dos instantes i1 e i2, devuelve verdadero si y solo si el instante i1 es estricta
   y cronológicamente posterior al instante i2
*/
bool posterior(const instante& i1, const instante& i2){
    return !iguales(i1, i2) && !anterior(i1, i2); 
}

/* Dados dos instantes i1 e i2, si son correspondientes al mismo año y mes, devuelve un entero con el
   número total de minutos comprendidos desde el instante i1 hasta el instante i2. Si ambos instantes
   i1 e i2 no pertenecen al mismo año y mes, entonces devolverá el entero de valor absoluto 100000.
   El resultado será un número positivo si anterior(i1,i2) o será negativo si posterior(i1,i2).
*/
int diferencia(const instante& i1, const instante& i2){ 
    if(i1.agno == i2.agno && i1.mes == i2.mes){ 
        /* Para instantes de un mismo año y mes, se calcula la diferencia componente por componente
            y se realiza la conversión a minutos. El resultado siempre será negativo y positivo en
            cada caso por propiedades matemáticas.
        */
        return (i2.dia - i1.dia) * (24 * 60) + (i2.hora - i1.hora) * 60 + i2.minuto - i1.minuto;
    }
    else{
        if(anterior(i1, i2)){
            return 100000;
        }
        else{
            return -100000;
        }
    }
}