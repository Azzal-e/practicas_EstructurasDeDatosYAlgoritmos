/*********************************************************************************************\
 * Estructuras de Datos y Algoritmos. Práctica 3
 * Autores: Athanasios Usero Samarás [NIP: 839543] y Alex Ionut Matei [NIP: 874031]
 * Ultima revisión: 14-11-2023
 * Resumen: Fichero de encabezado con la declaración e implementación del TAD genérico
 *          colección segmentada.
\*********************************************************************************************/

#ifndef COLSEGMENTADASTAD_HPP
#define COLSEGMENTADASTAD_HPP

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


// DECLARACIÓN DEL TAD GENÉRICO COLECCIÓN SEGMENTADA

template<typename S, typename V> struct colSegm{
    friend void crear<S, V>(colSegm<S, V>& cs);
    friend unsigned tamanyo<S, V>(const colSegm<S, V>& cs);
    friend bool esVacia<S, V>(const colSegm<S, V>& cs);
    friend void anyadir<S, V>(const S& sg, const V& v, colSegm<S, V>& cs);
    friend bool actualizar<S, V>(const S& sg, const V& v, colSegm<S, V>& cs);
    friend bool esta<S, V>(const S& sg, const colSegm<S, V>& cs);
    friend bool obtener<S, V>(const S& sg, const colSegm<S, V>& cs, V& v);
    friend bool seSolapa<S, V>(const S& sg, const colSegm<S, V>& cs);
    friend void borrar<S, V>(const S& sg, colSegm<S, V>& cs);
    friend void iniciarIterador<S, V>(colSegm<S, V>& cs);
    friend bool haySiguiente<S, V>(const colSegm<S, V>& cs);
    friend bool siguiente<S, V>(colSegm<S, V>& cs, S& sg, V& v);

    private:
    /* Internamente, el TAD colección segmentada se implementa como una lista enlazada con punteros y ordenada por el criterio de ordenación de segmentos.
       Cada elemento de la lista es un nodo unaPareja, registro que agrupa dos datos de tipo segmento (S) y valor (V) que forman el elemento (S, V) de la lista y
       un puntero sig a otro nodo, que será aquel cuyo segmento sea inmediatamente posterior al primero. 
    */
     struct unaPareja{
        S segmento;
        V valor;
        unaPareja* sig;
     };
     /* Consecuentemente, una colección segmentada se define como la agrupación de dos punteros, uno que apunta al primer elemento de la lista (primero) y otro que
        sirve para las operaciones del propio iterador; y de un entero tam con el número de elementos de la lista.
     */
     unaPareja* primero;
     int tam;
     unaPareja* iter;     
};


#endif

/* Devuelve una colección vacía cs. 
*/
template<typename S, typename V> void crear(colSegm<S, V>& cs){
    cs.primero = nullptr;
    cs.iter = nullptr;
    cs.tam = 0;
}

/* Devuelve el número de elementos que hay en la colección cs.
*/
template<typename S, typename V> unsigned tamanyo(const colSegm<S, V>& cs){
    return cs.tam;
}

/* Devuelve verdad si y solo si cs no contiene ningún elemento.
*/
template<typename S, typename V> bool esVacia(const colSegm<S, V>& cs){
    return cs.tam == 0;
}

