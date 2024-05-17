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

    /**
     * @brief Translates the center of the ellipse by the given translation vector.
     *
     * @param t The translation vector.
     */
    void Ellipse::translate(const Point &t)
    {
        center = center.translate(t);
    }

    /**
     * @brief Rotates the ellipse around a specified origin by a given number of degrees.
     *
     * @param origin The origin point around which the ellipse will be rotated.
     * @param degrees The number of degrees by which the ellipse will be rotated.
     */
    void Ellipse::rotate(const Point &origin, int degrees)
    {
        center = center.rotate(origin, degrees);
    }

    /**
     * @brief Scales the ellipse by a given factor around a specified origin point.
     *
     * @param origin The origin point around which the ellipse will be scaled.
     * @param v The scaling factor.
     */
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

    /**
     * @brief Translates the points of the polyline by the given translation vector.
     *
     * @param t The translation vector.
     */
    void Polyline::translate(const Point &t)
    {
        for (size_t i = 0; i < points.size(); i++) {
            points[i] = points[i].translate(t);
        }
    }

    /**
     * @brief Rotates the polyline around a specified origin by a given number of degrees.
     *
     * @param origin The origin point around which the polyline will be rotated.
     * @param degrees The number of degrees by which the polyline will be rotated.
     */
    void Polyline::rotate(const Point &origin, int degrees)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].rotate(origin, degrees);
        }
    }

    /**
     * @brief Scales the polyline by a given factor around a specified origin point.
     *
     * @param origin The origin point around which the polyline will be scaled.
     * @param v The scaling factor.
     */
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

    /**
     * @brief Translates the points of the line by the given translation vector.
     *
     * @param t The translation vector.
     */
    void Line::translate(const Point &t)
    {
        start = start.translate(t);
        end = end.translate(t);
    }

    /**
     * @brief Rotates the line around a specified origin by a given number of degrees.
     *
     * @param origin The origin point around which the line will be rotated.
     * @param degrees The number of degrees by which the line will be rotated.
     */
    void Line::rotate(const Point &origin, int degrees)
    {
        start = start.rotate(origin, degrees);
        end = end.rotate(origin, degrees);
    }

    /**
     * @brief Scales the line by a given factor around a specified origin point.
     *
     * @param origin The origin point around which the line will be scaled.
     * @param v The scaling factor.
     */
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

    /**
     * @brief Translates the points of the polygon by the given translation vector.
     *
     * @param t The translation vector.
     */
    void Polygon::translate(const Point &t)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].translate(t);
        }
    }

    /**
     * @brief Rotates the polygon around a specified origin by a given number of degrees.
     *
     * @param origin The origin point around which the polygon will be rotated.
     * @param degrees The number of degrees by which the polygon will be rotated.
     */
    void Polygon::rotate(const Point &origin, int degrees)
    {
        for (size_t i = 0; i < points.size(); i++)
        {
            points[i] = points[i].rotate(origin, degrees);
        }
    }

    /**
     * @brief Scales the polygon by a given factor around a specified origin point.
     *
     * @param origin The origin point around which the polygon will be scaled.
     * @param v The scaling factor.
     */
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

    /**
     * @brief Draws a group on the given PNGImage.
     *
     * @param img The PNGImage to draw on.
     */
    void Group::draw(PNGImage &img) const
    {
        for (auto y : V ){
            y->draw(img);
        }
    }

    /**
     * @brief Translates the elements of the group by the given translation vector.
     *
     * @param t The translation vector.
     */
    void Group::translate(const Point &t)
    {
        for (auto y : V ){
            y->translate(t);
        }
    }

    /**
     * @brief Rotates the elements of the group around a specified origin by a given number of degrees.
     *
     * @param origin The origin point around which the elements will be rotated.
     * @param degrees The number of degrees by which the elements will be rotated.
     */
    void Group::rotate(const Point &origin, int degrees)
    {
        for (auto y : V ){
            y->rotate(origin,degrees);
        }
    }

    /**
     * @brief Scales the elements of the group by a given factor around a specified origin point.
     *
     * @param origin The origin point around which the elements will be scaled.
     * @param v The scaling factor.
     */
    void Group::scale(const Point &origin, int v)
    {
        for (auto y : V ){
            y->scale(origin,v);
        }
    }


    /**
     * @brief Destructor for the Group class.
     * 
     * This destructor is responsible for freeing the memory allocated for the objects
     * stored in the `V` vector.
     */
    Group::~Group()
    {
        for (auto y : V ){
            delete y;
        }
    }

    /**
     * @brief Creates a deep copy of the Group object.
     * 
     * @return A pointer to the newly created Group object.
     */
    SVGElement* Group::copy() const{
        std::vector<SVGElement*> temp;
        for (auto y : V ){
            temp.push_back(y->copy());
        }
        return new Group(temp);
    }
}
