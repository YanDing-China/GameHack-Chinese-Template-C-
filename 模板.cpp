#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "TlHelp32.h"
#include <string>
#include <Psapi.h>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <list>
using namespace std;

/*

#include <d3d9types.h>
    以下信息由绿竹  独家提供，切勿用于非法途经；
    本源码仅供参考  学习  交流；
    本源码于下载24H内 请自行删除，否则后果自负；
    本源码未经允许，不可用于收费，销售，外卖，等情况；
    感谢您的使用，感谢您的支持，感谢您的理解；
    共同进步，学习至上，爱我爱国爱他人；
    交流QQ群：1018208491；
    作者QQ号：925931646；
    时间：2020年3月6日21:42:37
    内容：DLL绘制；
    PS：主要方针，重点于DLL调用绘制为主，故没写绘制！
*/

//D3D9 转换好的颜色
const int 绘艳青 = -16711681;
const int 绘橙黄 = -32768;
const int 绘红色 = -65536;
const int 绘黄色 = -256;
const int 绘绿色 = -16711936;
const int 绘天蓝 = -16742145;
const int 绘青绿 = -16719744;
const int 绘灰色 = -8355712;
const int 绘品红 = -65281;
const int 绘芙红 = -32576;
const int 绘嫩绿 = -8331264;
const int 绘白色 = -1;
const int 绘黑色 = -16579837;


//---------------定义常量----------------
#define M_PI	3.14159265358979323846264338327950288419716939937510

typedef DWORD64* 长整数型;//8字节
typedef DWORD32* 整数型;//4字节
typedef short* 短整数型;//2字节
typedef float* 小数型;//4字节
typedef double* 双精度小数型;//8字节
typedef bool* 逻辑型;//true(真)和false（假）
typedef const char* 文本型; 

//---------------自定义变量类型----------------

struct 坐标6D {
    float
        xy = 0.f,
        xz = 0.f,
        yz = 0.f,
        wx = 0.f,
        wy = 0.f,
        wz = 0.f;
};
struct 坐标4D {
    float
        x = 0.f,
        y = 0.f,
        w = 0.f,
        h = 0.f;
};
struct 坐标4D_ {
    int
        x = 0,
        y = 0,
        w = 0,
        h = 0;
};
struct 坐标3D {
    float
        x = 0.f,
        y = 0.f,
        z = 0.f;
};
struct 坐标3D_ {
    int
        x = 0,
        y = 0,
        z = 0;
};
struct 坐标2D {
    float
        x = 0.f,
        y = 0.f;
};
struct 坐标2D_ {
    int
        x = 0,
        y = 0;
};

//---------------自定义数据类型----------------

struct 名称标识 {
   const char *玩家  = { NULL },
       *角色 = { NULL },
       *人机 = { NULL },
       *快递 = { NULL },
       *载具 = { NULL },
       *空投 = { NULL },
       *物资 = { NULL };
};
struct 窗口信息 {
    LONG
        x = 0,
        y = 0,
        w = 0,
        h = 0;
    坐标2D_ 中心;
};
struct D3D矩阵 {
    float
        _11 = 0.f,
        _12 = 0.f,
        _13 = 0.f,
        _14 = 0.f,
        _21 = 0.f,
        _22 = 0.f,
        _23 = 0.f,
        _24 = 0.f,
        _31 = 0.f,
        _32 = 0.f,
        _33 = 0.f,
        _34 = 0.f,
        _41 = 0.f,
        _42 = 0.f,
        _43 = 0.f,
        _44 = 0.f;
};
struct 骨骼点 {
    int
        头部 = 0,
        脖子 = 0,
        盆骨 = 0,
        底盘 = 0,

        左臂 = 0,
        左肘 = 0,
        左手 = 0,

        右臂 = 0,
        右肘 = 0,
        右手 = 0,

        左腿 = 0,
        左膝 = 0,
        左脚 = 0,

        右腿 = 0,
        右膝 = 0,
        右脚 = 0;
};
struct 骨骼2D {
    坐标2D
        头部,
        脖子,
        盆骨,
        底盘,
        左臂,
        左肘,
        左手,
        右臂,
        右肘,
        右手,
        左腿,
        左膝,
        左脚,
        右腿,
        右膝,
        右脚;
};

struct 绘制信息 {
    string 内容 = { NULL };
    int    颜色 = 0;
};
struct 自瞄信息 {
    DWORD64   基址 = 0, 地址 = 0;
    bool    锁定 = false;
    int     当前 = 0, 最近 = 0;
    坐标3D  坐标;
};
struct 相机信息 {
    DWORD64 基址 = 0;
    float    fov = 0.f;
    坐标3D  坐标;
    坐标3D  视角;
    坐标3D 矩阵x;
    坐标3D 矩阵y;
    坐标3D 矩阵z;
};
struct 骨骼结构 {
    坐标4D 旋转;
    坐标3D 坐标;
    坐标3D 比例;
};

struct 自定菜单 {
    string 内容 = "  [开]";
    int  数值 = 0;
    int  颜色 = 绘绿色;
};

struct 对象信息 {
    DWORD64   地址 = 0;
    DWORD64   指针 = 0;
    int  距离 = 0;
    int  武器 = 0;
    int  状态 = 0;
    float  怒气 = 0.f;
    const char* 名称 = { NULL };
    const char* name = { NULL };
    坐标3D     坐标;
    坐标3D     底盘;
};


//---------------全局变量----------------
DWORD64
世界基址 = 0x348CC70,
矩阵基址 = 0x3100500,
名称基址 = 0x338A808,
雷达基址 = 0x3399D10,
模块地址 = 0,
世界地址 = 0,
名称地址 = 0,
矩阵地址 = 0,
雷达地址 = 0;

LPCSTR
窗口类名 = "UnrealWindow",
窗口标题 = "WuXiaX  ";
LPCWSTR 进程名称 = L"WuXiaXClient-Win64-Shipping.exe";
const char* 进程名 = "WuXiaXClient-Win64-Shipping.exe";

HWND
游戏句柄 = 0,
辅助句柄 = 0;
DWORD    游戏id = 0;
窗口信息   游戏窗口;
自瞄信息       自瞄;
相机信息       相机;
D3D矩阵        矩阵;
骨骼点         骨点;
名称标识       透视;
对象信息       本人;
自定菜单       人物, 一键, 菜单, 玩家, 马匹, 物资, 瞄准, 防空, 战斗, 垃圾,
               雷达, 徒手, 单剑, 单刀, 双剑, 双刺, 长剑, 长枪, 长刀, 重剑;

string         米 = "米";
float _地图x = 0.f, _地图y = 0.f, _地图w = 0.f, _地图h = 0.f, _地图2w = 0.f, _地图2h = 0.f, _地图中心x = 0.f, _地图中心y = 0.f, _地图比例 = 0.f;


void     绿竹窗口移动(HWND 句柄, LONG x, LONG y, LONG w, LONG h);
void     绿竹窗口置顶(HWND 句柄);
void     绿竹窗口显隐(HWND 句柄);
void     绿竹窗口取ID(HWND 句柄, DWORD _pid);
HWND     绿竹窗口取句柄(LPCSTR 类名, LPCSTR 标题);
窗口信息 绿竹窗口取坐标(HWND 句柄);

bool     绿竹热键状态(int 值);
DWORD    绿竹进程名取ID(LPCWSTR _名);
DWORD64  绿竹进程取模块(DWORD _Pid, LPCWSTR _nm);

坐标3D   绿竹骨骼乘矩阵(坐标3D _a, D3D矩阵 _b);
D3D矩阵  绿竹骨骼转矩阵(骨骼结构  _阵);
坐标3D   绿竹骨骼转坐标(DWORD64 地址, D3D矩阵 _矩);

坐标3D   绿竹读坐标(DWORD64 addr);
D3D矩阵  绿竹读矩阵(DWORD64 地址);
骨骼结构 绿竹读结构(DWORD64 地址);


void     绿竹玩家骨骼点();
void     绿竹初始透视();

int      绿竹矩阵距离(坐标3D _a);
坐标2D   绿竹矩阵转2D(坐标3D 坐标);
坐标4D   绿竹矩阵转4D(坐标3D 坐标);
void     绿竹矩阵骨骼(DWORD64 _组, int _色, int _宽);

坐标3D   绿竹3D坐标差(坐标3D _a, 坐标3D _b);
坐标3D   绿竹视角旋转(坐标3D _a);
void     绿竹自瞄视角(DWORD64 _地);
void     绿竹自瞄锁敌();

void     绿竹相机转阵();
坐标2D   绿竹相机转2D(坐标3D 坐标);
int      绿竹相机距离(坐标3D _a);
void     绿竹读相机();

void     视野循环();
void     热键循环();
void     本人循环();
void     雷达循环();
void     对象读取();
void     绘制循环();
void     绘制菜单();



string      状态返回(int _a);
string      武器返回(int _a);

绘制信息    判断物资(int _a);
void        读雷达(DWORD64 a);
void        画雷达(坐标3D _pos);

//                   DLL绘制

