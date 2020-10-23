#include <iostream>
#include <vector>
#include <set>
#include <ctime>
#include <math.h>
using namespace std;

unsigned long long counter;
unsigned long long LOG_N;

inline void C(int i) {
    counter += i;
}

inline void swap(int &a, int &b) {
    C(3);
    int tmp = a;
    a = b;
    b = tmp;
}

pair<int, int> makeDisjPair(int a, int b) {
    C(1);
    if (a == b) { 
        C(1);
        a = 0;
    }
    C(1);
    if (a > b) 
        swap(a, b);
    C(1);
    return make_pair(a, b);
}

bool isExceptional(pair<int, int> &disjPair) {
    C(2);
    if ((disjPair.first + disjPair.second) == 0)
        return true;
    return false;
}

int getCountraryDirection(pair<int, int> &disjPairA, pair<int, int> &disjPairB) {
    C(1);
    if (disjPairA.first == -disjPairB.first) return 1;
    C(1);
    if (disjPairA.first == -disjPairB.second) return 2;
    C(1);
    if (disjPairA.second == -disjPairB.first) return 3;
    C(1);
    if (disjPairA.second == -disjPairB.second) return 4;
    return 0;
}

bool isDuplicate(pair<int, int> &disjPair, set<pair<int, int>> &disjSet) {
    C(LOG_N + 1);
    if (disjSet.count(disjPair) > 0)
        return true;
    return false;
}

pair<int, int> getResolventDisjPair(int countraryDirection, pair<int, int> &disjPairA, pair<int, int> &disjPairB) {
    C(8);
    int new_first, new_second;
    switch (countraryDirection) {
        case 1: {
            new_first = disjPairA.second;
            new_second = disjPairB.second;
            break;
        }
        case 2: {
            new_first = disjPairA.second;
            new_second = disjPairB.first;
            break;
        }
        case 3: {
            new_first = disjPairA.first;
            new_second = disjPairB.second;
            break;
        }
        case 4: {
            new_first = disjPairA.first;
            new_second = disjPairB.first;
            break;
        }
        default: {
            perror("ERROR incorrect contrary direction!!!");
            exit(-1);
        }
    }
    return makeDisjPair(new_first, new_second);
}

void addDisjPair(pair<int, int> &disjPair, vector<pair<int, int>> &disjList, set<pair<int, int>> &disjSet) {
    C(LOG_N);
    disjList.push_back(disjPair);
    C(LOG_N);
    disjSet.insert(disjPair);
    //cout << disjList.size() << " " << counter << endl;
}

void print(vector<pair<int, int>> &disjList) {
    for (auto item : disjList) 
        cout << item.first << " " << item.second << endl;
}


void printInLine(vector<pair<int, int>> &disjList) {
    for (auto item : disjList) 
        cout << "(" << item.first << " " << item.second << ") ";
    cout << endl;
}

void print(set<pair<int, int>> &disjSet) {
    for (auto item : disjSet) 
        cout << item.first << " " << item.second << endl;
}

bool isResolvable(int leftIndex, int rightIndex, vector<pair<int, int>> &disjList, set<pair<int, int>> &disjSet) {
    C(1);
    if (leftIndex > rightIndex) return true;
    C(2);
    int countraryDirection;
    pair<int, int> resolventDisjPair;

    for (int elderItemIndex = rightIndex; leftIndex <= elderItemIndex; elderItemIndex--) 
        for (int youngerItemIndex = elderItemIndex - 1; 0 <= youngerItemIndex; youngerItemIndex--) {
            C(2);
            if ((countraryDirection = getCountraryDirection(disjList[elderItemIndex], disjList[youngerItemIndex])) == 0)
                continue;
            C(1);
            resolventDisjPair = getResolventDisjPair(countraryDirection, disjList[elderItemIndex], disjList[youngerItemIndex]);
            C(1);
            if (isExceptional(resolventDisjPair)) 
                return false;
            C(1);
            if (isDuplicate(resolventDisjPair, disjSet)) 
                continue;
            addDisjPair(resolventDisjPair, disjList, disjSet);
        }
    //printInLine(disjList);
    return isResolvable(rightIndex + 1, disjList.size() - 1, disjList, disjSet);
}


pair<int, int> getRandDisj(int maxValue) {
    int a, b;
    do {
        a = (rand() % (2 * maxValue) + 1) - maxValue; 
        b = (rand() % (2 * maxValue) + 1) - maxValue; 
    } while ((a + b) == 0);
    return makeDisjPair(a, b);
}

void addNUniqDisjToList(vector<pair<int, int>> &disjList, set<pair<int, int>> &disjSet, int disjCount, int maxValue) {
    for (int i = 0; i < disjCount; i++) {
        pair <int, int> tmpDisjPair;
        do {
            tmpDisjPair = getRandDisj(maxValue);
        } while (isDuplicate(tmpDisjPair, disjSet));
        addDisjPair(tmpDisjPair, disjList, disjSet);
    }
}

int doTest(int n) {
    LOG_N = (int)floor(log2(n));
    vector <pair<int, int>> v;
    set <pair<int, int>> s;
    addNUniqDisjToList(v, s, n, n);
    counter = 0;
    isResolvable(0, n-1, v, s);
    return counter;
}

long double getStats(int n, int iterations) {
    unsigned long long s = 0;
    for (int i = 1; i < iterations; i++) {
        s += doTest(n);
    }
    return s/iterations; 

}

int main() {
    srand(time(0));
    for (int i = 650; i <= 1000; i+=25) {
        cout << i << ";" << (int)floor(getStats(i, 100)) << endl;
    }


    return 0;
}
