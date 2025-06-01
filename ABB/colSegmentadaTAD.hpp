/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 4
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 28-11-2023
 * Resumen: Fichero de encabezado con la declaración e implementación del TAD genérico
 *          colección segmentada.
\*********************************************************************************************/

#ifndef COLSEGMENTADATAD_HPP
#define COLSEGMENTADATAD_HPP

#include "pilaTAD.hpp"

// PREDECLARACIÓN DEL TAD GENÉRICO COLECCIÓN SEGMENTADA

/* Los valores del TAD colección segmentada representan colecciones de elementos formados como parejas
   (S, V) tales que en la colección no se permiten elementos con S iguales o solapados.
   El parámetro formal de tipo S requiere tener definidas las siguientes funciones:
    bool operator==(const S& sg1,const S& sg2);
      {devuelve verdad si y solo si sg1 es igual que sg2}
    bool anterior(const S& sg1,const S& sg2);
      {devuelve verdad si y solo si sg1 es anterior a sg2}
    bool solapados(const S& sg1, const S& sg2);
      {devuelve verdad si y solo si sg1 y sg2 están solapados}
*/
template<typename S, typename V> struct colSegm;

/* Devuelve una colección vacía cs. 
*/
template<typename S, typename V> void crear(colSegm<S, V>& cs);

/* Devuelve el número de elementos que hay en la colección cs.
*/
template<typename S, typename V> unsigned tamanyo(const colSegm<S, V>& cs);

/* Devuelve verdad si y solo si cs no contiene ningún elemento
*/
template<typename S, typename V> bool esVacia(const colSegm<S, V>& cs);

/* Si en cs no hay ningún elemento con S igual o solapado con sg, modifica cs de manera
    que está es una colección igual a la resultante de añadir el elemento (sg, v).
*/
template<typename S, typename V> void anyadir(const S& sg, const V& v, colSegm<S, V>& cs);

/* Si en cs hay algún elemento con S igual a sg, sea (sg, v'), modifica la colección segmentada cs de manera
   que esta es la resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se devuelve falso y cs no se modifica.
*/
template<typename S, typename V> bool actualizar(const S& sg, const V& v, colSegm<S, V>& cs);

/* Devuelve verdad si y solo si en cs hay algún elemento con S igual a sg
*/
template<typename S, typename V> bool esta(const S& sg, const colSegm<S, V>& cs);

/* Si en cs hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el dato V que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
*/
template<typename S, typename V> bool obtener(const S& sg, const colSegm<S, V>& cs, V& v);

/* Devuelve verdad si y solo si en cs hay algún elemento cuyo segmento solape con sg
*/
template<typename S, typename V> bool seSolapa(const S& sg, const colSegm<S, V>& cs);

/* Si en cs hay algún elemento con S igual a sg, modifica la colección cs de manera
   que está sea la colección resultante de eliminar ese elemento de la colección cs. En 
   caso, contrario, no se modifica cs.
*/
template<typename S, typename V> void borrar(const S& sg, colSegm<S, V>& cs);

/* Modifica cs inicializando el iterador para recorrer los elementos de la colección, de forma que el siguiente
   elemento a visitar sea el que tiene un S anterior a los de todos los demás elementos de la
   colección (situación de no haber visitado ningún elemento).
*/
template<typename S, typename V> void iniciarIterador(colSegm<S, V>& cs);

/*Devuelve verdad si queda algún elemento por visitar con el iterador de la colección cs, devuelve
    falso si ya se ha visitado el último elemento.
*/
template<typename S, typename V> bool haySiguiente(const colSegm<S, V>& cs);

/* Si queda algún elemento por visitar, devuelve verdadero, se le asigna a sg y v el S y V del siguiente
   elemento a visitar de la colección cs (elemento no visitado con S anterior al resto de los no visitados)
   y se modifica cs avanzando para que se pueda visitar el siguiente elemento. En caso contrario, devuelve falso.
*/
template<typename S, typename V> bool siguiente(colSegm<S, V>& cs, S& sg, V& v);

