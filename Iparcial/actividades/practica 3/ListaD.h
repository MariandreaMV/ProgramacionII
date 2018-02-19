#ifndef LISTAD_H
#define LISTAD_H
#include <iostream>
#include "Nodo.h"

template<class T>
class ListaD{
	
	private:
		
		Nodo<T>* cab; 
		Nodo<T>* fin; 
		
		bool DOBLE; 
		bool CIRCU;
		int size; 
	
		Nodo<T>* getElemento( int& ); 
		
	public:
		
		static const int AGRE_INICIO = 1; // agregar al inicio
		static const int AGRE_FIN = 2; // agregar al final
		static const int AGRE_CRE = 3; // agregar en orden creciente
		static const int AGRE_DECRE = 4; // agregar en orden decreciente
		static const int BUSCAR_POS_CRE = -1; // buscar posicion en orden creciente 
		static const int BUSCAR_POS_DECRE = 1; // buscar posicion en orden decreciente   
		static const int BUSCAR_ELEMENTO = 0; // buscar elemento 
		static const int ELIM_INICIO = -1; // eliminar al incio
		static const int ELIM_ELEMENTO = 0; // eliminar elemento(buscandolo) 
		static const int ELIM_FINAL = 1; // eliminar al final
		

		ListaD(){
		
			this->cab = this->fin = NULL; // cab y fin a NULL
			this->DOBLE = this->CIRCU = false; // atributos de tipo de lista a false
			this->size = 0; // tamaño de la lista
		} // fin del constructor 
		
		ListaD( bool doble, bool circu ){
		
			this->cab = this->fin = NULL; // cab y fin a NULL
			this->DOBLE = doble; this->CIRCU = circu; // atributos tipo de lista
			this->size = 0; // tamaño de la lista
		} // fin del constructor 
		
		~ListaD(); 
		Nodo<T>* getCab() const; 
		Nodo<T>* getFin() const; 
		int getSize() const; 
		Nodo<T>* getElemento_nodo( int );
		T* getElemento_info( int ); 
		bool isDoble() const; 
		bool isCircu() const;
		bool isVacia() const; 
		Nodo<T>* buscar( T*, int tipo = BUSCAR_ELEMENTO, Nodo<T>** antes = NULL ) const; 
		int agregar( T*, int pos = AGRE_CRE, bool repeticion = true );
		int eliminar( int tipo = ELIM_FINAL, T* info = NULL ); 
		bool eliminarLista(); 
		void imprimir() const;
		void imprimir( bool ) const; 
}; // fin de ListaD


template<class T> ListaD<T>::~ListaD(){

	this->eliminarLista(); // elimina la lista
} // fin del destructor

template<class T> Nodo<T>* ListaD<T>::getCab() const{
	
	return this->cab; // cab de la lista
} // fin de getCab


template<class T> Nodo<T>* ListaD<T>::getFin() const{
	
	return this->fin; // fin de la lista
} // fin de getFin


template<class T> int ListaD<T>::getSize() const{
	
	return this->size; // tamaño de la lista
} // fin de size


template<class T> Nodo<T>* ListaD<T>::getElemento( int& indice ){
	
	Nodo<T>* recor = this->cab; // recor empieza en cab 
	
	// si el indice es negativo o es igual o mayor al tamaño de la lista
	if( indice < 0 || indice >= this->size )
		return NULL; // se retorna NULL
	
	
	// recorre la lista hasta el indice especificado
	for( int i = 0; i < indice; i++ )
		recor = recor->getLink_suc(); // recor sera su sucesor
	
	
	return recor; // retorna Nodo
} // fin de getElemento


template<class T> Nodo<T>* ListaD<T>::getElemento_nodo( int indice ){
	
	// obtengo el Nodo<T> en el indice especificado
	Nodo<T>* elemento = this->getElemento( indice );
	return elemento; // retorna Nodo<T>*
} // fin de getElemento_nodo


template<class T> T* ListaD<T>::getElemento_info( int indice ){
	
	// obtengo el Nodo<T> en el indice especificado
	Nodo<T>* elemento = this->getElemento( indice );
	
	if( elemento )
		return elemento->getInfo();
	else
		return NULL;
} // fin de getElemento_nodo

