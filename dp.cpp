#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::vector<std::vector<size_t>> OptimizeCombinations(std::vector<long> weights, long max_weight) {
    auto weights_length = weights.size();

    std::vector<std::vector<long>> dp;
    std::vector<std::vector<std::vector<size_t>>> used_weights_table;
    auto initialize_tables = [&]() {
        dp = std::vector<std::vector<long>>(weights_length + 1, std::vector<long>(max_weight + 1, 0));
        used_weights_table = std::vector<std::vector<std::vector<size_t>>>(weights_length + 1, std::vector<std::vector<size_t>>(max_weight + 1, {}));
    };
    initialize_tables();

    std::vector<std::vector<size_t>> used_weights_in_each_carry;
    auto used_weights = std::vector<bool>(weights_length, false);

    while(!std::all_of(used_weights.begin(), used_weights.end(), [](bool x){return x;})) {
        for(size_t i = 0; i < weights_length; ++i) {
            for(long w = 0; w <= max_weight; ++w) {
                if(!used_weights[i] && w >= weights[i]) {
                    if(dp[i][w - weights[i]] + weights[i] > dp[i][w]) {
                        used_weights_table[i + 1][w] = used_weights_table[i][w - weights[i]];
                        used_weights_table[i + 1][w].push_back(i);
                        dp[i + 1][w] = dp[i][w - weights[i]] + weights[i];
                    }
                    else {
                        used_weights_table[i + 1][w] = used_weights_table[i][w];
                        dp[i + 1][w] = dp[i][w];
                    }
                }
                else {
                    used_weights_table[i + 1][w] = used_weights_table[i][w];
                    dp[i + 1][w] = dp[i][w];
                }
            }
        }

        used_weights_in_each_carry.push_back(used_weights_table.at(weights_length).at(max_weight));
        for(auto index : used_weights_table.at(weights_length).at(max_weight)) {
            used_weights[index] = true;
        }

        initialize_tables();
    }

    return used_weights_in_each_carry;
}


int main() {
    int number;
    std::cout << "number of products? ";
    std::cin >> number;

    std::cout << "products?" << std::endl;
    std::vector<double> real_weights;
    auto max_decimal_places = 0;
    for(auto i = 0; i < number; ++i) {
        std::string tmp;
        std::cin >> tmp;

        auto dot_position = (int)tmp.find(".");
        if(dot_position != -1) {
            auto decimal_places = tmp.length() - dot_position - 1;
            if(max_decimal_places < decimal_places) {
                max_decimal_places = decimal_places;
            }
        }

        real_weights.push_back(std::stod(tmp));
    }

    auto weights = std::vector<long>(number);
    transform(real_weights.begin(), real_weights.end(), weights.begin(), [&](double x){return x * std::pow(10, max_decimal_places);});

    double real_max_weight;
    std::cout << "max weight? ";
    std::cin >> real_max_weight;
    long max_weight = real_max_weight * std::pow(10, max_decimal_places);

    auto combinations = OptimizeCombinations(weights, max_weight);
    std::cout << "[";
    for(auto combination : combinations) {
        std::cout << "{";
        for(auto elem : combination) {
            std::cout << elem << ",";
        }
        std::cout << "},";
    }
    std::cout << "]" << std::endl;

    return 0;
}
