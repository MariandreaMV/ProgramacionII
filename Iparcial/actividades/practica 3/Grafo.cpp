#include "Grafo.h"
using namespace std; 
#include <windows.h> 

void Grafo::inicializar( bool dirigido, bool ponderado ){
	
	this->DIRIGIDO = dirigido;
	this->PONDERADO = ponderado;
	this->longitud = 0;
	this->lista_adyacencia = new ListaD<Vertice>();
	this->lista_caminos = new ListaD<Camino>();
} // fin de inicializar


Grafo::Grafo(){
 
	this->inicializar(); 
} // fin del constructor

Grafo::Grafo( bool dirigido, bool ponderado ){
 
	this->inicializar( dirigido, ponderado );
} // fin del constructor

Grafo::Grafo( string nom_archivo, char delimitador, bool dirigido, bool ponderado ){
 
	this->inicializar( dirigido, ponderado );


	Archivo* archivo = new Archivo( nom_archivo ); 
	string* buffer; 
	
	archivo->abrir(); 
	
	while( !archivo->isFinal() ){
		
		buffer = archivo->leerCampos( delimitador, 3 ); 
		
		this->agregar( new Vertice( buffer[0] ), new Vertice( buffer[1], ( this->PONDERADO ? atof( buffer[2].c_str()) : 0 ) ));
	
		if( !this->DIRIGIDO ) 
			this->agregar(  new Vertice( buffer[1] ), new Vertice( buffer[0], ( this->PONDERADO ? atof( buffer[2].c_str()) : 0 ) ));
	} // fin del while
} // fin del constructor


bool Grafo::isDirigido() const{
	
	return this->DIRIGIDO;
} // fin de isDirigido


bool Grafo::isPonderado() const{
	
	return this->PONDERADO;
} // fin de isPonderado


int Grafo::getNumeroVertices() const{
	
	if( !this->DIRIGIDO ) 
		return this->lista_adyacencia->getSize();
	else{
	
		int vertices = this->lista_adyacencia->getSize();
		Nodo<Vertice>* recor = this->lista_adyacencia->getCab(); // recor será cab de LAP
		Nodo<Vertice>* travel = NULL; // travel será NULL 
		ListaD<Vertice>* ausentes = new ListaD<Vertice>(); // lista de Vertices ausentes en la LAP
		
		while( recor ){
		
			travel = recor->getInfo()->vertices_adyacentes->getCab();
	
			while( travel ){
			
				if( !this->lista_adyacencia->buscar( travel->getInfo() ) &&	!ausentes->buscar( travel->getInfo() )){
					
					vertices++; 
					ausentes->agregar( travel->getInfo(), ListaD<Vertice>::AGRE_FIN ); // agrego a ausentes
				} // fin del if
			
				travel = travel->getLink_suc(); // travel será su sucesor
			} // fin del while
		
			recor = recor->getLink_suc(); // recor sera su sucesor
		} // fin del while
		
		
		return vertices; // retorna numero de Vertices
	} // fin del if...else
} // fin de getNUmeroVertices

float Grafo::getLongitud() const{
	
	return this->longitud;
} // fin de getLongitud


bool Grafo::agregar( Vertice* vertice_partida, Vertice* vertice_destino ){

	Nodo<Vertice>* vertice_aux; // Lista de adyacencia
	int estado = 1; // estado de la operación de agregar
	
	vertices.agregar(vertice_partida,ListaD<Vertice>::AGRE_FIN,false);
	vertices.agregar(vertice_destino,ListaD<Vertice>::AGRE_FIN,false);
	
	if( this->lista_adyacencia->isVacia() ){
		
		 estado = this->lista_adyacencia->agregar( vertice_partida, // agrego vertice_partida a la lista 
			ListaD<Vertice>::AGRE_FIN ); // de adyacencia principal(LAP)
		vertice_aux = this->lista_adyacencia->getCab(); // obtengo la cab de la LAP
		estado = vertice_aux->getInfo()->vertices_adyacentes->agregar( // agrego vertice_destino a la lista 
			vertice_destino, ListaD<Vertice>::AGRE_FIN ); // de adyacencia secundaria(LAS)
	}
	else {
	
		vertice_aux = this->lista_adyacencia->buscar( vertice_partida );
		
		if( vertice_aux )
			estado = vertice_aux->getInfo()->vertices_adyacentes->agregar( // agrego vertice destino a 
				vertice_destino, ListaD<Vertice>::AGRE_FIN ); // vertice_aux
		else {
			
			estado = this->lista_adyacencia->agregar( // agrego vertice_partida a la lista 
				vertice_partida, ListaD<Vertice>::AGRE_FIN ); // de adyacencia principal(LAP)
			vertice_aux = this->lista_adyacencia->getFin(); // obtenga el final de la LAP
			estado = vertice_aux->getInfo()->vertices_adyacentes->agregar( // agrego vertice_destino a la  
				vertice_destino, ListaD<Vertice>::AGRE_FIN ); // lista de adyacencia secundaria(LAS)
		} // fin del if...else
	} // fin del if...else
	
	this->longitud += vertice_destino->getLongitudArista(); // acumulo la longitud de la arista
	return ( estado == 1 ); // retorna estado de agregar
} // fin de agregar



