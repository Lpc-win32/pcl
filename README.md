# pcl
a simple toml config file parser -- pcl

## pcl简介

- 作者：Lpc-Win32(Pengcheng Liu)/ Pepper Liu
- pcl是toml标准中的简化版本，暂时不支持数组配置，与多行配置。
- 采用CMake编译，生成libpcl.a静态库

## pcl版本：

- v1.0-beta: 实现基本功能，详情见下方示例

## pcl示例：

```
# 德玛西亚万众一心
name = ok

[global]
global_name = Hello World        # Hello World
global_val = "欢迎来到#德莱联盟" # 注释

[default]
val = nice
abc = abc
key=val_no_space    # no space
```
