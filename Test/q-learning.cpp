#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <limits>

int random_action(const std::vector<double>& V) {
    std::vector<int> index_list;
    for (size_t index = 0; index < V.size(); ++index) {
        if (V[index] >= 0) {
            index_list.push_back(index);
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, index_list.size() - 1);
    return index_list[distrib(gen)];
}

std::vector<std::vector<double>> reward_setting(int state_num, int action_num) {
    std::vector<std::vector<double>> R(state_num, std::vector<double>(action_num, -1));
    R[0][4] = 0;
    R[1][3] = 0;
    R[1][5] = 100;
    R[2][3] = 0;
    R[3][1] = 0;
    R[3][2] = 0;
    R[3][4] = 0;
    R[4][0] = 0;
    R[4][3] = 0;
    R[4][5] = 100;
    R[5][1] = 0;
    R[5][4] = 0;
    R[5][5] = 100;
    return R;
}

int main() {
    int action_num = 6;
    int state_num = 6;
    double gamma = 0.8;
    int epoch_number = 300;
    int condition_stop = 5;

    std::vector<std::vector<double>> Q(state_num, std::vector<double>(action_num, 0));
    std::vector<std::vector<double>> R = reward_setting(state_num, action_num);

    for (int epoch = 0; epoch < epoch_number; ++epoch) {
        for (int s = 0; s < state_num; ++s) {
            bool loop = true;
            while (loop) {
                int a = random_action(R[s]);
                double q_max = *std::max_element(Q[a].begin(), Q[a].end());
                Q[s][a] = R[s][a] + gamma * q_max;
                s = a;
                if (s == condition_stop) {
                    loop = false;
                }
            }
        }
    }

    for (auto& row : Q) {
        for (double& value : row) {
            value = static_cast<int>(value / 5);
        }
    }

    for (const auto& row : Q) {
        for (const auto& value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}