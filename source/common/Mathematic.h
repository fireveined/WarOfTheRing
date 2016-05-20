#ifndef MATHEMATIC_HPP_INCLUDED
#define MATHEMATIC_HPP_INCLUDED


//////////////////////////////////////////////////////////////////////
// (c) Janusz Ganczarski
// http://www.januszg.hg.pl
// JanuszG@enter.net.pl
//////////////////////////////////////////////////////////////////////


#include <cmath>
#include <math.h>
#include <GL/gl.h>


//////////////////////////////////////////////////////////////////////
// usuniêcie definicji makr near i far
//////////////////////////////////////////////////////////////////////
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif

//////////////////////////////////////////////////////////////////////
// szablon klasy obs³uguj¹cej wektor/punkt 3D
//////////////////////////////////////////////////////////////////////
template <class T = GLfloat> class vector3
{
protected:

public:
    // konstruktory
    T xyz[3];
    vector3();
    vector3( const T x, const T y, const T z );
    vector3( const T *v );
    vector3( const vector3<T> &v );

    // pobieranie i zmiana danych
    const T *data() const;
    T &operator[] ( unsigned int i );
    const T &operator[] ( unsigned int i ) const;
    const T x() const;
    const T y() const;
    const T z() const;
    void set( const T x, const T y, const T z );
    void setX( const T x );
    void setY( const T y );
    void setZ( const T z );

    void rotate(float angle, float cx, float cy)
    {
        angle=angle/180*3.14159265;
        T x=xyz[0],y=xyz[1];
        xyz[0] = (x-cx) * cos(angle)+ cx - (y-cy) * sin(angle) + cy;
        xyz[1] = (x-cx) * sin(angle)+ cx + (y-cy) * cos(angle) + cy;


    }

    // operatory arytmetyczne
    vector3<T> &operator += ( const vector3<T> &v );
    vector3<T> &operator -= ( const vector3<T> &v );
    vector3<T> &operator - ( const vector3<T> &v );
    vector3<T> &operator *= ( const T f );
    vector3<T> &operator /= ( const T f );
    vector3<T> operator * ( const T f );

    // operacje matematyczne
    const T length() const;
    vector3<T> normalize();
};

//////////////////////////////////////////////////////////////////////
// operatory i operacje matematyczne klasy vector3
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> normalize( const vector3<T> &v );
template <class T> const T dot3( const vector3<T> &v1, const vector3<T> &v2 );
template <class T> vector3<T> cross3( const vector3<T> &v1, const vector3<T> &v2 );
template <class T> vector3<T> operator + ( const vector3<T> &v1, const vector3<T> &v2 );
template <class T> vector3<T> operator - ( const vector3<T> &v1, const vector3<T> &v2 );
template <class T> vector3<T> operator * ( const T f, const vector3<T> &v );
template <class T> vector3<T> operator * ( const vector3<T> &v, const T f );
template <class T> vector3<T> operator / ( const vector3<T> &v, const T f );
template <class T> bool operator == ( const vector3<T> &v1, const vector3<T> &v2 );
template <class T> bool operator != ( const vector3<T> &v1, const vector3<T> &v2 );

//////////////////////////////////////////////////////////////////////
// szablon klasy obs³uguj¹cej wektor/punkt w przestrzeni jednorodnej
//////////////////////////////////////////////////////////////////////
template <class T = GLfloat> class vector4
{
protected:
    T xyzw[4];
public:
    // konstruktory
    vector4();
    vector4( const T x, const T y, const T z, const T w );
    vector4( const T *v );
    vector4( const vector4<T> &v );

    // pobieranie i zmiana danych
    const T *data() const;
    T &operator[] ( unsigned int i );
    const T &operator[] ( unsigned int i ) const;
    const T x() const;
    const T y() const;
    const T z() const;
    const T w() const;
    void set( const T x, const T y, const T z, const T w );
    void setX( const T x );
    void setY( const T y );
    void setZ( const T z );
    void setW( const T w );

    // operatory arytmetyczne
    vector4<T> &operator += ( const vector4<T> &v );
    vector4<T> &operator -= ( const vector4<T> &v );
    vector4<T> &operator - ( const vector4<T> &v );
    vector4<T> &operator *= ( const T f );
    vector4<T> &operator /= ( const T f );
    vector4<T> operator * ( const T f );

    // operacje matematyczne
    const T length() const;
    vector4<T> normalize();
};

//////////////////////////////////////////////////////////////////////
// operatory i operacje matematyczne na vector4
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> normalize( const vector4<T> &v );
template <class T> const T dot3( const vector4<T> &v1, const vector4<T> &v2 );
template <class T> const T dot4( const vector4<T> &v1, const vector4<T> &v2 );
template <class T> vector4<T> cross3( const vector4<T> &v1, const vector4<T> &v2 );
template <class T> vector4<T> operator + ( const vector4<T> &v1, const vector4<T> &v2 );
template <class T> vector4<T> operator - ( const vector4<T> &v1, const vector4<T> &v2 );
template <class T> vector4<T> operator * ( const T f, const vector4<T> &v );
template <class T> vector4<T> operator * ( const vector4<T> &v, const T f );
template <class T> vector4<T> operator / ( const vector4<T> &v, const T f );
template <class T> bool operator == ( const vector4<T> &v1, const vector4<T> &v2 );
template <class T> bool operator != ( const vector4<T> &v1, const vector4<T> &v2 );

//////////////////////////////////////////////////////////////////////
// szablon klasy obs³uguj¹cej macierz 3x3
//////////////////////////////////////////////////////////////////////
template <class T = GLfloat> class matrix3x3
{
protected:
    // dane macierzy w uk³adzie wierszowym
    T m33[9];
public:
    // konstruktory
    matrix3x3();
    matrix3x3( const T a11, const T a12, const T a13,
               const T a21, const T a22, const T a23,
               const T a31, const T a32, const T a33 );
    matrix3x3( const T *m );
    matrix3x3( const matrix3x3<T> &m );

    // pobieranie i zmiana danych
    const T *data() const;
    T &operator[] ( unsigned int i );
    const T &operator[] ( unsigned int i ) const;

    // operatory arytmetyczne
    matrix3x3<T> &operator += ( const matrix3x3<T> &m );
    matrix3x3<T> &operator -= ( const matrix3x3<T> &m );
    matrix3x3<T> &operator *= ( const matrix3x3<T> &m );
    matrix3x3<T> &operator *= ( const T f );
    matrix3x3<T> &operator /= ( const T f );
    matrix3x3<T> operator * ( const matrix3x3<T> &m );

    // operacje matematyczne
    matrix3x3<T> identity();
    matrix3x3<T> transpose();
    matrix3x3<T> inverse();
    const T det() const;
};

//////////////////////////////////////////////////////////////////////
// operatory i operacje matematyczne na matrix3x3
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> transpose( const matrix3x3<T> &m );
template <class T> matrix3x3<T> inverse( const matrix3x3<T> &m );
template <class T> const T det( const matrix3x3<T> &m );
template <class T> bool operator == ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 );
template <class T> bool operator != ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 );
template <class T> matrix3x3<T> operator + ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 );
template <class T> matrix3x3<T> operator - ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 );
template <class T> matrix3x3<T> operator * ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 );
template <class T> matrix3x3<T> operator * ( const T *m1, const matrix3x3<T> &m2 );
template <class T> matrix3x3<T> operator * ( const matrix3x3<T> &m1, const T *m2 );
template <class T> matrix3x3<T> operator * ( const matrix3x3<T> &m, const T f );
template <class T> matrix3x3<T> operator * ( const T f, const matrix3x3<T> &m );
template <class T> vector3<T> operator * ( const matrix3x3<T> &m, const vector3<T> &v );

//////////////////////////////////////////////////////////////////////
// szablon klasy obs³uguj¹cej macierz 4x4
//////////////////////////////////////////////////////////////////////
template <class T = GLfloat> class matrix4x4
{
protected:
    // dane macierzy w uk³adzie wierszowym
    T m44[16];
public:
    // konstruktory
    matrix4x4();
    matrix4x4( const T a11, const T a12, const T a13, const T a14,
               const T a21, const T a22, const T a23, const T a24,
               const T a31, const T a32, const T a33, const T a34,
               const T a41, const T a42, const T a43, const T a44 );
    matrix4x4( const T *m );
    matrix4x4( const matrix4x4<T> &m );

    // pobieranie i zmiana danych
    const T *data() const;
    T &operator[] ( unsigned int i );
    const T &operator[] ( unsigned int i ) const;

    // operatory arytmetyczne
    matrix4x4<T> &operator += ( const matrix4x4<T> &m );
    matrix4x4<T> &operator -= ( const matrix4x4<T> &m );
    matrix4x4<T> &operator *= ( const matrix4x4<T> &m );
    matrix4x4<T> &operator *= ( const T f );
    matrix4x4<T> &operator /= ( const T f );
    matrix4x4<T> operator * ( const matrix4x4<T> &m );

    // operacje matematyczne
    matrix4x4<T> identity();
    matrix4x4<T> transpose();
    matrix4x4<T> inverse();
    const T det() const;

    // operacje OpenGL i GLU
    void Ortho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far );
    void Ortho2D( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top );
    void Perspective( GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far );
    void LoadIdentity();
    void Frustum( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far );
    void LoadMatrixd( const GLdouble *m );
    void LoadMatrixf( const GLfloat *m );
    void MultMatrixd( const GLdouble *m );
    void MultMatrixf( const GLfloat *m );
    void LoadTransposeMatrixf( const GLfloat *m );
    void LoadTransposeMatrixd( const GLdouble *m );
    void MultTransposeMatrixf( const GLfloat *m );
    void MultTransposeMatrixd( const GLdouble *m );
    void LookAt( GLdouble eyex, GLdouble eyey, GLdouble eyez,
                 GLdouble centerx, GLdouble centery, GLdouble centerz,
                 GLdouble upx, GLdouble upy, GLdouble upz );
    void Rotated( GLdouble angle, GLdouble x, GLdouble y, GLdouble z );
    void Rotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z );
    void Scaled( GLdouble x, GLdouble y, GLdouble z );
    void Scalef( GLfloat x, GLfloat y, GLfloat z );
    void Translated( GLdouble x, GLdouble y, GLdouble z );
    void Translatef( GLfloat x, GLfloat y, GLfloat z );
};

