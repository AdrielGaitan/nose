# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?
//¿Qué es la neumonoultramicroscópicosilicovolcanoconiosis?
 
 Tambien conocida como la palabra mas grande en ingles. 
 su definicion en terminos medicos seria el nombre de una enfermedad,del sistema repiratorio.

## According to its man page, what does `getrusage` do?
//Según su página de manual, ¿qué hace `getrusage`?

getrusage es quien pone los parametros para evaluar las funciones.


## Per that same man page, how many members are in a variable of type `struct rusage`?
//Según esa misma página de manual, ¿cuántos miembros hay en una variable de tipo `struct rusage`?
 
 La variable struct rusage contiene 2 tipos de miembros, uno de tipo int y el otro de tipo char.


## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?
//¿Por qué crees que pasamos 'antes' y 'después' por referencia (en lugar de por valor) a 'calcular', aunque no estemos cambiando su contenido?

Eso es porque ambas fueron definidas como parametros para evaluar funciones en la lectura del diccionario


## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.
 //Explique con la mayor precisión posible, en un párrafo o más, cómo funciona 'main' en la lectura de palabras de un archivo.
 //En otras palabras, convéncenos de que realmente comprende cómo funciona el ciclo 'for' de esa función.
 
 El main se usa para usa para definir los argumentos y variables de tipo caracter, 
 el ciclo for de la funcion funciona como analizador que verifica si una palabra presenta
 errores ortograficos, por medio de las tildes en las palabras o si estan bien escritas ,
 de modo que si le falta algo logre corregirlo con exito.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?
//¿Por qué crees que usamos `fgetc` para leer los caracteres de cada palabra uno a la vez en lugar de usar` fscanf` con una cadena de formato como `'% s '` para leer palabras completas a la vez?
//Dicho de otra manera, ¿qué problemas pueden surgir si se confía únicamente en `fscanf`?

Se usa fgetc porque esta funcion tiene un limite de cantidad de caracteres a diferencia del fscanf la cual no lo tiene , 
por lo cual, al no tener
un limite estarian sobrecargando la memoria con un dato grande e innecesario, digo, el dado es necesario, lo innecesario es el inmenso espacio.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?
//¿Por qué crees que declaramos los parámetros para `check` y` load` como `const` (que significa' constante ')?
 
 load se usa para almacenar y leer el archivo en el diccionario,  check para hacer referencias crusadas y ver si una palabra
 determinada esta en el diccionario , y constante podria definirse como  accion  que no se interrumpe  y persiste en el estado que se encuentra 
 sin variar su  intensidad.



TODO
