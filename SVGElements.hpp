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
        virtual void draw(PNGImage &img) const = 0;

        std::string id;
        std::string transform;
        Point transformOrigin;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    /**
     * @class Ellipse
     * @brief Represents an ellipse SVG element.
     * 
     * The Ellipse class inherits from the SVGElement class and provides
     * functionality to draw an ellipse on a PNGImage.
     */
    class Ellipse : public SVGElement
    {
    public:
        /**
         * @brief Constructs an Ellipse object with the specified fill color, center point, and radius.
         * 
         * @param fill The fill color of the ellipse.
         * @param center The center point of the ellipse.
         * @param radius The radius of the ellipse.
         */
        Ellipse(const Color &fill, const Point &center, const Point &radius);

        /**
         * @brief Draws the ellipse on the specified PNGImage.
         * 
         * @param img The PNGImage to draw the ellipse on.
         */
        void draw(PNGImage &img) const override;

    private:
        Color fill;     ///< The fill color of the ellipse.
        Point center;   ///< The center point of the ellipse.
        Point radius;   ///< The radius of the ellipse.
    };

    /**
     * @class Circle
     * @brief Represents a circle shape.
     * 
     * The Circle class inherits from the Ellipse class and represents a circle shape
     * with a specified fill color, center point, and radius.
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
         */
        Circle(const Color &fill, const Point &center, const int &radius) : Ellipse(fill, center, {radius , radius}) { };

        /**
         * @brief Draws the circle on the specified PNG image.
         * 
         * @param img The PNG image to draw the circle on.
         */
        void draw(PNGImage &img) const override;

    private:
        Color fill;     ///< The fill color of the circle.
        Point center;   ///< The center point of the circle.
        int radius;     ///< The radius of the circle.
    };

    /**
     * @class Polyline
     * @brief Represents a polyline SVG element.
     * 
     * The Polyline class inherits from the SVGElement class and provides
     * functionality to draw a polyline on a PNGImage.
     */
    class Polyline : public SVGElement
    {
    public:
        /**
         * @brief Constructs a Polyline object with the given points and stroke color.
         * 
         * @param points The vector of points that define the polyline.
         * @param stroke The color of the polyline stroke.
         */
        Polyline(const std::vector<Point> &points, const Color &stroke);

        /**
         * @brief Draws the polyline on the given PNGImage.
         * 
         * @param img The PNGImage to draw the polyline on.
         */
        void draw(PNGImage &img) const override;

    private:
        std::vector<Point> points; ///< The vector of points that define the polyline.
        Color stroke;              ///< The color of the polyline stroke.
    };

    /**
     * @class Line
     * @brief Represents a line element in an SVG image.
     * 
     * The Line class inherits from the Polyline class and adds functionality specific to lines.
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
         */
        Line(const Point &start, const Point &end, const Color &stroke) : Polyline({&start, &end}, stroke) { };

        /**
         * @brief Draws the line on the specified PNG image.
         * 
         * @param img The PNG image to draw the line on.
         */
        void draw(PNGImage &img) const override;

    private:
        Point start;    ///< The starting point of the line.
        Point end;      ///< The ending point of the line.
        Color stroke;   ///< The color of the line stroke.
    };

    /**
     * @class Polygon
     * @brief Represents a polygon SVG element.
     * 
     * The `Polygon` class is a derived class of `SVGElement` and represents a polygon shape in an SVG image.
     * It contains a vector of points that define the vertices of the polygon and a fill color.
     */
    class Polygon : public SVGElement
    {
    public:
        /**
         * @brief Constructs a `Polygon` object with the given points and fill color.
         * 
         * @param points The vector of points that define the vertices of the polygon.
         * @param fill The fill color of the polygon.
         */
        Polygon(const std::vector<Point> &points, const Color &fill);

        /**
         * @brief Draws the polygon on the given `PNGImage`.
         * 
         * @param img The `PNGImage` on which the polygon will be drawn.
         */
        void draw(PNGImage &img) const override;

    private:
        std::vector<Point> points; ///< The vector of points that define the vertices of the polygon.
        Color fill;                ///< The fill color of the polygon.
    };

    /**
     * @class Rect
     * @brief Represents a rectangle shape.
     * 
     * The `Rect` class is a derived class of the `Polygon` class and represents a rectangle shape.
     * It inherits the properties and methods of the `Polygon` class and adds additional properties
     * and methods specific to rectangles.
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
        Rect(const Point &corner, const int &width, const int &height, const Color &fill) : Polygon({Point(corner), Point({corner.x + width, corner.y}), Point({corner.x + width, corner.y + height}), Point({corner.x, corner.y + height})}, fill) { };

        /**
         * @brief Draws the rectangle on the specified image.
         * 
         * @param img The image on which to draw the rectangle.
         */
        void draw(PNGImage &img) const override;

    private:
        Point corner;   ///< The top-left corner of the rectangle.
        int width;      ///< The width of the rectangle.
        int height;     ///< The height of the rectangle.
        Color fill;     ///< The fill color of the rectangle.
    };
}
#endif
