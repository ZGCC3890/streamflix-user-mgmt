/*
 * 个人信息：E12214013 王天心
 * 编译环境：easyx图形库 gcc 12.2.0
 * 使用工具：CLion InnoSetup（用于打包安装包）
 * 本程序基于easyx图形库编写，在gcc 8.1.0和11.2.0版本下会出现找不到程序输入点的错误，用附带的gcc 12.2.0版本替换本地编译库即可解决
 *
 */
#include<bits/stdc++.h>
#include<graphics.h>
#include<conio.h>
#include<pqxx/pqxx>
using namespace std;

ExMessage msg;//鼠标信息结构体
int lessonNumber;//当前科目总数
//数据节点（学生）
typedef struct stu {
    string name;//学生姓名
    string id;//学生学号
    double ls[100]{};//学生各科成绩
    string gender;//学生性别
    double score = 0;//学生总分
}stu;
string lessonList[100]; //各科目名称
vector<stu> s;

//输出函数封装（字体颜色，字号，字体，输出位置）
void ot(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st){
    settextcolor(color);
    settextstyle(nH,nW,st);
    outtextxy(x, y, str);
}

//按钮效果封装
void button_animation(ExMessage m, int l, int t, int r, int b, COLORREF colort, COLORREF colorf){
    if(m.x >= l && m.x <= r && msg.y >= t && msg.y <= b){
        setlinecolor(colort);
        roundrect(l + 1,  t + 1, r - 1, b - 1, 10, 10);
    }else{
        setlinecolor(colorf);
        roundrect(l + 1, t + 1, r - 1, b - 1, 10, 10);
    }
}

//界面跳转
int choose = 1;
int qchoose;
int choosegraph(int mx, int my){
    if(mx >= 0 && mx <= 170){
        if(my >= 25 && my <= 115){
            return 1;//所有学生信息PrintAll()
        }
        else if(my >= 115 && my <= 205){
            return 2;//添加学生信息AddStudent()
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
void menu(int n){
    cleardevice();
    setlinecolor(RGB(50, 100, 200));
    setfillcolor(RGB(50,100,200));
    fillrectangle(0, 0, 170, 720);
    setlinecolor(RGB(70, 120, 210));
    setfillcolor(RGB(70, 120, 210));
    fillrectangle(0, 25 + (n - 1) * 90, 170, 25 + n * 90);
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 180, 55, false);
    putimage(870, 5, &ah);
    ot(20,60,WHITE,20,0,"所有学生信息", "宋体");
    ot(20,150,WHITE,20,0,"添加学生信息", "宋体");
    ot(20,240,WHITE,20,0,"查找学生信息", "宋体");
    ot(20,330,WHITE,20,0,"统计课程信息", "宋体");
    ot(20,420,WHITE,20,0,"修改学生信息", "宋体");
    ot(20,510,WHITE,20,0,"删除学生信息", "宋体");
    ot(55,600,WHITE,20,0,"设置", "宋体");
    ot(55,680,WHITE,20,0,"退出", "宋体");
}

//菜单动画
void menuanimation(int mx, int my, int n){
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 115 && n != 1) ot(20,60,YELLOW,20,0,"所有学生信息", "宋体");
    else ot(20,60,WHITE,20,0,"所有学生信息", "宋体");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 115 && msg.y <= 205 && n != 2) ot(20,150,YELLOW,20,0,"添加学生信息", "宋体");
    else ot(20,150,WHITE,20,0,"添加学生信息", "宋体");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 205 && msg.y <= 295 && n != 3) ot(20,240,YELLOW,20,0,"查找学生信息", "宋体");
    else ot(20,240,WHITE,20,0,"查找学生信息", "宋体");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 295 && msg.y <= 385 && n != 4) ot(20,330,YELLOW,20,0,"统计课程信息", "宋体");
    else ot(20,330,WHITE,20,0,"统计课程信息", "宋体");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 385 && msg.y <= 475 && n != 5) ot(20,420,YELLOW,20,0,"修改学生信息", "宋体");
    else ot(20,420,WHITE,20,0,"修改学生信息", "宋体");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 475 && msg.y <= 565 && n != 6) ot(20,510,YELLOW,20,0,"删除学生信息", "宋体");
    else ot(20,510,WHITE,20,0,"删除学生信息", "宋体");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 565 && msg.y <= 645 && n != 7) ot(55,600,YELLOW,20,0,"设置", "宋体");
    else ot(55,600,WHITE,20,0,"设置", "宋体");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 645 && msg.y <= 720 && n != 8) ot(55,680,YELLOW,20,0,"退出", "宋体");
    else ot(55,680,WHITE,20,0,"退出", "宋体");
}

//输入合法性检查
bool check(char ch[]){
    bool flag = false;
    for (int i = 0; i < strlen(ch); ++i) {
        if(ch[i] != '.' && ch[i] < '0' || ch[i] > '9'){
            flag = true;
            break;
        }
    }
    if(!flag) return true;
    else return false;
}

//查找学生信息
void SearchStudent() {
    menu(3);
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(270, 60, 660, 100, 10, 10);
    ot(280, 70, WHITE, 20, 0, "请输入学号或姓名：", "宋体");
    fillroundrect(680, 60, 780, 100, 10, 10);
    ot(710, 70, WHITE, 20, 0, "查询", "宋体");
    //菜单和界面绘制

    string input = "No_Input_Information";//输入字符串初始化
    char cinput[100];
    while(true){
        msg = getmessage(EM_MOUSE);
        menuanimation(msg.x, msg.y, 3);//菜单动画

        button_animation(msg, 680, 60, 780, 100, WHITE, RGB(50, 100, 200));//按钮动画

        if(msg.x >= 460 && msg.x <= 655 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(460, 65, 655, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(460, 65, 655, 95, 10, 10);
        }
        if(input != "No_Input_Information") ot(470, 70, BLACK, 20, 0, cinput, "宋体");
        //显示输入信息

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                //界面跳转
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 3) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }

                //输入学生学号/姓名，如果找到便输出信息，历遍s后未找到便报错
                if(msg.x >= 460 && msg.x <= 655 && msg.y >= 65 && msg.y <= 95) {
                    InputBox(cinput, 100, "输入学生学号/姓名");
                    input = cinput;
                }
                if(msg.x >= 680 && msg.x <= 780 && msg.y >= 60 && msg.y <= 100){
                    clearrectangle(270, 130, 970, 720);
                    bool find = false;
                    for (auto & i : s) {
                        if(i.id == input || i.name == input){
                            find = true;
                            ot(270, 130, BLACK, 20, 0, "查询成功，学生信息如下：", "宋体");
                            input = "No_Input_Information";
                            char output[1000];
                            setlinecolor(BLACK);
                            line(270, 160, 970, 160);
                            line(270, 200, 970, 200);
                            sprintf(output, "%s%s      %s%s     %s%s", "学号：", i.id.c_str(), "姓名：", i.name.c_str(), "性别：", i.gender.c_str());
                            ot(280, 170, BLACK, 20, 0, output, "宋体");
                            line(620, 200, 620, 200 + (lessonNumber + 1) / 2 * 40);
                            for (int j = 0; j < lessonNumber; ++j) {
                                char les[100];
                                char les_score[20];
                                sprintf(les, "%s", lessonList[j].c_str());
                                sprintf(les_score, "%.2lf", i.ls[j]);
                                if(j % 2 == 0){
                                    ot(280, 210 + j / 2 * 40, BLACK, 20, 0, les, "宋体");
                                    ot(470, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "宋体");
                                }else{
                                    ot(630, 210 + j / 2 * 40, BLACK, 20, 0, les, "宋体");
                                    ot(820, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "宋体");
                                }
                            }
                        }
                    }
                    if(!find){
                        HWND er = GetHWnd();
                        MessageBox(er, "未找到该学生，请确认信息输入是否正确", "错误", MB_OK);
                        input = "No_Input_Information";
                    }
                }
            }
        }
    }
}

