#include <iostream>
#include <string>
#include "httplib.h"
#include "nlohmann/json.hpp"

#define CPPHTTPLIB_OPENSSL_SUPPORT

using json = nlohmann::json;

int main() {
    httplib::Client cli1("https://whatsmyip.dev");
    auto result = cli1.Get("/api/ip");

    json data = json::parse(result->body);

    std::string ip = data["addr"];

    std::string request = "/json/" + ip;

    httplib::Client cli2("http://ip-api.com");
    result = cli2.Get(request);

    data = json::parse(result->body);

    auto latitude = to_string(data["lat"]);
    auto longtitude = to_string(data["lon"]);

    request = "/v1/forecast?latitude=" + latitude + "&longitude=" + longtitude + 
    "daily=temperature_2m_max,temperature_2m_min&forecast_days=2&timezone=Europe%2FMoscow";

    httplib::Client cli3("https://api.open-meteo.com");
    result = cli3.Get(request);

    data = json::parse(result->body);

    std::cout << "Температура сегодня может колебаться от: " <<
    data["temperature_2m_max"][0] << " до: " << data["temperature_2m_min"][0] << "\n" <<
    "Температура завтра может колебаться от: " <<
    data["temperature_2m_max"][1] << " до: " << data["temperature_2m_min"][1] << "\n";

    return 0;
}