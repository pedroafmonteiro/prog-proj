# Programming project (L.EIC009)

## Description

This project concerns the conversion of images from the SVG vectorial format to the PNG raster format.

## Group elements

- up202304912 Vasco Nuno Pinhal Ferreira Alves 
- up202305431 Narciso António Terrão Barroso
- up202307242 Pedro André Freitas Monteiro

## Tasks

### SVG reading logic in readSVG.cpp

To complete the `readSVG` function in `readSVG.cpp`, we need to traverse the XML child nodes of the root SVG element and parse the SVG elements that are defined. Here's a step-by-step guide:

1. After getting the dimensions from the root SVG element, we need to iterate over its child nodes. We can use a loop with `xml_elem->FirstChildElement()` and `xml_elem->NextSiblingElement()` to traverse the child nodes.

2. For each child node, we need to determine the type of SVG element it represents. This can be done by checking the name of the element using `xml_elem->Name()`. The name will correspond to the type of SVG element (e.g., "circle", "rect", "line", etc.).

3. Once you know the type of the SVG element, we can parse the attributes of the element to create a new instance of the corresponding `SVGElement` subclass. For example, if the element is a circle, we would create a new instance of `SVGCircle`. The attributes of the element (e.g., "cx", "cy", "r" for a circle) can be accessed using `xml_elem->Attribute()`.

4. We should use the `Color::parse(std::string)` function from `Color.cpp` to parse color attributes.

5. After creating the new `SVGElement` instance, we will add it to the `svg_elements` vector using `svg_elements.push_back()`.

6. Continue this process until all child nodes of the root SVG element have been traversed and processed.

Common erros: if an SVG element has missing or invalid attributes or if an unknown SVG element type is encountered.