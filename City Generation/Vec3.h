// Original Credits to James Arvo

#ifndef __VEC3_INCLUDED__
#define __VEC3_INCLUDED__

#include <iostream>
#include <cmath>

struct Vec3 {
    inline Vec3() { x = 0; y = 0; z = 0; }
    inline Vec3( double a, double b, double c ) { x = a; y = b; z = c; }
    inline Vec3( const double *a ) { x = *a++; y = *a++; z = *a; }
    double x;
    double y;
    double z;
};

inline double LengthSquared( const Vec3 &A )
{
    return A.x * A.x + A.y * A.y + A.z * A.z;
}

inline double Length( const Vec3 &A )
{
    return sqrt( LengthSquared( A ) );
}

inline double Pythagoras(const Vec3 &A, const Vec3 &B)
{
	return sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2) + pow(B.z - A.z, 2));
}

inline Vec3 operator+( const Vec3 &A, const Vec3 &B )
{
    return Vec3( A.x + B.x, A.y + B.y, A.z + B.z );
}

inline Vec3 operator-( const Vec3 &A, const Vec3 &B )
{
    return Vec3( A.x - B.x, A.y - B.y, A.z - B.z );
}

inline Vec3 operator-( const Vec3 &A )  // Unary minus.
{
    return Vec3( -A.x, -A.y, -A.z );
}

inline Vec3 operator*( double a, const Vec3 &A )
{
    return Vec3( a * A.x, a * A.y, a * A.z );
}

inline Vec3 operator*( const Vec3 &A, double a )
{
    return Vec3( a * A.x, a * A.y, a * A.z );
}

inline Vec3 operator/( const Vec3 &A, double c )
{
    return Vec3( A.x / c, A.y / c, A.z / c );
}

inline double operator*( const Vec3 &A, const Vec3 &B )  // Dot product.
{
    return (A.x * B.x) + (A.y * B.y) + (A.z * B.z);
}

inline Vec3 operator^( const Vec3 &A, const Vec3 &B ) // Cross product.
{
    return Vec3( 
				A.y * B.z - A.z * B.y,
				A.z * B.x - A.x * B.z,
				A.x * B.y - A.y * B.x
				);
}

inline Vec3 &operator+=( Vec3 &A, const Vec3 &B )
{
    A.x += B.x;
    A.y += B.y;
    A.z += B.z;
    return A;
}

inline Vec3 &operator-=( Vec3 &A, const Vec3 &B )
{
    A.x -= B.x;
    A.y -= B.y;
    A.z -= B.z;
    return A;
}

inline Vec3 &operator*=( Vec3 &A, double a )
{
    A.x *= a;
    A.y *= a;
    A.z *= a;
    return A;
}

inline Vec3& operator/=( Vec3 &A, double a )
{
    A.x /= a;
    A.y /= a;
    A.z /= a;
    return A;
}

inline bool operator==(const Vec3 &A, const Vec3 &B)
{
	return A.x == B.x && A.y == B.y && A.z == B.z;
}

inline Vec3 Unit( const Vec3 &A ) // Return a normalized vector (if it is non-zero).
{
    double d = LengthSquared( A );
    return d > 0.0 ? A / sqrt(d) : Vec3(0,0,0);
}

inline Vec3 OrthogonalTo( const Vec3 &A )  // Return a non-zero vector orthogonal to A.
{
    if( A.x == 0 ) return Vec3( 1, 0, 0 );
    return Vec3( A.y, -A.x, 0 );
}

inline std::ostream &operator<<( std::ostream &out, const Vec3 &A )
{
    out << "(" << A.x << ", " << A.y << ", " << A.z << ") ";
    return out;
}

#endif

