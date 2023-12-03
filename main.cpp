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
    std::vector<Node*> allData;
    std::string input;
    getline(fileStream, input);
    while(getline(fileStream, input)) {
        try {
            std::stringstream dataIn(input);
            std::string token;

            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            tempCat = token;
            //std::cout << "tempCat = " << token << std::endl;
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            tempCountry = token;
            /*if (token == "") {
                std::cout << "tempCountry = Unknown" << std::endl;
            }
            else {
                std::cout << "tempCountry = " << token << std::endl;
            }*/
            //getline(dataIn, token, '\t');  WARNING: USED TO BE DESCRIPTION - FIELD HAS BEEN REMOVED FROM FILE
            getline(dataIn, token, '\t');
            std::cout << "tempSubs = " << token << std::endl;
            tempSubs = stol(token);
            //std::cout << "tempSubs = " << token << std::endl;
            getline(dataIn, token, '\t');
            tempDate = token;
            /*if (token == "") {
                std::cout << "tempDate = 2/14/2015" << std::endl;
            }
            else {
                std::cout << "tempCountry = " << token << std::endl;
            }*/
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            tempName = token;
            //std::cout << "tempName = " << token << std::endl;
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            getline(dataIn, token, '\t');
            std::cout << "tempVids = " << token << std::endl;
            tempVids = stol(token);
            //std::cout << "tempVids = " << token << std::endl;

            Node* temp = new Node(tempCat, tempCountry, tempSubs, tempDate, tempName, tempVids);
            allData.push_back(temp);
            channelCnt += 1;
            std::cout <<  "***" << channelCnt << " channels pushed. Vector size = " << allData.size()  << "***" << std::endl;
            /*std::cout << "**" << channelCnt << "**" << std::endl;
            if(channelCnt >= 100000) {
                break;
            }*/
        }
        catch (std::exception e) {
            continue;
        }

    }
    return 0;
}
