#ifndef USERQUERY_H
#define USERQUERY_H
#include "ustil.h"

//用户查询相关
//~InputBar为输入框 s_~为存储用string ~_为bool标志
extern bool genderMale_;
extern bool genderFemale_;
extern bool userTag_;
extern bool userName_;
extern bool userAgeInput1_;
extern bool userAgeInput2_;
extern bool showPage_;
extern int curPage;
extern int pageNum;
extern std::string s_userTag;
extern std::string s_userName;
extern std::string s_userAge1, s_userAge2;
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
