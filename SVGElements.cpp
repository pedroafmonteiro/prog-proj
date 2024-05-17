#include "SVGElements.hpp"

namespace svg
{
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    /**
     * @brief Constructs an Ellipse object with the specified fill color, center point, and radius.
     * 
     * @param fill The fill color of the ellipse.
     * @param center The center point of the ellipse.
     * @param radius The radius of the ellipse.
     */
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius, 
                     const std::string &id)
        : fill(fill), center(center), radius(radius)
    {
    }

    /**
     * @brief Draws an ellipse on the specified PNGImage.
     *
     * @param img The PNGImage on which the ellipse will be drawn.
     */
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    void Ellipse::translate(const Point &t)
    {
        center = center.translate(t);
    }

    void Ellipse::rotate(const Point &origin, int degrees)
    {
        center = center.rotate(origin, degrees);
    }

    void Ellipse::scale(const Point &origin, int v)
    {
        center = center.scale(origin, v);
        radius.x = radius.x * v;
        radius.y = radius.y * v;
    }

    /**
     * @brief Creates a copy of the Ellipse object.
     * 
     * @return A pointer to the copied Ellipse object.
     */
    SVGElement* Ellipse::copy() const{
        return new Ellipse(fill,center,radius,id);
    }

    /**
     * @brief Draws a circle on the specified PNGImage.
     *
     * @param img The PNGImage on which the circle will be drawn.
     */
    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    /* void Circle::translate(const Point &t)
    {
        center = center.translate(t);
    }

    void Circle::rotate(const Point &origin, int degrees)
    {
        center = center.rotate(origin, degrees);
    }

    void Circle::scale(const Point &origin, int v)
    {
        center = center.scale(origin, v);
        radius.x = radius.x * v;
        radius.y = radius.y * v;
    } */

    /**
     * @brief Creates a copy of the Circle object.
     * 
     * @return A pointer to the copied Circle object.
     */
    SVGElement* Circle::copy() const{
        return new Circle(fill,center,radius.x,id);
    }
    /**
     * @brief Constructs a Polyline object with the specified points and stroke color.
     * 
     * @param points The vector of points that define the polyline.
     * @param stroke The color of the polyline's stroke.
     */
    Polyline::Polyline(const std::vector<Point> &points,
                       const Color &stroke, 
                       const std::string &id)
        : points(points), stroke(stroke)
    {
    }

    /**
     * @brief Draws the polyline on the given PNGImage.
     * 
     * @param img The PNGImage on which the Polyline will be drawn.
     */
    void Polyline::draw(PNGImage &img) const
    {
        for (size_t i = 0; i < points.size() - 1; i++)
        {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }

    void Polyline::translate(const Point &t)
    {
        for (size_t i = 0; i < points.size(); i++) {
            points[i] = points[i].translate(t);
        }
    }

    void Polyline::rotate(const Point &origin, int degrees)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].rotate(origin, degrees);
        }
    }

    void Polyline::scale(const Point &origin, int v)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].scale(origin, v);
        }
    }

    /**
     * @brief Creates a copy of the Polyline object.
     * 
     * @return A pointer to the copied Polyline object.
     */
    SVGElement* Polyline::copy() const{
        return new Polyline(points,stroke,id);
    }

    /**
     * @brief Draws a line on the given PNGImage.
     *
     * @param img The PNGImage to draw the line on.
     */
    void Line::draw(PNGImage &img) const
    {
        img.draw_line(start, end, stroke);
    }

    void Line::translate(const Point &t)
    {
        start = start.translate(t);
        end = end.translate(t);
    }

    void Line::rotate(const Point &origin, int degrees)
    {
        start = start.rotate(origin, degrees);
        end = end.rotate(origin, degrees);
    }

    void Line::scale(const Point &origin, int v)
    {
        start = start.scale(origin, v);
        end = end.scale(origin, v);
    }

    /**
     * @brief Creates a copy of the Line object.
     * 
     * @return A pointer to the copied Line object.
     */
    SVGElement* Line::copy() const{
        return new Line(start,end,stroke,id);
    }

    /**
     * @brief Constructs a Polygon object with the specified points and fill color.
     * 
     * @param points The vector of points that define the polygon.
     * @param fill The fill color of the polygon.
     */
    Polygon::Polygon(const std::vector<Point> &points, 
                     const Color &fill, 
                     const std::string &id)
        : points(points), fill(fill)
    {
    }

    /**
     * @brief Draws a polygon on the given PNGImage.
     * 
     * @param img The PNGImage to draw the polygon on.
     */
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    void Polygon::translate(const Point &t)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].translate(t);
        }
    }

    void Polygon::rotate(const Point &origin, int degrees)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].rotate(origin, degrees);
        }
    }

    void Polygon::scale(const Point &origin, int v)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].scale(origin, v);
        }
    }

    /**
     * @brief Creates a copy of the Polygon object.
     * 
     * @return A pointer to the copied Ellipse object.
     */
    SVGElement* Polygon::copy() const{
        return new Polygon(points,fill,id);
    }

    /**
     * @brief Draws a rectangle on the given PNGImage.
     *
     * @param img The PNGImage to draw on.
     */
    void Rect::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    /**
     * @brief Creates a copy of the Rectangle object.
     * 
     * @return A pointer to the copied Rectangle object.
     */
    SVGElement* Rect::copy() const {
        return new Rect(points, fill, id);
    }
}