//添加学生信息
void AddStudent() {
    menu(2);
    char xh[20] = " ", xm[100] = " ", xb[10] = " ", cj[30][10] = {};
    setlinecolor(BLACK);
    setfillcolor(RGB(50, 100, 200));
    fillroundrect(280, 60, 655, 100, 10, 10);
    ot(290, 72, WHITE, 20, 0, "学生学号:", "宋体");
    fillroundrect(280, 120, 655, 160, 10, 10);
    ot(290, 132, WHITE, 20, 0, "学生姓名:", "宋体");
    fillroundrect(280, 180, 655, 220, 10, 10);
    ot(290, 192, WHITE, 20, 0, "学生性别:", "宋体");
    if(lessonNumber <= 10)
        fillroundrect(280, 240, 675, 280 + (lessonNumber) * 35, 10, 10);
    else{
        fillroundrect(280, 240, 675, 280 + 10 * 35, 10, 10);
        fillroundrect(685, 240, 1075, 245 + (lessonNumber - 10) * 35, 10, 10);
    }

    ot(290, 252, WHITE, 20, 0, "学生成绩:  总分：", "宋体");
    fillroundrect(675, 60, 785, 100, 10, 10);
    ot(690, 72, WHITE, 20, 0, "确认添加", "宋体");
    fillroundrect(675, 120, 785, 160, 10, 10);
    ot(708, 132, WHITE, 20, 0, "重置", "宋体");
    //界面绘制

    //初始化临时节点t
    stu t;
    for (int i = 0; i < lessonNumber; ++i) {
        t.ls[i] = -1;
    }
    t.id = "No_Input_id";
    t.name = "No_Input_name";
    t.gender = "No_Input_gender";
    char tid[100], tname[100], tls[30][10];
    char tscore[100];
    bool male = false;
    bool female = false;
    while(true){
        msg = getmessage(EM_MOUSE);
        menuanimation(msg.x, msg.y, 2);

        button_animation(msg, 675, 60, 785, 100, WHITE, RGB(50, 100, 200));
        button_animation(msg, 675, 120, 785, 160, WHITE, RGB(50, 100, 200));

        if(t.id != "No_Input_id") sprintf(tid, "%s", t.id.c_str());
        if(t.name != "No_Input_name") sprintf(tname, "%s", t.name.c_str());
        sprintf(tscore, "%.2lf", t.score);
        setfillcolor(WHITE);
        solidroundrect(495, 245, 670, 275, 10, 10);
        ot(505, 250, BLACK, 20, 0, tscore, "宋体");
        if(msg.x >= 400 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 65, 650, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(400, 65, 650, 95, 10, 10);
        }
        if(t.id != "No_Input_id") ot(410, 72, BLACK, 20, 0, tid, "宋体");

        if(msg.x >= 400 && msg.x <= 650 && msg.y >= 125 && msg.y <= 155){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 125, 650, 155, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(400, 125, 650, 155, 10, 10);
        }
        if(t.name != "No_Input_name") ot(410, 132, BLACK, 20, 0, tname, "宋体");

        if(msg.x >= 400 && msg.x <= 520 && msg.y >= 185 && msg.y <= 215 && !male){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 185, 520, 215, 10, 10);
        }else if(!male){
            setfillcolor(WHITE);
            solidroundrect(400, 185, 520, 215, 10, 10);
        }
        ot(450, 190, BLACK, 20, 0, "男", "宋体");
        if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215 && !female){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(530, 185, 650, 215, 10, 10);
        }else if(!female){
            setfillcolor(WHITE);
            solidroundrect(530, 185, 650, 215, 10, 10);
        }
        ot(580, 190, BLACK, 20, 0, "女", "宋体");

        if(male){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(400, 185, 520, 215, 10, 10);
            ot(450, 190, BLACK, 20, 0, "男", "宋体");
        }
        if(female){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(530, 185, 650, 215, 10, 10);
            ot(580, 190, BLACK, 20, 0, "女", "宋体");
        }
        //选中动画及输入信息输出

        if(lessonNumber <= 10) {
            for (int i = 0; i < lessonNumber; ++i) {
                char st[100];
                sprintf(st, "%s", lessonList[i].c_str());
                if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                    setfillcolor(RGB(200, 200, 200));
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }else{
                    setfillcolor(WHITE);
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }
                if(t.ls[i] >= 0){
                    sprintf(tls[i], "%.2lf", t.ls[i]);
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "宋体");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "宋体");
            }
        }
        else{
            for (int i = 0; i < 10; ++i) {
                char st[100];
                sprintf(st, "%s", lessonList[i].c_str());
                if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                    setfillcolor(RGB(200, 200, 200));
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }else{
                    setfillcolor(WHITE);
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }
                if(t.ls[i] >= 0){
                    sprintf(tls[i], "%.2lf", t.ls[i]);
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "宋体");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "宋体");
            }
            for (int i = 0; i < lessonNumber - 10; ++i) {
                char st[100];
                sprintf(st, "%s", lessonList[i + 10].c_str());
                if (msg.x >= 830 && msg.x <= 1070 && msg.y >= 245 + i * 35 && msg.y <= 275 + i * 35){
                    setfillcolor(RGB(200, 200, 200));
                    solidroundrect(830, 245 + i * 35, 1070, 275 + i * 35, 10, 10);
                }else{
                    setfillcolor(WHITE);
                    solidroundrect(830, 245 + i * 35, 1070, 275 + i * 35, 10, 10);
                }
                if(t.ls[i + 10] >= 0){
                    sprintf(tls[i + 10], "%.2lf", t.ls[i + 10]);
                    ot(840, 250 + i * 35, BLACK, 20, 0, tls[i + 10], "宋体");
                }
                ot(690, 247 + i * 35, WHITE, 20, 0, st, "宋体");
            }
        }

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 2) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }
                //和已有学生重复时报错
                if(msg.x >= 400 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95){
                    char txh[100];
                    InputBox(txh, 100, "请输入学生学号");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.id == txh){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "错误，该学生已存在：\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "错误", MB_OK);
                            exist = true;
                            break;
                        }
                    }
                    if(!exist){
                        t.id = txh;
                    }
                }
                if(msg.x >= 400 && msg.x <= 650 && msg.y >= 125 && msg.y <= 155){
                    char txm[100];
                    InputBox(txm, 100, "请输入学生姓名");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.name == txm){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "错误，该学生已存在：\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "错误", MB_OK);
                            exist = true;
                            break;
                        }
                    }
                    if(!exist){
                        t.name = txm;
                    }
                }
                if(msg.x >= 400 && msg.x <= 520 && msg.y >= 185 && msg.y <= 215){
                    male = true;
                    female = false;
                    t.gender = "男";
                }
                if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215){
                    female = true;
                    male = false;
                    t.gender = "女";
                }
                //输入不合法时报错，其他情况正常存入
                if(lessonNumber <= 10){
                    for (int i = 0; i < lessonNumber; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "请输入该学生 ", lessonList[i].c_str(), " 成绩");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "输入应为数字", "错误", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                                t.ls[i] = -1;
                                break;
                            }
                            t.score -= max(t.ls[i], double(0));
                            t.ls[i] = stod(tls[i]);
                            t.score += t.ls[i];
                        }
                    }
                }
                else{
                    for (int i = 0; i < lessonNumber; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "请输入该学生 ", lessonList[i].c_str(), " 成绩");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "输入应为数字", "错误", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                                t.ls[i] = -1;
                                break;
                            }
                            t.score -= max(t.ls[i], double(0));
                            t.ls[i] = stod(tls[i]);
                            t.score += t.ls[i];
                        }
                    }
                    for (int i = 0; i < lessonNumber - 10; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "请输入该学生 ", lessonList[i + 10].c_str(), " 成绩");
                        if (msg.x >= 830 && msg.x <= 1070 && msg.y >= 245 + i * 35 && msg.y <= 275 + i * 35){
                            InputBox(tls[i + 10], 100, st);
                            if(!check(tls[i + 10])){
                                HWND er = GetHWnd();
                                MessageBox(er, "输入应为数字", "错误", MB_OK);
                                break;
                            }
                            if(stod(tls[i + 10]) < 0 || stod(tls[i + 10]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                                t.ls[i + 10] = -1;
                            }
                            t.score -= max(t.ls[i + 10], double(0));
                            t.ls[i + 10] = stod(tls[i + 10]);
                            t.score += t.ls[i + 10];
                        }
                    }
                }

                //如果有未填写信息即报错，没有则将t存入s并初始化t
                if(msg.x >= 675 && msg.x <= 785 && msg.y >= 60 && msg.y <= 100){
                    bool all = false;
                    if(t.id == "No_Input_id" || t.name == "No_Input_name" || t.gender == "No_Input_gender") all = true;
                    for (int i = 0; i < lessonNumber; ++i) {
                        if(t.ls[i] < 0){
                            all = true;
                            break;
                        }
                    }
                    if(all) {
                        HWND er = GetHWnd();
                        MessageBox(er, "有信息未填写", "错误", MB_OK);
                    }
                    else{
                        HWND res = GetHWnd();
                        MessageBox(res, "添加成功", "提示", MB_OK);
                        s.push_back(t);
                        for (int i = 0; i < lessonNumber; ++i) {
                            t.ls[i] = -1;
                        }
                        t.id = "No_Input_id";
                        t.name = "No_Input_name";
                        t.gender = "No_Input_gender";
                        t.score = 0;
                        male = false;
                        female = false;
                    }
                }

                //重置按钮，初始化t
                if(msg.x >= 675 && msg.x <= 785 && msg.y >= 120 && msg.y <= 160){
                    for (int i = 0; i < lessonNumber; ++i) {
                        t.ls[i] = -1;
                    }
                    t.id = "No_Input_id";
                    t.name = "No_Input_name";
                    t.gender = "No_Input_gender";
                    t.score = 0;
                    male = false;
                    female = false;
                    HWND res = GetHWnd();
                    MessageBox(res, "已重置", "提示", MB_OK);
                }
            }
        }
    }
}

