// Simple struct for 2D vectors
#pragma once
#include <iostream>

struct Vector2D
{
    Vector2D() = default;
    Vector2D(double tx, double ty)
        : x(tx), y(ty) {};
    
    // TODO copy constructor and assigment operator
    
    double x;
    double y;

    // primarily for debuging purposes
    friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec);
};

// vector addition
// rvalue to avoid unnecessay copying 
Vector2D  operator+ (const Vector2D& v1,   const Vector2D& v2);
Vector2D& operator+=(Vector2D&       vlhs, const Vector2D& vrhs);
Vector2D  operator- (const Vector2D& v1,   const Vector2D& v2);

// Vector multiplication (dot product)
double vec_inner(const Vector2D& v1, const Vector2D& v2);
// Scalar multiplication 
Vector2D operator*(Vector2D& vec, const double c);