void Grafo::BuscarCaminos(){
	
	Nodo<Vertice>* recor = this->lista_adyacencia->getCab();
	Nodo<Camino>* camino = NULL; // apuntador a lista de caminos
	

	while( recor ){
		
		cout<<"buscar caminos"<<endl;
		// agrego a la sublista de camino a recor 
		this->agregar_camino( camino, recor );
		recor = recor->getLink_suc(); // recor ahora sera su sucesor
	
		if( recor ){
			
			this->lista_caminos->agregar( new Camino(), ListaD<Camino>::AGRE_FIN );
			camino = this->lista_caminos->getFin(); // camino ahora sera el fin de lista_caminos
		} // fin del if
	} // fin de while 
}  // fin de crearCaminos


bool Grafo::agregar_camino( Nodo<Camino>* nodo_lista_camino, Nodo<Vertice>* nodo_agregar ){
	
	Nodo<Vertice>* nodo_sublista_adyacencia; // posición en la sublista de adyacencia de nodo_agregar
	bool finCamino = false; // determina si se llego al final del camino
	Nodo<Vertice>* nodo_aux_vertice = NULL; // nodo para operaciones auxiliares
	Nodo<Camino>* nodo_aux_camino = NULL; // nodo para oporeaciones auxiliares
	
	if( this->lista_caminos->isVacia() ){
		
		// agrego a la lista de caminos un nuevo Camino
		this->lista_caminos->agregar( new Camino(), ListaD<Vertice>::AGRE_FIN );
		nodo_lista_camino = this->lista_caminos->getFin(); // nodo_lista_caminos sera el ultimo Camino creado 
	} // fin del if
	
	
	// si la lista de Vertices de nodo_lista_camino esta vacia
	if( nodo_lista_camino->getInfo()->lista_vertices->isVacia() ){
		
		// agrego a la lista de Vertices de nodo_lista_camino un nuevo 
		nodo_lista_camino->getInfo()->lista_vertices // Nodo con el Vertice 
			->agregar( nodo_agregar->getInfo(), ListaD<Vertice>::AGRE_FIN ); // de nodo_agregar
	} 
	else {
	
		if( nodo_lista_camino->getInfo()->lista_vertices->buscar( nodo_agregar->getInfo() ) )
			return false; // no se agrega y retorno false(no he llegado al fin del Camino)
		else // si no esta, entonces lo agrego
			nodo_lista_camino->getInfo()->lista_vertices->agregar( 
				nodo_agregar->getInfo(), ListaD<Vertice>::AGRE_FIN );
	} // fin del if...else

	if( nodo_agregar->getInfo()->vertices_adyacentes->isVacia() )
		nodo_agregar = this->lista_adyacencia-> // buscp al Vertice en la 
			buscar( nodo_agregar->getInfo() ); // lista principal de adyacencia

		
	// si el nodo_agregar no esta en la lista de adyacencia
	if( !nodo_agregar )
		return true; // entonces llegue al final del camino
		
		
	// nodo_sublista_adyacencia ahora sera la cab de la sublista de adyacencia de nodo_agregar
	if( !nodo_agregar->getInfo()->vertices_adyacentes->isVacia() )	/////////////////////////////
		nodo_sublista_adyacencia = nodo_agregar->getInfo()->vertices_adyacentes->getCab(); 
	else
	nodo_sublista_adyacencia = NULL; /////////////////////////////////////////////////////////////
	
	
	// llamada recursiva con argumentos de Nodo de Camino, y Nodo a agregar respectivamente 
	finCamino = this->agregar_camino( nodo_lista_camino, nodo_sublista_adyacencia ); 

	// hacer mientras nodo_sublista_adyacencia tenga un sucesor
	do{
		// si ya se llego al final de camino
		if( finCamino ){
			
			// si nodo_sublista_adyacencia no tiene sucesor
			if( !nodo_sublista_adyacencia->getLink_suc() )
				return true; // se llego al final del camino
			else {
				// nodo_aux_vertice será el Vertice en la cab de  
				nodo_aux_vertice = this->lista_caminos->getFin() // la lista de vertices del ultimo Camino
					->getInfo()->lista_vertices->getCab(); // en la lista de caminos
					
				// agrego a la lista de caminos un nuevo Camino
				this->lista_caminos->agregar( new Camino(), ListaD<Camino>::AGRE_FIN );
				nodo_aux_camino = this->lista_caminos->getFin(); // nodo_aux_camino será el ultimo Camino 
				
				
				// copio camino de nodo_lista_camino desde su cab hasta nodo_agregar al nuevo Camino
				while( true ){
					// agrego a nodo_aux_vertice a la lista de Vertices de nodo_aux_camino
					nodo_aux_camino->getInfo()->lista_vertices->agregar( 
						nodo_aux_vertice->getInfo(), ListaD<Vertice>::AGRE_FIN );


					// si nodo_aux_vertice es el mismo Vertice de nodo_agregar
					if (  *nodo_aux_vertice->getInfo() == *nodo_agregar->getInfo() )
						break; // dejo de copiar el camino 
					
					
					// nodo_aux_vertice ahora será su sucesor 	
					nodo_aux_vertice = nodo_aux_vertice->getLink_suc();
				} // fin del while
			} // fin del if...else
		} // fin del if
		
		if( nodo_sublista_adyacencia->getLink_suc() ){
			
			nodo_sublista_adyacencia = nodo_sublista_adyacencia->getLink_suc();
		
			// si ya se llego al final del camino
			if( finCamino ){
				agregar_camino( nodo_aux_camino, nodo_sublista_adyacencia );
			}
			else {
				// llamada recursiva con argumentos de Nodo de Camino, y Nodo a agregar respectivamente
				finCamino = agregar_camino( nodo_lista_camino, nodo_sublista_adyacencia );
			} // fin del if...else
		} // fin del if
	}while( nodo_sublista_adyacencia->getLink_suc() ); // fin del while
	
	
	return true; // se llego al final del camino
} // fin de agregar_camino

