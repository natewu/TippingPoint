#include "main.h"

class Vector{
    public:
        /* 
            Constructor.
            
            @param x The x-coordinate of the vector.
            @param y The y-coordinate of the vector.
        */
        Vector(float x, float y);
        /* 
            Returns the x-coordinate of the vector.
        */
        float x();
        /* 
            Returns the y-coordinate of the vector.
        */
        float y();
        /* 
            Returns the magnitude of the vector.
        */
        float magnitude();
        /* 
            Returns the angle of the vector.
        */
        float angle();

        /* 
            Normalizes the vector(return vector with magnitude of 1).
        */
        Vector& normalize();

        Vector& rotate(float angle);
        Vector& add(Vector v);
        Vector& subtract(Vector v);
        Vector& multiply(float scalar);
        Vector& divide(float scalar);

    private:
        float storedX = 0;
        float storedY = 0;
};

class Bezier{
    public:
        /* 
            Constructor.
            
            @param start The start point of the curve.
            @param end The end point of the curve.
            @param control The control point of the curve.
        */
        Bezier(Vector start, Vector end, Vector control);

        /* 
            Returns the start point of the curve.
        */
        Vector start();
        /* 
            Returns the end point of the curve.
        */
        Vector end();
        /* 
            Returns the control point of the curve.
        */
        Vector control();

        /* 
            Returns the length of the curve.
        */
        float length();

        /* 
            Returns the point at a given distance along the curve.
            
            @param distance The distance along the curve.
        */
        Vector point(float distance);

        /* 
            Returns the derivative of the curve at a given distance.
            
            @param distance The distance along the curve.
        */
        Vector derivative(float distance);

        /* 
            Returns the second derivative of the curve at a given distance.
            
            @param distance The distance along the curve.
        */
        Vector secondDerivative(float distance);

        /* 
            Returns the integral of the curve at a given distance.

            @param distance The distance along the curve.
        */
        Vector integral(float distance);


    private:
        Vector startPoint;
        Vector endPoint;
        Vector controlPoint;
};