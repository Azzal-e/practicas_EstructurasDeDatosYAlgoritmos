/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 3
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 14-11-2023
 * Resumen: Fichero de encabezado con la declaración e implementación del TAD genérico
 *          colección segmentada.
\*********************************************************************************************/

#ifndef COLSEGMENTADASTAD_HPP
#define COLSEGMENTADASTAD_HPP

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
template<typename S, typename V, template <typename> typename P> void crear(colSegm<S, V>& cs);

/* Devuelve el número de elementos que hay en la colección cs.
*/
template<typename S, typename V, template <typename> typename P> unsigned tamanyo(const colSegm<S, V, P>& cs);

/* Devuelve verdad si y solo si cs no contiene ningún elemento
*/
template<typename S, typename V, template <typename> typename P> bool esVacia(const colSegm<S, V, P>& cs);

/* Si en cs no hay ningún elemento con S igual o solapado con sg, modifica cs de manera
    que está es una colección igual a la resultante de añadir el elemento (sg, v).
*/
template<typename S, typename V, template <typename> typename P> void anyadir(const S& sg, const V& v, colSegm<S, V, P>& cs);

/* Si en cs hay algún elemento con S igual a sg, sea (sg, v'), modifica la colección segmentada cs de manera
   que esta es la resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se devuelve falso y cs no se modifica.
*/
template<typename S, typename V, template <typename> typename P> bool actualizar(const S& sg, const V& v, colSegm<S, V, P>& cs);

/* Devuelve verdad si y solo si en cs hay algún elemento con S igual a sg
*/
template<typename S, typename V, template <typename> typename P> bool esta(const S& sg, const colSegm<S, V, P>& cs);

/* Si en cs hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el dato V que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
*/
template<typename S, typename V, template <typename> typename P> bool obtener(const S& sg, const colSegm<S, V, P>& cs, V& v);

/* Devuelve verdad si y solo si en cs hay algún elemento cuyo segmento solape con sg
*/
template<typename S, typename V, template <typename> typename P> bool seSolapa(const S& sg, const colSegm<S, V, P>& cs);

/* Si en cs hay algún elemento con S igual a sg, modifica la colección cs de manera
   que está sea la colección resultante de eliminar ese elemento de la colección cs. En 
   caso, contrario, no se modifica cs.
*/
template<typename S, typename V, template <typename> typename P> void borrar(const S& sg, colSegm<S, V, P>& cs);

/* Modifica cs inicializando el iterador para recorrer los elementos de la colección, de forma que el siguiente
   elemento a visitar sea el que tiene un S anterior a los de todos los demás elementos de la
   colección (situación de no haber visitado ningún elemento).
*/
template<typename S, typename V, template <typename> typename P> void iniciarIterador(colSegm<S, V, P>& cs);

/*Devuelve verdad si queda algún elemento por visitar con el iterador de la colección cs, devuelve
    falso si ya se ha visitado el último elemento.
*/
template<typename S, typename V, template <typename> typename P> bool haySiguiente(const colSegm<S, V, P>& cs);

/* Si queda algún elemento por visitar, devuelve verdadero, se le asigna a sg y v el S y V del siguiente
   elemento a visitar de la colección cs (elemento no visitado con S anterior al resto de los no visitados)
   y se modifica cs avanzando para que se pueda visitar el siguiente elemento. En caso contrario, devuelve falso.
*/
template<typename S, typename V, template <typename> typename P> bool siguiente(colSegm<S, V>& cs, S& sg, V& v);

// DECLARACIÓN DEL TAD GENÉRICO COLECCIÓN SEGMENTADA

