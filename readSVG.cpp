
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
    void identificadorload(vector<SVGElement *> &pFigs, map<string, vector<SVGElement *>> &identif, const string &ref)
    {
        vector<SVGElement *> temp;
        string ident = ref.substr(1, string::npos); // tirar o '#' do href(referencia)//
        temp = identif[ident];
        for (SVGElement *elem : temp)
        {
            pFigs.push_back(elem->copy());
        }
    }
    void identificadorsave(const vector<SVGElement *> &pFigs, map<string, vector<SVGElement *>> &identif, const string &ident)
    {
        vector<SVGElement *> temp;
        for (SVGElement *elem : pFigs)
        {
            temp.push_back(elem->copy());
        }
        identif[ident] = temp;
    }

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

    void recursive(XMLElement *pParent, vector<SVGElement *> &svg_elements, map<string, vector<SVGElement *>> &identif)
    {
        for (XMLElement *child = pParent->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
        {
            vector<SVGElement *> figsofgrupos;
            if (strcmp(child->Name(), "ellipse") == 0)
            {
                Ellipse *ellipse_object = new Ellipse(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, {child->IntAttribute("rx"), child->IntAttribute("ry")});
                const char *transform_attr = child->Attribute("transform");
                const char *transform_origin = child->Attribute("transform-origin");
                parseTransform(ellipse_object, transform_attr, transform_origin);
                figsofgrupos.push_back(ellipse_object);
            }
            else if (strcmp(child->Name(), "circle") == 0)
            {
                Circle *circle_object = new Circle(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, child->IntAttribute("r"));
                const char *transform_attr = child->Attribute("transform");
                const char *transform_origin = child->Attribute("transform-origin");
                parseTransform(circle_object, transform_attr, transform_origin);
                figsofgrupos.push_back(circle_object);
            }
            else if (strcmp(child->Name(), "polyline") == 0)
            {
                string pontos = child->Attribute("points");
                transformcomma(pontos);
                istringstream iss(pontos);
                vector<Point> polypontos;
                Point temp;
                while (iss >> temp.x)
                {
                    iss >> temp.y;
                    polypontos.push_back(temp);
                }
                Polyline *polyline_object = new Polyline(polypontos, parse_color(child->Attribute("stroke")));
                const char *transform_attr = child->Attribute("transform");
                const char *transform_origin = child->Attribute("transform-origin");
                parseTransform(polyline_object, transform_attr, transform_origin);
                figsofgrupos.push_back(polyline_object);
            }
            else if (strcmp(child->Name(), "line") == 0)
            {
                Line *line_object = new Line({child->IntAttribute("x1"), child->IntAttribute("y1")}, {child->IntAttribute("x2"), child->IntAttribute("y2")}, parse_color(child->Attribute("stroke")));
                const char *transform_attr = child->Attribute("transform");
                const char *transform_origin = child->Attribute("transform-origin");
                parseTransform(line_object, transform_attr, transform_origin);
                figsofgrupos.push_back(line_object);
            }
            else if (strcmp(child->Name(), "polygon") == 0)
            {
                string pontos = child->Attribute("points");
                transformcomma(pontos);
                istringstream iss(pontos);
                vector<Point> polypontos;
                Point temp;
                while (iss >> temp.x)
                {
                    iss >> temp.y;
                    polypontos.push_back(temp);
                }
                Polygon *polygon_object = new Polygon(polypontos, parse_color(child->Attribute("fill")));
                const char *transform_attr = child->Attribute("transform");
                const char *transform_origin = child->Attribute("transform-origin");
                parseTransform(polygon_object, transform_attr, transform_origin);
                figsofgrupos.push_back(polygon_object);
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

                vector<Point> points;
                points.push_back(corner1);
                points.push_back(corner2);
                points.push_back(corner3);
                points.push_back(corner4);
                Rect *rect_object = new Rect(points, parse_color(child->Attribute("fill")));
                const char *transform_attr = child->Attribute("transform");
                const char *transform_origin = child->Attribute("transform-origin");
                parseTransform(rect_object, transform_attr, transform_origin);
                figsofgrupos.push_back(rect_object);
            }
            else if (strcmp(child->Name(), "g") == 0)
            {
                recursive(child, figsofgrupos, identif);
            }
            else if (strcmp(child->Name(), "use") == 0)
            {
                string ref = child->Attribute("href");
                identificadorload(figsofgrupos, identif, ref);
            }
            string ident = "";
            if (child->Attribute("id"))
            {
                ident = child->Attribute("id");
                identificadorsave(figsofgrupos, identif, ident);
            }
            svg_elements.insert(svg_elements.end(), figsofgrupos.begin(), figsofgrupos.end());
        }
    }
    
    void delmapa(map<string, vector<SVGElement *>> &identif)
    {
        // Iterate through the map and delete each vector of SVGElement pointers
        for (auto &entry : identif)
        {
            for (SVGElement *element : entry.second)
            {
                delete element; // Deallocate memory for each SVGElement
            }
            entry.second.clear(); // Clear the vector
        }
        identif.clear(); // Clear the entire map
    }

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

        map<string, vector<SVGElement *>> identif;
        recursive(xml_elem, svg_elements, identif);
    }
}