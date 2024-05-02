#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }

    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    void Circle::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, {radius, radius}, fill);
    }

    Polyline::Polyline(const std::vector<Point> &points,
                       const Color &stroke)
        : points(points), stroke(stroke)
    {
    }

    void Polyline::draw(PNGImage &img) const
    {
        for (size_t i = 0; i < points.size() - 1; i++)
        {
            img.draw_line(points[i], points[i + 1], stroke);
        }
    }

    void Line::draw(PNGImage &img) const
    {
        img.draw_line(start, end, stroke);
    }

    Polygon::Polygon(const std::vector<Point> &points, 
                     const Color &fill)
        : points(points), fill(fill)
    {
    }

    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(points, fill);
    }

    void Rect::draw(PNGImage &img) const
    {
        img.draw_polygon({Point(corner), Point({corner.x + width, corner.y}), Point({corner.x + width, corner.y + height}), Point({corner.x, corner.y + height})}, fill);
    }

}