const HINSTANCE 绿竹D3D = LoadLibraryA("绿竹D3D.dll");
//  FreeLibrary(hDll);释放DLL句柄      #define CALLBACK __stdcall //回调函数用  #define WINAPI __stdcall //WINAPI用
//DLL目录：  1. ....\绿竹模板\Debug\绿竹D3D.dll   或 2  ....\绿竹模板\绿竹D3D.dll   或 3  C:\Windows\SysWOW64\绿竹D3D.dll  或 4  C:\WINDOWS\system32\绿竹D3D.dll
//在这些目录中 都可调用

typedef int(__stdcall* DLL_ckcc)(int 大小, const char* 字名, const char* 类名, const char* 标题);
DLL_ckcc 窗口创建 = (DLL_ckcc)GetProcAddress(绿竹D3D, "窗口创建");

typedef void(__stdcall* DLL_ckyd)(LONG x, LONG y, LONG w, LONG h);
DLL_ckyd 移动窗口 = (DLL_ckyd)GetProcAddress(绿竹D3D, "窗口移动");

typedef void(__stdcall* DLL_hzfk)(int x, int y, int w, int h, int 颜色, int 宽);
DLL_hzfk 绘制方框 = (DLL_hzfk)GetProcAddress(绿竹D3D, "绘制方框");

typedef void(__stdcall* DLL_hzwb)(const char* str, int x, int y, int 颜色);
DLL_hzwb 绘制文本 = (DLL_hzwb)GetProcAddress(绿竹D3D, "绘制文本");

typedef void(__stdcall* DLL_hzzx)(int x1, int y1, int x2, int y2, int 宽, int 颜色);
DLL_hzzx 绘制直线 = (DLL_hzzx)GetProcAddress(绿竹D3D, "绘制直线");

typedef void(__stdcall* DLL_mbwb)(const char* str, int x, int y, int 描边, int 颜色);
DLL_mbwb 描边文本 = (DLL_mbwb)GetProcAddress(绿竹D3D, "描边文本");

typedef void(__stdcall* DLL_tmzt)();
DLL_tmzt 透明主题 = (DLL_tmzt)GetProcAddress(绿竹D3D, "透明主题");

typedef void(__stdcall* DLL_xxxh)();
DLL_xxxh 消息循环 = (DLL_xxxh)GetProcAddress(绿竹D3D, "消息循环");

typedef void(__stdcall* DLL_hzcx)(void* 程序);
DLL_hzcx 绘制程序 = (DLL_hzcx)GetProcAddress(绿竹D3D, "绘制程序");

typedef void(__stdcall* DLL_zhys)(int 颜色, int 透明);
DLL_zhys 转换颜色 = (DLL_zhys)GetProcAddress(绿竹D3D, "转换颜色");

typedef void(__stdcall* DLL_qckxx)(HWND a, LONG x, LONG y, LONG w, LONG h, int w2, int h2);
DLL_qckxx 取窗口坐标 = (DLL_qckxx)GetProcAddress(绿竹D3D, "取窗口信息");

typedef int (__stdcall* DLL_wbdb)(const char* _a, const char* _b);
DLL_wbdb 文本对比 = (DLL_wbdb)GetProcAddress(绿竹D3D, "文本对比");

//                   DLL驱动


class 内核
{
public:
    typedef void(__stdcall* QDdll_szjc)(DWORD a);
    QDdll_szjc 设置进程 = (QDdll_szjc)GetProcAddress(绿竹D3D, "设置进程");

    typedef void(__stdcall* QDdll_ckfjt)(HWND a);
    QDdll_ckfjt 窗口反截图 = (QDdll_ckfjt)GetProcAddress(绿竹D3D, "窗口反截图");

    typedef DWORD64(__stdcall* DLL_qmkdz)(const char* a);
    DLL_qmkdz 取模块地址 = (DLL_qmkdz)GetProcAddress(绿竹D3D, "取模块地址");

    typedef LPCWCH(__stdcall* QDdll_zjjj)(DWORD64 a, SIZE_T b);
    QDdll_zjjj 读字节集 = (QDdll_zjjj)GetProcAddress(绿竹D3D, "读字节集");

    typedef int(__stdcall* QDdll_dzjx)(DWORD64 a);
    QDdll_dzjx 读字节型 = (QDdll_dzjx)GetProcAddress(绿竹D3D, "读字节型");

    typedef float(__stdcall* QDdll_dxsx)(DWORD64 a);
    QDdll_dxsx 读小数型 = (QDdll_dxsx)GetProcAddress(绿竹D3D, "读小数型");

    typedef int(__stdcall* QDdll_dzsx)(DWORD64 a);
    QDdll_dzsx 读整数型 = (QDdll_dzsx)GetProcAddress(绿竹D3D, "读整数型");

    typedef int(__stdcall* QDdll_dczs)(DWORD64 a);
    QDdll_dczs 读长整数 = (QDdll_dczs)GetProcAddress(绿竹D3D, "读长整数");

    typedef const char* (__stdcall* QDdll_dwbx)(DWORD64 a, SIZE_T b);
    QDdll_dwbx 读文本型 = (QDdll_dwbx)GetProcAddress(绿竹D3D, "读文本型");

    typedef const char* (__stdcall* QDdll_dbs)(DWORD64 a, int b);
    QDdll_dbs 读UE4标识 = (QDdll_dbs)GetProcAddress(绿竹D3D, "读UE4标识");

    typedef int(__stdcall* QDdll_xgsx)(DWORD64 a, SIZE_T b);
    QDdll_xgsx 修改属性 = (QDdll_xgsx)GetProcAddress(绿竹D3D, "修改属性");

    typedef void(__stdcall* QDdll_xwbx)(DWORD64 a, const char* b);
    QDdll_xwbx 写文本型 = (QDdll_xwbx)GetProcAddress(绿竹D3D, "写文本型");

    typedef void(__stdcall* QDdll_xzjx)(DWORD64 a, int b);
    QDdll_xzjx 写字节型 = (QDdll_xzjx)GetProcAddress(绿竹D3D, "写字节型");

    typedef void(__stdcall* QDdll_xczs)(DWORD64 a, DWORD64 b);
    QDdll_xczs 写长整数 = (QDdll_xczs)GetProcAddress(绿竹D3D, "写长整数");

    typedef void(__stdcall* QDdll_xzsx)(DWORD64 a, DWORD32 b);
    QDdll_xzsx 写整数型 = (QDdll_xzsx)GetProcAddress(绿竹D3D, "写整数型");

    typedef void(__stdcall* QDdll_xxsx)(DWORD64 a, float b);
    QDdll_xxsx 写小数型 = (QDdll_xxsx)GetProcAddress(绿竹D3D, "写小数型");

    typedef void(__stdcall* QDdll_xzjj)(DWORD64 a, LPCWCH b, SIZE_T c);
    QDdll_xzjj 写字节集 = (QDdll_xzjj)GetProcAddress(绿竹D3D, "写字节集");

}; 内核           驱动;



DWORD    绿竹进程名取ID(LPCWSTR _名) {
    PROCESSENTRY32 _b;
    HANDLE _a = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    _b.dwSize = sizeof(PROCESSENTRY32);
    while (Process32Next(_a, &_b))
    {
        if (!wcscmp(_b.szExeFile, _名))
        {
            CloseHandle(_a);
            return _b.th32ProcessID;
        }
    }
    return 0;
};
DWORD64  绿竹进程取模块(DWORD _Pid, LPCWSTR _nm) {
    MODULEENTRY32 _b;
    HANDLE _a = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _Pid);
    _b.dwSize = sizeof(_b);
    while (Module32Next(_a, &_b))
    {
        if (!wcscmp(_b.szModule, _nm))
        {
            CloseHandle(_a);
            return (DWORD64)_b.modBaseAddr;//返回模块地址
        };
    }
    return 0;
};

//---------------定义运算函数----------------

void     绿竹窗口移动(HWND 句柄, LONG x, LONG y, LONG w, LONG h)
{
    MoveWindow(句柄, x, y, w, h, true); UpdateWindow(句柄);
};
void     绿竹窗口置顶(HWND 句柄)
{
    SetWindowPos(句柄, HWND_TOPMOST, 0, 0, 0, 0, 3);
};
void     绿竹窗口显隐(HWND 句柄)
{
    ShowWindow(句柄, SW_RESTORE);
};
void     绿竹窗口取ID(HWND 句柄, DWORD _pid) {
    GetWindowThreadProcessId(句柄, &_pid);
};
HWND     绿竹窗口取句柄(LPCSTR 类名, LPCSTR 标题)
{
    return FindWindowA(类名, 标题);
};
窗口信息 绿竹窗口取坐标(HWND 句柄)
{
    RECT   b;
    窗口信息 返回;
    GetWindowRect(句柄, &b);
    返回.x = b.left;
    返回.y = b.top;
    返回.w = b.right - b.left;
    返回.h = b.bottom - b.top;
    返回.中心.x = 返回.w / 2;
    返回.中心.y = 返回.h / 2;
    return 返回;
};

