#include <iostream>
#include "Grafo.h"

using namespace std;

int main(int argc, char** argv) {
	
	Archivo* lector = new Archivo( "input.txt" );

		if(lector->abrir()){
			
			string* buffer;
			string* puntos;
			
			while(!lector->isFinal()){
				
	
				buffer = lector->leerCampos(32,2);  //buffer[0]-->numero de nodos  buffer[1]-->numero de conexiones	
				
				
				}	
				
						
		}else cout<<"no se encontro el archivo input.txt"<<endl;

	
	return 0;
}
