// HackCCProject2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include <iostream>
//#include <curl/curl.h>
//
//using namespace std;
//
//void sendCoins(int userId, int coins) {
//    CURL* curl;
//    CURLcode res;
//
//    // Initialize cURL
//    curl = curl_easy_init();
//    if (curl) {
//        // Set the URL
//        curl_easy_setopt(curl, CURLOPT_URL, "https://api.yoursite.com/update-coins");
//
//        // Prepare the JSON payload
//        std::string jsonPayload = "{\"userId\": " + std::to_string(userId) + ", \"coins\": " + std::to_string(coins) + "}";
//
//        // Set the request method to POST
//        curl_easy_setopt(curl, CURLOPT_POST, 1L);
//
//        // Set the POST fields
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
//
//        // Set the headers
//        struct curl_slist* headers = NULL;
//        headers = curl_slist_append(headers, "Content-Type: application/json");
//        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
//
//        // Perform the request
//        res = curl_easy_perform(curl);
//
//        // Check for errors
//        if (res != CURLE_OK)
//            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
//
//        // Cleanup
//        curl_easy_cleanup(curl);
//        curl_slist_free_all(headers);
//    }
//}
//
//int main()
//{
//    sendCoins(123, 50);
//    cout << "Hello World!\n";
//    return 0;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


#include <iostream>
#include <string>
#include <curl/curl.h>

void sendCoinCountToServer(int coins) {
    CURL* curl;
    CURLcode res;
    //std::string url = "http://your-server-url/update_coins.php";
    std::string url = "http://localhost:8000/update_coins.php";

    // Initialize cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Prepare the POST data
        std::string postData = "coins=" + std::to_string(coins);

        // Set up the cURL options
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }

        // Clean up
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

int main() {
    bool isRunning = true;
    while (isRunning) {
        std::cout << "Please input coins: ";
        int numCoins;
        std::cin >> numCoins;
        sendCoinCountToServer(numCoins);
        std::string input1;
        std::cout << "Would you like to quit? (y/n): ";
        std::cin >> input1;
        if (input1 == "yes") {
            isRunning = false;
        }
    }
    int coins = 5; // Example coin count
    sendCoinCountToServer(coins);

    return 0;
}
