template <class T>
void reset_values(T* begin, std::vector<T>& hold, std::vector<size_t>& hold_index) {
    for (size_t i = 0; i < hold.size(); i++) {
        T* undo = begin + hold_index[i];
        *undo = hold[i];
    }
}

template <class T>
void TransformIf(T* begin, T* end, bool (*p)(const T&), void (*f)(T&)) {
    std::vector<T> hold;
    std::vector<size_t> hold_index;
    bool succses_copy = true;
    for (T* curr = begin; curr != end; curr++) {

        bool succses_p = false;

        try {
            succses_p = p(*curr);
        } catch(...) {
            if (succses_copy) reset_values(begin, hold, hold_index);
            throw;
        }
        
        if (succses_p) {

            try {
                hold.push_back(*curr);
                hold_index.push_back(curr - begin);
            } catch (...) {
                succses_copy = false;
            }

            try {
                f(*curr);
            } catch (...) {
                if (succses_copy) reset_values(begin, hold, hold_index);
                throw;
            }
        }
    }
}
