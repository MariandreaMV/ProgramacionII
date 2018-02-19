#ifndef GRAFO_H
#define GRAFO_H
#include "ListaD.h"
#include "Vertice.h"
#include "Camino.h"
#include "Nodo.h"
#include "Archivo.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

class Grafo {
	private:
		
		bool DIRIGIDO; 
		bool PONDERADO; 
		float longitud; 

		void inicializar( bool dirigido = true, bool ponderado = false );
		bool agregar_camino( Nodo<Camino>*, Nodo<Vertice>* ); 
		void actualizarCaminos(); 
		void buscarCaminos_MinMaxVertices( bool min = true ); 
		void buscarCaminos_MinMaxLongitud( 
		    bool min = true ); 
		void buscarCaminosSinVertice( Vertice* ); 
		

	public:
		
		ListaD<Vertice>* lista_adyacencia; 
		ListaD<Camino>* lista_caminos; 
		ListaD<Vertice> vertices;
	
		Grafo();
		Grafo( bool, bool ); 
		Grafo( std::string, char, bool, bool ); 
		bool isDirigido() const; 
		bool isPonderado() const; 
		int getNumeroVertices() const; 
		float getLongitud() const;
		bool agregar( Vertice*, Vertice* ); 
		void BuscarCaminos();
		void buscarCaminos_maxVertices(); 
		void buscarCaminos_MinMaxLongitud_Grafo( bool min ); 
		bool buscarCaminos_MinMaxVertices_Vertices( Vertice*, Vertice*, bool min = true, Vertice* inter = NULL ); 
		bool buscarCaminos_MinMaxLongitud_Vertices(Vertice*, Vertice*, bool min = true, Vertice* inter = NULL );
		bool conectividad( Vertice*, Vertice* ); 
		void imprimirListaAdyacencia() const; 
		int imprimirListaCaminos() const;
		void SegundoCaminoMasCorto(Vertice *, Vertice*);
	
	
}; 


#endif