template<typename S, typename V, template <typename> typename P> struct colSegm{
    friend void crear<S, V, P>(colSegm<S, V, P>& cs);
    friend unsigned tamanyo<S, V, P>(const colSegm<S, V, P>& cs);
    friend bool esVacia<S, V, P>(const colSegm<S, V, P>& cs);
    friend void anyadir<S, V, P>(const S& sg, const V& v, colSegm<S, V, P>& cs);
    friend bool actualizar<S, V, P>(const S& sg, const V& v, colSegm<S, V, P>& cs);
    friend bool esta<S, V, P>(const S& sg, const colSegm<S, V, P>& cs);
    friend bool obtener<S, V, P>(const S& sg, const colSegm<S, V, P>& cs, V& v);
    friend bool seSolapa<S, V, P>(const S& sg, const colSegm<S, V, P>& cs);
    friend void borrar<S, V, P>(const S& sg, colSegm<S, V, P>& cs);
    friend void iniciarIterador<S, V, P>(colSegm<S, V, P>& cs);
    friend bool haySiguiente<S, V, P>(const colSegm<S, V, P>& cs);
    friend bool siguiente<S, V, P>(colSegm<S, V, P>& cs, S& sg, V& v);

    private:
    /* Internamente, el TAD colección segmentada se implementa como un árbol de búsqueda binaria 1-equilibrado (AVL), es decir cada nodo del árbol tiene como máximo
       dos hijos, de manera que todos los nodos del subárbol izquierdo sean menores (anteriores) a él y todos los nodos de su subárbol derecho sean mayores que este.
       Además, para todo nodo del AVL se tiene que las alturas de sus subárboles difieren como mucho en uno (la altura es logarítmica respecto al número de nodos)
       Cada nodo del AVL es un nodo unaPareja, registro que agrupa dos datos de tipo segmento (S) y valor (V) que forman el elemento (S, V) de la lista y
       dos punteros hijDer, hijIzq sus hijos derecho e izquierdo. Concretamente hijDer apunta al nodo cuyo segmento sea posterior al del padre pero anterior a todos los
       demás segmentos de nodos del árbol que sean posteriores al padre; y hijIzq apunta al nodo cuyo segmento sea anterior al del padre pero posterior a los segmentos
        del resto de nodos del árbol que sean anterior al del padre. Además, también se declara un entero factorEq, que almacena la diferencia de alturas entre el subárbol
        derecho y el subárbol izquierdo del nodo, que toma valores entre -1 y 1 (-1 si es pesado a izquierdas, 0 si está perfectamente equilibrado y 1 si es pesado a derechas).
        Cabe destacar que ningún nodo del árbol podrá tener un segmento igual o solapado que otro, y que el factor de equilibrio se modificará en operaciones de adición y borrado,
        pudiendo ser necesario reequilibrar el árbol. 
    */
     struct unaPareja{
        S segmento;
        V valor;
        int factorEq;
        unaPareja* hijDer, hijIzq;
     };
     /* Consecuentemente, una colección segmentada se define como la agrupación de un puntero a la raíz del AVL, una pila para las operaciones del iterador y
        un entero con el número de nodos del árbol. 
     */

     unaPareja* raiz;
     int tam;
     Pila<unaPareja*> iter;     
};


#endif

// IIMPLEMENTACIÓN DE LAS OPERACIONES AUXILIARES DEL TAD COLECCIÓN SEGMENTADA

/* Dado un puntero a nodo n que es muy pesado a izquierdas (Feq = -2), cuyo
   subárbol izquierdo es un AVL pesado a izquierdas y su subárbol derecho es otro AVL, 
   se ejecuta una rotación a la izquierda. De este modo, el nodo  queda reequilibrado tras la operación. 
   La operación tiene un coste en tiempo constante.
*/
template<typename S, typename V> void rotIzq(colSegm<S, V>::unaPareja* n){
    typename colSegm<S, V>::unaPareja* aux = n->hijIzq;

    /* Como el subárbol izquierdo del nodo n es pesado a izquierdas, la altura de este
       viene dada por la longitud del recorrido desde su raíz (el hijo izquierdo de n) 
       hasta una hoja del subárbol izquierdo sarb1 de esta raíz. Al ser el nodo n muy 
       pesado a izquierdas, el sarb1 tendrá la misma altura que la longitud del recorrido
       desde n hasta una hoja de su subárbol derecho sarb3. Además, al ser la altura del subárbol
       derecho del hijo izquierdo sarb2 una unidad  menor que la de sarb1, se tiene que
       la altura de sarb2 es igual que la de sarb3.
    */

    n->hijIzq = aux -> hijDer; // El hijo izquierdo de n pasa a ser la raíz sarb2.
    n->factorEq = 0; // altura de sarb2 es igual a la de sarb3, n pasa a estar perfectamente equlibrado.
    aux -> hijDer = n; // El hijo izquierdo de n pasa a ser su padre
    n = aux;
    /* altura de sarb2 es igual a la longitud desde A hasta un nodo hoja de sarb3, que determina
       la altura del subárbol derecho del nuevo n (antiguo hijo izquierdo), por lo que n pasa
       a estar perfectamente equilibrado.
    */
    n->factorEq = 0; 

}