//删除学生信息
void DelStudent() {
    menu(6);

    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(270, 60, 660, 100, 10, 10);
    ot(280, 70, WHITE, 20, 0, "请输入学号或姓名：", "宋体");
    fillroundrect(680, 60, 780, 100, 10, 10);
    ot(690, 70, WHITE, 20, 0, "删除学生", "宋体");
    //绘制界面

    //前一部分同查找学生
    string input = "No_Input_Information";
    char cinput[100] = "No_Input";
    while(true){
        msg = getmessage(EM_MOUSE);
        menuanimation(msg.x, msg.y, 6);

        button_animation(msg, 680, 60, 780, 100, WHITE, RGB(50, 100, 200));
        if(msg.x >= 460 && msg.x <= 655 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(460, 65, 655, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(460, 65, 655, 95, 10, 10);
        }
        if(input != "No_Input_Information") ot(470, 70, BLACK, 20, 0, cinput, "宋体");

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 3) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }

                if(msg.x >= 460 && msg.x <= 655 && msg.y >= 65 && msg.y <= 95) {
                    InputBox(cinput, 100, "输入学生学号/姓名");
                    input = cinput;
                    clearrectangle(270, 130, 970, 720);
                    bool find = false;
                    for (auto &i: s) {
                        if (i.id == input || i.name == input) {
                            find = true;
                            ot(270, 130, BLACK, 20, 0, "当前学生信息如下：", "宋体");
                            input = "No_Input_Information";
                            char output[1000];
                            setlinecolor(BLACK);
                            line(270, 160, 970, 160);
                            line(270, 200, 970, 200);
                            sprintf(output, "%s%s      %s%s     %s%s", "学号：", i.id.c_str(), "姓名：", i.name.c_str(),
                                    "性别：", i.gender.c_str());
                            ot(280, 170, BLACK, 20, 0, output, "宋体");
                            line(620, 200, 620, 200 + (lessonNumber + 1) / 2 * 40);
                            for (int j = 0; j < lessonNumber; ++j) {
                                char les[100];
                                char les_score[20];
                                sprintf(les, "%s", lessonList[j].c_str());
                                sprintf(les_score, "%.2lf", i.ls[j]);
                                if (j % 2 == 0) {
                                    ot(280, 210 + j / 2 * 40, BLACK, 20, 0, les, "宋体");
                                    ot(470, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "宋体");
                                } else {
                                    ot(630, 210 + j / 2 * 40, BLACK, 20, 0, les, "宋体");
                                    ot(820, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "宋体");
                                }
                            }
                        }
                    }
                    if (!find) {
                        HWND er = GetHWnd();
                        MessageBox(er, "未找到学生，请确认信息输入是否正确", "错误", MB_OK);
                        input = "No_Input_Information";
                    }
                }

                //当点击“删除学生”时，弹出二级窗口询问，选择取消则清空界面并重新绘制窗口，重新显示学生信息，选择确认即从s中移除此节点
                if(msg.x >= 680 && msg.x <= 780 && msg.y >= 60 && msg.y <= 100){
                    setlinecolor(RGB(50, 100, 200));
                    setfillcolor(RGB(50, 100, 200));
                    fillrectangle(500, 240, 720, 270);
                    setfillcolor(WHITE);
                    fillrectangle(500, 270, 720, 400);
                    setfillcolor(RGB(50, 100, 200));
                    setlinecolor(BLACK);
                    fillroundrect(510, 290, 710, 330, 10, 10);
                    fillroundrect(510, 340, 710, 380, 10, 10);
                    ot(510, 245, WHITE, 20, 0, "确认删除该学生？", "宋体");
                    ot(570, 300, WHITE, 20, 0, "确认删除", "宋体");
                    ot(590, 350, WHITE, 20, 0, "取消", "宋体");
                    flushmessage(EM_MOUSE);
                    bool ewhile = false;
                    while(true){
                        if(ewhile) break;
                        msg = getmessage(EM_MOUSE);
                        button_animation(msg, 510, 290, 710, 330, WHITE, RGB(50, 100, 200));
                        button_animation(msg, 510, 340, 710, 380, WHITE, RGB(50, 100, 200));
                        switch (msg.message) {
                            case WM_LBUTTONDOWN:{
                                if(msg.x >= 510 && msg.x <= 710 && msg.y >= 290 && msg.y <= 330){
                                    input = cinput;
                                    auto p = s.begin();
                                    bool find = false;
                                    for (auto & i : s) {
                                        if(i.id == input || i.name == input){
                                            find = true;
                                            input = "No_Input_Information";
                                            s.erase(p);
                                            HWND res = GetHWnd();
                                            MessageBox(res, "已删除该学生", "提示", MB_OK);
                                            choose = 6;
                                            return;
                                        }
                                        p++;
                                    }
                                }

                                if(msg.x >= 510 && msg.x <= 710 && msg.y >= 340 && msg.y <= 380){
                                    clearrectangle(270, 100, 970, 720);
                                    input = cinput;
                                    bool find = false;
                                    for (auto &i: s) {
                                        if (i.id == input || i.name == input) {
                                            find = true;
                                            ot(270, 130, BLACK, 20, 0, "当前学生信息如下：", "宋体");
                                            input = "No_Input_Information";
                                            char output[1000];
                                            setlinecolor(BLACK);
                                            line(270, 160, 970, 160);
                                            line(270, 200, 970, 200);
                                            sprintf(output, "%s%s      %s%s     %s%s", "学号：", i.id.c_str(), "姓名：", i.name.c_str(),
                                                    "性别：", i.gender.c_str());
                                            ot(280, 170, BLACK, 20, 0, output, "宋体");
                                            line(620, 200, 620, 200 + (lessonNumber + 1) / 2 * 40);
                                            for (int j = 0; j < lessonNumber; ++j) {
                                                char les[100];
                                                char les_score[20];
                                                sprintf(les, "%s", lessonList[j].c_str());
                                                sprintf(les_score, "%.2lf", i.ls[j]);
                                                if (j % 2 == 0) {
                                                    ot(280, 210 + j / 2 * 40, BLACK, 20, 0, les, "宋体");
                                                    ot(470, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "宋体");
                                                } else {
                                                    ot(630, 210 + j / 2 * 40, BLACK, 20, 0, les, "宋体");
                                                    ot(820, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "宋体");
                                                }
                                            }
                                        }
                                    }
                                    ewhile = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//修改学生信息
void ChangeStudent() {
    menu(5);
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(280, 60, 655, 100, 10, 10);
    ot(290, 70, WHITE, 20, 0, "请输入学号或姓名：", "宋体");
    fillroundrect(675, 60, 785, 100, 10, 10);
    ot(710, 70, WHITE, 20, 0, "查询", "宋体");
    char xh[20] = " ", xm[100] = " ", xb[10] = " ", cj[30][10] = {};
    fillroundrect(280, 120, 655, 160, 10, 10);
    ot(290, 132, WHITE, 20, 0, "学生学号:", "宋体");
    fillroundrect(675, 120, 1040, 160, 10, 10);
    ot(685, 132, WHITE, 20, 0, "学生姓名:", "宋体");
    fillroundrect(280, 180, 655, 220, 10, 10);
    ot(290, 192, WHITE, 20, 0, "学生性别:", "宋体");
    if(lessonNumber <= 10)
        fillroundrect(280, 240, 675, 280 + (lessonNumber) * 35, 10, 10);
    else{
        fillroundrect(280, 240, 675, 280 + 10 * 35, 10, 10);
        fillroundrect(685, 240, 1075, 245 + (lessonNumber - 10) * 35, 10, 10);
    }

    ot(290, 252, WHITE, 20, 0, "学生成绩:  总分：", "宋体");
    fillroundrect(675, 180, 785, 220, 10, 10);
    ot(690, 192, WHITE, 20, 0, "保存修改", "宋体");
    fillroundrect(805, 180, 915, 220, 10, 10);
    ot(835, 192, WHITE, 20, 0, "重置", "宋体");

    string input = "No_Input_Information";
    char cinput[100];
    stu t;
    for (int i = 0; i < lessonNumber; ++i) {
        t.ls[i] = -1;
    }
    t.id = "No_Input_id";
    t.name = "No_Input_name";
    t.gender = "No_Input_gender";
    char tid[100], tname[100], tls[30][10];
    char tscore[100];
    bool male = false;
    bool female = false;
    auto p = s.begin();
    while(true){
        msg = getmessage(EM_MOUSE);
        menuanimation(msg.x, msg.y, 5);

        button_animation(msg, 675, 60, 785, 100, WHITE, RGB(50, 100, 200));

        button_animation(msg, 675, 180, 785, 220, WHITE, RGB(50, 100, 200));
        button_animation(msg, 805, 180, 915, 220, WHITE, RGB(50, 100, 200));

        if(t.id != "No_Input_id") sprintf(tid, "%s", t.id.c_str());
        if(t.name != "No_Input_name") sprintf(tname, "%s", t.name.c_str());
        sprintf(tscore, "%.2lf", t.score);
        setfillcolor(WHITE);
        solidroundrect(495, 245, 670, 275, 10, 10);
        ot(505, 250, BLACK, 20, 0, tscore, "宋体");
        if(msg.x >= 400 && msg.x <= 650 && msg.y >= 125 && msg.y <= 155){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 125, 650, 155, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(400, 125, 650, 155, 10, 10);
        }
        if(t.id != "No_Input_id") ot(410, 132, BLACK, 20, 0, tid, "宋体");

        if(msg.x >= 785 && msg.x <= 1035 && msg.y >= 125 && msg.y <= 155){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(785, 125, 1035, 155, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(785, 125, 1035, 155, 10, 10);
        }
        if(t.name != "No_Input_name") ot(800, 132, BLACK, 20, 0, tname, "宋体");

        if(msg.x >= 400 && msg.x <= 520 && msg.y >= 185 && msg.y <= 215 && !male){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 185, 520, 215, 10, 10);
        }else if(!male){
            setfillcolor(WHITE);
            solidroundrect(400, 185, 520, 215, 10, 10);
        }
        ot(450, 190, BLACK, 20, 0, "男", "宋体");
        if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215 && !female){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(530, 185, 650, 215, 10, 10);
        }else if(!female){
            setfillcolor(WHITE);
            solidroundrect(530, 185, 650, 215, 10, 10);
        }
        ot(580, 190, BLACK, 20, 0, "女", "宋体");

        if(male){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(400, 185, 520, 215, 10, 10);
            ot(450, 190, BLACK, 20, 0, "男", "宋体");
        }
        if(female){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(530, 185, 650, 215, 10, 10);
            ot(580, 190, BLACK, 20, 0, "女", "宋体");
        }

        if(msg.x >= 460 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(460, 65, 650, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(460, 65, 650, 95, 10, 10);
        }
        if(input != "No_Input_Information") ot(470, 70, BLACK, 20, 0, cinput, "宋体");

        if(lessonNumber <= 10) {
            for (int i = 0; i < lessonNumber; ++i) {
                char st[100];
                sprintf(st, "%s", lessonList[i].c_str());
                if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                    setfillcolor(RGB(200, 200, 200));
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }else{
                    setfillcolor(WHITE);
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }
                if(t.ls[i] >= 0){
                    sprintf(tls[i], "%.2lf", t.ls[i]);
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "宋体");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "宋体");
            }
        }
        else{
            for (int i = 0; i < 10; ++i) {
                char st[100];
                sprintf(st, "%s", lessonList[i].c_str());
                if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                    setfillcolor(RGB(200, 200, 200));
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }else{
                    setfillcolor(WHITE);
                    solidroundrect(430, 280 + i * 35, 670, 310 + i * 35, 10, 10);
                }
                if(t.ls[i] >= 0){
                    sprintf(tls[i], "%.2lf", t.ls[i]);
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "宋体");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "宋体");
            }
            for (int i = 0; i < lessonNumber - 10; ++i) {
                char st[100];
                sprintf(st, "%s", lessonList[i + 10].c_str());
                if (msg.x >= 830 && msg.x <= 1070 && msg.y >= 245 + i * 35 && msg.y <= 275 + i * 35){
                    setfillcolor(RGB(200, 200, 200));
                    solidroundrect(830, 245 + i * 35, 1070, 275 + i * 35, 10, 10);
                }else{
                    setfillcolor(WHITE);
                    solidroundrect(830, 245 + i * 35, 1070, 275 + i * 35, 10, 10);
                }
                if(t.ls[i + 10] >= 0){
                    sprintf(tls[i + 10], "%.2lf", t.ls[i + 10]);
                    ot(840, 250 + i * 35, BLACK, 20, 0, tls[i + 10], "宋体");
                }
                ot(690, 247 + i * 35, WHITE, 20, 0, st, "宋体");
            }
        }
        //选中反馈动画

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 5) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }

                //输入学生姓名/学号进行查找，找不到报错
                if(msg.x >= 460 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95) {
                    InputBox(cinput, 100, "输入学生学号/姓名");
                    input = cinput;
                }
                if(msg.x >= 675 && msg.x <= 785 && msg.y >= 60 && msg.y <= 100){
                    bool find = false;
                    p = s.begin();
                    for (auto & i : s) {
                        if(i.id == input || i.name == input){
                            find = true;
                            input = "No_Input_Information";
                            t = i;
                            if(t.gender == "男") male = true;
                            else female = true;
                            break;
                        }
                        ++p;
                    }
                    if(!find){
                        HWND er = GetHWnd();
                        MessageBox(er, "未找到该学生，请确认信息输入是否正确", "错误", MB_OK);
                        input = "No_Input_Information";
                    }
                }
                //修改时逻辑同添加学生，如果当前学号或姓名已存在便报错
                if(msg.x >= 400 && msg.x <= 650 && msg.y >= 125 && msg.y <= 155){
                    char txh[100];
                    InputBox(txh, 100, "请输入学生学号");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.id == txh){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "错误，该学生已存在：\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "错误", MB_OK);
                            exist = true;
                            break;
                        }
                    }
                    if(!exist){
                        t.id = txh;
                    }
                }
                if(msg.x >= 785 && msg.x <= 1035 && msg.y >= 125 && msg.y <= 155){
                    char txm[100];
                    InputBox(txm, 100, "请输入学生姓名");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.name == txm){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "错误，该学生已存在：\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "错误", MB_OK);
                            exist = true;
                            break;
                        }
                    }
                    if(!exist){
                        t.name = txm;
                    }
                }
                if(msg.x >= 400 && msg.x <= 520 && msg.y >= 185 && msg.y <= 215){
                    male = true;
                    female = false;
                    t.gender = "男";
                }
                if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215){
                    female = true;
                    male = false;
                    t.gender = "女";
                }

                //存入数据，不合法数据报错
                if(lessonNumber <= 10){
                    for (int i = 0; i < lessonNumber; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "请输入该学生 ", lessonList[i].c_str(), " 成绩");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "输入应为数字", "错误", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                                t.ls[i] = -1;
                                break;
                            }
                            t.score -= max(t.ls[i], double(0));
                            t.ls[i] = stod(tls[i]);
                            t.score += t.ls[i];
                        }
                    }
                }
                else{
                    for (int i = 0; i < lessonNumber; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "请输入该学生 ", lessonList[i].c_str(), " 成绩");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "输入应为数字", "错误", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                                t.ls[i] = -1;
                                break;
                            }
                            t.score -= max(t.ls[i], double(0));
                            t.ls[i] = stod(tls[i]);
                            t.score += t.ls[i];
                        }
                    }
                    for (int i = 0; i < lessonNumber - 10; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "请输入该学生 ", lessonList[i + 10].c_str(), " 成绩");
                        if (msg.x >= 830 && msg.x <= 1070 && msg.y >= 245 + i * 35 && msg.y <= 275 + i * 35){
                            InputBox(tls[i + 10], 100, st);
                            if(!check(tls[i + 10])){
                                HWND er = GetHWnd();
                                MessageBox(er, "输入应为数字", "错误", MB_OK);
                                break;
                            }
                            if(stod(tls[i + 10]) < 0 || stod(tls[i + 10]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                                t.ls[i + 10] = -1;
                            }
                            t.score -= max(t.ls[i + 10], double(0));
                            t.ls[i + 10] = stod(tls[i + 10]);
                            t.score += t.ls[i + 10];
                        }
                    }
                }

                //检查是否所有信息已填写，如果是则将当前t插入s并删除查找到的节点，反之报错
                if(msg.x >= 675 && msg.x <= 785 && msg.y >= 180 && msg.y <= 220){
                    bool all = false;
                    if(t.id == "No_Input_id" || t.name == "No_Input_name" || t.gender == "No_Input_gender") all = true;
                    for (int i = 0; i < lessonNumber; ++i) {
                        if(t.ls[i] < 0){
                            all = true;
                            break;
                        }
                    }
                    if(all) {
                        HWND er = GetHWnd();
                        MessageBox(er, "有信息未填写", "错误", MB_OK);
                    }
                    else{
                        HWND res = GetHWnd();
                        MessageBox(res, "修改成功", "提示", MB_OK);
                        s.erase(p);
                        s.push_back(t);
                        for (int i = 0; i < lessonNumber; ++i) {
                            t.ls[i] = -1;
                        }
                        t.id = "No_Input_id";
                        t.name = "No_Input_name";
                        t.gender = "No_Input_gender";
                        t.score = 0;
                        male = false;
                        female = false;
                    }
                }
                //重置即初始化t，不对s进行操作
                if(msg.x >= 805 && msg.x <= 915 && msg.y >= 180 && msg.y <= 220){
                    for (int i = 0; i < lessonNumber; ++i) {
                        t.ls[i] = -1;
                    }
                    t.id = "No_Input_id";
                    t.name = "No_Input_name";
                    t.gender = "No_Input_gender";
                    t.score = 0;
                    male = false;
                    female = false;
                    p = s.begin();
                }
            }
        }
    }
}

