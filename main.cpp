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

ExMessage msg;//�����Ϣ�ṹ��

User root = {"root", "admin"};

User tmp = {"root", "admin"};

//��д��fillroundrect��Բ�Ǿ��Σ�
void fillroundrect_(object x){
    fillroundrect(x.posx, x.posy, x.posx + x.width, x.posy + x.height, 10, 10);
}

//��д��roundrect��Բ�Ǿ����߿�
void roundrect_(object x){
    roundrect(x.posx, x.posy, x.posx + x.width, x.posy + x.height, 10, 10);
}

//��д��fillrectangle�����Σ�
void fillrectangle_(object x){
    fillrectangle(x.posx, x.posy, x.posx + x.width, x.posy + x.height);
}

//��д��rectangle��Բ�Ǿ����߿�
void rectangle_(object x){
    rectangle(x.posx, x.posy, x.posx + x.width, x.posy + x.height);
}

//�ж��Ƿ���object��
bool isInside(ExMessage m, object x){
    if(m.x >= x.posx && m.x <= x.posx + x.width && m.y <= x.posy + x.height && m.y >= x.posy) return true;
    return false;
}

//���������װ��������ɫ���ֺţ����壬���λ�ã�
void OutputText(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st){
    settextcolor(color);
    settextstyle(nH,nW,st);
    outtextxy(x, y, str);
}

//��ťЧ����װ
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

//�������
void InitMouseMsg(){
    msg.x = 0, msg.y = 0;
}

//������ת
int choose = 1;
int qchoose;
int ChooseGraph(int mx, int my){
    if(mx >= 0 && mx <= 170){
        if(my >= 25 && my <= 115){
            return 1;//��ѯ�û���ϢUserQuery()
        }
        else if(my >= 115 && my <= 205){
            return 4;//��ѯ��Ʒ��ϢGoodsQuery()
        }
        else if(my >= 205 && my <= 295){
            return 3;//����ѧ����ϢSearchStudent()
        }
        else if(my >= 295 && my <= 385){
            return 4;//ѡ��������ʽSort_or_Score()
        }
        else if(my >= 385 && my <= 475){
            return 5;//�޸�ѧ����ϢChangeStudent()
        }
        else if(my >= 475 && my <= 565){
            return 6;//ɾ��ѧ����ϢDelStudent()
        }
        else if(my >= 565 && my <= 645){
            return 7;//����Setting()
        }
        else if(my >= 645 && my <= 720){
            qchoose = choose;
            return 8;//�˳�Quitgraph()
        }
    }
}

//���˵��б�
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
    OutputText(20,60,WHITE,20,0,"�û���Ϣ���", "����");
    OutputText(20,150,WHITE,20,0,"��Ʒ��Ϣ���", "����");
    OutputText(20,240,WHITE,20,0,"������Ϣ���", "����");
    OutputText(20,330,WHITE,20,0,"��̬��Ϣ���", "����");
    OutputText(20,420,WHITE,20,0,"�����Ϣ���", "����");
    OutputText(20,510,WHITE,20,0,"����Ա��Ϣ���", "����");
    OutputText(55,600,WHITE,20,0,"����", "����");
    OutputText(55,680,WHITE,20,0,"�˳�", "����");
}

