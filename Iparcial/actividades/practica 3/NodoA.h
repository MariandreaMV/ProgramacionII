#ifndef NODOA_H
#define NODOA_H

template<class T>
class NodoA
{
	private: 
		
		NodoA<T>* link_hd; 
		NodoA<T>* link_hi; 
		T* info; 
		int nivel; 
		int altura_der; 
		int altura_izq; 
		int altura;
		int factorE; 
		bool hoja;
		
	public:
		
		explicit NodoA( T* inf ) : info( inf ) { 
		
			this->link_hd = this->link_hi = NULL;
			this->altura = this->altura_der = this->altura_izq = 0;
			this->nivel = this->factorE = 0;
			this->hoja = true; 
		} // fin del NodoA
		
		~NodoA(); 
		bool isHoja() const; 
		NodoA<T>* getLink_hd() const; 
		NodoA<T>* getLink_hi() const; 
		T* getInfo() const; 
		int getNivel() const; 
		int getAltura_der() const; 
		int getAltura_izq() const; 
		int getAltura() const; 
		int getFactorE() const; 
		void setLink_hd( NodoA<T>* const ); 
		void setLink_hi( NodoA<T>* const ); 
		void setInfo( T* const ); 
		void setInfo( T ); 
		void setNivel( int ); 
		void setAltura_der( int ); 
		void setAltura_izq( int ); 
		void setAltura( int );
		void setFactorE( int ); 
		void actualizar(); 
}; // fin de NodoA


template<class T> NodoA<T>::~NodoA(){
	
	this->link_hd = this->link_hi = NULL;
	this->info = NULL;
	this->altura = this->altura_der = this->altura_izq =
		this->factorE = this->nivel = this->hoja = 0;
} // fin del destructor


 template<class T> bool NodoA<T>::isHoja() const{
 	
	return this->hoja; // retorna atributo
 } // fin de isHoja


 template<class T> NodoA<T>* NodoA<T>::getLink_hd() const{
 	
	return this->link_hd; // retorna apuntador
 } // fin de getLink_hd
 

template<class T> NodoA<T>* NodoA<T>::getLink_hi() const{
	
	return this->link_hi; // retorna referencia
} // fin de getLink_hi


template<class T> T* NodoA<T>::getInfo() const {
	
	return this->info; // retorna apuntador a campo info
} // fin de getInfo

template<class T> int NodoA<T>::getNivel() const{
	
	return this->nivel;
} // fin de getNivel

template<class T> int NodoA<T>::getAltura_der() const{
	
	return this->altura_der;
} // fin de getAltura_der

template<class T> int NodoA<T>::getAltura_izq() const{
	
	return this->altura_izq;
} // fin de getAltura_izq


template<class T> int NodoA<T>::getAltura() const{
	
	return this->altura;
} // fin de getAltura

template<class T> int NodoA<T>::getFactorE() const{
	
	return this->factorE;
} // fin de getFactorE


template<class T> void NodoA<T>::setLink_hd( NodoA<T>* const hd ){
	
	this->link_hd = hd;
} // fin de de setLink_hd

template<class T> void NodoA<T>::setLink_hi( NodoA<T>* const hi ){
	
	this->link_hi = hi;
} // fin de de setLink_hi

template<class T> void NodoA<T>::setInfo( T* const inf ){
	
	delete this->info; // libero campo info actual
	this->info = inf; // referencio al nuevo campo info
} // fin de de setLink_ext


template<class T> void NodoA<T>::setInfo( T inf ){
	
	*this->info = inf; // nuevo campo info
} // fin de de setLink_ext

template<class T> void NodoA<T>::setNivel( int nivel ){
	
	this->nivel = nivel;
} // fin de de setNivel


template<class T> void NodoA<T>::setAltura_der( int altura_der ){
	
	this->altura_der = altura_der;
} // fin de de setAltura_der

template<class T> void NodoA<T>::setAltura_izq( int altura_izq ){
	
	this->altura_izq = altura_izq;
} // fin de de setAltura_izq

template<class T> void NodoA<T>::setAltura( int altura ){
	
	this->altura = altura;
} // fin de de setAltura

template<class T> void NodoA<T>::setFactorE( int factorE ){
	
	this->factorE = factorE;
} // fin de de setFactorE

template<class T> void NodoA<T>::actualizar(){
	
	this->altura = ( this->altura_der > this->altura_izq ? 
		this->altura_der : this->altura_izq );
	this->hoja = ( this->altura == 0 ); 
		
	this->factorE = this->altura_der - this->altura_izq;
} // fin de de actualizar

#endif