int ppage = 0;
int tsit[100];
vector<stu> SSlist;
//排序方式
int object;//当前学科
bool CmpUp(const stu& a, const stu& b) {
    return a.ls[object] > b.ls[object];
}//课程成绩降序
bool CmpDown(const stu& a, const stu& b) {
    return a.ls[object] < b.ls[object];
}//课程成绩升序
bool Cmp(const stu& a, const stu& b) {
    return a.id < b.id;
}//学号升序
bool CmpScore(const stu& a, const stu& b){
    return a.score > b.score;
}//总分降序
//指定分数段排名
//基础界面绘制
void ScoreStatisticsGraph(){
    clearrectangle(370, 100, 1080, 720);
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(370, 130, 450, 160);
    fillrectangle(450, 130, 680, 160);
    fillrectangle(680, 130, 880, 160);
    fillrectangle(880, 130, 950, 160);
    fillrectangle(950, 130, 1050, 160);
    ot(380, 135, BLACK, 25, 0, "排名", "楷体");
    ot(460, 135, BLACK, 25, 0, "学号", "楷体");
    ot(690, 135, BLACK, 25, 0, "姓名", "楷体");
    ot(890, 135, BLACK, 25, 0, "性别", "楷体");
    ot(960, 135, BLACK, 25, 0, "成绩", "楷体");
    for (int i = 0; i < 12; ++i) {
        fillrectangle(370, 160 + i * 30, 450, 190 + i * 30);
        fillrectangle(450, 160 + i * 30, 680, 190 + i * 30);
        fillrectangle(680, 160 + i * 30, 880, 190 + i * 30);
        fillrectangle(880, 160 + i * 30, 950, 190 + i * 30);
        fillrectangle(950, 160 + i * 30, 1050, 190 + i * 30);
    }
    setfillcolor(RGB(50, 100, 200));
    if(ppage != 0) {
        fillroundrect(790, 540, 860, 560, 10, 10);
        ot(800, 543, WHITE, 15, 0, "上一页", "宋体");
    }
    if(ppage != (int(SSlist.size()) + 11) / 12 - 1 && int(SSlist.size() + 11) / 12 != 0) {
        fillroundrect(1000, 540, 1070, 560, 10, 10);
        ot(1010, 543, WHITE, 15, 0, "下一页", "宋体");
    }
    //判断是否显示翻页按钮
    char tpage[100];
    sprintf(tpage, "第%d页  共%d页", ppage + 1, max(1, (int(SSlist.size() + 11) / 12)));
    ot(870, 540, BLACK, 20, 0, tpage, "宋体");
}
void ScoreStatistics() {
    clearrectangle(340, 0, 1080, 720);
    setfillcolor(RGB(100, 150, 220));
    setlinecolor(RGB(100, 150, 220));
    fillrectangle(170, 115, 340, 205);
    ot(182, 150, WHITE, 20, 0, "指定分数段统计", "宋体");
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(RGB(50, 100, 200));
    fillroundrect(370, 60, 650, 100, 10, 10);
    fillroundrect(670, 60, 950, 100, 10, 10);
    fillroundrect(970, 60, 1050, 100, 10, 10);
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    ot(385, 70, WHITE, 20, 0, "选择课程", "宋体");
    ot(685, 70, WHITE, 20, 0, "输入分段", "宋体");
    ot(850, 70, WHITE, 20, 0, "至", "宋体");
    ot(990, 70, WHITE, 20, 0, "查询", "宋体");
    ScoreStatisticsGraph();
    object = int(s.size()) + 1;
    char lesson[100];
    char score_input[100];
    bool tflag = false;
    bool cs1 = false, cs2 = false, cs3 = false;
    double max_score = -1, min_score = -1, fn = -1, sn = -1;
    char tfn[100] = " ", tsn[100] = " ";
    while(true){
        msg = getmessage(EM_MOUSE);
        menuanimation(msg.x, msg.y, 4);
        button_animation(msg, 970, 60 ,1050, 100, WHITE, RGB(50, 100, 200));
        if(ppage != 0) button_animation(msg, 790, 540, 860, 560, WHITE, RGB(50, 100, 200));
        if(ppage != (int(SSlist.size()) + 11) / 12 - 1 && int(SSlist.size() + 11) / 12 != 0) button_animation(msg, 1000, 540, 1070, 560, WHITE, RGB(50, 100, 200));

        sprintf(lesson, "%s", lessonList[object].c_str());
        if(fn >= 0 && sn >= 0){
            max_score = max(fn, sn);
            min_score = min(fn, sn);
        }
        if(fn >= 0) sprintf(tfn, "%.2lf", fn);
        if(sn >= 0) sprintf(tsn, "%.2lf", sn);
        if(msg.x >= 170 && msg.x <= 340 && msg.y >= 25 && msg.y <= 115)
            ot(190, 60, YELLOW, 20, 0, "指定课程排名", "宋体");
        else ot(190, 60, WHITE, 20, 0, "指定课程排名", "宋体");
        if(msg.x >= 490 && msg.x <= 640 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(230, 230, 230));
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, lesson, "宋体");
        }else{
            setfillcolor(WHITE);
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, lesson, "宋体");
        }
        if(msg.x >= 780 && msg.x <= 845 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(780, 65, 845, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(780, 65, 845, 95, 10, 10);
        }ot(785, 70, BLACK, 20, 0, tfn, "宋体");
        if(msg.x >= 875 && msg.x <= 940 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(875, 65, 940, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(875, 65, 940, 95, 10, 10);
        }ot(880, 70, BLACK, 20, 0, tsn, "宋体");

        switch (msg.message) {
            case WM_LBUTTONDOWN: {
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 4) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }
                if (msg.x >= 170 && msg.x <= 340 && msg.y >= 25 && msg.y <= 115) {
                    flushmessage(EM_MOUSE);
                    choose = 4;
                    return;
                }
                if (msg.x >= 790 && msg.x <= 860 && msg.y >= 540 && msg.y <= 560 && ppage != 0){
                    ppage --;
                    ScoreStatisticsGraph();
                    break;
                }
                if (msg.x >= 1000 && msg.x <= 1070 && msg.y >= 540 && msg.y <= 560 && ppage != (int(s.size()) + 11) / 12 - 1 && int(SSlist.size() + 11) / 12 != 0){
                    ppage ++;
                    ScoreStatisticsGraph();
                    break;
                }
                if (msg.x >= 780 && msg.x <= 845 && msg.y >= 60 && msg.y <= 100){
                    cs2 = true;
                    InputBox(tfn, 20, "请输入分数范围：");
                    if(!check(tfn)){
                        HWND er = GetHWnd();
                        MessageBox(er, "输入应为数字", "错误", MB_OK);
                        break;
                    }
                    if(stod(tfn) < 0 || stod(tfn) > 100){
                        HWND er = GetHWnd();
                        MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                        break;
                    }
                    ScoreStatisticsGraph();
                    tflag = false;
                    fn = stod(tfn);
                }
                if (msg.x >= 875 && msg.x <= 940 && msg.y >= 60 && msg.y <= 100){
                    cs3 = true;
                    InputBox(tsn, 20, "请输入分数范围：");
                    if(!check(tsn)){
                        HWND er = GetHWnd();
                        MessageBox(er, "输入应为数字", "错误", MB_OK);
                        break;
                    }
                    if(stod(tsn) < 0 || stod(tsn) > 100){
                        HWND er = GetHWnd();
                        MessageBox(er, "成绩应在0-100之间", "错误", MB_OK);
                        break;
                    }
                    ScoreStatisticsGraph();
                    tflag = false;
                    sn = stod(tsn);
                }
                if (msg.x >= 970 && msg.x <= 1050 && msg.y >= 60 && msg.y <= 100){
                    if(cs1 && cs2 && cs3) {
                        tflag = true;
                    }else{
                        HWND er = GetHWnd();
                        MessageBox(er, "请设置筛选条件", "错误", MB_OK);
                    }
                }
                //下拉选择课程
                if (msg.x >= 490 && msg.x <= 640 && msg.y >= 65 && msg.y <= 95) {
                    bool ewhile = false;
                    while (true) {
                        flushmessage(EM_MOUSE);
                        msg = getmessage(EM_MOUSE);
                        setlinecolor(WHITE);
                        if (msg.x < 490 || msg.x > 640 || msg.y < 65 || msg.y > lessonNumber * 20 + 95) {
                            break;
                        }
                        for (int i = 0; i < lessonNumber; ++i) {
                            char st1[100];
                            sprintf(st1, "%s", lessonList[i].c_str());
                            if (msg.x >= 490 && msg.x <= 640 && msg.y > 95 + i * 20 && msg.y <= 95 + (i + 1) * 20) {
                                setfillcolor(RGB(128, 128, 128));
                                fillrectangle(490, 95 + i * 20, 640, 95 + (i + 1) * 20);
                                ot(495, 100 + i * 20, BLACK, 15, 0, st1, "宋体");
                            } else {
                                setfillcolor(RGB(200, 200, 200));
                                fillrectangle(490, 95 + i * 20,  640, 95 + (i + 1) * 20);
                                ot(495, 100 + i * 20, BLACK, 15, 0, st1, "宋体");
                            }
                        }
                        switch (msg.message) {
                            case WM_LBUTTONDOWN:{
                                for (int i = 0; i < lessonNumber; ++i) {
                                    if(msg.x >= 490 && msg.x <= 640 && msg.y > 95 + i * 20 && msg.y <= 95 + (i + 1) * 20){
                                        object = i;
                                        flushmessage(EM_MOUSE);
                                        ScoreStatisticsGraph();
                                        tflag = false;
                                        ewhile = true;
                                        cs1 = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if(ewhile) break;
                    }
                    clearrectangle(370, 95, 1080, 720);
                    ScoreStatisticsGraph();
                    setfillcolor(RGB(50, 100, 200));
                    setlinecolor(RGB(50, 100, 200));
                    fillroundrect(370, 60, 650, 100, 10, 10);
                    fillroundrect(670, 60, 950, 100, 10, 10);
                    fillroundrect(970, 60, 1050, 100, 10, 10);
                    ot(385, 70, WHITE, 20, 0, "选择课程", "宋体");
                    ot(685, 70, WHITE, 20, 0, "输入分段", "宋体");
                    ot(850, 70, WHITE, 20, 0, "至", "宋体");
                    ot(990, 70, WHITE, 20, 0, "查询", "宋体");
                }
            }
        }
        if(!tflag) continue;//tflag标记是否对当前筛选条件进行了筛选，如果没有修改则不对输出内容进行重新输出以防止内容闪烁

        //将输入的两个数中较大较小的分开，并作为筛选条件
        max_score = max(fn, sn);
        min_score = min(fn, sn);
        SSlist.clear();
        int situation = 0;
        for (auto & i : s) {
            if(i.ls[object] <= max_score && i.ls[object] >= min_score){
                SSlist.push_back(i);
                ++situation;
            }
        }
        sort(SSlist.begin(), SSlist.end(), CmpUp);
        ScoreStatisticsGraph();
        setlinecolor(BLACK);
        setfillcolor(WHITE);
        fillrectangle(370, 130, 450, 160);
        fillrectangle(450, 130, 680, 160);
        fillrectangle(680, 130, 880, 160);
        fillrectangle(880, 130, 950, 160);
        fillrectangle(950, 130, 1050, 160);
        ot(380, 135, BLACK, 25, 0, "排名", "楷体");
        ot(460, 135, BLACK, 25, 0, "学号", "楷体");
        ot(690, 135, BLACK, 25, 0, "姓名", "楷体");
        ot(890, 135, BLACK, 25, 0, "性别", "楷体");
        ot(960, 135, BLACK, 25, 0, "成绩", "楷体");
        auto cmp = SSlist[max(0, ppage * 12 - 1)];
        int site;
        //确定当前页面显示的学生个数
        if(ppage == 0) site = 1;
        else site = 0;
        int point;
        if(ppage == (int(SSlist.size() + 11) / 12) - 1) point = int(SSlist.size()) % 12;
        else point = 12;
        //输出当前页面
        for (int i = 0; i < point; ++ i) {
            if (cmp.ls[object] != SSlist[i + ppage * 12].ls[object]) ++site;
            fillrectangle(370, 160 + i * 30, 450, 190 + i * 30);
            fillrectangle(450, 160 + i * 30, 680, 190 + i * 30);
            fillrectangle(680, 160 + i * 30, 880, 190 + i * 30);
            fillrectangle(880, 160 + i * 30, 950, 190 + i * 30);
            fillrectangle(950, 160 + i * 30, 1050, 190 + i * 30);
            char pm[10],xh[100],xm[100],cj[100],xb[100];
            sprintf(pm, "%d", site + tsit[ppage - 1]);
            sprintf(xh, "%s", SSlist[i + ppage * 12].id.c_str());
            sprintf(xm, "%s", SSlist[i + ppage * 12].name.c_str());
            sprintf(xb, "%s", SSlist[i + ppage * 12].gender.c_str());
            sprintf(cj, "%.2lf", SSlist[i + ppage * 12].ls[object]);
            ot(380, 165 + i * 30, BLACK, 25, 0, pm, "楷体");
            ot(460, 165 + i * 30, BLACK, 25, 0, xh, "楷体");
            ot(690, 165 + i * 30, BLACK, 25, 0, xm, "楷体");
            ot(890, 165 + i * 30, BLACK, 25, 0, xb, "楷体");
            ot(960, 165 + i * 30, BLACK, 25, 0, cj, "楷体");
            cmp = SSlist[i + ppage * 12];
        }
        tsit[ppage] = site + tsit[ppage - 1];

        char ratio[100];
        sprintf(ratio, "当前分段内共%d人，在总人数（%d）中占：", situation, int(s.size()));
        ot(380, 540, BLACK, 20, 0, ratio, "宋体");
        setlinecolor(BLACK);
        setfillcolor(WHITE);
        fillrectangle(380, 570, 680, 595);
        setfillcolor(RGB(50, 100, 200));
        fillrectangle(380, 570, 380 + int(double(situation) / double(s.size()) * 100) * 3, 595);
        sprintf(ratio, "%d%%", int(double(situation) / double(s.size()) * 100));
        ot(370 + int(double(situation) / double(s.size()) * 100) * 3, 600, BLACK, 20, 0, ratio, "宋体");
    }
}
//指定课程排名
//基础界面绘制
void SortPrintGraph(){
    clearrectangle(370, 100, 1080, 720);
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(370, 130, 450, 160);
    fillrectangle(450, 130, 680, 160);
    fillrectangle(680, 130, 880, 160);
    fillrectangle(880, 130, 950, 160);
    fillrectangle(950, 130, 1050, 160);
    ot(380, 135, BLACK, 25, 0, "排名", "楷体");
    ot(460, 135, BLACK, 25, 0, "学号", "楷体");
    ot(690, 135, BLACK, 25, 0, "姓名", "楷体");
    ot(890, 135, BLACK, 25, 0, "性别", "楷体");
    ot(960, 135, BLACK, 25, 0, "成绩", "楷体");
    for (int i = 0; i < 12; ++i) {
        fillrectangle(370, 160 + i * 30, 450, 190 + i * 30);
        fillrectangle(450, 160 + i * 30, 680, 190 + i * 30);
        fillrectangle(680, 160 + i * 30, 880, 190 + i * 30);
        fillrectangle(880, 160 + i * 30, 950, 190 + i * 30);
        fillrectangle(950, 160 + i * 30, 1050, 190 + i * 30);
    }
    setfillcolor(RGB(50, 100, 200));
    if(ppage != 0) {
        fillroundrect(790, 540, 860, 560, 10, 10);
        ot(800, 543, WHITE, 15, 0, "上一页", "宋体");
    }
    if(ppage != (int(s.size()) + 11) / 12 - 1) {
        fillroundrect(1000, 540, 1070, 560, 10, 10);
        ot(1010, 543, WHITE, 15, 0, "下一页", "宋体");
    }
    char tpage[100];
    sprintf(tpage, "第%d页  共%d页", ppage + 1, (int(s.size() + 11) / 12));
    ot(870, 540, BLACK, 20, 0, tpage, "宋体");
}
void SortPrint() {
    clearrectangle(340, 0, 1080, 720);
    setfillcolor(RGB(100, 150, 220));
    setlinecolor(RGB(100, 150, 220));
    fillrectangle(170, 25, 340, 115);
    ot(190, 60, WHITE, 20, 0, "指定课程排名", "宋体");
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(RGB(50, 100, 200));
    fillroundrect(370, 60, 650, 100, 10, 10);
    fillroundrect(670, 60, 950, 100, 10, 10);
    fillroundrect(970, 60, 1050, 100, 10, 10);
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    ot(385, 70, WHITE, 20, 0, "排序规则", "宋体");
    ot(685, 70, WHITE, 20, 0, "选择课程", "宋体");
    ot(990, 70, WHITE, 20, 0, "查询", "宋体");
    SortPrintGraph();
    int cs;
    object = int(s.size()) + 1;
    char lesson[100];
    char cmppath[100];
    bool tflag = false;
    bool cs1 = false, cs2 = false;
    while(true){
        msg = getmessage(EM_MOUSE);
        if(cs == 1) sprintf(cmppath, "%s", "成绩降序");
        else if(cs == 2) sprintf(cmppath, "%s", "成绩升序");
        else if(cs == 3) sprintf(cmppath, "%s", "学号升序");
        else sprintf(cmppath, "%s", " ");
        sprintf(lesson, "%s", lessonList[object].c_str());
        menuanimation(msg.x, msg.y, 4);
        if(msg.x >= 170 && msg.x <= 340 && msg.y >= 115 && msg.y <= 205)
            ot(182, 150, YELLOW, 20, 0, "指定分数段统计", "宋体");
        else ot(182, 150, WHITE, 20, 0, "指定分数段统计", "宋体");
        if(msg.x >= 490 && msg.x <= 640 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(230, 230, 230));
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, cmppath, "宋体");
        }else{
            setfillcolor(WHITE);
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, cmppath, "宋体");
        }
        if(msg.x >= 790 && msg.x <= 940 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(230, 230, 230));
            solidroundrect(790, 65, 940, 95, 10, 10);
            ot(795, 72, BLACK, 20, 0, lesson, "宋体");
        }else{
            setfillcolor(WHITE);
            solidroundrect(790, 65, 940, 95, 10, 10);
            ot(795, 72, BLACK, 20, 0, lesson, "宋体");
        }
        button_animation(msg, 970, 60, 1050, 100, WHITE, RGB(50, 100, 200));
        //判断是否显示按钮动画
        if(ppage != 0) button_animation(msg, 790, 540, 860, 560, WHITE, RGB(50, 100, 200));
        if(ppage != (int(s.size()) + 11) / 12 - 1) button_animation(msg, 1000, 540, 1070, 560, WHITE, RGB(50, 100, 200));

        switch (msg.message) {
            case WM_LBUTTONDOWN: {
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 4) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }
                if (msg.x >= 170 && msg.x <= 340 && msg.y >= 115 && msg.y <= 205) {
                    flushmessage(EM_MOUSE);
                    choose = 4;
                    return;
                }
                if (msg.x >= 790 && msg.x <= 860 && msg.y >= 540 && msg.y <= 560 && ppage != 0){
                    ppage --;
                    SortPrintGraph();
                    break;
                }
                if (msg.x >= 1000 && msg.x <= 1070 && msg.y >= 540 && msg.y <= 560 && ppage != (int(s.size()) + 11) / 12 - 1){
                    ppage ++;
                    SortPrintGraph();
                    break;
                }
                if (msg.x >= 970 && msg.x <= 1050 && msg.y >= 60 && msg.y <= 100){
                    if(cs1 && cs2) {
                        tflag = true;
                        cs1 = false;
                        cs2 = false;
                    }
                    else{
                        HWND er = GetHWnd();
                        MessageBox(er, "请设置筛选条件", "错误", MB_OK);
                    }
                }
                if (msg.x >= 490 && msg.x <= 640 && msg.y >= 65 && msg.y <= 95) {
                    bool ewhile = false;
                    while (true) {
                        flushmessage(EM_MOUSE);
                        msg = getmessage(EM_MOUSE);
                        setlinecolor(WHITE);
                        if (msg.x > 640 || msg.x < 490 || msg.y > 155 || msg.y < 65) {
                            break;
                        }
                        if (msg.y >= 95 && msg.y <= 115 && msg.x >= 490 && msg.x <= 640) {
                            setfillcolor(RGB(128, 128, 128));
                            fillrectangle(490, 95, 640, 115);
                            ot(495, 100, BLACK, 15, 0, "成绩降序", "宋体");
                        } else {
                            setfillcolor(RGB(200, 200, 200));
                            fillrectangle(490, 95, 640, 115);
                            ot(495, 100, BLACK, 15, 0, "成绩降序", "宋体");
                        }
                        if (msg.y >= 115 && msg.y <= 135 && msg.x >= 490 && msg.x <= 640) {
                            setfillcolor(RGB(128, 128, 128));
                            fillrectangle(490, 115, 640, 135);
                            ot(495, 120, BLACK, 15, 0, "成绩升序", "宋体");
                        } else {
                            setfillcolor(RGB(200, 200, 200));
                            fillrectangle(490, 115, 640, 135);
                            ot(495, 120, BLACK, 15, 0, "成绩升序", "宋体");
                        }
                        if (msg.y >= 135 && msg.y <= 155 && msg.x >= 490 && msg.x <= 640) {
                            setfillcolor(RGB(128, 128, 128));
                            fillrectangle(490, 135, 640, 155);
                            ot(495, 140, BLACK, 15, 0, "学号升序", "宋体");
                        } else {
                            setfillcolor(RGB(200, 200, 200));
                            fillrectangle(490, 135, 640, 155);
                            ot(495, 140, BLACK, 15, 0, "学号升序", "宋体");
                        }
                        //下拉栏动画
                        switch (msg.message) {
                            case WM_LBUTTONDOWN: {
                                if (msg.x >= 490 && msg.x <= 640 && msg.y >= 95 && msg.y <= 115) {
                                    cs = 1;
                                    flushmessage(EM_MOUSE);
                                    ppage = 0;
                                    SortPrintGraph();
                                    tflag = false;
                                    ewhile = true;
                                    cs1 = true;
                                }
                                if (msg.x >= 490 && msg.x <= 640 && msg.y >= 115 && msg.y <= 135) {
                                    cs = 2;
                                    flushmessage(EM_MOUSE);
                                    ppage = 0;
                                    SortPrintGraph();
                                    tflag = false;
                                    ewhile = true;
                                    cs1 = true;
                                }
                                if (msg.x >= 490 && msg.x <= 640 && msg.y >= 135 && msg.y <= 155) {
                                    cs = 3;
                                    flushmessage(EM_MOUSE);
                                    ppage = 0;
                                    SortPrintGraph();
                                    tflag = false;
                                    ewhile = true;
                                    cs1 = true;
                                }
                            }
                        }
                        if (ewhile) break;
                    }
                    clearrectangle(370, 95, 1080, 720);
                    SortPrintGraph();
                    setfillcolor(RGB(50, 100, 200));
                    setlinecolor(RGB(50, 100, 200));
                    fillroundrect(370, 60, 650, 100, 10, 10);
                    fillroundrect(670, 60, 950, 100, 10, 10);
                    fillroundrect(970, 60, 1050, 100, 10, 10);
                    ot(385, 70, WHITE, 20, 0, "排序规则", "宋体");
                    ot(685, 70, WHITE, 20, 0, "选择课程", "宋体");
                    ot(990, 70, WHITE, 20, 0, "查询", "宋体");
                }
                //下拉栏选择课程
                if (msg.x >= 790 && msg.x <= 940 && msg.y >= 65 && msg.y <= 95) {
                    bool ewhile = false;
                    while (true) {
                        flushmessage(EM_MOUSE);
                        msg = getmessage(EM_MOUSE);
                        setlinecolor(WHITE);
                        if (msg.x < 790 || msg.x > 940 || msg.y < 65 || msg.y > lessonNumber * 20 + 95) {
                            break;
                        }
                        for (int i = 0; i < lessonNumber; ++i) {
                            char st1[100];
                            sprintf(st1, "%s", lessonList[i].c_str());
                            if (msg.x >= 790 && msg.x <= 940 && msg.y > 95 + i * 20 && msg.y <= 95 + (i + 1) * 20) {
                                setfillcolor(RGB(128, 128, 128));
                                fillrectangle(790, 95 + i * 20, 940, 95 + (i + 1) * 20);
                                ot(795, 100 + i * 20, BLACK, 15, 0, st1, "宋体");
                            } else {
                                setfillcolor(RGB(200, 200, 200));
                                fillrectangle(790, 95 + i * 20,  940, 95 + (i + 1) * 20);
                                ot(795, 100 + i * 20, BLACK, 15, 0, st1, "宋体");
                            }
                        }
                        switch (msg.message) {
                            case WM_LBUTTONDOWN:{
                                for (int i = 0; i < lessonNumber; ++i) {
                                    if(msg.x >= 790 && msg.x <= 940 && msg.y > 95 + i * 20 && msg.y <= 95 + (i + 1) * 20){
                                        object = i;
                                        flushmessage(EM_MOUSE);
                                        ppage = 0;
                                        SortPrintGraph();
                                        tflag = false;
                                        ewhile = true;
                                        cs2 = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if(ewhile) break;
                    }
                    clearrectangle(370, 95, 1080, 720);
                    SortPrintGraph();
                    setfillcolor(RGB(50, 100, 200));
                    setlinecolor(RGB(50, 100, 200));
                    fillroundrect(370, 60, 650, 100, 10, 10);
                    fillroundrect(670, 60, 950, 100, 10, 10);
                    fillroundrect(970, 60, 1050, 100, 10, 10);
                    ot(385, 70, WHITE, 20, 0, "排序规则", "宋体");
                    ot(685, 70, WHITE, 20, 0, "选择课程", "宋体");
                    ot(990, 70, WHITE, 20, 0, "查询", "宋体");
                }
            }
        }
        flushmessage(EM_MOUSE);

        if(!tflag) continue;//同分数段统计，tflag代表筛选条件是否有更改

        //按选择的排序规则对学生进行排序
        if (cs == 1) sort(s.begin(), s.end(), CmpUp);
        else if (cs == 2) sort(s.begin(), s.end(), CmpDown);
        else sort(s.begin(), s.end(), Cmp);

        setlinecolor(BLACK);
        setfillcolor(WHITE);
        fillrectangle(370, 130, 450, 160);
        fillrectangle(450, 130, 680, 160);
        fillrectangle(680, 130, 880, 160);
        fillrectangle(880, 130, 950, 160);
        fillrectangle(950, 130, 1050, 160);
        ot(380, 135, BLACK, 25, 0, "排名", "楷体");
        ot(460, 135, BLACK, 25, 0, "学号", "楷体");
        ot(690, 135, BLACK, 25, 0, "姓名", "楷体");
        ot(890, 135, BLACK, 25, 0, "性别", "楷体");
        ot(960, 135, BLACK, 25, 0, "成绩", "楷体");
        auto cmp = s[max(0, ppage * 12 - 1)];
        int site;
        if(ppage == 0) site = 1;
        else site = 0;
        int point;
        if(ppage == (int(s.size() + 11) / 12) - 1) point = int(s.size()) % 12;
        else point = 12;

        for (int i = 0; i < point; ++ i) {
            if (cmp.ls[object] != s[i + ppage * 12].ls[object]) ++site;
            fillrectangle(370, 160 + i * 30, 450, 190 + i * 30);
            fillrectangle(450, 160 + i * 30, 680, 190 + i * 30);
            fillrectangle(680, 160 + i * 30, 880, 190 + i * 30);
            fillrectangle(880, 160 + i * 30, 950, 190 + i * 30);
            fillrectangle(950, 160 + i * 30, 1050, 190 + i * 30);
            char pm[10],xh[100],xm[100],cj[100],xb[100];
            sprintf(pm, "%d", site + tsit[ppage - 1]);
            sprintf(xh, "%s", s[i + ppage * 12].id.c_str());
            sprintf(xm, "%s", s[i + ppage * 12].name.c_str());
            sprintf(xb, "%s", s[i + ppage * 12].gender.c_str());
            sprintf(cj, "%.2lf", s[i + ppage * 12].ls[object]);
            ot(380, 165 + i * 30, BLACK, 25, 0, pm, "楷体");
            ot(460, 165 + i * 30, BLACK, 25, 0, xh, "楷体");
            ot(690, 165 + i * 30, BLACK, 25, 0, xm, "楷体");
            ot(890, 165 + i * 30, BLACK, 25, 0, xb, "楷体");
            ot(960, 165 + i * 30, BLACK, 25, 0, cj, "楷体");
            cmp = s[i + ppage * 12];
        }
        tsit[ppage] = site + tsit[ppage - 1];
    }
}