template<class T> bool ListaD<T>::isCircu() const{
	
	return this->CIRCU; // aributo de tipo de lista
} // fin de isCircu

template<class T> bool ListaD<T>::isDoble() const{
	
	return this->DOBLE; // aributo de tipo de lista
} // fin de isDoble

template<class T> bool ListaD<T>::isVacia() const{
	
	return !this->cab; // determinación
} // fin de isVacia


template<class T> Nodo<T>* ListaD<T>::buscar( T* info, int tipo, Nodo<T>** antes ) const{
	
	Nodo<T>* recor = this->cab; // recor empezara en cab
	bool empezo = false; // determinar si se empezo ya la busqueda

	while( recor && ( recor != this->cab || !empezo ) ){
		
		if( !empezo ) // si no se ha empezado la busqueda
			empezo = true; // busqueda empezada
			
		
		if( ( tipo == BUSCAR_ELEMENTO && *info == *recor->getInfo() ) || ( tipo == BUSCAR_POS_CRE && *info < *recor->getInfo() )  || ( tipo == BUSCAR_POS_DECRE && *info > *recor->getInfo() ) ) 
			return recor;			
			
		if( antes )		
			*antes = recor; 
			
		recor = recor->getLink_suc(); // recor ahora sera su sucesor 
	} // fin del while
	
	return NULL; // retorna NULL 
} // fin de buscar


template<class T> int ListaD<T>::agregar( T* info, int pos, bool repeticion ){
	
	Nodo<T>* nuevo = new Nodo<T>( info ); // crea nuevo Nodo
	Nodo<T>* recor = this->cab; // recorrido empezara en cab
	Nodo<T>* antes = NULL; // antes sera NULL
	 
	
	
	if( nuevo ) {
		
		// si se quiere evitar la repeticion
		if( !repeticion ){
			
			// busco si existe el elemento a agregar
			recor = this->buscar( info, BUSCAR_ELEMENTO, &antes );
			
			
			if( recor ) // si se encontro el elemento a agregar
				return -1; // el elemento a agregar ya existe
				
			recor = this->cab; // recor de nuevo sera cab
			antes = NULL; // antes de nuevo sera NULL
		} // fin del if
		
		if( pos == AGRE_CRE || pos == AGRE_DECRE ){ 
		
			// obtengo las posiciones recor y antes  del nuevo Nodo
			recor = this->buscar( info, ( pos == AGRE_CRE ? 
				BUSCAR_POS_CRE : BUSCAR_POS_DECRE ), &antes );
		} 
		else if( pos == AGRE_FIN ) {
			recor = NULL; // recor sera NULL
			antes = this->fin; // antes sera el fin
		} 
	
		// si la lista esta vacia
		if( !antes && !recor ) // antes y recor son NULL
			this->cab = this->fin = nuevo; // cab y fin serán nuevo
		
		
		// si se agregara de primero o en medio
		if( recor ){	// si la lista es doble, pre de recor será nuevo 
			recor->setLink_pre( ( this->DOBLE ? nuevo: NULL ) );
			nuevo->setLink_suc( recor ); // suc de nuevo sera recor
			
			// si agrege de primero, cab ahora será nuevo
			this->cab = ( recor == this->cab ? nuevo : this->cab );
		} // fin del if
		
		
		// si se agregara en medio o al fina
		if( antes ){	// si la lista es doble, pre de nuevo será antes 
			nuevo->setLink_pre( ( this->DOBLE ? antes: NULL ) );
			antes->setLink_suc( nuevo );
			
			// si agregue de ultimo, fin ahora sera nuevo
			this->fin = ( antes == this->fin ? nuevo : this->fin );
		} // fin del if
		
		
		// si la lista es circular
		if( this->CIRCU ){	// suc de fin sera cab
			this->fin->setLink_suc( cab );
			
			// si la lista ademas es doble 
			if( this->DOBLE )
				this->cab->setLink_pre( fin ); // pre de cab sera fin
		} // fin del if
	} 
	else // de lo contrario, no habia memoria suficiente
		return 0; // fallo al agregar por falta de memoria
		
		
	this->size++; // aumneta tamaño de la lista
	return 1; // exito al agregar
} // fin de agregar