void Grafo::buscarCaminos_maxVertices(){

	Nodo<Vertice>* recor_vertice = this->lista_adyacencia->getCab();
	Nodo<Camino>* camino = NULL; // apuntador a lista de caminos
	Nodo<Camino>* recor_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
	int numeroVertices = this->getNumeroVertices(); // numero de Vertices en el Grafo
	this->lista_caminos->eliminarLista(); // elimino lista de Caminos si es que la habia  
	
	
	// mientras recor tenga direccion valida
	while( recor_vertice ){
		
		// agrego a la sublista de camino a recor 
		this->agregar_camino( camino, recor_vertice );
		recor_vertice = recor_vertice->getLink_suc(); // recor ahora sera su sucesor
		this->actualizarCaminos(); // actualizo Caminos creados 

		
		// si el Grafo no es dirigido 
		if( !this->DIRIGIDO ){
			
			// recor_camino empieza en la cab de la lista de Caminos
			recor_camino = this->lista_caminos->getCab();
			
			while( recor_camino ){
				
				// si recor_camino tiene menos Vertices que la cantidad de Vertices en el Grafo
				if( recor_camino->getInfo()->getVertices() < numeroVertices ){
					
					eliminar_camino = recor_camino; // recor_camino se eliminara 
					recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
					this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
						ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos
				}
				else // si no, entonces el camino de recor_camino tiene tantos Vertices como el Grafo
					recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
			} // fin del while
		}
		else{
			
			// recor_camino empieza en la cab de la lista de Caminos
			recor_camino = this->lista_caminos->getCab();
	
	
			// mientras recor_camino tenga dirección valida 
			while( recor_camino ){
				
				// travel_camino empieza en la cab de la lista de Caminos
				travel_camino = this->lista_caminos->getCab();
	
				while( travel_camino ){
					
					// si travel_camino tiene menos Vertices que recor_camino 
					if( *travel_camino->getInfo() < *recor_camino->getInfo() ){
						
						eliminar_camino = travel_camino; // se eliminara a travel_camino
						travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
						this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
							ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
					}
					else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
						travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
				} // fin del while
			
				recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
			} // fin del while	
		} // fin del if...else
		
		
		// si recor aun tiene dirección valida
		if( recor_vertice ){
			
			// agrego a la lista de caminos un nuevo Camino
			this->lista_caminos->agregar( new Camino(), ListaD<Camino>::AGRE_FIN );
			camino = this->lista_caminos->getFin(); // camino ahora sera el fin de lista_caminos
//			cout << endl << "EMPIEZO CON CAMINOS DE OTRO VERTICE" << endl;////////////////////////////////
		} // fin del if
	} // fin de while
	
	if( !this->DIRIGIDO ){
		
		// recor_camino empieza en la cab de la lista de Caminos
		recor_camino = this->lista_caminos->getCab();
	
	
		// mientras recor_camino tenga dirección valida 
		while( recor_camino ){
			
			// travel_camino empieza en la cab de la lista de Caminos
			travel_camino = this->lista_caminos->getCab();
				
	
			while( travel_camino ){
				
				// si recor_camino y travel_camino no son el mismo Caminos pero son
				//  Caminos exactamente iguales(mismos vertices) 
				if( !( *recor_camino->getInfo() == *travel_camino->getInfo() ) && recor_camino->getInfo()->iguales( travel_camino->getInfo(), true ) ){
					
					eliminar_camino = travel_camino; // se eliminara a travel_camino
					travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
					this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
						ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
				}
				else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
					travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
			} // fin del while
						
			recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
		} // fin del while 
	} // fin del if
} // fin de buscarCaminos_maxVertices

