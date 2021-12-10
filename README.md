# ArrayExamples

El problema no es que tengamos CMonoBuffers ni std::vectors. El problema es que un array de arrays no equivale a un puntero a puntero. Pero se puede arreglar
con un truquillo que se puede ver en el main (un pequeño array auxiliar de punteros a los buffers). 

He sacado la idea de estas transparencias estupendas https://cs.brynmawr.edu/Courses/cs246/spring2014/Slides/16_2DArray_Pointers.pdf
