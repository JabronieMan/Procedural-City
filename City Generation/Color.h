// Original Credits to James Arvo

#ifndef __COLOR_INCLUDED__
#define __COLOR_INCLUDED__

#include <iostream>

struct Color {
    inline Color() { red = 0; green = 0; blue = 0; }
    inline Color( double r, double g, double b ) { red = r; green = g; blue = b; }
    double red;
    double green;
    double blue;
};

inline bool operator==(const Color& A, const Color& B)
{
	return A.red == B.red && A.green == B.green && A.blue == B.blue;
}

// Addition of colors is performed component-wise.
inline Color operator+( const Color &A, const Color &B )
{
    return Color( A.red + B.red, A.green + B.green, A.blue + B.blue );
}

// Scalar multiplication.
inline Color operator*( double c, const Color &A )
{
    return Color( c * A.red, c * A.green, c * A.blue );
}

// Scalar multiplication (scalar on the right).
inline Color operator*( const Color &A, double c )
{
    return Color( c * A.red, c * A.green, c * A.blue );
}

// Multiplication of colors is performed component-wise.
inline Color operator*( const Color &A, const Color &B )
{
    // Colors are multiplied component-wise, and result in another color, not
    // a scalar.  This is the most significant difference between the Vec3 class
    // and the Color class.
    return Color( A.red * B.red, A.green * B.green, A.blue * B.blue );
}

// Scalar division.
inline Color operator/( const Color &A, double c )
{
    return Color( A.red / c, A.green / c, A.blue / c );
}

// Increment one color by another.
inline Color& operator+=( Color &A, const Color &B )
{
    A.red   += B.red;
    A.green += B.green;
    A.blue  += B.blue;
    return A;
}

// Scalar multiplication.
inline Color& operator*=( Color &A, double c )
{
    A.red   *= c;
    A.green *= c;
    A.blue  *= c;
    return A;
}

// Scaling one color by another color, which is done by
// scalaing each channel by the corresponding channel of 
// the other color.
inline Color& operator*=( Color &A, const Color &B )
{
    A.red   *= B.red;
    A.green *= B.green;
    A.blue  *= B.blue;
    return A;
}

// Scalar division.
inline Color& operator/=( Color &A, double c )
{
    A.red   /= c;
    A.green /= c;
    A.blue  /= c;
    return A;
}

//Return a color that's the inverted version of the given color
inline Color InvertColor(const Color& c)
{
	return Color(1 - c.red, 1 - c.green, 1 - c.blue);
}

// Send a color to an output stream.  Use angle brackets, "<r,g,b>",
// so that it is distinguishable from a Vec3.
inline std::ostream &operator<<( std::ostream &out, const Color &C )
{
    out << "<" << C.red << "," << C.green << "," << C. blue << "> ";
    return out;
}

#endif



