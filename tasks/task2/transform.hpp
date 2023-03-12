template <class T>
void reset_values(T* begin, const std::vector<T>& hold, const std::vector<size_t>& hold_index) {
    T* undo = begin;
    for (int i = 0; i < hold_index[0]; undo++, i++) {}
    *undo = hold[0];
    for (size_t i = 1; i < hold.size(); i++) {
        for (size_t i = 0; i < hold_index[i] - hold_index[i - 1]; undo++, i++) {}
        *undo = hold[i];
    }
}

template <class T>
void TransformIf(T* begin, T* end, bool (*p)(const T&), void (*f)(T&)) {
    std::vector<T> hold;
    std::vector<size_t> hold_index;
    bool success_copy = true;
    for (T* curr = begin; curr != end; curr++) {

        bool success_p = false;

        try {
            success_p = p(*curr);
        } catch(...) {
            if (success_copy) reset_values(begin, hold, hold_index);
            throw;
        }
        
        if (success_p) {

            try {
                hold.push_back(*curr);
                hold_index.push_back(curr - begin);
            } catch (...) {
                success_copy = false;
            }

            try {
                f(*curr);
            } catch (...) {
                if (success_copy) reset_values(begin, hold, hold_index);
                throw;
            }
        }
    }
}
