#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct number {
    int value, index;
};

void readData (vector <int> &numbers, int &sum) {
    int number, n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> number;
        numbers.push_back(number);
    }
    cin >> sum;
}

void getSumTermsIndexesMethod1(vector <int> numbers, int sum) {
    for(int i = 0; i < numbers.size(); i++) {
        for(int j = i + 1; j < numbers.size(); j++) {
            if(numbers[i] + numbers[j] == sum) {
                cout << "Method1 - O(n^2)" << '\n';
                cout << i << " " << j << '\n';
                return;
            }
        }
    }
    cout << "Numbers not found" << '\n';
}

int cmpFunction(number number1, number number2) {
    return number1.value < number2.value;
}

int binSearchIndexesPair (int leftIndex, int rightIndex, int sumRest, vector <number> dataNumbers) {
    int middleIndex = (leftIndex + rightIndex) / 2;
    //cout <<sumRest << " " << dataNumbers[middleIndex].value << " " << leftIndex << " " << rightIndex << " " << middleIndex << '\n';
    if(leftIndex > rightIndex) {
        return -1;
    }
    if(sumRest < dataNumbers[middleIndex].value) {
        return binSearchIndexesPair(leftIndex, middleIndex - 1, sumRest, dataNumbers);
    }
    else if(sumRest > dataNumbers[middleIndex].value) {
        return binSearchIndexesPair(middleIndex + 1, rightIndex, sumRest, dataNumbers);
    }
    else {
        return middleIndex;
    }
}

void getSumTermsIndexesMethod2(vector <int> numbers, int sum) {
    vector <number> dataNumbers;
    for(int i = 0 ; i < numbers.size(); i++) {
        number nr;
        nr.value = numbers[i];
        nr.index = i;
        dataNumbers.push_back(nr);
    }
    sort(dataNumbers.begin(), dataNumbers.end(), cmpFunction);
    for(int i = 0; i < dataNumbers.size(); i++) {
        int searchStatus = binSearchIndexesPair(i + 1, dataNumbers.size() - 1, sum - dataNumbers[i].value, dataNumbers);
        if(searchStatus != -1) {
            cout << "Method2 - O(nlogn)" << '\n';
            cout << dataNumbers[i].index << " " << dataNumbers[searchStatus].index << '\n';
            return;
        }
    }
    cout << "Numbers not found" << '\n';
}

void getSumTermsIndexesMethod3(vector <int> numbers, int sum) {
     map <int, int> numbersHash;
     int restSum;

     for(int i = 0; i < numbers.size(); i++) {
        numbersHash.insert(pair<int, int>(numbers[i], i));
     }

     for(int i = 0; i < numbers.size(); i++) {
        restSum = sum - numbers[i];
        if(numbersHash.count(restSum) > 0) {
            int j = numbersHash.at(restSum);
            if(i != j) {
                cout << "Method2 - O(n)" << '\n';
                cout << i << " " << j << '\n';
                return;
            }
        }
     }
     cout << "Numbers not found" << '\n';
}

int main()
{
    //Data declaration
    int sum;
    vector <int> numbers;

    readData(numbers, sum);

    // O(n^2) complexity
    getSumTermsIndexesMethod1(numbers, sum);

    // O(nlogn) complexity
    getSumTermsIndexesMethod2(numbers, sum);

    // O(n) complexity
    getSumTermsIndexesMethod3(numbers, sum);

    return 0;
}
