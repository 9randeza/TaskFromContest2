#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

// Функция для генерации переменной с повторяющимися значениями
vector<int> generateVariable(int k, int size) {
    vector<int> variable;
    for (int i = 0; i < size; ++i) {
        variable.push_back(i % k);
    }
    return variable;
}

// Функция для генерации всех возможных комбинаций
vector<vector<vector<int>>> generateAllCombinations(const vector<int>& var1, const vector<vector<int>>& generatedFunctions) {
    vector<vector<vector<int>>> combinations;

    // Общее количество источников
    vector<vector<int>> allSources = {var1};
    allSources.insert(allSources.end(), generatedFunctions.begin(), generatedFunctions.end());

    int totalSources = allSources.size();

    // Генерация всех комбинаций (каждая позиция может брать значение из любого источника)
    for (int i = 0; i < totalSources; ++i) {
        for (int j = 0; j < totalSources; ++j) {
            vector<vector<int>> combination = {allSources[i], allSources[j]};
            combinations.push_back(combination);
        }
    }

    return combinations;
}

// Функция для вычисления новых функций
vector<int> f(const vector<int>& func, const vector<int>& x1_vals, const vector<int>& x2_vals, int k, set<vector<int>>& uniqueFunctions) {
    vector<int> ch;

    for (int i = 0; i < x1_vals.size(); ++i) {
        int x1 = x1_vals[i];
        int x2 = x2_vals[i];

        // Вычисление индекса для k-значной логики
        int index = x1 * k + x2;
        ch.push_back(func[index]);
    }

    if (uniqueFunctions.find(ch) == uniqueFunctions.end()) {
        uniqueFunctions.insert(ch);
        return ch;
    } else {
        return {};
    }
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    if (!outputFile.is_open()) {
        cerr << "Error: Could not open output file." << endl;
        return 1;
    }

    int k; // Основа логики
    int numVariables; // Количество переменных
    inputFile >> k >> numVariables;

    // Чтение строки значений функции
    string funcStr;
    inputFile >> funcStr;

    // Преобразование строки в вектор значений функции
    vector<int> initial_func;
    for (char c : funcStr) {
        initial_func.push_back(c - '0');
    }

    if (initial_func.size() != pow(k, numVariables)) {
        cerr << "Error: Function values size does not match the number of variables for k-ary logic." << endl;
        return 1;
    }

    // Генерация изначальных векторов переменных
    int numCombinations = pow(k, numVariables - 1);
    vector<int> x1 = generateVariable(k, numCombinations);

    // Хранилище всех уникальных функций
    set<vector<int>> uniqueFunctions;

    // Вектор для хранения всех порождённых функций
    vector<vector<int>> generatedFunctions;

    // Первая итерация: генерируем комбинации только для x1 и x2
    vector<vector<vector<int>>> combinations = generateAllCombinations(x1, {});

    // Начинаем цикл вычисления функций
    bool changed = true;
    while (changed) {
        changed = false;
        vector<vector<int>> newFunctions; // Для временного хранения новых уникальных функций

        // Обработка каждой комбинации
        for (const auto& combination : combinations) {
            vector<int> ch = f(initial_func, combination[0], combination[1], k, uniqueFunctions);
            if (!ch.empty()) {
                newFunctions.push_back(ch);
                changed = true;
            }
        }

        // Добавляем новые функции к порождённым
        for (const auto& func : newFunctions) {
            generatedFunctions.push_back(func);
        }

        // Перегенерация комбинаций с учётом новых функций
        combinations = generateAllCombinations(x1, generatedFunctions);
    }

    // Итоговый вывод всех уникальных функций
    for (const auto& uf : uniqueFunctions) {
        outputFile << k << " " << 1 << " ";
        for (int val : uf) {
            outputFile << val;
        }
        outputFile  << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