// PARTE PRIVADA DEL TAD GENÉRICO

    /* Si en el ABB con raíz en el nodo al que apunta rz no hay ningún nodo con segmento 
    igual o solapado con sg, se añade al árbol una nueva hoja cuyo segmento y valor forman el par (sg, v), 
    de manera que el árbol sigue siendo un ABB trás la adición. Además, se devuelve exito con valor de verdadero. 
    En caso contrario, exito toma el valor de falso y no se añade ningún nodo en el ABB.
    */
    template<typename S, typename V> void anyadirRec(const S& sg, const V& v, typename colSegm<S, V>::unaPareja*& rz,
    bool& exito);

    /* Devuelve verdad si y solo si el ABB que tiene como raíz a rz no tiene ningún nodo cuyo 
        segmento solape con sg.
    */
    template<typename S, typename V> bool seSolapaRec(const S& sg, const typename colSegm<S, V>::unaPareja* rz);

    /* Si en el ABB con raíz en rz hay algún elemento con segmento igual a sg, sea (sg, v'), modifica dicho nodo de manera
   que este sea el resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se de vuelve falso y no se modifica ningún nodo.
    */
    template<typename S, typename V> bool actualizarRec(const S& sg, const V& v,typename colSegm<S, V>::unaPareja*& rz);

    /* Devuelve verdad si y solo si en el ABB con rz como raíz hay algún nodo con segmento igual a sg.
    */
    template<typename S, typename V> bool estaRec(const S& sg, const typename colSegm<S, V>::unaPareja* rz);

    /* Si en el ABB con raíz en rz hay algún nodo con segmento igual a sg, devuelve verdadero y le asigna a v el valor que forma
        el elemento con dicho sg. En caso contrario, se devuelve falso.
    */
    template<typename S, typename V> bool obtenerRec(const S& sg, const typename colSegm<S, V>::unaPareja* rz, V& v);

    /* Dada la raíz rz de un ABB no vacío, se procede a devolver el nodo  con mayor segmento y se borra del árbol.
    */
    template<typename S, typename V> void borrarMax(typename colSegm<S, V>::unaPareja*& rz, typename colSegm<S, V>::unaPareja& nMax);

    /* Si en el ABB con rz como raíz hay algún elemento con segmento igual a sg, modifica el árbol de manera
   que este siga manteniendo la condición de ABB pero se haya eliminado dicho nodo y devuelve en exito
   verdadero. En caso, contrario, no se modifica el árbol y exito toma el valor de falso.
    */
    template<typename S, typename V> void borrarRec(const S& sg,typename colSegm<S, V>::unaPareja*& rz, bool& exito);

    // DECLARACIÓN DEL TAD GENÉRICO COLECCIÓN SEGMENTADA

