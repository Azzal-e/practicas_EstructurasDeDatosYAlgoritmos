/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 4
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 11-11-2023
 * Resumen: Programa que gestiona una colección de periodos de tiempo dedicados a realizar 
 *          actividades a través de un fichero de texto de entrada con diversas instrucciones, y que
 *          además informa del resultado de dichas operaciones en un fichero de texto de salida. 
\*********************************************************************************************/

#include "instantesTAD.hpp"
#include "periodosTAD.hpp"
#include "actividadesTAD.hpp"
#include "colSegmentadaTAD.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

/*
*   Pre: La línea en el flujo de entrada tiene un formato de fecha <<aaaa-mm-dd hh:mm>>
*   Post: Se ha devuelto un booleano con el valor de verdadero si el instante representado
*   en la línea es válido, y en ese caso se ha modificado i de manera que este sus componentes
*   horarias sean las de ese instante. En caso contrario, i no se modifica y se devuelve falso
*/
bool leerInstante(instante& i, ifstream& f){
    string a, m, d, h, min;
    getline(f, a, '-');
    getline(f,m, '-');
    getline(f, d, ' ');
    getline(f, h , ':');
    getline(f, min);
    return crearInstante(stoi(d), stoi(m), stoi(a), stoi(h), stoi(min), i);
}

/*
*   Pre: ---
*   Post: Se toman dos líneas con un instante inicial y otro final y, en caso de ser posible de que
*   formen un periodo válido, se devuelve verdadero y se crea dicho periodo. En caso contrario, se devuelve 
*   falso y es muestra el error.
*/
bool leerPeriodo(instante& iO, instante& iF, periodo& p, ifstream& f, ofstream& s){
    bool exitoi1 = leerInstante(iO, f);
    bool exitoi2 = leerInstante(iF, f);
    bool exitoP = false;
    if(exitoi1 && exitoi2){
        exitoP = crearPeriodo(iO, iF, p);
        if(!exitoP){
            s << "PERIODO NO VALIDO" << endl;
        }
    }
    else{
        s << "INSTANTE NO VALIDO" << endl;
        s << "PERIODO NO VALIDO" << endl;
    }
    return exitoP;
}

/*  Pre: El flujo de entrada se compone, al menos, de tres líneas: una con el nombre de una actividad,
*   otra con su tiempo estimado de realización y una última con su descripción.
*   Post: Se ha creado una actividad con los datos del flujo de entrada.
*/ 
void leerActividad(actividad& act, ifstream& f){
    string nombre, desc, tEst;
    getline(f, nombre);
    getline(f, tEst);
    getline(f, desc);
    crearActividad(nombre, desc, stoi(tEst), act);
}

/*
*   Pre: ---
*   Post: Se escribe por pantalla un instante en formato aaaa-mm-dd hh:mm.
*/
void mostrarInstante(ofstream& s, const instante& inst){
    s << setfill('0') << setw(4) << agno(inst) << "-" << setfill('0') << setw(2) << mes(inst) << "-" << setfill('0') << setw(2) << dia(inst) 
            << " " << setfill('0') << setw(2) << hora(inst) << ":" << setfill('0') << setw(2) << minuto(inst); 
}

/*
*   Pre: ---
*   Post: Se escriben por pantalla una los datos de un actividad.
*/
void mostrarActividad(ofstream& s, const actividad& act ){
    s << " ::: " << obtenerNombre(act) << " ::: (" << obtenerTiempoEstimado(act)<< ") ::: " << obtenerDescripcion(act);
}

/*
*   Pre: el flujo de entrada se compone, como mínimo, de cinco líneas: dos con el instante inicial
*   y el final (en formato aaaa-mm-dd hh:mm), una con el nombre de la actividad, otra con el tiempo estimado para esta y una última con su descripción
*   Post: Se han introducido en cP, en caso de ser posible, los datos de un nuevo periodo y su actividad. En el fichero de salida s
*   se ha escrito una línea que indica si se ha llevado a cabo la inserción y el elemento en cuestión
*
*/
void instruccionA(colSegm<periodo,actividad>& cP, ifstream& f, ofstream& s){
    instante iInicial, iFinal;
    periodo p;
    actividad act;
    bool exito = leerPeriodo(iInicial,iFinal,p, f, s);
    leerActividad(act, f);
    if(exito){
        unsigned tam = tamanyo(cP); // almacenamos el tamaño inicial de la colección
        anyadir(p, act, cP);
        if(tam == tamanyo(cP)){ // Si el tamaño después de llamar a anyadir no cambia significa no se ha podido introducir 
            s << "NO INTRODUCIDO: ";
        }
        else{ // El tamaño cambia, se ha introducido el elemento
            s << "INTRODUCIDO: ";
        }
        s << "[ ";
        mostrarInstante(s, iInicial);
        s << " ;;; ";
        mostrarInstante(s, iFinal); 
        s << " ]";
        mostrarActividad(s, act);
        s << endl;
    }
}