bool     绿竹热键状态(int 值)
{
    if (GetAsyncKeyState(值) & 1)//如果F1按下
    {
        return  true;
    }
    /*    VK_F1
     SHORT a = GetAsyncKeyState(值) & 1;
     if (a != 0) { return  true; }
    if (a == -32767) { return  true; }
   else if (a == -32768) { return  true; }
   else if (a == 32767) { return  true; }
   else if (a == 32768) { return  true; }
   else if (a != 0) { return  true; }
    */
    else { return false; }
};


坐标3D   绿竹骨骼乘矩阵(坐标3D _a, D3D矩阵 _b)
{
    坐标3D  _d;
    _d.x = _a.x * _b._11 + _a.y * _b._21 + _a.z * _b._31 + _b._41;
    _d.y = _a.x * _b._12 + _a.y * _b._22 + _a.z * _b._32 + _b._42;
    _d.z = _a.x * _b._13 + _a.y * _b._23 + _a.z * _b._33 + _b._43;
    return _d;
};
D3D矩阵  绿竹骨骼转矩阵(骨骼结构  _阵)
{
    D3D矩阵 _矩;
    坐标3D  _A, _B;
    坐标6D  _C;
    _A.x = _阵.旋转.x + _阵.旋转.x;
    _A.y = _阵.旋转.y + _阵.旋转.y;
    _A.z = _阵.旋转.w + _阵.旋转.w;

    _B.x = _阵.旋转.x * _A.x;
    _B.y = _阵.旋转.y * _A.y;
    _B.z = _阵.旋转.w * _A.z;

    _C.yz = _阵.旋转.y * _A.z;
    _C.wx = _阵.旋转.h * _A.x;
    _C.xy = _阵.旋转.x * _A.y;

    _C.wz = _阵.旋转.h * _A.z;
    _C.xz = _阵.旋转.x * _A.z;
    _C.wy = _阵.旋转.h * _A.y;

    _矩._31 = (_C.xz + _C.wy) * _阵.比例.z;
    _矩._32 = (_C.yz - _C.wx) * _阵.比例.z;
    _矩._33 = (1 - (_B.x + _B.y)) * _阵.比例.z;

    _矩._11 = (1 - (_B.y + _B.z)) * _阵.比例.x;
    _矩._12 = (_C.xy + _C.wz) * _阵.比例.x;
    _矩._13 = (_C.xz - _C.wy) * _阵.比例.x;

    _矩._21 = (_C.xy - _C.wz) * _阵.比例.y;
    _矩._22 = (1 - (_B.x + _B.z)) * _阵.比例.y;
    _矩._23 = (_C.yz + _C.wx) * _阵.比例.y;

    _矩._41 = _阵.坐标.x;
    _矩._42 = _阵.坐标.y;
    _矩._43 = _阵.坐标.z;
    _矩._44 = 1;
    return _矩;

}
坐标3D   绿竹骨骼转坐标(DWORD64 地址, D3D矩阵 _矩) {
    return 绿竹骨骼乘矩阵(绿竹读坐标(地址), _矩);
};

void     绿竹玩家骨骼点() {
    骨点.盆骨 = 3 * 0x30 + 0x10;
    骨点.脖子 = 6 * 0x30 + 0x10;
    骨点.头部 = 7 * 0x30 + 0x10;

    骨点.左臂 = 9 * 0x30 + 0x10;
    骨点.左肘 = 10 * 0x30 + 0x10;
    骨点.左手 = 11 * 0x30 + 0x10;

    骨点.右臂 = 29 * 0x30 + 0x10;
    骨点.右肘 = 30 * 0x30 + 0x10;
    骨点.右手 = 31 * 0x30 + 0x10;

    骨点.左腿 = 52 * 0x30 + 0x10;
    骨点.左膝 = 53 * 0x30 + 0x10;
    骨点.左脚 = 54 * 0x30 + 0x10;

    骨点.右腿 = 48 * 0x30 + 0x10;
    骨点.右膝 = 49 * 0x30 + 0x10;
    骨点.右脚 = 50 * 0x30 + 0x10;

    骨点.底盘 = 50 * 0x30 + 0x10;
};
void     绿竹初始透视() {


    透视.玩家 = "uXiaX_Character_C";
    透视.角色 = "akePlayer_C";
    透视.人机 = "pcCharacter_C";
    透视.载具 = "uXiaHorse_C";
    透视.空投 = "aradrop_C";
    透视.快递 = "Box";
    透视.物资 = "Item";

    人物.颜色 = 绘绿色;
    人物.数值 = 4;
    人物.内容 = "  [骨骼]";
    一键.颜色 = 绘绿色;
    一键.数值 = 2;
    一键.内容 = "  [刺杀]";
    瞄准.内容 = "  [开启]";
    雷达.内容 = "  [开启]";
    防空.内容 = "  [开启]";
    物资.内容 = "  [开启]";
    绿竹玩家骨骼点();
};

坐标3D   绿竹读坐标(DWORD64 地址)
{
    坐标3D _a;
    _a.x = 驱动.读小数型(地址);
    _a.y = 驱动.读小数型(地址 + 4);
    _a.z = 驱动.读小数型(地址 + 8);
    return _a;
};
D3D矩阵  绿竹读矩阵(DWORD64 地址) {
    D3D矩阵 _a;
    _a._11 = 驱动.读小数型(地址);
    _a._12 = 驱动.读小数型(地址+4);
    _a._13 = 驱动.读小数型(地址 + 8);
    _a._14 = 驱动.读小数型(地址 + 12);

    _a._21 = 驱动.读小数型(地址+16);
    _a._22 = 驱动.读小数型(地址 +20);
    _a._23 = 驱动.读小数型(地址 +24);
    _a._24 = 驱动.读小数型(地址 +28);

    _a._31 = 驱动.读小数型(地址 + 32);
    _a._32 = 驱动.读小数型(地址 + 36);
    _a._33 = 驱动.读小数型(地址 + 40);
    _a._34 = 驱动.读小数型(地址 + 44);

    _a._41 = 驱动.读小数型(地址 + 48);
    _a._42 = 驱动.读小数型(地址 + 52);
    _a._43 = 驱动.读小数型(地址 + 56);
    _a._44 = 驱动.读小数型(地址 + 60);
    return _a;
};
骨骼结构 绿竹读结构(DWORD64 地址) {
    骨骼结构 _a;
    _a.旋转.x = 驱动.读小数型(地址);
    _a.旋转.y = 驱动.读小数型(地址 + 4);
    _a.旋转.w = 驱动.读小数型(地址 + 8);
    _a.旋转.h = 驱动.读小数型(地址 + 12);

    _a.坐标.x = 驱动.读小数型(地址 + 16);
    _a.坐标.y = 驱动.读小数型(地址 + 20);
    _a.坐标.z = 驱动.读小数型(地址 + 24);

    _a.比例.x = 驱动.读小数型(地址 + 32);
    _a.比例.y = 驱动.读小数型(地址 + 36);
    _a.比例.z = 驱动.读小数型(地址 + 40);
    return _a;
    //驱动.读骨骼结构(地址,_a.旋转.x, _a.旋转.y, _a.旋转.w, _a.旋转.h, _a.坐标.x, _a.坐标.y, _a.坐标.z,_a.比例.x, _a.比例.y, _a.比例.z);
};


