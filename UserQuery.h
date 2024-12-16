#ifndef USERQUERY_H
#define USERQUERY_H
#include "ustil.h"

//用户查询相关
//~InputBar为输入框 纯小写为存储用string 驼峰命名为bool标志
extern bool genderMale;
extern bool genderFemale;
extern bool userID;
extern bool userNickname;
extern bool userAgeInput1;
extern bool userAgeInput2;
extern bool showPage;
extern int curPage;
extern int pageNum;
extern std::string userid;
extern std::string usernickname;
extern std::string userAge1, userAge2;
extern object userTag;
extern object userTagInputBar;
extern object userName;
extern object userNameInputBar;
extern object userGenderWindow;
extern object userGenderMale;
extern object userGenderFemale;
extern object userAge;
extern object userAgeInputBar1;
extern object userAgeInputBar2;
extern object userSearchButton;
extern object userResetButton;
extern object pageUpButton;
extern object pageDownButton;

void ClearUserQueryGraph();
void UserQueryGraph();
void UserQuerySecondMenu(int n);
void UserQuery();
#endif
