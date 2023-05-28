#include<iostream>
#include<cstdio>
#include<tchar.h> // 包含TCHAR和_tprintf函数的头文件
#include<windows.h>
#include<fstream>
#include<random>
#include <filesystem>
#include<commdlg.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include<sstream>
using namespace std;
int s, language;
string zeros;
string Paths;
int _lock = 1;
string giPath;
void LOG_INFO(string x) {

    default_random_engine generator;
    uniform_int_distribution<int> distribution(31, 37);

    int color = distribution(generator);
    cout << "\033[" << color << "m"<<x<<"\033[0m" << endl;
}
string GetGIPath() {
    ifstream file("config.ini");
    string line;
    string w;

    while (getline(file, line)) {
        // 去掉行首和行尾的空格
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // 如果line为空行或者以";"开头，忽略
        if (line.empty() || line[0] == ';') {
            continue;
        }

        // 如果line以"[GIpath]"开头，则获取路径
        if (line == "[GIpath]") {
            getline(file, line);
            w = line;
            break;
        }
    }

    return w;
}
int _configL()
{
    if (language == 1)
        LOG_INFO("正在加载配置文件...");
    else
        LOG_INFO("loading config...");
    ifstream file("config.ini");
    if (file.good()) {
        giPath = GetGIPath();
        if (language == 1)
            LOG_INFO("配置文件加载成功");
        else
            LOG_INFO("config.ini load success");
    }
    else {
        if (language == 1)
            cout << "config.ini文件不存在于当前目录" << endl;
        else
            cout << "config.ini does not exist" << endl;
        ofstream config("config.ini");
        string w = "...path...";
        OPENFILENAME ofn;       // 定义一个OPENFILENAME结构体，用于存储文件选择框的选项和结果
        // 初始化OPENFILENAME结构体
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFilter = "Yuanshen.exe;GenshinImpact.EXE\0Yuanshen.exe;GenshinImpact.EXE\0All Files\0*.*\0";
        TCHAR szFile[MAX_PATH];
        ofn.lpstrFile = szFile;
        ofn.lpstrFile[0] = L'\0';
        ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        if (GetOpenFileName(&ofn) == TRUE)
        {
            // 将ofn.lpstrFile转换为string类型
            string selectedFile(ofn.lpstrFile);
            zeros = selectedFile;
        }
        else
        {
            // 用户取消了选择，你可以在这里进行相关操作
            LOG_INFO("谁叫你乱点退出的😓");
            return 0;
        }
        config << "[GIpath]" << endl;
        config << "{" << zeros << "}" << endl;
        config.close();
        _lock = 0;
    }
    return 0;
}
string GetPath()
{
    giPath = GetGIPath();
    size_t pos = 0;
    while ((pos = giPath.find('{', pos)) != string::npos) {  // 查找左花括号
        giPath.erase(pos, 1);  // 删除左花括号
    }
    pos = 0;
    while ((pos = giPath.find('}', pos)) != string::npos) {  // 查找右花括号
        giPath.erase(pos, 1);  // 删除右花括号
    }
    // 获取程序路径
    filesystem::path programPath = filesystem::path(giPath);

    // 获取程序所在目录
    filesystem::path programDirectory = programPath.parent_path();

    // 将目录路径转换为字符串
    string programDirectoryString = programDirectory.string();

    return programDirectoryString;
}
int BypassStart()
{
    LOG_INFO("开始启动游戏并bypass");
    filesystem::path path(Paths);
    string filename = "HoYoKProtect.sys";
    filesystem::path file_path = path / filename;
    if (filesystem::exists(file_path)) {
        cout << "HoYoKProtect存在，正在使用方法A绕过" << endl;
        filesystem::path old_name = path / "HoYoKProtect.sys";
        filesystem::path new_name = path / "HoYoBypass.sys";
        try {
            filesystem::rename(old_name, new_name);
            LOG_INFO("绕过方法A成功");
        }
        catch (filesystem::filesystem_error& e) {
            cout << "绕过方法A失败: " << e.what() << endl;
        }
    }
    else {
        cout << "HoYoKProtect不存在，请检查你的游戏" << endl;
    }

    filename = "mhypbase.dll";
    file_path = path / filename;
    if (filesystem::exists(file_path)) {
        cout << "MHYPbase存在，正在使用方法A绕过" << endl;
        filesystem::path old_name = path / "mhypbase.dll";
        filesystem::path new_name = path / "mhyPBypass.dll";
        try {
            filesystem::rename(old_name, new_name);
            LOG_INFO("绕过方法A成功");
        }
        catch (filesystem::filesystem_error& e) {
            cout << "绕过方法A失败: " << e.what() << endl;
        }
    }
    else {
        cout << "MHYPbase不存在，请检查你的游戏" << endl;
    }
    filename = "mhyprot3.Sys";
    file_path = path / filename;
    if (filesystem::exists(file_path)) {
        cout << "mhyprot3文件存在，正在使用方法A绕过" << endl;
        filesystem::path old_name = path / "mhyprot3.Sys";
        filesystem::path new_name = path / "mhyP3Bypass.Sys";
        try {
            filesystem::rename(old_name, new_name);
            LOG_INFO("绕过方法A成功");
        }
        catch (filesystem::filesystem_error& e) {
            cout << "绕过方法A失败: " << e.what() << endl;
        }
    }
    else {
        cout << "mhyprot3文件不存在，请检查你的游戏" << endl;
    }

    return 0;
}
int main()
{
    system("title OpenKebiAtBypass");
    LOG_INFO("[OpenKebiAtBypass]");
    LOG_INFO("[原神！启动！]");
    LOG_INFO("--------");
    LOG_INFO("请选择语言 | plz select language");
    LOG_INFO("1. 中文(zh-cn)");
    LOG_INFO("2. 英文(en)");
    while (!(s == 1 || s == 2))
    {
        if (!(language == 1 || language == 2) && !(language == 0))
            LOG_INFO("语言输入错误 | Language ERROR??? WT LOSER IQ USRE???");
        cin >> s;
        language = s;
    }
    LOG_INFO("-------");
    _configL();
    if (_lock == 1)
        int love = 1;
    else
        giPath = zeros;
    Paths = GetPath();
    cout << "程序所在目录：" << Paths << endl;
    LOG_INFO("回车启动游戏并绕过尝试本地反作弊");
    system("pause");
    BypassStart();
    return 0;
    
    
}