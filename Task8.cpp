#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

struct Disjunctor {
    int first;
    int second;

    Disjunctor() {
        Disjunctor(0, 0);
    }

    Disjunctor(int a, int b) {
        if (a > b) 
            swap(a, b);
        this->first = a;
        this->second = b;
    }

    bool isExceptional() {
        if ((this->first + this->second) == 0)
            return true;
        return false;
    }

    bool isEqualTo(Disjunctor *d) {
        if (this->first == d->first && this->second == d->second) return true;
        if (this->first == d->second && this->second == d->first) return true;
        return false;
    }

    int getContraryDirection(Disjunctor *d) {
        if (this->first == -d->first) return 1;
        if (this->first == -d->second) return 2;
        if (this->second == -d->first) return 3;
        if (this->second == -d->second) return 4;
        return 0;
    }

};

bool isDuplicate(Disjunctor *disj, vector<Disjunctor*> &disjList) {
    for (int i = 0; i < disjList.size(); i++) 
        if (disj->isEqualTo(disjList[i])) 
            return true;
    return false;
}

Disjunctor* getResolvent(Disjunctor *a, Disjunctor *b) {
    int contraryDirection = a->getContraryDirection(b);
    if (contraryDirection == 0) 
        return 0;
    int new_first, new_second;
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
    return new Disjunctor(new_first, new_second);  
}


void print(vector<Disjunctor*> &disjList) {
    for (auto item : disjList) 
        cout << "( " << item->first << ", " << item->second << ")" << " ";
    cout << endl;
}

bool isResolvable(int leftIndex, int rightIndex, vector<Disjunctor*> &disjList) {
    if (leftIndex > rightIndex) return true;
    Disjunctor* tmpDisj;
    for (int elderItemIndex = rightIndex; leftIndex <= elderItemIndex; elderItemIndex--) 
        for (int youngerItemIndex = elderItemIndex - 1; 0 <= youngerItemIndex; youngerItemIndex--) {
            tmpDisj = getResolvent(disjList[elderItemIndex], disjList[youngerItemIndex]);
            if (tmpDisj == 0) 
                continue; 
            if (tmpDisj->isExceptional()) 
                return false;
            if (isDuplicate(tmpDisj, disjList)) 
                continue;
            disjList.push_back(tmpDisj);
        }
    print(disjList);
    return isResolvable(rightIndex + 1, disjList.size() - 1, disjList);
}

Disjunctor* getRandDisj(int max_value) {
    
}


int main() {
    srand(time(0));
    vector <Disjunctor*> v;
    v.push_back(new Disjunctor(0, 5));
    v.push_back(new Disjunctor(1, 2));
    v.push_back(new Disjunctor(-2, 0));

    print(v);
    cout << isResolvable(0, 2, v) << endl;
    //print(v);


    return 0;
}