/* Si en cs no hay ningún elemento con segm igual o solapado con sg, modifica cs de manera
*  que esta es una colección igual a la resultante de añadir el elemento (sg, v) en la colección.
*  El coste de la operación es lineal respecto al tamaño de la lista dado que está implementada de manera
*  que solo se recorra una vez.
*/
template<typename S, typename V> void anyadir(const S& sg, const V& v, colSegm<S, V>& cs){
    if(esVacia(cs)){ // Colección vacía, se procede a añadir el elemento (sg, v) como primero de la lista
        cs.primero = new typename colSegm<S, V>::unaPareja;
        cs.primero->sig = nullptr;
        cs.primero->segmento = sg;
        cs.primero->valor = v;
        cs.tam++;
    }
    else{ // Colección no vacía, se comprueba y efectua en caso de ser posible la adición
        typename colSegm<S, V>::unaPareja* aux = cs.primero, *nGuard;
        if(pAnterior(sg, cs.primero->segmento)){ // sg es anterior al segmento del primer elemento.
            // El bucle itera mientras no haya solapamiento con ningún elemento, y si se llega al final al último elemento finaliza.
            while(aux->sig != nullptr && !solapados(sg, aux->segmento)){ 
                aux = aux->sig;
            }
            /* Si el elemento no es el último de la lista, se debe a que ha habido solapamiento; y si se ha llegado al final se debe
            *  comprobar si ha habido solapamiento con el último elemento al no haberse comprobado al iterar en bucle.
            */
            if(aux->sig == nullptr && !solapados(sg, aux->segmento)){  // Adición como primer elemento de la lista.
                aux = cs.primero;
                cs.primero = new typename colSegm<S, V>::unaPareja;
                cs.primero->segmento = sg;
                cs.primero->valor = v;
                cs.primero->sig = aux;
                cs.tam++;
            }
        }
        else{ // No es menor que todos los demás elementos de la lista (en cuanto a segmento), por lo que se busca su posible adición
            /* Se recorre la colección hasta el final, siempre y cuando no haya solapamientos, y hasta encontrar un posible punto de inserción.
               Cuando se encuentra un primer segmento que no es anterior a sg, en caso de este sea además posterior, se ha encontrado un 
               punto de adición antes de este elemento posterior, pues sg será posterior a todos los anteriores segmentos y anterior a todos 
               los posteriores.
            */
            while(aux->sig != nullptr && pAnterior(aux->sig->segmento, sg) && !solapados(sg, aux->segmento)){ 
                aux = aux->sig;
            }
            /* Si no se ha llegado al final ni ha habido solapamiento, y además sg no es igual al segmento de esa posición, 
               se ha encontrado un punto de inserción en posiciones intermedias.
            */
            if(aux->sig != nullptr && !solapados(sg, aux->segmento) && !(aux->segmento == sg)){ 
                nGuard = aux; // Se almacena el elemento anterior al punto de inserción
                // Se comprueba que no haya solapamientos con el resto de elementos de la lista
                while(aux->sig != nullptr && !solapados(sg, aux->segmento)){ 
                aux = aux->sig;
                }
                /* Si se llega al final y no solapa con el útlimo elemento (no hay solapamientos), se añade el elemento (sg, v) 
                   entre el último elemento anterior de la colección y el primero posterior.
                */
                if(aux->sig == nullptr && !solapados(sg, aux->segmento)){ 
                    aux = new typename colSegm<S, V>::unaPareja;
                    aux->sig = nGuard->sig;
                    aux->valor = v;
                    aux->segmento = sg;
                    nGuard->sig = aux;
                    cs.tam++;
                }
            }
            // Se llega al final sin solapamientos, por lo que si sg es distinto al del último elemento, se inserta el elemento (sg, v) al final de la colección.
            else if(aux->sig == nullptr && !solapados(sg, aux->segmento) && !(sg == aux->segmento)){ 
                aux->sig = new typename colSegm<S, V>::unaPareja;
                aux = aux->sig;
                aux->sig = nullptr;
                aux->valor = v;
                aux-> segmento = sg;
                cs.tam++;
            }
        }
    }
}

