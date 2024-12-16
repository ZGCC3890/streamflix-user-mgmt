#ifndef USTIL_H  // 如果没有定义宏 USTIL_H
#define USTIL_H  // 定义宏 USTIL_H
#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <pqxx/pqxx>

#define CommonBlue RGB(50, 100, 200)
#define LightBlue RGB(70, 120, 210)

extern pqxx::connection conn;
extern pqxx::work txn;
extern pqxx::result res;

extern ExMessage msg;//鼠标信息结构体

typedef struct User{
    std::string userName;
    std::string password;
}User;

typedef struct object{
    int posx;
    int posy;
    int width;
    int height;
}object;

extern User root;

//重写版fillroundrect（圆角矩形）
void fillroundrect_(object x);
//重写版roundrect（圆角矩形线框）
void roundrect_(object x);
//重写版fillrectangle（矩形）
void fillrectangle_(object x);
//重写版rectangle（圆角矩形线框）
void rectangle_(object x);
//判断是否在object内
bool isInside(ExMessage m, object x);
//输出函数封装（字体颜色，字号，字体，输出位置）
void OutputText(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st);
//按钮效果封装（默认线宽=2，类型为roundrect圆角矩形）
void ButtonAnimation(ExMessage m, object x, COLORREF colorOn, COLORREF colorOff, int lineWidth = 2, std::string sort = "roundrect");
//重置鼠标
void InitMouseMsg();

void Menu(int n);
void MenuAnimation(int mx, int my, int n);

//界面跳转
extern int choose;
extern int qchoose;
int ChooseGraph(int mx, int my);

//登录界面
extern User tmp;
extern bool endsystem;
#endif // USTIL_H
