#pragma once

/*#ifndef __TRANSMISSION__
#error only libtransmission should #include this header.
#endif*/

#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <variant>

//#include "net.h" // tr_port
#include "tr-assert.h" // TR_ASSERT
#include "utils.h" // tr_str_is_empty
#include "variant.h" // tr_variant_parse_opts

namespace transmission
{

using setting = std::variant<bool, int, double, size_t, std::string>;
using settings = std::map<std::string, setting>;

class Settings
{
public:
    bool Load(char const*, char const*);
    bool LoadFromFile(tr_variant_parse_opts, std::filesystem::path const&);

    settings* GetSettings()
    {
        return &this->_settings;
    }

    template<typename T>
    void set(std::string key, T value, std::string comment = "")
    {
        this->_settings.insert_or_assign(key, value);
        this->_comments.insert_or_assign(key, comment);
    };

    template<typename T>
    T get(std::string key)
    {
        return this->_settings[key];
    };

private:
    settings _settings;
    std::map<std::string, std::string> _comments;

    bool ParseJson(std::ifstream&);
};

} // namespace transmission
