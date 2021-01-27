# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Es un termino utilizado para referirse a una enfermedad pulmonar ocasionada por
la absorcion de ceniza volcanica en el sistema respiratorio.

## According to its man page, what does `getrusage` do?

Devuelve medidas de uso de recursos relacionados al proceso que se esta realizando en el momento

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

porque Rusage posee una gran cantidad de memoria, es mejor pasarlo por referencia en lugar de realizar copias

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.
// Explique de la manera más precisa posible, en un párrafo o más, cómo `main` trata la lectura de palabras de un archivo. 
//En otras palabras, convencernos de que realmente comprende cómo funciona el bucle `for` de esa función.

El For en el main lee cada letra hasta llegar al fin de la linea, luego realiza un salto de linea.
Las palabras ingresadas solamente pueden contener letras o apostrofes, de otra forma el programa no lee lo
que se ha ingresado ya que no alcanza en la longitud y por lo tanto no encaja en el bufer. Ademas las palabras
ingresadas no pueden tener una longitud superior a 45 letras.
Las palabras completas se terminan con un caracter NUL y se comparan en el diccionario.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

Porque en un "%s" se lee tanto numeros como caracteres, lo cual no es valido en el programa ya que no esta
en la palabra y no puede compararse en el diccionario.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

Porque constantemente debe cargarse la informacion del diccionario y verificar si existe para compararlo con
la palabra.
