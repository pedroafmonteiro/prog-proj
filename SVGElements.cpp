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
                     const std::string &id, 
                     const std::string &transform, 
                     const Point &transformOrigin)
        : fill(fill), center(center), radius(radius)
    {
        this->id = id;
        this->transform = transform;
        this->transformOrigin = transformOrigin;
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

    /**
     * @brief Draws a circle on the specified PNGImage.
     *
     * @param img The PNGImage on which the circle will be drawn.
     */
    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    /**
     * @brief Constructs a Polyline object with the given points and stroke color.
     * 
     * @param points The vector of points that define the polyline.
     * @param stroke The color of the polyline's stroke.
     */
    Polyline::Polyline(const std::vector<Point> &points,
                       const Color &stroke, 
                       const std::string &id, 
                       const std::string &transform, 
                       const Point &transformOrigin)
        : points(points), stroke(stroke)
    {
        this->id = id;
        this->transform = transform;
        this->transformOrigin = transformOrigin;
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

    /**
     * @brief Draws a line on the given PNGImage.
     *
     * @param img The PNGImage to draw the line on.
     */
    void Line::draw(PNGImage &img) const
    {
        img.draw_line(start, end, stroke);
    }

    /**
     * @brief Constructs a Polygon object with the given points and fill color.
     * 
     * @param points The vector of points that define the polygon.
     * @param fill The fill color of the polygon.
     */
    Polygon::Polygon(const std::vector<Point> &points, 
                     const Color &fill, 
                     const std::string &id, 
                     const std::string &transform, 
                     const Point &transformOrigin)
        : points(points), fill(fill)
    {
        this->id = id;
        this->transform = transform;
        this->transformOrigin = transformOrigin;
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

    /**
     * @brief Draws a rectangle on the given PNGImage.
     *
     * @param img The PNGImage to draw on.
     */
    void Rect::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

}
