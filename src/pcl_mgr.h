/*
 * FileName : pcl_mgr.h
 * Author   : Pengcheng Liu(Lpc-Win32)
 * Date     : Mon 24 Jul 2017 02:19:17 PM CST   Created
*/

#pragma once

#include "pcl_table.h"
#include <list>
#include <string>

namespace pcl
{
    class pclMgr
    {
        public:
            pclMgr(const pclMgr &other) = delete;

            pclMgr *operator=(const pclMgr &other) = delete;

            static pclMgr *get_instance();

            int add_table(const std::string table_name);

            int insert_kv(std::string key, std::string value);

            pclTable *get_table();

            std::string kvStr(const std::string table_name, const std::string key) const;

            int kvInt(const std::string table_name, const std::string key) const;

            void printAllPcl() const;
        private:
            pclMgr() noexcept;

            std::list<pcl::pclTable *> pcl_table_list_;
    };
}
