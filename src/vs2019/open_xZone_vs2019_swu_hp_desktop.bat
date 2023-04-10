@echo off

REM define environment variables, do not change the variable name, just it's value!
set GTEST_INC=C:\pkg\googletest\vs2019-install\include
set GTEST_LIB=C:\pkg\googletest\vs2019-install\lib

set CV_INC=C:\pkg\opencv\opencv-4.1.1\install-local-w-contrib-vc2019-x64\include
set CV_LIB=C:\pkg\opencv\opencv-4.1.1\install-local-w-contrib-vc2019-x64\x64\vc16\lib

set BOOST_INC=C:\pkg\boost\boost_1_71_0
set BOOST_LIB=C:\pkg\boost\boost_1_71_0\lib64-msvc-14.2

set DDS_INC=C:\pkg\fastDDS\v2.9.1\include
set DDS_LIB=C:\pkg\fastDDS\v2.9.1\lib\x64Win64VS2019

set APP_SRC=E:\swu\projects\xZone\src
set APP_BUILD_INT=E:\swu\projects\xZone\build-vs2019-x64\int
set APP_BUILD_BIN=E:\swu\projects\xZone\build-vs2019-x64\bin

"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\IDE\devenv.exe" %APP_SRC%\vs2019\xZone_vs2019.sln

REM ---eof---/Users/wus1/Projects/2020/p803/software/payload-cpu/pyxis-analysis/vs2017/pyxisAnalysis.props
