#ifndef CAMINO_H
#define CAMINO_H
#include "ListaD.h"
#include "Vertice.h"
#include <iostream>

class Camino{
	
	friend std::ostream& operator<<( std::ostream&, const Camino& );
	private:
		
		static int id_static; 
		int id; 
		int vertices; 
		double longitud; 
		
	public:
		
		ListaD<Vertice>* lista_vertices; 
		Camino(); 
		~Camino(); 
		double getLongitud() const;
		int getVertices() const;
		void actualizar(); 
		bool eliminarListaVerticesDesde( Vertice* );
		bool iguales( Camino*, bool opuesto = false ) const;
		bool operator==( const Camino& ); 
		bool operator<( const Camino& ); 
		bool operator>( const Camino& ); 
}; // fin de Camino

#endif
