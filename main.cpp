#include <bits/stdc++.h>
#include <graphics.h>
#include <conio.h>
#include <pqxx/pqxx>
#include "UserQuery.h"
#include "GoodsQuery.h"

using namespace std;

pqxx::connection conn(
        "dbname=SMUMS057 user=dboper password=dboper@321 host=120.46.71.168 port=26000 options='-c client_encoding=UTF8'");
pqxx::work txn(conn);
pqxx::result res;

ExMessage msg;//鼠标信息结构体

User root = {"root", "admin"};

User tmp = {"root", "admin"};

//重写版fillroundrect（圆角矩形）
void fillroundrect_(object x){
    fillroundrect(x.posx, x.posy, x.posx + x.width, x.posy + x.height, 10, 10);
}

//重写版roundrect（圆角矩形线框）
void roundrect_(object x){
    roundrect(x.posx, x.posy, x.posx + x.width, x.posy + x.height, 10, 10);
}

//重写版fillrectangle（矩形）
void fillrectangle_(object x){
    fillrectangle(x.posx, x.posy, x.posx + x.width, x.posy + x.height);
}

//重写版rectangle（圆角矩形线框）
void rectangle_(object x){
    rectangle(x.posx, x.posy, x.posx + x.width, x.posy + x.height);
}

//判断是否在object内
bool isInside(ExMessage m, object x){
    if(m.x >= x.posx && m.x <= x.posx + x.width && m.y <= x.posy + x.height && m.y >= x.posy) return true;
    return false;
}

//输出函数封装（字体颜色，字号，字体，输出位置）
void OutputText(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st){
    settextcolor(color);
    settextstyle(nH,nW,st);
    outtextxy(x, y, str);
}

//按钮效果封装
void ButtonAnimation(ExMessage m, object x, COLORREF colorOn, COLORREF colorOff, int lineWidth, string sort){
    if(isInside(m, x)){
        setlinecolor(colorOn);
        if(sort == "roundrect")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
        else if(sort == "rectangle")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
    }else{
        setlinecolor(colorOff);
        if(sort == "roundrect")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
        else if(sort == "rectangle")
            for (int i = 0; i < lineWidth; ++i) roundrect_({x.posx + i, x.posy + i, x.width - 2 * i, x.height - 2 * i});
    }
}

//重置鼠标
void InitMouseMsg(){
    msg.x = 0, msg.y = 0;
}

//界面跳转
int choose = 1;
int qchoose;
int ChooseGraph(int mx, int my){
    if(mx >= 0 && mx <= 170){
        if(my >= 25 && my <= 115){
            return 1;//查询用户信息UserQuery()
        }
        else if(my >= 115 && my <= 205){
            return 4;//查询商品信息GoodsQuery()
        }
        else if(my >= 205 && my <= 295){
            return 3;//查找学生信息SearchStudent()
        }
        else if(my >= 295 && my <= 385){
            return 4;//选择排名方式Sort_or_Score()
        }
        else if(my >= 385 && my <= 475){
            return 5;//修改学生信息ChangeStudent()
        }
        else if(my >= 475 && my <= 565){
            return 6;//删除学生信息DelStudent()
        }
        else if(my >= 565 && my <= 645){
            return 7;//设置Setting()
        }
        else if(my >= 645 && my <= 720){
            qchoose = choose;
            return 8;//退出Quitgraph()
        }
    }
}

//左侧菜单列表
void Menu(int n){
    cleardevice();
    setlinecolor(CommonBlue);
    setfillcolor(CommonBlue);
    fillrectangle(0, 0, 170, 720);
    setlinecolor(LightBlue);
    setfillcolor(LightBlue);
    fillrectangle(0, 25 + (n - 1) * 90, 170, 25 + n * 90);
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 180, 55, false);
    putimage(870, 5, &ah);
    OutputText(20,60,WHITE,20,0,"用户信息面板", "宋体");
    OutputText(20,150,WHITE,20,0,"商品信息面板", "宋体");
    OutputText(20,240,WHITE,20,0,"评论信息面板", "宋体");
    OutputText(20,330,WHITE,20,0,"动态信息面板", "宋体");
    OutputText(20,420,WHITE,20,0,"稿件信息面板", "宋体");
    OutputText(20,510,WHITE,20,0,"管理员信息面板", "宋体");
    OutputText(55,600,WHITE,20,0,"设置", "宋体");
    OutputText(55,680,WHITE,20,0,"退出", "宋体");
}

//菜单动画
void MenuAnimation(int mx, int my, int n){
    if(mx >= 0 && mx <= 170 && my >= 25 && my <= 115 && n != 1)
        OutputText(20,60,YELLOW,20,0,"用户信息面板", "宋体");
    else OutputText(20,60,WHITE,20,0,"用户信息面板", "宋体");
    if(mx >= 0 && mx <= 170 && my >= 115 && my <= 205 && n != 2)
        OutputText(20,150,YELLOW,20,0,"商品信息面板", "宋体");
    else OutputText(20,150,WHITE,20,0,"商品信息面板", "宋体");
    if(mx >= 0 && mx <= 170 && my >= 205 && my <= 295 && n != 3)
        OutputText(20,240,YELLOW,20,0,"评论信息面板", "宋体");
    else OutputText(20,240,WHITE,20,0,"评论信息面板", "宋体");
    if(mx >= 0 && mx <= 170 && my >= 295 && my <= 385 && n != 4)
        OutputText(20,330,YELLOW,20,0,"动态信息面板", "宋体");
    else OutputText(20,330,WHITE,20,0,"动态信息面板", "宋体");
    if(mx >= 0 && mx <= 170 && my >= 385 && my <= 475 && n != 5)
        OutputText(20,420,YELLOW,20,0,"稿件信息面板", "宋体");
    else OutputText(20,420,WHITE,20,0,"稿件信息面板", "宋体");
    if(mx >= 0 && mx <= 170 && my >= 475 && my <= 565 && n != 6)
        OutputText(20,510,YELLOW,20,0,"管理员信息面板", "宋体");
    else OutputText(20,510,WHITE,20,0,"管理员信息面板", "宋体");
    if(mx >= 0 && mx <= 170 && my >= 565 && my <= 645 && n != 7)
        OutputText(55,600,YELLOW,20,0,"设置", "宋体");
    else OutputText(55,600,WHITE,20,0,"设置", "宋体");
    if(mx >= 0 && mx <= 170 && my >= 645 && my <= 720 && n != 8)
        OutputText(55,680,YELLOW,20,0,"退出", "宋体");
    else OutputText(55,680,WHITE,20,0,"退出", "宋体");
}

