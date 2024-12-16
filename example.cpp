/*
 * ������Ϣ��E12214013 ������
 * ���뻷����easyxͼ�ο� gcc 12.2.0
 * ʹ�ù��ߣ�CLion InnoSetup�����ڴ����װ����
 * ���������easyxͼ�ο��д����gcc 8.1.0��11.2.0�汾�»�����Ҳ������������Ĵ����ø�����gcc 12.2.0�汾�滻���ر���⼴�ɽ��
 *
 */
#include<bits/stdc++.h>
#include<graphics.h>
#include<conio.h>
#include<pqxx/pqxx>
using namespace std;

ExMessage msg;//�����Ϣ�ṹ��
int lessonNumber;//��ǰ��Ŀ����
//���ݽڵ㣨ѧ����
typedef struct stu {
    string name;//ѧ������
    string id;//ѧ��ѧ��
    double ls[100]{};//ѧ�����Ƴɼ�
    string gender;//ѧ���Ա�
    double score = 0;//ѧ���ܷ�
}stu;
string lessonList[100]; //����Ŀ����
vector<stu> s;

//���������װ��������ɫ���ֺţ����壬���λ�ã�
void ot(int x, int y, COLORREF color, int nH, int nW, LPCTSTR str, LPCTSTR st){
    settextcolor(color);
    settextstyle(nH,nW,st);
    outtextxy(x, y, str);
}

//��ťЧ����װ
void button_animation(ExMessage m, int l, int t, int r, int b, COLORREF colort, COLORREF colorf){
    if(m.x >= l && m.x <= r && msg.y >= t && msg.y <= b){
        setlinecolor(colort);
        roundrect(l + 1,  t + 1, r - 1, b - 1, 10, 10);
    }else{
        setlinecolor(colorf);
        roundrect(l + 1, t + 1, r - 1, b - 1, 10, 10);
    }
}

//������ת
int choose = 1;
int qchoose;
int choosegraph(int mx, int my){
    if(mx >= 0 && mx <= 170){
        if(my >= 25 && my <= 115){
            return 1;//����ѧ����ϢPrintAll()
        }
        else if(my >= 115 && my <= 205){
            return 2;//���ѧ����ϢAddStudent()
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
    ot(20,60,WHITE,20,0,"����ѧ����Ϣ", "����");
    ot(20,150,WHITE,20,0,"���ѧ����Ϣ", "����");
    ot(20,240,WHITE,20,0,"����ѧ����Ϣ", "����");
    ot(20,330,WHITE,20,0,"ͳ�ƿγ���Ϣ", "����");
    ot(20,420,WHITE,20,0,"�޸�ѧ����Ϣ", "����");
    ot(20,510,WHITE,20,0,"ɾ��ѧ����Ϣ", "����");
    ot(55,600,WHITE,20,0,"����", "����");
    ot(55,680,WHITE,20,0,"�˳�", "����");
}

//�˵�����
void menuanimation(int mx, int my, int n){
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 115 && n != 1) ot(20,60,YELLOW,20,0,"����ѧ����Ϣ", "����");
    else ot(20,60,WHITE,20,0,"����ѧ����Ϣ", "����");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 115 && msg.y <= 205 && n != 2) ot(20,150,YELLOW,20,0,"���ѧ����Ϣ", "����");
    else ot(20,150,WHITE,20,0,"���ѧ����Ϣ", "����");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 205 && msg.y <= 295 && n != 3) ot(20,240,YELLOW,20,0,"����ѧ����Ϣ", "����");
    else ot(20,240,WHITE,20,0,"����ѧ����Ϣ", "����");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 295 && msg.y <= 385 && n != 4) ot(20,330,YELLOW,20,0,"ͳ�ƿγ���Ϣ", "����");
    else ot(20,330,WHITE,20,0,"ͳ�ƿγ���Ϣ", "����");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 385 && msg.y <= 475 && n != 5) ot(20,420,YELLOW,20,0,"�޸�ѧ����Ϣ", "����");
    else ot(20,420,WHITE,20,0,"�޸�ѧ����Ϣ", "����");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 475 && msg.y <= 565 && n != 6) ot(20,510,YELLOW,20,0,"ɾ��ѧ����Ϣ", "����");
    else ot(20,510,WHITE,20,0,"ɾ��ѧ����Ϣ", "����");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 565 && msg.y <= 645 && n != 7) ot(55,600,YELLOW,20,0,"����", "����");
    else ot(55,600,WHITE,20,0,"����", "����");
    if(msg.x >= 0 && msg.x <= 170 && msg.y >= 645 && msg.y <= 720 && n != 8) ot(55,680,YELLOW,20,0,"�˳�", "����");
    else ot(55,680,WHITE,20,0,"�˳�", "����");
}

//����Ϸ��Լ��
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

//����ѧ����Ϣ
void SearchStudent() {
    menu(3);
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(270, 60, 660, 100, 10, 10);
    ot(280, 70, WHITE, 20, 0, "������ѧ�Ż�������", "����");
    fillroundrect(680, 60, 780, 100, 10, 10);
    ot(710, 70, WHITE, 20, 0, "��ѯ", "����");
    //�˵��ͽ������

    string input = "No_Input_Information";//�����ַ�����ʼ��
    char cinput[100];
    while(true){
        msg = getmessage(EM_MOUSE);
        menuanimation(msg.x, msg.y, 3);//�˵�����

        button_animation(msg, 680, 60, 780, 100, WHITE, RGB(50, 100, 200));//��ť����

        if(msg.x >= 460 && msg.x <= 655 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(460, 65, 655, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(460, 65, 655, 95, 10, 10);
        }
        if(input != "No_Input_Information") ot(470, 70, BLACK, 20, 0, cinput, "����");
        //��ʾ������Ϣ

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                //������ת
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 3) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }

                //����ѧ��ѧ��/����������ҵ��������Ϣ������s��δ�ҵ��㱨��
                if(msg.x >= 460 && msg.x <= 655 && msg.y >= 65 && msg.y <= 95) {
                    InputBox(cinput, 100, "����ѧ��ѧ��/����");
                    input = cinput;
                }
                if(msg.x >= 680 && msg.x <= 780 && msg.y >= 60 && msg.y <= 100){
                    clearrectangle(270, 130, 970, 720);
                    bool find = false;
                    for (auto & i : s) {
                        if(i.id == input || i.name == input){
                            find = true;
                            ot(270, 130, BLACK, 20, 0, "��ѯ�ɹ���ѧ����Ϣ���£�", "����");
                            input = "No_Input_Information";
                            char output[1000];
                            setlinecolor(BLACK);
                            line(270, 160, 970, 160);
                            line(270, 200, 970, 200);
                            sprintf(output, "%s%s      %s%s     %s%s", "ѧ�ţ�", i.id.c_str(), "������", i.name.c_str(), "�Ա�", i.gender.c_str());
                            ot(280, 170, BLACK, 20, 0, output, "����");
                            line(620, 200, 620, 200 + (lessonNumber + 1) / 2 * 40);
                            for (int j = 0; j < lessonNumber; ++j) {
                                char les[100];
                                char les_score[20];
                                sprintf(les, "%s", lessonList[j].c_str());
                                sprintf(les_score, "%.2lf", i.ls[j]);
                                if(j % 2 == 0){
                                    ot(280, 210 + j / 2 * 40, BLACK, 20, 0, les, "����");
                                    ot(470, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "����");
                                }else{
                                    ot(630, 210 + j / 2 * 40, BLACK, 20, 0, les, "����");
                                    ot(820, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "����");
                                }
                            }
                        }
                    }
                    if(!find){
                        HWND er = GetHWnd();
                        MessageBox(er, "δ�ҵ���ѧ������ȷ����Ϣ�����Ƿ���ȷ", "����", MB_OK);
                        input = "No_Input_Information";
                    }
                }
            }
        }
    }
}

