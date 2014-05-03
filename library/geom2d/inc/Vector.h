#ifndef GUARD_GEOM2D_VECTOR
#define GUARD_GEOM2D_VECTOR

#include <ostream>

namespace geom2d {

    template<typename T>
    class Vector {
        public:
            Vector<T> (T x, T y);
            ~Vector<T> () = default;

            bool operator== (const Vector<T>& other);
            bool operator!= (const Vector<T>& other);

            Vector<T> operator+ (const Vector<T>& other);
            void operator+= (const Vector<T>& other);

            Vector<T> operator- (const Vector<T>& other);
            void operator-= (const Vector<T>& other);

            Vector<T> operator* (const Vector<T>& other);
            void operator*= (const Vector<T>& other);

            T get_x () const {
                return x;
            };
            T get_y () const {
                return y;
            };

        private:
            T x;
            T y;
    };

    template<typename T>
    Vector<T>::Vector (T x, T y) {
        this->x = x;
        this->y = y;
    }

    template<typename T>
    bool Vector<T>::operator== (const Vector<T>& other) {
        return x == other.get_x() && y == other.get_y();
    }

    template<typename T>
    bool Vector<T>::operator!= (const Vector<T>& other) {
        return !(*this == other);
    }

    template<typename T>
    Vector<T> Vector<T>::operator+ (const Vector<T>& other) {
        return Vector<T> (get_x() + other.get_x(), get_y() + other.get_y());
    }

    template<typename T>
    void Vector<T>::operator+= (const Vector<T>& other) {
        x += other.get_x();
        y += other.get_y();
    }

    template<typename T>
    Vector<T> Vector<T>::operator- (const Vector<T>& other) {
        return Vector<T> (get_x() - other.get_x(), get_y() - other.get_y());
    }

    template<typename T>
    void Vector<T>::operator-= (const Vector<T>& other) {
        x -= other.get_x();
        y -= other.get_y();
    }

    template<typename T>
    Vector<T> Vector<T>::operator* (const Vector<T>& other) {
        return Vector<T> (get_x() * other.get_x(), get_y() * other.get_y());
    }

    template<typename T>
    void Vector<T>::operator*= (const Vector<T>& other) {
        x *= other.get_x();
        y *= other.get_y();
    }

    template<typename T>
    std::ostream& operator<< (std::ostream& stream, const Vector<T>& vector) {
        stream << "(" << vector.get_x() << "," << vector.get_y() << ")";
        return stream;
    }

}

#endif // GUARD_GEOM2D_VECTOR
