#include "Camera.hpp"

namespace rt
{
    // Create a new Camera and define its position relative to the viewport
    Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double verticalFovInDegrees, double aspectRatio, double aperture, double focusDistance) noexcept
    :   m_origin(lookFrom)
    ,   m_w(unitVector(lookFrom - lookAt))
    ,   m_u(unitVector(cross(viewUp, m_w)))
    ,   m_v(cross(m_w, m_u))
    ,   m_lensRadius(aperture / 2)
    {
        auto theta = degreesToRadians(verticalFovInDegrees);
        auto h = std::tan(theta / 2);
        
        double const viewportHeight = 2.0 * h;  // the height of the viewport (or scene)
        double const viewportWidth = aspectRatio * viewportHeight; // the width of the viewport (or scene)

        m_horizontal = focusDistance * viewportWidth * m_u;
        m_vertical = focusDistance * viewportHeight * m_v;

        m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - (focusDistance * m_w); // lower-left corner of the viewport
    }

    Ray Camera::getRay(double const s, double const t) const& noexcept
    {
        Vec3 rd = m_lensRadius * randomInUnitDisk();
        Vec3 offset = (m_u * rd.x()) + (m_v * rd.y());

        return Ray(m_origin + offset, m_lowerLeftCorner + (s * m_horizontal) + (t * m_vertical) - m_origin - offset);
    }
}