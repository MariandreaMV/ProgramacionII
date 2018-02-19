#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char** argv)
{
	int filas, iterador_anterior = 0, posicion_final = 1, espacios = 0;

	vector<vector<int> > vectores;

	cout << "ingrese numero de filas a generar: ";
	cin >> filas;

	espacios = filas;

	if (filas == 1)
		cout << 1 << endl;
	else
		for (int y = 0; y < filas; y++) {
			vector<int> vector_fila; 
			 
			for (int x = 0; x < posicion_final; x++) {
				if (x == 0 || x == posicion_final - 1)
					vector_fila.push_back(1);
				else {
					int suma = vectores[y-1][iterador_anterior] + vectores[y-1][iterador_anterior+1];
					vector_fila.push_back(suma);
					iterador_anterior++;
				}
			}

			for (int x = 0; x < espacios; x++)
				cout << "  ";
				
			for(int x = 0; x < vector_fila.size(); x++)
				cout << vector_fila[x] << "   ";
		
			espacios--;
			cout << endl;
			vectores.push_back(vector_fila);
			posicion_final++;
			iterador_anterior = 0;
		}
	return 0;
}