template<typename S, typename V> struct colSegm{
    friend void crear<S,V>(colSegm<S, V>& cs);
    friend unsigned tamanyo<S,V>(const colSegm<S, V>& cs);
    friend bool esVacia<S,V>(const colSegm<S, V>& cs);
    friend void anyadir<S,V>(const S& sg, const V& v, colSegm<S, V>& cs);
    friend bool actualizar<S,V>(const S& sg, const V& v, colSegm<S, V>& cs);
    friend bool esta<S,V>(const S& sg, const colSegm<S, V>& cs);
    friend bool obtener<S,V>(const S& sg, const colSegm<S, V>& cs, V& v);
    friend bool seSolapa<S,V>(const S& sg, const colSegm<S, V>& cs);
    friend void borrar<S,V>(const S& sg, colSegm<S, V>& cs);
    friend void iniciarIterador<S,V>(colSegm<S, V>& cs);
    friend bool haySiguiente<S,V>(const colSegm<S, V>& cs);
    friend bool siguiente<S,V>(colSegm<S, V>& cs, S& sg, V& v);

    private:
    /* Internamente, el TAD colección segmentada se implementa como un árbol de búsqueda binaria, es decir, cada nodo del árbol tiene como máximo
       dos hijos, de manera que todos los nodos del subárbol izquierdo sean menores (anteriores) que él y todos los nodos de su subárbol derecho sean mayores que este.
       Sus subárboles también serán ABB.
       Cada nodo del ABB es un nodo unaPareja, registro que agrupa dos datos de tipo segmento (S) y valor (V) que forman el elemento (S, V) de la colección y
       dos punteros hijDer e hijIzq, sus hijos derecho e izquierdo. Concretamente hijDer apunta al nodo cuyo segmento sea posterior al del padre pero anterior a todos los
       demás segmentos de nodos del árbol que sean posteriores al padre; e hijIzq apunta al nodo cuyo segmento sea anterior al del padre pero posterior a los segmentos
        del resto de nodos del árbol que sean anteriores al del padre.
        Cabe destacar que ningún nodo del árbol podrá tener un segmento igual o solapado que otro.
    */
     struct unaPareja{
        S segmento;
        V valor;
        unaPareja* hijDer, *hijIzq;
    };

    // OPERACIONES AUXILIARES

    /* Si en el ABB con raíz en el nodo al que apunta rz no hay ningún nodo con segmento 
    igual o solapado con sg, se añade al árbol una nueva hoja cuyo segmento y valor forman el par (sg, v), 
    de manera que el árbol sigue siendo un ABB trás la adición. Además, se devuelve exito con valor de verdadero. 
    En caso contrario, exito toma el valor de falso y no se añade ningún nodo en el ABB.
    */
    friend void anyadirRec<S,V>(const S& sg, const V& v, unaPareja*& rz,
    bool& exito);

    /* Devuelve verdad si y solo si el ABB que tiene como raíz a rz no tiene ningún nodo cuyo 
   segmento solape con sg.
    */
    friend bool seSolapaRec<S,V>(const S& sg,const unaPareja* rz);

    /* Si en el ABB con raíz en rz hay algún elemento con segmento igual a sg, sea (sg, v'), modifica dicho nodo de manera
   que este sea el resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se de vuelve falso y no se modifica ningún nodo.
    */
    friend bool actualizarRec<S,V>(const S& sg, const V& v, unaPareja*& rz);

    /* Devuelve verdad si y solo si en el ABB con rz como raíz hay algún nodo con segmento igual a sg.
    */
    friend bool estaRec<S,V>(const S& sg,const unaPareja* rz);

    /* Si en el AVL con raíz en rz hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el valor que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
    */
    friend bool obtenerRec<S,V>(const S& sg, const unaPareja* rz, V& v);

    /* Dada la raíz rz de un ABB no vacío, se procede a devolver el nodo  con mayor segmento y se borra del árbol.
   El coste temporal es lineal en el número de nodos del árbol al no estar la altura restringida.
    */
    friend void borrarMax<S,V>(unaPareja*& rz, unaPareja& nMax);

    /* Si en el ABB con rz como raíz hay algún elemento con segmento igual a sg, modifica el árbol de manera
   que este siga manteniendo la condición de ABB pero se haya eliminado dicho nodo y devuelve en exito
   verdadero. En caso, contrario, no se modifica el árbol y exito toma el valor de falso.
    */
    friend void borrarRec<S,V>(const S& sg, unaPareja*& rz, bool& exito);  
    // FIN DE LAS OPERACIONES AUXILIARES

    /* Consecuentemente, una colección segmentada se define como la agrupación de un puntero a la raíz del ABB, una pila para las operaciones del iterador y
        una variable entera con el número de nodos del árbol. 
     */

     unaPareja* raiz;
     int tam;
     Pila<unaPareja*> iter; 
};

// IIMPLEMENTACIÓN DE LAS OPERACIONES AUXILIARES DEL TAD COLECCIÓN SEGMENTADA