//���ѧ����Ϣ
void AddStudent() {
    menu(2);
    char xh[20] = " ", xm[100] = " ", xb[10] = " ", cj[30][10] = {};
    setlinecolor(BLACK);
    setfillcolor(RGB(50, 100, 200));
    fillroundrect(280, 60, 655, 100, 10, 10);
    ot(290, 72, WHITE, 20, 0, "ѧ��ѧ��:", "����");
    fillroundrect(280, 120, 655, 160, 10, 10);
    ot(290, 132, WHITE, 20, 0, "ѧ������:", "����");
    fillroundrect(280, 180, 655, 220, 10, 10);
    ot(290, 192, WHITE, 20, 0, "ѧ���Ա�:", "����");
    if(lessonNumber <= 10)
        fillroundrect(280, 240, 675, 280 + (lessonNumber) * 35, 10, 10);
    else{
        fillroundrect(280, 240, 675, 280 + 10 * 35, 10, 10);
        fillroundrect(685, 240, 1075, 245 + (lessonNumber - 10) * 35, 10, 10);
    }

    ot(290, 252, WHITE, 20, 0, "ѧ���ɼ�:  �ܷ֣�", "����");
    fillroundrect(675, 60, 785, 100, 10, 10);
    ot(690, 72, WHITE, 20, 0, "ȷ�����", "����");
    fillroundrect(675, 120, 785, 160, 10, 10);
    ot(708, 132, WHITE, 20, 0, "����", "����");
    //�������

    //��ʼ����ʱ�ڵ�t
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
        ot(505, 250, BLACK, 20, 0, tscore, "����");
        if(msg.x >= 400 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 65, 650, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(400, 65, 650, 95, 10, 10);
        }
        if(t.id != "No_Input_id") ot(410, 72, BLACK, 20, 0, tid, "����");

        if(msg.x >= 400 && msg.x <= 650 && msg.y >= 125 && msg.y <= 155){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 125, 650, 155, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(400, 125, 650, 155, 10, 10);
        }
        if(t.name != "No_Input_name") ot(410, 132, BLACK, 20, 0, tname, "����");

        if(msg.x >= 400 && msg.x <= 520 && msg.y >= 185 && msg.y <= 215 && !male){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 185, 520, 215, 10, 10);
        }else if(!male){
            setfillcolor(WHITE);
            solidroundrect(400, 185, 520, 215, 10, 10);
        }
        ot(450, 190, BLACK, 20, 0, "��", "����");
        if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215 && !female){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(530, 185, 650, 215, 10, 10);
        }else if(!female){
            setfillcolor(WHITE);
            solidroundrect(530, 185, 650, 215, 10, 10);
        }
        ot(580, 190, BLACK, 20, 0, "Ů", "����");

        if(male){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(400, 185, 520, 215, 10, 10);
            ot(450, 190, BLACK, 20, 0, "��", "����");
        }
        if(female){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(530, 185, 650, 215, 10, 10);
            ot(580, 190, BLACK, 20, 0, "Ů", "����");
        }
        //ѡ�ж�����������Ϣ���

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
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "����");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "����");
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
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "����");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "����");
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
                    ot(840, 250 + i * 35, BLACK, 20, 0, tls[i + 10], "����");
                }
                ot(690, 247 + i * 35, WHITE, 20, 0, st, "����");
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
                //������ѧ���ظ�ʱ����
                if(msg.x >= 400 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95){
                    char txh[100];
                    InputBox(txh, 100, "������ѧ��ѧ��");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.id == txh){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "���󣬸�ѧ���Ѵ��ڣ�\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "����", MB_OK);
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
                    InputBox(txm, 100, "������ѧ������");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.name == txm){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "���󣬸�ѧ���Ѵ��ڣ�\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "����", MB_OK);
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
                    t.gender = "��";
                }
                if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215){
                    female = true;
                    male = false;
                    t.gender = "Ů";
                }
                //���벻�Ϸ�ʱ�������������������
                if(lessonNumber <= 10){
                    for (int i = 0; i < lessonNumber; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "�������ѧ�� ", lessonList[i].c_str(), " �ɼ�");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "����ӦΪ����", "����", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
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
                        sprintf(st, "%s%s%s", "�������ѧ�� ", lessonList[i].c_str(), " �ɼ�");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "����ӦΪ����", "����", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
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
                        sprintf(st, "%s%s%s", "�������ѧ�� ", lessonList[i + 10].c_str(), " �ɼ�");
                        if (msg.x >= 830 && msg.x <= 1070 && msg.y >= 245 + i * 35 && msg.y <= 275 + i * 35){
                            InputBox(tls[i + 10], 100, st);
                            if(!check(tls[i + 10])){
                                HWND er = GetHWnd();
                                MessageBox(er, "����ӦΪ����", "����", MB_OK);
                                break;
                            }
                            if(stod(tls[i + 10]) < 0 || stod(tls[i + 10]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
                                t.ls[i + 10] = -1;
                            }
                            t.score -= max(t.ls[i + 10], double(0));
                            t.ls[i + 10] = stod(tls[i + 10]);
                            t.score += t.ls[i + 10];
                        }
                    }
                }

                //�����δ��д��Ϣ������û����t����s����ʼ��t
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
                        MessageBox(er, "����Ϣδ��д", "����", MB_OK);
                    }
                    else{
                        HWND res = GetHWnd();
                        MessageBox(res, "��ӳɹ�", "��ʾ", MB_OK);
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

                //���ð�ť����ʼ��t
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
                    MessageBox(res, "������", "��ʾ", MB_OK);
                }
            }
        }
    }
}

