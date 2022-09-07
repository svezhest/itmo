#include <cstddef>
#include <random>

#pragma once

static int get_rand() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  return gen();
}

struct in_place_t{};
in_place_t in_place_tag;

nullptr_t not_in_place_tag;