/* Si en el ABB con raíz en el nodo al que apunta rz no hay ningún nodo con segmento 
   igual o solapado con sg, se añade al árbol una nueva hoja cuyo segmento y valor forman el par (sg, v), 
   de manera que el árbol sigue siendo un ABB trás la adición. Además, se devuelve exito con valor de verdadero. 
   En caso contrario, exito toma el valor de falso y no se añade ningún nodo en el ABB.
   El coste en tiempo de la operación es lineal en el número de nodos del árbol con rz como raíz, puesto
   que ha que comprobar el solape con cada uno de ellos.
*/
template<typename S, typename V> void anyadirRec(const S& sg, const V& v,typename colSegm<S, V>::unaPareja*& rz,
    bool& exito){
    if(rz == nullptr){
        /*  Si rz es vacía, como no hay solapamiento
            con ningún nodo, se procede a añadir una hoja con el par
            (sg, v) como elemento.
            */
            rz = new typename colSegm<S, V>::unaPareja; 
            rz-> segmento = sg;
            rz-> valor = v;
            rz-> hijDer = nullptr;
            rz-> hijIzq = nullptr;
            exito = true;
    }
    else{
        if(!solapados(sg, rz->segmento)){
            if(anterior(sg, rz->segmento)){
                /* Si el segmento sg es anterior al de rz y no solapan, se tendría
                que buscar la adición en el subárbol izquierdo de rz, comprobando
                antes que no hay solapamiento con ningún segmento de un nodo 
                del subárbol derecho.
                */ 
                if(!seSolapaRec<S, V>(sg, rz -> hijDer)){
                    anyadirRec<S, V>(sg, v, rz -> hijIzq, exito); // Adición en el subárbol izquierdo.
                }
                else{
                    exito = false; // Solapamiento con el subárbol derecho.
                }
            }
            else if(anterior(rz->segmento, sg)){
                /* Si el segmento sg es posterior al de rz y no solapan, se tendría
                que buscar la adición en el subárbol derecho de rz, comprobando
                antes que no hay solapamiento con ningún segmento de un nodo 
                del subárbol izquierdo.
                */ 
                if(!seSolapaRec<S, V>(sg, rz -> hijIzq)){
                    anyadirRec<S, V>(sg, v, rz -> hijDer, exito); // Adición en el subárbol derecho.
                }
                else{
                    exito = false; // Solapamiento con el subárbol izquierdo.
                }
            }
            else{
                // Se ha encontrado un nodo con mismo segmento que sg.
                exito = false;
            } 
        }
        else{
            // Se ha encontrado solapamiento con el segmento de rz
            exito = false;
        }  
    }
}


/* Devuelve verdad si y solo si el ABB que tiene como raíz a rz no tiene ningún nodo cuyo 
   segmento solape con sg.
   El coste temporal de la operación es lineal respecto al número de nodos, puesto que 
   la solapación no tiene por qué tener una relación clara con el criterio de ordenación.
*/
template<typename S, typename V> bool seSolapaRec(const S& sg, const typename colSegm<S, V>::unaPareja* rz){
    if(rz != nullptr){
        /* Si la raíz no apunta al puntero nulo (arbol no vacío), se procede a comprobar
           que no haya solapamiento con la raíz.
        */
        if(!solapados(sg,  rz -> segmento)){
            /* Si no hay solape con el segmento de la raíz, se comprueba que 
               no exista solapamiento con el subárbol izquierdo, del que es raíz
               su hijo izquierdo; y con el subárbol derecho, del que es es raíz 
               su hijo derecho.
            */
            return (seSolapaRec<S, V>(sg, rz -> hijIzq) || seSolapaRec<S, V>(sg, rz -> hijDer));
        }
        else{
            /* Si solapa con el segmento de la raíz, se devuelve verdadero.*/
            return true;
        }
    }
    else{
        /* En caso de que la raíz apunte al puntero nulo, se devuelve falso, pues no
           existe nodo con un segmento que comparar. Este caso se da cuando efectivamente
           el árbol inicial introducido sea vacío, o cuando se haya ido llamando recursivamente
           a la función para cada hijo de cada nodo sin solapamientos y cuando se llegue a las
           hojas estás tampoco solapen, siendo todos sus hijos árboles vacíos, en este sentido.
        */
        return false;
    }
    
}

