#ifndef CURLY_HPP
#define CURLY_HPP

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <cctype>

namespace curly {

class json {
public:
    enum Type {
        Null,
        Boolean,
        Number,
        String,
        Array,
        Object
    };

private:
    Type type;
    bool boolValue;
    double numberValue;
    std::string stringValue;
    std::vector<json> arrayValue;
    std::map<std::string, json> objectValue;

public:
    // Конструкторы
    json() : type(Null), boolValue(false), numberValue(0.0) {}
    json(bool b) : type(Boolean), boolValue(b), numberValue(0.0) {}
    json(double n) : type(Number), boolValue(false), numberValue(n) {}
    json(int n) : type(Number), boolValue(false), numberValue(static_cast<double>(n)) {}
    json(const std::string& s) : type(String), boolValue(false), numberValue(0.0), stringValue(s) {}
    json(const char* s) : type(String), boolValue(false), numberValue(0.0), stringValue(s) {}

    // Получение типа
    Type getType() const { return type; }

    // Операторы доступа
    json& operator[](const std::string& key) {
        if (type != Object) type = Object;
        return objectValue[key];
    }

    const json& operator[](const std::string& key) const {
        static json null;
        auto it = objectValue.find(key);
        return (it != objectValue.end()) ? it->second : null;
    }

    json& operator[](size_t index) {
        if (type != Array) type = Array;
        if (index >= arrayValue.size()) {
            arrayValue.resize(index + 1);
        }
        return arrayValue[index];
    }

    const json& operator[](size_t index) const {
        static json null;
        return (index < arrayValue.size()) ? arrayValue[index] : null;
    }

    // Преобразования типов
    std::string asString() const {
        if (type == String) return stringValue;
        if (type == Null) return "null";
        if (type == Boolean) return boolValue ? "true" : "false";
        if (type == Number) {
            std::ostringstream oss;
            oss << numberValue;
            return oss.str();
        }
        return "";
    }

    double asNumber() const {
        return (type == Number) ? numberValue : 0.0;
    }

    bool asBoolean() const {
        return (type == Boolean) ? boolValue : false;
    }

    // Оператор преобразования
    operator std::string() const { return asString(); }
    operator double() const { return asNumber(); }
    operator bool() const { return asBoolean(); }

    // Парсинг JSON
    static json parse(const std::string& jsonStr) {
        size_t pos = 0;
        return parseValue(jsonStr, pos);
    }

private:
    static json parseValue(const std::string& str, size_t& pos) {
        skipWhitespace(str, pos);

        if (pos >= str.length()) return json();

        char ch = str[pos];

        if (ch == '{') return parseObject(str, pos);
        if (ch == '[') return parseArray(str, pos);
        if (ch == '"') return parseString(str, pos);
        if (ch == 't' || ch == 'f') return parseBoolean(str, pos);
        if (ch == 'n') return parseNull(str, pos);
        if (ch == '-' || isdigit(ch)) return parseNumber(str, pos);

        return json();
    }

    static json parseObject(const std::string& str, size_t& pos) {
        json obj;
        obj.type = Object;
        pos++; // пропустить '{'

        skipWhitespace(str, pos);
        if (pos < str.length() && str[pos] == '}') {
            pos++;
            return obj;
        }

        while (pos < str.length()) {
            skipWhitespace(str, pos);
            std::string key = parseString(str, pos).asString();
            skipWhitespace(str, pos);

            if (pos < str.length() && str[pos] == ':') {
                pos++;
                skipWhitespace(str, pos);
                obj.objectValue[key] = parseValue(str, pos);
            }

            skipWhitespace(str, pos);
            if (pos < str.length() && str[pos] == ',') {
                pos++;
            } else if (pos < str.length() && str[pos] == '}') {
                pos++;
                break;
            }
        }

        return obj;
    }

    static json parseArray(const std::string& str, size_t& pos) {
        json arr;
        arr.type = Array;
        pos++; // пропустить '['

        skipWhitespace(str, pos);
        if (pos < str.length() && str[pos] == ']') {
            pos++;
            return arr;
        }

        while (pos < str.length()) {
            arr.arrayValue.push_back(parseValue(str, pos));
            skipWhitespace(str, pos);

            if (pos < str.length() && str[pos] == ',') {
                pos++;
            } else if (pos < str.length() && str[pos] == ']') {
                pos++;
                break;
            }
        }

        return arr;
    }

    static json parseString(const std::string& str, size_t& pos) {
        pos++; // пропустить открывающую кавычку
        std::string result;

        while (pos < str.length() && str[pos] != '"') {
            if (str[pos] == '\\' && pos + 1 < str.length()) {
                pos++;
                if (str[pos] == 'n') result += '\n';
                else if (str[pos] == 't') result += '\t';
                else if (str[pos] == 'r') result += '\r';
                else if (str[pos] == '"') result += '"';
                else if (str[pos] == '\\') result += '\\';
                else result += str[pos];
            } else {
                result += str[pos];
            }
            pos++;
        }

        if (pos < str.length()) pos++; // пропустить закрывающую кавычку
        return json(result);
    }

    static json parseNumber(const std::string& str, size_t& pos) {
        size_t start = pos;
        if (str[pos] == '-') pos++;
        while (pos < str.length() && (isdigit(str[pos]) || str[pos] == '.')) pos++;
        return json(std::stod(str.substr(start, pos - start)));
    }

    static json parseBoolean(const std::string& str, size_t& pos) {
        if (str.substr(pos, 4) == "true") {
            pos += 4;
            return json(true);
        } else if (str.substr(pos, 5) == "false") {
            pos += 5;
            return json(false);
        }
        return json();
    }

    static json parseNull(const std::string& str, size_t& pos) {
        if (str.substr(pos, 4) == "null") {
            pos += 4;
        }
        return json();
    }

    static void skipWhitespace(const std::string& str, size_t& pos) {
        while (pos < str.length() && isspace(str[pos])) pos++;
    }
};

} // namespace curly

#endif // CURLY_HPP