//账密检查
bool loginCheck(){
    if(tmp.userName == root.userName && tmp.password == root.password) return true;
    else return false;
}
//开始界面绘制
void startgraph() {
    flushmessage(EM_MOUSE);
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 250, 80, false);
    putimage(400, 150, &ah);
    setlinecolor(BLACK);
    rectangle(290,250,790,295);
    OutputText(310, 260, BLACK, 30, 0, "欢迎使用流媒体网站用户管理系统", "楷体");

    object user = {400, 310, 280, 35};
    object password = {400, 360, 280, 35};
    setfillcolor(WHITE);
    fillroundrect_(user);
    fillroundrect_(password);
    OutputText(user.posx + 20, user.posy + 10, RGB(200, 200, 200), 17, 0, "请输入用户名", "宋体");
    OutputText(password.posx + 20, password.posy + 10, RGB(200, 200, 200), 17, 0, "请输入密码", "宋体");

    object login = {450, 410, 180, 35};
    object exit = {450, 460, 180, 35};
    setfillcolor(CommonBlue);
    fillroundrect_(login);
    fillroundrect_(exit);
    OutputText(login.posx + 70, login.posy + 10, WHITE, 20, 0, "登录", "楷体");
    OutputText(exit.posx + 70, exit.posy + 10, WHITE, 20, 0, "退出", "楷体");

    while(true){
        flushmessage(EM_MOUSE);
        if(peekmessage(&msg, EM_MOUSE)){
            ButtonAnimation(msg, login, WHITE, CommonBlue);
            ButtonAnimation(msg, exit, WHITE, CommonBlue);
            switch(msg.message){
                case WM_LBUTTONDOWN:
                    if(isInside(msg, login)){
                        cout << tmp.userName << " " << tmp.password << endl;
                        if(loginCheck()){
                            InitMouseMsg();
                            return;
                        }else{
                            HWND er = GetHWnd();
                            MessageBox(er, "登录失败，请检查账号密码", "错误", MB_OK);
                            InitMouseMsg();
                        }
                    }
                    if(isInside(msg, exit)){
                        endsystem = true;
                        closegraph();
                        return;
                    }
                    if(isInside(msg, user)){
                        char s[100];
                        InputBox(s, 100, "请输入用户名");
                        tmp.userName = s;
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillroundrect_(user);
                        OutputText(user.posx + 20, user.posy + 10, BLACK, 17, 0, tmp.userName.c_str(), "楷体");
                        flushmessage(EM_MOUSE);
                    }
                    if(isInside(msg, password)){
                        char s[100];
                        InputBox(s, 100, "请输入密码");
                        tmp.password = s;
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillroundrect_(password);
                        string encodedPassword = "";
                        for (int i = 0; i < tmp.password.size(); ++i) encodedPassword += '*';
                        OutputText(password.posx + 20, password.posy + 10, BLACK, 17, 0, encodedPassword.c_str(), "楷体");
                        flushmessage(EM_MOUSE);
                    }
            }
        }
    }
}

//退出界面
bool endsystem;
void Quit(){
    setlinecolor(CommonBlue);
    object quitWindowUp = {500, 230, 220, 30};
    object quitWindowDown = {500, 260, 220, 110};
    setfillcolor(CommonBlue);
    fillrectangle_(quitWindowUp);
    setfillcolor(WHITE);
    fillrectangle_(quitWindowDown);
    setfillcolor(CommonBlue);
    object quit = {520, 280, 180, 30};
    object cancel = {520, 320, 180, 30};
    fillroundrect_(quit);
    fillroundrect_(cancel);
    OutputText(quitWindowUp.posx + 5, quitWindowUp.posy + 5, WHITE, 20, 0, "退出系统？", "宋体");
    OutputText(quit.posx + 65, quit.posy + 5, WHITE, 20, 0, "退出", "宋体");
    OutputText(cancel.posx + 65, cancel.posy + 5, WHITE, 20, 0, "取消", "宋体");
    while(true){
        msg = getmessage(EM_MOUSE);
        ButtonAnimation(msg, quit, WHITE, CommonBlue);
        ButtonAnimation(msg, cancel, WHITE, CommonBlue);

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                if(isInside(msg, quit)){
                    choose = 0;
                    closegraph();
                    return;
                }
                //如果选择取消，则将界面恢复到进入退出界面前的界面，即qchoose对应的界面
                if(isInside(msg, cancel)){
                    choose = qchoose;
                    flushmessage(EM_MOUSE);
                    return;
                }
            }
        }
    }
}

int main() {
    initgraph(1080, 720 | EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    cleardevice();

    startgraph();//主界面
    flushmessage(EM_MOUSE);
    if(endsystem) return 0;//主界面退出

    //界面跳转
    while (true) {
        switch (choose) {
            case 1:
                UserQuery();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                GoodsQuery();
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                Quit();
                break;
            case 0:
                return 0;
            default:
                break;
        }
    }
}