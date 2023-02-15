#include "some_library.hpp"

class hacker {
  public: 
    std::string name_;
    int value_;
};

inline void SetValue(SomeLibrary::ValueHolder& valueHolder, int value) {
    SomeLibrary::ValueHolder* ptr = &valueHolder;
    hacker* ptr1 = reinterpret_cast<hacker*>(ptr);
    ptr1->value_ = value;
}
