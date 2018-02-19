#include "Camino.h"

int Camino::id_static = 0; // inicia en cero 

Camino::Camino(){ 

	this->id = Camino::id_static; // id será id_static actual
	Camino::id_static++; // incremento id_static en uno
	this->longitud = this->vertices = 0;
	this->lista_vertices = new ListaD<Vertice>( true, false );
} // fin del contructor


Camino::~Camino(){ 

	delete this->lista_vertices;
} // fin del destructor


double Camino::getLongitud() const{
	
	return this->longitud; // longitud del camino
} // fin de getLongitud


int Camino::getVertices() const{
	
	return this->vertices; // cantidad de vertices del camino
} // fin de getVertices

void Camino::actualizar(){
	
	// cantidad de vertices sera la cantidad de elementos en la lista
	this->vertices = this->lista_vertices->getSize();
	this->longitud = 0; // antes de actualizarce debe ser cero
		
	for( int i = 0; i < this->lista_vertices->getSize(); i++ )
		this->longitud += 
			this->lista_vertices->getElemento_info( i )->getLongitudArista();
} // fin de actualizar

bool Camino::eliminarListaVerticesDesde( Vertice* partida ){
	
	Nodo<Vertice>* recor = this->lista_vertices->buscar( partida );
	Nodo<Vertice>* eliminar; // auxiliar para eliminar Vertices
	
	if( recor ){
		
		recor = recor->getLink_suc(); // recor inicia siendo su sucesor 
		
		
		// mientras recor tenga direccion valida
		while( recor ){
			
			eliminar = recor; // eliminar ser recor
			recor = recor->getLink_suc(); // recor será su sucesor
			this->lista_vertices->eliminar( ListaD<Vertice>::ELIM_ELEMENTO, eliminar->getInfo() ); // elimino 
		} // fin del while 
	}
	else 
		return false;  // no se encontro el Vertice de partida
		
		
	return true; // se encontro el Vertice de partida y elimino despues de el la lista de Caminos 
} // fin de eliminarListaVerticesDesde

bool Camino::iguales( Camino* contrario, bool opuesto ) const{
	
	Nodo<Vertice>* recor = this->lista_vertices->getCab();
	Nodo<Vertice>* travel = ( opuesto ? 
		contrario->lista_vertices->getFin() : 
			contrario->lista_vertices->getCab() );

	if( this->vertices == contrario->vertices ){ 
	
		while( recor && travel ){ 
		
			if( !( *recor->getInfo() == *travel->getInfo() ) )
				return false; // Caminos diferentes
					
			recor = recor->getLink_suc(); // su predecesor dependiendo de opuesto
			travel = ( opuesto ? travel->getLink_pre() : travel->getLink_suc() ); 
		} // fin del while
	}
	else
		return false; // los Caminos no son iguales 
			
			
	return true; // Caminos iguales
} // fin de iguales

std::ostream& operator<<( std::ostream& salida, const Camino& datos ){
	
	char delim = '/'; // separador 

	salida << "(id: " << datos.id << delim << "Vertices: " << datos.vertices-1
		<< delim << "Longitud: " << datos.longitud << ")";
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<


bool Camino::operator<( const Camino& datos ){
	
	return ( this->vertices < datos.vertices );
} // fin del operador<

bool Camino::operator>( const Camino& datos ){
	
	return ( this->longitud > datos.longitud );
} // fin del operador>

bool Camino::operator==( const Camino& datos ){
	
	return ( this->id == datos.id ); // retorna desición  
} // fin de operator== 


















