
#include <iostream>
#include "SVGElements.hpp"
#include "Color.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <sstream>
#include <map>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    map<string, SVGElement *> mapa_use;

    /**
     * @brief Transforms all the commas in a string to spaces.
     *
     * @param prestring The string containing commas.
     */
    void transformcomma(string &prestring)
    {
        for (char &c : prestring)
        {
            if (c == ',')
            {
                c = ' ';
            }
        }
    }

    /**
     * @brief Parses a translate string and returns a Point object representing the translation.
     *
     * @param str The translate string in the format "translate(x, y)" or "translate(x y)".
     * @return A Point struct representing the translation, with x and y coordinates.
     */
    Point parseTranslate(const string &str)
    {
        Point result;
        string numbers = str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1);
        transformcomma(numbers);
        istringstream iss(numbers);
        string x_str, y_str;
        getline(iss, x_str, ' ');
        getline(iss, y_str);
        result.x = stoi(x_str);
        result.y = stoi(y_str);
        return result;
    }

    /**
     * @brief Parses a scale or rotate string and returns a Point object representing respectivily.
     *
     * @param str The string in the format "scale(x)" or "rotate(x)".
     * @return An integer representing the scaling or rotation.
     */
    int parseScaleOrRotate(const string &str)
    {
        int result;
        string number = str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1);
        istringstream iss(number);
        iss >> result;
        return result;
    }

    /**
     * @brief Parses a point string and returns it in a point struct.
     *
     * @param str The translation string in the format "x y".
     * @return A Point struct with x and y coordinates.
     */
    Point parsePoint(const string &str)
    {
        Point result;
        istringstream iss(str);
        iss >> result.x >> result.y;
        return result;
    }

    /**
     * @brief Parses the corresponding transformation and applies it to the SVG element.
     *
     * @param element The SVG element to apply the transformation.
     * @param transformAttribute The type of transformation.
     * @param transformOrigin The origin point of the transformation.
     * @return A Point object representing the translation, with x and y coordinates.
     */
    void parseTransform(SVGElement *element, const char *transformAttribute, const char *transformOrigin)
    {
        if (transformAttribute && strstr(transformAttribute, "translate") != nullptr)
        {
            string transform_str(transformAttribute);
            Point translate = parseTranslate(transform_str);
            element->translate(translate);
        }
        else if (transformAttribute && strstr(transformAttribute, "scale") != nullptr)
        {
            string transform_str(transformAttribute);
            int scale = parseScaleOrRotate(transform_str);
            if (transformOrigin)
            {
                Point transformOriginPoint = parsePoint(transformOrigin);
                element->scale(transformOriginPoint, scale);
            }
            else
            {
                element->scale({0, 0}, scale);
            }
        }
        else if (transformAttribute && strstr(transformAttribute, "rotate") != nullptr)
        {
            string transform_str(transformAttribute);
            int rotate = parseScaleOrRotate(transform_str);
            if (transformOrigin)
            {
                Point transformOriginPoint = parsePoint(transformOrigin);
                element->rotate(transformOriginPoint, rotate);
            }
            else
            {
                element->rotate({0, 0}, rotate);
            }
        }
    }

    /**
     * @brief Recursively parses an XML element and creates corresponding SVG elements.
     * @param pParent The parent XML element to parse.
     * @return A pointer to the created SVG element.
     */
    SVGElement *recursive(XMLElement *pParent)
    {
        vector<SVGElement *> figsofgrupos;
        for (XMLElement *child = pParent->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            SVGElement *p;
            // Check which element to add to figsofgrupos.
            if (strcmp(child->Name(), "ellipse") == 0)
            {
                p = new Ellipse(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, {child->IntAttribute("rx"), child->IntAttribute("ry")});
            }
            else if (strcmp(child->Name(), "circle") == 0)
            {
                p = new Circle(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, child->IntAttribute("r"));
            }
            else if (strcmp(child->Name(), "polyline") == 0)
            {
                string pontos = child->Attribute("points");
                transformcomma(pontos);
                istringstream iss(pontos);
                vector<Point> polypontos;
                Point temp;
                // Get coordinates (x, y) from input.
                while (iss >> temp.x)
                {
                    iss >> temp.y;
                    polypontos.push_back(temp);
                }
                p = new Polyline(polypontos, parse_color(child->Attribute("stroke")));
            }
            else if (strcmp(child->Name(), "line") == 0)
            {
                p = new Line({child->IntAttribute("x1"), child->IntAttribute("y1")}, {child->IntAttribute("x2"), child->IntAttribute("y2")}, parse_color(child->Attribute("stroke")));
            }
            else if (strcmp(child->Name(), "polygon") == 0)
            {
                string pontos = child->Attribute("points");
                transformcomma(pontos);
                istringstream iss(pontos);
                vector<Point> polypontos;
                Point temp;
                // Get coordinates (x, y) from input.
                while (iss >> temp.x)
                {
                    iss >> temp.y;
                    polypontos.push_back(temp);
                }
                p = new Polygon(polypontos, parse_color(child->Attribute("fill")));
            }
            else if (strcmp(child->Name(), "rect") == 0)
            {
                int x = child->IntAttribute("x");
                int y = child->IntAttribute("y");
                int width = child->IntAttribute("width");
                int height = child->IntAttribute("height");
                Point corner1, corner2, corner3, corner4;
                corner1.x = x;
                corner1.y = y;

                corner2.x = x + width - 1;
                corner2.y = y;

                corner3.x = x + width - 1;
                corner3.y = y + height - 1;

                corner4.x = x;
                corner4.y = y + height - 1;

                vector<Point> points; // Add every corner of the rectangle to a vector of points.
                points.push_back(corner1);
                points.push_back(corner2);
                points.push_back(corner3);
                points.push_back(corner4);
                p = new Rect(points, parse_color(child->Attribute("fill")));
            }
            else if (strcmp(child->Name(), "g") == 0)
            {
                p = recursive(child); // Recursive case call for groups.
            }
            else if (strcmp(child->Name(), "use") == 0)
            {
                string ref = child->Attribute("href");
                string ident = ref.substr(1, string::npos);
                // Copy the object from the map using the identifier as the key
                p = mapa_use[ident]->copy();
            }
            // Initialize an empty identifier
            string ident = "";
            if (child->Attribute("id"))
            {
                // Get the id attribute of the child
                ident = child->Attribute("id");
                // Add the object to the map with the identifier as the key
                mapa_use[ident] = p;
            }
            if (child->Attribute("transform"))
            {
                const char *transform_attr = child->Attribute("transform");
                const char *transform_origin = child->Attribute("transform-origin");
                parseTransform(p, transform_attr, transform_origin);
            }
            figsofgrupos.push_back(p);
        }
        return new Group(figsofgrupos);
    }

    /**
     * Reads an SVG file and extracts the dimensions and SVG elements.
     *
     * @param svg_file The path to the SVG file to be read.
     * @param dimensions The reference to a Point object where the dimensions of the SVG will be stored.
     * @param svg_elements The reference to a vector of SVGElement pointers where the extracted SVG elements will be stored.
     */
    void readSVG(const string &svg_file, Point &dimensions, vector<SVGElement *> &svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        SVGElement *A = recursive(xml_elem);
        svg_elements.push_back(A);
    }
}