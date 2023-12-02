#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <set>
#include "Node.h"


bool compareDates(string one, string two)
{
    int yearOne = stoi(one.substr(one.length() - 4, one.length()));
    int yearTwo = stoi(two.substr(two.length() - 4, two.length()));

    if (yearOne == yearTwo)
    {
        int monthOne = stoi(one.substr(0, one.find('/')));
        int monthTwo = stoi(two.substr(0, two.find('/')));
        if (monthOne == monthTwo)
        {
            int dayOne = stoi(one.substr(one.find('/') + 1, one.length() + 5));
            int dayTwo = stoi(two.substr(two.find('/') + 1, two.length() + 5));
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

void printArray(vector<Node> list, string type, long start, long end)
{

    if (type == "vids")
    {
        for (auto i = start; i < end; i++)
            cout << list[i].value << ": " << list[i].video << endl;
    } else if (type == "subs") {
        for (auto i = start; i < end; i++)
            cout << list[i].value << ": " << list[i].subscriber << endl;
    } else if (type == "date") {
        for (auto i = start; i < end; i++)
            cout << list[i].value << ": " << list[i].date << endl;
    }

    cout << endl;
}

int partition(vector<Node> list, string type,int low,int high)
{


    if (type == "vids"){
        //Note that the pivot is chosen is high and the list isnt sorted yet
        //choose the pivot
        auto pivot = list[high].video;
        int i=(low-1);

        for(int j=low;j<=high;j++)
        {
            if(list[j].video <pivot)
            {
                i++;
                swap(list[i],list[j]);
            }
        }
        swap(list[i+1],list[high]);
        return (i+1);
    }

    if (type == "subs"){
        auto pivot = list[high].subscriber;
        int i=(low-1);

        for(int j=low;j<=high;j++)
        {
            if(list[j].subscriber <pivot)
            {
                i++;
                swap(list[i],list[j]);
            }
        }
        swap(list[i+1],list[high]);
        return (i+1);
    }

    if(type == "date"){
        auto pivot = list[high].date;
        int i=(low-1);

        //compareDates(list[j].data, pivot) != true ;
        for(int j=low; compareDates(list[j].date, pivot) != true ;j++)
        {
            if(compareDates(list[j].date, pivot))
            {
                i++;
                swap(list[i],list[j]);
            }
        }
        swap(list[i+1],list[high]);
        return (i+1);
    }


}

void quickSort(vector<Node> &list, string type, int low,int high)
{

    if(low<high)
    {
        int pivot = partition(list, type ,low,high);
        //pivot left
        quickSort(list, type,low,pivot-1);
        //pivot right
        quickSort(list, type ,pivot+1,high);
    }
}

void category(vector<Node> copy)
{
    while(true)
    {
        cout << "Choose which category we want to work through" << endl;
        cout << "1. Amount of Videos" << endl;
        cout << "2. Subscriber Count" << endl;
        cout << "3. Date Joined" << endl;
        cout << "4. Back" << endl;
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
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    mergeSort(copy, "vids", 0, copy.size() - 1);
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
                            cout << endl << "<Amount of Videos - Merge Sort>" << endl;
                            printArray(copy, "vids", 0, copy.size());
                            break;
                        } else if (amountInput == "2") {
                            cout << endl << "<Amount of Videos - Merge Sort>" << endl;
                            printArray(copy, "vids", 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl << endl;
                    break;
                } else if (sortInput == "2"){
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    quickSort(copy, "vids", 0, copy.size() - 1);
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
                            cout << endl << "<Amount of Videos - Quick Sort>" << endl;
                            printArray(copy, "vids", 0, copy.size());
                            break;
                        } else if (amountInput == "2") {
                            cout << endl << "<Amount of Videos - Quick Sort>" << endl;
                            printArray(copy, "vids", 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl << endl;
                    break;
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
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    mergeSort(copy, "subs", 0, copy.size() - 1);
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
                            cout << endl << "<Subscriber Count - Merge Sort>" << endl;
                            printArray(copy, "subs", 0, copy.size());
                            break;
                        } else if (amountInput == "2") {
                            cout << endl << "Subscriber Count - Merge Sort" << endl;
                            printArray(copy, "subs", 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl << endl;
                    break;
                } else if (sortInput == "2"){
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    quickSort(copy, "subs", 0, copy.size() - 1);
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
                            cout << endl << "<Subscriber Count - Quick Sort>" << endl;
                            printArray(copy, "subs", 0, copy.size());
                            break;
                        } else if (amountInput == "2") {
                            cout << endl << "Subscriber Count - Quick Sort" << endl;
                            printArray(copy, "subs", 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl << endl;
                    break;
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
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    mergeSort(copy, "date", 0, copy.size() - 1);
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
                            cout << endl << "<Date Joined - Merge Sort>" << endl;
                            printArray(copy, "date", 0, copy.size());
                            break;
                        } else if (amountInput == "2") {
                            cout << endl << "<Date Joined - Merge Sort>" << endl;
                            printArray(copy, "date", 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl << endl;
                    break;
                } else if (sortInput == "2"){
                    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                    quickSort(copy, "date", 0, copy.size() - 1);
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
                            cout << endl << "<Date Joined - Quick Sort>" << endl;
                            printArray(copy, "date", 0, copy.size());
                            break;
                        } else if (amountInput == "2") {
                            cout << endl << "<Date Joined - Quick Sort>" << endl;
                            printArray(copy, "date", 0, 20);
                            break;
                        } else {
                            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                        }
                    }
                    cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << endl << endl << endl;
                    break;
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

int main()
{
    vector<Node> youtubers;
    youtubers.emplace_back("", 15757, 19169156, "1/25/2007");
    youtubers.emplace_back("DemiLovatoVEVO", 165, 12109565, "5/12/2009");
    youtubers.emplace_back("RomanAtwoodVlogs", 1561, 14990695, "8/12/2013");
    youtubers.emplace_back("Like Nastya", 226, 10476486, "1/14/2016");
    youtubers.emplace_back("Its JoJo Siwa", 405, 8146407, "2/1/2015");
    while (true)
    {
        vector<Node> copy = youtubers;
        cout << "Choose whether you wish to sort all the youtube channels or seperated by country or category" << endl;
        cout << "1. All" << endl;
        cout << "2. Separate by Country" << endl;
        cout << "3. Separate by Category" << endl;
        cout << "4. Exit program" << endl;

        string separateInput;
        cin >> separateInput;

        if (separateInput == "1")
        {
            category(copy);
        } else if (separateInput == "2") {

            set<string> countries;
            for(int i = 0; i < youtubers.size(); i++)
            {
                countries.insert(youtubers[i].country);
            }

            while (true)
            {
                cout << "Enter which country you wish access" << endl;

                string channelInput;
                cin >> channelInput;
                if (countries.count(channelInput) != 0)
                {
                    //M put code here
                    category(copy);
                    break;
                } else {
                    cout << "Sorry that does not countries. You may have misspelled it. Please try again." << endl;
                }

            }
        } else if (separateInput == "3") {
            while (true)
            {
                cout << "Choose which category you wish access" << endl;
                cout << "1. Film and Animation" << endl;
                cout << "2. Autos & Vehicles" << endl;
                cout << "3. Music" << endl;
                cout << "4. Pets & Animals" << endl;
                cout << "5. Sports" << endl;
                cout << "6. Travel & Events" << endl;
                cout << "7. Gaming" << endl;
                cout << "8. People & Blogs" << endl;
                cout << "9. Comedy" << endl;
                cout << "10. Entertainment" << endl;
                cout << "11. News & Politics" << endl;
                cout << "12. Howto & Style" << endl;
                cout << "13. Education" << endl;
                cout << "14. Science & Technology" << endl;
                cout << "15. Channel Trailer:" << endl;
                cout << "16. Back" << endl;

                string channelInput;
                cin >> channelInput;

                if (channelInput == "1")
                {
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "2"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "3"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "4"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "5"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "6"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "7"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "8"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "9"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "10"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "11"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "12"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "13"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "14"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "15"){
                    //M put code here
                    category(copy);
                    break;
                } else if (channelInput == "16"){
                    break;
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }

            }

        } else if (separateInput == "4") {
            break;
        } else {
            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
        }

    }

}