void Grafo::buscarCaminos_MinMaxVertices( bool min ){
	
	Nodo<Camino>* recor_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
		
	
	// recor_camino empieza en la cab de la lista de Caminos
	recor_camino = this->lista_caminos->getCab();
	
	
	// mientras recor_camino tenga dirección valida 
	while( recor_camino ){
		
		// travel_camino empieza en la cab de la lista de Caminos
		travel_camino = this->lista_caminos->getCab();
				
				
		// mientras travel_camino tenga dirección valida
		while( travel_camino ){
			
			// si estoy buscando Caminos maximos y el Camino de recor_camino
			// tiene mayor longitud que el Camino de travel_camino
			if( ( !min && *travel_camino->getInfo() < *recor_camino->getInfo() ) ||( min && *recor_camino->getInfo() < *travel_camino->getInfo() ) ){
				
				eliminar_camino = travel_camino; // se eliminara a travel_camino
				travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
				this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
					ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
			} 
			else 
				travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
		} // fin del while
			
		recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
	} // fin del while	
} // fin de buscarCaminos_minMaxLongitud

void Grafo::buscarCaminos_MinMaxLongitud( bool min ){
	
	Nodo<Camino>* recor_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
	
	
	// si el Grafo es no ponderado
	if( !this->PONDERADO )
		return; // no hago busqueda de Caminos largos o cortos
		
	
	// recor_camino empieza en la cab de la lista de Caminos
	recor_camino = this->lista_caminos->getCab();
	
	
	// mientras recor_camino tenga dirección valida 
	while( recor_camino ){
		
		// travel_camino empieza en la cab de la lista de Caminos
		travel_camino = this->lista_caminos->getCab();
				
				
		// mientras travel_camino tenga dirección valida
		while( travel_camino ){
			
			// si estoy buscando Caminos maximos y el Camino de recor_camino
			// tiene mayor longitud que el Camino de travel_camino
			if( ( !min && *recor_camino->getInfo() > *travel_camino->getInfo() ) ||( min && *travel_camino->getInfo() > *recor_camino->getInfo() ) ){
				
				eliminar_camino = travel_camino; // se eliminara a travel_camino
				travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
				this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
					ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
			} // si no, entonces estoy buscando minimos
			else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
				travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
		} // fin del while
		
		recor_camino = recor_camino->getLink_suc(); // recor_camino será su sucesor 
	} // fin del while	
} // fin de buscarCaminos_minMaxLongitud


