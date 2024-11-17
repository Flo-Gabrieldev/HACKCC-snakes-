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