/* Si en cs hay algún elemento con S igual a sg, sea (sg, v'), modifica la colección segmentada cs de manera
   que esta es la resultante de sustituir dicho elemento por (sg, v) en la colección cs y devuelve verdadero.
   En caso contrario se devuelve falso y cs no se modifica.
   El coste temporal se ve reducido aprovechando las propiedades de la lista ordenada, pero sigue aproximándose 
   a un coste lineal respecto al número de elementos para muchos casos.
*/
template<typename S, typename V> bool actualizar(const S& sg, const V& v, colSegm<S, V>& cs){
    // puntero auxiliar que apunta a un nodo para recorrer la colección
    typename colSegm<S, V>::unaPareja* aux = cs.primero;
    bool exito;

    if(!esVacia(cs)){
        /* Recorre mientras el segmento de la pareja apuntada por aux sea anterior a sg, o se llegue al final.
        Imponiendo que sea anterior reduce el coste temporal porque si no se llegaría siempre al final de la colección
        cuando se sabe que a partir de cierto punto sg no podrá ser igual al de ningún elemento (consecuencia de que la lista sea ordenada).
        */
        while(pAnterior(aux->segmento, sg) && aux->sig != nullptr){
            aux = aux->sig;
        }
        // variable que parametriza el éxito, pues si ambos segmentos no son iguales, el de la lista será posterior, y también todos los restantes.
        exito = (sg == aux -> segmento);   
        /* Si sg es igual al del dato apuntado por el puntero, se modifica el dato val de este asignándole v.
        */
        if(exito){
            aux->valor = v;
        } 
    }
    else{
        exito = false;
    }
    return exito; 


}

/* Devuelve verdad si y solo si en cs hay algún elemento con S igual a sg.
   El coste temporal se ve reducido aprovechando las propiedades de la lista ordenada, pero sigue aproximándose 
   a un coste lineal respecto al número de elementos para muchos casos.
*/
template<typename S, typename V> bool esta(const S& sg, const colSegm<S, V>& cs){
    typename colSegm<S, V>::unaPareja* aux = cs.primero;
    bool exito;

    if(!esVacia(cs)){    
        /* Recorre mientras el segmento de la pareja apuntada por aux sea anterior a sg, o se llegue al final.
        Imponiendo que sea anterior reduce el coste temporal porque si no se llegaría siempre al final de la colección
        cuando se sabe que a partir de cierto punto sg no podrá ser igual al de ningún elemento (consecuencia de que la lista sea ordenada).
        */
        while(pAnterior(aux->segmento, sg) && aux->sig != nullptr){ 
            aux = aux->sig;
        }
        exito = sg == aux->segmento; // Si ambos segmentos no son iguales, sg no lo será para ningún caso al ser los restantes elementos de sg posteriores.
    }
    else{
        exito = false;
    }
    return exito;
}


/* Si en cs hay algún elemento con segmento igual a sg, devuelve verdadero y le asigna a v el dato V que forma
   el elemento con dicho sg. En caso contrario contrario, se devuelve falso.
   El coste temporal se ve reducido aprovechando las propiedades de la lista ordenada, pero sigue aproximándose 
   a un coste lineal respecto al número de elementos para muchos casos.
*/
template<typename S, typename V> bool obtener(const S& sg, const colSegm<S, V>& cs, V& v){
    typename colSegm<S, V>::unaPareja* aux = cs.primero;
    bool exito;

    if(!esVacia(cs)){ // Lista no vacía
        /* Se recorre la colección mientras el segmento de la pareja apuntada por aux sea anterior a sg, o se llegue al final.
        Imponiendo que sea anterior reduce el coste temporal porque si no se llegaría siempre al final de la colección,
        cuando se sabe que a partir de cierto punto sg no podrá ser igual al de ningún elemento (consecuencia de que la lista sea ordenada).
        */
        while(pAnterior(aux->segmento, sg) && aux->sig != nullptr){
            aux = aux->sig;
        }
        // variable que parametriza el éxito, pues si ambos segmentos no son iguales, el de la lista será posterior, y también todos los restantes.
        exito = (sg == aux -> segmento);   
        if(exito){
            /* Si sg es igual al del dato apuntado por el puntero, se le asigna a v el valor del elemento de la lista.
            */
            v = aux->valor;
        } 
    }
    else{
        exito = false;
    }
    return exito;

}

