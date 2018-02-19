#ifndef NODO_H
#define NODO_H

template<class T> 
class Nodo{
	
	private: 
	
		Nodo<T>* link_pre;
		Nodo<T>* link_suc;
		T* info;
		
	public:
		
		explicit Nodo( T* inf ) : info( inf ) 
		{ this->link_pre = this->link_suc = NULL; } 
		~Nodo(); // destructor de Nodo
		Nodo<T>* getLink_pre() const; 
		Nodo<T>* getLink_suc() const; 
		T* getInfo() const; 
		void setLink_pre( Nodo<T>* const ); 
		void setLink_suc( Nodo<T>* const ); 
		void setInfo( T* const ); 
}; // fin de la template class Nodo


template<class T> Nodo<T>::~Nodo(){
	
	//delete this->info; // libera memoria campo info
	
	// asigana a NULL apuntadores
	this->link_pre = this->link_suc = NULL;
	this->info = NULL;
} // fin del destructo
 template<class T> Nodo<T>* Nodo<T>::getLink_pre() const{
 	
	return this->link_pre; // retorna referencia
 } // fin de getLink_pre

template<class T> Nodo<T>* Nodo<T>::getLink_suc() const{
	
	return this->link_suc; // retorna referencia
} // fin de getLink_suc

template<class T> T* Nodo<T>::getInfo() const{
	
	return this->info; // retorna campo info
} // fin de getInfo


template<class T> void Nodo<T>::setLink_pre( Nodo<T>* const pre ){
	
	this->link_pre = pre;
} // fin de de setLink_pre


template<class T> void Nodo<T>::setLink_suc( Nodo<T>* const suc ){
	
	this->link_suc = suc;
} // fin de de setLink_suc

template<class T> void Nodo<T>::setInfo( T* const inf ) {
	
	delete this->info; // libero campo info actual
	this->info = inf; // referencio al nuevo campo info
} // fin de de setLink_ext

#endif