//////////////////////////////////////////////////////////////////////
// operatory i operacje matematyczne na matrix4x4
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> transpose( const matrix4x4<T> &m );
template <class T> matrix4x4<T> inverse( const matrix4x4<T> &m );
template <class T> const T det( const matrix4x4<T> &m );
template <class T> bool operator == ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 );
template <class T> bool operator != ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 );
template <class T> matrix4x4<T> operator + ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 );
template <class T> matrix4x4<T> operator - ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 );
template <class T> matrix4x4<T> operator * ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 );
template <class T> matrix4x4<T> operator * ( const T *m1, const matrix4x4<T> &m2 );
template <class T> matrix4x4<T> operator * ( const matrix4x4<T> &m1, const T *m2 );
template <class T> matrix4x4<T> operator * ( const matrix4x4<T> &m, const T f );
template <class T> matrix4x4<T> operator * ( const T f, const matrix4x4<T> &m );
template <class T> vector4<T> operator * ( const matrix4x4<T> &m, const vector4<T> &v );

////////////////////////////////////////////////////////////////////////////////
// szablon klasy obs³uguj¹cej kwaterniony jednostkowe
////////////////////////////////////////////////////////////////////////////////
template <class T = GLfloat > class quaternion : public vector4<>
{
public:
    // konstruktory
    quaternion();
    quaternion( const T *q );
    quaternion( const T x, const T y, const T z, const T w );
    quaternion( const matrix4x4<T> & m );
    quaternion( const vector3<T> &axis, T angle );

    // obs³uga konwersji do klasy vector4
    operator vector4<T>();
    quaternion( const vector4<T> &v );

    // operacje matematyczne i konwersje
    const T norm() const;
    const matrix4x4<T> matrix4() const;
    const matrix3x3<T> matrix3() const;
    quaternion<T> conjugate();
    quaternion<T> inverse();
    void getAxisAngle( vector3<T> &axis, T &angle ) const;

    // operator arytmetyczny, który ró¿ni siê od analogicznej
    // operacji zdefiniowanej dla klasy vector4
    quaternion<T> &operator *= ( const quaternion<T> & q );
};

//////////////////////////////////////////////////////////////////////
// operatory i operacje matematyczne na quaternion
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> conjugate( const quaternion<T> & q );
template <class T> quaternion<T> inverse( const quaternion<T> & q );
template <class T> quaternion<T> slerp( const quaternion<T> & p, const quaternion<T> & q, T alpha );
template <class T> quaternion<T> operator * ( const quaternion<T> & q1, const quaternion<T> & q2 );

