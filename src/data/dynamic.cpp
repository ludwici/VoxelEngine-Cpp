#include "dynamic.h"

#include <stdexcept>

using namespace dynamic;

List::~List() {
}

std::string List::str(size_t index) const {
    const auto& val = values[index];
    switch (val->type) {
        case valtype::string: return std::get<std::string>(val->value);
        case valtype::boolean: return std::get<bool>(val->value) ? "true" : "false";
        case valtype::number: return std::to_string(std::get<double>(val->value));
        case valtype::integer: return std::to_string(std::get<int64_t>(val->value));
        default:
            throw std::runtime_error("type error");
    }
}

number_t List::num(size_t index) const {
    const auto& val = values[index];
    switch (val->type) {
        case valtype::number: return std::get<number_t>(val->value);
        case valtype::integer: return std::get<integer_t>(val->value);
        case valtype::string: return std::stoll(std::get<std::string>(val->value));
        case valtype::boolean: return std::get<bool>(val->value);
        default:
            throw std::runtime_error("type error");
    }
}

integer_t List::integer(size_t index) const {
    const auto& val = values[index];
    switch (val->type) {
        case valtype::number: return std::get<number_t>(val->value);
        case valtype::integer: return std::get<integer_t>(val->value);
        case valtype::string: return std::stoll(std::get<std::string>(val->value));
        case valtype::boolean: return std::get<bool>(val->value);
        default:
            throw std::runtime_error("type error");
    }
}

Map* List::map(size_t index) const {
    if (values[index]->type != valtype::map) {
        throw std::runtime_error("type error");
    }
    return std::get<Map*>(values[index]->value);
}

List* List::list(size_t index) const {
    if (values[index]->type != valtype::list) {
        throw std::runtime_error("type error");
    }
    return std::get<List*>(values[index]->value);
}

bool List::flag(size_t index) const {
    const auto& val = values[index];
    switch (val->type) {
        case valtype::integer: return std::get<integer_t>(val->value);
        case valtype::boolean: return std::get<bool>(val->value);
        default:
            throw std::runtime_error("type error");
    }
}

Value* List::getValueWriteable(size_t index) const {
    if (index > values.size()) {
        throw std::runtime_error("index error");
    }
    return values.at(index).get();
}

List& List::put(std::string value) {
    values.push_back(std::make_unique<Value>(valtype::string, value));
    return *this;
}

List& List::put(uint value) {
    return put((int64_t)value);
}

List& List::put(int value) {
    return put((int64_t)value);
}

List& List::put(int64_t value) {
    values.push_back(std::make_unique<Value>(valtype::integer, value));
    return *this;
}

List& List::put(uint64_t value) {
    return put((int64_t)value);
}

List& List::put(double value) {
    values.push_back(std::make_unique<Value>(valtype::number, value));
    return *this;
}

List& List::put(float value) {
    return put((double)value);
}

List& List::put(bool value) {
    values.push_back(std::make_unique<Value>(valtype::boolean, value));
    return *this;
}

List& List::put(Map* value) {
    values.push_back(std::make_unique<Value>(valtype::map, value));
    return *this;
}

List& List::put(List* value) {
    values.push_back(std::make_unique<Value>(valtype::list, value));
    return *this;
}

List& List::putList() {
    List* arr = new List();
    put(arr);
    return *arr;
}

Map& List::putMap() {
    Map* map = new Map();
    put(map);
    return *map;
}

void List::remove(size_t index) {
    values.erase(values.begin() + index);
}

Map::~Map() {
}

void Map::str(std::string key, std::string& dst) const {
    dst = getStr(key, dst);
}

std::string Map::getStr(std::string key) const {
    if (values.find(key) == values.end()) {
        throw std::runtime_error("missing key '"+key+"'");
    }
    return getStr(key, "");
}

double Map::getNum(std::string key) const {
    if (values.find(key) == values.end()) {
        throw std::runtime_error("missing key '"+key+"'");
    }
    return getNum(key, 0);
}

int64_t Map::getInt(std::string key) const {
    if (values.find(key) == values.end()) {
        throw std::runtime_error("missing key '"+key+"'");
    }
    return getInt(key, 0);
}

bool Map::getBool(std::string key) const {
    if (values.find(key) == values.end()) {
        throw std::runtime_error("missing key '"+key+"'");
    }
    return getBool(key, false);
}

std::string Map::getStr(std::string key, const std::string& def) const {
    auto found = values.find(key);
    if (found == values.end())
        return def;
    auto& val = found->second;
    switch (val->type) {
        case valtype::string: return std::get<std::string>(val->value);
        case valtype::boolean: return std::get<bool>(val->value) ? "true" : "false";
        case valtype::number: return std::to_string(std::get<number_t>(val->value));
        case valtype::integer: return std::to_string(std::get<integer_t>(val->value));
        default: throw std::runtime_error("type error");
    } 
}

