
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
    void identificadorload(vector<SVGElement*>& pFigs, map<string,vector<SVGElement *>>& identif,const string& ref){
        vector<SVGElement*> temp;
        string ident = ref.substr(1,string::npos); //tirar o '#' do href(referencia)//
        temp = identif[ident];
        for (SVGElement* elem:temp){
            pFigs.push_back(elem->copy());
        }
    }
    void identificadorsave(const vector<SVGElement*>& pFigs, map<string,vector<SVGElement *>>& identif,const string& ident){
        vector<SVGElement*> temp;
        for (SVGElement* elem:pFigs){
            temp.push_back(elem->copy());
        }
        identif[ident]=temp;
    }
    void transformdot(string& prestring){
        for (char& c : prestring){
            if (c==','){
                c=' ';
            }
        }
    }
    
    Point parseTranslate(const string &str) {
        Point result;
        string numbers = str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1);
        istringstream iss(numbers);
        string x_str, y_str;
        getline(iss, x_str, ',');
        getline(iss, y_str);
        result.x = stoi(x_str);
        result.y = stoi(y_str);
        return result;
    }

    int parseScaleOrRotate(const string &str) {
        int result;
        string number = str.substr(str.find("(") + 1, str.find(")") - str.find("(") - 1);
        istringstream iss(number);
        iss >> result;
        return result;
    }

    void recursive(XMLElement *pParent,vector<SVGElement *>& svg_elements,map<string,vector<SVGElement*>>& identif){
        for (XMLElement *child = pParent->FirstChildElement(); child != nullptr; child = child->NextSiblingElement()) {
            vector<SVGElement *> figsofgrupos;
            if (strcmp(child->Name(), "ellipse") == 0) {
                Ellipse* ellipse_object = new Ellipse(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, {child->IntAttribute("rx"), child->IntAttribute("ry")});
                figsofgrupos.push_back(ellipse_object);
            } else if (strcmp(child->Name(), "circle") == 0) {
                Circle* circle_object = new Circle(parse_color(child->Attribute("fill")), {child->IntAttribute("cx"), child->IntAttribute("cy")}, child->IntAttribute("r"));
                figsofgrupos.push_back(circle_object);
            } else if (strcmp(child->Name(), "polyline") == 0) {
                string pontos = child->Attribute("points");
                transformdot(pontos);
                istringstream iss(pontos);
                vector<Point> polypontos;
                Point temp;
                while (iss >> temp.x ){
                    iss >> temp.y;
                    polypontos.push_back(temp);
                }
                Polyline* polyline_object = new Polyline(polypontos,parse_color(child->Attribute("stroke")) );
                figsofgrupos.push_back(polyline_object);
            } else if (strcmp(child->Name(), "line") == 0) {
                Line* line_object = new Line({child->IntAttribute("x1"),child->IntAttribute("y1")},{child->IntAttribute("x2"),child->IntAttribute("y2")},parse_color(child->Attribute("stroke")));
                figsofgrupos.push_back(line_object);
            } else if (strcmp(child->Name(), "polygon") == 0) {
                string pontos = child->Attribute("points");
                transformdot(pontos);
                istringstream iss(pontos);
                vector<Point> polypontos;
                Point temp;
                while (iss >> temp.x ){
                    iss >> temp.y;
                    polypontos.push_back(temp);
                }
                Polygon* polygon_object = new Polygon(polypontos,parse_color(child->Attribute("fill")));
                figsofgrupos.push_back(polygon_object);
            } else if (strcmp(child->Name(), "rect") == 0) {
                Rect* rect_object = new Rect({child->IntAttribute("x"),child->IntAttribute("y")},child->IntAttribute("width"),child->IntAttribute("height"),parse_color(child->Attribute("fill")));
                figsofgrupos.push_back(rect_object);
            } else if (strcmp(child->Name(), "g") == 0) {
                recursive(child,figsofgrupos,identif);
            } else if (strcmp(child->Name(), "use") == 0) {
                string ref = child->Attribute("href");
                identificadorload(figsofgrupos,identif,ref);
            }
            string ident="";
            if (child->Attribute("id")){
                ident = child->Attribute("id");
                identificadorsave(figsofgrupos,identif,ident);

            } 
            svg_elements.insert(svg_elements.end(),figsofgrupos.begin(),figsofgrupos.end());
        }
    }
    void delmapa(map<string,vector<SVGElement *>> identif){
        //por concluir desalocar memoria
    }
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
        
        map<string,vector<SVGElement *>> identif;

        recursive(xml_elem,svg_elements,identif);
}
}