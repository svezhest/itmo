#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cassert>
#include <memory>

using namespace std;

struct Node;

using vector_bool = vector<bool>;

using Graph = vector<map<vector_bool, unique_ptr<Node>>>;

struct Matrix {
    vector<vector_bool> data;
    int rows = 0, cols = 0;

    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        for (int i = 0; i < rows; ++i) {
            data.emplace_back(vector_bool(cols, false));
        }
    }

    vector_bool get_column(int idx) {
        vector_bool res;
        for (auto &row: data) {
            res.push_back(row[idx]);
        }
        return res;
    }

    void gauss() {
        int filled_rows = 0;
//        while rows are not done and there's cols left
        for (int col = 0; col < cols && filled_rows < rows; col++) {
//            find 1 in col and put it in i-th row and make it the only 1 in this row
            for (int i = filled_rows; i < rows; i++) {
                if (data[i][col] == 1) {
                    swap(data[filled_rows], data[i]);
                    for (int j = filled_rows + 1; j < rows; j++) {
                        if (data[j][col] == 1) {
                            xor_assign(j, filled_rows);
                        }
                    }
                    filled_rows++;
                    break;
                }
            }
        }

        filled_rows = 0;
        vector_bool unique_end_col = vector_bool(rows, false);
//        while rows are not done and there's cols left
        for (int col = cols - 1; col >= 0 && filled_rows < rows; col--) {
//            go from the last row and find 1 and xor it with other 1s in the row if necessary
            for (int i = rows - 1; i >= 0; i--) {
                if (!unique_end_col[i] && data[i][col] == 1) {
                    for (int j = rows - 1; j >= 0; j--) {
                        if (i == j) {
                            continue;
                        }
                        if (!unique_end_col[j] && data[j][col] == 1) {
                            xor_assign(j, i);
                        }
                    }
                    unique_end_col[i] = true;
                    filled_rows++;
                    break;
                }
            }
        }
    }

    vector<pair<int, int>> find_spans() {
        vector<pair<int, int>> res;
        for (auto &row: data) {
            int start = 0;
            int end = cols - 1;

            while (row[start] == 0) {
                start++;
                if (start == cols) {
                    break;
                }
            }

            while (row[end] == 0) {
                end--;
                if (end == -1) {
                    break;
                }
            }

            res.emplace_back(start, end - 1);
        }
        return res;
    }

    void xor_assign(int a, int b) {
        for (int i = 0; i < cols; ++i) {
            data[a][i] = data[a][i] ^ data[b][i];
        }
    }

    [[maybe_unused]] void print() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }
};


bool scalar_product(vector_bool &a, vector_bool &b) {
    assert(a.size() == b.size());
    bool res = false;
    for (int i = 0; i < a.size(); ++i)
        res ^= a[i] & b[i];
    return res;
}

vector_bool encode(Matrix &matrix, vector_bool &params) {
    vector_bool ans;
    for (int i = 0; i < matrix.cols; ++i) {
        vector_bool column = matrix.get_column(i);
        ans.push_back(scalar_product(column, params));
    }
    return ans;
}

struct Node {
    bool incoming_edge_bit = false;
    Node *prev_node = nullptr;
    double distance = -1;
    vector<Node *> children = vector<Node *>(2, nullptr);
};

void add_edge(Node *node, Graph &graph, int cur_idx, vector_bool &column, vector_bool &next_decoded,
              const vector_bool &decoded) {
    vector_bool both_decoded = next_decoded;
    for (int i = 0; i < both_decoded.size(); ++i) {
        both_decoded[i] = both_decoded[i] | decoded[i];
    }
    bool edge_bit = scalar_product(both_decoded, column);
    if (graph[cur_idx + 1].count(next_decoded) == 0) {
        graph[cur_idx + 1].emplace(next_decoded, make_unique<Node>());
    }
    node->children[edge_bit] = graph[cur_idx + 1][next_decoded].get();
}

void clear_distances(Graph &graph) {
    for (auto &m: graph) {
        for (auto &p: m) {
            p.second->distance = -numeric_limits<double>::infinity();
        }
    }
    for (auto &p: graph[0]) {
        p.second->distance = 0;
    }
}

double get_dist(bool b, double x) {
    return b == 0 ? x : -x;
}