/* Dado un puntero a nodo n que es muy pesado a izquierdas (Feq = -2), cuyo
   subárbol izquierdo es un AVL pesado a derechas y su subárbol derecho es un AVL,
   se ejecuta una rotación a la izquierda-derecha. De este modo, el nodo  queda 
   reequilibrado tras la operación. 
   La operación tiene un coste en tiempo constante.
*/
template<typename S, typename V, template <typename> typename P> void rotIzqDer(colSegm<S, V, P>::unaPareja* n){
    typename colSegm<S, V, P>::unaPareja* aux = n->hijIzq->hijDer;

    /* Como el subárbol izquierdo del nodo n es pesado a derechas, la altura de este
       viene dada por la longitud del recorrido desde su raíz (el hijo izquierdo de n, nIzq) 
       hasta una hoja de su subárbol derecho. Este subárbol derecho será un AVL con raiz nIzqDer,
       siendo la altura de su subárbol izquierdo (sarb2) y/o derecho (sarb3) es igual o menor en una unidad
       a la del subárbol izquierdo de nIzq sarb1 (pues la máxima longitud del camino desde nIzqDer hasta una hoja
       de uno de sus subárboles será una unidad mayor a la altura de sarb1, y si en el otro no se da el caso dicha
       longitud será igual a la altura de sarb1 por ser el subárbol con raíz en nIzqDer un AVL). 
       Con un mismo razonamiento, se llega a que la altura del subárbol derecho de n sarb4 será
       siempre igual o mayor en una unidad a la de sarb2 o/y sarb3, pues son esto subárboles los que determinaran
       la altura del subárbol izquierdo de n. Por tanto, también se puede concluir que la altura de sarb1 y sarb4 
       son iguales.
    */
    n->hijIzq->hijDer = aux->hijIzq; // El hijo derecho de nIzq pasa a ser la raíz de sarb2
    aux->hijIzq = n->hijIzq; // El antiguo hijo derecho de nIzq (nIzqDer) pasa a ser su padre
    n->hijIzq = aux->hijDer; // La raíz de sarb3 pasa a ser hijo izquierdo de n;
    aux->hijDer = n; // n pasa  a ser hijo derecho de nIzqDer
    n = aux; // nIzqDer será la raíz del nuevo árbol.

    /* El nuevo árbol será perfectamente equilibrado, puesto que los subárboles sarb2 y sarb3 tienen 
       como máximo la altura de sarb1 y sarb4, y como mínimo una unidad menor; y dado que los subárboles
       izquierdo y derecho de la nueva raíz tienen en su recorrido el camino desde sus respectivas raíces
       hasta un nodo hoja de sarb1 o sarb4, respectivamente. 
       Pero hay que actualizar el factor de equilibro de las raíces de estos subárboles en función de las
       condiciones iniciales.
    */
    if(n->factorEq == -1){
        /* La altura del sarb2 es la máxima, igual a la de sarb1;
           mientras que la altura de sarb3 es mínima, una unidad menor que la de sarb4.
        */
        // hijo izquierdo de raíz tiene como subárbol izquierdo a sarb1 y subárbol derecho a sarb2
        n->hijIzq->factorEq = 0; 
        // hijo derecho de raíz tiene como subárbol izquierdo a sarb3 y subárbol derecho a sarb4
        n->hiDer->factorEq = 1;
    }
    if(n->factorEq == 0){
        /* Las alturas de sarb2 y sarb3 son máximas e iguales a las de sarb1 y sarb4.
        */
        // hijo izquierdo de raíz tiene como subárbol izquierdo a sarb1 y subárbol derecho a sarb2
        n->hijIzq->factorEq = 0; 
        // hijo derecho de raíz tiene como subárbol izquierdo a sarb3 y subárbol derecho a sarb4
        n->hiDer->factorEq = 0;
    } 
    else{
        /* La altura del sarb2 es la mínima, una unidad menor que la de sarb1;
           mientras que la altura de sarb3 es máxima, igual a la de sarb4.
        */
        // hijo izquierdo de raíz tiene como subárbol izquierdo a sarb1 y subárbol derecho a sarb2
        n->hijIzq->factorEq = -1; 
        // hijo derecho de raíz tiene como subárbol izquierdo a sarb3 y subárbol derecho a sarb4
        n->hiDer->factorEq = 0;
    } 
    n->factorEq = 0;     
}

