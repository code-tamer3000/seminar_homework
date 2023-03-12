template <class T>
void reset_values(const std::vector<T>& hold, const std::vector<T*>& place_to_insert) {
    for (size_t i = 0; i < hold.size(); i++) {
        *place_to_insert[i] = hold[i];
    }
}

template <class T>
void TransformIf(T* begin, T* end, bool (*p)(const T&), void (*f)(T&)) {
    std::vector<T> hold;
    std::vector<T*> place_to_insert;
    bool success_copy = true;
    for (T* curr = begin; curr != end; curr++) {

        bool success_p = false;

        try {
            success_p = p(*curr);
        } catch(...) {
            if (success_copy) reset_values(hold, place_to_insert);
            throw;
        }
        
        if (success_p) {

            try {
                hold.push_back(*curr);
                place_to_insert.push_back(curr);
            } catch (...) {
                success_copy = false;
            }

            try {
                f(*curr);
            } catch (...) {
                if (success_copy) reset_values(hold, place_to_insert);
                throw;
            }
        }
    }
}