//ɾ��ѧ����Ϣ
void DelStudent() {
    menu(6);

    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(270, 60, 660, 100, 10, 10);
    ot(280, 70, WHITE, 20, 0, "������ѧ�Ż�������", "����");
    fillroundrect(680, 60, 780, 100, 10, 10);
    ot(690, 70, WHITE, 20, 0, "ɾ��ѧ��", "����");
    //���ƽ���

    //ǰһ����ͬ����ѧ��
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
        if(input != "No_Input_Information") ot(470, 70, BLACK, 20, 0, cinput, "����");

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
                    InputBox(cinput, 100, "����ѧ��ѧ��/����");
                    input = cinput;
                    clearrectangle(270, 130, 970, 720);
                    bool find = false;
                    for (auto &i: s) {
                        if (i.id == input || i.name == input) {
                            find = true;
                            ot(270, 130, BLACK, 20, 0, "��ǰѧ����Ϣ���£�", "����");
                            input = "No_Input_Information";
                            char output[1000];
                            setlinecolor(BLACK);
                            line(270, 160, 970, 160);
                            line(270, 200, 970, 200);
                            sprintf(output, "%s%s      %s%s     %s%s", "ѧ�ţ�", i.id.c_str(), "������", i.name.c_str(),
                                    "�Ա�", i.gender.c_str());
                            ot(280, 170, BLACK, 20, 0, output, "����");
                            line(620, 200, 620, 200 + (lessonNumber + 1) / 2 * 40);
                            for (int j = 0; j < lessonNumber; ++j) {
                                char les[100];
                                char les_score[20];
                                sprintf(les, "%s", lessonList[j].c_str());
                                sprintf(les_score, "%.2lf", i.ls[j]);
                                if (j % 2 == 0) {
                                    ot(280, 210 + j / 2 * 40, BLACK, 20, 0, les, "����");
                                    ot(470, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "����");
                                } else {
                                    ot(630, 210 + j / 2 * 40, BLACK, 20, 0, les, "����");
                                    ot(820, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "����");
                                }
                            }
                        }
                    }
                    if (!find) {
                        HWND er = GetHWnd();
                        MessageBox(er, "δ�ҵ�ѧ������ȷ����Ϣ�����Ƿ���ȷ", "����", MB_OK);
                        input = "No_Input_Information";
                    }
                }

                //�������ɾ��ѧ����ʱ��������������ѯ�ʣ�ѡ��ȡ������ս��沢���»��ƴ��ڣ�������ʾѧ����Ϣ��ѡ��ȷ�ϼ���s���Ƴ��˽ڵ�
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
                    ot(510, 245, WHITE, 20, 0, "ȷ��ɾ����ѧ����", "����");
                    ot(570, 300, WHITE, 20, 0, "ȷ��ɾ��", "����");
                    ot(590, 350, WHITE, 20, 0, "ȡ��", "����");
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
                                            MessageBox(res, "��ɾ����ѧ��", "��ʾ", MB_OK);
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
                                            ot(270, 130, BLACK, 20, 0, "��ǰѧ����Ϣ���£�", "����");
                                            input = "No_Input_Information";
                                            char output[1000];
                                            setlinecolor(BLACK);
                                            line(270, 160, 970, 160);
                                            line(270, 200, 970, 200);
                                            sprintf(output, "%s%s      %s%s     %s%s", "ѧ�ţ�", i.id.c_str(), "������", i.name.c_str(),
                                                    "�Ա�", i.gender.c_str());
                                            ot(280, 170, BLACK, 20, 0, output, "����");
                                            line(620, 200, 620, 200 + (lessonNumber + 1) / 2 * 40);
                                            for (int j = 0; j < lessonNumber; ++j) {
                                                char les[100];
                                                char les_score[20];
                                                sprintf(les, "%s", lessonList[j].c_str());
                                                sprintf(les_score, "%.2lf", i.ls[j]);
                                                if (j % 2 == 0) {
                                                    ot(280, 210 + j / 2 * 40, BLACK, 20, 0, les, "����");
                                                    ot(470, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "����");
                                                } else {
                                                    ot(630, 210 + j / 2 * 40, BLACK, 20, 0, les, "����");
                                                    ot(820, 210 + j / 2 * 40, BLACK, 20, 0, les_score, "����");
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

//�޸�ѧ����Ϣ
void ChangeStudent() {
    menu(5);
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(280, 60, 655, 100, 10, 10);
    ot(290, 70, WHITE, 20, 0, "������ѧ�Ż�������", "����");
    fillroundrect(675, 60, 785, 100, 10, 10);
    ot(710, 70, WHITE, 20, 0, "��ѯ", "����");
    char xh[20] = " ", xm[100] = " ", xb[10] = " ", cj[30][10] = {};
    fillroundrect(280, 120, 655, 160, 10, 10);
    ot(290, 132, WHITE, 20, 0, "ѧ��ѧ��:", "����");
    fillroundrect(675, 120, 1040, 160, 10, 10);
    ot(685, 132, WHITE, 20, 0, "ѧ������:", "����");
    fillroundrect(280, 180, 655, 220, 10, 10);
    ot(290, 192, WHITE, 20, 0, "ѧ���Ա�:", "����");
    if(lessonNumber <= 10)
        fillroundrect(280, 240, 675, 280 + (lessonNumber) * 35, 10, 10);
    else{
        fillroundrect(280, 240, 675, 280 + 10 * 35, 10, 10);
        fillroundrect(685, 240, 1075, 245 + (lessonNumber - 10) * 35, 10, 10);
    }

    ot(290, 252, WHITE, 20, 0, "ѧ���ɼ�:  �ܷ֣�", "����");
    fillroundrect(675, 180, 785, 220, 10, 10);
    ot(690, 192, WHITE, 20, 0, "�����޸�", "����");
    fillroundrect(805, 180, 915, 220, 10, 10);
    ot(835, 192, WHITE, 20, 0, "����", "����");

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
        ot(505, 250, BLACK, 20, 0, tscore, "����");
        if(msg.x >= 400 && msg.x <= 650 && msg.y >= 125 && msg.y <= 155){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 125, 650, 155, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(400, 125, 650, 155, 10, 10);
        }
        if(t.id != "No_Input_id") ot(410, 132, BLACK, 20, 0, tid, "����");

        if(msg.x >= 785 && msg.x <= 1035 && msg.y >= 125 && msg.y <= 155){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(785, 125, 1035, 155, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(785, 125, 1035, 155, 10, 10);
        }
        if(t.name != "No_Input_name") ot(800, 132, BLACK, 20, 0, tname, "����");

        if(msg.x >= 400 && msg.x <= 520 && msg.y >= 185 && msg.y <= 215 && !male){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(400, 185, 520, 215, 10, 10);
        }else if(!male){
            setfillcolor(WHITE);
            solidroundrect(400, 185, 520, 215, 10, 10);
        }
        ot(450, 190, BLACK, 20, 0, "��", "����");
        if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215 && !female){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(530, 185, 650, 215, 10, 10);
        }else if(!female){
            setfillcolor(WHITE);
            solidroundrect(530, 185, 650, 215, 10, 10);
        }
        ot(580, 190, BLACK, 20, 0, "Ů", "����");

        if(male){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(400, 185, 520, 215, 10, 10);
            ot(450, 190, BLACK, 20, 0, "��", "����");
        }
        if(female){
            setfillcolor(RGB(180, 180, 180));
            solidroundrect(530, 185, 650, 215, 10, 10);
            ot(580, 190, BLACK, 20, 0, "Ů", "����");
        }

        if(msg.x >= 460 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(460, 65, 650, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(460, 65, 650, 95, 10, 10);
        }
        if(input != "No_Input_Information") ot(470, 70, BLACK, 20, 0, cinput, "����");

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
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "����");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "����");
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
                    ot(440, 285 + i * 35, BLACK, 20, 0, tls[i], "����");
                }
                ot(290, 282 + i * 35, WHITE, 20, 0, st, "����");
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
                    ot(840, 250 + i * 35, BLACK, 20, 0, tls[i + 10], "����");
                }
                ot(690, 247 + i * 35, WHITE, 20, 0, st, "����");
            }
        }
        //ѡ�з�������

        switch (msg.message) {
            case WM_LBUTTONDOWN:{
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = choosegraph(msg.x, msg.y);
                    if (choose != 5) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }

                //����ѧ������/ѧ�Ž��в��ң��Ҳ�������
                if(msg.x >= 460 && msg.x <= 650 && msg.y >= 65 && msg.y <= 95) {
                    InputBox(cinput, 100, "����ѧ��ѧ��/����");
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
                            if(t.gender == "��") male = true;
                            else female = true;
                            break;
                        }
                        ++p;
                    }
                    if(!find){
                        HWND er = GetHWnd();
                        MessageBox(er, "δ�ҵ���ѧ������ȷ����Ϣ�����Ƿ���ȷ", "����", MB_OK);
                        input = "No_Input_Information";
                    }
                }
                //�޸�ʱ�߼�ͬ���ѧ���������ǰѧ�Ż������Ѵ��ڱ㱨��
                if(msg.x >= 400 && msg.x <= 650 && msg.y >= 125 && msg.y <= 155){
                    char txh[100];
                    InputBox(txh, 100, "������ѧ��ѧ��");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.id == txh){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "���󣬸�ѧ���Ѵ��ڣ�\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "����", MB_OK);
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
                    InputBox(txm, 100, "������ѧ������");
                    bool exist = false;
                    for (auto & i : s) {
                        if(i.name == txm){
                            HWND er = GetHWnd();
                            char txs[100];
                            sprintf(txs, "���󣬸�ѧ���Ѵ��ڣ�\n%s %s", i.id.c_str(), i.name.c_str());
                            MessageBox(er, txs, "����", MB_OK);
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
                    t.gender = "��";
                }
                if(msg.x >= 530 && msg.x <= 650 && msg.y >= 185 && msg.y <= 215){
                    female = true;
                    male = false;
                    t.gender = "Ů";
                }

                //�������ݣ����Ϸ����ݱ���
                if(lessonNumber <= 10){
                    for (int i = 0; i < lessonNumber; ++i) {
                        char st[100];
                        sprintf(st, "%s%s%s", "�������ѧ�� ", lessonList[i].c_str(), " �ɼ�");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "����ӦΪ����", "����", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
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
                        sprintf(st, "%s%s%s", "�������ѧ�� ", lessonList[i].c_str(), " �ɼ�");
                        if (msg.x >= 430 && msg.x <= 670 && msg.y >= 280 + i * 35 && msg.y <= 310 + i * 35){
                            InputBox(tls[i], 100, st);
                            if(!check(tls[i])){
                                HWND er = GetHWnd();
                                MessageBox(er, "����ӦΪ����", "����", MB_OK);
                                break;
                            }
                            if(stod(tls[i]) < 0 || stod(tls[i]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
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
                        sprintf(st, "%s%s%s", "�������ѧ�� ", lessonList[i + 10].c_str(), " �ɼ�");
                        if (msg.x >= 830 && msg.x <= 1070 && msg.y >= 245 + i * 35 && msg.y <= 275 + i * 35){
                            InputBox(tls[i + 10], 100, st);
                            if(!check(tls[i + 10])){
                                HWND er = GetHWnd();
                                MessageBox(er, "����ӦΪ����", "����", MB_OK);
                                break;
                            }
                            if(stod(tls[i + 10]) < 0 || stod(tls[i + 10]) > 100){
                                HWND er = GetHWnd();
                                MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
                                t.ls[i + 10] = -1;
                            }
                            t.score -= max(t.ls[i + 10], double(0));
                            t.ls[i + 10] = stod(tls[i + 10]);
                            t.score += t.ls[i + 10];
                        }
                    }
                }

                //����Ƿ�������Ϣ����д��������򽫵�ǰt����s��ɾ�����ҵ��Ľڵ㣬��֮����
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
                        MessageBox(er, "����Ϣδ��д", "����", MB_OK);
                    }
                    else{
                        HWND res = GetHWnd();
                        MessageBox(res, "�޸ĳɹ�", "��ʾ", MB_OK);
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
                //���ü���ʼ��t������s���в���
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
//����ʽ
int object;//��ǰѧ��
bool CmpUp(const stu& a, const stu& b) {
    return a.ls[object] > b.ls[object];
}//�γ̳ɼ�����
bool CmpDown(const stu& a, const stu& b) {
    return a.ls[object] < b.ls[object];
}//�γ̳ɼ�����
bool Cmp(const stu& a, const stu& b) {
    return a.id < b.id;
}//ѧ������
bool CmpScore(const stu& a, const stu& b){
    return a.score > b.score;
}//�ֽܷ���
//ָ������������
//�����������
void ScoreStatisticsGraph(){
    clearrectangle(370, 100, 1080, 720);
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(370, 130, 450, 160);
    fillrectangle(450, 130, 680, 160);
    fillrectangle(680, 130, 880, 160);
    fillrectangle(880, 130, 950, 160);
    fillrectangle(950, 130, 1050, 160);
    ot(380, 135, BLACK, 25, 0, "����", "����");
    ot(460, 135, BLACK, 25, 0, "ѧ��", "����");
    ot(690, 135, BLACK, 25, 0, "����", "����");
    ot(890, 135, BLACK, 25, 0, "�Ա�", "����");
    ot(960, 135, BLACK, 25, 0, "�ɼ�", "����");
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
        ot(800, 543, WHITE, 15, 0, "��һҳ", "����");
    }
    if(ppage != (int(SSlist.size()) + 11) / 12 - 1 && int(SSlist.size() + 11) / 12 != 0) {
        fillroundrect(1000, 540, 1070, 560, 10, 10);
        ot(1010, 543, WHITE, 15, 0, "��һҳ", "����");
    }
    //�ж��Ƿ���ʾ��ҳ��ť
    char tpage[100];
    sprintf(tpage, "��%dҳ  ��%dҳ", ppage + 1, max(1, (int(SSlist.size() + 11) / 12)));
    ot(870, 540, BLACK, 20, 0, tpage, "����");
}
void ScoreStatistics() {
    clearrectangle(340, 0, 1080, 720);
    setfillcolor(RGB(100, 150, 220));
    setlinecolor(RGB(100, 150, 220));
    fillrectangle(170, 115, 340, 205);
    ot(182, 150, WHITE, 20, 0, "ָ��������ͳ��", "����");
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(RGB(50, 100, 200));
    fillroundrect(370, 60, 650, 100, 10, 10);
    fillroundrect(670, 60, 950, 100, 10, 10);
    fillroundrect(970, 60, 1050, 100, 10, 10);
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    ot(385, 70, WHITE, 20, 0, "ѡ��γ�", "����");
    ot(685, 70, WHITE, 20, 0, "����ֶ�", "����");
    ot(850, 70, WHITE, 20, 0, "��", "����");
    ot(990, 70, WHITE, 20, 0, "��ѯ", "����");
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
            ot(190, 60, YELLOW, 20, 0, "ָ���γ�����", "����");
        else ot(190, 60, WHITE, 20, 0, "ָ���γ�����", "����");
        if(msg.x >= 490 && msg.x <= 640 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(230, 230, 230));
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, lesson, "����");
        }else{
            setfillcolor(WHITE);
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, lesson, "����");
        }
        if(msg.x >= 780 && msg.x <= 845 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(780, 65, 845, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(780, 65, 845, 95, 10, 10);
        }ot(785, 70, BLACK, 20, 0, tfn, "����");
        if(msg.x >= 875 && msg.x <= 940 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(200, 200, 200));
            solidroundrect(875, 65, 940, 95, 10, 10);
        }else{
            setfillcolor(WHITE);
            solidroundrect(875, 65, 940, 95, 10, 10);
        }ot(880, 70, BLACK, 20, 0, tsn, "����");

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
                    InputBox(tfn, 20, "�����������Χ��");
                    if(!check(tfn)){
                        HWND er = GetHWnd();
                        MessageBox(er, "����ӦΪ����", "����", MB_OK);
                        break;
                    }
                    if(stod(tfn) < 0 || stod(tfn) > 100){
                        HWND er = GetHWnd();
                        MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
                        break;
                    }
                    ScoreStatisticsGraph();
                    tflag = false;
                    fn = stod(tfn);
                }
                if (msg.x >= 875 && msg.x <= 940 && msg.y >= 60 && msg.y <= 100){
                    cs3 = true;
                    InputBox(tsn, 20, "�����������Χ��");
                    if(!check(tsn)){
                        HWND er = GetHWnd();
                        MessageBox(er, "����ӦΪ����", "����", MB_OK);
                        break;
                    }
                    if(stod(tsn) < 0 || stod(tsn) > 100){
                        HWND er = GetHWnd();
                        MessageBox(er, "�ɼ�Ӧ��0-100֮��", "����", MB_OK);
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
                        MessageBox(er, "������ɸѡ����", "����", MB_OK);
                    }
                }
                //����ѡ��γ�
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
                                ot(495, 100 + i * 20, BLACK, 15, 0, st1, "����");
                            } else {
                                setfillcolor(RGB(200, 200, 200));
                                fillrectangle(490, 95 + i * 20,  640, 95 + (i + 1) * 20);
                                ot(495, 100 + i * 20, BLACK, 15, 0, st1, "����");
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
                    ot(385, 70, WHITE, 20, 0, "ѡ��γ�", "����");
                    ot(685, 70, WHITE, 20, 0, "����ֶ�", "����");
                    ot(850, 70, WHITE, 20, 0, "��", "����");
                    ot(990, 70, WHITE, 20, 0, "��ѯ", "����");
                }
            }
        }
        if(!tflag) continue;//tflag����Ƿ�Ե�ǰɸѡ����������ɸѡ�����û���޸��򲻶�������ݽ�����������Է�ֹ������˸

        //��������������нϴ��С�ķֿ�������Ϊɸѡ����
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
        ot(380, 135, BLACK, 25, 0, "����", "����");
        ot(460, 135, BLACK, 25, 0, "ѧ��", "����");
        ot(690, 135, BLACK, 25, 0, "����", "����");
        ot(890, 135, BLACK, 25, 0, "�Ա�", "����");
        ot(960, 135, BLACK, 25, 0, "�ɼ�", "����");
        auto cmp = SSlist[max(0, ppage * 12 - 1)];
        int site;
        //ȷ����ǰҳ����ʾ��ѧ������
        if(ppage == 0) site = 1;
        else site = 0;
        int point;
        if(ppage == (int(SSlist.size() + 11) / 12) - 1) point = int(SSlist.size()) % 12;
        else point = 12;
        //�����ǰҳ��
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
            ot(380, 165 + i * 30, BLACK, 25, 0, pm, "����");
            ot(460, 165 + i * 30, BLACK, 25, 0, xh, "����");
            ot(690, 165 + i * 30, BLACK, 25, 0, xm, "����");
            ot(890, 165 + i * 30, BLACK, 25, 0, xb, "����");
            ot(960, 165 + i * 30, BLACK, 25, 0, cj, "����");
            cmp = SSlist[i + ppage * 12];
        }
        tsit[ppage] = site + tsit[ppage - 1];

        char ratio[100];
        sprintf(ratio, "��ǰ�ֶ��ڹ�%d�ˣ�����������%d����ռ��", situation, int(s.size()));
        ot(380, 540, BLACK, 20, 0, ratio, "����");
        setlinecolor(BLACK);
        setfillcolor(WHITE);
        fillrectangle(380, 570, 680, 595);
        setfillcolor(RGB(50, 100, 200));
        fillrectangle(380, 570, 380 + int(double(situation) / double(s.size()) * 100) * 3, 595);
        sprintf(ratio, "%d%%", int(double(situation) / double(s.size()) * 100));
        ot(370 + int(double(situation) / double(s.size()) * 100) * 3, 600, BLACK, 20, 0, ratio, "����");
    }
}
//ָ���γ�����
//�����������
void SortPrintGraph(){
    clearrectangle(370, 100, 1080, 720);
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(370, 130, 450, 160);
    fillrectangle(450, 130, 680, 160);
    fillrectangle(680, 130, 880, 160);
    fillrectangle(880, 130, 950, 160);
    fillrectangle(950, 130, 1050, 160);
    ot(380, 135, BLACK, 25, 0, "����", "����");
    ot(460, 135, BLACK, 25, 0, "ѧ��", "����");
    ot(690, 135, BLACK, 25, 0, "����", "����");
    ot(890, 135, BLACK, 25, 0, "�Ա�", "����");
    ot(960, 135, BLACK, 25, 0, "�ɼ�", "����");
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
        ot(800, 543, WHITE, 15, 0, "��һҳ", "����");
    }
    if(ppage != (int(s.size()) + 11) / 12 - 1) {
        fillroundrect(1000, 540, 1070, 560, 10, 10);
        ot(1010, 543, WHITE, 15, 0, "��һҳ", "����");
    }
    char tpage[100];
    sprintf(tpage, "��%dҳ  ��%dҳ", ppage + 1, (int(s.size() + 11) / 12));
    ot(870, 540, BLACK, 20, 0, tpage, "����");
}
void SortPrint() {
    clearrectangle(340, 0, 1080, 720);
    setfillcolor(RGB(100, 150, 220));
    setlinecolor(RGB(100, 150, 220));
    fillrectangle(170, 25, 340, 115);
    ot(190, 60, WHITE, 20, 0, "ָ���γ�����", "����");
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(RGB(50, 100, 200));
    fillroundrect(370, 60, 650, 100, 10, 10);
    fillroundrect(670, 60, 950, 100, 10, 10);
    fillroundrect(970, 60, 1050, 100, 10, 10);
    setfillcolor(WHITE);
    setlinecolor(WHITE);
    ot(385, 70, WHITE, 20, 0, "�������", "����");
    ot(685, 70, WHITE, 20, 0, "ѡ��γ�", "����");
    ot(990, 70, WHITE, 20, 0, "��ѯ", "����");
    SortPrintGraph();
    int cs;
    object = int(s.size()) + 1;
    char lesson[100];
    char cmppath[100];
    bool tflag = false;
    bool cs1 = false, cs2 = false;
    while(true){
        msg = getmessage(EM_MOUSE);
        if(cs == 1) sprintf(cmppath, "%s", "�ɼ�����");
        else if(cs == 2) sprintf(cmppath, "%s", "�ɼ�����");
        else if(cs == 3) sprintf(cmppath, "%s", "ѧ������");
        else sprintf(cmppath, "%s", " ");
        sprintf(lesson, "%s", lessonList[object].c_str());
        menuanimation(msg.x, msg.y, 4);
        if(msg.x >= 170 && msg.x <= 340 && msg.y >= 115 && msg.y <= 205)
            ot(182, 150, YELLOW, 20, 0, "ָ��������ͳ��", "����");
        else ot(182, 150, WHITE, 20, 0, "ָ��������ͳ��", "����");
        if(msg.x >= 490 && msg.x <= 640 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(230, 230, 230));
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, cmppath, "����");
        }else{
            setfillcolor(WHITE);
            solidroundrect(490, 65, 640, 95, 10, 10);
            ot(495, 72, BLACK, 20, 0, cmppath, "����");
        }
        if(msg.x >= 790 && msg.x <= 940 && msg.y >= 65 && msg.y <= 95){
            setfillcolor(RGB(230, 230, 230));
            solidroundrect(790, 65, 940, 95, 10, 10);
            ot(795, 72, BLACK, 20, 0, lesson, "����");
        }else{
            setfillcolor(WHITE);
            solidroundrect(790, 65, 940, 95, 10, 10);
            ot(795, 72, BLACK, 20, 0, lesson, "����");
        }
        button_animation(msg, 970, 60, 1050, 100, WHITE, RGB(50, 100, 200));
        //�ж��Ƿ���ʾ��ť����
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
                        MessageBox(er, "������ɸѡ����", "����", MB_OK);
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
                            ot(495, 100, BLACK, 15, 0, "�ɼ�����", "����");
                        } else {
                            setfillcolor(RGB(200, 200, 200));
                            fillrectangle(490, 95, 640, 115);
                            ot(495, 100, BLACK, 15, 0, "�ɼ�����", "����");
                        }
                        if (msg.y >= 115 && msg.y <= 135 && msg.x >= 490 && msg.x <= 640) {
                            setfillcolor(RGB(128, 128, 128));
                            fillrectangle(490, 115, 640, 135);
                            ot(495, 120, BLACK, 15, 0, "�ɼ�����", "����");
                        } else {
                            setfillcolor(RGB(200, 200, 200));
                            fillrectangle(490, 115, 640, 135);
                            ot(495, 120, BLACK, 15, 0, "�ɼ�����", "����");
                        }
                        if (msg.y >= 135 && msg.y <= 155 && msg.x >= 490 && msg.x <= 640) {
                            setfillcolor(RGB(128, 128, 128));
                            fillrectangle(490, 135, 640, 155);
                            ot(495, 140, BLACK, 15, 0, "ѧ������", "����");
                        } else {
                            setfillcolor(RGB(200, 200, 200));
                            fillrectangle(490, 135, 640, 155);
                            ot(495, 140, BLACK, 15, 0, "ѧ������", "����");
                        }
                        //����������
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
                    ot(385, 70, WHITE, 20, 0, "�������", "����");
                    ot(685, 70, WHITE, 20, 0, "ѡ��γ�", "����");
                    ot(990, 70, WHITE, 20, 0, "��ѯ", "����");
                }
                //������ѡ��γ�
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
                                ot(795, 100 + i * 20, BLACK, 15, 0, st1, "����");
                            } else {
                                setfillcolor(RGB(200, 200, 200));
                                fillrectangle(790, 95 + i * 20,  940, 95 + (i + 1) * 20);
                                ot(795, 100 + i * 20, BLACK, 15, 0, st1, "����");
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
                    ot(385, 70, WHITE, 20, 0, "�������", "����");
                    ot(685, 70, WHITE, 20, 0, "ѡ��γ�", "����");
                    ot(990, 70, WHITE, 20, 0, "��ѯ", "����");
                }
            }
        }
        flushmessage(EM_MOUSE);

        if(!tflag) continue;//ͬ������ͳ�ƣ�tflag����ɸѡ�����Ƿ��и���

        //��ѡ�����������ѧ����������
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
        ot(380, 135, BLACK, 25, 0, "����", "����");
        ot(460, 135, BLACK, 25, 0, "ѧ��", "����");
        ot(690, 135, BLACK, 25, 0, "����", "����");
        ot(890, 135, BLACK, 25, 0, "�Ա�", "����");
        ot(960, 135, BLACK, 25, 0, "�ɼ�", "����");
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
            ot(380, 165 + i * 30, BLACK, 25, 0, pm, "����");
            ot(460, 165 + i * 30, BLACK, 25, 0, xh, "����");
            ot(690, 165 + i * 30, BLACK, 25, 0, xm, "����");
            ot(890, 165 + i * 30, BLACK, 25, 0, xb, "����");
            ot(960, 165 + i * 30, BLACK, 25, 0, cj, "����");
            cmp = s[i + ppage * 12];
        }
        tsit[ppage] = site + tsit[ppage - 1];
    }
}

