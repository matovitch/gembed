#ifndef __EUCLIDIAN_VECTOR_H__
#define __EUCLIDIAN_VECTOR_H__

#include <array>

#include <iostream>

template <typename T, unsigned N>
struct EuclidianVector
{
    const EuclidianVector& operator+= (const EuclidianVector& rhs)
    {
        for (unsigned i = 0; i < N; i++)
        {
            this->_coordinates[i] += rhs._coordinates[i];
        }

        return *this; 
    }

    const EuclidianVector& operator-= (const EuclidianVector& rhs)
    {
        for (unsigned i = 0; i < N; i++)
        {
            this->_coordinates[i] -= rhs._coordinates[i];
        }

        return *this; 
    }

    const EuclidianVector& operator*= (const T rhs)
    {
        for (unsigned i = 0; i < N; i++)
        {
            this->_coordinates[i] *= rhs;
        }

        return *this;
    }

    const EuclidianVector& operator/= (const T rhs)
    {
        for (unsigned i = 0; i < N; i++)
        {
            this->_coordinates[i] /= rhs;
        }

        return *this;
    }

    const EuclidianVector& setAsOrigin()
    {
        for (unsigned i = 0; i < N; i++)
        {
            this->_coordinates[i] = 0.0;
        }

        return *this;
    }

    T norm() const
    {
        T norm = 0;

        for (unsigned i = 0; i < N; i++)
        {
            const T coordinate = this->_coordinates[i];
            norm += coordinate *
                    coordinate;
        }

        return norm;
    }

    T& dot(const EuclidianVector& rhs) const
    {
        T dot = 0;

        for (unsigned i = 0; i < N; i++)
        {
            dot += this->_coordinates[i] * rhs._coordinates[i];
        }

        return dot;
    }

    std::array<T, N> _coordinates;
};

template <typename T, unsigned N>
EuclidianVector<T, N> operator+ (      EuclidianVector<T, N>  lhs,
                                 const EuclidianVector<T, N>& rhs)
{
    return lhs += rhs;
}

template <typename T, unsigned N>
EuclidianVector<T, N> operator- (      EuclidianVector<T, N>  lhs,
                                 const EuclidianVector<T, N>& rhs)
{
    return lhs -= rhs;
}

template <typename T, unsigned N>
EuclidianVector<T, N> operator* (const T& lhs,
                                 EuclidianVector<T, N>  rhs)
{
    return rhs *= lhs;
}

template <typename T, unsigned N>
EuclidianVector<T, N> operator/ (EuclidianVector<T, N>  lhs,
                                 const T& rhs)
{
    return lhs /= rhs;
}

template <typename T, unsigned N>
T dot(const EuclidianVector<T, N>& lhs,
      const EuclidianVector<T, N>& rhs)
{
    return lhs.dot(rhs);
}

template <typename T, unsigned N>
T distance(const EuclidianVector<T, N>& lhs,
           const EuclidianVector<T, N>& rhs)
{
    T distance = 0.0;

    for (unsigned i = 0; i < N; i++)
    {
        const T delta = lhs._coordinates[i] - rhs._coordinates[i];
        distance += delta * delta;
    }

    return distance;
}

#endif