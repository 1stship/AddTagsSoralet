#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>

#include <emscripten.h>
#include "soracom/orbit.h"

#include "nlohmann/json.hpp"
using nlohmann::json;

int32_t uplink_body();

extern "C" {

EMSCRIPTEN_KEEPALIVE
int32_t uplink() {
    return uplink_body();
}

}

std::string get_tag(const std::string& tag_name) {
    const char* tag_value = NULL;
    size_t tag_value_len = 0;
    int32_t err = soracom_get_tag_value(tag_name.c_str(), tag_name.size(), &tag_value, &tag_value_len);
    if (err < 0) {
        return "";
    }

    return std::string(tag_value);
}

std::vector<std::string> split(std::string& input, char delimiter)
{
    std::istringstream stream(input);
    std::string field;
    std::vector<std::string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int32_t uplink_body() {
    const char* buf = NULL;
    size_t siz = 0;
    int32_t err = soracom_get_input_buffer_as_string(&buf, &siz);
    if (err < 0) {
        return err;
    }
    json j = json::parse(buf);
    soracom_release_input_buffer(buf);

    std::string tagNames = get_tag("tags");
    std::vector<std::string> tags = split(tagNames, ',');

    for (int i = 0; i < tags.size(); i++){
        std::string tagName = tags.at(i);
        std::string tagValue = get_tag(tagName);
        j[tagName] = tagValue;
    }

    std::string output = j.dump();
    soracom_set_json_output(output.c_str(), output.size());

    return 0;
}