int page = 0;
int sit[100];
//���ѧ���ɼ�
void PrintScore(int li){
    int p = 1;
    for (int i = 0; i < li; ++ i){
        char zf[10];
        sprintf(zf, "%.2lf", s[i + page * 12].score);
        fillrectangle(840, 130 + p * 30, 1000, 160 + p * 30);
        ot(850, 135 + p * 30, BLACK, 25, 0, zf, "����");
        ++p;
    }
}
//�������ѧ����Ϣ
void PrintAll() {
    menu(1);
    char st[100];
    sprintf(st, "%s%d%s", "��ǰȫ��ѧ����Ϣ���£���", int(s.size()), "�ˣ���");
    ot(220, 50, BLACK, 25, 0, st, "����");
    ot(220, 100, BLACK, 15, 0, "�ֵܷ㿪�ɲ鿴���Ƴɼ�", "����");
    char tpage[100];
    sprintf(tpage, "��%dҳ  ��%dҳ", page + 1, (int(s.size()) + 11) / 12);
    ot(800, 100, BLACK, 20, 0, tpage, "����");
    sort(s.begin(), s.end(), CmpScore);
    setlinecolor(BLACK);
    setfillcolor(RGB(50, 100, 200));
    //�ж��Ƿ���ʾ��ҳ��ť
    if(page != 0) {
        fillroundrect(720, 100, 790, 120, 10, 10);
        ot(730, 103, WHITE, 15, 0, "��һҳ", "����");
    }
    else if(page != (int(s.size()) + 11) / 12 - 1) {
        fillroundrect(930, 100, 1000, 120, 10, 10);
        ot(940, 103, WHITE, 15, 0, "��һҳ", "����");
    }
    setlinecolor(BLACK);
    setfillcolor(WHITE);
    fillrectangle(220, 130, 290, 160);
    fillrectangle(290, 130, 530, 160);
    fillrectangle(530, 130, 770, 160);
    fillrectangle(770, 130, 840, 160);
    fillrectangle(840, 130, 1000, 160);
    ot(230, 135, BLACK, 25, 0, "����", "����");
    ot(300, 135, BLACK, 25, 0, "ѧ��", "����");
    ot(540, 135, BLACK, 25, 0, "����", "����");
    ot(780, 135, BLACK, 25, 0, "�Ա�", "����");
    ot(850, 135, BLACK, 25, 0, "�ܷ�", "����");
    //�жϵ�ǰҳ����Ҫ��ʾ��ѧ������
    int point;
    if(page == (int(s.size()) + 11) / 12 - 1) point = int(s.size()) % 12;
    else point = 12;
    int site;
    if(page == 0) site = 1;
    else site = 0;
    auto cmp = s[max(page * 12 - 1, 0)];//��ʱ�Ƚ��ýڵ㣬������������
    //���Ʊ��
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
        ot(230, 165 + i * 30, BLACK, 25, 0, pm, "����");
        ot(300, 165 + i * 30, BLACK, 25, 0, xh, "����");
        ot(540, 165 + i * 30, BLACK, 25, 0, xm, "����");
        ot(780, 165 + i * 30, BLACK, 25, 0, xb, "����");
        cmp = s[i + page * 12];
    }
    sit[page] = site + sit[page - 1];//��ǰҳ��ĵ�һλ��������һҳ������һλѧ��������ֵ+0��1��ȡ�����Ƿ�����һҳ���һ��ͬѧ�ܷ���ͬ��
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

                //��ʾ���Ƴɼ�
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
                            ot(450 + j % 3 * 200, 195 + i * 30 + j / 3 * 30, BLACK, 20, 0, tmp1, "����");
                            ot(580 + j % 3 * 200, 195 + i * 30 + j / 3 * 30, BLACK, 20, 0, tmp2, "����");
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

