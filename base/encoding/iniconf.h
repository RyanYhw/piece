#ifndef ONEPIECE_BASE_ENCODING_INICONF_H_
#define ONEPIECE_BASE_ENCODING_INICONF_H_

#include <map>
#include <string>
#include <memory>

#include "base/noncopyable.h"
#include "base/common.h"

/*!
    v1.0.1 根据当前需求, 仅仅做初级配置文件使用
    1. # 和 ; 作为注释
    2. [] 作为 session 字段
    3. 格式为 key = value 模式
    4. 会忽略开始和结尾的'空格'和'\t'
    5. 不区分整数和字符串, 因此 引号会被作为字段的一部分

    不支持
    1. 转义字符如 \# \; \[ \] 等等
    2. 不支持嵌套的session
    3. 不支持数组

    示例:
    test.ini start
        ; 测试使用

        # 单位为毫秒
        timeout = 100

        [ap]
            port = 145  ; ap 端口
            host = vrv.linkdood.cn ; ap 服务端地址
    test.ini end
 */
const char * default_session = "global";


typedef struct session_s {
    std::map <std::string, std::string> pairs_;
} session_t;

class INIConfigParser : public noncopyable {
    using MapINI = std::map<std::string, std::shared_ptr<session_t>>;
public:
    INIConfigParser();
    ~INIConfigParser() = default;

    /**
     *  @param file full path of ini file
     *  @return 0 for success, -1 file is nullptr, 1 can not open file
     */ 
    int parse(const char * file);

    template <class T>
    bool getValue(T & v, const std::string& key,  
                  const std::string & session = "") const {
        std::string value = get_value(key, session);
        if (value.empty()) {
            return false;
        }
        v = convert<T>(value);
        return true;
    }

    template <class T>
    bool getValue(std::string& v, const std::string &key,  
                  std::string& session = "") const {
        v = get_value(key, session);
        return !v.empty();
    }

    std::shared_ptr<session_t> getSessionValues(const std::string& session);
private:
    void parseLine(const std::string& line, std::string& current_session);
    std::string get_value(const std::string& key, const std::string & session) const;
private:
    MapINI ini_;
};

#endif  // ONEPIECE_BASE_ENCODING_INICONF_H_