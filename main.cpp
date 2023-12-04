#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <set>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
    std::string category;
    std::string country;
    long subs;
    std::string join_date;
    std::string name;
    long videos;

    Node() = default;
    Node(std::string category_, std::string country_, long subs_, std::string join_date_, std::string name_, long videos_) {
        category = category_;
        country = country_;
        subs = subs_;
        join_date = join_date_;
        name = name_;
        videos = videos_;
    }
};

//determines if one has an earlier date than two
bool compareDates(string one, string two)
{
    //get the years for both strings
    int yearOne = stoi(one.substr(one.length() - 4, one.length()));
    int yearTwo = stoi(two.substr(two.length() - 4, two.length()));

    //checks if they have the same year
    if (yearOne == yearTwo)
    {
        //get the months for both strings
        int monthOne = stoi(one.substr(0, one.find('/')));
        int monthTwo = stoi(two.substr(0, two.find('/')));

        //checks if they have the same month
        if (monthOne == monthTwo)
        {
            //get the days for both strings
            int dayOne = stoi(one.substr(one.find('/') + 1, one.length() + 5));
            int dayTwo = stoi(two.substr(two.find('/') + 1, two.length() + 5));

            //returns true if day one is earlier than day two or if they are the same and false if not
            if (dayOne >= dayTwo)
            {
                return true;
            } else {
                return false;
            }

        //returns true if month one is earlier than month two and false if not
        } else if (monthOne > monthTwo) {
            return true;
        } else {
            return false;
        }

    //returns true if year one is earlier than year two and false if not
    } else if (yearOne > yearTwo) {
        return true;
    } else {
        return false;
    }
}

//merges two list together
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

    //merges based on videos
    if(type == "vids")
    {
        while(leftIndex < lengthOne && rightIndex < lengthTwo)
        {
            if(left[leftIndex].videos >= right[rightIndex].videos)
            {
                list[totalIndex] = left[leftIndex];
                leftIndex++;
            } else {
                list[totalIndex] = right[rightIndex];
                rightIndex++;
            }
            totalIndex++;
        }

    //merges based on number of subscribers
    } else if (type == "subs") {

        while(leftIndex < lengthOne && rightIndex < lengthTwo)
        {
            if(left[leftIndex].subs >= right[rightIndex].subs)
            {
                list[totalIndex] = left[leftIndex];
                leftIndex++;
            } else {
                list[totalIndex] = right[rightIndex];
                rightIndex++;
            }
            totalIndex++;
        }

    //merges based on date joined
    } else if (type == "date") {
        while(leftIndex < lengthOne && rightIndex < lengthTwo)
        {
            if(compareDates(left[leftIndex].join_date, right[rightIndex].join_date))
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

//sorts the list using the merge sort algorithm
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

//prints out the items in the list, from start to end, and there type
void printArray(vector<Node> list, string type, long start, long end)
{
    //checks if type is vids
    if (type == "vids")
    {
        //prints out the name and the number of videos
        for (auto i = start; i < end; i++)
            cout << list[i].name << ": " << list[i].videos << endl;

    //checks if type is subs
    } else if (type == "subs") {
        //prints out the name and the number of subscribers
        for (auto i = start; i < end; i++)
            cout << list[i].name << ": " << list[i].subs << endl;

    //checks if type is date
    } else if (type == "date") {
        //prints out the name and the date joined
        for (auto i = start; i < end; i++)
            cout << list[i].name << ": " << list[i].join_date << endl;
    }

    cout << endl;
}

long partition(vector<Node> list, string type, long low, long high)
{


    if (type == "vids"){
        //Note that the pivot is chosen is high and the list isnt sorted yet
        //choose the pivot
        auto pivot = list[high].videos;
        long i=(low-1);

        for(long j=low;j<=high;j++)
        {
            if(list[j].videos <pivot)
            {
                i++;
                swap(list[i],list[j]);
            }
        }
        swap(list[i+1],list[high]);
        return (i+1);
    }

    if (type == "subs"){
        auto pivot = list[high].subs;
        long i=(low-1);

        for(long j=low;j<=high;j++)
        {
            if(list[j].subs <pivot)
            {
                i++;
                swap(list[i],list[j]);
            }
        }
        swap(list[i+1],list[high]);
        return (i+1);
    }

    if(type == "date"){
        auto pivot = list[high].join_date;
        long i=(low-1);

        //compareDates(list[j].data, pivot) != true ;
        for(long j=low; compareDates(list[j].join_date, pivot) != true ;j++)
        {
            if(compareDates(list[j].join_date, pivot))
            {
                i++;
                swap(list[i],list[j]);
            }
        }
        swap(list[i+1],list[high]);
        return (i+1);
    }


}

void quickSort(vector<Node> &list, string type, long low,long high)
{

    if(low<high)
    {
        long pivot = partition(list, type ,low,high);
        //pivot left
        quickSort(list, type,low,pivot-1);
        //pivot right
        quickSort(list, type ,pivot+1,high);
    }
}

//chooses which category to sort based on
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

        //Sorts based on video count
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

                //merge sorts based on videos
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
                //quick sorts based on videos
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
                //goes back
                } else if (sortInput == "3"){
                    break;
                //incorrect response
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }
            }

        //Sorts based on subscriber count
        } else if (typeInput == "2") {

            while (true)
            {
                cout << "Please choose what sorting algorithm you would like to use" << endl;
                cout << "1. Merge Sort" << endl;
                cout << "2. Quick Sort" << endl;
                cout << "3. Back" << endl;
                string sortInput;
                cin >> sortInput;

                //merge sorts based on subscribers
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

                //quick sorts based on subscribers
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

                //goes back
                } else if (sortInput == "3"){
                    break;
                //incorrect response
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }
            }

        //Sorts based on date joined
        } else if (typeInput == "3") {

            while (true)
            {
                cout << "Please choose what sorting algorithm you would like to use" << endl;
                cout << "1. Merge Sort" << endl;
                cout << "2. Quick Sort" << endl;
                cout << "3. Back" << endl;
                string sortInput;
                cin >> sortInput;

                //merge sorts based on date
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

                //quick sorts based on date
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
                //goes back
                } else if (sortInput == "3"){
                    break;
                //incorrect response
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }
            }

        //goes back
        } else if (typeInput == "4") {
            break;
        //incorrect response
        } else {
            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
        }
    }
}

