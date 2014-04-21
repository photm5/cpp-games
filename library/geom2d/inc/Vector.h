#ifndef GUARD_GEOM2D_VECTOR
#define GUARD_GEOM2D_VECTOR

namespace geom2d {

    template<typename T>
    class Vector {
        public:
            Vector<T> (T x, T y);
            ~Vector<T> () = default;

            bool operator== (const Vector<T>& other);

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

}

#endif // GUARD_GEOM2D_VECTOR
