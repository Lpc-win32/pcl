/*
 * FileName : pcl.h
 * Author   : Pengcheng Liu(Lpc-Win32)
 * Date     : Wed 19 Jul 2017 07:39:18 PM CST   Created
*/

#pragma once

#include "pcl_mgr.h"

namespace pcl
{
    #define SPACE ' '

    class pclCls
    {
        public:
            pclCls(const pclCls &other) = delete;

            pclCls &operator=(const pclCls &other) = delete;

            static pclCls *get_instance();

            int pcl_init(std::string pcl_);

        private:
            pclCls() = default;

            int read_pcl();

            std::string pcl_file_;
    };
}
