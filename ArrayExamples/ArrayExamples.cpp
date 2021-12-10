// ArrayExamples.cpp 
//

#include <iostream>
#include <vector>

// Miniversión de CMonoBuffer
template <unsigned int NChannels,class stored>
class CBuffer : public std::vector<stored, std::allocator<stored>> {
	using std::vector<stored>::vector;    //   inherit all std::vector constructors
};
template<class stored>
using CMonoBuffer = CBuffer<1, stored>;


constexpr int nsalidas = 2; // suponemos hay sólo 2 fuentes en el array de salida

// El problema no es que tengamos CMonoBuffers ni std::vectors. 
// El problema es que un array de arrays no equivale a un puntero a puntero. Pero se puede arreglar
// con un truquillo que se puede ver en el main (un pequeño array auxiliar de punteros a los buffers). 

// Función tontorrona que simplemente copia de la entrada a las salidas. 
void Run(float* input_array, int nsamples, float** output_array) 
{
	for (int i = 0; i<nsalidas; i++) {
		std::copy(input_array, input_array + nsamples, output_array[i]);
	}
}
int main()
{

	//Llamo a la función tres veces, una con arrays, otra con vectores y otra con CMonoBuffers.
	//Perdonad si me puesto en plan muy profe pesao e id directamente a los monobuffers si queréis :)

	// 1) CON ARRAYS
	float input[6] = { 3,3,3,3,3,3 };
	float output[nsalidas][6] = { {0,0,0,0,0,0}, {0,0,0,0,0,0} }; 
	float* aux[nsalidas]; // array de punteros auxiliar, de tamaño el número de filas de output 
	for (int i = 0; i < nsalidas; i++) {
		aux[i] = (float*)output + i * 6; // ...que hacemos apuntar a cada fila
	}
	Run(input, 6, (float**)aux);
	std::cout << "output[0][0]" << output[0][0] << std::endl;

	// 2) CON STD::VECTORS
	std::vector<float> vinput{ 3,3,3,3,3,3 };
	std::vector< std::vector<float> > voutput{{0,0,0,0,0,0}, {0,0,0,0,0,0} };
	float* vaux[nsalidas]; // array de punteros auxiliar, de tamaño el número de filas de voutput
	for (int i = 0; i < nsalidas; i++) {
		vaux[i] = voutput[i].data(); //...que hacemos apuntar a cada fila
	}
	Run(vinput.data(), 3, (float**)vaux) ; 
	std::cout << "voutput[0][0]:" << voutput[0][0] << std::endl;

	// 3) CON MONOBUFFERS
	CMonoBuffer<float> binput{ 3,3,3,3,3,3 };
	std::vector< CMonoBuffer<float> > boutput{ {0,0,0,0,0,0}, {0,0,0,0,0,0} };
	float* baux[nsalidas]; // array de punteros auxiliar, de tamaño el número de filas de boutput
	for (int i = 0; i < nsalidas; i++) {
		baux[i] = boutput[i].data(); //...que hacemos apuntar a cada fila (buffer)
	}
	Run(binput.data(), 3, (float**)baux);
	std::cout << "boutput[0][0]:" << boutput[0][0] << std::endl;

	return 0;
}