/*
*   Pre: el flujo de entrada se compone, como mínimo, de cinco líneas: dos con el instante inicial
*   y el final (en formato aaaa-mm-dd hh:mm), una con el nombre de la actividad, otra con el tiempo estimado para esta y una última con su descripción
*   Post: Se han actualizado en cP, en caso de ser posible, los datos de una actividad de la colección que tienen un periodo
*   igual al introducido. En el fichero de salida s se ha escrito una línea que indica si se ha podido actualizar o no y
*    el elemento (periodo, actividad) en cuestión.
*/
void instruccionC(colSegm<periodo,actividad>& cP, ifstream& f, ofstream& s){
    instante iInicial, iFinal;
    periodo p;
    actividad act;

    bool exito = leerPeriodo(iInicial, iFinal, p, f, s);
    leerActividad(act, f);
    if(exito){
        if(actualizar(p, act, cP)){
            s << "CAMBIADO: ";
        }
        else{ 
            s << "NO CAMBIADO: ";
        }
        s << "[ ";
        mostrarInstante(s, iInicial);
        s << " ;;; ";
        mostrarInstante(s, iFinal); 
        s << " ]";
        mostrarActividad(s, act);
        s << endl;
    }
}

/*
*   Pre: el flujo de entrada se compone, como mínimo, de dos líneas: una con un instante inicial
*   y otra con un instante final, ambas en formato aaaa-mm-dd hh:mm.
*   Post: Si el periodo introducido es válido, en caso de que en la colección cP exista una actividad
*   con dicho periodo, se válida por pantalla dicha condición y se muestran los datos del periodo
*   y dicha actividad. En caso contrario, se informa de que no ha sido localizado dicho periodo.
*/
void instruccionO(colSegm<periodo,actividad>& cP, ifstream& f, ofstream& s){
    instante iInicial, iFinal;
    periodo p;
    actividad act;

    bool exito = leerPeriodo(iInicial, iFinal, p, f, s);
    if(exito){
        bool obt = obtener(p, cP, act);
        if(obt){
            s << "LOCALIZADO: ";
        }
        else{
            s << "NO LOCALIZADO: ";
        }
        s << "[ " ;
        mostrarInstante(s, iInicial);
        s << " ;;; ";
        mostrarInstante(s, iFinal);
        if(obt){ // Solo se muestra la actividad en caso de poder obtenerla
            s << " -> " << obtenerDuracion(p) << " ]";
            mostrarActividad(s, act);
        }
        else{
            s << " ]";
        }
        s << endl;    
    }
}

/*
*   Pre: el flujo de entrada se compone, como mínimo, de dos líneas: una con un instante inicial
*   y otra con un instante final, ambas en formato aaaa-mm-dd hh:mm.
*   Post: Si el periodo introducido es válido, y además se encuentra un elemento con un periodo que 
*   solapa con el dado, se informa por pantalla de dicho solape. Se informa de cualquier otra condición
*   en otro caso.
*/
void instruccionS(colSegm<periodo,actividad>& cP, ifstream& f, ofstream& s){
    instante iInicial, iFinal;
    periodo p;
    actividad act;

    bool exito = leerPeriodo(iInicial, iFinal, p, f, s);
    if(exito){
        if(seSolapa(p, cP)){
            s << "SOLAPE con: ";
        }
        else{
            s << "NO SOLAPE con: ";
        }
        s << "[ ";
        mostrarInstante(s, iInicial);
        s << " ;;; ";
        mostrarInstante(s, iFinal); 
        s << " ]" << endl;
    }
}

