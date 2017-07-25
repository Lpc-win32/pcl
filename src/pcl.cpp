/*
 * FileName : pcl.cpp
 * Author   : Pengcheng Liu(Lpc-Win32)
 * Date     : Thu 20 Jul 2017 03:57:36 PM CST   Created
*/

#include "pcl.h"

#include <fstream>
#include <string.h>
#include <vector>
#include <string>

using namespace pcl;

pclCls *pclCls::get_instance()
{
    static pclCls *pcl_obj_ = new pclCls;
    return pcl_obj_;
}

int pclCls::pcl_init(std::string pcl_)
{
    if (pcl_.length() == 0) {
        return -1;
    }
    pcl_file_ = pcl_;

    read_pcl();

    return 0;
}

static void split(std::vector<std::string> &result, const std::string &str, const std::string delim)
{
    char *tmp = strdup(str.c_str());
    char *s = tmp;
    char *token;
    for (token = strsep(&s, delim.c_str()); token != NULL;
            token = strsep(&s, delim.c_str())) {
        if (token[0] != '\0') {
            result.push_back(token);
        }
    }
    free(tmp);
}

// 去首尾空格
static void str_trunc(std::string &line)
{
    int pos = line.length();
    if (pos <= 0) {
        return;
    }
    
    int count = 0;
    while (line[pos-1] == SPACE) {
        --pos;
        ++count;
    }
    line.replace(pos, count, "");

    pos = 0;
    count = 0;
    while (line[pos] == SPACE) {
        ++pos;
        ++count;
    }
    line.replace(0, count, "");
}

// 去除首尾引号
static void str_trunc_quotation_marks(std::string &line)
{
    if (line[0] == '"' && line[line.length() - 1] == '"') {
        int pos = line.length() - 1;
        line.replace(pos, 1, "");
        line.replace(0, 1, "");
    }
}

// 过滤注释内容，注释内容可在行尾，可独占一行
static void str_ignore_annotation(std::string &value)
{
    // 忽略在引号中的#
    // 1. 清除首尾空格
    str_trunc(value);
    if (value.at(0) == '"') {
        // 找到后面的"
        int qm_pos = 0;
        for (unsigned int i = 1; i < value.length(); i++) {
            if (value.at(i) == '"') {
                if (value.at(i-1) == '\\') {
                    continue;
                } else {
                    qm_pos = i;
                    break;
                }
            }
        }
        if (qm_pos == 0) {
            value = "";
            return;
        } else {
            value = value.substr(0, qm_pos);
            str_trunc_quotation_marks(value);
            return;
        }
    } else {
        // 直接寻找SPACE#
        size_t pos = value.find(" #");
        if (pos == std::string::npos) {
            return;
        } else {
            value = value.substr(0, pos);
            str_trunc(value);
            return;
        }
    }
}

// 判断当前行是否为纯注释行
static bool is_pure_annotation(std::string &line)
{
    return line.at(0) == '#' ? true : false;
}

// 判断当前key的命名是否合法，key的命名规则同c语言
static bool is_key_legal(std::string &key)
{
    if (key.length() == 0) {
        return false;
    }
    for (unsigned int i = 0; i < key.length(); i++) {
        if (i == 0) {
            if ((key[i] < 'A' && key[i] > 'Z') ||
                (key[i] < 'a' && key[i] > 'z') ||
                (key[i] != '_')) {
                return false;
            }
        } else {
            if ((key[i] < '0' && key[i] > '9') ||
                (key[i] < 'A' && key[i] > 'Z') ||
                (key[i] < 'a' && key[i] > 'z') ||
                (key[i] != '_')) {
                return false;
            }
        }
    }

    return true;
}

// 判断当前行是否用于创建新的table
static bool is_table(std::string &line)
{
    int pos_start = line.find('[');
    if (pos_start == -1) {
        return false;
    }
    int pos_end   = line.find(']');
    if (pos_end == -1) {
        return false;
    }
    if ((pos_start > pos_end) ||
        ((pos_end - 1) == pos_start)) {
        return false;
    }
    line = line.substr(pos_start + 1, pos_end - 1);
    // 清除line的首尾空格
    str_trunc(line);
    if (!is_key_legal(line)) {
        return false;
    }
    return true;
}

static int deal_with_line(std::string line)
{
    // 清除首尾空格
    str_trunc(line);
    
    // 去除首尾引号
    str_trunc_quotation_marks(line);

    if (line.length() == 0) {
        return 0;
    }

    // 判断当前行是否为纯注释行
    if (is_pure_annotation(line)) {
        return 0;
    }

    // 判断当前行是否为[table]
    if (is_table(line)) {
        pclMgr::get_instance()->add_table(line);
        return 0;
    }

    // 提取key and val
    std::vector<std::string> kv;
    split(kv, line, "=");

    // 取value出来单独作处理
    std::string value;

    // 对key进行trunc操作
    str_trunc(kv[0]);
    str_trunc_quotation_marks(kv[0]);
    // 判断key名称是否合法
    if (!is_key_legal(kv[0])) {
        return 0;
    }

    if (2 == kv.size()) {
        // 有kv数据，获取匹配的pclTable对象
        value = kv[1];
    } else if (1 == kv.size()) {
        // do nothing.....
        value = kv[0];
    } else if (kv.size() > 2) {
        // 将value的值取出来
        for (unsigned int i = 1; i < kv.size(); i++) {
            value += kv[i] + "=";
        }
    }

    // 过滤注释内容，注释内容为#.....
    str_ignore_annotation(value);

    str_trunc(value);
    str_trunc_quotation_marks(value);

    // 将kv插入相应的table中
    pclMgr::get_instance()->insert_kv(kv[0], value);

    return 0;
}

int pclCls::read_pcl()
{
    if (pcl_file_.length() == 0) {
        return -1;
    }
    // open a file
    std::fstream pcl_f;
    pcl_f.open(pcl_file_);

    std::string pcl_line;
    
    while (std::getline(pcl_f, pcl_line)) {
        deal_with_line(pcl_line);
    }

    pcl_f.close();

    return 0;
}