//�������ݵ�����
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

//�ӱ��ض�ȡ����
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

//���ý������
void settinggraph(){
    menu(7);
    char ts1[100];
    sprintf(ts1, "%s%d","��ǰ���п�Ŀ������", lessonNumber);
    ot(220, 80, BLACK, 20, 0, ts1, "����");
    char ts2[100];
    sprintf(ts2, "%s%zu%s", "��ǰ����ѧ����", s.size(), "��");
    ot(220, 115, BLACK, 20, 0, ts2, "����");

    setfillcolor(RGB(100, 150, 250));
    setlinecolor(BLACK);
    fillroundrect(220, 160, 710, 210, 10, 10);
    setfillcolor(RGB(50, 100, 200));
    solidroundrect(230, 170, 380, 200, 10, 10);
    solidroundrect(390, 170, 540, 200, 10, 10);
    solidroundrect(550, 170, 700, 200, 10, 10);
    ot(235, 176, WHITE, 20, 0, "�����γ�", "����");
    ot(395, 176, WHITE, 20, 0, "�������ݵ�����", "����");
    ot(555, 176, WHITE, 20, 0, "��ȡ��������", "����");
    for (int i = 0; i < lessonNumber; ++i) {
        fillroundrect(220 + i % 4 * 200, 240 + i / 4 * 100, 370 + i % 4 * 200, 270 + i / 4 * 100, 10, 10);
        char st[100];
        sprintf(st, "%s", lessonList[i].c_str());
        ot(225 + i % 4 * 200, 247 + i / 4 * 100, WHITE, 20, 0, st, "����");
    }
}
//����
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
                            MessageBox(er, "���ʧ�ܣ��γ����ѳ������ޣ�20��", "����", MB_OK);
                            break;
                        }
                        char st[100];
                        InputBox(st, 100, "������γ�����");
                        bool flag = false;
                        for (int i = 0; i < lessonNumber; ++i) {
                            if(lessonList[i] == st){
                                HWND er = GetHWnd();
                                MessageBox(er, "���ʧ�ܣ��γ��Ѵ���", "����", MB_OK);
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
                        MessageBox(res, "����ɹ�", "��ʾ", MB_OK);
                        settinggraph();
                    }
                    if(msg.x >= 550 && msg.x <= 700 && msg.y >= 170 && msg.y <= 200){
                        Read();
                        if(lessonNumber == 0 && s.empty()){
                            HWND er = GetHWnd();
                            MessageBox(er, "���������ݣ���ȡʧ��", "����", MB_OK);
                        }
                        else if(lessonNumber == 0){
                            HWND er = GetHWnd();
                            MessageBox(er, "��ǰ�γ�����Ϊ�㣬���ӿγ�", "��ʾ", MB_OK);

                        }
                        else{
                            HWND er = GetHWnd();
                            char ch[100];
                            sprintf(ch, "%s", "��ȡ�ɹ��������Ѹ���");
                            MessageBox(er, ch, "��ʾ", MB_OK);
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
                            ot(225 + tx, 275 + ty, BLACK, 15, 0, "�޸�����", "����");
                            ot(225 + tx, 300 + ty, BLACK, 15, 0, "ɾ��", "����");
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
                                    ot(225 + tx, 275 + ty, BLACK, 15, 0, "�޸�����", "����");
                                }else{
                                    setfillcolor(RGB(200,200,200));
                                    fillrectangle(220 + tx, 270 + ty, 370 + tx, 295 + ty);
                                    ot(225 + tx, 275 + ty, BLACK, 15, 0, "�޸�����", "����");
                                }
                                if (msg.y <= 320 + ty && msg.y > 295 + ty){
                                    setfillcolor(RGB(128,128,128));
                                    fillrectangle(220 + tx, 295 + ty, 370 + tx, 320 + ty);
                                    ot(225 + tx, 300 + ty, BLACK, 15, 0, "ɾ��", "����");
                                }else{
                                    setfillcolor(RGB(200,200,200));
                                    fillrectangle(220 + tx, 295 + ty, 370 + tx, 320 + ty);
                                    ot(225 + tx, 300 + ty, BLACK, 15, 0, "ɾ��", "����");
                                }
                                switch (msg.message) {
                                    case WM_LBUTTONDOWN:{
                                        if(msg.y <= 295 + ty && msg.y > 270 + ty && msg.x <= 370 + tx && msg.x >= 220 + tx){
                                            char st[100];
                                            InputBox(st,100,"�޸ĺ�Ŀγ�����");
                                            lessonList[i] = st;
                                            settinggraph();
                                        }
                                        //ɾ�����ÿ���˵��ܳɼ��м�ȥ�˿γ̵ĳɼ�����������γ̵ĳɼ���ǰ�ƶ�����lessonNumber - 1
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
                                            MessageBox(res, "ɾ���ɹ�", "��ʾ", MB_OK);
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

//�˳�����
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
    ot(505, 235, WHITE, 20, 0, "�˳�ϵͳ��", "����");
    ot(560, 285, WHITE, 20, 0, "���沢�˳�", "����");
    ot(570, 325, WHITE, 20, 0, "ֱ���˳�", "����");
    ot(585, 365, WHITE, 20, 0, "ȡ��", "����");
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
                //���ѡ��ȡ�����򽫽���ָ��������˳�����ǰ�Ľ��棬��qchoose��Ӧ�Ľ���
                if(msg.x >= 520 && msg.x <= 700 && msg.y >= 360 && msg.y <= 390){
                    choose = qchoose;
                    flushmessage(EM_MOUSE);
                    return;
                }
            }
        }
    }
}