vector_bool decode(Graph &graph, vector<double> &params) {
    vector_bool res;
    clear_distances(graph);
    for (int i = 0; i < params.size(); ++i) {
        for (auto &el: graph[i]) {
            for (int bit = 0; bit < 2; bit++) {
                Node *node = el.second->children[bit];
                if (node != nullptr) {
                    double new_dist = el.second->distance + get_dist(bit, params[i]);
                    if (new_dist > node->distance) {
                        node->incoming_edge_bit = bit;
                        node->prev_node = el.second.get();
                        node->distance = new_dist;
                    }
                }
            }
        }
    }

    for (auto &el: graph.back()) {
        Node *node = el.second.get();
        while (node != nullptr) {
            res.push_back(node->incoming_edge_bit);
            node = node->prev_node;
        }
    }
    res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

double simulate(Matrix &matrix, Graph &graph, int num_of_iterations, int max_errors, double sigma) {
    mt19937 get_random((random_device()) ());
    normal_distribution<double> distribution{0, pow(sigma, 0.5)};
    int it = 0, errors = 0;
    while (it < num_of_iterations && errors < max_errors) {
        vector_bool generated;
        for (int i = 0; i < matrix.rows; ++i) {
            generated.push_back(get_random() % 2);
        }
        vector_bool encoded = encode(matrix, generated);
        vector<double> noise_levels;
        for (auto value: encoded) {
            noise_levels.push_back((value ? -1 : 1) + distribution(get_random));
        }
        vector_bool decoded = decode(graph, noise_levels);
        for (int i = 0; i < matrix.cols; i++) {
            if (bool(encoded[i]) != bool(decoded[i])) {
                errors++;
                break;
            }
        }
        it++;
    }
    return ((double) errors) / ((double) it);
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int num_rows, num_cols;
    cin >> num_cols >> num_rows;
    Matrix matrix = Matrix(num_rows, num_cols);

    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            bool value;
            cin >> value;
            if (value == 1) {
                matrix.data[i][j] = true;
            }
        }
    }

    Matrix m = matrix;
    m.gauss();

    vector<pair<int, int>> spans = m.find_spans();


    auto graph = Graph();
    int lines_count = 0;
    auto init = vector_bool(m.rows, false);
    vector_bool lines = init;
    graph.emplace_back();
    graph[0].emplace(init, make_unique<Node>());
    for (int i = 0; i < m.cols; ++i) {
        vector_bool column = m.get_column(i);
        graph.emplace_back();
        bool new_line = lines_count < m.rows && spans[lines_count].first == i;
        for (int row = 0; row <= lines_count; ++row) {
            lines[row] = false;
            if ((spans[row].first <= i) && (spans[row].second >= i)) {
                lines[row] = true;
            }
        }
        for (auto &el: graph[i]) {
            vector_bool next_decoded = el.first;
            for (int row = 0; row < m.rows; ++row) {
                next_decoded[row] = next_decoded[row] & lines[row];
            }
            add_edge(el.second.get(), graph, i, column, next_decoded, el.first);
            if (new_line) {
                next_decoded[lines_count] = true;
                add_edge(el.second.get(), graph, i, column, next_decoded, el.first);
            }
        }
        if (new_line) {
            lines_count++;
        }
    }

    for (auto &level_size: graph) {
        cout << level_size.size() << ' ';
    }
    cout << '\n';

    string line;
    while (cin >> line) {
        if ("Encode" == line) {
            vector_bool inf_vector;
            for (int i = 0; i < matrix.rows; ++i) {
                bool value;
                cin >> value;
                inf_vector.push_back(value);
            }
            vector_bool encoded = encode(matrix, inf_vector);
            for (auto value: encoded) {
                cout << bool(value) << ' ';
            }
        } else if ("Decode" == line) {
            vector<double> noisy_vector;
            for (int i = 0; i < matrix.cols; ++i) {
                double value;
                cin >> value;
                noisy_vector.push_back(value);
            }
            vector_bool decoded = decode(graph, noisy_vector);
            for (auto value: decoded) {
                cout << bool(value) << ' ';
            }
        } else if ("Simulate" == line) {
            double noise_level;
            int num_of_iterations, max_errors;
            cin >> noise_level >> num_of_iterations >> max_errors;
            cout << simulate(matrix, graph, num_of_iterations, max_errors,
                             (pow(10, -noise_level / 10) * num_cols / num_rows / 2));
        }
        cout << '\n';
    }
    return 0;
}