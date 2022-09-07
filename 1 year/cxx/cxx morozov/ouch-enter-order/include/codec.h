#include <string>

template<class T>
inline void encode(std::vector<unsigned char> &vec, T value) {
    const int sz = sizeof(T);
    for (int i = 0; i < sz; ++i) {
        vec.push_back(static_cast<unsigned char>(value & 0xFF));
        value >>= 8;
    }
}

template<class T>
inline void encode_big(std::vector<unsigned char> &vec, T value) {
    const int sz = sizeof(T);
    for (int i = 0; i < sz; ++i) {
        vec.push_back(static_cast<unsigned char>(value >> (8 * (sz - 1))));
        value <<= 8;
    }
}

inline void encode(std::vector<unsigned char> &vec, const std::string &str, const size_t field_size) {
    size_t i = 0;
    while (i < str.size() && i < field_size) {
        vec.push_back(str[i]);
        ++i;
    }
    while (i < field_size) {
        vec.push_back(0x20);
        ++i;
    }
}

inline unsigned char encode_bit(unsigned char bit_mask, const unsigned int num, const bool value) {
    unsigned char one_bit = 1 << num;
    return ((bit_mask | one_bit) - one_bit) | (value << num);
}

inline long long parse(const std::string &str) {
    long long r = 0;
    for (char i : str) {
        r = r * 10 + i - '0';
    }
    return r;
}