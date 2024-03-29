#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "Vec3.hpp"

#include <iostream>
#include <ostream>

namespace rt
{
    /// \brief RGB colour
    using Colour = Vec3;

    /// \brief Write a single pixel's colour to the standard output stream
    /// \param[in] pixelColour The pixel whose colour is being written
    /// \param[inout] out The output stream written to
    /// \param[in] samplesPerPixel The number of samples of each pixel
    void writeColour(std::ostream& out, Colour const& pixelColour, int const samplesPerPixel);
}

#endif