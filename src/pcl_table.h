/*
 * FileName : pcl_table.h
 * Author   : Pengcheng Liu(Lpc-Win32)
 * Date     : Wed 19 Jul 2017 04:54:46 PM CST   Created
*/

#include <map>
#include <string>

#pragma once

namespace pcl
{
    class pclTable {
        public:
            pclTable() = default;
            pclTable(const pclTable &other) = delete;
            pclTable &operator=(const pclTable &other) = delete;

            int set_name(const std::string name);
            int insert_map(const std::string key, const std::string val);

            std::string get_name() const;
            std::string get_val(std::string key);

            void printKv() const;
        private:
            std::string                        pcl_table_name_;
            std::map<std::string, std::string> kv_map_;
    };
}