/* Si en el ABB con raíz en rz hay algún elemento con segmento igual a sg, sea (sg, v'), modifica dicho nodo de manera
   que este sea el resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se devuelve falso y no se modifica ningún nodo.
   El coste temporal en caso peor será lineal respecto al número de nodos del árbol por no estar su
   altura restringida.
*/
template<typename S, typename V> bool actualizarRec(const S& sg, const V& v, typename colSegm<S, V>::unaPareja*& rz){
    if(rz == nullptr){
        // Si el árbol es vacío, no hay ningún nodo que actualizar.
        return false;
    }
    else{
        if(anterior(sg, rz->segmento)){
            return actualizarRec(sg, v, rz->hijIzq); // Actualización en el subárbol izquierdo
        }
        else if(anterior (rz->segmento, sg)){
            return actualizarRec(sg, v, rz->hijDer); // Actualización en el subárbol derecho.
        }
        else{
            // Se ha encontrado un nodo con segmento igual, por lo que se actualiza su valor y devuelve verdadero.
            rz -> valor = v;
            return true; 
        }
    }
}

/* Devuelve verdad si y solo si en el ABB con rz como raíz hay algún nodo con segmento igual a sg.
   El coste temporal en caso peor será lineal respecto al número de nodos del árbol por no estar su
   altura restringida.
*/
template<typename S, typename V> bool estaRec(const S& sg,typename colSegm<S, V>::unaPareja* rz){
    if(rz == nullptr){
        // Si el árbol es vacío, no hay ningún nodo con segmento igual a sg.
        return false;
    }
    else{
        if(anterior(sg, rz->segmento)){
            return estaRec(sg, rz->hijIzq); // Búsqueda en el subárbol izquierdo
        }
        else if(anterior (rz->segmento, sg)){
            return estaRec(sg, rz->hijDer); // Búsqueda en el subárbol derecho.
        }
        else{
            // Se ha encontrado un nodo con segmento igual, por lo que se devuelve verdadero.
            return true; 
        }
    }
}

/* Si en el ABB con raíz en rz hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el valor que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
   El coste temporal en caso peor será lineal respecto al número de nodos del árbol por no estar su
   altura restringida.
*/
template<typename S, typename V> bool obtenerRec(const S& sg, const typename colSegm<S, V>::unaPareja* rz, V& v){
    if(rz == nullptr){
        // Si el árbol es vacío, no hay ningún nodo con segmento igual a sg.
        return false;
    }
    else{
        if(anterior(sg, rz->segmento)){
            return obtenerRec<S, V>(sg, rz->hijIzq, v); // Obtención en el subárbol izquierdo
        }
        else if(anterior (rz->segmento, sg)){
            return obtenerRec<S, V>(sg, rz->hijDer, v); // Obtención en el subárbol derecho.
        }
        else{
            // Se ha encontrado un nodo con segmento igual, por lo que asigna a v el valor del nodo y devuelve verdadero.
            v = rz->valor;
            return true; 
        }
    }
}

/* Si en el ABB con rz como raíz hay algún elemento con segmento igual a sg, modifica el árbol de manera
   que este siga manteniendo la condición de ABB pero se haya eliminado dicho nodo y devuelve en exito
   verdadero. En caso, contrario, no se modifica el árbol y exito toma el valor de falso.
   El coste temporal en caso peor será lineal respecto al número de nodos del árbol por no estar su
   altura restringida.
*/
template<typename S, typename V> void borrarRec(const S& sg, typename colSegm<S, V>::unaPareja*& rz, bool& exito){
    if(rz == nullptr){
        // El árbol es vacío, no hay ningún nodo que eliminar.
        exito = false;
    }
    else if(anterior(sg, rz->segmento)){
        borrarRec<S, V>(sg, rz->hijIzq, exito); // Borrado en subárbol izquierdo, pues sg anterior al segmento de rz.
    }
    else if(anterior(rz->segmento, sg)){
        borrarRec<S, V>(sg, rz->hijDer, exito); // Borrado en subárbol derecho, pues sg posterior al segmento de rz.
    }
    else{ // Se ha encontrado un nodo con segmento igual a sg
        if(rz->hijIzq == nullptr){
            /* Si rz no tiene hijo izquierdo, eliminamos rz y hacemos
               que el hijo derecho (forme parte de un subárbol vacío o no) 
               tome su posición. Al ser menor que el padre de rz el árbol 
               seguirá siendo ordenado, y si el subárbol está vacío el padre 
               de rz no tendrá hijos en ese subárbol, pero será ordenado.
            */
           typename colSegm<S, V>::unaPareja* aux = rz;
           rz = rz->hijDer;
           delete aux;
        }
        else{
            /* Si rz tiene hijo izquierdo, se busca en el subárbol izquierdo el nodo
               con mayor segmento, y se "desplaza" sustituyendo a rz. Este nodo será anterior
               a su nuevo padre por ser el árbol ABB, y forma un nuevo ABB por ser anterior a los nodos
               de su subárbol derecho (por propiedad) y posterior a los nodos de su subárbol izquierdo
               (por elección).
            */
            typename colSegm<S, V>::unaPareja nMax;
            borrarMax<S,V>(rz->hijIzq, nMax); //Se borra el nodo con máximo elemento y devuelve en nMax.
            /* Se sustituye segmento y valor del nodo a eliminar por aquellos del nodo nMax;
            */
            rz->segmento = nMax.segmento; 
            rz->valor = nMax.valor;
        }
        exito = true;
    }
}

