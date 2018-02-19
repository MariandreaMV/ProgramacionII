#include <iostream>
#include "archivotxt.h"
#include "MyLinkedList.h"
#include <vector>
#include <cstring>
#include "Colas_dinamicas.h"
#include "Pilas_dinamicas.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
int main(int argc, char** argv) {
	
	ArchivoTXT lector("Listas.txt");
	int numero;
	
	if (lector.abrir()){
		while(true){
			
		MyLinkedList<string> ordenTipos;
		MyLinkedList<string> tipos;
		MyLinkedList<int> listadoNumeros;
		MyLinkedList<string> listadoPalabras;
		Colas_dinamicas<string> listadoPalabrasOriginales;
		Pilas_dinamicas<string> pila;
		Pilas_dinamicas<int> pilaNumeros;
		Pilas_dinamicas<string> tiposOrden;
	
		
			string linea = lector.leerCampo('.');
			if(linea.length()==0) break;
			//cout<<linea<<" FIN LINEA"<<endl;
			string	palabra="";
			int i=0;
			bool fin=false;
			while(true){
					
					if(linea[i]==','||!linea[i]||linea[i]=='\n'){
						if(palabra.length()!=0){
							if(isdigit(palabra[0])||palabra[0]=='-'){
								int numero=atoi(palabra.c_str());
								tipos.agregar("int");
								listadoNumeros.ordenar(numero);
							} 
							else{
								tipos.agregar("string");
								listadoPalabrasOriginales.AnadirFinal(palabra);
								for(int i=0;i<palabra.size();i++){
									palabra[i]=tolower(palabra[i]);
								}
								listadoPalabras.ordenar(palabra);
							}
							palabra="";
						}
					}else{
						if(!(linea[i]==' '))
						palabra=palabra+linea[i];
						
					}	
					if(!linea[i]) break;			
				i++;	
			}
			
			int indicador=listadoPalabras.getsize();
			
			for(int m=0;m<listadoPalabras.getsize();m++){
				string word;
				listadoPalabras.eliminar(word);
				pila.AnadirFinal(word);
			}
			
			
			for(int m=0;m<listadoNumeros.getsize();m++){
				int nume;
				listadoNumeros.eliminar(nume);
				pilaNumeros.AnadirFinal(nume);
			}
			
			int indicadorTipos = tipos.getsize();
			for(int m=0;m<tipos.getsize();m++){
				string t;
				tipos.eliminar(t);
				tiposOrden.AnadirFinal(t);
			}
			
			for(int m=0;m<indicadorTipos;m++){
				string tipo=tiposOrden.Leer();
				if(tipo=="int"){
					int num= pilaNumeros.Leer();
					cout<<num<<" ";
				}else{
				string word = pila.Leer();			
				
					for(int n=0; n< indicador; n++){
						string palabra_Original=listadoPalabrasOriginales.Leer();
						string original;
						original=palabra_Original;
						
						for(int i=0;i<palabra_Original.size();i++){
									palabra_Original[i] = tolower(original[i]);
						}

						if((strcmp(palabra_Original.c_str(),word.c_str())==0)){
							cout<<original<<" ";
							indicador--;
							break;
						}else{
							listadoPalabrasOriginales.AnadirFinal(original);
						} 
						
					}
				}
			}
			
			cout<<"."<<endl;
			
		}
	}	
	else 
		cout <<"no encontrado el archivo Listas.txt"<<endl;
	return 0;
}
