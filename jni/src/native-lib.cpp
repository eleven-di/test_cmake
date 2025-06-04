#include <iostream>
#include <sstream>
#include "json/json.h"
#include "curl/curl.h"
#include <jni.h>

size_t WriteCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    ((std::string*)userdata)->append(ptr, size * nmemb);
    return size * nmemb;
}

std::basic_string<char, std::char_traits<char>, std::allocator<char>>
SendGetRequest(const std::string& param1, const std::string& param2) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://qsuy.sijbgzbbtc.top/fuop/oy/xqjt";

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // 关闭 SSL 验证（仅用于测试）
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "Request Error: " << curl_easy_strerror(res) << std::endl;
//            printf("");
            return "Error";
        }

        // 解析 JSON 响应
//        Json::Value root;
//        Json::CharReaderBuilder reader;
//        std::string errors;
//        std::istringstream s(readBuffer);
//        if (!Json::parseFromStream(reader, s, &root, &errors)) {
//            std::cerr << "JSON Parse Error: " << errors << std::endl;
//        }
//
//        // 开始解析json数据
//        if (root["elements"].asString() == "ok" && root["field2"].isObject()) {
//            Json::Value field2 = root["field2"];
//            int field3 = field2["field3"].asInt();
//            std::string field4 = field2["field4"].asString();
//        }
        return readBuffer;  // 直接返回原始响应内容
    }
    return "null";
}




extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_test_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(SendGetRequest("111","222").c_str());
}