#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <curl/curl.h>
#include <boost/algorithm/string/join.hpp>

#include "Network.hpp"

using namespace wtlgo;

Network::
Network(){
    curl_global_init(CURL_GLOBAL_ALL);
}

Network::~Network(){
}

Network& Network::getInstance(){
    static Network instance;
    return instance;
}

void Network::set_proxy(const std::string& proxy){
    this->proxy = proxy;
}

std::string Network::request(std::string url, const std::map<std::string, std::string>& args, bool post) const{
    CURL_ptr curl;
    CURLcode res;
    std::string readBuffer;
    
    std::string fields;
    curl = curl_init();
    if(curl){
        std::vector<std::string> tmp_list;
        for(const std::pair<std::string, std::string> row : args){
            std::shared_ptr<char> data(
                                       curl_easy_escape(curl.get(), row.second.c_str(), static_cast<int>(row.second.size())),
                                       curl_free);
            tmp_list.push_back(row.first + "=" + (data ? std::string(data.get()) : row.second));
        }
        
        fields = boost::algorithm::join(tmp_list, "&");
    }
    
    curl = curl_init();
    if(curl) {
        if(fields.size() > 0){
            if(post){
                curl_easy_setopt(curl.get(), CURLOPT_POST, 1);
                curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, fields.c_str());
            }
            else{
                url += "?" + fields;
            }
        }
        
        curl_easy_setopt(curl.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, string_writer);
        curl_easy_setopt(curl.get(), CURLOPT_FOLLOWLOCATION, 1);
        if(proxy.size() > 0)
            curl_easy_setopt(curl.get(), CURLOPT_PROXY, proxy.c_str());
        
        res = curl_easy_perform(curl.get());
                
        if(res != 0){
            std::cerr << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }

    return readBuffer;
}

bool Network::download(const std::string& url, const std::string& save_as) const{
    CURL_ptr curl;
    CURLcode res;
    
    std::string filename = save_as;
    if(filename.size() == 0){
        std::string::size_type slash_p = url.find_last_of('/');
        filename = std::string(url.begin() + 1 + slash_p, url.end());
    }
    
    curl = curl_init();
    if(curl){
        std::shared_ptr<FILE> file(fopen(filename.c_str(), "wb"), fclose);
        
        curl_easy_setopt(curl.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, file.get());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, file_writer);
        curl_easy_setopt(curl.get(), CURLOPT_FOLLOWLOCATION, 1);
        if(proxy.size() > 0)
            curl_easy_setopt(curl.get(), CURLOPT_PROXY, proxy.c_str());
        
        res = curl_easy_perform(curl.get());
                        
        if(res != 0){
            std::cerr << curl_easy_strerror(res) << std::endl;
            remove(filename.c_str());
            return false;
        }
    }
    else{
        return false;
    }
    
    return true;
}

std::string Network::upload(std::string url, const std::string& fieldname, const std::string& filename) const{
    CURL_ptr curl;
    CURLcode res;
    std::string readBuffer;
    
    curl_httppost *formpost = nullptr;
    curl_httppost *lastptr = nullptr;
        
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, fieldname.c_str(),
                 CURLFORM_FILE, filename.c_str(),
                 CURLFORM_END);
    
    curl = curl_init();
    
    if (curl) {
        curl_easy_setopt(curl.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, string_writer);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_HTTPPOST, formpost);
        
        res = curl_easy_perform(curl.get());
        curl_formfree(formpost);
        
        if (res != CURLE_OK){
            std::cerr << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }
    
    return readBuffer;    
}


size_t Network::string_writer(void *contents, size_t size, size_t nmemb, std::string *stream){
    stream->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

size_t Network::file_writer(void *contents, size_t size, size_t nmemb, FILE *stream){
    size_t written = fwrite(contents, size, nmemb, stream);
    return written;
}

Network::CURL_ptr Network::curl_init() const {
    return std::shared_ptr<CURL>(curl_easy_init(), curl_easy_cleanup);
}