//////////////////////////////////////////////////////////////////////
// konstruktor domyœlny
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T>::vector3()
{
    xyz[0] = static_cast<T> ( 0.0 );
    xyz[1] = static_cast<T> ( 0.0 );
    xyz[2] = static_cast<T> ( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// konstruktor trzyelementowy
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T>::vector3( const T x, const T y, const T z )
{
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}

//////////////////////////////////////////////////////////////////////
// konstruktor wektorowy
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T>::vector3( const T *v )
{
    xyz[0] = v[0];
    xyz[1] = v[1];
    xyz[2] = v[2];
}

//////////////////////////////////////////////////////////////////////
// konstruktor kopiuj¹cy
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T>::vector3( const vector3<T> &v )
{
    xyz[0] = v[0];
    xyz[1] = v[1];
    xyz[2] = v[2];
}

//////////////////////////////////////////////////////////////////////
// pobranie danych
//////////////////////////////////////////////////////////////////////
template <class T> const T *vector3<T>::data() const
{
    return xyz;
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy
//////////////////////////////////////////////////////////////////////
template <class T> T &vector3<T>::operator[] ( unsigned int i )
{
    return xyz[i];
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy
//////////////////////////////////////////////////////////////////////
template <class T> const T &vector3<T>::operator[] ( unsigned int i ) const
{
    return xyz[i];
}

//////////////////////////////////////////////////////////////////////
// pobranie pierwszej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> const T vector3<T>::x() const
{
    return xyz[0];
}

//////////////////////////////////////////////////////////////////////
// pobranie drugiej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> const T vector3<T>::y() const
{
    return xyz[1];
}

//////////////////////////////////////////////////////////////////////
// pobranie trzeciej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> const T vector3<T>::z() const
{
    return xyz[2];
}

//////////////////////////////////////////////////////////////////////
// zapis danych wszystkich sk³adowych
//////////////////////////////////////////////////////////////////////
template <class T> void vector3<T>::set( const T x, const T y, const T z )
{
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}

//////////////////////////////////////////////////////////////////////
// zapis danych pierwszej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> void vector3<T>::setX( const T x )
{
    xyz[0] = x;
}

//////////////////////////////////////////////////////////////////////
// zapis danych drugiej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> void vector3<T>::setY( const T y )
{
    xyz[1] = y;
}

//////////////////////////////////////////////////////////////////////
// zapis danych trzeciej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> void vector3<T>::setZ( const T z )
{
    xyz[2] = z;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> operator * ( const T f, const vector3<T> &v )
{
    return vector3<T>( v[0] * f, v[1] * f, v[2] * f );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> operator * ( const vector3<T> &v, const T f )
{
    return vector3<T>( v[0] * f, v[1] * f, v[2] * f );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> &vector3<T>::operator *= ( const T f )
{
    xyz[0] *= f;
    xyz[1] *= f;
    xyz[2] *= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// dzielenie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> &vector3<T>::operator /= ( const T f )
{
    xyz[0] /= f;
    xyz[1] /= f;
    xyz[2] /= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// dzielenie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> operator / ( const vector3<T> &v, const T f )
{
    return vector3<T>( v[0] / f, v[1] / f, v[2] / f );
}

//////////////////////////////////////////////////////////////////////
// przypisanie - operator +=
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> &vector3<T>::operator += ( const vector3<T> &v )
{
    xyz[0] += v[0];
    xyz[1] += v[1];
    xyz[2] += v[2];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// przypisanie - operator -=
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> &vector3<T>::operator -= ( const vector3<T> &v )
{
    xyz[0] -= v[0];
    xyz[1] -= v[1];
    xyz[2] -= v[2];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// negacja sk³adowych wektora
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> &vector3<T>::operator - ( const vector3<T> &v )
{
    xyz[0] = -v[0];
    xyz[1] = -v[1];
    xyz[2] = -v[2];
    xyz[3] = -v[3];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> vector3<T>::operator * ( const T f )
{
    return vector3<T>( xyz[0] *= f, xyz[1] *= f, xyz[2] *= f );
}

//////////////////////////////////////////////////////////////////////
// dodawanie - operator +
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> operator + ( const vector3<T> &v1, const vector3<T> &v2 )
{
    return vector3<T>( v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2] );
}

//////////////////////////////////////////////////////////////////////
// odejmowanie - operator -
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> operator - ( const vector3<T> &v1, const vector3<T> &v2 )
{
    return vector3<T>( v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2] );
}

//////////////////////////////////////////////////////////////////////
// test równoœci wektorów
//////////////////////////////////////////////////////////////////////
template <class T> bool operator == ( const vector3<T> &v1, const vector3<T> &v2 )
{
    return ( v1[0] == v2[0] ) && ( v1[1] == v2[1] ) && ( v1[2] == v2[2] );
}

//////////////////////////////////////////////////////////////////////
// test nierównoœci wektorów
//////////////////////////////////////////////////////////////////////
template <class T> bool operator != ( const vector3<T> &v1, const vector3<T> &v2 )
{
    return ( v1[0] != v2[0] ) || ( v1[1] != v2[1] ) || ( v1[2] != v2[2] );
}

//////////////////////////////////////////////////////////////////////
// d³ugoœæ wektora
//////////////////////////////////////////////////////////////////////
template <class T> const T vector3<T>::length() const
{
    return static_cast<T> ( sqrt( xyz[0]*xyz[0] + xyz[1]*xyz[1] + xyz[2]*xyz[2] ) );
}

//////////////////////////////////////////////////////////////////////
// wektor jednostkowy 3D (normalizacja)
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> vector3<T>::normalize()
{
    T d = length();
    if ( d )
    {
        xyz[0] /= d;
        xyz[1] /= d;
        xyz[2] /= d;
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////
// wektor jednostkowy 3D (normalizacja)
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> normalize( const vector3<T> &v )
{
    vector3<T> vec( v );
    return vec.normalize();
}

//////////////////////////////////////////////////////////////////////
// iloczyn skalarny wektorów
//////////////////////////////////////////////////////////////////////
template <class T> const T dot3( const vector3<T> &v1, const vector3<T> &v2 )
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

//////////////////////////////////////////////////////////////////////
// iloczyn wektorowy
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> cross3( const vector3<T> &v1, const vector3<T> &v2 )
{
    return vector3<T>( v1[1]*v2[2] - v2[1]*v1[2],
                       v2[0]*v1[2] - v1[0]*v2[2],
                       v1[0]*v2[1] - v2[0]*v1[1] );
}
//////////////////////////////////////////////////////////////////////
// konstruktor domyœlny
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T>::vector4()
{
    xyzw[0] = static_cast<T> ( 0.0 );
    xyzw[1] = static_cast<T> ( 0.0 );
    xyzw[2] = static_cast<T> ( 0.0 );
    xyzw[3] = static_cast<T> ( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// konstruktor czteroelementowy
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T>::vector4( const T x, const T y, const T z, const T w )
{
    xyzw[0] = x;
    xyzw[1] = y;
    xyzw[2] = z;
    xyzw[3] = w;
}

//////////////////////////////////////////////////////////////////////
// konstruktor wektorowy
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T>::vector4( const T *v )
{
    xyzw[0] = v[0];
    xyzw[1] = v[1];
    xyzw[2] = v[2];
    xyzw[3] = v[3];
}

//////////////////////////////////////////////////////////////////////
// konstruktor kopiuj¹cy
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T>::vector4( const vector4<T> &v )
{
    xyzw[0] = v[0];
    xyzw[1] = v[1];
    xyzw[2] = v[2];
    xyzw[3] = v[3];
}

//////////////////////////////////////////////////////////////////////
// pobranie danych
//////////////////////////////////////////////////////////////////////
template <class T> const T *vector4<T>::data() const
{
    return xyzw;
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy
//////////////////////////////////////////////////////////////////////
template <class T> T &vector4<T>::operator[] ( unsigned int i )
{
    return xyzw[i];
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy
//////////////////////////////////////////////////////////////////////
template <class T> const T &vector4<T>::operator[] ( unsigned int i ) const
{
    return xyzw[i];
}

//////////////////////////////////////////////////////////////////////
// pobranie pierwszej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> const T vector4<T>::x() const
{
    return xyzw[0];
}

//////////////////////////////////////////////////////////////////////
// pobranie drugiej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> const T vector4<T>::y() const
{
    return xyzw[1];
}

//////////////////////////////////////////////////////////////////////
// pobranie trzeciej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> const T vector4<T>::z() const
{
    return xyzw[2];
}

//////////////////////////////////////////////////////////////////////
// pobranie czwartej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> const T vector4<T>::w() const
{
    return xyzw[3];
}

//////////////////////////////////////////////////////////////////////
// zapis danych wszystkich sk³adowych
//////////////////////////////////////////////////////////////////////
template <class T> void vector4<T>::set( const T x, const T y, const T z, const T w )
{
    xyzw[0] = x;
    xyzw[1] = y;
    xyzw[2] = z;
    xyzw[3] = w;
}

//////////////////////////////////////////////////////////////////////
// zapis danych pierwszej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> void vector4<T>::setX( const T x )
{
    xyzw[0] = x;
}

//////////////////////////////////////////////////////////////////////
// zapis danych drugiej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> void vector4<T>::setY( const T y )
{
    xyzw[1] = y;
}

//////////////////////////////////////////////////////////////////////
// zapis danych trzeciej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> void vector4<T>::setZ( const T z )
{
    xyzw[2] = z;
}

//////////////////////////////////////////////////////////////////////
// zapis danych czwartej sk³adowej
//////////////////////////////////////////////////////////////////////
template <class T> void vector4<T>::setW( const T w )
{
    xyzw[3] = w;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> operator * ( const T f, const vector4<T> &v )
{
    return vector4<T>( v[0] * f, v[1] * f, v[2] * f, v[3] * f );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> operator * ( const vector4<T> &v, const T f )
{
    return vector4<T>( v[0] * f, v[1] * f, v[2] * f, v[3] * f );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> &vector4<T>::operator *= ( const T f )
{
    xyzw[0] *= f;
    xyzw[1] *= f;
    xyzw[2] *= f;
    xyzw[3] *= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// dzielenie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> &vector4<T>::operator /= ( const T f )
{
    xyzw[0] /= f;
    xyzw[1] /= f;
    xyzw[2] /= f;
    xyzw[3] /= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> vector4<T>::operator * ( const T f )
{
    return vector4<T>( xyzw[0] *= f, xyzw[1] *= f, xyzw[2] *= f, xyzw[3] *= f );
}

//////////////////////////////////////////////////////////////////////
// dzielenie przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> operator / ( const vector4<T> &v, const T f )
{
    return vector4<T>( v[0] / f, v[1] / f, v[2] / f, v[3] / f );
}

//////////////////////////////////////////////////////////////////////
// przypisanie - operator +=
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> &vector4<T>::operator += ( const vector4<T> &v )
{
    xyzw[0] += v[0];
    xyzw[1] += v[1];
    xyzw[2] += v[2];
    xyzw[3] += v[3];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// przypisanie - operator -=
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> &vector4<T>::operator -= ( const vector4<T> &v )
{
    xyzw[0] -= v[0];
    xyzw[1] -= v[1];
    xyzw[2] -= v[2];
    xyzw[3] -= v[3];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// negacja sk³adowych wektora
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> &vector4<T>::operator - ( const vector4<T> &v )
{
    xyzw[0] = -v[0];
    xyzw[1] = -v[1];
    xyzw[2] = -v[2];
    xyzw[3] = -v[3];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// dodawanie - operator +
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> operator + ( const vector4<T> &v1, const vector4<T> &v2 )
{
    return vector4<T>( v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2], v1[3]+v2[3] );
}

//////////////////////////////////////////////////////////////////////
// odejmowanie - operator -
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> operator - ( const vector4<T> &v1, const vector4<T> &v2 )
{
    return vector4<T>( v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2], v1[3]-v2[3] );
}

//////////////////////////////////////////////////////////////////////
// test równoœci wektorów
//////////////////////////////////////////////////////////////////////
template <class T> bool operator == ( const vector4<T> &v1, const vector4<T> &v2 )
{
    return ( v1[0] == v2[0] ) && ( v1[1] == v2[1] ) && ( v1[2] == v2[2] ) && ( v1[3] == v2[3] );
}

//////////////////////////////////////////////////////////////////////
// test nierównoœci wektorów
//////////////////////////////////////////////////////////////////////
template <class T> bool operator != ( const vector4<T> &v1, const vector4<T> &v2 )
{
    return ( v1[0] != v2[0] ) || ( v1[1] != v2[1] ) || ( v1[2] != v2[2] ) || ( v1[3] != v2[3] );
}

//////////////////////////////////////////////////////////////////////
// d³ugoœæ wektora
//////////////////////////////////////////////////////////////////////
template <class T> const T vector4<T>::length() const
{
    return static_cast<T> ( sqrt( xyzw[0]*xyzw[0] + xyzw[1]*xyzw[1] + xyzw[2]*xyzw[2] + xyzw[3]*xyzw[3] ) );
}

//////////////////////////////////////////////////////////////////////
// wektor jednostkowy 4D (normalizacja)
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> vector4<T>::normalize()
{
    T d = length();
    if ( d )
    {
        xyzw[0] /= d;
        xyzw[1] /= d;
        xyzw[2] /= d;
        xyzw[3] /= d;
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////
// wektor jednostkowy 4D (normalizacja)
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> normalize( const vector4<T> &v )
{
    vector4<T> vec( v );
    return vec.normalize();
}

//////////////////////////////////////////////////////////////////////
// iloczyn skalarny wektorów (3D)
//////////////////////////////////////////////////////////////////////
template <class T> const T dot3( const vector4<T> &v1, const vector4<T> &v2 )
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

//////////////////////////////////////////////////////////////////////
// iloczyn skalarny wektorów
//////////////////////////////////////////////////////////////////////
template <class T> const T dot4( const vector4<T> &v1, const vector4<T> &v2 )
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] + v1[3]*v2[3];
}

//////////////////////////////////////////////////////////////////////
// iloczyn wektorowy (3D), czwarta wspó³rzêdna równa 0
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> cross3( const vector4<T> &v1, const vector4<T> &v2 )
{
    return vector4<T>( v1[1]*v2[2] - v2[1]*v1[2],
                       v2[0]*v1[2] - v1[0]*v2[2],
                       v1[0]*v2[1] - v2[0]*v1[1],
                       static_cast<T>( 0.0 ) );
}

//////////////////////////////////////////////////////////////////////
// konstruktor domyœlny - zerowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T>::matrix3x3()
{
    m33[0] = static_cast<T>( 0.0 );
    m33[1] = static_cast<T>( 0.0 );
    m33[2] = static_cast<T>( 0.0 );
    m33[3] = static_cast<T>( 0.0 );
    m33[4] = static_cast<T>( 0.0 );
    m33[5] = static_cast<T>( 0.0 );
    m33[6] = static_cast<T>( 0.0 );
    m33[7] = static_cast<T>( 0.0 );
    m33[8] = static_cast<T>( 0.0 );
}

//////////////////////////////////////////////////////////////////////
// konstruktor 9-cio elementowy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T>::matrix3x3( const T a11, const T a12, const T a13,
        const T a21, const T a22, const T a23,
        const T a31, const T a32, const T a33 )
{
    m33[0] = a11;
    m33[1] = a12;
    m33[2] = a13;
    m33[3] = a21;
    m33[4] = a22;
    m33[5] = a23;
    m33[6] = a31;
    m33[7] = a32;
    m33[8] = a33;
}

//////////////////////////////////////////////////////////////////////
// konstruktor wskaŸnikowy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T>::matrix3x3( const T *m )
{
    m33[0] = m[0];
    m33[1] = m[1];
    m33[2] = m[2];
    m33[3] = m[3];
    m33[4] = m[4];
    m33[5] = m[5];
    m33[6] = m[6];
    m33[7] = m[7];
    m33[8] = m[8];
}

//////////////////////////////////////////////////////////////////////
// konstruktor kopiuj¹cy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T>::matrix3x3( const matrix3x3<T> &m )
{
    m33[0] = m[0];
    m33[1] = m[1];
    m33[2] = m[2];
    m33[3] = m[3];
    m33[4] = m[4];
    m33[5] = m[5];
    m33[6] = m[6];
    m33[7] = m[7];
    m33[8] = m[8];
}

//////////////////////////////////////////////////////////////////////
// pobranie danych
//////////////////////////////////////////////////////////////////////
template <class T> const T *matrix3x3<T>::data() const
{
    return m33;
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy (liniowy)
//////////////////////////////////////////////////////////////////////
template <class T> T &matrix3x3<T>::operator[] ( unsigned int i )
{
    return m33[i];
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy (liniowy)
//////////////////////////////////////////////////////////////////////
template <class T> const T &matrix3x3<T>::operator[] ( unsigned int i ) const
{
    return m33[i];
}

//////////////////////////////////////////////////////////////////////
// przypisanie, operator +=
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> &matrix3x3<T>::operator += ( const matrix3x3<T> &m )
{
    m33[0] += m[0];
    m33[1] += m[1];
    m33[2] += m[2];
    m33[3] += m[3];
    m33[4] += m[4];
    m33[5] += m[5];
    m33[6] += m[6];
    m33[7] += m[7];
    m33[8] += m[8];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// przypisanie, operator -=
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> &matrix3x3<T>::operator -= ( const matrix3x3<T> &m )
{
    m33[0] -= m[0];
    m33[1] -= m[1];
    m33[2] -= m[2];
    m33[3] -= m[3];
    m33[4] -= m[4];
    m33[5] -= m[5];
    m33[6] -= m[6];
    m33[7] -= m[7];
    m33[8] -= m[8];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// przypisanie, operator *=
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> &matrix3x3<T>::operator *= ( const matrix3x3<T> &m )
{
    matrix3x3<T> matrix( m33[0] * m[0] + m33[1] * m[3] + m33[2] * m[6],
                         m33[0] * m[1] + m33[1] * m[4] + m33[2] * m[7],
                         m33[0] * m[2] + m33[1] * m[5] + m33[2] * m[8],
                         m33[3] * m[0] + m33[4] * m[3] + m33[5] * m[6],
                         m33[3] * m[1] + m33[4] * m[4] + m33[5] * m[7],
                         m33[3] * m[2] + m33[4] * m[5] + m33[5] * m[8],
                         m33[6] * m[0] + m33[7] * m[3] + m33[8] * m[6],
                         m33[6] * m[1] + m33[7] * m[4] + m33[8] * m[7],
                         m33[6] * m[2] + m33[7] * m[5] + m33[8] * m[8] );
    *this = matrix;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> &matrix3x3<T>::operator *= ( const T f )
{
    m33[0] *= f;
    m33[1] *= f;
    m33[2] *= f;
    m33[3] *= f;
    m33[4] *= f;
    m33[5] *= f;
    m33[6] *= f;
    m33[7] *= f;
    m33[8] *= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// dzielenie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> &matrix3x3<T>::operator /= ( const T f )
{
    m33[0] /= f;
    m33[1] /= f;
    m33[2] /= f;
    m33[3] /= f;
    m33[4] /= f;
    m33[5] /= f;
    m33[6] /= f;
    m33[7] /= f;
    m33[8] /= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// operator porównania - test równoœci macierzy
//////////////////////////////////////////////////////////////////////
template <class T> bool operator == ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 )
{
    return ( m1[0] == m2[0] ) && ( m1[1] == m2[1] ) && ( m1[2] == m2[2] ) &&
           ( m1[3] == m2[3] ) && ( m1[4] == m2[4] ) && ( m1[5] == m2[5] ) &&
           ( m1[6] == m2[6] ) && ( m1[7] == m2[7] ) && ( m1[8] == m2[8] );
}

//////////////////////////////////////////////////////////////////////
// operator porównania - test nierównoœci macierzy
//////////////////////////////////////////////////////////////////////
template <class T> bool operator != ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 )
{
    return ( m1[0] != m2[0] ) || ( m1[1] != m2[1] ) || ( m1[2] != m2[2] ) ||
           ( m1[3] != m2[3] ) || ( m1[4] != m2[4] ) || ( m1[5] != m2[5] ) ||
           ( m1[6] != m2[6] ) || ( m1[7] != m2[7] ) || ( m1[8] != m2[8] );
}

//////////////////////////////////////////////////////////////////////
// dodawanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> operator + ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 )
{
    return matrix3x3<T>( m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2],
                         m1[3] + m2[3], m1[4] + m2[4], m1[5] + m2[5],
                         m1[6] + m2[6], m1[7] + m2[7], m1[8] + m2[8] );
}

//////////////////////////////////////////////////////////////////////
// odejmowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> operator - ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 )
{
    return matrix3x3<T>( m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2],
                         m1[3] - m2[3], m1[4] - m2[4], m1[5] - m2[5],
                         m1[6] - m2[6], m1[7] - m2[7], m1[8] - m2[8] );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> operator * ( const matrix3x3<T> &m1, const matrix3x3<T> &m2 )
{
    return matrix3x3<T>( m1[0] * m2[0] + m1[1] * m2[3] + m1[2] * m2[6],
                         m1[0] * m2[1] + m1[1] * m2[4] + m1[2] * m2[7],
                         m1[0] * m2[2] + m1[1] * m2[5] + m1[2] * m2[8],
                         m1[3] * m2[0] + m1[4] * m2[3] + m1[5] * m2[6],
                         m1[3] * m2[1] + m1[4] * m2[4] + m1[5] * m2[7],
                         m1[3] * m2[2] + m1[4] * m2[5] + m1[5] * m2[8],
                         m1[6] * m2[0] + m1[7] * m2[3] + m1[8] * m2[6],
                         m1[6] * m2[1] + m1[7] * m2[4] + m1[8] * m2[7],
                         m1[6] * m2[2] + m1[7] * m2[5] + m1[8] * m2[8] );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////

template <class T> matrix3x3<T> operator * ( const T *m1, const matrix3x3<T> &m2 )
{
    return matrix3x3<T>( m1 ) * m2;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> operator * ( const matrix3x3<T> &m1, const T *m2 )
{
    return m1 * matrix3x3<T>( m2 );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> operator * ( const matrix3x3<T> &m, const T f )
{
    return m * f;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> operator * ( const T f, const matrix3x3<T> &m )
{
    return f * m;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> matrix3x3<T>::operator * ( const matrix3x3<T> &m )
{
    return matrix3x3<T>( m33[0] * m[0] + m33[1] * m[3] + m33[2] * m[6],
                         m33[0] * m[1] + m33[1] * m[4] + m33[2] * m[7],
                         m33[0] * m[2] + m33[1] * m[5] + m33[2] * m[8],
                         m33[3] * m[0] + m33[4] * m[3] + m33[5] * m[6],
                         m33[3] * m[1] + m33[4] * m[4] + m33[5] * m[7],
                         m33[3] * m[2] + m33[4] * m[5] + m33[5] * m[8],
                         m33[6] * m[0] + m33[7] * m[3] + m33[8] * m[6],
                         m33[6] * m[1] + m33[7] * m[4] + m33[8] * m[7],
                         m33[6] * m[2] + m33[7] * m[5] + m33[8] * m[8] );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez wektor
//////////////////////////////////////////////////////////////////////
template <class T> vector3<T> operator * ( const matrix3x3<T> &m, const vector3<T> &v )
{
    return vector3<T>( m[0] * v[0] + m[1] * v[1] + m[2] * v[2],
                       m[3] * v[0] + m[4] * v[1] + m[5] * v[2],
                       m[6] * v[0] + m[7] * v[1] + m[8] * v[2] );
}

//////////////////////////////////////////////////////////////////////
// macierz jednostkowa
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> matrix3x3<T>::identity()
{
    m33[0] = static_cast<T>( 1.0 );
    m33[1] = static_cast<T>( 0.0 );
    m33[2] = static_cast<T>( 0.0 );
    m33[3] = static_cast<T>( 0.0 );
    m33[4] = static_cast<T>( 1.0 );
    m33[5] = static_cast<T>( 0.0 );
    m33[6] = static_cast<T>( 0.0 );
    m33[7] = static_cast<T>( 0.0 );
    m33[8] = static_cast<T>( 1.0 );
    return *this;
}

//////////////////////////////////////////////////////////////////////
// transponowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> matrix3x3<T>::transpose()
{
    matrix3x3<T> matrix( m33[0], m33[3], m33[6],
                         m33[1], m33[4], m33[7],
                         m33[2], m33[5], m33[8] );
    *this = matrix;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// odwracanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> matrix3x3<T>::inverse()
{
    // obliczanie wyznacznika macierzy
    const T determinant = det();

    // sprawdzanie, czy macierz posiada macierz odwrotn¹;
    // je¿eli nie zwracamy macierz jednostkow¹
    if ( determinant == static_cast<T> ( 0.0 ) )
    {
        identity();
    }
    else
    {
        const T invDet = static_cast<T> ( 1.0 / determinant );
        T matrix[9];
        matrix[0] = (m33[4] * m33[8] - m33[5] * m33[7]) * invDet;
        matrix[1] = (m33[2] * m33[7] - m33[1] * m33[8]) * invDet;
        matrix[2] = (m33[1] * m33[5] - m33[2] * m33[4]) * invDet;
        matrix[3] = (m33[5] * m33[6] - m33[3] * m33[8]) * invDet;
        matrix[4] = (m33[0] * m33[8] - m33[2] * m33[6]) * invDet;
        matrix[5] = (m33[2] * m33[3] - m33[0] * m33[5]) * invDet;
        matrix[6] = (m33[3] * m33[7] - m33[4] * m33[6]) * invDet;
        matrix[7] = (m33[1] * m33[6] - m33[0] * m33[7]) * invDet;
        matrix[8] = (m33[0] * m33[4] - m33[1] * m33[3]) * invDet;
        *this = matrix3x3<T>( matrix );
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////
// wyznacznik macierzy
//////////////////////////////////////////////////////////////////////
template <class T> const T matrix3x3<T>::det() const
{
    return m33[0] * (m33[4] * m33[8] - m33[7] * m33[5]) +
           m33[3] * (m33[7] * m33[2] - m33[1] * m33[8]) +
           m33[6] * (m33[1] * m33[5] - m33[4] * m33[2]);
}

//////////////////////////////////////////////////////////////////////
// transponowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> transpose( const matrix3x3<T> &m )
{
    matrix3x3<T> matrix( m );
    return matrix.transpose();
}

//////////////////////////////////////////////////////////////////////
// odwracanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix3x3<T> inverse( const matrix3x3<T> &m )
{
    matrix3x3<T> matrix( m );
    return matrix.inverse();
}

//////////////////////////////////////////////////////////////////////
// obliczanie wyznacznika macierzy
//////////////////////////////////////////////////////////////////////
template <class T> const T det( const matrix3x3<T> &m )
{
    return m.det();
}

//////////////////////////////////////////////////////////////////////
// konstruktor domyœlny - zerowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T>::matrix4x4()
{
    m44[0] = static_cast<T>( 1.0 );
    m44[1] = static_cast<T>( 0.0 );
    m44[2] = static_cast<T>( 0.0 );
    m44[3] = static_cast<T>( 0.0 );
    m44[4] = static_cast<T>( 0.0 );
    m44[5] = static_cast<T>( 1.0 );
    m44[6] = static_cast<T>( 0.0 );
    m44[7] = static_cast<T>( 0.0 );
    m44[8] = static_cast<T>( 0.0 );
    m44[9] = static_cast<T>( 0.0 );
    m44[10] = static_cast<T>( 1.0 );
    m44[11] = static_cast<T>( 0.0 );
    m44[12] = static_cast<T>( 0.0 );
    m44[13] = static_cast<T>( 0.0 );
    m44[14] = static_cast<T>( 0.0 );
    m44[15] = static_cast<T>( 1.0 );
}

//////////////////////////////////////////////////////////////////////
// konstruktor 16-to elementowy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T>::matrix4x4( const T a11, const T a12, const T a13, const T a14,
        const T a21, const T a22, const T a23, const T a24,
        const T a31, const T a32, const T a33, const T a34,
        const T a41, const T a42, const T a43, const T a44 )
{
    m44[0] = a11;
    m44[1] = a12;
    m44[2] = a13;
    m44[3] = a14;
    m44[4] = a21;
    m44[5] = a22;
    m44[6] = a23;
    m44[7] = a24;
    m44[8] = a31;
    m44[9] = a32;
    m44[10] = a33;
    m44[11] = a34;
    m44[12] = a41;
    m44[13] = a42;
    m44[14] = a43;
    m44[15] = a44;
}

//////////////////////////////////////////////////////////////////////
// konstruktor wskaŸnikowy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T>::matrix4x4( const T *m )
{
    m44[0] = m[0];
    m44[1] = m[1];
    m44[2] = m[2];
    m44[3] = m[3];
    m44[4] = m[4];
    m44[5] = m[5];
    m44[6] = m[6];
    m44[7] = m[7];
    m44[8] = m[8];
    m44[9] = m[9];
    m44[10] = m[10];
    m44[11] = m[11];
    m44[12] = m[12];
    m44[13] = m[13];
    m44[14] = m[14];
    m44[15] = m[15];
}

//////////////////////////////////////////////////////////////////////
// konstruktor kopiuj¹cy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T>::matrix4x4( const matrix4x4<T> &m )
{
    m44[0] = m[0];
    m44[1] = m[1];
    m44[2] = m[2];
    m44[3] = m[3];
    m44[4] = m[4];
    m44[5] = m[5];
    m44[6] = m[6];
    m44[7] = m[7];
    m44[8] = m[8];
    m44[9] = m[9];
    m44[10] = m[10];
    m44[11] = m[11];
    m44[12] = m[12];
    m44[13] = m[13];
    m44[14] = m[14];
    m44[15] = m[15];
}

//////////////////////////////////////////////////////////////////////
// pobranie danych
//////////////////////////////////////////////////////////////////////
template <class T> const T *matrix4x4<T>::data() const
{
    return m44;
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy (liniowy)
//////////////////////////////////////////////////////////////////////
template <class T> T &matrix4x4<T>::operator[] ( unsigned int i )
{
    return m44[i];
}

//////////////////////////////////////////////////////////////////////
// operator tablicowy (liniowy)
//////////////////////////////////////////////////////////////////////
template <class T> const T &matrix4x4<T>::operator[] ( unsigned int i ) const
{
    return m44[i];
}

//////////////////////////////////////////////////////////////////////
// przypisanie, operator +=
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> &matrix4x4<T>::operator += ( const matrix4x4<T> &m )
{
    m44[0] += m[0];
    m44[1] += m[1];
    m44[2] += m[2];
    m44[3] += m[3];
    m44[4] += m[4];
    m44[5] += m[5];
    m44[6] += m[6];
    m44[7] += m[7];
    m44[8] += m[8];
    m44[9] += m[9];
    m44[10] += m[10];
    m44[11] += m[11];
    m44[12] += m[12];
    m44[13] += m[13];
    m44[14] += m[14];
    m44[15] += m[15];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// przypisanie, operator -=
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> &matrix4x4<T>::operator -= ( const matrix4x4<T> &m )
{
    m44[0] -= m[0];
    m44[1] -= m[1];
    m44[2] -= m[2];
    m44[3] -= m[3];
    m44[4] -= m[4];
    m44[5] -= m[5];
    m44[6] -= m[6];
    m44[7] -= m[7];
    m44[8] -= m[8];
    m44[9] -= m[9];
    m44[10] -= m[10];
    m44[11] -= m[11];
    m44[12] -= m[12];
    m44[13] -= m[13];
    m44[14] -= m[14];
    m44[15] -= m[15];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// przypisanie, operator *=
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> &matrix4x4<T>::operator *= ( const matrix4x4<T> &m )
{
    matrix4x4<T> matrix( m44[0] * m[0] + m44[1] * m[4] + m44[2] * m[8] + m44[3] * m[12],
                         m44[0] * m[1] + m44[1] * m[5] + m44[2] * m[9] + m44[3] * m[13],
                         m44[0] * m[2] + m44[1] * m[6] + m44[2] * m[10] + m44[3] * m[14],
                         m44[0] * m[3] + m44[1] * m[7] + m44[2] * m[11] + m44[3] * m[15],
                         m44[4] * m[0] + m44[5] * m[4] + m44[6] * m[8] + m44[7] * m[12],
                         m44[4] * m[1] + m44[5] * m[5] + m44[6] * m[9] + m44[7] * m[13],
                         m44[4] * m[2] + m44[5] * m[6] + m44[6] * m[10] + m44[7] * m[14],
                         m44[4] * m[3] + m44[5] * m[7] + m44[6] * m[11] + m44[7] * m[15],
                         m44[8] * m[0] + m44[9] * m[4] + m44[10] * m[8] + m44[11] * m[12],
                         m44[8] * m[1] + m44[9] * m[5] + m44[10] * m[9] + m44[11] * m[13],
                         m44[8] * m[2] + m44[9] * m[6] + m44[10] * m[10] + m44[11] * m[14],
                         m44[8] * m[3] + m44[9] * m[7] + m44[10] * m[11] + m44[11] * m[15],
                         m44[12] * m[0] + m44[13] * m[4] + m44[14] * m[8] + m44[15] * m[12],
                         m44[12] * m[1] + m44[13] * m[5] + m44[14] * m[9] + m44[15] * m[13],
                         m44[12] * m[2] + m44[13] * m[6] + m44[14] * m[10] + m44[15] * m[14],
                         m44[12] * m[3] + m44[13] * m[7] + m44[14] * m[11] + m44[15] * m[15] );
    *this = matrix;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> &matrix4x4<T>::operator *= ( const T f )
{
    m44[0] *= f;
    m44[1] *= f;
    m44[2] *= f;
    m44[3] *= f;
    m44[4] *= f;
    m44[5] *= f;
    m44[6] *= f;
    m44[7] *= f;
    m44[8] *= f;
    m44[9] *= f;
    m44[10] *= f;
    m44[11] *= f;
    m44[12] *= f;
    m44[13] *= f;
    m44[14] *= f;
    m44[15] *= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// dzielenie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> &matrix4x4<T>::operator /= ( const T f )
{
    m44[0] /= f;
    m44[1] /= f;
    m44[2] /= f;
    m44[3] /= f;
    m44[4] /= f;
    m44[5] /= f;
    m44[6] /= f;
    m44[7] /= f;
    m44[8] /= f;
    m44[9] /= f;
    m44[10] /= f;
    m44[11] /= f;
    m44[12] /= f;
    m44[13] /= f;
    m44[14] /= f;
    m44[15] /= f;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// operator porównania - test równoœci macierzy
//////////////////////////////////////////////////////////////////////
template <class T> bool operator == ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 )
{
    return ( m1[0] == m2[0] ) && ( m1[1] == m2[1] ) && ( m1[2] == m2[2] ) &&
           ( m1[3] == m2[3] ) && ( m1[4] == m2[4] ) && ( m1[5] == m2[5] ) &&
           ( m1[6] == m2[6] ) && ( m1[7] == m2[7] ) && ( m1[8] == m2[8] ) &&
           ( m1[9] == m2[9] ) && ( m1[10] == m2[10] ) && ( m1[11] == m2[11] ) &&
           ( m1[12] == m2[12] ) && ( m1[13] == m2[13] ) && ( m1[14] == m2[14] ) &&
           ( m1[15] == m2[15] );
}

//////////////////////////////////////////////////////////////////////
// operator porównania - test nierównoœci macierzy
//////////////////////////////////////////////////////////////////////
template <class T> bool operator != ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 )
{
    return ( m1[0] != m2[0] ) || ( m1[1] != m2[1] ) || ( m1[2] != m2[2] ) ||
           ( m1[3] != m2[3] ) || ( m1[4] != m2[4] ) || ( m1[5] != m2[5] ) ||
           ( m1[6] != m2[6] ) || ( m1[7] != m2[7] ) || ( m1[8] != m2[8] ) ||
           ( m1[9] != m2[9] ) || ( m1[10] != m2[10] ) || ( m1[11] != m2[11] ) ||
           ( m1[12] != m2[12] ) || ( m1[13] != m2[13] ) || ( m1[14] != m2[14] ) ||
           ( m1[15] != m2[15] );
}

//////////////////////////////////////////////////////////////////////
// dodawanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> operator + ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 )
{
    return matrix4x4<T>( m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2],
                         m1[3] + m2[3], m1[4] + m2[4], m1[5] + m2[5],
                         m1[6] + m2[6], m1[7] + m2[7], m1[8] + m2[8],
                         m1[9] + m2[9], m1[10] + m2[10], m1[11] + m2[11],
                         m1[12] + m2[12], m1[13] + m2[13], m1[14] + m2[14],
                         m1[15] + m2[15] );
}

//////////////////////////////////////////////////////////////////////
// odejmowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> operator - ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 )
{
    return matrix4x4<T>( m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2],
                         m1[3] - m2[3], m1[4] - m2[4], m1[5] - m2[5],
                         m1[6] - m2[6], m1[7] - m2[7], m1[8] - m2[8],
                         m1[9] - m2[9], m1[10] - m2[10], m1[11] - m2[11],
                         m1[12] - m2[12], m1[13] - m2[13], m1[14] - m2[14],
                         m1[15] - m2[15] );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> operator * ( const matrix4x4<T> &m1, const matrix4x4<T> &m2 )
{

    return matrix4x4<T>( m1[0] * m2[0] + m1[1] * m2[4] + m1[2] * m2[8] + m1[3] * m2[12],
                         m1[0] * m2[1] + m1[1] * m2[5] + m1[2] * m2[9] + m1[3] * m2[13],
                         m1[0] * m2[2] + m1[1] * m2[6] + m1[2] * m2[10] + m1[3] * m2[14],
                         m1[0] * m2[3] + m1[1] * m2[7] + m1[2] * m2[11] + m1[3] * m2[15],
                         m1[4] * m2[0] + m1[5] * m2[4] + m1[6] * m2[8] + m1[7] * m2[12],
                         m1[4] * m2[1] + m1[5] * m2[5] + m1[6] * m2[9] + m1[7] * m2[13],
                         m1[4] * m2[2] + m1[5] * m2[6] + m1[6] * m2[10] + m1[7] * m2[14],
                         m1[4] * m2[3] + m1[5] * m2[7] + m1[6] * m2[11] + m1[7] * m2[15],
                         m1[8] * m2[0] + m1[9] * m2[4] + m1[10] * m2[8] + m1[11] * m2[12],
                         m1[8] * m2[1] + m1[9] * m2[5] + m1[10] * m2[9] + m1[11] * m2[13],
                         m1[8] * m2[2] + m1[9] * m2[6] + m1[10] * m2[10] + m1[11] * m2[14],
                         m1[8] * m2[3] + m1[9] * m2[7] + m1[10] * m2[11] + m1[11] * m2[15],
                         m1[12] * m2[0] + m1[13] * m2[4] + m1[14] * m2[8] + m1[15] * m2[12],
                         m1[12] * m2[1] + m1[13] * m2[5] + m1[14] * m2[9] + m1[15] * m2[13],
                         m1[12] * m2[2] + m1[13] * m2[6] + m1[14] * m2[10] + m1[15] * m2[14],
                         m1[12] * m2[3] + m1[13] * m2[7] + m1[14] * m2[11] + m1[15] * m2[15] );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////

template <class T> matrix4x4<T> operator * ( const T *m1, const matrix4x4<T> &m2 )
{
    return matrix4x4<T>( m1 ) * m2;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> operator * ( const matrix4x4<T> &m1, const T *m2 )
{
    return m1 * matrix4x4<T>( m2 );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> operator * ( const matrix4x4<T> &m, const T f )
{
    return m * f;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez sta³¹
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> operator * ( const T f, const matrix4x4<T> &m )
{
    return f * m;
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> matrix4x4<T>::operator * ( const matrix4x4<T> &m )
{
    return matrix4x4<T>( m44[0] * m[0] + m44[1] * m[4] + m44[2] * m[8] + m44[3] * m[12],
                         m44[0] * m[1] + m44[1] * m[5] + m44[2] * m[9] + m44[3] * m[13],
                         m44[0] * m[2] + m44[1] * m[6] + m44[2] * m[10] + m44[3] * m[14],
                         m44[0] * m[3] + m44[1] * m[7] + m44[2] * m[11] + m44[3] * m[15],
                         m44[4] * m[0] + m44[5] * m[4] + m44[6] * m[8] + m44[7] * m[12],
                         m44[4] * m[1] + m44[5] * m[5] + m44[6] * m[9] + m44[7] * m[13],
                         m44[4] * m[2] + m44[5] * m[6] + m44[6] * m[10] + m44[7] * m[14],
                         m44[4] * m[3] + m44[5] * m[7] + m44[6] * m[11] + m44[7] * m[15],
                         m44[8] * m[0] + m44[9] * m[4] + m44[10] * m[8] + m44[11] * m[12],
                         m44[8] * m[1] + m44[9] * m[5] + m44[10] * m[9] + m44[11] * m[13],
                         m44[8] * m[2] + m44[9] * m[6] + m44[10] * m[10] + m44[11] * m[14],
                         m44[8] * m[3] + m44[9] * m[7] + m44[10] * m[11] + m44[11] * m[15],
                         m44[12] * m[0] + m44[13] * m[4] + m44[14] * m[8] + m44[15] * m[12],
                         m44[12] * m[1] + m44[13] * m[5] + m44[14] * m[9] + m44[15] * m[13],
                         m44[12] * m[2] + m44[13] * m[6] + m44[14] * m[10] + m44[15] * m[14],
                         m44[12] * m[3] + m44[13] * m[7] + m44[14] * m[11] + m44[15] * m[15] );
}

//////////////////////////////////////////////////////////////////////
// mno¿enie macierzy przez wektor
//////////////////////////////////////////////////////////////////////
template <class T> vector4<T> operator * ( const matrix4x4<T> &m, const vector4<T> &v )
{
    return vector4<T>( m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3] * v[3],
                       m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7] * v[3],
                       m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11] * v[3],
                       m[12] * v[0] + m[13] * v[1] + m[14] * v[2] + m[15] * v[3] );
}

//////////////////////////////////////////////////////////////////////
// macierz jednostkowa
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> matrix4x4<T>::identity()
{
    m44[0] = static_cast<T>( 1.0 );
    m44[1] = static_cast<T>( 0.0 );
    m44[2] = static_cast<T>( 0.0 );
    m44[3] = static_cast<T>( 0.0 );
    m44[4] = static_cast<T>( 0.0 );
    m44[5] = static_cast<T>( 1.0 );
    m44[6] = static_cast<T>( 0.0 );
    m44[7] = static_cast<T>( 0.0 );
    m44[8] = static_cast<T>( 0.0 );
    m44[9] = static_cast<T>( 0.0 );
    m44[10] = static_cast<T>( 1.0 );
    m44[11] = static_cast<T>( 0.0 );
    m44[12] = static_cast<T>( 0.0 );
    m44[13] = static_cast<T>( 0.0 );
    m44[14] = static_cast<T>( 0.0 );
    m44[15] = static_cast<T>( 1.0 );
    return *this;
}

//////////////////////////////////////////////////////////////////////
// transponowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> matrix4x4<T>::transpose()
{
    matrix4x4<T> matrix( m44[0], m44[4], m44[8], m44[12],
                         m44[1], m44[5], m44[9], m44[13],
                         m44[2], m44[6], m44[10], m44[14],
                         m44[3], m44[7], m44[11], m44[15] );
    *this = matrix;
    return *this;
}

//////////////////////////////////////////////////////////////////////
// odwracanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> matrix4x4<T>::inverse()
{
    // obliczanie wyznacznika macierzy
    const T determinant = det();

    // sprawdzanie, czy macierz posiada macierz odwrotn¹;
    // je¿eli nie zwracamy macierz jednostkow¹
    if ( determinant == static_cast<T> ( 0.0 ) )
    {
        identity();
    }
    else
    {
        T matrix[16];
        const T invDet = static_cast<T> ( 1.0 / determinant );
        T d12 = m44[8] * m44[13] - m44[12] * m44[9];
        T d13 = m44[8] * m44[14] - m44[12] * m44[10];
        T d23 = m44[9] * m44[14] - m44[13] * m44[10];
        T d24 = m44[9] * m44[15] - m44[13] * m44[11];
        T d34 = m44[10] * m44[15] - m44[14] * m44[11];
        T d41 = m44[11] * m44[12] - m44[15] * m44[8];

        matrix[0] =  (m44[5] * d34 - m44[6] * d24 + m44[7] * d23) * invDet;
        matrix[4] = -(m44[4] * d34 + m44[6] * d41 + m44[7] * d13) * invDet;
        matrix[8] =  (m44[4] * d24 + m44[5] * d41 + m44[7] * d12) * invDet;
        matrix[12] = -(m44[4] * d23 - m44[5] * d13 + m44[6] * d12) * invDet;
        matrix[1] = -(m44[1] * d34 - m44[2] * d24 + m44[3] * d23) * invDet;
        matrix[5] =  (m44[0] * d34 + m44[2] * d41 + m44[3] * d13) * invDet;
        matrix[9] = -(m44[0] * d24 + m44[1] * d41 + m44[3] * d12) * invDet;
        matrix[13] =  (m44[0] * d23 - m44[1] * d13 + m44[2] * d12) * invDet;

        d12 = m44[0] * m44[5] - m44[4] * m44[1];
        d13 = m44[0] * m44[6] - m44[4] * m44[2];
        d23 = m44[1] * m44[6] - m44[5] * m44[2];
        d24 = m44[1] * m44[7] - m44[5] * m44[3];
        d34 = m44[2] * m44[7] - m44[6] * m44[3];
        d41 = m44[0] * m44[4] - m44[7] * m44[0];

        matrix[2]  =  (m44[13] * d34 - m44[14] * d24 + m44[15] * d23) * invDet;
        matrix[6]  = -(m44[12] * d34 + m44[14] * d41 + m44[15] * d13) * invDet;
        matrix[10] =  (m44[12] * d24 + m44[13] * d41 + m44[15] * d12) * invDet;
        matrix[14] = -(m44[12] * d23 - m44[13] * d13 + m44[14] * d12) * invDet;
        matrix[3] = -(m44[9] * d34 - m44[10] * d24 + m44[11] * d23) * invDet;
        matrix[7] =  (m44[8] * d34 + m44[10] * d41 + m44[11] * d13) * invDet;
        matrix[11] = -(m44[8] * d24 + m44[9] * d41 + m44[11] * d12) * invDet;
        matrix[15] =  (m44[8] * d23 - m44[9] * d13 + m44[10] * d12) * invDet;
        *this = matrix4x4<T>( matrix );
    }
    return *this;
}

//////////////////////////////////////////////////////////////////////
// wyznacznik macierzy
//////////////////////////////////////////////////////////////////////
template <class T> const T matrix4x4<T>::det() const
{
    const T d12 = m44[8] * m44[13] - m44[12] * m44[9];
    const T d13 = m44[8] * m44[14] - m44[12] * m44[10];
    const T d23 = m44[9] * m44[14] - m44[13] * m44[10];
    const T d24 = m44[9] * m44[15] - m44[13] * m44[11];
    const T d34 = m44[10] * m44[15] - m44[14] * m44[11];
    const T d41 = m44[11] * m44[12] - m44[15] * m44[8];
    return m44[0] * (m44[5] * d34 - m44[6] * d24 + m44[7] * d23) -
           m44[1] * (m44[4] * d34 + m44[6] * d41 + m44[7] * d13) +
           m44[2] * (m44[4] * d24 + m44[5] * d41 + m44[7] * d12) -
           m44[3] * (m44[4] * d23 - m44[5] * d13 + m44[6] * d12);
}

//////////////////////////////////////////////////////////////////////
// transponowanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> transpose( const matrix4x4<T> &m )
{
    matrix4x4<T> matrix( m );
    return matrix.transpose();
}

//////////////////////////////////////////////////////////////////////
// odwracanie macierzy
//////////////////////////////////////////////////////////////////////
template <class T> matrix4x4<T> inverse( const matrix4x4<T> &m )
{
    matrix4x4<T> matrix( m );
    return matrix.inverse();
}

//////////////////////////////////////////////////////////////////////
// obliczanie wyznacznika macierzy
//////////////////////////////////////////////////////////////////////
template <class T> const T det( const matrix4x4<T> &m )
{
    return m.det();
}

//////////////////////////////////////////////////////////////////////
// macierz rzutu prostok¹tnego 2D
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Ortho2D( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top )
{
    Ortho( left, right, bottom, top, -1.0, 1.0 );
}

//////////////////////////////////////////////////////////////////////
// macierz rzutu prostok¹tnego 3D
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Ortho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far )
{
    matrix4x4<T> matrix ( static_cast<T>( 2.0 / (right - left) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( -(right + left) / (right - left) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 2.0 / (top - bottom) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( -(top + bottom) / (top - bottom) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( -2.0 / (far - near) ),
                          static_cast<T>( -(far + near) / (far - near) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz rzutu perspektywicznego
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Perspective( GLdouble fovy, GLdouble aspect, GLdouble near, GLdouble far )
{
    T radians = static_cast<T>( fovy / 2.0 * 3.14159265358979323846 / 180.0 );
    T sine = static_cast<T>( sin( radians ) );
    if ( (far == near) || (sine == static_cast<T>( 0.0 )) || (aspect == static_cast<T>( 0.0 )) ) return;
    T cotangent = static_cast<T>( cos( radians ) / sine );

    // macierz wynikowa
    matrix4x4<T> matrix( static_cast<T>( cotangent / aspect ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),

                         static_cast<T>( 0.0 ),
                         static_cast<T>( cotangent ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),

                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( -(far + near) / (far - near) ),
                         static_cast<T>( -1.0 ),

                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( -2.0 * near * far / (far - near) ),
                         static_cast<T>( 0.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz jednostkowa; wynik zastêpuje bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::LoadIdentity()
{
    identity();
}

//////////////////////////////////////////////////////////////////////
// macierz rzutu perspektywicznego
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Frustum( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far )
{
    matrix4x4<T> matrix ( static_cast<T>( 2.0 * near / (right - left) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( (right + left) / (right - left) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 2.0 * near / (top - bottom) ),
                          static_cast<T>( (top + bottom) / (top - bottom) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( -(far + near) / (far - near) ),
                          static_cast<T>( -2.0 * far * near / (far - near) ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( 0.0 ),
                          static_cast<T>( -1.0 ),
                          static_cast<T>( 0.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy z tablicy danych typu GLdouble
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::LoadMatrixd( const GLdouble *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[1] ), static_cast<T>( m[2] ), static_cast<T>( m[3] ),
                         static_cast<T>( m[4] ), static_cast<T>( m[5] ), static_cast<T>( m[6] ), static_cast<T>( m[7] ),
                         static_cast<T>( m[8] ), static_cast<T>( m[9] ), static_cast<T>( m[10] ), static_cast<T>( m[11] ),
                         static_cast<T>( m[12] ), static_cast<T>( m[13] ), static_cast<T>( m[14] ), static_cast<T>( m[15] ) );
    *this = matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy z tablicy danych typu GLfloat
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::LoadMatrixf( const GLfloat *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[1] ), static_cast<T>( m[2] ), static_cast<T>( m[3] ),
                         static_cast<T>( m[4] ), static_cast<T>( m[5] ), static_cast<T>( m[6] ), static_cast<T>( m[7] ),
                         static_cast<T>( m[8] ), static_cast<T>( m[9] ), static_cast<T>( m[10] ), static_cast<T>( m[11] ),
                         static_cast<T>( m[12] ), static_cast<T>( m[13] ), static_cast<T>( m[14] ), static_cast<T>( m[15] ) );
    *this = matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy z tablicy danych typu GLdouble
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::MultMatrixd( const GLdouble *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[1] ), static_cast<T>( m[2] ), static_cast<T>( m[3] ),
                         static_cast<T>( m[4] ), static_cast<T>( m[5] ), static_cast<T>( m[6] ), static_cast<T>( m[7] ),
                         static_cast<T>( m[8] ), static_cast<T>( m[9] ), static_cast<T>( m[10] ), static_cast<T>( m[11] ),
                         static_cast<T>( m[12] ), static_cast<T>( m[13] ), static_cast<T>( m[14] ), static_cast<T>( m[15] ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy z tablicy danych typu GLfloat
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::MultMatrixf( const GLfloat *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[1] ), static_cast<T>( m[2] ), static_cast<T>( m[3] ),
                         static_cast<T>( m[4] ), static_cast<T>( m[5] ), static_cast<T>( m[6] ), static_cast<T>( m[7] ),
                         static_cast<T>( m[8] ), static_cast<T>( m[9] ), static_cast<T>( m[10] ), static_cast<T>( m[11] ),
                         static_cast<T>( m[12] ), static_cast<T>( m[13] ), static_cast<T>( m[14] ), static_cast<T>( m[15] ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy transponowanej z tablicy danych typu GLfloat
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::LoadTransposeMatrixf( const GLfloat *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[4] ), static_cast<T>( m[8] ), static_cast<T>( m[12] ),
                         static_cast<T>( m[1] ), static_cast<T>( m[5] ), static_cast<T>( m[9] ), static_cast<T>( m[13] ),
                         static_cast<T>( m[2] ), static_cast<T>( m[6] ), static_cast<T>( m[10] ), static_cast<T>( m[14] ),
                         static_cast<T>( m[3] ), static_cast<T>( m[7] ), static_cast<T>( m[11] ), static_cast<T>( m[15] ) );
    *this = matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy transponowanej z tablicy danych typu GLdouble
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::LoadTransposeMatrixd( const GLdouble *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[4] ), static_cast<T>( m[8] ), static_cast<T>( m[12] ),
                         static_cast<T>( m[1] ), static_cast<T>( m[5] ), static_cast<T>( m[9] ), static_cast<T>( m[13] ),
                         static_cast<T>( m[2] ), static_cast<T>( m[6] ), static_cast<T>( m[10] ), static_cast<T>( m[14] ),
                         static_cast<T>( m[3] ), static_cast<T>( m[7] ), static_cast<T>( m[11] ), static_cast<T>( m[15] ) );
    *this = matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy transponowanej z tablicy danych typu GLfloat
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::MultTransposeMatrixf( const GLfloat *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[4] ), static_cast<T>( m[8] ), static_cast<T>( m[12] ),
                         static_cast<T>( m[1] ), static_cast<T>( m[5] ), static_cast<T>( m[9] ), static_cast<T>( m[13] ),
                         static_cast<T>( m[2] ), static_cast<T>( m[6] ), static_cast<T>( m[10] ), static_cast<T>( m[14] ),
                         static_cast<T>( m[3] ), static_cast<T>( m[7] ), static_cast<T>( m[11] ), static_cast<T>( m[15] ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// za³adowanie macierzy transponowanej z tablicy danych typu GLdouble
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::MultTransposeMatrixd( const GLdouble *m )
{
    matrix4x4<T> matrix( static_cast<T>( m[0] ), static_cast<T>( m[4] ), static_cast<T>( m[8] ), static_cast<T>( m[12] ),
                         static_cast<T>( m[1] ), static_cast<T>( m[5] ), static_cast<T>( m[9] ), static_cast<T>( m[13] ),
                         static_cast<T>( m[2] ), static_cast<T>( m[6] ), static_cast<T>( m[10] ), static_cast<T>( m[14] ),
                         static_cast<T>( m[3] ), static_cast<T>( m[7] ), static_cast<T>( m[11] ), static_cast<T>( m[15] ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz rzutowania na podstawie po³o¿enjia obserwatora (eye*),
// punktu centralnego (center*) i wektora kierunku "do góry" (up*)
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::LookAt( GLdouble eyex, GLdouble eyey, GLdouble eyez,
        GLdouble centerx, GLdouble centery, GLdouble centerz,
        GLdouble upx, GLdouble upy, GLdouble upz )
{
    T forward[3];
    forward[0] = static_cast<T>( centerx - eyex );
    forward[1] = static_cast<T>( centery - eyey );
    forward[2] = static_cast<T>( centerz - eyez );
    T d = static_cast<T>( sqrt( forward[0] * forward[0] + forward[1] * forward[1] + forward[2] * forward[2] ) );
    if ( d != static_cast<T>( 1.0 ) && d != static_cast<T>( 0.0 ) )
    {
        forward[0] /= d;
        forward[1] /= d;
        forward[2] /= d;
    }

    T up[3];
    up[0] = static_cast<T>( upx );
    up[1] = static_cast<T>( upy );
    up[2] = static_cast<T>( upz );

    T side[3];
    side[0] = forward[1]*up[2] - forward[2]*up[1];
    side[1] = forward[2]*up[0] - forward[0]*up[2];
    side[2] = forward[0]*up[1] - forward[1]*up[0];

    d = static_cast<T>( sqrt( side[0] * side[0] + side[1] * side[1] + side[2] * side[2] ) );
    if ( d != static_cast<T>( 1.0 ) && d != static_cast<T>( 0.0 ) )
    {
        forward[0] /= d;
        forward[1] /= d;
        forward[2] /= d;
    }

    up[0] = side[1]*forward[2] - side[2]*forward[1];
    up[1] = side[2]*forward[0] - side[0]*forward[2];
    up[2] = side[0]*forward[1] - side[1]*forward[0];

    // macierz przekszta³cenia
    matrix4x4<T> matrix( side[0], side[1], side[2], static_cast<T>( -eyex ),
                         up[0], up[1], up[2], static_cast<T>( -eyey ),
                         -forward[0], -forward[1], -forward[2], static_cast<T>( -eyez ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz obrotu
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Rotated( GLdouble angle, GLdouble x, GLdouble y, GLdouble z )
{
    const T d = static_cast<T>( sqrt( x * x + y * y + z * z ) );
    if ( d != 1.0 && d != 0.0 )
    {
        x /= static_cast<GLdouble>( d );
        y /= static_cast<GLdouble>( d );
        z /= static_cast<GLdouble>( d );
    }
    const T c = static_cast<T>( cos( angle * 3.141592653589793 / 180.0 ) );
    const T s = static_cast<T>( sin( angle * 3.141592653589793 / 180.0 ) );
    matrix4x4<T> matrix( static_cast<T>( x * x * (1 - c) + c ),
                         static_cast<T>( x * y * (1 - c) - z * s ),
                         static_cast<T>( x * z * (1 - c) + y * s ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( y * x * (1 - c) + z * s ),
                         static_cast<T>( y * y * (1 - c) + c ),
                         static_cast<T>( y * z * (1 - c) - x * s ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( x * z * (1 - c) - y * s ),
                         static_cast<T>( y * z * (1 - c) + x * s ),
                         static_cast<T>( z * z * (1 - c) + c ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz obrotu
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Rotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z )
{
    const T d = static_cast<T>( sqrt( x * x + y * y + z * z ) );
    if ( d != 1.0 && d != 0.0 )
    {
        x /= static_cast<GLfloat>( d );
        y /= static_cast<GLfloat>( d );
        z /= static_cast<GLfloat>( d );
    }
    const T c = static_cast<T>( cos( angle * 3.141592653589793 / 180.0 ) );
    const T s = static_cast<T>( sin( angle * 3.141592653589793 / 180.0 ) );
    matrix4x4<T> matrix( static_cast<T>( x * x * (1 - c) + c ),
                         static_cast<T>( x * y * (1 - c) - z * s ),
                         static_cast<T>( x * z * (1 - c) + y * s ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( y * x * (1 - c) + z * s ),
                         static_cast<T>( y * y * (1 - c) + c ),
                         static_cast<T>( y * z * (1 - c) - x * s ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( x * z * (1 - c) - y * s ),
                         static_cast<T>( y * z * (1 - c) + x * s ),
                         static_cast<T>( z * z * (1 - c) + c ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz skalowania
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Scaled( GLdouble x, GLdouble y, GLdouble z )
{
    matrix4x4<T> matrix( static_cast<T>( x ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( y ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( z ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz skalowania
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Scalef( GLfloat x, GLfloat y, GLfloat z )
{
    matrix4x4<T> matrix( static_cast<T>( x ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( y ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( z ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz przesuniêcia
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Translated( GLdouble x, GLdouble y, GLdouble z )
{
    matrix4x4<T> matrix( static_cast<T>( 1.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( x ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( y ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ),
                         static_cast<T>( z ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// macierz przesuniêcia
// wynik jest mno¿ony przez bie¿¹c¹ macierz
//////////////////////////////////////////////////////////////////////
template <class T> void matrix4x4<T>::Translatef( GLfloat x, GLfloat y, GLfloat z )
{
    matrix4x4<T> matrix( static_cast<T>( 1.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( x ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( y ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ),
                         static_cast<T>( z ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 0.0 ),
                         static_cast<T>( 1.0 ) );
    *this *= matrix;
}

//////////////////////////////////////////////////////////////////////
// konstruktor domyœlny
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T>::quaternion(): vector4<T>()
{
}

//////////////////////////////////////////////////////////////////////
// konstruktor wektorowy
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T>::quaternion( const T *q ): vector4<T>( q )
{
}

//////////////////////////////////////////////////////////////////////
// konstruktor czteroelementowy
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T>::quaternion( const T x, const T y, const T z, const T w ): vector4<T>( x, y, z, w )
{
}

//////////////////////////////////////////////////////////////////////
// konwersja do klasy vector4
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T>::operator vector4<T>()
{
    return vector4<T>( xyzw );
}

//////////////////////////////////////////////////////////////////////
// konstruktor kopiuj¹cy z klasy vector4
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T>::quaternion( const vector4<T> &v ): vector4<T>( v )
{
}

//////////////////////////////////////////////////////////////////////
// konstruktor z macierzy obrotu 4x4, tworzony jest kwaternion jednostkowy
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T>::quaternion( const matrix4x4<T> & m )
{
    // suma elementów na g³ównej przek¹tnej macierzy obrotu 3x3 (œlad)
    T tr = m[0] + m[5] + m[10];

    // rozwi¹zanie wzglêdem wspó³czynnika w
    if ( tr > 0.0 )
    {
        T s = static_cast<T> ( sqrt( tr + m[15] ) );
        xyzw[3] = static_cast<T> ( s * 0.5 );
        s = static_cast<T> ( 0.5 / s );
        xyzw[0] = (m[9] - m[6]) * s;
        xyzw[1] = (m[2] - m[8]) * s;
        xyzw[2] = (m[4] - m[1]) * s;
    }
    else
    {
        // rozwi¹anie wzglêdem wspó³czynników x, y i z
        // poszukiwanie elelemntu o najwiêkszej wartoœci bezwzglêdnej
        int i = 0;
        if ( m[5] > m[0] ) i = 1;
        if ( m[10] > m[i*3+i] ) i = 2;
        const int nxt[3] = { 1, 2, 0 };
        int j = nxt[i];
        int k = nxt[j];
        T s = static_cast<T> ( sqrt( ( m[i*3+j] - ( m[j*3+j] + m[k*3+k] ) ) + 1.0 ) );
        xyzw[i] = static_cast<T> ( s * 0.5 );
        s = static_cast<T> ( 0.5 / s );
        xyzw[3] = ( m[j*3+k] - m[k*3+j] ) * s;
        xyzw[j] = ( m[i*3+j] + m[j*3+i] ) * s;
        xyzw[k] = ( m[i*3+k] + m[k*3+i] ) * s;
    }
}

//////////////////////////////////////////////////////////////////////
// konstruktor z wektora opisuj¹cego oœ obrotu i k¹t obrotu w stopniach
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T>::quaternion( const vector3<T> &axis, T angle )
{
    // kwadrat modu³u wektora osi obrotu
    T sqnorm = dot3( axis, axis );

    // kwadrat modu³u równy zero
    if ( sqnorm == static_cast<T> ( 0.0 ) )
    {
        xyzw[0] = static_cast<T> ( 0.0 );
        xyzw[1] = static_cast<T> ( 0.0 );
        xyzw[2] = static_cast<T> ( 0.0 );
        xyzw[3] = static_cast<T> ( 1.0 );
    }
    else
    {
        // konwersja stopnie -> radiany * 1/2 i obliczanie wartoœci funkcji sinus
        angle *= static_cast<T>( 0.5 * 3.141592653589793 / 180.0 );
        T sinAngle = static_cast<T>( sin( angle ) );

        // w razie potrzeby normalizacja (je¿eli wektor obrotu nie jest wersorem)
        if ( sqnorm != static_cast<T>( 1.0 ) )
            sinAngle /= static_cast<T>( sqrt( sqnorm ) );

        // koñcowe obliczenia wspó³czynników kwaternionu
        xyzw[0] = sinAngle * axis[0];
        xyzw[1] = sinAngle * axis[1];
        xyzw[2] = sinAngle * axis[2];
        xyzw[3] = static_cast<T>( cos( angle ) );
    }
}

//////////////////////////////////////////////////////////////////////
// modu³
//////////////////////////////////////////////////////////////////////
template <class T> const T quaternion<T>::norm() const
{
    return length();
}

//////////////////////////////////////////////////////////////////////
// pobranie macierzy obrotu 4x4
//////////////////////////////////////////////////////////////////////
template <class T> const matrix4x4<T> quaternion<T>::matrix4() const
{
    // obliczenie wspó³czynnika normalizuj¹cego
    // (niezbêdne dla kwaternionów innych ni¿ jednostkowe)
    T norm = dot4( *this, *this );
    T s = ( norm == static_cast<T> ( 0.0 ) ) ? static_cast<T> ( 0.0 ) : static_cast<T> ( 2.0 / norm );

    // zmienne pomocnicze
    T xs = xyzw[0] * s;
    T ys = xyzw[1] * s;
    T zs = xyzw[2] * s;
    T wx = xyzw[3] * xs;
    T wy = xyzw[3] * ys;
    T wz = xyzw[3] * zs;
    T xx = xyzw[0] * xs;
    T xy = xyzw[0] * ys;
    T xz = xyzw[0] * zs;
    T yy = xyzw[1] * ys;
    T yz = xyzw[1] * zs;
    T zz = xyzw[2] * zs;

    // macierz wynikowa
    return matrix4x4<T> ( static_cast<T> ( 1.0 - (yy + zz) ),
                          xy - wz,
                          xz + wy,
                          static_cast<T> ( 0.0 ),
                          xy + wz,
                          static_cast<T> ( 1.0 - (xx + zz) ),
                          yz - wx,
                          static_cast<T> ( 0.0 ),
                          xz - wy,
                          yz + wx,
                          static_cast<T> ( 1.0 - (xx + yy) ),
                          static_cast<T> ( 0.0 ),
                          static_cast<T> ( 0.0 ),
                          static_cast<T> ( 0.0 ),
                          static_cast<T> ( 0.0 ),
                          static_cast<T> ( 1.0 ) );
}

//////////////////////////////////////////////////////////////////////
// pobranie macierzy obrotu 3x3
//////////////////////////////////////////////////////////////////////
template <class T> const matrix3x3<T> quaternion<T>::matrix3() const
{
    // obliczenie wspó³czynnika normalizuj¹cego
    // (niezbêdne dla kwaternionów innych ni¿ jednostkowe)
    T norm = dot4( *this, *this );
    T s = ( norm == static_cast<T> ( 0.0 ) ) ? static_cast<T> ( 0.0 ) : static_cast<T> ( 2.0 / norm );

    // zmienne pomocnicze
    T xs = xyzw[0] * s;
    T ys = xyzw[1] * s;
    T zs = xyzw[2] * s;
    T wx = xyzw[3] * xs;
    T wy = xyzw[3] * ys;
    T wz = xyzw[3] * zs;
    T xx = xyzw[0] * xs;
    T xy = xyzw[0] * ys;
    T xz = xyzw[0] * zs;
    T yy = xyzw[1] * ys;
    T yz = xyzw[1] * zs;
    T zz = xyzw[2] * zs;

    // macierz wynikowa
    return matrix3x3<T> ( static_cast<T> ( 1.0 - (yy + zz) ),
                          xy - wz,
                          xz + wy,
                          xy + wz,
                          static_cast<T> ( 1.0 - (xx + zz) ),
                          yz - wx,
                          xz - wy,
                          yz + wx,
                          static_cast<T> ( 1.0 - (xx + yy) ) );
}

//////////////////////////////////////////////////////////////////////
// sprzê¿enie
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> quaternion<T>::conjugate()
{
    xyzw[0] = -xyzw[0];
    xyzw[1] = -xyzw[1];
    xyzw[2] = -xyzw[2];
    return *this;
}

//////////////////////////////////////////////////////////////////////
// kwaternion odwrotny
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> quaternion<T>::inverse()
{
    return conjugate();
}

//////////////////////////////////////////////////////////////////////
// pobranie osi i k¹ta obrotu (w stopniach)
//////////////////////////////////////////////////////////////////////
template <class T> void quaternion<T>::getAxisAngle( vector3<T> &axis, T &angle ) const
{
    angle = static_cast<T> ( 180.0 /3.141592653589793 * acos( xyzw[3] ) * 2.0 );
    if ( angle == 0.0 )
        axis = vector3<T>( static_cast<T>( 0.0 ), static_cast<T>( 0.0 ), static_cast<T>( 1.0 ) );
    else
    {
        axis[0] = xyzw[0];
        axis[1] = xyzw[1];
        axis[2] = xyzw[2];
        axis.normalize();
    }
}

//////////////////////////////////////////////////////////////////////
// interpolacja kwaternionów, k¹t alpha w rasianch
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> slerp( const quaternion<T> & p, const quaternion<T> & q, T alpha )
{
    // cosinus k¹ta miêdzy wektorami
    T cosOmega = p[0] * q[0] + p[1] * q[1] + p[2] * q[2] + p[3] * q[3];
    bool bflip = cosOmega < static_cast<T>( 0.0 );
    if ( bflip ) cosOmega = -cosOmega;

    // obliczanie parametrów interpolacji
    T beta = static_cast<T>( 1.0 ) - alpha;
    if ( cosOmega >= static_cast<T>( 1.0 ) ) return p;
    T omega = static_cast<T>( acos( cosOmega ) );
    T oneOverSinOmega = static_cast<T>( 1.0 / sin( omega ) );
    beta = static_cast<T>( sin( omega * beta )  * oneOverSinOmega );
    alpha = static_cast<T>( sin( omega * alpha ) * oneOverSinOmega );
    if ( bflip ) alpha = -alpha;

    // kwaternion wynikowy
    quaternion<T> r;
    r[0] = beta * p[0]+ alpha * q[0];
    r[1] = beta * p[1]+ alpha * q[1];
    r[2] = beta * p[2]+ alpha * q[2];
    r[3] = beta * p[3]+ alpha * q[3];
    return r;
}

//////////////////////////////////////////////////////////////////////
// operator *=
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> &quaternion<T>::operator *= ( const quaternion<T> & q )
{
    *this = quaternion<T>( xyzw[3] * q[0] + xyzw[0] * q[3] + xyzw[1] * q[2] - xyzw[2] * q[1],
                           xyzw[3] * q[1] + xyzw[1] * q[3] + xyzw[2] * q[0] - xyzw[0] * q[2],
                           xyzw[3] * q[2] + xyzw[2] * q[3] + xyzw[0] * q[1] - xyzw[1] * q[0],
                           xyzw[3] * q[3] - xyzw[0] * q[0] - xyzw[1] * q[1] - xyzw[2] * q[2] );
    return *this;
}

//////////////////////////////////////////////////////////////////////
// sprzê¿enie
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> conjugate( const quaternion<T> & q )
{
    quaternion<T> quat( q );
    quat.conjugate();
    return quat;
}

//////////////////////////////////////////////////////////////////////
// kwaternion odwrotny
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> inverse( const quaternion<T> & q )
{
    quaternion<T> quat( q );
    quat.inverse();
    return quat;
}

//////////////////////////////////////////////////////////////////////
// operator *
//////////////////////////////////////////////////////////////////////
template <class T> quaternion<T> operator * ( const quaternion<T> & q1, const quaternion<T> & q2 )
{
    quaternion<T> q( q1 );
    q *= q2;
    return q;
}


#endif // MATHEMATIC_HPP_INCLUDED