void Grafo::buscarCaminosSinVertice( Vertice* inter ){

	Nodo<Camino>* travel_camino; // apuntador para recorrer lista de Caminos
	Nodo<Camino>* eliminar_camino; // apuntador para eliminar Caminos
		
		
	// travel_camino empieza en la cab de la lista de Caminos
	travel_camino = this->lista_caminos->getCab();
			
			
	// mientras travel_camino tenga dirección valida
	while( travel_camino ){
		
		// si estoy buscando Caminos maximos y el Camino de recor_camino
		// tiene mayor longitud que el Camino de travel_camino
		if( travel_camino->getInfo()->lista_vertices->buscar( inter ) ){
			
			eliminar_camino = travel_camino; // se eliminara a travel_camino
			travel_camino = travel_camino->getLink_suc(); // travel_camino será sus sucesor
			this->lista_caminos->eliminar( // elimino a eliminar_camino de la lista de 
				ListaD<Camino>::ELIM_ELEMENTO, eliminar_camino->getInfo() ); // Caminos 
		} // si no, entonces estoy buscando minimos
		else // si no, entonces travel_camino no tiene menos Vertices que recor_camino
			travel_camino = travel_camino->getLink_suc();  // travel_camino será sus sucesor
	} // fin del while
} // buscarCaminosSinVertice


void Grafo::buscarCaminos_MinMaxLongitud_Grafo( bool min ){
	
	this->buscarCaminos_maxVertices(); // busca los Caminos con más Vertices 
	this->buscarCaminos_MinMaxLongitud( min ); // busca Caminos largos o cortos
} // fin de buscarCaminos_MinMaxLongitud_Grafo


bool Grafo::conectividad( Vertice* A, Vertice* B ){
	
	// busco el Vertice A en el grafo y este sera mi Vertice de partida
	Nodo<Vertice>* partida = this->lista_adyacencia->buscar( A );
	Nodo<Camino>* recor; // Nodo para recorrer la lista de Caminos resultante
	Nodo<Camino>* travel; // Nodo para recorrer la lista de Caminos resultante
	Nodo<Camino>* eliminar; // apuntador para eliminar Caminos
	this->lista_caminos->eliminarLista(); // elimino lista de Caminos si es que la habia  


	// si el Vertice de partida se encuentra en la lista de adyacencia 
	if( partida ){	
	
		// agrego a la sublista de camino a partida 
		this->agregar_camino( NULL, partida );
		
		// recor empezara en la cab de la lista de Caminos
		recor = this->lista_caminos->getCab(); 
	

		// mientras recor tenga una direccion valida
		while( recor ){
			
			// si no se encontro a B en el Camino de recor
			if( !recor->getInfo()->eliminarListaVerticesDesde( B ) ) {
				
				eliminar = recor; // eliminar sera recor
				recor = recor->getLink_suc(); // recor será su sucesor 
				this->lista_caminos->eliminar( // elimino a recor de la lista de Caminos 
					ListaD<Camino>::ELIM_ELEMENTO, eliminar->getInfo() ); // del Grafo 
			} // fin del if 
			else
				recor = recor->getLink_suc(); // recor será su sucesor 
		} // fin del while
	} // fin del if
	else
		return false; // no se encuentra Vertice A o es un pozo( con Grafo dirigido)
		
	
	// si la lista de Caminos esta vacia
	// ( no se encontro a B en ningun Camino partiendo de A ) 	
	if( this->lista_caminos->isVacia() )
		return false; // no hay conectividad
	else{
		
		this->actualizarCaminos(); // actualizo Caminos	
		
		// recor empieza en la cab de la lista de Caminos
		recor = this->lista_caminos->getCab();
	
	
		// mientras recor tenga dirección valida 
		while( recor ){
				// travel empieza en la cab de la lista de Caminos
				travel = this->lista_caminos->getCab();
				
				
				// mientras travel tenga dirección valida
				while( travel ){
					// si recor y travel no son el mismo Caminos pero son
					//  Caminos exactamente iguales(mismos vertices)
					if(  !( *recor->getInfo() == *travel->getInfo() ) && recor->getInfo()->iguales( travel->getInfo() ) ){
						
						eliminar = travel; // se eliminara a travel
						travel = travel->getLink_suc(); // travel será sus sucesor
						this->lista_caminos->eliminar( // elimino a eliminar de la lista de 
							ListaD<Camino>::ELIM_ELEMENTO, eliminar->getInfo() ); // Caminos 
					}
					else // si no, entonces travel y recor no son Caminso iguales
						travel = travel->getLink_suc();  // travel será sus sucesor
				} // fin del while
				
				
				recor = recor->getLink_suc(); // recor será su sucesor 
		} // fin del while
		
		
		return true; // si hay conectividad 
	} // fin del if...else
} // fin de conectividad

