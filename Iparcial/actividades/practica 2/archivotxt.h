#ifndef ARCHIVOTXT_H
#define ARCHIVOTXT_H

#include <string>
#include <fstream>

class ArchivoTXT
{
	private:
		std::string nombre;
		std::fstream flujo;
		bool isFinLinea( const char );

	public:
		ArchivoTXT() {}
		explicit ArchivoTXT( std::string );
		~ArchivoTXT();
		std::string getNombre() const; // retorna el nombre del archivo asociado
		bool abrir(); // apertura el archivo, asociandolo con el flujo
		std::string leerLinea(); // lee linea del archivo asociado y la retorna
		std::string leerLinea( const char ); // sin el caracter especificado
		std::string leerCampo( const char ); // delimitador especificado
		std::string* leerCampos( const char, const unsigned int );  //arreglo de campos(linea)
		bool isFinal() const;
};


#endif