int main()
{
    std::cout << "First few lines..." << std::endl;
    std::string file = "channels_no_description.txt";
    std::ifstream fileStream;
    fileStream.open(file);
    if(!(fileStream.is_open())) {
        std::cout << "File not open. Check file location (cmake-build-debug for clion), and file/stream name" << std::endl;
    }

    std::string tempCat = "";
    std::string tempCountry = "";
    std::string tempName = "";
    long tempSubs = 0;
    std::string tempDate = "";
    long tempVids = 0;

    int channelCnt = 0;
    std::vector<Node> allData;
    std::string input;
    getline(fileStream, input);
    while(getline(fileStream, input)) {
        try {
            std::stringstream dataIn(input);
            std::string token;

            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            tempCat = token;
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            if (token == "") {
                tempCountry = "Unknown";
            }
            else {
                tempCountry = token;
            }
            //getline(dataIn, token, '\t');  WARNING: USED TO BE DESCRIPTION - FIELD HAS BEEN REMOVED FROM FILE
            getline(dataIn, token, '\t');
            tempSubs = stol(token);
            getline(dataIn, token, '\t');
            if (token == "") {
                tempDate = "2/14/2015";
            }
            else {
                tempDate = token;
            }
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            tempName = token;
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            tempVids = stol(token);
            Node* temp = new Node(tempCat, tempCountry, tempSubs, tempDate, tempName, tempVids);
            allData.push_back(*temp);
            channelCnt += 1;
        }
        catch (std::exception e) {
            continue;
        }

    }


    while (true)
    {
        vector<Node> copy = allData;
        cout << "Choose whether you wish to sort all the youtube channels or seperated by country or category" << endl;
        cout << "1. All" << endl;
        cout << "2. Separate by Country" << endl;
        cout << "3. Separate by Category" << endl;
        cout << "4. Exit program" << endl;

        string separateInput;
        cin >> separateInput;

        //Sorts with all items in it
        if (separateInput == "1")
        {
            category(copy);

        //sorts based on the countries the youtubers live in
        } else if (separateInput == "2") {

            //makes a set of all the countries in the list
            set<string> countries;
            for(int i = 0; i < allData.size(); i++)
            {
                countries.insert(allData[i].country);
            }

            while (true)
            {
                cout << "Enter which country you wish access or enter \"back\" to go back" << endl;

                string channelInput;
                getline(cin, channelInput);
                getline(cin, channelInput);

                //goes back
                if (channelInput == "back")
                {
                    break;

                //checks if channelInput is in the list
                } else if (countries.count(channelInput) != 0){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->country != channelInput)
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;

                //incorrect response
                } else {
                    cout << "Sorry that does not countries. You may have misspelled it. Please try again." << endl;
                }

            }
        //sorts based on the category of the channel
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

                //sorts based on one of the categories stated above
                if (channelInput == "1")
                {
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Film and Animation")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "2"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Autos & Vehicles")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "3"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Music")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "4"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Pets & Animals")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "5"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Sports")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "6"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Travel & Events")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "7"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Gaming")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "8"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "People & Blogs")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "9"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Comedy")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "10"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Entertainment")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "11"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "News & Politics")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "12"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Howto & Style")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "13"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Education")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "14"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category == "Science & Technology")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;
                } else if (channelInput == "15"){
                    vector<Node> copy2;
                    for(auto i = copy.begin(); i != copy.end(); i++)
                    {
                        if(i->category =="Channel Trailer:")
                        {
                            copy2.emplace_back(*i);
                        }
                    }
                    category(copy2);
                    break;

                //goes back
                } else if (channelInput == "16"){
                    break;

                //incorrect response
                } else {
                    cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
                }
            }
        //ends the program
        } else if (separateInput == "4") {
            break;
        //incorrect response
        } else {
            cout << "Sorry that does not seem to be one of the options. Please try again." << endl;
        }

    }

}
