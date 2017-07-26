/*
 * FileName : pcl_main.cpp
 * Author   : Pengcheng Liu(Lpc-Win32)
 * Date     : Wed 26 Jul 2017 02:27:38 PM CST   Created
*/

#include <pcl/pcl.h>

#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "argc must equal 2" << std::endl;
        return -1;
    }

    pcl::pclCls *pcl_ptr = pcl::pclCls::get_instance();
    if (nullptr == pcl_ptr) {
        std::cout << "pclCls get_instance failure" << std::endl;
        return -1;
    }

    if (0 != pcl_ptr->pcl_init(argv[1])) {
        std::cout << "pcl_init failure" << std::endl;
        return -1;
    }

    pcl::pclMgr *pcl_mgr_ptr = pcl::pclMgr::get_instance();
    if (nullptr == pcl_mgr_ptr) {
        std::cout << "pcl_mgr get_instance failure" << std::endl;
        return -1;
    }

    pcl_mgr_ptr->printAllPcl();

    std::string name_ = pcl_mgr_ptr->kvStr("default", "name");

    return 0;
}