number_t Map::getNum(std::string key, double def) const {
    auto found = values.find(key);
    if (found == values.end())
        return def;
    auto& val = found->second;
    switch (val->type) {
        case valtype::number: return std::get<number_t>(val->value);
        case valtype::integer: return std::get<integer_t>(val->value);
        case valtype::string: return std::stoull(std::get<std::string>(val->value));
        case valtype::boolean: return std::get<bool>(val->value);
        default: throw std::runtime_error("type error");
    }
}

integer_t Map::getInt(std::string key, integer_t def) const {
    auto found = values.find(key);
    if (found == values.end())
        return def;
    auto& val = found->second;
    switch (val->type) {
        case valtype::number: return std::get<number_t>(val->value);
        case valtype::integer: return std::get<integer_t>(val->value);
        case valtype::string: return std::stoull(std::get<std::string>(val->value));
        case valtype::boolean: return std::get<bool>(val->value);
        default: throw std::runtime_error("type error");
    }
}

bool Map::getBool(std::string key, bool def) const {
    auto found = values.find(key);
    if (found == values.end())
        return def;
    auto& val = found->second;
    switch (val->type) {
        case valtype::integer: return std::get<integer_t>(val->value);
        case valtype::boolean: return std::get<bool>(val->value);
        default: throw std::runtime_error("type error");
    }
}

void Map::num(std::string key, double& dst) const {
    dst = getNum(key, dst);
}

void Map::num(std::string key, float& dst) const {
    dst = getNum(key, dst);
}

void Map::num(std::string key, ubyte& dst) const {
    dst = getInt(key, dst);
}

void Map::num(std::string key, int& dst) const {
    dst = getInt(key, dst);
}

void Map::num(std::string key, int64_t& dst) const {
    dst = getInt(key, dst);
}

void Map::num(std::string key, uint64_t& dst) const {
    dst = getInt(key, dst);
}

void Map::num(std::string key, uint& dst) const {
    dst = getInt(key, dst);
}

Map* Map::map(std::string key) const {
    auto found = values.find(key);
    if (found != values.end()) {
        auto& val = found->second;
        if (val->type != valtype::map)
            return nullptr;
        return std::get<Map*>(val->value);
    }
    return nullptr;
}

List* Map::list(std::string key) const {
    auto found = values.find(key);
    if (found != values.end())
        return std::get<List*>(found->second->value);
    return nullptr;
}

void Map::flag(std::string key, bool& dst) const {
    dst = getBool(key, dst);
}

Map& Map::put(std::string key, uint value) {
    return put(key, (int64_t)value);
}

Map& Map::put(std::string key, int value) {
    return put(key, (int64_t)value);
}

Map& Map::put(std::string key, int64_t value) {
    values[key] = std::make_unique<Value>(valtype::integer, value);
    return *this;
}

Map& Map::put(std::string key, uint64_t value) {
    return put(key, (int64_t)value);
}

Map& Map::put(std::string key, float value) {
    return put(key, (double)value);
}

Map& Map::put(std::string key, double value) {
    values[key] = std::make_unique<Value>(valtype::number, value);
    return *this;
}

Map& Map::put(std::string key, std::string value){
    values[key] = std::make_unique<Value>(valtype::string, value);
    return *this;
}

Map& Map::put(std::string key, const char* value) {
    return put(key, std::string(value));
}

Map& Map::put(std::string key, Map* value){
    values[key] = std::make_unique<Value>(valtype::map, value);
    return *this;
}

Map& Map::put(std::string key, List* value){
    values[key] = std::make_unique<Value>(valtype::list, value);
    return *this;
}

Map& Map::put(std::string key, bool value){
    values[key] = std::make_unique<Value>(valtype::boolean, value);
    return *this;
}

List& Map::putList(std::string key) {
    List* arr = new List();
    put(key, arr);
    return *arr;
}

Map& Map::putMap(std::string key) {
    Map* obj = new Map();
    put(key, obj);
    return *obj;
}

bool Map::has(std::string key) {
    return values.find(key) != values.end();
}

Value::Value(valtype type, valvalue value) : type(type), value(value) {
}

Value::~Value() {
    switch (type) {
        case valtype::map: delete std::get<Map*>(value); break;
        case valtype::list: delete std::get<List*>(value); break;
        default:
            break;
    }
}

Value Value::boolean(bool value) {
    return Value(valtype::boolean, value);
}

Value Value::of(number_u value) {
    if (std::holds_alternative<integer_t>(value)) {
        return Value(valtype::integer, std::get<integer_t>(value));
    } else {
        return Value(valtype::number, std::get<number_t>(value));
    }
}

Value Value::of(const std::string& value) {
    return Value(valtype::string, value);
}