int      绿竹矩阵距离(坐标3D _a) {
    float  _W = 矩阵._14 * _a.x + 矩阵._24 * _a.y + 矩阵._34 * _a.z + 矩阵._44;
    if (_W < 0.01) { return  -1; };
    return  int(_W / 100.0f);
};
坐标2D   绿竹矩阵转2D(坐标3D 坐标) {
    坐标2D 屏幕;
    float  _W = 矩阵._14 * 坐标.x + 矩阵._24 * 坐标.y + 矩阵._34 * 坐标.z + 矩阵._44;
    if (_W < 0.01) { return  屏幕; };
    _W = 1 / _W;
    屏幕.x = 游戏窗口.中心.x + (矩阵._11 * 坐标.x + 矩阵._21 * 坐标.y + 矩阵._31 * 坐标.z + 矩阵._41) * _W * 游戏窗口.中心.x;
    屏幕.y = 游戏窗口.中心.y - (矩阵._12 * 坐标.x + 矩阵._22 * 坐标.y + 矩阵._32 * 坐标.z + 矩阵._42) * _W * 游戏窗口.中心.y;
    return  屏幕;
};
坐标4D   绿竹矩阵转4D(坐标3D 坐标) {
    坐标2D _2D, _4D;
    坐标4D 方框;
    float  _W = 矩阵._14 * 坐标.x + 矩阵._24 * 坐标.y + 矩阵._34 * 坐标.z + 矩阵._44;
    if (_W < 0.01) { return  方框; };
    _W = 1.0f / _W;
    _2D.x = 游戏窗口.中心.x + (矩阵._11 * 坐标.x + 矩阵._21 * 坐标.y + 矩阵._31 * 坐标.z + 矩阵._41) * _W * 游戏窗口.中心.x;

    _2D.y = 游戏窗口.中心.y - (矩阵._12 * 坐标.x + 矩阵._22 * 坐标.y + 矩阵._32 * (坐标.z - 90) + 矩阵._42) * _W * 游戏窗口.中心.y;
    _4D.y = 游戏窗口.中心.y - (矩阵._12 * 坐标.x + 矩阵._22 * 坐标.y + 矩阵._32 * (坐标.z + 90) + 矩阵._42) * _W * 游戏窗口.中心.y;

    _4D.x = _2D.y - _4D.y;

    方框.x = _2D.x - _4D.x / 4;
    方框.y = _4D.y;
    方框.w = _4D.x / 2;
    方框.h = _4D.x;

    return 方框;
};
void   绿竹矩阵骨骼(DWORD64 _组, int _色, int _宽) {
    骨骼结构  _阵;
    D3D矩阵   _矩;
    骨骼2D    _骨;
    DWORD64  _地 = 驱动.读长整数(_组 + 0x5B0);
    _阵 = 绿竹读结构(_组 + 0x190);
    _矩 = 绿竹骨骼转矩阵(_阵);
    坐标3D    _头 = 绿竹骨骼转坐标(_地 + 骨点.头部, _矩);

    int _距 = 绿竹矩阵距离(_头);
    if (_距 > 250 || _距 == 0) { return; };

    _骨.头部 = 绿竹矩阵转2D(_头);
    if (_骨.头部.x == 0 && _骨.头部.y == 0) { return; };
        _骨.盆骨 = 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.盆骨, _矩));
        _骨.脖子= 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.脖子, _矩));

        _骨.左手= 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.左手, _矩));
        _骨.左肘= 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.左肘, _矩));
        _骨.左臂=  绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.左臂, _矩));

        _骨.右手=绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.右手, _矩));
        _骨.右肘=绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.右肘, _矩));
        _骨.右臂=绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.右臂, _矩));

        _骨.左膝=绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.左膝, _矩));
        _骨.左腿=绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.左腿, _矩));
        _骨.左脚 = 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.左脚, _矩));

        _骨.右腿 = 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.右腿, _矩));
        _骨.右膝 = 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.右膝, _矩));
        _骨.右脚 = 绿竹矩阵转2D(绿竹骨骼转坐标(_地 + 骨点.右脚, _矩));

        绘制直线(_骨.头部.x, _骨.头部.y, _骨.脖子.x, _骨.脖子.y, _宽, _色);
        绘制直线(_骨.盆骨.x, _骨.盆骨.y, _骨.脖子.x, _骨.脖子.y, _宽, _色);
        绘制直线(_骨.脖子.x, _骨.脖子.y, _骨.左臂.x, _骨.左臂.y, _宽, _色);
        绘制直线(_骨.左臂.x, _骨.左臂.y, _骨.左肘.x, _骨.左肘.y, _宽, _色);
        绘制直线(_骨.左肘.x, _骨.左肘.y, _骨.左手.x, _骨.左手.y, _宽, _色);
        绘制直线(_骨.脖子.x, _骨.脖子.y, _骨.右臂.x, _骨.右臂.y, _宽, _色);
        绘制直线(_骨.右臂.x, _骨.右臂.y, _骨.右肘.x, _骨.右肘.y, _宽, _色);
        绘制直线(_骨.右肘.x, _骨.右肘.y, _骨.右手.x, _骨.右手.y, _宽, _色);
        绘制直线(_骨.盆骨.x, _骨.盆骨.y, _骨.左腿.x, _骨.左腿.y, _宽, _色);
        绘制直线(_骨.左腿.x, _骨.左腿.y, _骨.左膝.x, _骨.左膝.y, _宽, _色);
        绘制直线(_骨.左膝.x, _骨.左膝.y, _骨.左脚.x, _骨.左脚.y, _宽, _色);
        绘制直线(_骨.盆骨.x, _骨.盆骨.y, _骨.右腿.x, _骨.右腿.y, _宽, _色);
        绘制直线(_骨.右腿.x, _骨.右腿.y, _骨.右膝.x, _骨.右膝.y, _宽, _色);
        绘制直线(_骨.右膝.x, _骨.右膝.y, _骨.右脚.x, _骨.右脚.y, _宽, _色);
        return ;
};

坐标3D   绿竹3D坐标差(坐标3D _a, 坐标3D _b) {
    坐标3D  _c;
    _c.x = _a.x - _b.x;
    _c.y = _a.y - _b.y;
    _c.z = _a.z - _b.z;
    return _c;
};
坐标3D   绿竹视角旋转(坐标3D _a) {
    坐标3D  _b;
    float p = float(180.0f / M_PI);
    _b.y = float(atan2(_a.x, _a.y) * p);
    _b.x = float(atan2(_a.z, sqrt(_a.x * _a.x + _a.y * _a.y)) * p);
    _b.z = 0.f;
    return _b;
};
void     绿竹自瞄目标(坐标2D _敌, DWORD64 _地) {
    坐标2D _b;
    _b.x = _敌.x - 游戏窗口.中心.x;
    _b.y = _敌.y - 游戏窗口.中心.y;
    自瞄.当前 = int(sqrt(_b.x * _b.x + _b.y * _b.y));
    if (自瞄.当前 == 0 || 自瞄.当前 <= 自瞄.最近)
    {
        自瞄.最近 = 自瞄.当前;
        自瞄.地址 = _地;
        return;
    };
};
void     绿竹自瞄视角(DWORD64 _地) {
    坐标3D  _p = 绿竹视角旋转(绿竹3D坐标差(绿竹读坐标(驱动.读长整数(_地 + 0x158) + 0x1A0), 相机.坐标));
    驱动.写小数型(自瞄.基址, _p.x);
    驱动.写小数型(自瞄.基址 + 4, _p.y);
    return;
};
void     绿竹自瞄锁敌() {
    if (GetAsyncKeyState(VK_RBUTTON) != 0 && 自瞄.地址 > 0) {
        自瞄.锁定 = true;
        自瞄.最近 = 自瞄.当前;
        绿竹自瞄视角(自瞄.地址);
        return;
    }
    else {
        自瞄.锁定 = false;
        自瞄.最近 = 150;
        自瞄.地址 = 0;
        return;
    }
};

void     绿竹相机转阵() {

    float 俯仰角 = float(相机.视角.x * M_PI / 180.0f);
    float 偏航角 = float(相机.视角.y * M_PI / 180.0f);
    float 翻滚角 = float(相机.视角.z * M_PI / 180.0f);

    float S俯 = sin(俯仰角);
    float C俯 = cos(俯仰角);

    float S偏 = sin(偏航角);
    float C偏 = cos(偏航角);

    float S翻 = sin(翻滚角);
    float C翻 = cos(翻滚角);

    
    相机.矩阵x.x = C俯 * C偏;
    相机.矩阵x.y = C俯 * S偏;
    相机.矩阵x.z = S俯;

    相机.矩阵y.x = S翻 * S俯 * C偏 - C翻 * S偏;
    相机.矩阵y.y = S翻 * S俯 * S偏 + C翻 * C偏;
    相机.矩阵y.z = -S翻 * C俯;

    相机.矩阵z.x = -(C翻 * S俯 * C偏 + S翻 * S偏);
    相机.矩阵z.y = C偏 * S翻 - C翻 * S俯 * S偏;
    相机.矩阵z.z = C翻 * C俯;
};
坐标3D   绿竹3D坐标积(坐标3D _a) {
    坐标3D _c;
    _c.x = _a.x * 相机.矩阵y.x + _a.y * 相机.矩阵y.y + _a.z * 相机.矩阵y.z;
    _c.y = _a.x * 相机.矩阵z.x + _a.y * 相机.矩阵z.y + _a.z * 相机.矩阵z.z;
    _c.z = _a.x * 相机.矩阵x.x + _a.y * 相机.矩阵x.y + _a.z * 相机.矩阵x.z;
    return _c;
};
坐标2D   绿竹相机转2D(坐标3D 坐标) {
    坐标2D 屏幕,a;
    坐标3D p = 绿竹3D坐标积(绿竹3D坐标差(坐标, 相机.坐标));
    if (p.z >= 1) {
        屏幕.x = 游戏窗口.中心.x + p.x * 游戏窗口.中心.x / float(tan(相机.fov * M_PI / 360.0f)) / p.z;
        屏幕.y = 游戏窗口.中心.y - p.y * 游戏窗口.中心.x / float(tan(相机.fov * M_PI / 360.0f)) / p.z;
        if (屏幕.x > 0 && 屏幕.y > 0) {
            if (屏幕.x <= 游戏窗口.w && 屏幕.y <= 游戏窗口.h) {
                return 屏幕;
            };
        };
    };
    return a;
};
int      绿竹相机距离(坐标3D _a) {
    坐标3D d = 绿竹3D坐标差(_a, 本人.坐标);
    return int(sqrt(d.x * d.x + d.y * d.y + d.z * d.z) / 100.0f);
};
void     绿竹读相机() {
    相机.坐标 = 绿竹读坐标(相机.基址 + 0x190);
    相机.视角 = 绿竹读坐标(相机.基址 + 0x1D0);
    相机.fov = 驱动.读小数型(相机.基址 + 0x238);
};

