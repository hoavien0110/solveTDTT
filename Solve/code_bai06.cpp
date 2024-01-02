#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

struct Tuple {
    int value;
    int sequenceIndex;
    int elementIndex;
};

// Struct để so sánh các Tuple trong hàng đợi ưu tiên
struct TupleCompare {
    bool operator()(const Tuple& lhs, const Tuple& rhs) {
        return lhs.value > rhs.value;
    }
};

// Hàm gộp các dãy số và trả về dãy số đã gộp và được sắp xếp theo thứ tự tăng dần
std::vector<int> mergeSequences(const std::vector<std::vector<int>>& sequences) {
    std::priority_queue<Tuple, std::vector<Tuple>, TupleCompare> pq;

    for (int i = 0; i < sequences.size(); i++) {
        pq.push({sequences[i][0], i, 0});
    }

    std::vector<int> mergedSequence;

    while (!pq.empty()) {
        Tuple tuple = pq.top();
        pq.pop();
        mergedSequence.push_back(tuple.value);

        if (tuple.elementIndex + 1 < sequences[tuple.sequenceIndex].size()) {
            pq.push({sequences[tuple.sequenceIndex][tuple.elementIndex + 1], tuple.sequenceIndex, tuple.elementIndex + 1});
        }
    }

    return mergedSequence;
}

int main() {
    int k;
    std::cin >> k;

    std::vector<std::vector<int>> sequences(k, std::vector<int>());

    std::cin.ignore();

    for (int i = 0; i < k; i++) {
        std::string s;
        std::getline(std::cin, s);

        std::stringstream ss(s);
        int x;
        while (ss >> x) {
            sequences[i].push_back(x);
        }
    }

    std::vector<int> mergedSequence = mergeSequences(sequences);

    for (int i = 0; i < mergedSequence.size(); i++) {
        std::cout << mergedSequence[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}