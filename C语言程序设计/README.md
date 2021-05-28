# C语言程序设计

## 特性

C语言程序设计的作业完全使用C语言编写，
并利用了C99的特性。
代码全部采用 UTF-8 编码。
代码结构采用 CMake 组织。


## 编译

由于使用了C99特性，代码无法使用 msbuild 编译。
下面仅介绍 Windows 下使用 GCC 编译的方法。


### GCC 下载和安装

[MinGW 下载页面](https://sourceforge.net/projects/mingw-w64/files/mingw-w64/mingw-w64-release/)

[MinGW 8.1.0 x86_64-posix-seh 下载链接](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download)

安装完成后，把 gcc.exe 等文件所在路径（例如：C:\Program Files\mingw64\bin）添加到 PATH 环境变量中。


### CMake 下载和安装
[CMake 下载页面](https://cmake.org/download/)

[CMake 3.20.3 x86_64 MSI 下载链接](https://github.com/Kitware/CMake/releases/download/v3.20.3/cmake-3.20.3-windows-x86_64.msi)


### 编译
1. 打开 CMake (cmake-gui)
2. 点击 Browse Source... 选择源码路径。
3. 点击 Browse Build... 选择编译生成路径。
4. 点击 Configure
5. 弹出窗口中，Specify the generator for this project 下拉列表选择 MinGW Makefiles。
6. 点击 Generate
