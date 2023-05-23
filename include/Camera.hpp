#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Common.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

namespace rt
{
    class Camera
    {
    public:
        /// \brief Create a camera with the specified field of view and aspect ratio
        /// \param[in] verticalFovInDegrees The angle you see through the portal
        /// \param[in] aspectRatio The ratio between the image width and height
        constexpr Camera(double verticalFovInDegrees, double aspectRatio) noexcept;

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
    constexpr Camera::Camera(double verticalFovInDegrees, double aspectRatio) noexcept
    {
        auto theta = degreesToRadians(verticalFovInDegrees);
        auto h = std::tan(theta / 2);
        
        double const viewportHeight = 2.0 * h;  // the height of the viewport (or scene)
        double const viewportWidth = aspectRatio * viewportHeight; // the width of the viewport (or scene)

        constexpr double focalLength = 1.0; // the distance from the camera to the viewport

        m_horizontal = Vec3(viewportWidth, 0.0, 0.0);   // offset vector relative to the viewport width
        m_vertical = Vec3(0.0, viewportHeight, 0.0);    // offset vector relative to the viewport height
        m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - Vec3(0, 0, focalLength); // lower-left corner of the viewport
    }

    constexpr Ray Camera::getRay(double const u, double const v) const& noexcept
    {
        return Ray(m_origin, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin);
    }
}

#endif