/*
*   Pre: el flujo de entrada se compone, como mínimo, de dos líneas: una con un instante inicial
*   y otra con un instante final, ambas en formato aaaa-mm-dd hh:mm.
*   Post: Si el periodo introducido es válido, y además se encuentra un elemento con ese mismo
*   periodo EN cP, se elimina ese elemento de cP y se informa por pantalla de ello. En caso de
*   que no haya sido posible borrar o los instantes no son validos por si mismo o no forman un periodo
*   válido, también se informa por pantalla
*/
void instruccionB(colSegm<periodo,actividad>& cP, ifstream& f, ofstream& s){
    instante iInicial, iFinal;
    periodo p;
    actividad act;


    bool exito = leerPeriodo(iInicial, iFinal, p, f, s);
    if(exito){
        unsigned tam = tamanyo(cP); // tamaño inicial
        borrar(p, cP);
        if(tam == tamanyo(cP)){ // Si no cambia el tamaño no se ha podido borrar ningún elemento
            s << "NO BORRADO: ";
        }
        else{ // Cambia tamaño, se ha borrado
            s << "BORRADO: ";
        }
        s << "[ ";
        mostrarInstante(s, iInicial);
        s << " ;;; ";
        mostrarInstante(s, iFinal); 
        s << " ]" << endl;
        
    }
}
/*  Pre: El flujo de entrada se compondrá, como mínimo, de una línea, con el
*   nombre de una actividad.
*   Post: Se muestra una lista con todos los periodos dedicados a esa actividad y
*   tanto la duración parcial en cada periodo como de la total finalmente.
*/
void instruccionLA(colSegm<periodo,actividad>& cP, ifstream& f, ofstream& s){
    periodo p;
    actividad act;
    string nombre;
    instante iInicial, iFinal;
    unsigned durTotal = 0;

    getline(f, nombre);
    s << "****ACTIVIDAD: " << nombre << endl;

    iniciarIterador(cP);
    while(haySiguiente(cP)){
        siguiente(cP, p, act);
        /* Se comprueba en cada iteración si hay una
        actividad como la introducida para contabilizarla */
        if(nombre == obtenerNombre(act)){ 
            iInicial = obtenerInicio(p);
            iFinal = obtenerFinal(p);
            
            s << "[ " ;
            mostrarInstante(s, iInicial);
            s << " ;;; ";
            mostrarInstante(s, iFinal);
            s << " -> " << obtenerDuracion(p) << " ]" << endl;    

            durTotal += obtenerDuracion(p);  
        }
    }
    s << "****TOTAL dedicados: " << durTotal << endl;
}

/*
*   Pre: ---
*   Post: Se muestra por pantalla una lista de los elementos (periodo, valor) contenidos
*   en la colección cP, junto con la duración de cada periodo.
*/
void instruccionLT(colSegm<periodo,actividad>& cP, ifstream& f, ofstream& s){
    periodo p;
    actividad act;
    instante iInicial, iFinal;

    s << "-----LISTADO: " << tamanyo(cP) << endl;
    iniciarIterador(cP);
    while(haySiguiente(cP)){
        siguiente(cP, p, act);
        iInicial = obtenerInicio(p);
        iFinal = obtenerFinal(p);

        s << "[ " ;
        mostrarInstante(s, iInicial);
        s << " ;;; ";
        mostrarInstante(s, iFinal);
        s << " -> " << obtenerDuracion(p) << " ]";   
        mostrarActividad(s, act);
        s << endl;
    }
    s << "-----" << endl;
}
// g++ actividadesTAD.cpp periodosTAD.cpp  instantesTAD.cpp main.cpp -o main

/*
*   Pre: ---
*   Post: Se toman dos ficheros de texto, uno de entrada con instrucciones para tratar
*   una colección de pares de periodos y actividades; y otro de salida en el que se muestra
*   el resultado de estas operaciones.
*/
int main(){
 ifstream fichEnt("entrada.txt");
 if(fichEnt.is_open()){
    ofstream fichSal("salida.txt");
    if(fichSal.is_open()){
        string instruccion, salto;
        colSegm<periodo, actividad> cP;
        crear(cP);
        while(fichEnt >> instruccion){
            getline(fichEnt,salto); //Se elimina el resto de la línea, pues esta no afecta.
            if(instruccion == "A"){
                instruccionA(cP, fichEnt, fichSal);
            }
            else if(instruccion == "C"){
                instruccionC(cP, fichEnt, fichSal);
            }
            else if(instruccion == "O"){
                instruccionO(cP, fichEnt, fichSal);
            }
            else if(instruccion == "S"){
                instruccionS(cP, fichEnt, fichSal);
            }
            else if(instruccion == "B"){
                instruccionB(cP, fichEnt, fichSal);
            }
            else if(instruccion == "LA"){
                instruccionLA(cP, fichEnt, fichSal);
            }
            else if(instruccion == "LT"){
                instruccionLT(cP, fichEnt, fichSal);
            }
            else{

            }
        }
        fichSal.close();
    }
    fichEnt.close();
  }
}