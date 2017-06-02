#ifndef DEFINES_H
#define DEFINES_H

#include <QApplication>
#include <QtOpenGL>
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif

#include <stdint.h>
#include <iostream>

using namespace std;

#include <math.h>
#include <float.h>

#define WINDOW_WIDTH  1800
#define WINDOW_HEIGHT 1100

#define MOUSE_WHEEL_SENSIBILTY 0.01

#define	b2_maxFloat		FLT_MAX
#define	b2_epsilon		FLT_EPSILON
#define b2_pi			3.14159265359f

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

typedef signed char	int8;
typedef signed short int16;
typedef signed int int32;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef float float32;
typedef double float64;


enum editionMode {
    EDIT_MODE_ADD_TILE,
    EDIT_MODE_ERASE_TILE,
    EDIT_MODE_EDIT_TILE,
    EDIT_MODE_SELECTION_TILE,
    EDIT_MODE_FLAG,
    EDIT_MODE_START_POSITION,
    EDIT_MODE_END_POSITION,
    EDIT_MODE_ADD_PAINT_BUCKET_TILE,
    EDIT_MODE_ADD_LASER,
    EDIT_MODE_SELECT_OBJECT,
    EDIT_MODE_ADD_JETON,
    EDIT_MODE_REMOVE_OBJECT,
    EDIT_MODE_ADD_EMITTER,
    EDIT_MODE_ADD_SWITCH,
    EDIT_MODE_SWITCH_SELECT_TARGET,
    EDIT_MODE_ADD_AND_DOOR,
    EDIT_MODE_AND_DOOR_SELECT_TARGET,
    EDIT_MODE_ADD_OR_DOOR,
    EDIT_MODE_OR_DOOR_SELECT_TARGET,
    EDIT_MODE_ADD_NO_DOOR,
    EDIT_MODE_NO_DOOR_SELECT_TARGET,
    EDIT_MODE_ADD_PLATFORM,
    EDIT_MODE_PLATFORM_ADD_POINT,
    EDIT_MODE_ADD_PUSH_BUTTON,
    EDIT_MODE_PUSH_BUTTON_SELECT_TARGET
};

#ifdef UNUSED
#elif defined(__GNUC__)
# define UNUSED(x) UNUSED_ ## x __attribute__((unused))
#elif defined(__LCLINT__)
# define UNUSED(x) /*@unused@*/ x
#elif defined(__cplusplus)
# define UNUSED(x)
#else
# define UNUSED(x) x
#endif

inline static QString appDirPath(){
    #ifdef __APPLE__
        return QCoreApplication::applicationDirPath().remove("/MapEditor.app/Contents/MacOS"); // Va falloir adapter cette ligne
    #else
        return QCoreApplication::applicationDirPath();
    #endif
}

inline static QString imagesDirPath(){
    #ifdef __APPLE__
        return QCoreApplication::applicationDirPath().replace("//", "/").remove("MacOS")+"Resources/images/"; // Va falloir adapter cette ligne
    #else
        return QCoreApplication::applicationDirPath() + "/images/";
    #endif
}


inline static bool QImageIsTransparent(QImage img){
    quint32 *pixels = (quint32 *)img.bits();
    int imgSize = img.width() * img.height();
    bool isTransparent = true;

    for (int i = 0; i < imgSize; ++i){
        if (((pixels[i] >> 24) & 0xFF) != 0){
            isTransparent = false;
            break;
        }
    }

    return isTransparent;
}

//TO DELETE AFTER BOX2D INTEGRATION

inline bool b2IsValid(float32 x)
{
    int32 ix = *reinterpret_cast<int32*>(&x);
    return (ix & 0x7f800000) != 0x7f800000;
}

#define	b2Sqrt(x)	sqrtf(x)
#define	b2Atan2(y, x)	atan2f(y, x)

/// A 2D column vector.
struct b2Vec2
{
    /// Default constructor does nothing (for performance).
    b2Vec2() {}

    /// Construct using coordinates.
    b2Vec2(float32 x, float32 y) : x(x), y(y) {}

    /// Set this vector to all zeros.
    void SetZero() { x = 0.0f; y = 0.0f; }

    /// Set this vector to some specified coordinates.
    void Set(float32 x_, float32 y_) { x = x_; y = y_; }

    /// Negate this vector.
    b2Vec2 operator -() const { b2Vec2 v; v.Set(-x, -y); return v; }

    /// Read from and indexed element.
    float32 operator () (int32 i) const
    {
        return (&x)[i];
    }

    /// Write to an indexed element.
    float32& operator () (int32 i)
    {
        return (&x)[i];
    }