bool Grafo::buscarCaminos_MinMaxVertices_Vertices( Vertice* A, Vertice* B, bool min, Vertice* inter ) {
	
	// si existe conectividad entre A y B
	if( this->conectividad( A, B ) ){
		
		// si se especifico un vertice intermedio a obviar
		if( inter ){
			
			this->buscarCaminosSinVertice( inter );
		} // fin del if
		
		
		// busca los Caminos mas largos o cortos segun se especifico 
		this->buscarCaminos_MinMaxVertices( min );
		return true; 
	}
	else // si no, entonces no existe conectividad
		return false; // no existen Caminos entre A y B
} // fin de buscarCaminos_MinMaxVertices_Vertices

 
bool Grafo::buscarCaminos_MinMaxLongitud_Vertices( Vertice* A, Vertice* B, bool min, Vertice* inter ){
	
	// si existe conectividad entre A y B
	if( this->conectividad( A, B ) ){
		
		// si se especifico un vertice intermedio a obviar
		if( inter ){
			
			this->buscarCaminosSinVertice( inter );
		} // fin del if
			
		// busca los Caminos mas largos o cortos segun se especifico 
		this->buscarCaminos_MinMaxLongitud( min );
		return true; 
	}
	else // si no, entonces no existe conectividad 
		return false; // no existen Caminos entre A y B
} // fin de buscarCaminos_MinMaxLongitud_Vertices


void Grafo::actualizarCaminos(){
	
	// recor empezara en la cab de la lista de Caminos
	Nodo<Camino>* recor = this->lista_caminos->getCab(); 
	
	
	// mientras recor tenga una direccion valida
	while( recor ){
		
		recor->getInfo()->actualizar(); // actualizo Camino
		recor = recor->getLink_suc(); // recor será su sucesor 
	} // fin del while
} // fin de actualizarCaminos

void Grafo::imprimirListaAdyacencia() const{
	
	// recor será la cab de la lista de adyacencia principal
	Nodo<Vertice>* recor = this->lista_adyacencia->getCab(); 
	
	if( this->lista_adyacencia->isVacia() ){
		
		cout << "NULL" << endl; // grafo vacio
		return; // retorno
	} // fin del if
	
	
	// mientras recor tenga direccion 
	while( recor ){
		
		cout << *recor->getInfo() << ": " << endl; // imprimo vertice
		recor->getInfo()->vertices_adyacentes->imprimir(); // imprimo sublista 
		recor = recor->getLink_suc(); // recor será su sucesor
	} // fin del while
} // fin de imprimirListaAdyacencia

int Grafo::imprimirListaCaminos() const{
	
	// recor empezara en la cab de la lista de Caminos
	Nodo<Camino>* recor = this->lista_caminos->getCab(); 
	int retorno=0;
	
	// si la lista de Caminos esta vacia 
	if( this->lista_caminos->isVacia() ){
		
		cout << "NULL" << endl; // lista vacia
		return retorno; // retorno a quien hizo la llamada
	} // fin del if
	
	
	// mientras recor tenga una direccion valida
	while( recor ){
		
		// actualizo e impirmo Camino y su lista de Vertices
		recor->getInfo()->actualizar(); // actualizo camino
		cout << *recor->getInfo() << ": " << endl;
		recor->getInfo()->lista_vertices->imprimir(); // lista de Vertices
		retorno=recor->getInfo()->getVertices();
		recor = recor->getLink_suc(); // recor será su sucesor 
		
	} // fin del while
	return retorno;
} // fin de imprimirListaCaminos

