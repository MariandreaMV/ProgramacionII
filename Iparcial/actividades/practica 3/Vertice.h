#ifndef VERTICE_H
#define VERTICE_H
#include <string>
#include <iostream>
#include "ListaD.h"

class Vertice{

	friend std::ostream& operator<<( std::ostream&, const Vertice& );
	
	private:
	
		double longitud_arista; 
		std::string identificador;
		
	public:
		
		ListaD<Vertice>* vertices_adyacentes;
		
		Vertice( std::string, double longitud = 0 ); 
		double getLongitudArista() const; 
		std::string getIdentificador() const; 
		bool operator==( const Vertice& );
		bool operator<( const Vertice& ){} 
		bool operator>( const Vertice& ){} 
}; 


#endif