/* Devuelve verdad si y solo si en cs hay algún elemento cuyo segm solape con sg
   El coste temporal de la operación es lineal respecto al número de elementos.
*/
template<typename segm, typename val> bool seSolapa(const segm& sg, const colSegm<segm, val>& cs){
    typename colSegm<segm, val>::unaPareja* aux = cs.primero;
    bool exito;

    if(!esVacia(cs)){
        /* Se recorre la lista hasta encontrar algún elemento cuyo segmento solape con sg o se llegue al final.
        */ 
        while(!solapados(sg, aux-> segmento) && aux->sig != nullptr){ 
            aux = aux->sig;
        }
        // Si cesa el bucle, se ha encontrado un elemento solapado o no (si alcanza el final y el segmento del últlimo elemento tampoco solapa con sg) 
        exito = solapados(sg, aux -> segmento); 
    }
    else{
        exito = false;
    }
    return exito;
}


/* Si en cs hay algún elemento con S igual a sg, modifica la colección cs de manera
   que está sea la colección resultante de eliminar ese elemento de la colección cs. En 
   caso, contrario, no se modifica cs.
*/
template<typename S, typename V> void borrar(const S& sg, colSegm<S, V>& cs){
    /* Se declaran dos punteros, uno aux para recorrer la lista y otro ant que apunta al nodo
    inmediatamente anterior, y que sirve para posiblitar la eliminación de un elemento y distinguir
    el caso en el que se elimina el primer elemento de cs.
    */
    typename colSegm<S, V>::unaPareja* ant = nullptr, *aux = cs.primero;

    if(!esVacia(cs)){
        /* Se recorre la colección mientras el segmento de la pareja apuntada por aux sea anterior a sg, o se llegue al final.
       Imponiendo que sea anterior reduce el coste temporal porque si no se llegaría siempre al final de la colección
       cuando se sabe que a partir de cierto punto sg no podrá ser igual al de ningún elemento (consecuencia de que la lista sea ordenada).
       */
        while(pAnterior(aux->segmento, sg) && aux->sig != nullptr){ 
            ant = aux;
            aux = aux->sig;
        }
        if(sg == aux->segmento){ // Existe un elemento con segmento igual sg
            if(ant == nullptr){ // Se elimina el primer elemento de la colección
                cs.primero = aux-> sig;
                delete(aux);
            }
            else{ // se elimina un elemento en posiciones intermedias o al final
                ant->sig = aux->sig;
                delete(aux);
            }
            cs.tam--;
        }
    }
}

/* Modifica cs inicializando el iterador para recorrer los elementos de la colección, de forma que el siguiente
   elemento a visitar sea el que tiene un S anterior a los de todos los demás elementos de la
   colección (situación de no haber visitado ningún elemento).
*/
template<typename S, typename V> void iniciarIterador(colSegm<S, V>& cs){
    cs.iter = cs.primero;
}

/* Devuelve verdad si queda algún elemento por visitar con el iterador de la colección cs, devuelve
   falso si ya se ha visitado el último elemento.
*/
template<typename S, typename V> bool haySiguiente(const colSegm<S, V>& cs){
    return cs.iter != nullptr;
}

/* Si queda algún elemento por visitar, devuelve verdadero, se le asigna a sg y v el S y V del siguiente
   elemento a visitar con el iterador de la colección cs (elemento no visitado con S anterior al resto de los no visitados)
   y se modifica cs avanzando el iterador para que se pueda visitar el siguiente elemento. En caso contrario, devuelve falso.
*/
template<typename S, typename V> bool siguiente(colSegm<S, V>& cs, S& sg, V& v){
    bool exito = haySiguiente(cs);
    if(exito){ // Primero se asigna y después se avanza (si no nunca se obtendría el primer elemento y se trataría de obtener uno después del final).
        sg = cs.iter-> segmento;
        v = cs.iter-> valor;
        cs.iter = cs.iter->sig;
    }
    return exito;
}