/* Dado un puntero a nodo n que es muy pesado a derechas (Feq = 2), cuyo
   subárbol derecho es un AVL pesado a derechas y su subárbol izquierdo es otro AVL,
   se ejecuta una rotación a la derecha. De este modo, el nodo queda reequilibrado tras la operación. 
   La operación tiene un coste en tiempo constante.
*/
template<typename S, typename V, template <typename> typename P> void rotDer(colSegm<S, V, P>::unaPareja* n){
    typename colSegm<S, V, P>::unaPareja* aux = n->hijDer;

    /* Como el subárbol derecho del nodo n es pesado a derechas, la altura de este
       viene dada por la longitud del recorrido desde su raíz (el hijo derecho de n) 
       hasta una hoja del subárbol derecho sarb1 de esta raíz. Al ser el nodo n muy 
       pesado a derecho, el sarb1 tendrá la misma altura que la longitud del recorrido
       desde n hasta una hoja de su subárbol izquierdo sarb3. Además, al ser la altura del subárbol
       izquierdo del hijo derecho sarb2 una unidad  menor que la de sarb1, se tiene que
       la altura de sarb2 es igual que la de sarb3.
    */

    n->hijDer = aux -> hijIzq; // El hijo derecho de n pasa a ser la raíz de sarb2.
    n->factorEq = 0; // altura de sarb2 es igual a la de sarb3, n pasa a estar perfectamente equlibrado.
    aux -> hijizq = n; // El hijo derecho de n pasa a ser su padre.
    n = aux;
    /* altura de sarb2 es igual a la longitud desde A hasta un nodo hoja de sarb3 que determina
       la altura del subárbol izquierdo del nuevo n (antiguo hijo izquierdo), por lo que n pasa
       a estar perfectamente equilibrado.
    */
    n->factorEq = 0; 
}

/* Dado un puntero a nodo n que es muy pesado derechas (Feq = 2), cuyo
   subárbol derecho es un AVL pesado a izquierdas y su subárbol
   izquierdo es otro AVL, se ejecuta una rotación a la izquierda-derecha. 
   De este modo, el nodo  queda reequilibrado tras la operación. 
   La operación tiene un coste en tiempo constante.
*/
template<typename S, typename V, template <typename> typename P> void rotDerIzq(colSegm<S, V, P>::unaPareja* n){
    typename colSegm<S, V, P>::unaPareja* aux = n->hijDer->hijIzq;

    /* Como el subárbol derecho del nodo n es pesado a izquierdas, la altura de este
       viene dada por la longitud del recorrido desde su raíz (el hijo derecho de n, nDer) 
       hasta una hoja de su subárbol izquierdo. Este subárbol izquierdo será un AVL con raiz nDerIzq,
       siendo la altura de su subárbol izquierdo (sarb3) y/o derecho (sarb2) igual o menor en una unidad
       a la del subárbol derecho de nIzq sarb1 (pues la máxima longitud del camino desde nDerIzq hasta una hoja
       de uno de sus subárboles será una unidad mayor a la altura de sarb1, y si en el otro no se da el caso dicha
       longitud será igual a la altura de sarb1 por ser el subárbol con raíz en nDerIzq un AVL). 
       Con un mismo razonamiento, se llega a que la altura del subárbol izquierdo de n sarb4 será
       siempre igual o mayor en una unidad a la de sarb2 o/y sarb3, pues son estos subárboles los que determinarán
       la altura del subárbol izquierdo de n. Por tanto, también se puede concluir que las alturas de sarb1 y sarb4 
       son iguales.
    */
    n->hijDer->hijIzq = aux->hijDer; // La raíz de sarb3 pasa a ser el hijo izquierdo de nDer 
    aux->hijDer = n->hijDer; // El antiguo hijo izquierdo de nDer (nDerIzq) pasa a ser su padre
    n->hijDer = aux->hijIzq; // La raíz de sarb2 pasa a ser hijo derecho de n;
    aux->hijIzq = n; // n pasa  a ser hijo izquierdo de nDerIzq
    n = aux; // nDerIzq será la raíz del nuevo árbol.

    /* El nuevo árbol será perfectamente equilibrado, puesto que los subárboles sarb2 y sarb3 tienen 
       como máximo la altura de sarb1 y sarb4, y como mínimo una unidad menor; y dado que los subárboles
       izquierdo y derecho de la nueva raíz tienen en su recorrido el camino desde sus respectivas raíces
       hasta un nodo hoja de sarb4 o sarb1, respectivamente. 
       Pero hay que actualizar el factor de equilibro de las raíces de estos subárboles en función de las
       condiciones iniciales.
    */
    if(n->factorEq == -1){
        /* La altura del sarb2 es la mínima, una unidad menor que la de sarb1;
           mientras que la altura de sarb3 es máxima, igual a la de sarb4.
        */
        // hijo izquierdo de raíz tiene como subárbol izquierdo a sarb4 y subárbol derecho a sarb3
        n->hijIzq->factorEq = 0; 
        // hijo derecho de raíz tiene como subárbol izquierdo a sarb2 y subárbol derecho a sarb1
        n->hiDer->factorEq = 1;
    }
    if(n->factorEq == 0){
        /* Las alturas de sarb2 y sarb3 son máximas e iguales a las de sarb1 y sarb4.
        */
        // hijo izquierdo de raíz tiene como subárbol izquierdo a sarb4 y subárbol derecho a sarb3
        n->hijIzq->factorEq = 0; 
        // hijo derecho de raíz tiene como subárbol izquierdo a sarb2 y subárbol derecho a sarb1
        n->hiDer->factorEq = 0;
    } 
    else{
        /* La altura del sarb2 es la máxima, igual a la de sarb1;
           mientras que la altura de sarb3 es mínima, una unidad menor que la de sarb4.
        */
        // hijo izquierdo de raíz tiene como subárbol izquierdo a sarb4 y subárbol derecho a sarb3
        n->hijIzq->factorEq = -1; 
        // hijo derecho de raíz tiene como subárbol izquierdo a sarb2 y subárbol derecho a sarb1
        n->hiDer->factorEq = 0;
    } 
    n->factorEq = 0; 
}