void Grafo::SegundoCaminoMasCorto(Vertice *partida, Vertice *llegada){
		
	int tamanio = this->vertices.getSize();
	string v1[tamanio];
	int MA[tamanio][tamanio];
	double MatrizPesos[tamanio][tamanio];
	
	for(int i=0;i<tamanio;i++){
		
		for(int j=0;j<tamanio;j++){
			
			MA[i][j]=0;
			MatrizPesos[i][j]=0;
		}
	}
	
	Nodo<Vertice> *vert=this->vertices.getCab();
	
	for(int i=0;i<tamanio;i++){
		
		v1[i] = vert->getInfo()->getIdentificador();
		vert=vert->getLink_suc();
	}
	
	//matriz de adyacencia ordenada	
	int a;
	string aux;
	int y;
	int flag=1;
	for(a=0; a<tamanio-1&&flag==1;a++){	
	
		flag=0;
		for(y=0;y<tamanio-1;y++){
						
			if(v1[y]>v1[y+1]){
			flag=1;
			aux=v1[y+1];
			v1[y+1]=v1[y];
			v1[y]=aux;
			}
		}
	}
	
	
	
	// si la lista de adyacencia esta vacia
	if( this->lista_adyacencia->isVacia() ){
		
		cout << "NULL" << endl; // grafo vacio
		return; // retorno
	} // fin del if
	
	Nodo<Vertice>* recor = this->lista_adyacencia->getCab();
	// mientras recor tenga direccion 
	while( recor ){
		
		for(int y=0;y<tamanio;y++){
			
			if(v1[y]==recor->getInfo()->getIdentificador()){
				
				Nodo<Vertice> *adyacente= recor->getInfo()->vertices_adyacentes->getCab();
				int cont=0;
				
				while(cont<recor->getInfo()->vertices_adyacentes->getSize()){
					
					for(int x=0; x<tamanio;x++){
						
						if(v1[x]==adyacente->getInfo()->getIdentificador()){
							
							MA[y][x]=1;
							MatrizPesos[y][x]=adyacente->getInfo()->getLongitudArista();
							break;	
						} 	
					}	
					cont++;
					adyacente= adyacente->getLink_suc();	
				}			
			}
		}
		recor = recor->getLink_suc(); // recor será su sucesor
	} 
	
	ListaD<double>* lista_caminos_dos_puntos_menor_peso;
	vector<ListaD <int> > lista_posibles_caminos;

	ListaD<Camino>* caminos;
	
	int x=0;
		
		ListaD<int> posible_camino;
		vector<double> pesos_camino_posible;
		bool posible = false;
		double pesos;
	
	while(x<tamanio){

		if(MA[atoi(partida->getIdentificador().c_str())][x]==1){
			
			int iterador = x;
			int horizontal=0;
			
			int *p = new int();
			*p = atoi(partida->getIdentificador().c_str());
			posible_camino.agregar(p,2,false);	
			pesos = MatrizPesos[atoi(partida->getIdentificador().c_str())][x];
			
			if( x == atoi(llegada->getIdentificador().c_str())){
				
				posible = true;
				pesos_camino_posible.push_back(pesos);
			}
			
			else{
			
				while(iterador<tamanio){
					
						if(MA[iterador][horizontal]==1 && horizontal!=atoi(partida->getIdentificador().c_str())){
							
							int *cam = new int();
							*cam = iterador;
							posible_camino.agregar(cam,2,false);
										
							pesos += MatrizPesos[iterador][horizontal];
							iterador = horizontal;
							
							if(horizontal==atoi(llegada->getIdentificador().c_str())){
								
								horizontal =tamanio;	
								pesos_camino_posible.push_back(pesos);
								posible = true;	
							}
							else
								horizontal = 0;					
						}	
				horizontal++;	
				}
			}	
		}		
		posible = false;
		x++;
	}
	
	if(pesos_camino_posible.size()==1) cout<<"-1"<<endl;
	
	else{
		
		double temp;
		for (int i=1; i<pesos_camino_posible.size(); i++)
		for (int j=0 ; j<pesos_camino_posible.size() - 1; j++)
		
		    if (pesos_camino_posible[j] > pesos_camino_posible[j+1]){
		    	
		    	temp = pesos_camino_posible[j];
                pesos_camino_posible[j] = pesos_camino_posible[j+1];
                pesos_camino_posible[j+1] = temp;
			}
			
        double segundo;    	
        double penultimo;
        
		for(int i=0;i<pesos_camino_posible.size();i++){
			
			penultimo=pesos_camino_posible[i+1];
				if(penultimo>pesos_camino_posible[i]){
					
					cout<<penultimo<<endl;
					break;	
				}
		}
	
	}
	
	
	
	
	

}


