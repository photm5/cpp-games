#ifndef GUARD_GEOM2D_VECTOR
#define GUARD_GEOM2D_VECTOR

namespace geom2d {

    template<typename T>
    class Vector {
        public:
            Vector<T> (T x, T y);
            ~Vector<T> () = default;

            bool operator== (Vector<T>& other);

            T get_x () {
                return x;
            };
            T get_y () {
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
    bool Vector<T>::operator== (Vector<T>& other) {
        return x == other.x && y == other.y;
    }

}

#endif // GUARD_GEOM2D_VECTOR
