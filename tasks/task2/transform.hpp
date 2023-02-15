template <class T>
void TransformIf(T* begin, T* end, bool (*p)(const T&), void (*f)(T&)) {
    T* curr = begin;
    std::vector<T> hold;
    while (curr++ != end) {
        bool succses_p = false;
        bool succses_copy = true;

        try {
            hold.push_back(*curr);
        } catch (...) {
            succses_copy = false;
        }

        try {
            succses_p = p(*curr);
        } catch(...) {
            if (!succses_copy) throw;
            for (int i = 0; i < hold.size(); i++) {
                T* undo = begin + i;
                *undo = hold[i];
            }
            throw;
        }

        if (succses_p) {
            try {
                f(*curr);
            } catch (...) {
                if (!succses_copy) throw;
                for (int i = 0; i < hold.size(); i++) {
                    T* undo = begin + i;
                    *undo = hold[i];
                }
                throw;
            }
        }

    }
}
