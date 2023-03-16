#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Common/Common.hpp"
#include "Vec3/Vec3.hpp"

class Camera
{
public:
    /// \brief Default constructor
    constexpr Camera() noexcept;

    /// \brief 
    /// \param[in] u
    /// \param[in] v
    /// \returns
    constexpr Ray getRay(double const u, double const v) const& noexcept;

private:
    Point3 m_origin {};
    Point3 m_lowerLeftCorner;
    Vec3 m_horizontal;
    Vec3 m_vertical;
};

// Create a new Camera and define its position relative to the viewport
constexpr Camera::Camera() noexcept
{
    constexpr double aspectRatio = 16.0 / 9.0;  // ratio of the image width to image height
    constexpr double viewportHeight = 2.0;  // the height of the viewport (or scene)
    constexpr double viewportWidth = aspectRatio * viewportHeight; // the width of the viewport (or scene)
    constexpr double focalLength = 1.0; // the distance from the camera to the viewport

    m_horizontal = Vec3(viewportWidth, 0.0, 0.0);   // offset vector relative to the viewport width
    m_vertical = Vec3(0.0, viewportHeight, 0.0);    // offset vector relative to the viewport height
    m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - Vec3(0, 0, focalLength); // lower-left corner of the viewport
}

constexpr Ray Camera::getRay(double const u, double const v) const& noexcept
{
    return Ray(m_origin, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin);
}

#endif