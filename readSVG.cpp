
#include <iostream>
#include "SVGElements.hpp"
#include "Color.hpp"
#include "external/tinyxml2/tinyxml2.h"

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
            }
        }
        
    }
}