/* Dada la raíz rz de un ABB no vacío, se procede a devolver el nodo  con mayor segmento y se borra del árbol.
   El coste temporal es lineal en el número de nodos del árbol al no estar la altura restringida.
*/
template<typename S, typename V> void borrarMax(typename colSegm<S, V>::unaPareja*& rz,typename colSegm<S, V>::unaPareja& nMax){
    if(rz->hijDer != nullptr){
        borrarMax<S,V>(rz->hijDer, nMax); // Si existe hijo derecho (con segmento mayor), se busca borrado en subárbol derecho.
    }
    else{
        //Si no existe hijo derecho se ha encontrado el nodo con segmento máximo.
        typename colSegm<S, V>::unaPareja* aux = rz;
        nMax = *rz;
        rz = rz->hijIzq;
        delete aux; 
    }
}

// IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD COLECCIÓN SEGMENTADA
/* Devuelve una colección vacía cs. 
   El coste temporal de la operación es constante.
*/
template<typename S, typename V> void crear(colSegm<S, V>& cs){
    cs.raiz = nullptr;
    cs.tam = 0;
    crearVacia(cs.iter);
}

/* Devuelve el número de elementos que hay en la colección cs.
   El coste temporal de la operación es constante.
*/
template<typename S, typename V> unsigned tamanyo(const colSegm<S, V>& cs){
    return cs.tam;
}

/* Devuelve verdad si y solo si cs no contiene ningún elemento.
   El coste temporal de la operación es constante.
*/
template<typename S, typename V> bool esVacia(const colSegm<S, V>& cs){
    return cs.tam == 0;
}

/* Si en cs no hay ningún elemento con segm igual o solapado con sg, modifica cs de manera
*  que esta es una colección igual a la resultante de añadir el elemento (sg, v) en la colección.
*  El coste de la operación es lineal respecto al tamaño del árbol dado que está implementada de manera
*  que solo se recorra una vez.
*/
template<typename S, typename V> void anyadir(const S& sg, const V& v, colSegm<S, V>& cs){
    bool exito;
    anyadirRec<S, V>(sg, v, cs.raiz, exito);
    if(exito){
        cs.tam++;
    }
}    

/* Si en cs hay algún elemento con S igual a sg, sea (sg, v'), modifica la colección segmentada cs de manera
   que esta es la resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se de vuelve falso y cs no se modifica.
   El coste temporal será lineal en caso peor al no estar la altura del ABB limitada.
*/
template<typename S, typename V> bool actualizar(const S& sg, const V& v, colSegm<S, V>& cs){
    return actualizarRec<S, V>(sg, v, cs.raiz);
}

/* Devuelve verdad si y solo si en cs hay algún elemento con S igual a sg.
   El coste temporal será lineal en caso peor al no estar la altura del ABB limitada.
*/
template<typename S, typename V> bool esta(const S& sg, const colSegm<S, V>& cs){
    return estaRec<S, V>(sg, cs.raiz);
}