int page = 0;
int sit[100];
//输出学生成绩
void PrintScore(int li){
    int p = 1;
    for (int i = 0; i < li; ++ i){
        char zf[10];
        sprintf(zf, "%.2lf", s[i + page * 12].score);
        fillrectangle(840, 130 + p * 30, 1000, 160 + p * 30);
        ot(850, 135 + p * 30, BLACK, 25, 0, zf, "楷体");
        ++p;
    }
}
//输出所有学生信息
void PrintAll() {
    menu(1);
    char st[100];
    sprintf(st, "%s%d%s", "当前全部学生信息如下（共", int(s.size()), "人）：");
    ot(220, 50, BLACK, 25, 0, st, "宋体");
    ot(220, 100, BLACK, 15, 0, "总分点开可查看各科成绩", "宋体");
    char tpage[100];
    sprintf(tpage, "第%d页  共%d页", page + 1, (int(s.size()) + 11) / 12);
    ot(800, 100, BLACK, 20, 0, tpage, "宋体");
    sort(s.begin(), s.end(), CmpScore);
    setlinecolor(BLACK);
    setfillcolor(RGB(50, 100, 200));
    //判断是否显示翻页按钮
    if(page != 0) {
        fillroundrect(720, 100, 790, 120, 10, 10);
        ot(730, 103, WHITE, 15, 0, "上一页", "宋体");
    }
    else if(page != (int(s.size()) + 11) / 12 - 1) {
        fillroundrect(930, 100, 1000, 120, 10, 10);
        ot(940, 103, WHITE, 15, 0, "下一页", "宋体");
    }
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(220, 130, 290, 160);
    fillrectangle(290, 130, 530, 160);
    fillrectangle(530, 130, 770, 160);
    fillrectangle(770, 130, 840, 160);
    fillrectangle(840, 130, 1000, 160);
    ot(230, 135, BLACK, 25, 0, "排名", "楷体");
    ot(300, 135, BLACK, 25, 0, "学号", "楷体");
    ot(540, 135, BLACK, 25, 0, "姓名", "楷体");
    ot(780, 135, BLACK, 25, 0, "性别", "楷体");
    ot(850, 135, BLACK, 25, 0, "总分", "楷体");
    //判断当前页面需要显示的学生个数
    int point;
    if(page == (int(s.size()) + 11) / 12 - 1) point = int(s.size()) % 12;
    else point = 12;
    int site;
    if(page == 0) site = 1;
    else site = 0;
    auto cmp = s[max(page * 12 - 1, 0)];//临时比较用节点，用来计算排名
    //绘制表格
    for (int i = 0; i < point; ++ i) {
        if(s[i + page * 12].score != cmp.score) ++ site;
        fillrectangle(220, 160 + i * 30, 290, 190 + i * 30);
        fillrectangle(290, 160 + i * 30, 530, 190 + i * 30);
        fillrectangle(530, 160 + i * 30, 770, 190 + i * 30);
        fillrectangle(770, 160 + i * 30, 840, 190 + i * 30);
        char pm[10],xh[100],xm[100],xb[10];
        sprintf(pm, "%d", site + sit[page - 1]);
        sprintf(xh, "%s", s[i + page * 12].id.c_str());
        sprintf(xm, "%s", s[i + page * 12].name.c_str());
        sprintf(xb, "%s", s[i + page * 12].gender.c_str());
        ot(230, 165 + i * 30, BLACK, 25, 0, pm, "楷体");
        ot(300, 165 + i * 30, BLACK, 25, 0, xh, "楷体");
        ot(540, 165 + i * 30, BLACK, 25, 0, xm, "楷体");
        ot(780, 165 + i * 30, BLACK, 25, 0, xb, "楷体");
        cmp = s[i + page * 12];
    }
    sit[page] = site + sit[page - 1];//当前页面的第一位排名是上一页面的最后一位学生排名的值+0或1（取决于是否与上一页最后一个同学总分相同）
    PrintScore(point);
    bool ewhile = false;
    while(true){
        msg = getmessage(EM_MOUSE);
        menuanimation(msg.x, msg.y, 1);

        if(page != 0) button_animation(msg, 720, 100, 790, 120, WHITE, RGB(50, 100, 200));
        if(page != (int(s.size()) + 11) / 12 - 1) button_animation(msg, 930, 100, 1000, 120, WHITE, RGB(50, 100, 200));

        for (int i = 0; i < point; ++i) {
            char zf[100];
            if(msg.x >= 840 && msg.x <= 1000 && msg.y > 160 + i * 30 && msg.y <= 190 + i * 30){
                setlinecolor(BLACK);
                line(990, 170 + i * 30, 982, 180 + i * 30);
                line(990, 171 + i * 30, 982, 181 + i * 30);
                line(975, 170 + i * 30, 982, 180 + i * 30);
                line(975, 171 + i * 30, 982, 181 + i * 30);
            }else{
                setlinecolor(WHITE);
                line(990, 170 + i * 30, 982, 180 + i * 30);
                line(990, 171 + i * 30, 982, 181 + i * 30);
                line(975, 170 + i * 30, 982, 180 + i * 30);
                line(975, 171 + i * 30, 982, 181 + i * 30);
            }
        }
        switch (msg.message) {
            case WM_LBUTTONDOWN: {
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 1) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }

                if(msg.x >= 720 && msg.x <= 790 && msg.y >= 100 && msg.y <= 120 && page != 0){
                    page--;
                    return;
                }
                if(msg.x >= 930 && msg.x <= 1000 && msg.y >= 100 && msg.y <= 120 && page != (int(s.size()) + 11) / 12){
                    page++;
                    return;
                }

                //显示各科成绩
                for (int i = 0; i < point; ++i) {
                    if(msg.x >= 840 && msg.x <= 1000 && msg.y > 160 + i * 30 && msg.y <= 190 + i * 30) {
                        setfillcolor(RGB(200, 200, 200));
                        solidrectangle(440 , 190 + i * 30, 1060, 190 + i * 30 + ((lessonNumber + 2) / 3) * 30);
                        setlinecolor(WHITE);
                        line(645, 190 + i * 30, 645, 190 + i * 30 + ((lessonNumber + 2) / 3) * 30);
                        line(646, 190 + i * 30, 646, 190 + i * 30 + ((lessonNumber + 2) / 3) * 30);
                        line(845, 190 + i * 30, 845, 190 + i * 30 + ((lessonNumber + 2) / 3) * 30);
                        line(846, 190 + i * 30, 846, 190 + i * 30 + ((lessonNumber + 2) / 3) * 30);
                        for (int j = 0; j < lessonNumber; ++j) {
                            char tmp1[100],tmp2[10];
                            sprintf(tmp1, "%s", lessonList[j].c_str());
                            sprintf(tmp2, "%.2lf", s[i + page * 12].ls[j]);
                            ot(450 + j % 3 * 200, 195 + i * 30 + j / 3 * 30, BLACK, 20, 0, tmp1, "楷体");
                            ot(580 + j % 3 * 200, 195 + i * 30 + j / 3 * 30, BLACK, 20, 0, tmp2, "楷体");
                            line(440, 220 + i * 30 + j / 3 * 30, 1060, 220 + i * 30 + j / 3 * 30);
                            line(440, 221 + i * 30 + j / 3 * 30, 1060, 221 + i * 30 + j / 3 * 30);
                        }
                        while(true){
                            flushmessage(EM_MOUSE);
                            msg = getmessage(EM_MOUSE);
                            if(msg.y >= 160 + i * 30 && msg.y <= 190 + i * 30 && msg.x < 840 || msg.y >= 160 + i * 30 && msg.y <= 190 + i * 30 && msg.x > 1000 || msg.y < 160 + i * 30 || msg.y > 220 + i * 30 + lessonNumber / 3 * 30 || msg.y >= 190 + i * 30 && msg.y <= 220 + i * 30 + lessonNumber / 3 * 30 && msg.x < 440 || msg.y >= 190 + i * 30 && msg.y <= 220 + i * 30 + lessonNumber / 3 * 30 && msg.x > 1060){
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}

//保存数据到本地
void Save() {
    ofstream outfile;
    outfile.open("data.txt");
    outfile << s.size() << " " << lessonNumber << endl;
    for (int i = 0; i < lessonNumber; ++i) {
        outfile << lessonList[i] << " ";
    }outfile << endl;
    for (const auto& i : s) {
        outfile << i.id << " " << i.name << " " << i.gender << " ";
        for (int j = 0; j < lessonNumber; ++j) {
            outfile << i.ls[j] << " ";
        }outfile << endl;
    }
    outfile.close();
}

//从本地读取数据
void Read() {
    ifstream infile;
    infile.open("data.txt");
    int vsize;
    infile >> vsize >> lessonNumber;
    for (int i = 0; i < lessonNumber; ++i) {
        infile >> lessonList[i];
    }
    stu t;
    while(!empty(s)) s.pop_back();
    for (int i = 0; i < vsize; ++i) {
        infile >> t.id >> t.name >> t.gender;
        for (int j = 0; j < lessonNumber; ++j) {
            infile >> t.ls[j];
        }
        s.push_back(t);
    }
    for (auto & i : s){
        for (int j = 0; j < lessonNumber; ++j) {
            i.score += i.ls[j];
        }
    }
    infile.close();
}

//设置界面绘制
void settinggraph(){
    menu(7);
    char ts1[100];
    sprintf(ts1, "%s%d","当前已有科目数量：", lessonNumber);
    ot(220, 80, BLACK, 20, 0, ts1, "宋体");
    char ts2[100];
    sprintf(ts2, "%s%zu%s", "当前已有学生：", s.size(), "人");
    ot(220, 115, BLACK, 20, 0, ts2, "宋体");

    setfillcolor(RGB(100, 150, 250));
    setlinecolor(BLACK);
    fillroundrect(220, 160, 710, 210, 10, 10);
    setfillcolor(RGB(50, 100, 200));
    solidroundrect(230, 170, 380, 200, 10, 10);
    solidroundrect(390, 170, 540, 200, 10, 10);
    solidroundrect(550, 170, 700, 200, 10, 10);
    ot(235, 176, WHITE, 20, 0, "新增课程", "楷体");
    ot(395, 176, WHITE, 20, 0, "保存数据到本地", "楷体");
    ot(555, 176, WHITE, 20, 0, "读取本地数据", "楷体");
    for (int i = 0; i < lessonNumber; ++i) {
        fillroundrect(220 + i % 4 * 200, 240 + i / 4 * 100, 370 + i % 4 * 200, 270 + i / 4 * 100, 10, 10);
        char st[100];
        sprintf(st, "%s", lessonList[i].c_str());
        ot(225 + i % 4 * 200, 247 + i / 4 * 100, WHITE, 20, 0, st, "楷体");
    }
}
//设置
void Setting() {
    settinggraph();
    while(true){
        if(peekmessage(&msg, EM_MOUSE)){
            menuanimation(msg.x, msg.y, 7);

            button_animation(msg, 230, 170, 380, 200, WHITE, RGB(50, 100, 200));
            button_animation(msg, 390, 170, 540, 200, WHITE, RGB(50, 100, 200));
            button_animation(msg, 550, 170, 700, 200, WHITE, RGB(50, 100, 200));
            for (int i = 0; i < lessonNumber; ++i) {
                int tx = i % 4 * 200;
                int ty = i / 4 * 100;
                if(msg.x >= 220 + tx && msg.x <= 370 + tx && msg.y > 240 + ty && msg.y <= 270 + ty){
                    setlinecolor(WHITE);
                    roundrect(221 + tx, 241 + ty, 369 + tx, 269 + ty, 10, 10);
                }else{
                    setlinecolor(RGB(50,100,200));
                    roundrect(221 + tx, 241 + ty, 369 + tx, 269 + ty, 10, 10);
                }
            }
            switch (msg.message) {
                case WM_LBUTTONDOWN:
                    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720){
                        choose = choosegraph(msg.x, msg.y);
                        if(choose != 7){
                            flushmessage(EM_MOUSE);
                            return;
                        }
                    }
                    if(msg.x >= 230 && msg.x <= 380 && msg.y >= 170 && msg.y <= 200){
                        if(lessonNumber == 20){
                            HWND er = GetHWnd();
                            MessageBox(er, "添加失败，课程数已超过上限（20）", "错误", MB_OK);
                            break;
                        }
                        char st[100];
                        InputBox(st, 100, "请输入课程名称");
                        bool flag = false;
                        for (int i = 0; i < lessonNumber; ++i) {
                            if(lessonList[i] == st){
                                HWND er = GetHWnd();
                                MessageBox(er, "添加失败，课程已存在", "错误", MB_OK);
                                flag = true;
                                break;
                            }
                        }
                        if(flag) break;
                        lessonNumber++;
                        lessonList[lessonNumber-1] = st;
                        flushmessage(EM_MOUSE);
                        settinggraph();
                    }
                    if(msg.x >= 390 && msg.x <= 540 && msg.y >= 170 && msg.y <= 200) {
                        Save();
                        HWND res = GetHWnd();
                        MessageBox(res, "保存成功", "提示", MB_OK);
                        settinggraph();
                    }
                    if(msg.x >= 550 && msg.x <= 700 && msg.y >= 170 && msg.y <= 200){
                        Read();
                        if(lessonNumber == 0 && s.empty()){
                            HWND er = GetHWnd();
                            MessageBox(er, "本地无数据，读取失败", "错误", MB_OK);
                        }
                        else if(lessonNumber == 0){
                            HWND er = GetHWnd();
                            MessageBox(er, "当前课程数量为零，增加课程", "提示", MB_OK);

                        }
                        else{
                            HWND er = GetHWnd();
                            char ch[100];
                            sprintf(ch, "%s", "读取成功，数据已更新");
                            MessageBox(er, ch, "提示", MB_OK);
                        }
                        settinggraph();
                    }
                    for (int i = 0; i < lessonNumber; ++i) {
                        int tx = i % 4 * 200;
                        int ty = i / 4 * 100;
                        if(msg.x >= 220 + tx && msg.x <= 370 + tx && msg.y > 240 + ty && msg.y <= 270 + ty){
                            setfillcolor(RGB(200,200,200));
                            setlinecolor(BLACK);
                            fillrectangle(220 + tx, 270 + ty, 370 + tx, 295 + ty);
                            fillrectangle(220 + tx, 295 + ty, 370 + tx, 320 + ty);
                            ot(225 + tx, 275 + ty, BLACK, 15, 0, "修改名称", "宋体");
                            ot(225 + tx, 300 + ty, BLACK, 15, 0, "删除", "宋体");
                            flushmessage(EM_MOUSE);
                            setlinecolor(WHITE);
                            while(true) {
                                msg = getmessage(EM_MOUSE);
                                if (msg.x < 220 + tx || msg.x > 370 + tx || msg.y < 240 + ty || msg.y > 320 + ty) {
                                    clearrectangle(220 + tx, 270 + ty, 370 + tx, 320 + ty);
                                    break;
                                }
                                if (msg.y <= 295 + ty && msg.y > 270 + ty){
                                    setfillcolor(RGB(128,128,128));
                                    fillrectangle(220 + tx, 270 + ty, 370 + tx, 295 + ty);
                                    ot(225 + tx, 275 + ty, BLACK, 15, 0, "修改名称", "宋体");
                                }else{
                                    setfillcolor(RGB(200,200,200));
                                    fillrectangle(220 + tx, 270 + ty, 370 + tx, 295 + ty);
                                    ot(225 + tx, 275 + ty, BLACK, 15, 0, "修改名称", "宋体");
                                }
                                if (msg.y <= 320 + ty && msg.y > 295 + ty){
                                    setfillcolor(RGB(128,128,128));
                                    fillrectangle(220 + tx, 295 + ty, 370 + tx, 320 + ty);
                                    ot(225 + tx, 300 + ty, BLACK, 15, 0, "删除", "宋体");
                                }else{
                                    setfillcolor(RGB(200,200,200));
                                    fillrectangle(220 + tx, 295 + ty, 370 + tx, 320 + ty);
                                    ot(225 + tx, 300 + ty, BLACK, 15, 0, "删除", "宋体");
                                }
                                switch (msg.message) {
                                    case WM_LBUTTONDOWN:{
                                        if(msg.y <= 295 + ty && msg.y > 270 + ty && msg.x <= 370 + tx && msg.x >= 220 + tx){
                                            char st[100];
                                            InputBox(st,100,"修改后的课程名称");
                                            lessonList[i] = st;
                                            settinggraph();
                                        }
                                        //删除后从每个人的总成绩中减去此课程的成绩，并将后面课程的成绩向前移动，将lessonNumber - 1
                                        if(msg.y <= 320 + ty && msg.y > 295 + ty && msg.x <= 370 + tx && msg.x >= 220 + tx){
                                            for (int j = i; j < lessonNumber - 1; ++j) {
                                                lessonList[j] = lessonList[j + 1];
                                            }
                                            for (auto & j : s) {
                                                j.score -= j.ls[i];
                                                for (int k = i; k < lessonNumber - 1; ++k) {
                                                    j.ls[k] = j.ls[k + 1];
                                                }
                                            }lessonList[lessonNumber] = " ";
                                            lessonNumber --;
                                            HWND res = GetHWnd();
                                            MessageBox(res, "删除成功", "提示", MB_OK);
                                            settinggraph();
                                        }
                                    }
                                }
                            }
                        }
                    }
            }
            flushmessage(EM_MOUSE);
        }
    }
}

//退出界面
void Quit(){
    setlinecolor(RGB(50, 100, 200));
    setfillcolor(RGB(50, 100, 200));
    fillrectangle(500, 230, 720, 260);
    setfillcolor(WHITE);
    fillrectangle(500, 260, 720, 410);
    setfillcolor(RGB(50, 100, 200));
    fillroundrect(520, 280, 700, 310, 10, 10);
    fillroundrect(520, 320, 700, 350, 10, 10);
    fillroundrect(520, 360, 700, 390, 10, 10);
    ot(505, 235, WHITE, 20, 0, "退出系统？", "宋体");
    ot(560, 285, WHITE, 20, 0, "保存并退出", "宋体");
    ot(570, 325, WHITE, 20, 0, "直接退出", "宋体");
    ot(585, 365, WHITE, 20, 0, "取消", "宋体");
    while(true){
        msg = getmessage(EM_MOUSE);
        button_animation(msg, 520, 280, 700, 310, WHITE, RGB(50, 100, 200));
        button_animation(msg, 520, 320, 700, 350, WHITE, RGB(50, 100, 200));
        button_animation(msg, 520, 360, 700, 390, WHITE, RGB(50, 100, 200));

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                if(msg.x >= 520 && msg.x <= 700 && msg.y >= 280 && msg.y <= 310){
                    Save();
                    choose = 10;
                    closegraph();
                    return;
                }
                if(msg.x >= 520 && msg.x <= 700 && msg.y >= 320 && msg.y <= 350){
                    choose  = 10;
                    closegraph();
                    return;
                }
                //如果选择取消，则将界面恢复到进入退出界面前的界面，即qchoose对应的界面
                if(msg.x >= 520 && msg.x <= 700 && msg.y >= 360 && msg.y <= 390){
                    choose = qchoose;
                    flushmessage(EM_MOUSE);
                    return;
                }
            }
        }
    }
}

//开始界面绘制
bool endsystem;
void startgraph() {
    flushmessage(EM_MOUSE);
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 250, 80, false);
    putimage(400, 150, &ah);
    setlinecolor(BLACK);
    rectangle(380,250,700,295);
    ot(390, 260, BLACK, 30, 0, "欢迎使用小型教务系统", "楷体");

    setfillcolor(RGB(50,100,200));
    fillroundrect(450, 320, 630, 355, 10, 10);
    fillroundrect(450, 370, 630, 405, 10, 10);

    ot(500, 330, WHITE, 20, 0, "进入系统", "楷体");
    ot(520, 378, WHITE, 20, 0, "退出", "楷体");
    while(true){
        if(peekmessage(&msg, EM_MOUSE)){
            if(msg.x >= 450 && msg.x <= 630 && msg.y >= 320 && msg.y <= 355){
                setlinecolor(WHITE);
                roundrect(451, 321, 629, 354, 10, 10);
            }
            else {
                setlinecolor(RGB(50, 100, 200));
                roundrect(451, 321, 629, 354, 10, 10);
            }
            if(msg.x >= 450 && msg.x <= 630 && msg.y >= 370 && msg.y <= 405){
                setlinecolor(WHITE);
                roundrect(451, 371, 629, 404, 10, 10);
            }
            else {
                setlinecolor(RGB(50, 100, 200));
                roundrect(451, 371, 629, 404, 10, 10);
            }

            switch(msg.message){
                case WM_LBUTTONDOWN:
                    if(msg.x >= 450 && msg.x <= 630 && msg.y >= 320 && msg.y <= 355){
                        flushmessage(EM_MOUSE);
                        return;
                    }
                    if(msg.x >= 450 && msg.x <= 630 && msg.y >= 370 && msg.y <= 405){
                        endsystem = true;
                        closegraph();
                        return;
                    }
            }
        }
    }
}

//统计信息二级菜单
void Sort_or_Score(){
    menu(4);
    setlinecolor(RGB(70,120,210));
    setfillcolor(RGB(70,120,210));
    fillrectangle(170, 0, 340, 720);
    ot(190, 60, WHITE, 20, 0, "指定课程排名", "宋体");
    ot(182, 150, WHITE, 20, 0, "指定分数段统计", "宋体");
    while(true) {
        if (peekmessage(&msg, EM_MOUSE)) {
            menuanimation(msg.x, msg.y, 4);
            if (msg.x >= 170 && msg.x <= 340 && msg.y >= 25 && msg.y <= 115) ot(190, 60, YELLOW, 20, 0, "指定课程排名", "宋体");
            else ot(190, 60, WHITE, 20, 0, "指定课程排名", "宋体");
            if(msg.x >= 170 && msg.x <= 340 && msg.y >= 115 && msg.y <= 205) ot(182,  150, YELLOW, 20, 0, "指定分数段统计", "宋体");
            else ot(182, 150, WHITE, 20, 0, "指定分数段统计", "宋体");
        }
        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                if(msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720){
                    choose = choosegraph(msg.x, msg.y);
                    if(choose != 4) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }
                if(msg.x >= 170 && msg.x <= 340 && msg.y >= 25 && msg.y <= 115){
                    flushmessage(EM_MOUSE);
                    choose = 9;
                    return;
                }
                if(msg.x >= 170 && msg.x <= 340 && msg.y >= 115 && msg.y <= 205){
                    flushmessage(EM_MOUSE);
                    choose = 0;
                    return;
                }
            }
        }
    }
}

