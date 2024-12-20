#include <graphics.h>
#include <conio.h>
#include <pqxx/pqxx>
#include "UserQuery.h"

using namespace std;

bool genderMale = false;
bool genderFemale = false;
bool userID = false;
bool userNickname = false;
bool userAgeInput1 = false;
bool userAgeInput2 = false;
bool showPage = false;
int curPage = 0;
int pageNum = 0;
std::string userid;
std::string usernickname;
std::string userAge1 = "0", userAge2 = "0";
object userTag = {220, 70, 350, 40};
object userTagInputBar = {userTag.posx + 100, userTag.posy + 5, 240, 30};
object userName = {userTag.posx + userTag.width + 30, userTag.posy, 350, 40};
object userNameInputBar = {userName.posx + 100, userTag.posy + 5, 240, 30};
object userGenderWindow = {userTag.posx, userTag.posy + userTag.height + 15, 220, 40};
object userGenderMale = {userGenderWindow.posx + 100, userTag.posy + userTag.height + 20, 50, 30};
object userGenderFemale = {userGenderMale.posx + userGenderMale.width + 10, userGenderMale.posy, 50, 30};
object userAge = {userGenderWindow.posx + userGenderWindow.width + 35, userGenderWindow.posy, 215, 40};
object userAgeInputBar1 = {userAge.posx + 70, userGenderWindow.posy + 5, 50, 30};
object userAgeInputBar2 = {userAgeInputBar1.posx + userAgeInputBar1.width + 40, userGenderWindow.posy + 5, 50, 30};
object userSearchButton = {userAge.posx + userAge.width + 30, userGenderWindow.posy, 100, 40};
object userResetButton = {userSearchButton.posx + userSearchButton.width + 30, userGenderWindow.posy, 100, 40};
object pageUpButton = {880, 530, 50, 20};
object pageDownButton = {730, 530, 50, 20};

