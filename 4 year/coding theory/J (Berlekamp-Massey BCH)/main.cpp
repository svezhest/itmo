#include <iostream>
#include <vector>
#include <functional>
#include <random>
#include <set>
#include <cstdio>
#include <cmath>
#include <numeric>

std::vector<int> minimal_polynomial(const std::set<int> &cycle, int n, const std::vector<int> &field,
                                    const std::vector<int> &filed_reversed) {
    std::vector<int> poly;
    poly.push_back(0);
    for (auto root: cycle) {
        std::vector<int> temp;
        temp.push_back(-1);
        temp.insert(temp.cend(), poly.cbegin(), poly.cend());

        for (int i = 0; i < poly.size(); i++) {
            if (poly[i] != -1) {
                poly[i] = (root + poly[i]) % n;
            }
            if (temp[i] != -1) {
                poly[i] = poly[i] >= 0 ? filed_reversed[field[poly[i]] ^ field[temp[i]]] : temp[i];
            }
        }
        poly.push_back(temp.back());
    }
    return poly;
}

std::vector<bool> generative_polynomial(int n, int d, const std::vector<int> &field, const std::vector<int> &field_reversed) {
    std::vector<bool> res = {true};
    std::set<int> numbers;

    for (int i = 1; i < std::min(d, n); ++i) {
        numbers.emplace_hint(numbers.end(), i);
    }

    std::vector<std::set<int>> cycles;

    auto it = numbers.cbegin();
    while (it != numbers.cend()) {
        int c = *it;
        std::set<int> temp;
        while (!temp.count(c)) {
            temp.insert(c);
            numbers.erase(c);
            c <<= 1;
            c %= n;
        }
        it = numbers.cbegin();
        cycles.emplace_back(std::move(temp));
    }

    for_each(cycles.cbegin(), cycles.cend(), [&](const std::set<int> &cycle) {
        std::vector<int> poly = minimal_polynomial(cycle, n, field, field_reversed);
        std::vector<bool> temp(res.size() + poly.size() - 1, false);
        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < poly.size(); j++) {
                temp[i + j] = temp[i + j] ^ (res[i] & !(poly[j]));
            }
        }
        res = temp;
    });

    return res;
}

std::vector<bool> berlekamp_massey(std::vector<int> &syndrome_poly, const std::vector<bool> &v, int d, int n,
                                   const std::vector<std::vector<int>> &precalculated_multiplication, const std::vector<int> &field,
                                   const std::vector<int> &field_reversed) {
    int L = 0;
    int m = 0;
    std::vector<int> locators = {1};
    std::vector<int> b = {1};
    for (int r = 1; r <= d - 1; r++) {
        int delta = 0; - невязка
        for (int j = 0; j <= L; j++) {
            delta ^= precalculated_multiplication[locators[j]][syndrome_poly[r - 1 - j]];
        }

        if (delta != 0) {
            std::vector<int> temp = locators;
            temp.resize(std::max(temp.size(), r - m + b.size()), 0);
            for (int i = 0; i < b.size(); i++) {
                temp[r - m + i] ^= precalculated_multiplication[delta][b[i]];
            }

            if (2 * L <= r - 1) {
                int delta_reversed = field[(n - field_reversed[delta]) % n];
                b = std::vector<int>();
                transform(locators.cbegin(), locators.cend(), std::back_inserter(b),
                          [&](int x) { return precalculated_multiplication[delta_reversed][x]; });
                L = r - L;
                m = r;
            }

            locators = temp;
        }
    }


    if (L == locators.size() - 1) {
        std::vector<bool> res = v;
        int fixed = 0;
        for (int i = 0; i < n && fixed < L; i++) {
            int temp = locators[0];
            for (int j = 1; j < locators.size(); j++) {
                temp ^= precalculated_multiplication[field[(j * i) % n]][locators[j]];
            }
            if (temp == 0) {
                res[(n - i) % n] = !res[(n - i) % n];
                fixed++;
            }
        }
        return res;
    } else {
        return v;
    }
}

std::vector<int> find_syndrome_poly(int d, int n, const std::vector<bool> &v, const std::vector<int> &field) {
    std::vector<int> res(d - 1);
    for (int j = 0; j < d - 1; j++) {
        int t = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i]) {
                t ^= field[(i * (j + 1)) % n];
            }
        }
        res[j] = t;
    }
    return res;
}