template<class T> int ListaD<T>::eliminar( int tipo, T* info ){
	
	Nodo<T>* eliminar = this->cab; // Nodo a eliminar de la lista
	Nodo<T>* antes = NULL; // Nodo anterior a eliminar 
	
	if( !this->isVacia() ){	
	
		// si se viola la nomenclatura de los parámteros de la función
		// si se enivo elemento, y el tipo de eliminacion no es ELIM_ELEMENTO
		// o si no se envio elemento y el tipo de eliminación es ELIM_ELEMENTO
		if( ( info && tipo != ELIM_ELEMENTO ) || ( !info && tipo == ELIM_ELEMENTO ) )
			return -1; // combinación de parámetros invalida 
			
		
		// si se quiere eliminar un elemento especifico 
		if( tipo == ELIM_ELEMENTO ){
			
			// obtengo las posiciones antes y eliminar 
			eliminar = this->buscar( info, BUSCAR_ELEMENTO, &antes );
						
			// si no se encuentra el elemento a eliminar
			if( !eliminar ) 
				return 404; // no existe elemento a eliminar
		} 
		else if( tipo == ELIM_FINAL ){
			
			// obtengo copia del campo info del ultimo Nodo
			T* nodoFin = this->fin->getInfo();
			
			//obtengo las posiciones antes y eliminar del ultimo elemento
			eliminar = this->buscar(  nodoFin, BUSCAR_ELEMENTO, &antes );
		} // si no, entonces se quiere eliminar al inicio 
		  // por lo tanto no se modifican eliminar y antes
	
	
		// si eliminar es el unico en la lista
		if( this->cab == this->fin ){
			
			this->cab = this->fin = NULL; // cab y fin a NULL
			delete eliminar; // elimino Nodo
			this->size = 0; // tamaño de la ListaD será cero
			return 1; // exito al eliminar
		}  // fin del fi
		
		
		// si se eliminar en el inicio, fin o intermedio de la ListaD
		if( eliminar == this->cab ) // eliminar es cab
			this->cab = this->cab->getLink_suc(); // cab será su sucesor
		else if( eliminar == this->fin ) // si eliminar es fin
			this->fin = antes; // fin será antes
		else{
			
			// suc de antes ahora sera el suc de eliminar
			antes->setLink_suc( eliminar->getLink_suc() );
			
			// si la lista es doble, pre del suc de eliminar sera antes
			eliminar->getLink_suc()->setLink_pre( this->DOBLE ? antes : NULL ); 
		} // fin de los if...else
		
		// probando a reemplazar codigo de abajo
		this->fin->setLink_suc( ( this->CIRCU ? cab : NULL ) );
		this->cab->setLink_pre( ( this->DOBLE && this->CIRCU ? fin : NULL) );
		// termino prueba
					
		delete eliminar; // elimina Nodo	
	}
	else // de lo contrario, esta vacia la lista
		return 0; // No hay nada que eliminar
	
	
	this->size--; // decremento el tamaño de la ListaD en uno	
	return 1; // exito al eliminar
} // fin de eliminar

template<class T> bool ListaD<T>::eliminarLista(){
	
	Nodo<T>* recor = this->cab; // recor empieza en cab cab
	Nodo<T>* eliminar = NULL; // eliminar será NULL
	
	
	// si la ListaD no esta vacia 
	if( !this->isVacia() ) {
		
		// si eliminar es el unico en la lista
		if( this->cab == this->fin ){
			
			this->cab = this->fin = NULL; // cab y fin a NULL
			delete recor; // elimino Nodo
			return true; // exito al eliminar ListaD
		}  // fin del if
		
		
		// mientras la lista no este vacia 
		while(  recor ) {	
		
			eliminar = recor; // eliminar ahora sera recor
			recor = recor->getLink_suc(); // recor pasa a su sucesor
		
			delete eliminar; // elimino Nodo
			
			// si se llego al final de la ListaD
			if( recor == this->fin ){
				
				delete recor; // elimino ultimo Nodo
				this->cab = this->fin = recor = NULL; // cab, fin y recor serán NULL
				this->size = 0; // el tamaño de la ListaD será cero
			} // fin del if
		} // end while
	}
	else
		return false; // ListaD vacia
		
		
	return true; // exito al eliminar
} // fin de eliminarLista


