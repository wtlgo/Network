#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <cstdio>
#include <memory>

#include <curl/curl.h>

#include <Network.hpp>

wtlgo::Network& wtlgo::network = wtlgo::Network::instance();

using namespace wtlgo;

Network::Network() {
    curl_global_init(CURL_GLOBAL_ALL);
}

Network::~Network() {}

Network& Network::instance() {
    static Network instance;
    return instance;
}

void Network::set_proxy(const std::string& proxy) {
    this->proxy = proxy;
}

std::string Network::request(std::string url, const std::map<std::string, std::string>& args, bool post) const {
    std::unique_ptr<CURL, void(*)(CURL*)> curl { curl_easy_init(), curl_easy_cleanup };
    CURLcode res;
    std::string readBuffer;
    
    std::string fields;
    {
        std::vector<std::string> tmp_list;
        for(const std::pair<std::string, std::string>& row : args) {
            tmp_list.push_back(url_encode(row.first) + "=" + url_encode(row.second));
        }
        fields = join(tmp_list, "&");
    }
    
    if(curl) {
        if(fields.size() > 0) {
            if(post) {
                curl_easy_setopt(curl.get(), CURLOPT_POST, 1);
                curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, fields.c_str());
            }
            else {
                url += "?" + fields;
            }
        }
        
        curl_easy_setopt(curl.get(), CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, string_writer);
        curl_easy_setopt(curl.get(), CURLOPT_FOLLOWLOCATION, 1);
        if(proxy.size() > 0)
            curl_easy_setopt(curl.get(), CURLOPT_PROXY, proxy.c_str());
        
        res = curl_easy_perform(curl.get());
                
        if(res != 0) {
            logger->log(res);
            return "";
        }
    }

    return readBuffer;
}

bool Network::download(const std::string& url, const std::string& save_as) const {
    std::unique_ptr<CURL, void(*)(CURL*)> curl { curl_easy_init(), curl_easy_cleanup };
    CURLcode res;
    
    std::string filename = save_as;
    if(filename.size() == 0) {
        std::string::size_type slash_p = url.find_last_of('/');
        filename = std::string(url.begin() + 1 + slash_p, url.end());
    }
    
    if(curl) {
        std::unique_ptr<FILE, int(*)(FILE*)> file(fopen(filename.c_str(), "wb"), fclose);
        
        curl_easy_setopt(curl.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, file.get());
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, file_writer);
        curl_easy_setopt(curl.get(), CURLOPT_FOLLOWLOCATION, 1);
        if(proxy.size() > 0)
            curl_easy_setopt(curl.get(), CURLOPT_PROXY, proxy.c_str());
        
        res = curl_easy_perform(curl.get());
                        
        if(res != 0){
            logger->log(res);
            remove(filename.c_str());
            return false;
        }
    }
    else {
        return false;
    }
    
    return true;
}

std::string Network::upload(std::string url, const std::string& fieldname, const std::string& filename) const {
    std::unique_ptr<CURL, void(*)(CURL*)> curl { curl_easy_init(), curl_easy_cleanup };
    CURLcode res;
    std::string readBuffer;
    
    if (curl) {
        std::unique_ptr<curl_httppost, void(*)(curl_httppost*)> formpost([&fieldname, &filename]{
            curl_httppost *formpost = nullptr;
            curl_httppost *lastptr = nullptr;
                
            curl_formadd(&formpost,
                         &lastptr,
                         CURLFORM_COPYNAME, fieldname.c_str(),
                         CURLFORM_FILE, filename.c_str(),
                         CURLFORM_END);
            
            return formpost;
        }(), curl_formfree);
        
        curl_easy_setopt(curl.get(), CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_1);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, string_writer);
        curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl.get(), CURLOPT_HTTPPOST, formpost.get());
        
        res = curl_easy_perform(curl.get());
        
        if (res != CURLE_OK){
            logger->log(res);
            return "";
        }
    }
    
    return readBuffer;
}

size_t Network::string_writer(char* contents, size_t size, size_t nmemb, std::string* stream) {
    stream->append(contents, size * nmemb);
    return size * nmemb;
}

size_t Network::file_writer(void* contents, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(contents, size, nmemb, stream);
    return written;
}

std::string Network::join(const std::vector<std::string> lst, const std::string& delim) const {
    std::ostringstream ss;
    for(size_t i = 0; i < lst.size(); i++)
        ss << lst[i] << (i + 1 == lst.size() ? "" : delim);
    return ss.str();
}

std::string Network::url_encode(const std::string& str) const {
    std::unique_ptr<CURL, void(*)(CURL*)> curl { curl_easy_init(), curl_easy_cleanup };
    std::unique_ptr<char, void(*)(void*)> data {
        curl_easy_escape(curl.get(), str.c_str(), static_cast<int>(str.size())),
        curl_free
    };

    return data ? std::string(data.get()) : str;
}

void Network::set_logger(std::shared_ptr<ILogger> obj) {
    logger = obj;
}

std::shared_ptr<ILogger> Network::get_logger() {
    return logger;
}
