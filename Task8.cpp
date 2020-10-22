#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

unsigned long long counter;

void C(unsigned long long a = 1) {
    counter += a;
}

inline void swap(int &a, int &b) {
    C(3);
    int tmp = a;
    a = b;
    b = tmp;
}

struct Disjunctor {
    int first;
    int second;

    Disjunctor() {
        Disjunctor(0, 0);
    }

    Disjunctor(int a, int b) {
        C(5);
        if (a == b) 
            a = 0;
        if (a > b) 
            swap(a, b);
        this->first = a;
        this->second = b;
    }

    bool isExceptional() {
        C(2);
        if ((this->first + this->second) == 0)
            return true;
        return false;
    }

    bool isEqualTo(Disjunctor *d) {
        C(2);
        if (this->first == d->first && this->second == d->second) return true;
        C(2);
        if (this->first == d->second && this->second == d->first) return true;
        return false;
    }

    int getContraryDirection(Disjunctor *d) {
        C(2);
        if (this->first == -d->first) return 1;
        C(2);
        if (this->first == -d->second) return 2;
        C(2);
        if (this->second == -d->first) return 3;
        C(2);
        if (this->second == -d->second) return 4;
        return 0;
    }

};

bool isDuplicate(Disjunctor *disj, vector<Disjunctor*> &disjList) {
    for (int i = 0; i < disjList.size(); i++) {
        C();
        if (disj->isEqualTo(disjList[i])) 
            return true;
    }
    return false;
}

Disjunctor* getResolvent(Disjunctor *a, Disjunctor *b) {
    C();
    int contraryDirection = a->getContraryDirection(b);
    C();
    if (contraryDirection == 0) 
        return 0;
    C(2);
    int new_first, new_second;
    C(6);
    switch (contraryDirection) {
        case 1: {
            new_first = a->second;
            new_second = b->second;
            break;
        }
        case 2: {
            new_first = a->second;
            new_second = b->first;
            break;
        }
        case 3: {
            new_first = a->first;
            new_second = b->second;
            break;
        }
        case 4: {
            new_first = a->first;
            new_second = b->first;
            break;
        }
        default: {
            perror("ERROR incorrect contrary direction!!!");
            exit(-1);
        }
    }
    C();
    return new Disjunctor(new_first, new_second);  
}


void print(vector<Disjunctor*> &disjList) {
    cout << disjList.size() << endl;
    for (auto item : disjList) 
        cout << item->first << " " << item->second << endl;
}

bool isResolvable(int leftIndex, int rightIndex, vector<Disjunctor*> &disjList) {
    C();
    if (leftIndex > rightIndex) return true;
    C();
    Disjunctor* tmpDisj;
    for (int elderItemIndex = rightIndex; leftIndex <= elderItemIndex; elderItemIndex--) 
        for (int youngerItemIndex = elderItemIndex - 1; 0 <= youngerItemIndex; youngerItemIndex--) {
            C();
            tmpDisj = getResolvent(disjList[elderItemIndex], disjList[youngerItemIndex]);
            C();
            if (tmpDisj == 0) {
                delete tmpDisj;
                continue; 
            }
            C();
            if (tmpDisj->isExceptional()) 
                return false;
            C();
            if (isDuplicate(tmpDisj, disjList)) { 
                delete tmpDisj;
                continue;
            }
            C();
            disjList.push_back(tmpDisj);
        }
    //print(disjList);
    return isResolvable(rightIndex + 1, disjList.size() - 1, disjList);
}

Disjunctor* getRandDisj(int maxValue) {
    int a, b;
    do {
        a = (rand() % (2 * maxValue) + 1) - maxValue; 
        b = (rand() % (2 * maxValue) + 1) - maxValue; 
    } while ((a + b) == 0);
    return new Disjunctor(a, b);
}

void addDisj(int a, int b, vector<Disjunctor*> &disjList) {
    disjList.push_back(new Disjunctor(a, b));
}

void addNUniqDisjToList(vector<Disjunctor*> &disjList, int disjCount, int maxValue) {
    for (int i = 0; i < disjCount; i++) {
        Disjunctor* tmp = 0;
        do {
            tmp = getRandDisj(maxValue);
        } while (isDuplicate(tmp, disjList) || tmp->isExceptional());
        disjList.push_back(tmp);
    }
}

unsigned long long doTest(int disjCount, int maxLiteralIndex) {
    counter = 0;
    vector <Disjunctor*> v;
    addNUniqDisjToList(v, disjCount, maxLiteralIndex);
    print(v);
    cout << isResolvable(0, disjCount - 1, v) << endl;
    return counter;
}


int main() {
    srand(time(0));


    cout << doTest(10000, 10000) << endl;

    return 0;
}