template<class T> void ListaD<T>::imprimir() const{
	
	// El recorrido empezara en la cabezera de la lista
	Nodo<T>* recor = this->cab; 

	if( !recor ){
		
		std::cout << "NULL" << std::endl;
		return; // retorna a la funcion que hizo la llamada
	} // fin del if
	

	if( recor && this->cab == this->fin ){
		
		// si la ListaD es doble repito el preocesos
		for( int i = 0; i < ( this->DOBLE ? 2 : 1 ); i++ )
		{
			std::cout << *recor->getInfo();
		
			// si la ListaD es circular
			if( this->CIRCU ) // imprimo enlace circular
				std::cout << "|-->" << *recor->getLink_suc()->getInfo() << std::endl; 
			else
				std::cout << "-->NULL" << std::endl; // enlace utimo Nodo
		} // fin del for
	} // fin del if 
	
	
	// mientras la lista no este vacia y no se llegue al final 
	while(  recor && recor != this->fin ) {		
	
		std::cout << *recor->getInfo() /*<< "-->"*/ << std::endl; // imprime Nodo
		recor = recor->getLink_suc(); // recor pasa a su sucesor
		
		// si se llego al final de la ListaD
		if( recor == this->fin ){
			
			std::cout << *recor->getInfo(); // ultimo Nodo
			
			// si la ListaD es circular
			if( this->CIRCU ) // imprimo enlace circular
				std::cout << "|-->" << *recor->getLink_suc()->getInfo() << std::endl; 
			else
				std::cout /*<< "-->NULL"*/ << std::endl; // enlace utimo Nodo
		}
	} // end while
	
	
	recor = this->fin; // recor empezara en fin ahora
	
	
	// mientras la lista no este vacia, sea doble y recor no llegue a cab
	while( recor && this->DOBLE && recor != this->cab ) {
		
		std::cout << *recor->getInfo() << "-->"; // imprime Nodo
		recor = recor->getLink_pre(); // recor pasa a su predecesor
		
		
		// si se llego a la cab de la ListaD 
		if( recor == this->cab ){
			
			std::cout << *recor->getInfo(); // ultimo Nodo
			
			// si la ListaD es circular
			if( this->CIRCU ) // imprimo enlace circular
				std::cout << "|-->" << *recor->getLink_pre()->getInfo() << std::endl; 
			else
				std::cout << "-->NULL" << std::endl; // enlace utimo Nodo
		}
	} // end while
} // fin de imprimir

template<class T> void ListaD<T>::imprimir( bool sobrecarga ) const{
	
	// El recorrido empezara en la cabezera de la lista
	Nodo<T>* recor = this->cab; 
	
	
	// si al ListaD esta vacia
	if( !recor ){
		
		std::cout << "NULL" << std::endl; // imprime enlace del ultimo Nodo
		return; // retorna a la funcion que hizo la llamada
	} // fin del if
	
	
	// si solo hay un elemento en la ListaD
	if( recor && this->cab == this->fin )
		std::cout << recor->getLink_pre() << "<--" << *recor->getInfo() << "-->" << recor->getLink_suc() << std::endl; // imprime Nodo y sus dos enlaces

	// mientras la lista no este vacia y no se llegue al final o..
	while(  recor && recor != this->fin ) {	
	
		std::cout << recor->getLink_pre() << "<--" << *recor->getInfo() <<	"-->" << recor->getLink_suc(); // imprime Nodo y sus dos enlaces
		recor = recor->getLink_suc(); // recor pasa a su sucesor
		
		
		// si se llego al final de la ListaD
		if( recor == this->fin )
			std::cout << std::endl << recor->getLink_pre() << "<--" << *recor->getInfo() <<"-->" << recor->getLink_suc() ; // imprime ultimo Nodo y sus dos enlaces

		std::cout << std::endl; // deja linea en blanco
	} // end while
} // fin de imprimir

#endif
