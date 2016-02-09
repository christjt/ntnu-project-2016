#ifndef ROBOROBO2_VECTOR2_H
#define ROBOROBO2_VECTOR2_H

#include <math.h>
#include <ostream>
template <class T>
struct Vector2
{
    public:
        T x;
        T y;

    Vector2<T>(T _x, T _y)
    {
        x = _x;
        y = _y;
    }

    Vector2<T>()
    {
        //Do nothing
    }

    Vector2<T> operator+(const Vector2<T>& other)
    {
        return Vector2<T>{x=this->x + other.x, y=this->y + other.y};
    }

    void operator+=(const Vector2<T>& other)
    {
        this->x += other.x;
        this->y += other.y;
    }

    void operator-=(const Vector2<T>& other)
    {
        this->x -= other.x;
        this->y -= other.y;
    }

    Vector2<T> operator-(const Vector2<T>& other)
    {
        return Vector2<T>(this->x - other.x, this->y - other.y);
    }

    T length()
    {
        return sqrt(x*x + y*y);
    }

    friend std::ostream& operator<<(std::ostream &strm, const Vector2<double> vec);


};


#endif //ROBOROBO2_VECTOR2_H