void     画雷达(坐标3D _pos) {
    坐标2D _雷达;
    坐标3D _差 = 绿竹3D坐标差(_pos, 相机.坐标);
    _雷达.x = _地图中心x + _差.x * _地图比例;
    _雷达.y = _地图中心y + _差.y * _地图比例;
    if (_雷达.x > _地图x&& _雷达.y > _地图y&& _雷达.x < _地图w && _雷达.y < _地图h)
    {
        绘制方框(int(_雷达.x - 4), int(_雷达.y - 4), 12, 12, 绘红色, 2);
    };
};
void     读雷达(DWORD64 a) {
    float _x = 驱动.读小数型(a + 0x90);
    float _y = 驱动.读小数型(a + 0x94);
    float _w = 驱动.读小数型(a + 0xA8);
    float _h = 驱动.读小数型(a + 0xAC);
    if (_x == 0 && _y == 0) { return; };
    _地图x = _x; _地图y = _y; _地图w = _w; _地图h = _h; _地图2w = _w - _x; _地图2h = _h - _y; _地图中心x = _地图2w / 2; _地图中心y = _地图2h / 2; _地图比例 = _地图2w / 40000;
};

void     视野循环() {
    while (true)
    {
        矩阵 = 绿竹读矩阵(矩阵地址);
        Sleep(3);
    };
};
void     热键循环() {
    while (true) {
        if (一键.数值 == 1 || 一键.数值 == 3)
        {   if (本人.怒气 == 100) {   
                keybd_event(71, MapVirtualKeyA(71, 0), 0, 0);
                keybd_event(71, MapVirtualKeyA(71, 0), 0, 2); };
        };
        if (一键.数值 == 2 || 一键.数值 == 3)
        {
            if (本人.状态 == 6) {
                keybd_event(70, MapVirtualKeyA(71, 0), 0, 0);
                keybd_event(70, MapVirtualKeyA(71, 0), 0, 2);
            };
        };

        if ((GetAsyncKeyState(VK_HOME) & 1) == 1)
        { 
            菜单.数值 = 菜单.数值 + 1;
            if (菜单.数值 > 1)
            {
                菜单.数值 = 0;
            };
        };
        if ((GetAsyncKeyState(VK_F3) & 1) == 1)
        { 
            瞄准.数值 = 瞄准.数值 + 1;
            if (瞄准.数值 > 1)
            {
                瞄准.数值 = 0;
            };
            if (瞄准.数值 ==0)
            {
                瞄准.内容 = "  [开启]";
                瞄准.颜色 = 绘绿色;
            };
            if (瞄准.数值 == 1) {
                瞄准.内容 = "  [关闭]";
                瞄准.颜色 = 绘白色;
            };
        };

        if ((GetAsyncKeyState(VK_F4) & 1) == 1)
        {
            雷达.数值 = 雷达.数值 + 1;
            if (雷达.数值 > 1)
            {
                雷达.数值 = 0;
            };
            if (雷达.数值 == 0)
            {
                雷达.内容 = "  [开启]";
                雷达.颜色 = 绘绿色;
            };
            if (雷达.数值 == 1) {
                雷达.内容 = "  [关闭]";
                雷达.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(VK_F6) & 1) == 1)

        {
            防空.数值 = 防空.数值 + 1;
            if (防空.数值 > 1)
            {
                防空.数值 = 0;
            };
            if (防空.数值 == 0)
            {
                防空.内容 = "  [开启]";
                防空.颜色 = 绘绿色;
            };
            if (防空.数值 == 1) {
                防空.内容 = "  [关闭]";
                防空.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(VK_F1) & 1) == 1)
        {
            物资.数值 = 物资.数值 + 1;
            if (物资.数值 > 1)
            {
                物资.数值 = 0;
            };
            if (物资.数值 == 0)
            {
                物资.内容 = "  [开启]";
                物资.颜色 = 绘绿色;
            };
            if (物资.数值 == 1) {
                物资.内容 = "  [关闭]";
                物资.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(106) & 1) == 1)//小键盘乘
        {
            马匹.数值 = 马匹.数值 + 1;
            if (马匹.数值 > 1)
            {
                马匹.数值 = 0;
            };
            if (马匹.数值 == 0)
            {
                马匹.内容 = "  [开]";
                马匹.颜色 = 绘绿色;
            };
            if (马匹.数值 == 1) {
                马匹.内容 = "";
                马匹.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(96) & 1) == 1)//小键盘0
        {
            垃圾.数值 = 垃圾.数值 + 1;
            if (垃圾.数值 > 1)
            {
                垃圾.数值 = 0;
            };
            if (垃圾.数值 == 0)
            {
                垃圾.内容 = "  [开]";
                垃圾.颜色 = 绘绿色;
            };
            if (垃圾.数值 == 1) {
                垃圾.内容 = "";
                垃圾.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(97) & 1) == 1)
        {
            徒手.数值 = 徒手.数值 + 1;
            if (徒手.数值 > 1)
            {
                徒手.数值 = 0;
            };
            if (徒手.数值 == 0)
            {
                徒手.内容 = "  [开]";
                徒手.颜色 = 绘绿色;
            };
            if (徒手.数值 == 1) {
                徒手.内容 = "";
                徒手.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(98) & 1) == 1)
        {
            单剑.数值 = 单剑.数值 + 1;
            if (单剑.数值 > 1)
            {
                单剑.数值 = 0;
            };
            if (单剑.数值 == 0)
            {
                单剑.内容 = "  [开]";
                单剑.颜色 = 绘绿色;
            };
            if (单剑.数值 == 1) {
                单剑.内容 = "";
                单剑.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(99) & 1) == 1)

        {
            单刀.数值 = 单刀.数值 + 1;
            if (单刀.数值 > 1)
            {
                单刀.数值 = 0;
            };
            if (单刀.数值 == 0)
            {
                单刀.内容 = "  [开]";
                单刀.颜色 = 绘绿色;
            };
            if (单刀.数值 == 1) {
                单刀.内容 = "";
                单刀.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(100) & 1) == 1)
        {
            双剑.数值 = 双剑.数值 + 1;
            if (双剑.数值 > 1)
            {
                双剑.数值 = 0;
            };
            if (双剑.数值 == 0)
            {
                双剑.内容 = "  [开]";
                双剑.颜色 = 绘绿色;
            };
            if (双剑.数值 == 1) {
                双剑.内容 = "";
                双剑.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(101) & 1) == 1)

        {
            双刺.数值 = 双刺.数值 + 1;
            if (双刺.数值 > 1)
            {
                双刺.数值 = 0;
            };
            if (双刺.数值 == 0)
            {
                双刺.内容 = "  [开]";
                双刺.颜色 = 绘绿色;
            };
            if (双刺.数值 ==1) {
                双刺.内容 = "";
                双刺.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(102) & 1) == 1)
        {
            长剑.数值 = 长剑.数值 + 1;
            if (长剑.数值 > 1)
            {
                长剑.数值 = 0;
            };
            if (长剑.数值 == 0)
            {
                长剑.内容 = "  [开]";
                长剑.颜色 = 绘绿色;
            };
            if (长剑.数值 == 1) {
                长剑.内容 = "";
                长剑.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(103) & 1) == 1)
        {
            长刀.数值 = 长刀.数值 + 1;
            if (长刀.数值 > 1)
            {
                长刀.数值 = 0;
            };
            if (长刀.数值 == 0)
            {
                长刀.内容 = "  [开]";
                长刀.颜色 = 绘绿色;
            };
            if (长刀.数值 == 1) {
                长刀.内容 = "";
                长刀.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(104) & 1) == 1)
        {
            长枪.数值 = 长枪.数值 + 1;
            if (长枪.数值 > 1)
            {
                长枪.数值 = 0;
            };
            if (长枪.数值 == 0)
            {
                长枪.内容 = "  [开]";
                长枪.颜色 = 绘绿色;
            };
            if (长枪.数值 == 1) {
                长枪.内容 = "";
                长枪.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(105) & 1) == 1)//小键盘9
        {
            重剑.数值 = 重剑.数值 + 1;
            if (重剑.数值 > 1)
            {
                重剑.数值 = 0;
            };
            if (重剑.数值 == 0)
            {
                重剑.内容 = "  [开]";
                重剑.颜色 = 绘绿色;
            };
            if (重剑.数值 == 1) {
                重剑.内容 = "";
                重剑.颜色 = 绘白色;
            };
        };
        if ((GetAsyncKeyState(VK_F5) & 1) == 1)
        {
            一键.数值 = 一键.数值 + 1;
            if (一键.数值 > 3)
            {
                一键.内容 = "  [关闭]";
                一键.数值 = 0;
                一键.颜色 = 绘白色;
            };
            一键.颜色 = 绘绿色;
            if (一键.数值 == 1) {
                一键.内容 = "  [曝气]";
            }
            else if (一键.数值 == 2) {
                一键.内容 = "  [刺杀]";
            }
            else if (一键.数值 == 3) {
                一键.内容 = "  [全开]";
            };
        };
        if ((GetAsyncKeyState(VK_F2) & 1) == 1)
        {
            人物.数值 = 人物.数值 + 1;
            if (人物.数值 > 7)
            {
                人物.内容 = "  [关闭]";
                人物.数值 = 0;
                人物.颜色 = 绘白色;
            };
            人物.颜色 = 绘绿色;
            if (人物.数值 == 1) {
                人物.内容 = "  [方框]";
            }
            else if (人物.数值 == 2) {
                人物.内容 = "  [火柴]";
            }
            else if (人物.数值 == 3) {
                人物.内容 = "  [火距]";
            }
            else if (人物.数值 == 4) {
                人物.内容 = "  [骨骼]";
            }
            else if (人物.数值 == 5) {
                人物.内容 = "  [骨距]";
            }
            else if (人物.数值 == 6) {
                人物.内容 = "  [距离]";
            }
            else if (人物.数值 == 7) {
                人物.内容 = "  [精简]";
            };
        };
     Sleep(50);
    };
};
void     本人循环() {
    while (true) {
        世界地址 = 驱动.读长整数(模块地址 + 世界基址);
        名称地址 = 驱动.读长整数(模块地址 + 名称基址);
        矩阵地址 = 驱动.读长整数(驱动.读长整数(模块地址 + 矩阵基址) + 0x20) + 0x270;
        雷达地址 = 驱动.读长整数(驱动.读长整数(驱动.读长整数(驱动.读长整数(模块地址 + 雷达基址) + 0x20) + 0x158) + 0x08) + 0x90;
        本人.地址= 驱动.读长整数(驱动.读长整数(驱动.读长整数(世界地址 + 0x30) + 0xA8) + 0x48);
        本人.怒气 = 驱动.读小数型(驱动.读长整数(驱动.读长整数(驱动.读长整数(本人.地址 + 0x2A0) + 0x00) + 0xF8) + 0x24);
        if (瞄准.数值 == 0)
        {自瞄.基址 = 驱动.读长整数(驱动.读长整数(驱动.读长整数(世界地址 + 0x30) + 0xA8) + 0x28) + 0x398;};
        本人.指针 = 驱动.读长整数(本人.地址 + 0x2B0);
        本人.状态 = 驱动.读字节型(驱动.读长整数(本人.指针 + 0x50) + 0x101);
        相机.基址= 驱动.读长整数(本人.指针 + 0xE0);
        本人.武器 = 驱动.读整数型(驱动.读长整数(本人.指针 + 0x70) + 0x190);
        Sleep(255);
    };
};
void     雷达循环() {
    while (true) {
        取窗口坐标(游戏句柄, 游戏窗口.x, 游戏窗口.y, 游戏窗口.w, 游戏窗口.h, 游戏窗口.中心.x, 游戏窗口.中心.y);
        //绿竹窗口移动(游戏句柄, 游戏窗口.x, 游戏窗口.y, 游戏窗口.w, 游戏窗口.h);
        本人.坐标 = 绿竹读坐标(驱动.读长整数(本人.地址 + 0x158) + 0x1A0);
        相机.坐标 = 绿竹读坐标(相机.基址 + 0x1A0);
        if (本人.状态 == 3 || 本人.状态 > 7)
        {本人.坐标 = 相机.坐标;};
        读雷达(雷达地址);
        Sleep(25);
    };
};
void     对象读取() 
{
    DWORD64 起始 = 驱动.读长整数(世界地址 + 0x30);
    DWORD64 数组 = 驱动.读长整数(起始 + 0x98);
    int     数量 = 驱动.读整数型(起始 + 0xA0);
    for (int i = 0; i < 数量; i++) 
    {
        对象信息 对象;
        对象.地址= 驱动.读长整数(数组 + i * 0x08);
        if (对象.地址 == 本人.地址) { continue; };
            //cout << hex<<对象.地址 << "\n";
        对象.名称 = 驱动.读UE4标识(名称地址, 驱动.读整数型(对象.地址 + 0x18));
            //cout << 文本对比(对象.名称, 透视.玩家) << "\n";
        if (文本对比(对象.名称, 透视.玩家) != -1 || 文本对比(对象.名称, 透视.角色) != -1 || 文本对比(对象.名称, 透视.人机) != -1)
        {
            对象.状态 = 驱动.读字节型(驱动.读长整数(驱动.读长整数(对象.地址 + 0x2B0) + 0x50) + 0x101);
            if (对象.状态 == 3 || 对象.状态 == 11) { continue; };
            对象.坐标 = 绿竹读坐标(驱动.读长整数(对象.地址 + 0x158) + 0x1A0);
            if (对象.坐标.x == 0 && 对象.坐标.y == 0 && 对象.坐标.z == 0) { continue; };
            对象.距离 = 绿竹相机距离(对象.坐标);
            坐标4D 画框; 坐标2D 画屏;
            if (文本对比(对象.名称, 透视.人机) == -1)
            {
                if (雷达.数值 == 0) { if (本人.状态 != 3) { 画雷达; }; };

                if (对象.距离 < 15 && 防空.数值 == 0) { mouse_event(0x18, 0, 0, 0, 0); };
                对象.距离 = 绿竹矩阵距离(对象.坐标);
                if (对象.距离 >= 0 )
                {
                    if (人物.数值 > 0) {
                    
                        画框 = 绿竹矩阵转4D(对象.坐标);
                        if (人物.数值 == 1) { 绘制方框(画框.x, 画框.y, 画框.w, 画框.h, 绘艳青, 2); };
                        const char* 文本;
                        if (人物.数值 == 1 || 人物.数值 == 3 || 人物.数值 > 4)
                        {
                            对象.武器 = 驱动.读整数型(驱动.读长整数(驱动.读长整数(对象.地址 + 0x2B0) + 0x70) + 0x190); string 状态 = 状态返回(对象.状态);
                            if (人物.数值 == 7) { 文本 = (状态 + to_string(对象.距离) + 米).c_str(); }
                            else { 文本 = (武器返回(对象.武器) + 状态 + to_string(对象.距离) + 米).c_str(); };
                            画屏 = 绿竹矩阵转2D(对象.坐标);
                            if (瞄准.数值 == 0 && 自瞄.地址 == 对象.地址 && GetAsyncKeyState(VK_RBUTTON) != 0) {
                                描边文本("已瞄准", 画屏.x, 画屏.y, 绘黑色, 绘橙黄);
                            }
                            else if (对象.武器 == 14 || 对象.武器 == 16) {
                                描边文本(文本, 画框.x, 画框.y + 画框.h, 绘黑色, 绘橙黄);
                            }
                            else { 描边文本(文本, 画框.x, 画框.y + 画框.h, 绘黑色, 绘艳青); };
                        };
                        if (文本对比(对象.名称, 透视.玩家) != -1) {
                            绿竹矩阵骨骼(驱动.读长整数(对象.地址 + 0x390), 绘艳青, 2);
                            if (瞄准.数值 == 0 && 自瞄.锁定 == false) { 绿竹自瞄目标(画屏, 对象.地址); };
                        };
                    
                    
                    };
                   
                };
                continue;
            }
            else {
                对象.距离 = 绿竹矩阵距离(对象.坐标);
                if (对象.距离!=0) {
                    画框 = 绿竹矩阵转4D(对象.坐标);
                    绘制方框(画框.x, 画框.y, 画框.w, 画框.h, 2, 绘艳青);
                    绘制文本((string("人机") + to_string(对象.距离) + 米).c_str(), 画框.x, 画框.y + 画框.h, 绘艳青);
                    continue;
                };
            };
        };
        if (马匹.数值 == 0)
        {
            if (文本对比(对象.名称, 透视.快递) != -1 || 文本对比(对象.名称, 透视.载具) != -1 || 文本对比(对象.名称, 透视.空投) != -1) {
                对象.坐标 = 绿竹读坐标(驱动.读长整数(对象.地址 + 0x158) + 0x1A0);
                if (对象.坐标.x == 0 && 对象.坐标.y == 0 && 对象.坐标.z == 0) { continue; };
                对象.距离 = 绿竹相机距离(对象.坐标);
                if (对象.距离 > 3) {
                    坐标2D 画出 = 绿竹矩阵转2D(对象.坐标);
                    if (画出.x == 0 && 画出.y == 0) {}
                    else {
                        if (文本对比(对象.名称, 透视.载具) != -1) {
                            描边文本((string("宝马  ") + to_string(对象.距离) + 米).c_str(), 画出.x, 画出.y, 绘黑色, 绘绿色);
                            continue;
                        }
                        else if (文本对比(对象.名称, 透视.快递) != -1) {
                            描边文本((string("快递  ") + to_string(对象.距离) + 米).c_str(), 画出.x, 画出.y, 绘黑色, 绘黄色);
                            continue;
                        }
                        else {
                            描边文本((string("空投  ") + to_string(对象.距离) + 米).c_str(), 画出.x, 画出.y, 绘黑色, 绘红色);
                            continue;
                        };
                    };
                };
            };
        };
        if (物资.数值 == 0) {
            if (文本对比(对象.名称, 透视.物资) != -1) {
                对象.坐标 = 绿竹读坐标(驱动.读长整数(对象.地址 + 0x158) + 0x1A0);
                if (对象.坐标.x == 0 && 对象.坐标.y == 0 && 对象.坐标.z == 0) { continue; };
                绘制信息 绘制 = 判断物资(驱动.读整数型(对象.地址 + 0x354));
                if (绘制.颜色!=0) {
                    对象.距离 = 绿竹矩阵距离(对象.坐标);
                    if (对象.距离>0) {
                        坐标2D 画出 = 绿竹矩阵转2D(对象.坐标);
                        if (对象.距离 > 50) { continue; };
                        if (对象.距离 < 5) { 描边文本((绘制.内容).c_str(), 画出.x, 画出.y, 绘黑色, 绘制.颜色); }
                        else { 描边文本((绘制.内容 + string(" ") + to_string(对象.距离)).c_str(), 画出.x, 画出.y, 绘黑色, 绘制.颜色); };
                    };
               };
            };
        };
    };
    if (瞄准.数值 == 0) { 绿竹自瞄锁敌(); };
};
void     绘制菜单()
{
    int  行距 = 350;
    if (菜单.数值 == 0)
    {
        描边文本("[Hom] 显隐菜单 ", 0, 0, 绘白色, 绘黑色);
        描边文本((string("  F1键     物品透视") + 物资.内容).c_str(), 60, 行距, 绘黑色, 物资.颜色);
        行距 = 行距 + 20;
        描边文本((string(" |小键盘* 空投马匹| ") + 马匹.内容).c_str(), 60, 行距, 绘黑色, 马匹.颜色);
        if (物资.数值 == 0) {
            行距 = 行距 + 20;
            描边文本((string(" |小键盘0 垃圾道具| ") + 垃圾.内容).c_str(), 60, 行距, 绘黑色, 垃圾.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘1 徒手功法| ") + 徒手.内容).c_str(), 60, 行距, 绘黑色, 徒手.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘2 单剑功法| ") + 单剑.内容).c_str(), 60, 行距, 绘黑色, 单剑.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘3 单刀功法| ") + 单刀.内容).c_str(), 60, 行距, 绘黑色, 单刀.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘4 双剑功法| ") + 双剑.内容).c_str(), 60, 行距, 绘黑色, 双剑.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘5 双刺功法| ") + 双刺.内容).c_str(), 60, 行距, 绘黑色, 双刺.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘6 长剑功法| ") + 长剑.内容).c_str(), 60, 行距, 绘黑色, 长剑.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘7 长刀功法| ") + 长刀.内容).c_str(), 60, 行距, 绘黑色, 长刀.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘8 长枪功法| ") + 长枪.内容).c_str(), 60, 行距, 绘黑色, 长枪.颜色);
            行距 = 行距 + 20;
            描边文本((string(" |小键盘9 重剑功法| ") + 重剑.内容).c_str(), 60, 行距, 绘黑色, 重剑.颜色);
        };
        行距 = 行距 + 20;
        描边文本((string("  F2键     人物透视") + 人物.内容).c_str(), 46, 行距, 绘黑色, 人物.颜色);
        行距 = 行距 + 20;
        描边文本((string("  F3键     自瞄开关") + 瞄准.内容).c_str(), 46, 行距, 绘黑色, 瞄准.颜色);
        行距 = 行距 + 20;
        描边文本((string("  F4键     雷达开关") + 雷达.内容).c_str(), 46, 行距, 绘黑色, 雷达.颜色);
        行距 = 行距 + 20;
        描边文本((string("  F5键     智能一键") + 一键.内容).c_str(), 46, 行距, 绘黑色, 人物.颜色);
        行距 = 行距 + 20;
        描边文本((string("  F6键     防空开关") + 防空.内容).c_str(), 46, 行距, 绘黑色, 防空.颜色);
    };
    Sleep(3);
};
void     绘制循环() {
    绘制菜单();
    对象读取();
    Sleep(1);};