    /// Add a vector to this vector.
    void operator += (const b2Vec2& v)
    {
        x += v.x; y += v.y;
    }

    /// Subtract a vector from this vector.
    void operator -= (const b2Vec2& v)
    {
        x -= v.x; y -= v.y;
    }

    /// Multiply this vector by a scalar.
    void operator *= (float32 a)
    {
        x *= a; y *= a;
    }

    /// Get the length of this vector (the norm).
    float32 Length() const
    {
        return b2Sqrt(x * x + y * y);
    }

    /// Get the length squared. For performance, use this instead of
    /// b2Vec2::Length (if possible).
    float32 LengthSquared() const
    {
        return x * x + y * y;
    }

    /// Convert this vector into a unit vector. Returns the length.
    float32 Normalize()
    {
        float32 length = Length();
        if (length < b2_epsilon)
        {
            return 0.0f;
        }
        float32 invLength = 1.0f / length;
        x *= invLength;
        y *= invLength;

        return length;
    }

    /// Does this vector contain finite coordinates?
    bool IsValid() const
    {
        return b2IsValid(x) && b2IsValid(y);
    }

    /// Get the skew vector such that dot(skew_vec, other) == cross(vec, other)
    b2Vec2 Skew() const
    {
        return b2Vec2(-y, x);
    }

    float32 x, y;
};

/// Add two vectors component-wise.
inline b2Vec2 operator + (const b2Vec2& a, const b2Vec2& b)
{
    return b2Vec2(a.x + b.x, a.y + b.y);
}

/// Subtract two vectors component-wise.
inline b2Vec2 operator - (const b2Vec2& a, const b2Vec2& b)
{
    return b2Vec2(a.x - b.x, a.y - b.y);
}

inline b2Vec2 operator * (float32 s, const b2Vec2& a)
{
    return b2Vec2(s * a.x, s * a.y);
}

inline b2Vec2 operator * (const b2Vec2& a, float32 s)
{
    return b2Vec2(s * a.x, s * a.y);
}

inline bool operator == (const b2Vec2& a, const b2Vec2& b)
{
    return a.x == b.x && a.y == b.y;
}

inline float32 b2Distance(const b2Vec2& a, const b2Vec2& b)
{
    b2Vec2 c = a - b;
    return c.Length();
}

//END TO DELETE





inline b2Vec2 operator / (const b2Vec2& a, float32 s)
{
    return b2Vec2(a.x / s, a.y / s);
}




struct Settings{
    Settings(){
        viewCenter.Set(0.0f, 0.0f);
        cameraPosition.Set(0.0f, 0.0f);
        lower.Set(0, 0);
        upper.Set(0, 0);
        viewZoom = 1.0f;
        cameraZoom = 1.0f;
        viewSize = 25.0f;
        hz       = 10.0f;
        velocityIterations = 8;
        positionIterations = 3;
        pause = 0;
        singleStep = 0;
        height = WINDOW_HEIGHT;
        width  = WINDOW_WIDTH;
        simulation_speed = 1;
    }

    b2Vec2 viewCenter, cameraPosition;
    b2Vec2 lower;
    b2Vec2 upper;
    float viewZoom, cameraZoom;
    float viewSize;
    float hz;
    int   velocityIterations;
    int   positionIterations;
    int   pause;
    int   singleStep;
    int   height, width;
    int   simulation_speed;
};

template<typename T>
void delete_obj(T *&ptr) {
    if(ptr)
        delete ptr;
    ptr = NULL;
}


struct Rect{
    b2Vec2 min, max;
};

struct BBox{
    BBox(){
        for(int i = 0; i < 4; i++){
            x[i] = 0;
            y[i] = 0;
        }

        rect.min = b2Vec2(0, 0);
        rect.max = b2Vec2(0, 0);
    }

    BBox(Rect r){
        rect = r;
        x[0] = rect.min.x;
        y[0] = rect.min.y;
        x[1] = rect.min.x;
        y[1] = rect.max.y;
        x[2] = rect.max.x;
        y[2] = rect.max.y;
        x[3] = rect.max.x;
        y[3] = rect.min.y;
    }

    bool collide(BBox box){
        float d1x = box.rect.min.x - rect.max.x;
        float d1y = box.rect.min.y - rect.max.y;
        float d2x = rect.min.x - box.rect.max.x;
        float d2y = rect.min.y - box.rect.max.y;

        if(d1x > 0.0f || d1y > 0.0f)
            return false;

        if(d2x > 0.0f || d2y > 0.0f)
            return false;

        return true;
    }

    float x[4];
    float y[4];
    Rect  rect;
};

inline float doubRand(){
    return (float)rand()/RAND_MAX;
}

#endif // DEFINES_H