/* Si en cs hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el dato V que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
   El coste temporal será lineal en caso peor al no estar la altura del ABB limitada.
*/
template<typename S, typename V> bool obtener(const S& sg, const colSegm<S, V>& cs, V& v){
    return obtenerRec<S, V>(sg, cs.raiz, v);
}

/* Devuelve verdad si y solo si en cs hay algún elemento cuyo segmento solape con sg
   El coste temporal de la operación es lineal respecto al número de elementos, puesto que 
   la solapación no tiene por qué tener una relación clara con el criterio de ordenación.
*/
template<typename S, typename V> bool seSolapa(const S& sg, const colSegm<S, V>& cs){
    return seSolapaRec<S, V>(sg, cs.raiz);    
}


/* Si en cs hay algún elemento con S igual a sg, modifica la colección cs de manera
   que está sea la colección resultante de eliminar ese elemento de la colección cs. En 
   caso, contrario, no se modifica cs.
   El coste temporal será lineal en caso peor al no estar la altura del ABB limitada.
*/
template<typename S, typename V> void borrar(const S& sg, colSegm<S, V>& cs){
    bool exito;
    borrarRec<S, V>(sg, cs.raiz, exito);
    if(exito){
        cs.tam--;
    }
}

/* Modifica cs inicializando el iterador para recorrer los elementos de la colección, de forma que el siguiente
   elemento a visitar sea el que tiene un S anterior a los de todos los demás elementos de la
   colección (situación de no haber visitado ningún elemento). El coste en tiempo de la operación será logarítmico
   respecto al número de nodos dado que la altura también lo es.
*/
template<typename S, typename V> void iniciarIterador(colSegm<S, V>& cs){
    typename colSegm<S, V>::unaPareja* aux = cs.raiz;
    liberar(cs.iter);
    while(aux != nullptr){
        /* Dado que el árbol está ordenado, el elemento con menor segmento (primero a visitar), será el nodo
           más a la izquierda del árbol. Por ello, se apilan en la pila sucesivos hijos izquierdos de las raíces
           de los respectivos subárboles hasta llegar a un nodo que no tenga. Este nodo será el primero a visitar.
        */
        apilar(cs.iter, aux);
        aux = aux->hijIzq;
    }
}

/* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección cs, devuelve
   falso si ya se ha visitado el último elemento.
*/
template<typename S, typename V> bool haySiguiente(const colSegm<S, V>& cs){
    return !esVacia(cs.iter);
}

/* Si queda algún elemento por visitar, devuelve verdadero, se le asigna a sg y v el S y V del siguiente
   elemento a visitar con el iterador de la colección cs (elemento no visitado con S anterior al resto de los no visitados)
   y se modifica cs avanzando el iterador para que se pueda visitar el siguiente elemento. En caso contrario, devuelve falso.
*/
template<typename S, typename V> bool siguiente(colSegm<S, V>& cs, S& sg, V& v){
    bool exito = haySiguiente(cs);
    if(exito){
        typename colSegm<S, V>::unaPareja* aux;
        bool error;
        /* El siguiente elemento a visitar es la cima de la pila iter
           de la colección, por lo que se toma el valor del segmento y valor 
           de la pareja del nodo cuyo puntero se almacena y se elimina este. 
        */
        cima(cs.iter, aux, error);
        sg = aux->segmento;
        v = aux->valor;
        desapilar(cs.iter);
        
        /* Se ha eliminado el menor elemento de los existentes en la pila.
           Por construcción, la nueva cima de la colección es el padre del nodo
           visitado, pero si este nodo tiene hijo derecho (sin recorrer aún), todo
           nodo del subárbol derecho tiene anterior segmento que el del padre. Se recorre
           así el subárbol derecho en búsqueda del menor segmento existente, que será
           el amacenado por el nodo que viene de recorrer sucesivos hijos izquierdos
           y no tiene hijo izquierdo. Si no tiene hijo derecho, entonces el siguiente
           anterior segmento vendrá almacenado por su padre, siguiente nodo a visitar
           al no haberse modificado la pila.
        */
        aux = aux->hijDer;
        while(aux != nullptr){
            apilar(cs.iter, aux);
            aux = aux->hijIzq;
        }
    }
    return exito;
}


#endif