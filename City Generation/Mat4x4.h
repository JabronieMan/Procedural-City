// Original Credits to James Arvo

#ifndef __MAT4x4_INCLUDED__
#define __MAT4x4_INCLUDED__

#include <iostream>
#include "Vec2.h"
#include "Vec3.h"

class Mat4x4 {
public:
	inline Mat4x4();
	inline Mat4x4( const Mat4x4 &M );
	inline Mat4x4( const double *a );
	inline ~Mat4x4() {}
	inline       double &operator()( int i, int j )       { return m[i][j]; }
	inline const double &operator()( int i, int j ) const { return m[i][j]; }
	inline static Mat4x4 Identity();
	inline Vec2 Trans2D() const { return Vec2( m[0][3], m[1][3]          ); }
	inline Vec3 Trans3D() const { return Vec3( m[0][3], m[1][3], m[2][3] ); }
	double *array() { return &(m[0][0]); } // This should be used very rarely!
private:
	double m[4][4];
};

inline Mat4x4::Mat4x4()
{
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ) m[i][j] = 0.0;
}

inline Mat4x4::Mat4x4( const double *a )
{
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ) m[i][j] = *a++;
}

inline Mat4x4::Mat4x4( const Mat4x4 &M )
{
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ) 
			m[i][j] = M(i, j);
}

inline Mat4x4 operator+( const Mat4x4 &A, const Mat4x4 &B )
{
    Mat4x4 C;
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ) C(i,j) = A(i,j) + B(i,j);
    return C;
}

inline Mat4x4 operator-( const Mat4x4 &A, const Mat4x4 &B )
{
    Mat4x4 C;
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ) C(i,j) = A(i,j) - B(i,j);
    return C;
}

inline Mat4x4 operator*( double c, const Mat4x4 &M )
{
    Mat4x4 A;
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ) A(i,j) = c * M(i,j);
    return A;    
}

inline Mat4x4 operator*( const Mat4x4 &M, double c )
{
    return c * M;
}

// Matrix-Vector multiplication.  When transforming a
// vector with three components by a 4x4 matrix, assume
// that the vector has an attitional 1 appended in the
// 4'th slot.  Return only the first three elements of
// the result as a Vec3.
inline Vec3 operator*( const Mat4x4 &M, const Vec3 &A )
{
    return Vec3(
				M(0,0) * A.x + M(0,1) * A.y + M(0,2) * A.z + M(0,3),
				M(1,0) * A.x + M(1,1) * A.y + M(1,2) * A.z + M(1,3),
				M(2,0) * A.x + M(2,1) * A.y + M(2,2) * A.z + M(2,3)
				);
}

// Matrix-Vector multiplication.  When transforming a
// vector with two components by a 4x4 matrix, assume
// that the vector's z component is zero, and that it's
// last component is 1.  Return only the first two elements
// of the result as a Vec2.
inline Vec2 operator*( const Mat4x4 &M, const Vec2 &A )
{
    return Vec2(
				M(0,0) * A.x + M(0,1) * A.y + M(0,3),
				M(1,0) * A.x + M(1,1) * A.y + M(1,3)
				);
}

// Matrix multiplication.
inline Mat4x4 operator*( const Mat4x4 &A, const Mat4x4 &B )
{
    Mat4x4 C;
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ )
			C(i,j) = A(i,0) * B(0,j) + A(i,1) * B(1,j) + A(i,2) * B(2,j) + A(i,3) * B(3,j);
    return C;
}

inline Mat4x4 operator/( const Mat4x4 &M, double c )
{
    return (1/c) * M;
}

inline Mat4x4 Transpose( const Mat4x4 &M )
{
    Mat4x4 W;
    for( int i = 0; i < 4; i++ )
		for( int j = 0; j < 4; j++ ) W(i,j) = M(j,i);
    return W;
}

inline Mat4x4 Mat4x4::Identity()
{
    Mat4x4 I;
    I(0,0) = 1.0;
    I(1,1) = 1.0;
    I(2,2) = 1.0;
    I(3,3) = 1.0;
    return I;
}

// Return a 4x4 modeling matrix that performs a
// translation by tx, ty, and tz (if specified).
inline Mat4x4 Trans4x4( double tx, double ty, double tz = 0.0 )
{
    Mat4x4 M( Mat4x4::Identity() );
    M(0,3) = tx;
    M(1,3) = ty;
    M(2,3) = tz;
    return M;
}

// Return a 4x4 modeling matrix that performs a
// translation by the 2D vector A.
inline Mat4x4 Trans4x4( const Vec2 &A )
{
    Mat4x4 M( Mat4x4::Identity() );
    M(0,3) = A.x;
    M(1,3) = A.y;
    return M;
}

// Return a 4x4 modeling matrix that performs a
// translation by the 3D vector A.
inline Mat4x4 Trans4x4( const Vec3 &A )
{
    Mat4x4 M( Mat4x4::Identity() );
    M(0,3) = A.x;
    M(1,3) = A.y;
    M(2,3) = A.z;
    return M;
}

// Return a 4x4 modeling matrix that scales the
// X, Y, and Z components by the same scale factor, s.
inline Mat4x4 Scale4x4( double s )
{
    Mat4x4 M;
    M(0,0) = s;
    M(1,1) = s;
    M(2,2) = s;
    M(3,3) = 1.0;
    return M;
}

