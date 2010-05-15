// Original Credits to James Arvo

#ifndef __VEC2_INCLUDED__
#define __VEC2_INCLUDED__

#include <iostream>
#include <cmath>

// Vec2 allows public access to its two data members: x and y.
struct Vec2 {
    inline Vec2()                     { x = 0; y = 0; }
    inline Vec2( double a, double b ) { x = a; y = b; }
    double x;
    double y;
};

// Squared Euclidean length.
inline double LengthSquared( const Vec2 &A )
{
    return A.x * A.x + A.y * A.y;
}

// The Euclidean length.
inline double Length( const Vec2 &A )
{
    return sqrt( LengthSquared( A ) );
}

// The Euclidean length between the points denoted by two vectors.
inline double Pythagoras(const Vec2& A, const Vec2& B)
{
	return sqrt( pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
}

// Vector addition.
inline Vec2 operator+( const Vec2 &A, const Vec2 &B )
{
    return Vec2( A.x + B.x, A.y + B.y );
}

// Vector subtraction.
inline Vec2 operator-( const Vec2 &A, const Vec2 &B )
{
    return Vec2( A.x - B.x, A.y - B.y );
}

// Unary minus.
inline Vec2 operator-( const Vec2 &A )
{
    return Vec2( -A.x, -A.y );
}

// Scalar multiplication.
inline Vec2 operator*( double a, const Vec2 &A )
{
    return Vec2( a * A.x, a * A.y );
}

// Scalar multiplication (with scalar on the right).
inline Vec2 operator*( const Vec2 &A, double a )
{
    return Vec2( a * A.x, a * A.y );
}

// Dot product.
inline double operator*( const Vec2 &A, const Vec2 &B )
{
    return (A.x * B.x) + (A.y * B.y);
}

// Division by a scalar.
inline Vec2 operator/( const Vec2 &A, double c )
{
    return Vec2( A.x / c, A.y / c );
}

// Compute the cross product of the 3D vectors formed
// from A and B by appending a zero Z coordinate.  Return
// only the Z coord of the result (as both X and Y will
// be zero anyway).
inline double operator^( const Vec2 &A, const Vec2 &B )
{
    return A.x * B.y - A.y * B.x;
}

// Increment one vector by another.
inline Vec2& operator+=( Vec2 &A, const Vec2 &B )
{
    A.x += B.x;
    A.y += B.y;
    return A;
}

// Decrement one vector by another.
inline Vec2& operator-=( Vec2 &A, const Vec2 &B )
{
    A.x -= B.x;
    A.y -= B.y;
    return A;
}

// Scalar multiplication.
inline Vec2 &operator*=( Vec2 &A, double a )
{
    A.x *= a;
    A.y *= a;
    return A;
}

// Division by a scalar.
inline Vec2& operator/=( Vec2 &A, double a )
{
    A.x /= a;
    A.y /= a;
    return A;
}

// Returns normalized version of vector.
inline Vec2 Unit( const Vec2 &A )
{
    double d = LengthSquared( A );
    return d > 0.0 ? A / sqrt(d) : Vec2(0,0);
}

// Send vector to an output stream.
inline std::ostream &operator<<( std::ostream &out, const Vec2 &A )
{
    out << "(" << A.x << ", " << A.y << ") ";
    return out;
}

#endif