//清空表格区域
void ClearUserQueryGraph(){
    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle_({180, 215, 780, 500});
    setlinecolor(BLACK);
    rectangle_({220, 185, 140, 30});
    rectangle_({360, 185, 180, 30});
    rectangle_({540, 185, 80, 30});
    rectangle_({620, 185, 70, 30});
    rectangle_({690, 185, 260, 30});
    OutputText(220 + 10, 185 + 5, BLACK, 20, 0, "用户id", "宋体");
    OutputText(360 + 10, 185 + 5, BLACK, 20, 0, "用户昵称", "宋体");
    OutputText(540 + 10, 185 + 5, BLACK, 20, 0, "性别", "宋体");
    OutputText(620 + 10, 185 + 5, BLACK, 20, 0, "年龄", "宋体");
    OutputText(690 + 10, 185 + 5, BLACK, 20, 0, "电子邮件", "宋体");
    if(showPage){
        setfillcolor(CommonBlue);
        fillroundrect_(pageUpButton);
        fillroundrect_(pageDownButton);
        OutputText(pageDownButton.posx + 15, pageUpButton.posy + 3, WHITE, 15, 0, "<=", "宋体");
        OutputText(pageUpButton.posx + 15, pageDownButton.posy + 3, WHITE, 15, 0, "=>", "宋体");
        setfillcolor(WHITE);
    }
}
//基础控件绘制
void UserQueryGraph(){
    setlinecolor(CommonBlue);
    setfillcolor(CommonBlue);
    fillroundrect_(userTag);
    fillroundrect_(userName);
    fillroundrect_(userGenderWindow);
    fillroundrect_(userAge);
    fillroundrect_(userSearchButton);
    fillroundrect_(userResetButton);
    setfillcolor(LightBlue);
    fillroundrect_(userGenderMale);
    fillroundrect_(userGenderFemale);
    setfillcolor(WHITE);
    fillroundrect_(userTagInputBar);
    fillroundrect_(userNameInputBar);
    fillroundrect_(userAgeInputBar1);
    fillroundrect_(userAgeInputBar2);

    OutputText(userTag.posx + 10, userTag.posy + 10, WHITE, 20, 0, "精确查找", "宋体");
    OutputText(userName.posx + 10, userTag.posy + 10, WHITE, 20, 0, "用户昵称", "宋体");
    OutputText(userGenderWindow.posx + 10, userGenderWindow.posy + 10, WHITE, 20, 0, "性别", "宋体");
    OutputText(userGenderMale.posx + 15, userGenderMale.posy + 5, WHITE, 20, 0, "男", "宋体");
    OutputText(userGenderFemale.posx + 15, userGenderFemale.posy + 5, WHITE, 20, 0, "女", "宋体");
    OutputText(userAge.posx + 10, userAge.posy + 10, WHITE, 20, 0, "年龄", "宋体");
    OutputText(userAgeInputBar1.posx + userAgeInputBar1.width + 10, userGenderWindow.posy + 10, WHITE, 20, 0, "到", "宋体");
    OutputText(userSearchButton.posx + 30, userSearchButton.posy + 10, WHITE, 20, 0, "查找", "宋体");
    OutputText(userResetButton.posx + 30, userResetButton.posy + 10, WHITE, 20, 0, "重置", "宋体");
    ClearUserQueryGraph();
}
//用户查询二级菜单
void UserQuerySecondMenu(int n){

}
//用户查询功能
void UserQuery(){
    Menu(1);
    UserQueryGraph();

    vector<string> conditions;
    while(true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(msg.x, msg.y, 1);
        if (peekmessage(&msg, EM_MOUSE)) {
            ButtonAnimation(msg, userSearchButton, WHITE, CommonBlue);
            ButtonAnimation(msg, userResetButton, WHITE, CommonBlue);
            ButtonAnimation(msg, userGenderMale, WHITE, CommonBlue);
            ButtonAnimation(msg, userGenderFemale, WHITE, CommonBlue);
            ButtonAnimation(msg, userAgeInputBar1, WHITE, CommonBlue, 3);
            ButtonAnimation(msg, userAgeInputBar2, WHITE, CommonBlue, 3);
            ButtonAnimation(msg, userTagInputBar, WHITE, CommonBlue, 3);
            ButtonAnimation(msg, userNameInputBar, WHITE, CommonBlue, 3);

            if(genderMale) ButtonAnimation(msg, userGenderMale, WHITE, WHITE);
            else ButtonAnimation(msg, userGenderMale, WHITE, CommonBlue);

            if(genderFemale) ButtonAnimation(msg, userGenderFemale, WHITE, WHITE);
            else ButtonAnimation(msg, userGenderFemale, WHITE, CommonBlue);

            if(userID) OutputText(userTagInputBar.posx + 10, userTagInputBar.posy + 8, BLACK, 15, 0, userid.c_str(), "宋体");
            if(userNickname) OutputText(userNameInputBar.posx + 10, userNameInputBar.posy + 8, BLACK, 15, 0, usernickname.c_str(), "宋体");
            if(userAgeInput1) OutputText(userAgeInputBar1.posx + 10, userAgeInputBar1.posy + 8, BLACK, 15, 0, userAge1.c_str(), "宋体");
            if(userAgeInput2) OutputText(userAgeInputBar2.posx + 10, userAgeInputBar2.posy + 8, BLACK, 15, 0, userAge2.c_str(), "宋体");

            if(showPage){
                ButtonAnimation(msg, pageUpButton, WHITE, CommonBlue);
                ButtonAnimation(msg, pageDownButton, WHITE, CommonBlue);
                OutputText(815, 530, BLACK, 20, 0, to_string(curPage + 1).c_str(), "宋体");
                OutputText(835, 530, BLACK, 20, 0, ("/" + to_string(pageNum + 1)).c_str(), "宋体");
            }

            if (res.size() > 0) {
                for (int i = curPage * 10; i < min(curPage * 10 + 10, res.size()); ++i) {
                    setlinecolor(BLACK);
                    rectangle_({220, 215 + (i % 10) * 30, 140, 30});
                    rectangle_({360, 215 + (i % 10) * 30, 180, 30});
                    rectangle_({540, 215 + (i % 10) * 30, 80, 30});
                    rectangle_({620, 215 + (i % 10) * 30, 70, 30});
                    rectangle_({690, 215 + (i % 10) * 30, 260, 30});
                    OutputText(220 + 10, 215 + 5 + (i % 10) * 30, BLACK, 20, 0, res[i]["userid"].as<string>().c_str(), "宋体");
                    OutputText(360 + 10, 215 + 5 + (i % 10) * 30, BLACK, 20, 0, res[i]["username"].as<string>().c_str(), "宋体");
                    OutputText(540 + 10, 215 + 5 + (i % 10) * 30, BLACK, 20, 0, res[i]["gender"].as<string>().c_str(), "宋体");
                    OutputText(620 + 10, 215 + 5 + (i % 10) * 30, BLACK, 20, 0, res[i]["age"].as<string>().c_str(), "宋体");
                    OutputText(690 + 10, 215 + 5 + (i % 10) * 30, BLACK, 20, 0, res[i]["email"].as<string>().c_str(), "宋体");
                }
            } else {
                OutputText(400, 350, BLACK, 30, 0, "未找到符合要求的用户", "宋体");
            }

            switch(msg.message) {
                case WM_LBUTTONDOWN:
                    if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                        choose = ChooseGraph(msg.x, msg.y);
                        if (choose != 1) {
                            flushmessage(EM_MOUSE);
                            return;
                        }
                    }
                    else if (isInside(msg, userTagInputBar)){
                        fillroundrect_(userTagInputBar);
                        char s[100];
                        InputBox(s, 100, "请输入用户ID");
                        userID = true;
                        userid = s;
                    }
                    else if (isInside(msg, userNameInputBar)){
                        fillroundrect_(userNameInputBar);
                        char s[100];
                        InputBox(s, 100, "请输入用户昵称");
                        userNickname = true;
                        usernickname = s;
                    }
                    else if (isInside(msg, userGenderMale)) {
                        if(genderFemale) {
                            genderFemale = false;
                            genderMale = true;
                        }else if(genderMale){
                            genderMale = false;
                        }else {
                            genderMale = true;
                        }
                    }
                    else if (isInside(msg, userGenderFemale)){
                        if(genderMale){
                            genderMale = false;
                            genderFemale = true;
                        }else if(genderFemale){
                            genderFemale = false;
                        }else{}
                        genderFemale = true;
                    }
                    else if(isInside(msg, userAgeInputBar1)){
                        fillroundrect_(userAgeInputBar1);
                        char s[100];
                        InputBox(s, 100, "请输入用户年龄限制");
                        userAgeInput1 = true;
                        userAge1 = s;
                    }
                    else if(isInside(msg, userAgeInputBar2)){
                        fillroundrect_(userAgeInputBar2);
                        char s[100];
                        InputBox(s, 100, "请输入用户年龄限制");
                        userAgeInput2 = true;
                        userAge2 = s;
                    }
                    else if(isInside(msg, pageUpButton) && curPage != pageNum) {
                        curPage++;
                        ClearUserQueryGraph();
                    }
                    else if(isInside(msg, pageDownButton) && curPage != 0) {
                        curPage--;
                        ClearUserQueryGraph();
                    }
                    else if(isInside(msg, userResetButton)) {
                        ClearUserQueryGraph();
                        conditions.clear();
                        res.clear();
                        genderMale = false;
                        genderFemale = false;
                        userID = false;
                        userNickname = false;
                        userAgeInput1 = false;
                        userAgeInput2 = false;
                        showPage = false;
                        curPage = pageNum = 0;
                        setfillcolor(WHITE);
                        fillroundrect_(userTagInputBar);
                        fillroundrect_(userNameInputBar);
                        fillroundrect_(userAgeInputBar1);
                        fillroundrect_(userAgeInputBar2);
                    }
                    else if(isInside(msg, userSearchButton)) {
                        ClearUserQueryGraph();
                        if (userNickname) conditions.push_back("username LIKE '%" + usernickname + "%'");
                        if (genderMale) conditions.push_back("gender = 'male'");
                        if (genderFemale) conditions.push_back("gender = 'female'");
                        if (userID) conditions.push_back("userid = '" + userid + "'");
                        if (userAgeInput1 && userAgeInput2)
                            conditions.push_back("age BETWEEN " + userAge1 + " AND " + userAge2);
                        else if (userAgeInput1) conditions.push_back("age = " + userAge1);
                        else if (userAgeInput2) conditions.push_back("age = " + userAge2);

                        string where_clause = "";
                        res.clear();
                        showPage = false;
                        if (!conditions.empty()) {
                            where_clause = " WHERE " + conditions[0];
                            for (size_t i = 1; i < conditions.size(); ++i) {
                                where_clause += " AND " + conditions[i];
                            }
                        }
                        string sql_query = "SELECT userid, username, gender, age, email FROM users" + where_clause;
                        res = txn.exec(sql_query);
                        conditions.clear();
                        //多页处理
                        curPage = 0, pageNum = (float(res.size()) + 0.5) / 10;
                        if(res.size() > 10){
                            showPage = true;
                        }
                        if(showPage){
                            setfillcolor(CommonBlue);
                            fillroundrect_(pageUpButton);
                            fillroundrect_(pageDownButton);
                            OutputText(pageDownButton.posx + 15, pageUpButton.posy + 3, WHITE, 15, 0, "<=", "宋体");
                            OutputText(pageUpButton.posx + 15, pageDownButton.posy + 3, WHITE, 15, 0, "=>", "宋体");
                        }
                    }
                    break;
            }
        }
    }
}