// Return a 4x4 modeling matrix that scales the
// X, Y, and Z components by sx, sy, and sz, respectively.
// Leave off the third argument for scaling in 2D.
inline Mat4x4 Scale4x4( double sx, double sy, double sz = 1.0 )
{
    Mat4x4 M;
    M(0,0) = sx;
    M(1,1) = sy;
    M(2,2) = sz;
    M(3,3) = 1.0;
    return M;
}

//Return 4x4 modeling matrix with scales based on 3D Vector
inline Mat4x4 Scale4x4( const Vec3 &A )
{
    Mat4x4 M;
	M(0,0) = A.x;
    M(1,1) = A.y;
    M(2,2) = A.z;
    M(3,3) = 1.0;
    return M;
}



// Return a 4x4 modeling matrix that performs a clockwise
// rotation by "angle" radians about the X-Axis.  (That is,
// the Z-axis is rotated toward the Y-axis.)
inline Mat4x4 X_Rotate4x4( double angle )
{
    Mat4x4 M;
    double c = cos( angle );
    double s = sin( angle );
    M(0,0) = 1;
    M(1,1) = c; M(1,2) = -s;
    M(2,1) = s; M(2,2) =  c;
    M(3,3) = 1;
    return M;
}

// Return a 4x4 modeling matrix that performs a clockwise
// rotation by "angle" radians about the Y-Axis.  (That is,
// the X-axis is rotated toward the Z-axis.)
Mat4x4 Y_Rotate4x4( double angle )
{
    Mat4x4 M;
    double c = cos( angle );
    double s = sin( angle );
    M(0,0) = c; M(0,2) = -s;
    M(1,1) = 1;
    M(2,0) = s; M(2,2) =  c;
    M(3,3) = 1;
    return M;
}

// Return a 4x4 modeling matrix that performs a clockwise
// rotation by "angle" radians about the Z-Axis.  (That is,
// the Y-axis is rotated toward the X-axis.)
Mat4x4 Z_Rotate4x4( double angle )
{
    Mat4x4 M;
    double c = cos( angle );
    double s = sin( angle );
    M(0,0) = c; M(0,1) = -s;
    M(1,0) = s; M(1,1) =  c;
    M(2,2) = 1;
    M(3,3) = 1;
    return M;
}

// Compute the inverse of a 4x4 matrix ASSUMING that its last row is the last
// row of the 4x4 identity matrix.  This is a common situation, and it makes the
// computation of the inverse much easier than the general case.  This is called
// "3x4" as a reminder that the last row is essentially ignored.

inline Mat4x4 Inverse3x4( const Mat4x4 &M )
{
    // Compute the determinant of the upper left 3x3 matrix.
    const double det( 
					 M(0,0) * ( M(1,1) * M(2,2) - M(1,2) * M(2,1) )
					 - M(0,1) * ( M(1,0) * M(2,2) - M(1,2) * M(2,0) )
					 + M(0,2) * ( M(1,0) * M(2,1) - M(1,1) * M(2,0) )
					 );
    
    // Compute the inverse of the upper left 3x3 matrix.  This is
    // the transpose of the "adjoint" matrix divided by the determinant.
    Mat4x4 W;
    W(0,0) = ( M(1,1) * M(2,2) - M(1,2) * M(2,1) ) / det;
    W(1,0) = ( M(1,2) * M(2,0) - M(1,0) * M(2,2) ) / det;
    W(2,0) = ( M(1,0) * M(2,1) - M(1,1) * M(2,0) ) / det;
	
    W(0,1) = ( M(0,2) * M(2,1) - M(0,1) * M(2,2) ) / det;
    W(1,1) = ( M(0,0) * M(2,2) - M(0,2) * M(2,0) ) / det;
    W(2,1) = ( M(0,1) * M(2,0) - M(0,0) * M(2,1) ) / det;
	
    W(0,2) = ( M(0,1) * M(1,2) - M(0,2) * M(1,1) ) / det;
    W(1,2) = ( M(0,2) * M(1,0) - M(0,0) * M(1,2) ) / det;
    W(2,2) = ( M(0,0) * M(1,1) - M(0,1) * M(1,0) ) / det;
	
    W(3,3) = 1;
	
    // Multiply this inverse by the tranlation component of the
    // original matrix.
    const Vec3 b( W * M.Trans3D() );
	
    // Fill in the translation component of the inverse matrix.
    W(0,3) = -b.x;
    W(1,3) = -b.y;
    W(2,3) = -b.z;
	
    return W;
}



// This output operator prints a 4x4 matrix in "Matlab" format.  That is,
// with entries listed within brackets and rows separated by semicolons.
inline std::ostream &operator<<( std::ostream &out, const Mat4x4 &M )
{
    out  
	<< M(0,0) << "\t|\t" << M(0,1) << "\t|\t" << M(0,2) << "\t|\t" << M(0,3) << std::endl
	<< M(1,0) << "\t|\t" << M(1,1) << "\t|\t" << M(1,2) << "\t|\t" << M(1,3) << std::endl
	<< M(2,0) << "\t|\t" << M(2,1) << "\t|\t" << M(2,2) << "\t|\t" << M(2,3) << std::endl
	<< M(3,0) << "\t|\t" << M(3,1) << "\t|\t" << M(3,2) << "\t|\t" << M(3,3) << std::endl;
    return out;
}

#endif

