# ArrayExamples

El problema no es que tengamos CMonoBuffers ni std::vectors. El problema es que un array de arrays no equivale a un puntero a puntero. Pero se puede arreglar
con un truquillo que se puede ver en el main (un pequeño array auxiliar de punteros a los buffers). 
