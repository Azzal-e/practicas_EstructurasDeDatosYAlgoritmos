/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 3
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 11-11-2023
 * Resumen: Fichero de encabezado con la declaración del TAD instante.
\*********************************************************************************************/

#ifndef INSTANTESTAD_HPP
#define INSTANTESTAD_HPP

// PREDECLARACIÓN DEL TAD INSTANTE


/* Los valores del TAD representan instantes de tiempo correctos,
*  es decir, valores que incluyen una fecha y hora válidos según
*  las reglas del calendario gregoriano
*/
struct instante;

/* 
*  Si los enteros que representan un dia, un mes, un año, una hora y un minuto forman
*  un instante válido acorde al calendario gregoriano, se procede a crear un dato de
*  tipo instante i iniciándolo con dichos valores como componentes y se devuelve verdadero.
*  En caso contrario, no se crea el dato i y se devuelve falso.
*/
bool crearInstante(const int dia,const int mes,const int agno,const int hora,const int minuto, instante& i);

/* Dado un instante i, devuelve el entero correspondiente al día en ese instante i.
*/
int dia(const instante&  i);

/* Dado un instante i, devuelve el entero correspondiente al mes en ese instante i.
*/
int mes(const instante&  i);

/* Dado un instante i, devuelve el entero correspondiente al agno en ese instante i.
*/
int agno(const instante&  i);

/* Dado un instante i, devuelve el entero correspondiente a la hora en ese instante i.
*/
int hora(const instante&  i);

/* Dado un instante i, devuelve el entero correspondiente al minuto en ese instante i.
*/
int minuto(const instante&  i);

/* Dados dos instante i1 e i2, devuelve verdadero si ambos instantes son iguales, es decir,
   corresponden al mismo día, mes, año, hora y minuto. Devuelve falso en caso contrario.
*/
bool iguales(const instante& i1, const instante& i2);

/* Dados dos instantes i1 e i2, devuelve verdadero si y solo si el instante i1 es estricta
   y cronológicamente anterior al instante i2.
*/
bool anterior(const instante& i1, const instante& i2);

/* Dados dos instantes i1 e i2, devuelve verdadero si y solo si el instante i1 es estricta
   y cronológicamente posterior al instante i2.
*/
bool posterior(const instante& i1, const instante& i2);

/* Dados dos instantes i1 e i2, si son correspondientes al mismo año y mes, devuelve un entero con el
   número total de minutos comprendidos desde el instante i1 hasta el instante i2. Si ambos instantes
   i1 e i2 no pertenecen al mismo año y mes, entonces devolverá el entero de valor absoluto 100000.
   El resultado será un número positivo si anterior(i1,i2) o será negativo si posterior(i1,i2).
*/
int diferencia(const instante& i1, const instante& i2);

// SECCIÓN PRIVADA DE DECLARACIONES 

bool valido(int minuto, int hora, int dia, int mes, int agno);

//Declaración del TAD instante

struct instante{
    friend bool crearInstante(const int dia,const int mes,const int agno,const int hora,const int minuto, instante& i);
    friend int dia(const instante&  i);
    friend int mes(const instante&  i);
    friend int agno(const instante&  i);
    friend int hora(const instante&  i);
    friend int minuto(const instante&  i);
    friend bool iguales(const instante& i1, const instante& i2);
    friend bool anterior(const instante& i1, const instante& i2);
    friend bool posterior(const instante& i1, const instante& i2);
    friend int diferencia(const instante& i1, const instante& i2);

   
   private:
     /* Internamente, un instante se define como una agrupación de cinco enteros
        para el día, mes, agno, hora y minuto.
     */
     int dia, mes, agno, hora, minuto;
};

#endif