#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>
#include <ostream>

struct Vector
{
    Vector() :
                    x(-1), y(-1), z(-1)
    {
    }
    Vector(int x, int y, int z) :
                    x(x), y(y), z(z)
    {
    }
    Vector(const Vector& vector) :
                    x(vector.x), y(vector.y), z(vector.z)
    {
    }

    int x;
    int y;
    int z;

    const unsigned int getModulus() const
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }


    friend std::ostream& operator<<(std::ostream& stream, Vector& vector)
    {
    	stream << "x: "<<vector.x <<  "\ty: "<<vector.y <<  "\tz: "<<vector.z <<  std::endl ;
    	return stream;
    }

};

typedef Vector Position;

#endif /* VECTOR_H_ */