std::vector<bool>
decode(const std::vector<bool> &v, int d, int n, const std::vector<std::vector<int>> &precalculated_multiplication, const std::vector<int> &field,
       const std::vector<int> &field_reversed) {
    std::vector<int> syndrome_poly = find_syndrome_poly(d, n, v, field);

    if (std::count(syndrome_poly.cbegin(), syndrome_poly.cend(), 0) == d - 1) {
        return v;
    }

    return berlekamp_massey(syndrome_poly, v, d, n, precalculated_multiplication, field, field_reversed);
}


std::vector<bool> encode(int n, const std::vector<bool> &v, const std::vector<bool> &gen) {
    std::vector<bool> res(n, false);

    for (int i = 0; i < v.size(); i++) {
        res[gen.size() + i - 1] = v[i];
    }

    std::vector<bool> temp = res;
    for (int i = n; i >= gen.size(); i--) {
        if (temp[i - 1]) {
            for (int j = 1; j <= gen.size(); j++) {
                temp[i - j] = temp[i - j] ^ gen[gen.size() - j];
            }
        }
    }

    for (int i = 0; i < gen.size() - 1; i++) {
        res[i] = temp[i];
    }

    return res;
}

void print_vec(const std::vector<bool> &data) {
    for_each(data.cbegin(), data.cend(), [](auto b) { std::cout << b << ' '; });
    std::cout << '\n';

}

double
simulate(int d, int n, const std::vector<bool> &gen, const std::vector<std::vector<int>> &precalculated_multiplication,
         const std::vector<int> &field, const std::vector<int> &field_reversed, int iterations, int max_errors,
         double noise_level) {
    std::mt19937 get_random((std::random_device()) ());
    std::uniform_int_distribution bool_distribution(0, 1);
    std::uniform_real_distribution<> distribution(0, 1);
    int iteration = 0, errors = 0;
    while (iteration < iterations && errors < max_errors) {
        std::vector<bool> generated(n - ((int) gen.size() - 1));
        generate(generated.begin(), generated.end(), [&]() { return bool_distribution(get_random); });
        std::vector<bool> encoded = encode(n, generated, gen);
        std::vector<bool> corrupted;
        transform(encoded.cbegin(), encoded.cend(), back_inserter(corrupted),
                  [&](bool b) {
                      return (distribution(get_random) > noise_level) ? b : !b;
                  });
        std::vector<bool> decoded = decode(corrupted, d, n, precalculated_multiplication, field, field_reversed);
        for (int i = 0; i < decoded.size(); i++) {
            if (encoded[i] != decoded[i]) {
                errors++;
                break;
            }
        }
        iteration++;
    }
    return ((double) errors) / iteration;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, a, d;
    std::cin >> n >> a >> d;

    int highest_bit = 1 << ((int) ceil(log2(a)) - 1);

    std::vector<int> field;
    std::vector<int> field_reversed;

    field = {1};
    field_reversed = std::vector<int>(n + 1, -1);
    field_reversed[1] = 0;
    for (int i = 1; i < n; i++) {
        int t = field[i - 1] * 2;
        t = t >= highest_bit ? t ^ a : t;
        field.push_back(t);
        field_reversed[field[i]] = i;
    }

    std::vector<std::vector<int>> precalculated_multiplication = {std::vector<int>(n + 1, 0)};
    for (int i = 1; i <= n; i++) {
        precalculated_multiplication.push_back({0});
        for (int j = 1; j <= n; j++) {
            precalculated_multiplication[i].push_back(field[(field_reversed[i] + field_reversed[j]) % n]);
        }
    }

    std::vector<bool> g = generative_polynomial(n, d, field, field_reversed);
    int k = n - ((int) g.size() - 1);

    std::cout << k << '\n';
    print_vec(g);

    std::string line;
    while (std::cin >> line) {
        if (line == "Encode") {
            std::vector<bool> input(k);
            for (int i = 0; i < k; i++) {
                bool t;
                std::cin >> t;
                input[i] = t;
            }
            print_vec(encode(n, input, g));
        } else if (line == "Decode") {
            std::vector<bool> input(n);
            for (int i = 0; i < n; i++) {
                bool t;
                std::cin >> t;
                input[i] = t;
            }
            print_vec(decode(input, d, n, precalculated_multiplication, field, field_reversed));
        } else if (line == "Simulate") {
            double noise_level;
            int iterations, max_errors;
            std::cin >> noise_level >> iterations >> max_errors;
            std::cout << simulate(d, n, g, precalculated_multiplication, field, field_reversed, iterations, max_errors,
                                  noise_level) << '\n';
        }
    }
}
