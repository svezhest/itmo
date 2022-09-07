#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <array>
#include "codec.h"

enum class RequestType {
    EnterOrder
};

enum class Side {
    Buy,
    Sell
};

enum class OrdType {
    Market,
    Limit
};

enum class TimeInForce {
    Day,
    IOC
};

enum class Capacity {
    Agency,
    Principal,
    RisklessPrincipal
};

std::vector<unsigned char> create_enter_order_request(
        const std::string &cl_ord_id,
        Side side,
        double volume,
        double price,
        const std::string &symbol,
        OrdType ord_type,
        TimeInForce time_in_force,
        Capacity capacity,
        const std::string &firm,
        const std::string &user
);

#define toChar(x) toChar_##x(x)

inline unsigned char toChar_side(Side side) {
    return side == Side::Buy ? 'B' : 'S';
}

inline unsigned char toChar_time_in_force(TimeInForce timeInForce) {
    switch (timeInForce) {
        case TimeInForce::Day:
            return '0';
        case TimeInForce::IOC:
            return '3';
    }
    return 0;
}

inline unsigned char toChar_capacity(Capacity capacity) {
    switch (capacity) {
        case Capacity::Agency:
            return '1';
        case Capacity::Principal:
            return '2';
        case Capacity::RisklessPrincipal:
            return '7';
    }
    return 0;
}

#define encode_extra(vec, x, order_byte, order_bit) vec[order_byte] = encode_bit(vec[order_byte], order_bit, 1);\
encode<unsigned char>(vec, toChar(x));
