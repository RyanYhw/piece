#include "iniconf.h"

#include <fstream>
#include <iostream>

const int INI_SUCCESS = 0;
const int INI_NULL_FILE         = -1;
const int INI_CAN_NOT_OPEN_FILE = 1;

const char comment_pound = '#';
const char comment_semicolon = ';';
const char comment_backslash = 0x5C;

static void erase_comment(std::string & line, const char comment) {
    auto pos = line.find(comment);
    if (pos != std::string::npos) { 
        line.erase(pos);
    }
}

static void erase_prefix_and_subfix_spaces(std::string & word) {
    word.erase(0, word.find_first_not_of(' '));
    word.erase(word.find_last_not_of(' ')+1);

    word.erase(0, word.find_first_not_of('\t'));
    word.erase(word.find_last_not_of('\t')+1);
}

static std::string get_current_session(const std::string & line) {
    size_t pos_f = line.find('[');
    size_t pos_e = line.find(']');

    if (pos_f == std::string::npos || 
        pos_e == std::string::npos || 
        pos_f >= pos_e) {
        return "";
    }
    std::string session = line.substr(pos_f+1, pos_e - pos_f - 1);
    if (!session.empty()) {
        erase_prefix_and_subfix_spaces(session);
    }
    return session;
}

INIConfigParser::INIConfigParser() {}

int INIConfigParser::parse(const char * file) {
    if (nullptr == file) {
        return INI_NULL_FILE;
    }

    std::fstream f(file, std::ios_base::binary | std::ios_base::in);
    if (!f.is_open()) return INI_CAN_NOT_OPEN_FILE;

    std::string line;
    std::string current_session(default_session);
    while (std::getline(f, line)) {
        parseLine(line, current_session);
    }

    f.close();
    return INI_SUCCESS;
}

void INIConfigParser::parseLine(const std::string &line, 
                                std::string& current_session) {
    std::string tmp = line;
    // 去掉开始的空格
    tmp.erase(0, tmp.find_first_not_of(' '));
    // 去掉注释
    erase_comment(tmp, comment_pound);
    erase_comment(tmp, comment_semicolon);
    if (tmp.empty()) return;
    
    // 获取session
    {
        std::string session = get_current_session(tmp);
        if (!session.empty()) {
            current_session = std::move(session);
            return;
        }
    }
    size_t pos = tmp.find('=');
    
    if (pos != std::string::npos) {
        std::string key;
        std::string value;
        key = tmp.substr(0, pos-1);
        value = tmp.substr(pos + 1);

        erase_prefix_and_subfix_spaces(key);
        erase_prefix_and_subfix_spaces(value);
        
        std::cout << "key = " << key << " value = " << value << "\n";
        auto it = ini_.find(current_session);
        if (it == ini_.end()) {
            std::shared_ptr<session_t> s(new session_t);
            s->pairs_[std::move(key)] = std::move(value);
            ini_[current_session] = std::move(s);
        } else {
            it->second->pairs_[std::move(key)] = std::move(value);
        }
    }
}

std::string INIConfigParser::get_value(const std::string& key, 
                                       const std::string & session) const {
        std::string sname (default_session);
        if (!session.empty()) { sname = session; } 

        MapINI::const_iterator session_it = ini_.find(sname);
        if (session_it == ini_.end()) { return ""; }

        auto it = session_it->second->pairs_.find(key);
        if (it == session_it->second->pairs_.end()) { return ""; }
        return it->second;
    }

std::shared_ptr<session_t> INIConfigParser::getSessionValues(const std::string& session) {
    std::shared_ptr<session_t> s;
    auto it = ini_.find(session);
    if (it != ini_.end()) {
        s = it->second;
    }
    return s;
}
