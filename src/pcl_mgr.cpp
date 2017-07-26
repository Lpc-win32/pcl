/*
 * FileName : pcl_mgr.cpp
 * Author   : Pengcheng Liu(Lpc-Win32)
 * Date     : Mon 24 Jul 2017 02:35:30 PM CST   Created
*/

#include "pcl_mgr.h"

#include <iostream>
#include <stdlib.h>

using namespace pcl;

pclMgr::pclMgr() noexcept
{
    pclTable *default_table = new pclTable();
    default_table->set_name("default");
    pcl_table_list_.push_back(default_table);
}

pclMgr *pclMgr::get_instance()
{
    static pclMgr *pcl_mgr_ptr = new pclMgr();
    return pcl_mgr_ptr;
}

int pclMgr::add_table(std::string table_name)
{
    std::list<pcl::pclTable *>::iterator list_iter;
    for (list_iter = pcl_table_list_.begin(); list_iter != pcl_table_list_.end(); ++list_iter) {
        if (table_name == (*list_iter)->get_name()) {
            break;
        }
    }

    if ((list_iter != pcl_table_list_.end())) {
        // 需要将当前list_node替换到结尾
        pclTable *tmp = *list_iter;
        pcl_table_list_.erase(list_iter);
        pcl_table_list_.push_back(tmp);
    } else {
        pclTable *new_table = new pclTable();
        new_table->set_name(table_name);
        pcl_table_list_.push_back(new_table);
    }

    return 0;
}

int pclMgr::insert_kv(std::string key, std::string val)
{
    pclTable *pcl_table_ptr = get_table();
    if (nullptr == pcl_table_ptr)  {
        std::cout << "INSERT KV ERROR: pcl_table_list_ is empty" << std::endl;
        return -1;
    }
    pcl_table_ptr->insert_map(key, val);

    return 0;
}

pclTable *pclMgr::get_table()
{
    if (pcl_table_list_.size() == 0) {
        return nullptr;
    }
    return pcl_table_list_.back();
}

std::string pclMgr::kvStr(const std::string table_name, const std::string key) const
{
    for (auto list_node : pcl_table_list_) {
        if (list_node->get_name() == table_name) {
            return list_node->get_val(key);
        }
    }
    std::string empty_str;
    return empty_str;
}

int pclMgr::kvInt(const std::string table_name, const std::string key) const
{
    return atoi(kvStr(table_name, key).c_str());
}

void pclMgr::printAllPcl() const
{
    for (auto list_node : pcl_table_list_) {
        list_node->printKv();
    }
}
