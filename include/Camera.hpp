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
        /// \param[in] lookFrom The location of the camera
        /// \param[in] lookAt The location the camera is facing
        /// \param[in] viewUp The sideways tilt of the camera
        /// \param[in] verticalFovInDegrees The angle you see through the portal
        /// \param[in] aspectRatio The ratio between the image width and height
        constexpr Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double verticalFovInDegrees, double aspectRatio) noexcept;

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
    constexpr Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double verticalFovInDegrees, double aspectRatio) noexcept
    :   m_origin(lookFrom)
    {
        auto theta = degreesToRadians(verticalFovInDegrees);
        auto h = std::tan(theta / 2);
        
        double const viewportHeight = 2.0 * h;  // the height of the viewport (or scene)
        double const viewportWidth = aspectRatio * viewportHeight; // the width of the viewport (or scene)

        auto const w = unitVector(lookFrom - lookAt);
        auto const u = unitVector(cross(viewUp, w));
        auto const v = cross(w, u);

        m_horizontal = viewportWidth * u;
        m_vertical = viewportHeight * v;

        m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - w; // lower-left corner of the viewport
    }

    constexpr Ray Camera::getRay(double const u, double const v) const& noexcept
    {
        return Ray(m_origin, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin);
    }
}

#endif