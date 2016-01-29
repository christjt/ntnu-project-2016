#ifndef ROBOROBO2_VECTOR2_H
#define ROBOROBO2_VECTOR2_H

template <class T>
struct Vector2
{
    public:
        T x;
        T y;

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
        return Vector2<T>{x=this->x - other.x, y=this->y - other.y};
    }

    T length()
    {
        return sqrt(x*x + y*y);
    }

};


#endif //ROBOROBO2_VECTOR2_H
