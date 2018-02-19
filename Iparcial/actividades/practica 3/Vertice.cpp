#include "Vertice.h"
using namespace std;

Vertice::Vertice( string identificador, double longitud ){
	
	this->vertices_adyacentes = new ListaD<Vertice>();
	this->identificador = identificador; // asigna identificador
	this->longitud_arista = longitud; // asigna longitud_arista
} // fin del contsructor

double Vertice::getLongitudArista() const{
	
	return this->longitud_arista; // retorna longitud
} // fin de getLongitudArista

string Vertice::getIdentificador() const {
	
	return this->identificador; // retorna campo info
} // fin de getIdentificador

ostream& operator<<( ostream& salida, const Vertice& datos ){
	
	// imprime identificador del vertice
	salida << datos.identificador;
		
	return salida; // retorna el objeto del flujo de salida
} // fin de operator<<

bool Vertice::operator==( const Vertice& datos ){
	
	return ( this->identificador == datos.identificador ); // retorna desición  
} // fin de operator==




