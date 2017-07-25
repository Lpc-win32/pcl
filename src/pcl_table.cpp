/*
 * FileName : pcl_table.cpp
 * Author   : Pengcheng Liu(Lpc-Win32)
 * Date     : Wed 19 Jul 2017 05:33:04 PM CST   Created
*/

#include "pcl_table.h"

#include <iostream>

using namespace pcl;

int pclTable::set_name(std::string name)
{
    if (name.length() == 0) {
        pcl_table_name_ = "global";
    } else {
        pcl_table_name_ = name;
    }
    return 0;
}

int pclTable::insert_map(std::string key, std::string val)
{
    std::string str_ret = kv_map_[key];
    if (str_ret.length() != 0) {
        return -1;
    }
    kv_map_[key] = val;

    return 0;
}

std::string pclTable::get_name() const
{
    return pcl_table_name_;
}

std::string pclTable::get_val(std::string key)
{
    return kv_map_[key];
}

void pclTable::printKv() const
{
    std::cout << "Table Name : " << pcl_table_name_ << std::endl;
    for (auto map_node : kv_map_) {
        std::cout << map_node.first << " = " << map_node.second << std::endl;
    }
}