/* Si en el AVL con raíz en rz (que apunta a la raíz de un árbol no vacío) no hay ningún nodo con segmento 
   igual o solapado con sg, se añade al árbol una nueva hoja cuyo segmento y valor forman el par (sg, v), 
   de manera que el árbol sigue siendo un AVL trás la adición. Además, se devuelve exito con valor de verdadero. 
   En caso contrario, exito toma el valor de falso y no se añade ningún nodo en el AVL.
   El coste en tiempo de la operación es lineal en el número de nodos del árbol con rz como raíz, puesto
   que ha que comprobar el solape con cada uno de ellos. La variable booleana altMod indica si la altura del
   subárbol en el que se ha buscado o producido la adición se ha modificado y al final actualiza este análisis
   para el árbol con raíz en rz.
*/
template<typename S, typename V, template <typename> typename P> void anyadirRec(const S& sg, const V& v, colSegm<S, V, P>::UnaPareja* rz,
     bool& altMod, bool& exito){
    if(anterior(sg, rz->segmento) || !solapados(sg, rz->segmento)){
        /* Si el segmento sg es anterior al de rz y no solapan, se tendría
           que buscar la adición en el subárbol izquierdo de rz, y además
           comprobar que no hay solapamiento con ningún segmento de un nodo 
           del subárbol derecho.
        */ 
        bool solape = seSolapaRec(sg, rz -> hijDer);
        if(!solape){
            // No hay solape con el subárbol derecho
            if(rz->hijIzq == nullptr){
                /* Si rz no tiene hijo izquierdo, como no hay solapamiento
                   con ningún nodo, se procede a añadir una hoja con el par
                   (sg, v) como elemento.
                */
                rz->hijIzq->segmento = sg;
                rz->hijIzq->valor = v;
                rz->hijIzq->hijDer = nullptr;
                rz->hijIzq->hijIzq = nullptr;
                rz->hijIzq->factorEq = 0; 
                /* El árbol con raíz en el nuevo hijo izquierdo de rz ha pasado
                   der ser vacío a no serlo. En este sentido, se ha modificado su altura.
                */
                altMod = true;
                exito = true;
            }
            else{
                // El subárbol de rz no es vacío, se sigue buscando adición en este.
                anyadirRec(sg, v, rz -> hijIzq);
            }
            if(altMod){
                /* Si la altura de su subárbol izquierdo se ha visto modificada en el proceso  
                   (se ha llevado a cabo la adición ), hay que actualizar el factor de equilibrio 
                    y posiblemente reequilibrar para mantener la condición de AVL. 
                */
                if(rz->factorEq == 1){
                    /* Si el árbol era pesado a derechas, al aumentar de altura
                       pasa a ser equilibrado, pero su altura sigue siendo la misma,
                       esta no se ve modificada.
                    */
                    rz->factorEq == 0;
                    altMod = false;
                }
                else if(rz->factorEq == 0){
                    /* En caso de que el árbol fuese equilibrado, la adición en su
                       subárbol izquierdo hace que pase a ser pesado a izquierdas.
                    */
                    rz->factorEq = -1;
                }
                else{
                    /* Si el árbol con rz como raíz era pesado a izquierdas, se produce
                       un desequilibrio al ser el factor de equilibrio igual a -2.
                    */
                    if(rz->hijIzq->factorEq == -1){
                        /* Siendo sus dos subárboles AVL`s (si no se hubiese producido
                           un reequilibrio), como el subárbol izquierdo es pesado a 
                           izquierdas se realiza la rotación a izquierdas.
                        */
                        rotIzq(rz);
                    }
                    else{
                        /* Ambos subárboles AVL's, y árbol izquierdo tiene que ser
                           pesado a derechas, por lo que se reequilibra con una rotación 
                           izquierda-derecha.
                        */
                        rotIzqDer(rz);
                    }
                    altMod = false;
                }
            }        
        }
    }
    else if(anterior(rz->segmento, sg) || !solapados(sg, rz->segmento)){
        bool solape = seSolapaRec(sg, rz -> hijIzq);
        if(!solape){
            if(rz->hijDer == nullptr){
                rz->hijDer->segmento = sg;
                rz->hijDer->valor = v;
                rz->hijDer->hijDer = nullptr;
                rz->hijDer->hijIzq = nullptr;
                rz->hijDer->factorEq = 0; 
                altMod = true;
                exito = true;
            }
            else{
                anyadirRec(sg, v, rz -> hijDer);
            }
            if(altMod){
                if(rz->factorEq == 1){
                    if(rz-hijDer->factorEq == 1){
                        rotDer(rz);
                    }
                    else{
                        rotDerIzq(rz);
                    }
                    altMod = false;
                }
                else if(rz->factorEq == 0){
                    rz->factorEq = -1;
                }
                else{
                    rz->factorEq = 0;
                    altMod = false;
                }
            }        
        }
    }
    else{
        // Se ha encontrado un nodo con mismo segmento que sg o solapamiento en el recorrido de búsqueda.
        exito = false;
    }
}


