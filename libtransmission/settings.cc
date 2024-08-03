#include "settings.h"

#include <iostream>
#include <nlohmann/json.hpp>
#include "file.h" // tr_sys_path_exists
#include "log.h" // tr_logAddDebug
#include "tr-strbuf.h" // tr_pathbuf
#include "transmission.h" // tr_getDefaultConfigDir

using namespace std::literals::string_view_literals; // ""sv operator
using json = nlohmann::json;

namespace
{
namespace settings_helpers
{

std::filesystem::path const get_settings_filename(char const* config_dir, char const* appname)
{
    std::string const& config_dir_ = config_dir;
    std::string const& app_name = appname;
    if (not config_dir_.empty())
    {
        return config_dir_ + "/settings.json";
    }

    std::string const& default_config_dir = tr_getDefaultConfigDir(app_name);
    return default_config_dir + "/settings.json";
}

} // namespace settings_helpers
} // namespace

namespace transmission
{

bool Settings::Load(char const* config_dir, char const* app_name)
{
    using namespace settings_helpers;

    /* file settings override the defaults */
    auto success = bool{};
    auto filename = get_settings_filename(config_dir, app_name);
    if (!tr_sys_path_exists(filename))
    {
        success = true;
    }
    else if (this->LoadFromFile(TR_VARIANT_PARSE_JSON, filename))
    {
        success = true;
    }
    else
    {
        success = false;
    }

    /* cleanup */
    return success;
}

bool Settings::LoadFromFile(tr_variant_parse_opts opts, std::filesystem::path const& filename)
{
    auto success = false;

    // supported formats: benc, json
    TR_ASSERT((opts & (TR_VARIANT_PARSE_BENC | TR_VARIANT_PARSE_JSON)) != 0);

    std::ifstream file_contents(filename);

    /*auto const success = ((opts & TR_VARIANT_PARSE_BENC) != 0) ? tr_variantParseBenc(*setme, opts, buf, setme_end, error) :
                                                                 tr_variantParseJson(*setme, opts, buf, setme_end, error);*/
    if ((opts & TR_VARIANT_PARSE_BENC) != 0)
    {
    }
    else
    {
        return this->ParseJson(file_contents);
    }

    return success;
}

bool Settings::ParseJson(std::ifstream& file_contents)
{
    auto const success = true;

    json data = json::parse(file_contents);

    return success;
}

} // namespace transmission