//��ʼ�������
bool endsystem;
void startgraph() {
    flushmessage(EM_MOUSE);
    IMAGE ah;
    loadimage(&ah,R"(.\ahu.jpg)", 250, 80, false);
    putimage(400, 150, &ah);
    setlinecolor(BLACK);
    rectangle(380,250,700,295);
    ot(390, 260, BLACK, 30, 0, "��ӭʹ��С�ͽ���ϵͳ", "����");

    setfillcolor(RGB(50,100,200));
    fillroundrect(450, 320, 630, 355, 10, 10);
    fillroundrect(450, 370, 630, 405, 10, 10);

    ot(500, 330, WHITE, 20, 0, "����ϵͳ", "����");
    ot(520, 378, WHITE, 20, 0, "�˳�", "����");
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

//ͳ����Ϣ�����˵�
void Sort_or_Score(){
    menu(4);
    setlinecolor(RGB(70,120,210));
    setfillcolor(RGB(70,120,210));
    fillrectangle(170, 0, 340, 720);
    ot(190, 60, WHITE, 20, 0, "ָ���γ�����", "����");
    ot(182, 150, WHITE, 20, 0, "ָ��������ͳ��", "����");
    while(true) {
        if (peekmessage(&msg, EM_MOUSE)) {
            menuanimation(msg.x, msg.y, 4);
            if (msg.x >= 170 && msg.x <= 340 && msg.y >= 25 && msg.y <= 115) ot(190, 60, YELLOW, 20, 0, "ָ���γ�����", "����");
            else ot(190, 60, WHITE, 20, 0, "ָ���γ�����", "����");
            if(msg.x >= 170 && msg.x <= 340 && msg.y >= 115 && msg.y <= 205) ot(182,  150, YELLOW, 20, 0, "ָ��������ͳ��", "����");
            else ot(182, 150, WHITE, 20, 0, "ָ��������ͳ��", "����");
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

//�״ν���������
void askinggraph() {
    flushmessage(EM_MOUSE);
    cleardevice();
    ot(230, 230, BLACK, 25, 0, "��ǰϵͳ������,��ѡ���ȡ�������ݻ���г�ʼ������", "����");
    setfillcolor(RGB(50, 100, 200));
    setlinecolor(BLACK);
    fillroundrect(450, 280, 630, 325, 10, 10);
    fillroundrect(450, 355, 630, 400, 10, 10);
    ot(480, 293, WHITE, 20, 0, "��ȡ��������", "����");
    ot(500, 368, WHITE, 20, 0, "��������", "����");
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
                        MessageBox(er, "���������ݣ�����������", "����", MB_OK);
                        flushmessage(EM_MOUSE);
                        Setting();
                        return;
                    } else if (lessonNumber == 0) {
                        HWND er = GetHWnd();
                        MessageBox(er, "��ǰ�γ�����Ϊ�㣬������������ӿγ�", "��ʾ", MB_OK);
                        flushmessage(EM_MOUSE);
                        Setting();
                        return;
                    } else {
                        HWND er = GetHWnd();
                        char ch[100];
                        sprintf(ch, "%s%d%s%d%s", "��ȡ�ɹ�����ǰ��", int(s.size()), "��ѧ����", lessonNumber,
                                "�ſγ�");
                        flushmessage(EM_MOUSE);
                        MessageBox(er, ch, "��ʾ", MB_OK);
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
    //��ʼ������

    try {
        pqxx::connection conn("dbname=SMUMS0 user=dboper password=dboper@123 host=120.46.71.168 port=26000");
        std::cout << "Connection successful." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    startgraph();//������
    flushmessage(EM_MOUSE);
    if(endsystem) return 0;//�������˳�

    if (lessonNumber == 0 && s.empty()) {
        askinggraph();
    }//��ʼ������

    //������ת
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