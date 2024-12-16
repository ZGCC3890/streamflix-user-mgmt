#ifndef GOODSQUERY_H
#define GOODSQUERY_H
#include "ustil.h"

//用户查询相关
//~InputBar为输入框 s_~为存储用string ~_为bool标志
extern bool orderSearch_;
extern bool goodsName_;
extern std::string s_orderSearch;
extern std::string s_goodsName;
extern object orderSearch;
extern object orderSearchInputBar;
extern object goodsName;
extern object goodsNameInputBar;
extern object goodsCategory;
extern object goodsPrice;
extern object goodsPriceInputBar1;
extern object goodsPriceInputBar2;
extern object goodsCategoryInputBar;
extern object goodsSearchButton;
extern object goodsResetButton;

//重置界面
void ClearGoodsQueryGraph();
//基础控件绘制
void GoodsQueryGraph();
//商品/订单查询二级菜单
void GoodsQuerySecondMenu(int n);
//商品/订单查询功能
void GoodsQuery();
#endif