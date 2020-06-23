#include <iostream>
#include <memory>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>

const std::string fileName = "KeyLogger.txt";

#define __GET_FIRST_ARG(FirstArg, ...) FirstArg
#define GET_HEAD(...) __GET_FIRST_ARG(__VA_ARGS__)
#define LOG_INF(...) printf(GET_HEAD(__VA_ARGS__), __VA_ARGS__)
#define LOG_INF_2(STRING, ...) printf(STRING, ##__VA_ARGS__) //##removes comma when __VA_ARGS__ is empty

void merge(std::vector<int>& vect, uint32_t l, uint32_t m, uint32_t r)
{
    std::vector<int> leftTemporary(&vect[l], &vect[m + 1]);
    std::vector<int> rightTemporary(&vect[m+1], &vect[r + 1]);

    int count = 0;
    uint32_t leftIndex = 0;
    uint32_t rightIndex = 0;
    uint32_t initialIndexOfMergedArray = l;

    while (leftIndex < leftTemporary.size()
           && rightIndex < rightTemporary.size())
    {
        if(leftTemporary[leftIndex] <= rightTemporary[rightIndex])
        {
            vect[initialIndexOfMergedArray] = leftTemporary[leftIndex];
            ++leftIndex;
        }
        else
        {

            vect[initialIndexOfMergedArray] = rightTemporary[rightIndex];
            ++rightIndex;
            ++inversion;
        }
        ++initialIndexOfMergedArray;
    }

    while(leftIndex < leftTemporary.size())
    {
        vect[initialIndexOfMergedArray] = leftTemporary[leftIndex];
        ++initialIndexOfMergedArray;
        ++leftIndex;
    }

    while(rightIndex < rightTemporary.size())
    {
        vect[initialIndexOfMergedArray] = rightTemporary[rightIndex];
        ++initialIndexOfMergedArray;
        ++rightIndex;
    }
}

void mergeSort(std::vector<int>& vect, int leftMostIndex, int rightMostIndex)
{
    if (leftMostIndex < rightMostIndex)
    {
        int midIndex = (leftMostIndex + (rightMostIndex)) / 2;
        mergeSort(vect, leftMostIndex, midIndex);
        mergeSort(vect, midIndex+1, rightMostIndex);
        merge(vect, leftMostIndex, midIndex, rightMostIndex);
    }
}

void myMergeSort(std::vector<int>& vect)
{
    std::vector<std::vector<int>> awef {};
    bool isNotFinished = false;

    for (auto cout : vect)
    {
        std::vector<int>> awefg {cout};
        awef.emplace_back(awefg):
    }

}


int main(int argc, char** argv)
{
    std::vector<int> vect {7, 1, 3, 2, 4, 5, 6};
    for (int x : vect)
    {
        std::cout << x << ",";
    }
    std::cout << std::endl;

    ::mergeSort(vect, 0, vect.size() -  1);

    for (int x : vect)
    {
        std::cout << x << ",";
    }

    std::cout << std::endl;
    std::cout << inversion << std::endl;
}