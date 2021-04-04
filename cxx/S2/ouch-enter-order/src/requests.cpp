#include "requests.h"

#include <string>

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
) {
    std::vector<unsigned char> res;
    encode<unsigned char>(res, 'O');
    encode(res, cl_ord_id, 14);
    encode<unsigned char>(res, toChar(side));
    encode_big<uint32_t>(res, static_cast<uint32_t> (volume));
    encode_big<uint32_t>(res, static_cast<uint32_t> (parse(symbol)));
    if (ord_type == OrdType::Market) {
        price = 0x7FFFFFFF;
    } else {
        price *= 10000;
    }
    encode_big<uint32_t>(res, static_cast<uint32_t> (price));
    encode(res, firm, 4);
    encode(res, user, 6);
    encode(res, {0, 0, 0, 0}, 4);

    encode_extra(res, time_in_force, 38, 0);
    encode_extra(res, capacity, 38, 3);
    return res;
}