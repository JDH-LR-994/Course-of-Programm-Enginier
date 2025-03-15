#include <ostream>
#include <utility>

template <typename T>
class Box {
    T value;
    public:
    explicit Box(const T &value)
        : value(value) {
    }

    Box(const Box &other)
        : value(other.value) {
    }

    Box(Box &&other) noexcept
        : value(std::move(other.value)) {
    }

    Box & operator=(const Box &other) {
        if (this == &other)
            return *this;
        value = other.value;
        return *this;
    }

    Box & operator=(Box &&other) noexcept {
        if (this == &other)
            return *this;
        value = std::move(other.value);
        return *this;
    }
};


