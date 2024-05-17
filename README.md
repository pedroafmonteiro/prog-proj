# Programming project (L.EIC009)

## Description

This project concerns the conversion of images from the SVG vectorial format to the PNG raster format.

## Group elements

- up202304912 Vasco Nuno Pinhal Ferreira Alves 
- up202305431 Narciso António Terrão Barroso
- up202307242 Pedro André Freitas Monteiro

## Accomplished tasks
### SVG reading logic in [readSVG.cpp](readSVG.cpp)

The image dimensions are obtained successfully with their respect width and height and every type of element can be dynamically allocated as a SVGElement* pointer.

### Geometrical elements

Every geometrical element have their own class defined in [SVGElements.hpp](SVGElements.hpp)derived from their superior element or from the SVGElement class. All elements have their respect attributes and support for identifiers and transformations parameters and functions.

### Element transformations

All types of transformations (translate, rotate and scale) are well implemented and binded for every type of element using virtual pure functions. The function that parses every transformation is in the file [readSVG.cpp](readSVG.cpp).

### Groups

### Element duplication