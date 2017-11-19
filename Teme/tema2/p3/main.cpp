#include <iostream>

using namespace std;

struct weigthElement {
    float weight;
    int val;
};

void read(weigthElement elements[], int &numberOfElements) {
    int i;
    cin >> numberOfElements;
    for(i = 1; i <= numberOfElements; i++) {
        cin >> elements[i].val;
    }
    for(i = 1; i <= numberOfElements; i++) {
        cin >> elements[i].weight;
    }
}

void display(weigthElement elements[], int numberOfElements) {
    int i;
    for(i = 1; i <= numberOfElements; i++) {
        cout << elements[i].val << " ";
    }
    cout << '\n' << '\n';
}

void swapElements(weigthElement &el1, weigthElement &el2) {
    weigthElement aux = el1;
    el1 = el2;
    el2 = aux;
}

int makePartition(weigthElement elements[], int left, int right) {
    weigthElement el = elements[right], aux;
    int i = left, j;
    for(j = left; j <= right - 1; j++) {
        if(elements[j].val <= el.val) {
            swapElements(elements[j], elements[i]);
            i++;
        }
    }
    swapElements(elements[j], elements[i]);
    return i;
}

void findMedian(weigthElement elements[], int left, int right, int k) {
    if(k >= 1 && k <= right - left + 1) {
        int pos = makePartition(elements, left, right), i;
        if(pos == right) {
            pos = makePartition(elements, left, right - 1);
        }
        float leftSum = 0, rightSum = 0;
        for(i = left; i <= right; i++) {
            if(i < pos) {
                leftSum += elements[i].weight;
            }
            if(i > pos) {
                rightSum += elements[i].weight;
            }
        }
        if(leftSum < 0.5 && rightSum <= 0.5) {
            cout << elements[pos].val << '\n';
            return;
        }
        else if(leftSum >= 0.5) {
            elements[pos].weight += rightSum;
            findMedian(elements, left, pos, k);
        }
        else {
            elements[pos].weight += leftSum;
            findMedian(elements, pos, right, k - pos + left - 1);
        }
        return;
    }
    return;
}

int main()
{
    weigthElement elements[1000];
    int numberOfElements, k;
    read(elements, numberOfElements);
    k = numberOfElements / 2;
    findMedian(elements, 1, numberOfElements, k);
    return 0;
}