string   状态返回(int _a) {

    if (_a == 6) { return "偷"; };
    if (_a == 2) { return "偷"; };
    if (_a == 1) { return "攻"; };
    return "距";
};
string   武器返回(int _a) {

    if (_a == 0) { return "徒手-"; };
    if (_a == 1) { return "单剑-"; };
    if (_a == 2) { return "单刀-"; };
    if (_a == 3) { return "双剑-"; };
    if (_a == 4) { return "双刺-"; };
    if (_a == 5) { return "长剑-"; };
    if (_a == 6) { return "长刀-"; };
    if (_a == 7) { return "重剑-"; };
    if (_a == 8) { return "长枪-"; };
    if (_a == 10) { return "长弓-"; };
    if (_a == 11) { return "飞镖-"; };
    if (_a == 12) { return "投弹-"; };
    if (_a == 13) { return "弩弓-"; };
    if (_a == 14) { return "鸟统-"; };
    if (_a == 15) { return "流星-"; };
    if (_a == 16) { return "三眼-"; };
    return "-";
};
绘制信息 判断物资(int _a) 
{
    static 绘制信息 _b;
    if (_a == 110010) {
        _b.颜色 = 绘白色;
        _b.内容 = "[饲] 高料";
        return _b;
    }
    else if (_a == 110011) {
        _b.颜色 = 绘白色;
        _b.内容 = "[饲] 特料";
        return _b;
    }
    else if (_a == 120020) {
        _b.颜色 = 绘白色;
        _b.内容 = "[投] 迷烟";
        return _b;
    }
    else if (_a == 120017) {
        _b.颜色 = 绘白色;
        _b.内容 = "[远] 长弓";
        return _b;
    }
    else if (_a == 120018) {
        _b.颜色 = 绘白色;
        _b.内容 = "[远] 箭支";
        return _b;
    }
    else if (_a == 120021) {
        _b.颜色 = 绘白色;
        _b.内容 = "[远] 弩弓";
        return _b;
    }
    else if (_a == 120022) {
        _b.颜色 = 绘白色;
        _b.内容 = "[远] 弩箭";
        return _b;
    }
    else if (_a == 130114) {
        _b.颜色 = 绘白色;
        _b.内容 = "[防] 一包";
        return _b;
    }

    else if (_a == 110005) {
        _b.颜色 = 绘绿色;
        _b.内容 = "[药] 金疮";
        return _b;
    }
    else if (_a == 110006) {
        _b.颜色 = 绘绿色;
        _b.内容 = "[药] 续命";
        return _b;
    }

    else if (_a == 120016) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[投] 飞镖";
        return _b;
    }
    else if (_a == 120039) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[修] 铁片";
        return _b;
    }
    else if (_a == 140030) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[技] 游墙";
        return _b;
    }
    else if (_a == 140035) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[心] 吐纳";
        return _b;
    }
    else if (_a == 140036) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[心] 天罡";
        return _b;
    }
    else if (_a == 140068) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[心] 紫霞";
        return _b;
    }
    else if (_a == 140070) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[心] 纯阳";
        return _b;
    }
    else if (_a == 140071) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[秘] 血针";
        return _b;
    }
    else if (_a == 140072) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[秘] 寸芒";
        return _b;
    }
    else if (_a == 140074) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[秘] 摩叱";
        return _b;
    }
    else if (_a == 140075) {
        _b.颜色 = 绘青绿;
        _b.内容 = "[秘] 燕归";
        return _b;
    }

    else if (_a == 110007) {
        _b.颜色 = 绘橙黄;
        _b.内容 = "[药] 大补";
        return _b;
    }
    else if (_a == 110008) {
        _b.颜色 = 绘橙黄;
        _b.内容 = "[药] 华佗";
        return _b;
    }
    else if (_a == 110013) {
        _b.颜色 = 绘橙黄;
        _b.内容 = "[物] 普石";
        return _b;
    }
    else if (_a == 130034) {
        _b.颜色 = 绘橙黄;
        _b.内容 = "[极] 三甲";
        return _b;
    }
    else if (_a == 140065) {
        _b.颜色 = 绘橙黄;
        _b.内容 = "[密] 断龙";
        return _b;
    }
    else if (_a == 140066) {
        _b.颜色 = 绘橙黄;
        _b.内容 = "[密] 墨衍";
        return _b;
    }
    else if (_a == 130001 || _a == 130158) {
        _b.颜色 = 绘黄色;
        _b.内容 = "[防] 二帽";
        return _b;
    }
    else if (_a == 130004) {
        _b.颜色 = 绘黄色;
        _b.内容 = "[防] 二包";
        return _b;
    }
    else if (_a == 130033) {
        _b.颜色 = 绘黄色;
        _b.内容 = "[防] 二甲";
        return _b;
    }
    else if (_a == 120019) {
        _b.颜色 = 绘红色;
        _b.内容 = "[投] 手雷";
        return _b;
    }
    else if (_a == 120023) {
        _b.颜色 = 绘红色;
        _b.内容 = "[炮] 鸟铳";
        return _b;
    }
    else if (_a == 120024) {
        _b.颜色 = 绘红色;
        _b.内容 = "[弹] 铁砂";
        return _b;
    }
    else if (_a == 120026) {
        _b.颜色 = 绘红色;
        _b.内容 = "[炮] 三眼";
        return _b;
    }
    else if (_a == 120027) {
        _b.内容 = "[弹] 铸铁";
        return _b;
    }

    else if (_a == 120007) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 单剑";
        return _b;
    }
    else if (_a == 120008) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 单刀";
        return _b;
    }
    else if (_a == 120009) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 双剑";
        return _b;
    }
    else if (_a == 120010) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 双刺";
        return _b;
    }
    else if (_a == 120011) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 长剑";
        return _b;
    }
    else if (_a == 120012) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 长刀";
        return _b;
    }
    else if (_a == 120013) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 重剑";
        return _b;
    }
    else if (_a == 120014) {
        _b.颜色 = 绘艳青;
        _b.内容 = "[器] 长枪";
        return _b;
    }

    else if (_a == 110012) {
        _b.颜色 = 绘品红;
        _b.内容 = "[密] 钥匙";
        return _b;
    }
    else if (_a == 110014) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 稀石";
        return _b;
    }
    else if (_a == 110015) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 陨石";
        return _b;
    }
    else if (_a == 110018) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 灵芝";
        return _b;
    }
    else if (_a == 110019) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 雪莲";
        return _b;
    }
    else if (_a == 120015) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 空牙";
        return _b;
    }
    else if (_a == 120033) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 墨文";
        return _b;
    }
    else if (_a == 130019) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 三帽";
        return _b;
    }
    else if (_a == 140028) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 格反";
        return _b;
    }
    else if (_a == 140067) {
        _b.颜色 = 绘品红;
        _b.内容 = "[极] 金刚";
        return _b;
    }
    else if (_a == 140069) {
        _b.颜色 = 绘品红;
        _b.内容 = "[心] 混元";
        return _b;
    };
    if (垃圾.数值 == 0)
    {
        _b.颜色 = 绘白色;
        if (_a == 110003) {
            _b.内容 = "[药] 纱布";
            return _b;
        }
        else if (_a == 110004) {
            _b.内容 = "[药] 解毒";
            return _b;
        }
        else if (_a == 110009) {
            _b.内容 = "[饲] 普料";
            return _b;
        }
        else if (_a == 120036) {
            _b.内容 = "[陷] 竹刺";
            return _b;
        }
        else if (_a == 120035) {
            _b.内容 = "[陷] 毒坛";
            return _b;
        }
        else if (_a == 120034) {
            _b.内容 = "[陷] 兽夹";
            return _b;
        }
        else if (_a == 120025) {
            _b.内容 = "[投] 流星";
            return _b;
        }
        else if (_a == 120028) {
            _b.内容 = "[器] 斧头";
            return _b;
        }
        else if (_a == 120029) {
            _b.内容 = "[器] 柴刀";
            return _b;
        }
        else if (_a == 120030) {
            _b.内容 = "[器] 镰刀";
            return _b;
        }
        else if (_a == 120031) {
            _b.内容 = "[器] 鱼叉";
            return _b;
        }
        else if (_a == 120032) {
            _b.内容 = "[器] 钢叉";
            return _b;
        }
        else if (_a == 120037) {
            _b.内容 = "[修] 布片";
            return _b;
        }
        else if (_a == 120038) {
            _b.内容 = "[修] 皮片";
            return _b;
        }
        else if (_a == 130018) {
            _b.内容 = "[防] 一帽";
            return _b;
        }
        else if (_a == 130032) {
            _b.内容 = "[防] 一甲";
            return _b;
        }
        else if (_a == 140031) {
            _b.内容 = "[技] 梯云";
            return _b;
        }
        else if (_a == 140033) {
            _b.内容 = "[技] 轻身";
            return _b;
        }
        else if (_a == 140037) {
            _b.内容 = "[心] 般若";
            return _b;
        };

    };
    if (徒手.数值 == 0)
    {
        _b.颜色 = 绘青绿;
        if (_a == 140001) {
            _b.内容 = "[功] 徒手一";
            return _b;
        }
        else if (_a == 140003) {
            _b.内容 = "[功] 徒手三";
            return _b;
        }
        else if (_a == 140002) {
            _b.内容 = "[功] 徒手二";
            _b.颜色 = 绘橙黄;
            return _b;
        };


    };
    if (单剑.数值 == 0) {
        _b.颜色 = 绘青绿;
        if (_a == 140005) {
            _b.内容 = "[功] 单剑二";
            return _b;
        }
        else if (_a == 140043) {
            _b.内容 = "[功] 单剑六";
            return _b;
        }
        else if (_a == 140004) {
            _b.内容 = "[功] 单剑一";
            _b.颜色 = 绘橙黄;
            return _b;
        };

    };
    if (单刀.数值 == 0) {
        _b.颜色 = 绘青绿;
        if (_a == 140007) {
            _b.内容 = "[功] 单刀一";
            return _b;
        }
        else if (_a == 140045) {
            _b.内容 = "[功] 单刀五";
            return _b;
        }
        else if (_a == 140009) {
            _b.内容 = "[功] 单刀三";
            return _b;
        }
        else if (_a == 140044) {
            _b.内容 = "[功] 单刀四";
            _b.颜色 = 绘橙黄;
            return _b;
        };

    };
    if (长刀.数值 == 0)
    {
        _b.颜色 = 绘青绿;
        if (_a == 140019) {
            _b.内容 = "[功] 长刀一";
            return _b;
        }
        else if (_a == 140020) {
            _b.内容 = "[功] 长刀二";
            return _b;
        }
        else if (_a == 140058) {
            _b.内容 = "[功] 长刀六";
            _b.颜色 = 绘橙黄;
            return _b;
        };

    };
    if (长枪.数值 == 0) {
        _b.颜色 = 绘青绿;
        if (_a == 140025) {
            _b.内容 == "[功] 长枪一";
            return _b;
        }
        else if (_a == 140064) {
            _b.内容 = "[功] 长枪六";
            return _b;
        }
        else if (_a == 140063) {
            _b.内容 = "[功] 长枪五";
            _b.颜色 = 绘橙黄;
            return _b;
        };


    };
    if (双剑.数值 == 0) {
        _b.颜色 = 绘青绿;
        if (_a == 140012) {
            _b.内容 = "[功] 双剑三";
            return _b;
        }
        else if (_a == 140047) {
            _b.内容 = "[功] 双剑四";
            return _b;
        }
        else if (_a == 140049) {
            _b.内容 = "[功] 双剑六";
            return _b;
        };

    };
    if (双刺.数值 == 0) {
        _b.颜色 = 绘青绿;
        if (_a == 140050) {
            _b.内容 = "[功] 双刺四";
            return _b;
        }
        else if (_a == 140051) {
            _b.内容 = "[功] 双刺五";
            return _b;
        }
        else if (_a == 140052) {
            _b.内容 = "[功] 双刺六";
            return _b;
        }
        else if (_a == 140015) {
            _b.内容 = "[功] 双刺三";
            _b.颜色 = 绘橙黄;
            return _b;
        };

    };
    if (长剑.数值 == 0) {
        _b.颜色 = 绘青绿;
        if (_a == 140016) {
            _b.内容 = "[功] 长剑一";
            return _b;
        }
        else if (_a == 140054) {
            _b.内容 = "[功] 长剑五";
            return _b;
        }
        else if (_a == 140055) {
            _b.内容 = "[功] 长剑六";
            return _b;
        };

    };
    if (重剑.数值 == 0) {
        _b.颜色 = 绘青绿;
        if (_a == 140023) {
            _b.内容 = "[功] 重剑二";
            return _b;
        }
        else if (_a == 140059) {
            _b.内容 = "[功] 重剑四";
            return _b;
        }
        else if (_a == 140061) {
            _b.内容 = "[功] 重剑六";
            return _b;
        }
        else if (_a == 140022) {
            _b.内容 = "[功] 重剑一";
            _b.颜色 = 绘橙黄;
            return _b;
        };
    };
    _b.内容 = "啥也没有";
    _b.颜色 = 0;
    return _b;
 };

//---------------透视开始----------------
int main() {
    透明主题();

    绿竹初始透视();

    do {
        游戏句柄 = 绿竹窗口取句柄(窗口类名, 窗口标题);
        cout << "游戏id：" << "游戏句柄" << 游戏句柄 << "\n";
        游戏id = 绿竹进程名取ID(进程名称);
        cout << "游戏id：" << "\n";
        驱动.设置进程(游戏id);
        游戏窗口 = 绿竹窗口取坐标(游戏句柄);
        cout << "游戏id：" << 游戏id << "游戏句柄" << 游戏句柄 << "\n";
        模块地址= 驱动.取模块地址(进程名);
        cout << "模块地址" << 模块地址 << "\n";
        Sleep(500);
    } while (模块地址<65535);


    int 句柄 = 窗口创建(18, "微软雅黑", "我爱一根柴", "风流人物");
    cout << 句柄 << "\n";
    CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)视野循环, 0, 0, 0));
    CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)热键循环, 0, 0, 0));
    CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)本人循环, 0, 0, 0));
    CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)雷达循环, 0, 0, 0));
    绘制程序(绘制循环);
    消息循环();
    return 0;
};
