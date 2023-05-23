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
        Camera(Point3 lookFrom, Point3 lookAt, Vec3 viewUp, double verticalFovInDegrees, double aspectRatio, double aperture, double focusDistance) noexcept;

        /// \brief 
        /// \param[in] u
        /// \param[in] v
        /// \returns
        Ray getRay(double const s, double const t) const& noexcept;

    private:
        Point3 m_origin {};
        Point3 m_lowerLeftCorner;
        Vec3 m_horizontal;
        Vec3 m_vertical;
        Vec3 m_w;
        Vec3 m_u;
        Vec3 m_v;
        double m_lensRadius;
    };
}

#endif