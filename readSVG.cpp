
#include <iostream>
#include "SVGElements.hpp"
#include "Color.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <sstream>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
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
        
        for (XMLElement *child = xml_elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
            if (strcmp(child->Name(), "ellipse") == 0) {
                Ellipse* ellipse_object = new Ellipse(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, {child->IntAttribute("rx"), child->IntAttribute("ry")});
                svg_elements.push_back(ellipse_object);
            } else if (strcmp(child->Name(), "circle") == 0) {
                Circle* circle_object = new Circle(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, child->IntAttribute("r"));
                svg_elements.push_back(circle_object);
            } else if (strcmp(child->Name(), "polyline") == 0) {
                istringstream iss(child->Attribute("points"));
                vector<Point> polypontos;
                Point temp;
                while (iss >> temp.x ){
                    char virgula;
                    iss >> virgula;
                    iss >> temp.y;
                    polypontos.pushback(temp);
                }
                Polyline* polyline_object = new Polyline(polypontos,parse_color(child->Attribute("stroke")) );
                svg_elements.push_back(polyline_object);
            } else if (strcmp(child->Name(), "line") == 0) {
                Line* line_object = new Line({child->IntAttribute("x1"),child->IntAttribute("y1")},{child->IntAttribute("x2"),child->IntAttribute("y2")},parse_color(child->Attribute("stroke")));
                svg_elements.push_back(line_object);
            } else if (strcmp(child->Name(), "polygon") == 0) {
                istringstream iss(child->Attribute("points"));
                vector<Point> polypontos;
                Point temp;
                while (iss >> temp.x ){
                    char virgula;
                    iss >> virgula;
                    iss >> temp.y;
                    polypontos.pushback(temp);
                }
                Polygon* polygon_object = new Polygon(polypontos,parse_color(child->Attribute("fill")));
                svg_elements.push_back(polygon_object);
            } else if (strcmp(child->Name(), "rect") == 0) {
                Rect* rect_object = new Rect({child->IntAttribute("x"),child->IntAttribute("y")},child->IntAttribute("width"),child->IntAttribute("height"),parse_color(child->Attribute("fill")));
                svg_elements.push_back(rect_object);
            }
    }
}
}