//�˵�����
void MenuAnimation(int mx, int my, int n){
    if(mx >= 0 && mx <= 170 && my >= 25 && my <= 115 && n != 1)
        OutputText(20,60,YELLOW,20,0,"�û���Ϣ���", "����");
    else OutputText(20,60,WHITE,20,0,"�û���Ϣ���", "����");
    if(mx >= 0 && mx <= 170 && my >= 115 && my <= 205 && n != 2)
        OutputText(20,150,YELLOW,20,0,"��Ʒ��Ϣ���", "����");
    else OutputText(20,150,WHITE,20,0,"��Ʒ��Ϣ���", "����");
    if(mx >= 0 && mx <= 170 && my >= 205 && my <= 295 && n != 3)
        OutputText(20,240,YELLOW,20,0,"������Ϣ���", "����");
    else OutputText(20,240,WHITE,20,0,"������Ϣ���", "����");
    if(mx >= 0 && mx <= 170 && my >= 295 && my <= 385 && n != 4)
        OutputText(20,330,YELLOW,20,0,"��̬��Ϣ���", "����");
    else OutputText(20,330,WHITE,20,0,"��̬��Ϣ���", "����");
    if(mx >= 0 && mx <= 170 && my >= 385 && my <= 475 && n != 5)
        OutputText(20,420,YELLOW,20,0,"�����Ϣ���", "����");
    else OutputText(20,420,WHITE,20,0,"�����Ϣ���", "����");
    if(mx >= 0 && mx <= 170 && my >= 475 && my <= 565 && n != 6)
        OutputText(20,510,YELLOW,20,0,"����Ա��Ϣ���", "����");
    else OutputText(20,510,WHITE,20,0,"����Ա��Ϣ���", "����");
    if(mx >= 0 && mx <= 170 && my >= 565 && my <= 645 && n != 7)
        OutputText(55,600,YELLOW,20,0,"����", "����");
    else OutputText(55,600,WHITE,20,0,"����", "����");
    if(mx >= 0 && mx <= 170 && my >= 645 && my <= 720 && n != 8)
        OutputText(55,680,YELLOW,20,0,"�˳�", "����");
    else OutputText(55,680,WHITE,20,0,"�˳�", "����");
}

//���ܼ��
bool loginCheck(){
    if(tmp.userName == root.userName && tmp.password == root.password) return true;
    else return false;
}
//��ʼ�������
void startgraph() {
    flushmessage(EM_MOUSE);
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 250, 80, false);
    putimage(400, 150, &ah);
    setlinecolor(BLACK);
    rectangle(290,250,790,295);
    OutputText(310, 260, BLACK, 30, 0, "��ӭʹ����ý����վ�û�����ϵͳ", "����");

    object user = {400, 310, 280, 35};
    object password = {400, 360, 280, 35};
    setfillcolor(WHITE);
    fillroundrect_(user);
    fillroundrect_(password);
    OutputText(user.posx + 20, user.posy + 10, RGB(200, 200, 200), 17, 0, "�������û���", "����");
    OutputText(password.posx + 20, password.posy + 10, RGB(200, 200, 200), 17, 0, "����������", "����");

    object login = {450, 410, 180, 35};
    object exit = {450, 460, 180, 35};
    setfillcolor(CommonBlue);
    fillroundrect_(login);
    fillroundrect_(exit);
    OutputText(login.posx + 70, login.posy + 10, WHITE, 20, 0, "��¼", "����");
    OutputText(exit.posx + 70, exit.posy + 10, WHITE, 20, 0, "�˳�", "����");

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
                            MessageBox(er, "��¼ʧ�ܣ������˺�����", "����", MB_OK);
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
                        InputBox(s, 100, "�������û���");
                        tmp.userName = s;
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillroundrect_(user);
                        OutputText(user.posx + 20, user.posy + 10, BLACK, 17, 0, tmp.userName.c_str(), "����");
                        flushmessage(EM_MOUSE);
                    }
                    if(isInside(msg, password)){
                        char s[100];
                        InputBox(s, 100, "����������");
                        tmp.password = s;
                        setlinecolor(BLACK);
                        setfillcolor(WHITE);
                        fillroundrect_(password);
                        string encodedPassword = "";
                        for (int i = 0; i < tmp.password.size(); ++i) encodedPassword += '*';
                        OutputText(password.posx + 20, password.posy + 10, BLACK, 17, 0, encodedPassword.c_str(), "����");
                        flushmessage(EM_MOUSE);
                    }
            }
        }
    }
}

//�˳�����
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
    OutputText(quitWindowUp.posx + 5, quitWindowUp.posy + 5, WHITE, 20, 0, "�˳�ϵͳ��", "����");
    OutputText(quit.posx + 65, quit.posy + 5, WHITE, 20, 0, "�˳�", "����");
    OutputText(cancel.posx + 65, cancel.posy + 5, WHITE, 20, 0, "ȡ��", "����");
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
                //���ѡ��ȡ�����򽫽���ָ��������˳�����ǰ�Ľ��棬��qchoose��Ӧ�Ľ���
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

    startgraph();//������
    flushmessage(EM_MOUSE);
    if(endsystem) return 0;//�������˳�

    //������ת
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