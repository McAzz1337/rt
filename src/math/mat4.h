#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"
#include "vec3.h"

class Mat4
{

    static constexpr int SIZE = 4;
    Vec4 m[SIZE];

    public:
    Mat4();
    Mat4(const Mat4& mat);
    Mat4(double* m);

    Mat4 transpose();
    Mat4 inverse();

    void translate(const Vec3& t);
    void rotate(const Vec3& axis, double angle);
    void scale(const Vec3& s);

    Mat4 operator*(Mat4& m);
    Vec4 operator*(const Vec4& v) const;

    Vec4& operator[](int i);

    bool operator==(Mat4& m);

    void print() const;
};

#endif // MAT4_H