//首次进入界面绘制
void askinggraph() {
    flushmessage(EM_MOUSE);
    cleardevice();
    ot(230, 230, BLACK, 25, 0, "当前系统无数据,可选择读取本地数据或进行初始化设置", "楷体");
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(450, 280, 630, 325, 10, 10);
    fillroundrect(450, 355, 630, 400, 10, 10);
    ot(480, 293, WHITE, 20, 0, "读取本地数据", "楷体");
    ot(500, 368, WHITE, 20, 0, "进入设置", "楷体");
    while (true) {
        msg = getmessage(EM_MOUSE);
        if (msg.x >= 450 && msg.x <= 630 && msg.y >= 280 && msg.y <= 325) {
            setlinecolor(WHITE);
            roundrect(451, 281, 629, 324, 10, 10);
        } else {
            setlinecolor(RGB(50, 100, 200));
            roundrect(451, 281, 629, 324, 10, 10);
        }
        if (msg.x >= 450 && msg.x <= 630 && msg.y >= 330 && msg.y <= 375) {
            setlinecolor(WHITE);
            roundrect(451, 356, 629, 399, 10, 10);
        } else {
            setlinecolor(RGB(50, 100, 200));
            roundrect(451, 356, 629, 399, 10, 10);
        }

        switch (msg.message) {
            case WM_LBUTTONDOWN:
                if (msg.x >= 450 && msg.x <= 630 && msg.y >= 280 && msg.y <= 325) {
                    Read();
                    if (lessonNumber == 0 && s.empty()) {
                        HWND er = GetHWnd();
                        MessageBox(er, "本地无数据，将进入设置", "错误", MB_OK);
                        flushmessage(EM_MOUSE);
                        Setting();
                        return;
                    } else if (lessonNumber == 0) {
                        HWND er = GetHWnd();
                        MessageBox(er, "当前课程数量为零，请进入设置增加课程", "提示", MB_OK);
                        flushmessage(EM_MOUSE);
                        Setting();
                        return;
                    } else {
                        HWND er = GetHWnd();
                        char ch[100];
                        sprintf(ch, "%s%d%s%d%s", "读取成功，当前有", int(s.size()), "名学生，", lessonNumber,
                                "门课程");
                        flushmessage(EM_MOUSE);
                        MessageBox(er, ch, "提示", MB_OK);
                        return;
                    }
                }
                if (msg.x >= 450 && msg.x <= 630 && msg.y >= 355 && msg.y <= 400) {
                    endsystem = true;
                    flushmessage(EM_MOUSE);
                    Setting();
                    return;
                }
        }
    }
}

int main() {
    initgraph(1080, 720 | EX_SHOWCONSOLE);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    cleardevice();
    //初始化窗口

    try {
        pqxx::connection conn("dbname=SMUMS0 user=dboper password=dboper@123 host=120.46.71.168 port=26000");
        std::cout << "Connection successful." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    startgraph();//主界面
    flushmessage(EM_MOUSE);
    if(endsystem) return 0;//主界面退出

    if (lessonNumber == 0 && s.empty()) {
        askinggraph();
    }//初始化界面

    //界面跳转
    while (true) {
        switch (choose) {
            case 1:
                PrintAll(); break;
            case 2:
                AddStudent(); break;
            case 3:
                SearchStudent(); break;
            case 4:
                Sort_or_Score(); break;
            case 5:
                ChangeStudent(); break;
            case 6:
                DelStudent(); break;
            case 7:
                Setting(); break;
            case 8:
                Quit(); break;
            case 9:
                SortPrint(); break;
            case 0:
                ScoreStatistics(); break;
            case 10:
                return 0;
            default: break;
        }
    }
}