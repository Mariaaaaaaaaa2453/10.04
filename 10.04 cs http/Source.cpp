#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <Urlmon.h>
#pragma comment(lib, "urlmon.lib")

using namespace std;

void extractTemperature(const string& sourceURL, const string& cityName) {
    const string tempFile = "weather_data.txt";

    // Перезаписываем файл для нового использования
    ofstream outFile(tempFile, ios::trunc);
    outFile.close();

    if (URLDownloadToFile(NULL, sourceURL.c_str(), tempFile.c_str(), 0, NULL) != S_OK) {
        cout << "Failed to download weather data for " << cityName << endl;
        return;
    }

    ifstream inFile(tempFile);
    string line;
    string temperature;

    while (getline(inFile, line)) {
        size_t start = line.find("data-temperature-f=\"") + 20; // Позиция начала температуры
        if (start != string::npos) {
            size_t end = line.find("\"", start); // Позиция конца температуры
            if (end != string::npos) {
                temperature = line.substr(start, end - start);
                cout << "Current temperature in " << cityName << ": " << temperature << "°F\n";
                break;
            }
        }
    }

    inFile.close();
}

int main() {
    struct CityWeather {
        string url;
        string name;
    };

    const vector<CityWeather> cities = {
        {"https://www.gismeteo.ua/weather-odessa-4982/", "Odessa"},
        {"https://meteofor.com.ua/ru/weather-kyiv-4944/", "Kyiv"},
        {"https://meteofor.com.ua/ru/weather-lviv-4949", "Lviv"},
        {"https://meteofor.com.ua/ru/weather-kharkiv-5053/", "Kharkiv"},
        {"https://meteofor.com.ua/ru/weather-sumy-4936/", "Sumy"},
        {"https://meteofor.com.ua/ru/weather-dnipro-5077/", "Dnipro"},
        {"https://meteofor.com.ua/ru/weather-zaporizhia-5093/", "Zaporizhzhia"},
        {"https://meteofor.com.ua/ru/weather-kryvyi-rih-4978/", "Kryviy Rih"},
        {"https://meteofor.com.ua/ru/weather-vinnytsia-4962/", "Vinnytsia"},
        {"https://meteofor.com.ua/ru/weather-poltava-4957/", "Poltava"},
        {"https://meteofor.com.ua/ru/weather-chernihiv-4923/", "Chernihiv"}
    };

    for (const auto& city : cities) {
        extractTemperature(city.url, city.name);
    }

    return 0;
}