/* Devuelve verdad si y solo si el AVL que tiene como raíz a rz no tiene ningún nodo cuyo 
   segmento solape con sg.
   El coste temporal de la operación es lineal respecto al número de elementos, puesto que 
   la solapación no tiene por qué tener una relación clara con el criterio de ordenación.
*/
template<typename S, typename V, template <typename> typename P> bool seSolapaRec(const S& sg, colSegm<S, V, P>::unaPareja* rz){
    if(cs.raiz != nullptr){
        /* Si la raíz no apunta al puntero nulo (arbol no vacío), se procede a comprobar
           que no haya solapamiento con la raíz.
        */
        if(!solapados( rz -> segmento)){
            /* Si no hay solape con el segmento de la raíz, se comprueba que 
               no exita solapamiento con el subárbol izquierdo, del que es raíz
               su hijo izquierdo; y con el subárbol derecho, del que es es raíz 
               su hijo derecho.
            */
            return seSolapa(sg, rz -> hijIzq) || seSolapa(sg, rz -> hijDer);
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

/* Si en el AVL con raíz en rz hay algún elemento con segmento igual a sg, sea (sg, v'), modifica dicho nodo de manera
   que este sea el resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se de vuelve falso y no se modifica ningún nodo.
   El coste temporal será logarítmico respecto al número de nodos en el árbol, al ser este ordenado
   y su altura también logarítmica respecto al número de nodos.
*/
template<typename S, typename V, template <typename> typename P> bool actualizarRec(const S& sg, const V& v, colSegm<S, V, P>::unaPareja* rz){
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
            // Se ha encontrado un nodo con segmento igual, por lo que actualiza su valor y devuelve verdadero.
            rz -> valor = v;
            return true; 
        }
    }
}

/* Devuelve verdad si y solo si en el AVL con rz como raíz hay algún nodo con segmento igual a sg.
   El coste temporal será logarítmico respecto al número de nodos en el árbol, al ser este ordenado
   y su altura también logarítmica respecto al número de nodos.
*/
template<typename S, typename V, template <typename> typename P> bool estaRec(const S& sg, colSegm<S, V>::unaPareja* rz){
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

/* Si en el AVL con raíz en rz hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el valor que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
   El coste temporal será logarítmico respecto al número de nodos en el árbol, al ser este ordenado
   y su altura también logarítmica respecto al número de nodos.
*/
template<typename S, typename V, template <typename> typename P> bool obtenerRec(const S& sg, const colSegm<S, V>::unaPareja* rz, V& v){
    if(rz == nullptr){
        // Si el árbol es vacío, no hay ningún nodo con segmento igual a sg.
        return false;
    }
    else{
        if(anterior(sg, rz->segmento)){
            return obtenerRec(sg, rz->hijIzq); // Obtención en el subárbol izquierdo
        }
        else if(anterior (rz->segmento, sg)){
            return obtenerRec(sg, rz->hijDer); // Obtención en el subárbol derecho.
        }
        else{
            // Se ha encontrado un nodo con segmento igual, por lo que asigna a v el valor del nodo y devuelve verdadero.
            v = rz->valor;
            return true; 
        }
    }
}

/* Si en el árbol no vacío con rz como raíz hay algún elemento con segmento igual a sg, modifica el árbol de manera
   que este siga manteniendo la condición de AVL pero se haya eliminado dicho nodo y devuelve en exito
   verdadero. En caso, contrario, no se modifica el árbol y exito toma el valor de falso.
   El coste temporal será logarítmico respecto al número de nodos en el árbol, al ser este ordenado
   y su altura también logarítmica respecto al número de nodos. La variable booleana altMod indica si la altura del
   subárbol en el que se ha buscado o producido la adición se ha modificado y al final actualiza este análisis
   para el árbol con raíz en rz.
*/
template<typename S, typename V,  template <typename> typename P> void borrarRec(const S& sg, colSegm<S, V, P>::unaPareja* rz, bool& exito){
    if(anterior(sg, rz->segmento)){
        if(rz->hijIzq == nullptr){
            exito = false;
        }
        else{
            borrarRec(sg, rz->hijIzq, exito);
        }
        if(exito){
            /* Si se ha podido borrar, hay que actualizar el factor de equilibrio 
               y posiblemente reequilibrar para mantener la condición de AVL. 
            */
            if(rz->factorEq == 1){
                if(rz-hijDer->factorEq == 1){
                    rotDer(rz);
                }
                else{
                    rotDerIzq(rz);
                }
            }
            else if(rz->factorEq == 0){
                rz->factorEq = -1;
            }
            else{
                rz->factorEq = 0;
            }
        }            
    }
    else if(anterior(rz->segmento, sg)){
        if(rz->hijDer == nullptr){
            exito = false;
        }
        else{
            borrarRec(sg, rz->hijDer, exito);
        }
        if(exito){
            /* Si se ha podido borrar, hay que actualizar el factor de equilibrio 
               y posiblemente reequilibrar para mantener la condición de AVL. 
            */
            if(rz->factorEq == -1){
                if(rz-hijIzq->factorEq == -1){
                    rotIzq(rz);
                }
                else{
                    rotIzqDer(rz);
                }
            }
            else if(rz->factorEq == 0){
                rz->factorEq = -1;
            }
            else{
                rz->factorEq = 0;
            }
        }          
    }
    else{ // Se ha encontrado un nodo con segmento igual a sg
        if(rz->hijIzq == nullptr){
            /* Si rz no tiene hijo izquierdo, eliminamos rz y hacemos
               que el hijo derecho (forme parte de un subárbol vacío o no) 
               tome su posición. Al ser menor que el padre de rz el árbol 
               seguirá siendo ordenado, y si el subárbol está vacío  el padre 
               de rz no tendrá hijos en ese subárbol, pero será ordenado.
            */
           typename colSegm<S, V>::unaPareja* aux = rz;
           rz = rz->hijDer;
           delete rz;
           exito = true;
        }
        else if(rz->hijDer == nullptr){
            /* Si el subárbol izquierdo no esta vacío pero el derecho sí,
               el hijo izquierdo pasará a tomar la posición de rz, pues al
               ser anterior que rz seguirá siéndolo del padre. 
            */
           typename colSegm<S, V>::unaPareja* aux = rz;
           rz = rz->hijIzq;
           delete rz;
           exito = true;  
        }
        else{
            /* Si ni el subárbol izquierdo ni el derecho de rz son vacíos, se procede
               a eliminar rz y se sustituye por el nodo del subárbol izquierdo con segmento 
               posterior a todos los demás. Se cumple además que será anterior a los segmentos del
               padre y de todos los nodos del subárbol derecho de rz por ser anterios al segmento de
               rz.
            */
            borrarNoVacios(rz, exito);
        }
    }
}

/* Dado la raíz rz de un AVL, 
*/
void borrarNoVacios(colsegm<S, V>::unaPareja* rz, exito){

}

// IMPLEMENTACIÓN DE LAS OPERACIONES DEL TAD COLECCIÓN SEGMENTADA
/* Devuelve una colección vacía cs. 
   El coste temporal de la operación es constante.
*/
template<typename S, typename V> void crear(colSegm<S, V, P>& cs){
    cs.raiz = nullptr;
    crearVacia(cs.iter);
    cs.tam = 0;
}

/* Devuelve el número de elementos que hay en la colección cs.
   El coste temporal de la operación es constante.
*/
template<typename S, typename V, template <typename> typename P> unsigned tamanyo(const colSegm<S, V>& cs){
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
*  que solo se recorra una vez, pero no es logarítmico dado que hay que recorrer todos los nodos para comprobar
   que no hay solape.
*/
template<typename S, typename V, template <typename> typename P> void anyadir(const S& sg, const V& v, colSegm<S, V, P>& cs){
    bool altMod = false, exito;
    if(!esVacia(cs)){
        anyadirRec(sg, v, cs.raiz, altMod, exito);
        if(exito){
            cs.tam++;
        }
    }
}    

/* Si en cs hay algún elemento con S igual a sg, sea (sg, v'), modifica la colección segmentada cs de manera
   que esta es la resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se de vuelve falso y cs no se modifica.
   El coste temporal será logarítmico respecto al número de elementos en la colección, al ser esta un árbol ordenado
   y su altura también logarítmica respecto al número de nodos.
*/
template<typename S, typename V, template <typename> typename P> bool actualizar(const S& sg, const V& v, colSegm<S, V, P>& cs){
    return actualizarRec(sg, v, cs.raiz);
}

/* Devuelve verdad si y solo si en cs hay algún elemento con S igual a sg.
   El coste temporal será logarítmico respecto al número de elementos en la colección, al ser esta un árbol ordenado
   y su altura también logarítmica respecto al número de nodos.
*/
template<typename S, typename V, template <typename> typename P> bool esta(const S& sg, const colSegm<S, V>& cs){
    return estaRec(sg, cs.raiz);
}


/* Si en cs hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el dato V que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
   El coste temporal será logarítmico respecto al número de elementos en la colección, al ser esta un árbol ordenado
   y su altura también logarítmica respecto al número de nodos.
*/
template<typename S, typename V, template <typename> typename P> bool obtener(const S& sg, const colSegm<S, V>& cs, V& v){
    return obtenerRec(sg, cs.raiz, v);
}

/* Devuelve verdad si y solo si en cs hay algún elemento cuyo segmento solape con sg
   El coste temporal de la operación es lineal respecto al número de elementos, puesto que 
   la solapación no tiene por qué tener una relación clara con el criterio de ordenación.
*/
template<typename S, typename V, template <typename> typename P> bool seSolapa(const S& sg, const colSegm<S, V, P>& cs){
    return seSolapaRec(sg, cs.raiz);    
}


/* Si en cs hay algún elemento con S igual a sg, modifica la colección cs de manera
   que está sea la colección resultante de eliminar ese elemento de la colección cs. En 
   caso, contrario, no se modifica cs.
   El coste temporal será logarítmico respecto al número de elementos en la colección, al ser esta un árbol ordenado
   y su altura también logarítmica respecto al número de nodos.
*/
template<typename S, typename V,  template <typename> typename P> void borrar(const S& sg, colSegm<S, V, P>& cs){
    bool exito;
    if(!esVacia(cs)){
        borrarRec(sg, cs.raiz, exito);
        if(exito){
            cs.tam--;
        }
    }
}

/* Modifica cs inicializando el iterador para recorrer los elementos de la colección, de forma que el siguiente
   elemento a visitar sea el que tiene un S anterior a los de todos los demás elementos de la
   colección (situación de no haber visitado ningún elemento). El coste en tiempo de la operación será logarítmico
   respecto al número de nodos dado que la altura también lo es.
*/
template<typename S, typename V,  template <typename> typename P> void iniciarIterador(colSegm<S, V, P>& cs){
    typename colSegm<S, V, P>::unaPareja* aux = cs.raiz;
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
template<typename S, typename V,  template <typename> typename P> bool haySiguiente(const colSegm<S, V, P>& cs){
    return esVacia(cs.iter);
}

/* Si queda algún elemento por visitar, devuelve verdadero, se le asigna a sg y v el S y V del siguiente
   elemento a visitar con el iterador de la colección cs (elemento no visitado con S anterior al resto de los no visitados)
   y se modifica cs avanzando el iterador para que se pueda visitar el siguiente elemento. En caso contrario, devuelve falso.
*/
template<typename S, typename V,  template <typename> typename P> bool siguiente(colSegm<S, V, P>& cs, S& sg, V& v){
    bool exito = haySiguiente(cs);
    if(exito){
        typename colSegm<S, V, P>::unaPareja* aux;
    
        /* El siguiente elemento a visitar es la cima de la pila iterador
           de la colección, por lo que se toma el valor del segmento y valor 
           del nodo de la pareja cuyo puntero se almacena y se elimina este. 
        */
        cima(cs.iter, aux);
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
            aux = aux -> hijIzq;
        }
    }
    return exito;
}
