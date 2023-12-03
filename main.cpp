#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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

int main() {
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
    return 0;
}
