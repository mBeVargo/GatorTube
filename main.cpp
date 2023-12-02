#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Node.h"


bool compareDates(string one, string two)
{
    int yearOne = stoi(one.substr(one.length() - 4, one.length()));
    int yearTwo = stoi(two.substr(two.length() - 4, two.length()));
    int monthOne = stoi(one.substr(0, one.find('/')));
    int monthTwo = stoi(two.substr(0, two.find('/')));
    int dayOne = stoi(one.substr(one.find('/') + 1, one.length() + 5));
    int dayTwo = stoi(two.substr(two.find('/') + 1, two.length() + 5));

    if (yearOne == yearTwo)
    {
        if (monthOne == monthTwo)
        {
            if (dayOne >= dayTwo)
            {
                return true;
            } else {
                return false;
            }
        } else if (monthOne > monthTwo) {
            return true;
        } else {
            return false;
        }
    } else if (yearOne > yearTwo) {
        return true;
    } else {
        return false;
    }
}

void merge(vector<Node> &list, string type, long start, long middle, long end)
{
    long lengthOne = middle - start + 1;
    long lengthTwo = end - middle;
    long leftIndex = 0;
    long rightIndex = 0;
    long totalIndex = start;

    vector<Node> left;
    vector<Node> right;

    for(auto i = 0; i < lengthOne; i++)
    {
        left.emplace_back(list[start + i]);
    }
    for(auto j = 0; j < lengthTwo; j++)
    {
        right.emplace_back(list[middle + 1 + j]);
    }

    if(type == "vids")
    {
        while(leftIndex < lengthOne && rightIndex < lengthTwo)
        {
            if(left[leftIndex].video >= right[rightIndex].video)
            {
                list[totalIndex] = left[leftIndex];
                leftIndex++;
            } else {
                list[totalIndex] = right[rightIndex];
                rightIndex++;
            }
            totalIndex++;
        }

    } else if (type == "subs") {

        while(leftIndex < lengthOne && rightIndex < lengthTwo)
        {
            if(left[leftIndex].subscriber >= right[rightIndex].subscriber)
            {
                list[totalIndex] = left[leftIndex];
                leftIndex++;
            } else {
                list[totalIndex] = right[rightIndex];
                rightIndex++;
            }
            totalIndex++;
        }

    } else if (type == "date") {
        while(leftIndex < lengthOne && rightIndex < lengthTwo)
        {
            if(compareDates(left[leftIndex].date, right[rightIndex].date))
            {
                list[totalIndex] = left[leftIndex];
                leftIndex++;
            } else {
                list[totalIndex] = right[rightIndex];
                rightIndex++;
            }
            totalIndex++;
        }

    }

    while (leftIndex < lengthOne)
    {
        list[totalIndex] = left[leftIndex];
        leftIndex++;
        totalIndex++;
    }

    while (rightIndex < lengthTwo)
    {
        list[totalIndex] = right[rightIndex];
        rightIndex++;
        totalIndex++;
    }
}

void mergeSort(vector<Node> &list, string type, long start, long end)
{
    if (start < end)
    {
        long middle = (start + end) / 2;
        mergeSort(list, type, start, middle);
        mergeSort(list, type, middle + 1, end);
        merge(list, type, start, middle, end);
    } else {
        return;
    }
}

void printArray(vector<Node> list, long start, long end)
{
    for (auto i = start; i < end; i++)
        cout << list[i].value << " ";
    cout << endl;
}

int main()
{
    vector<Node> youtubers;
    youtubers.emplace_back("WatchMojo.com", 15757, 19169156, "1/25/2007");
    youtubers.emplace_back("DemiLovatoVEVO", 165, 12109565, "5/12/2009");
    youtubers.emplace_back("RomanAtwoodVlogs", 1561, 14990695, "8/12/2013");
    youtubers.emplace_back("Like Nastya", 226, 10476486, "1/14/2016");
    youtubers.emplace_back("Its JoJo Siwa", 405, 8146407, "2/1/2015");
    while (true)
    {
        cout << "Choose which category we want to work through" << endl;
        cout << "1. Amount of Videos" << endl;
        cout << "2. Subscriber Count" << endl;
        cout << "3. Date Started" << endl;
        cout << "4. Exit Program" << endl;
        string typeInput;
        cin >> typeInput;
        if (typeInput == "1")
        {
            while (true)
            {
                cout << "Please choose what sorting algorithm you would like to use" << endl;
                cout << "1. Merge Sort" << endl;
                cout << "2. Quick Sort" << endl;
                cout << "3. Back" << endl;
                string sortInput;
                cin >> sortInput;

                if (sortInput == "1")
                {
                    vector<Node> copy = youtubers;
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    mergeSort(copy, "vids", 0, youtubers.size() - 1);
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    while (true)
                    {
                        cout << "Please choose how many items you would like to see" << endl;
                        cout << "1. All" << endl;
                        cout << "2. 20" << endl;
                        string amountInput;
                        cin >> amountInput;
                        if (amountInput == "1")
                        {
                            printArray(copy, 0, youtubers.size());
                            break;
                        } else if (amountInput == "2") {
                            printArray(copy, 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl;
                    break;
                } else if (sortInput == "2"){

                } else if (sortInput == "3"){
                    break;
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }
            }
        } else if (typeInput == "2") {

            while (true)
            {
                cout << "Please choose what sorting algorithm you would like to use" << endl;
                cout << "1. Merge Sort" << endl;
                cout << "2. Quick Sort" << endl;
                cout << "3. Back" << endl;
                string sortInput;
                cin >> sortInput;

                if (sortInput == "1")
                {
                    vector<Node> copy = youtubers;
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    mergeSort(copy, "subs", 0, youtubers.size() - 1);
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    while (true)
                    {
                        cout << "Please choose how many items you would like to see" << endl;
                        cout << "1. All" << endl;
                        cout << "2. 20" << endl;
                        string amountInput;
                        cin >> amountInput;
                        if (amountInput == "1")
                        {
                            printArray(copy, 0, youtubers.size());
                            break;
                        } else if (amountInput == "2") {
                            printArray(copy, 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl;
                    break;
                } else if (sortInput == "2"){

                } else if (sortInput == "3"){
                    break;
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }
            }

        } else if (typeInput == "3") {

            while (true)
            {
                cout << "Please choose what sorting algorithm you would like to use" << endl;
                cout << "1. Merge Sort" << endl;
                cout << "2. Quick Sort" << endl;
                cout << "3. Back" << endl;
                string sortInput;
                cin >> sortInput;

                if (sortInput == "1")
                {
                    vector<Node> copy = youtubers;
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    mergeSort(copy, "date", 0, youtubers.size() - 1);
                    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                    while (true)
                    {
                        cout << "Please choose how many items you would like to see" << endl;
                        cout << "1. All" << endl;
                        cout << "2. 20" << endl;
                        string amountInput;
                        cin >> amountInput;
                        if (amountInput == "1")
                        {
                            printArray(copy, 0, youtubers.size());
                            break;
                        } else if (amountInput == "2") {
                            printArray(copy, 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl;
                    break;
                } else if (sortInput == "2"){

                } else if (sortInput == "3"){
                    break;
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }
            }

        } else if (typeInput == "4") {
            break;
        } else {
            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
        }
    }

}
