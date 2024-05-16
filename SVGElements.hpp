//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;                     // Declaration of the draw virtual pure function for each SVG element.
        virtual Point translate(const Point &t) const = 0;              // Declaration of the translate virtual pure function for each SVG element.
        virtual Point rotate(const Point &origin, 
                             int degrees) const = 0;                    // Declaration of the rotate virtual pure function for each SVG element.
        virtual Point scale(const Point &origin, 
                            int v) const = 0;                           // Declaration of the scale virtual pure function for each SVG element.
        virtual SVGElement* copy() const = 0;                           // Declaration of the translate virtual pure function for each SVG element.
        std::string id;
    };

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);              // Declaration of namespace function readSVG.
    void convert(const std::string &svg_file,
                 const std::string &png_file);                          // Declaration of namespace function convert.

    /**
     * @class Ellipse
     * @brief Represents an ellipse SVG element.
     */
    class Ellipse : public SVGElement
    {
    public:
        /**
         * @brief Constructs an Ellipse object.
         * 
         * @param fill The fill color of the ellipse.
         * @param center The center point of the ellipse.
         * @param radius The radius of the ellipse.
         * @param id The id of the ellipse.
         */
        Ellipse(const Color &fill,
                const Point &center, 
                const Point &radius, 
                const std::string &id = "");  

        void draw(PNGImage &img) const override;                        // Declaration of the Ellipse's draw function.
        Point translate(const Point &t) const override;                 // Declaration of the Ellipse's translate function.
        Point rotate(const Point &origin, 
                     int degrees) const override;                       // Declaration of the Ellipse's rotate function.
        Point scale(const Point &origin, 
                    int v) const override;                              // Declaration of the Ellipse's scale function.
        SVGElement* copy() const override;                              // Declaration of the Ellipse's copy function.

    protected:
        Color fill;     // The fill color of the ellipse.
        Point center;   // The center point of the ellipse.
        Point radius;   // The radius of the ellipse.
    };

    /**
     * @class Circle
     * @brief Represents a circle SVG element.
     */
    class Circle : public Ellipse
    {
    public:
        /**
         * @brief Constructs a Circle object with the specified fill color, center point, and radius.
         * 
         * @param fill The fill color of the circle.
         * @param center The center point of the circle.
         * @param radius The radius of the circle.
         * @param id The id of the circle.
         */
        Circle(const Color &fill, 
            const Point &center, 
            const int &radius, 
            const std::string &id = "") 
        : Ellipse(fill, center, {radius , radius}, id) { };

        void draw(PNGImage &img) const override;                        // Declaration of the Circle's draw function.
        Point translate(const Point &t) const override;                 // Declaration of the Circle's translate function.
        Point rotate(const Point &origin, 
                     int degrees) const override;                       // Declaration of the Circle's rotate function.
        Point scale(const Point &origin, 
                    int v) const override;                              // Declaration of the Circle's scale function.
        SVGElement* copy() const override;                              // Declaration of the Circle's copy function.
    };

    /**
     * @class Polyline
     * @brief Represents a polyline SVG element.
     */
    class Polyline : public SVGElement
    {
    public:
        /**
         * @brief Constructs a Polyline object with the given points and stroke color.
         * 
         * @param points The vector of points that define the polyline.
         * @param stroke The color of the polyline stroke.
         * @param id The id for the polyline.
         */
        Polyline(const std::vector<Point> &points, 
                 const Color &stroke, 
                 const std::string &id = "");

        void draw(PNGImage &img) const override;                        // Declaration of the Polyline's draw function.
        Point translate(const Point &t) const override;                 // Declaration of the Polyline's translate function.
        Point rotate(const Point &origin, 
                     int degrees) const override;                       // Declaration of the Polyline's rotate function.
        Point scale(const Point &origin, 
                    int v) const override;                              // Declaration of the Polyline's scale function.
        SVGElement* copy() const override;                              // Declaration of the Polyline's copy function.

    protected:
        std::vector<Point> points; // The vector of points that define the polyline.
        Color stroke;              // The color of the polyline stroke.
    };

    /**
     * @class Line
     * @brief Represents a line SVG element.
     */
    class Line : public Polyline
    {
    public:
        /**
         * @brief Constructs a Line object with the given start and end points and stroke color.
         * 
         * @param start The starting point of the line.
         * @param end The ending point of the line.
         * @param stroke The color of the line stroke.
         * @param id The id of the line.
         */
        Line(const Point &start, 
             const Point &end, 
             const Color &stroke, 
             const std::string &id = "") 
        : Polyline({start, end}, stroke, id), start(start), end(end) { };

        void draw(PNGImage &img) const override;                        // Declaration of the Line's draw function.
        Point translate(const Point &t) const override;                 // Declaration of the Line's translate function.
        Point rotate(const Point &origin, 
                     int degrees) const override;                       // Declaration of the Line's rotate function.
        Point scale(const Point &origin, 
                    int v) const override;                              // Declaration of the Line's scale function.
        SVGElement* copy() const override;                              // Declaration of the Line's copy function.

    private:
        Point start;    // The starting point of the line.
        Point end;      // The ending point of the line.
    };

    /**
     * @class Polygon
     * @brief Represents a polygon SVG element.
     */
    class Polygon : public SVGElement
    {
    public:
        /**
         * @brief Constructs a `Polygon` object with the given points and fill color.
         * 
         * @param points The vector of points that define the vertices of the polygon.
         * @param fill The fill color of the polygon.
         * @param id The id for the polygon.
         */
        Polygon(const std::vector<Point> &points, 
                const Color &fill, 
                const std::string &id = "");

        void draw(PNGImage &img) const override;                        // Declaration of the Polygon's draw function.
        Point translate(const Point &t) const override;                 // Declaration of the Polygon's translate function.
        Point rotate(const Point &origin, 
                     int degrees) const override;                       // Declaration of the Polygon's rotate function.
        Point scale(const Point &origin, 
                    int v) const override;                              // Declaration of the Polygon's scale function.
        SVGElement* copy() const override;                              // Declaration of the Polygon's copy function.

    protected:
        std::vector<Point> points; // The vector of points that define the vertices of the polygon.
        Color fill;                // The fill color of the polygon.
    };

    /**
     * @class Rect
     * @brief Represents a rectangle SVG element.
     */
    class Rect : public Polygon
    {
    public:
        /**
         * @brief Constructs a `Rect` object with the specified corner, width, height, and fill color.
         * 
         * @param corner The top-left corner of the rectangle.
         * @param width The width of the rectangle.
         * @param height The height of the rectangle.
         * @param fill The fill color of the rectangle.
         */
        Rect(const Point &corner, 
             const int &width, 
             const int &height, 
             const Color &fill, 
             const std::string &id = "") 
        : Polygon({Point(corner), Point({corner.x + width-1, corner.y}), Point({corner.x + width-1, corner.y + height-1}), Point({corner.x, corner.y + height-1})}, fill, id), corner(corner), width(width), height(height) { };

        void draw(PNGImage &img) const override;                        // Declaration of the Rectangle's draw function.
        Point translate(const Point &t) const override;                 // Declaration of the Rectangle's translate function.
        Point rotate(const Point &origin, 
                     int degrees) const override;                       // Declaration of the Rectangle's rotate function.
        Point scale(const Point &origin, 
                    int v) const override;                              // Declaration of the Rectangle's scale function.
        SVGElement* copy() const override;                              // Declaration of the Rectangle's copy function.

    private:
        Point corner;   // The top-left corner of the rectangle.
        int width;      // The width of the rectangle.
        int height;     // The height of the rectangle.
    };
}
#endif
