#include <graphics.h>
#include <conio.h>
#include <pqxx/pqxx>
#include "GoodsQuery.h"

using namespace std;

object orderSearch = {220, 70, 350, 40};
object orderSearchInputBar = {orderSearch.posx + 100, orderSearch.posy + 5, 240, 30};
object goodsName = {orderSearch.posx + orderSearch.width + 30, orderSearch.posy, 350, 40};
object goodsNameInputBar = {goodsName.posx + 100, orderSearch.posy + 5, 240, 30};
object goodsCategory = {orderSearch.posx, orderSearch.posy + orderSearch.height + 15, 220, 40};
object goodsCategoryInputBar = {goodsCategory.posx + 100, orderSearch.posy + orderSearch.height + 20, 110, 30};
object goodsPrice = {goodsCategory.posx + goodsCategory.width + 35, goodsCategory.posy, 215, 40};
object goodsPriceInputBar1 = {goodsPrice.posx + 70, goodsCategory.posy + 5, 50, 30};
object goodsPriceInputBar2 = {goodsPriceInputBar1.posx + goodsPriceInputBar1.width + 40, goodsCategory.posy + 5, 50, 30};
object goodsSearchButton = {goodsPrice.posx + goodsPrice.width + 30, orderSearch.posy + orderSearch.height + 15, 100, 40};
object goodsResetButton = {goodsSearchButton.posx + goodsSearchButton.width + 30, goodsSearchButton.posy, 100, 40};

void ClearGoodsQueryGraph(){
    setlinecolor(WHITE);
    setfillcolor(WHITE);
    fillrectangle_({180, 215, 780, 500});
    setlinecolor(BLACK);
    rectangle_({220, 185, 140, 30});
    rectangle_({360, 185, 230, 30});
    rectangle_({590, 185, 100, 30});
    rectangle_({690, 185, 100, 30});
    rectangle_({790, 185, 160, 30});
    OutputText(220 + 10, 185 + 5, BLACK, 20, 0, "商品id", "宋体");
    OutputText(360 + 10, 185 + 5, BLACK, 20, 0, "商品名称", "宋体");
    OutputText(590 + 10, 185 + 5, BLACK, 20, 0, "库存", "宋体");
    OutputText(690 + 10, 185 + 5, BLACK, 20, 0, "价格", "宋体");
    OutputText(790 + 10, 185 + 5, BLACK, 20, 0, "商品类别", "宋体");
//    if(showPage){
//        setfillcolor(CommonBlue);
//        fillroundrect_(pageUpButton);
//        fillroundrect_(pageDownButton);
//        OutputText(pageDownButton.posx + 15, pageUpButton.posy + 3, WHITE, 15, 0, "<=", "宋体");
//        OutputText(pageUpButton.posx + 15, pageDownButton.posy + 3, WHITE, 15, 0, "=>", "宋体");
//        setfillcolor(WHITE);
//    }
}
void GoodsQueryGraph(){
    setlinecolor(CommonBlue);
    setfillcolor(CommonBlue);
    fillroundrect_(orderSearch);
    fillroundrect_(goodsName);
    fillroundrect_(goodsCategory);
    fillroundrect_(goodsPrice);
    fillroundrect_(goodsSearchButton);
    fillroundrect_(goodsResetButton);
    setfillcolor(WHITE);
    fillroundrect_(orderSearchInputBar);
    fillroundrect_(goodsNameInputBar);
    fillroundrect_(goodsPriceInputBar1);
    fillroundrect_(goodsPriceInputBar2);
    fillroundrect_(goodsCategoryInputBar);

    OutputText(orderSearch.posx + 10, orderSearch.posy + 10, WHITE, 20, 0, "订单查找", "宋体");
    OutputText(goodsName.posx + 10, orderSearch.posy + 10, WHITE, 20, 0, "商品名称", "宋体");
    OutputText(goodsCategory.posx + 10, goodsCategory.posy + 10, WHITE, 20, 0, "商品类别", "宋体");
    OutputText(goodsPrice.posx + 10, goodsPrice.posy + 10, WHITE, 20, 0, "价格", "宋体");
    OutputText(goodsPriceInputBar1.posx + goodsPriceInputBar1.width + 10, goodsCategory.posy + 10, WHITE, 20, 0, "到", "宋体");
    OutputText(goodsSearchButton.posx + 30, goodsSearchButton.posy + 10, WHITE, 20, 0, "查找", "宋体");
    OutputText(goodsResetButton.posx + 30, goodsResetButton.posy + 10, WHITE, 20, 0, "重置", "宋体");

    OutputText(400, 350, BLACK, 30, 0, "未找到符合要求的商品/订单", "宋体");
    ClearGoodsQueryGraph();
}
void GoodsQuerySecondMenu(int n){
    setlinecolor(LightBlue);
    setfillcolor(LightBlue);
    fillrectangle(165, 0, 165 + 160, 720);

    OutputText(185,60,WHITE,20,0,"用户查询", "宋体");
    OutputText(185,150,YELLOW,20,0,"添加/修改用户", "宋体");
    OutputText(185,240,WHITE,20,0,"删除用户", "宋体");
}
void GoodsQuery(){
    Menu(2);
    GoodsQueryGraph();
//    GoodsQuerySecondMenu(2);
    vector<string> conditions;
    while(true) {
        flushmessage(EM_MOUSE);
        MenuAnimation(msg.x, msg.y, 2);
        if (peekmessage(&msg, EM_MOUSE)) {
            ButtonAnimation(msg, goodsSearchButton, WHITE, CommonBlue);
            ButtonAnimation(msg, goodsResetButton, WHITE, CommonBlue);
            ButtonAnimation(msg, orderSearchInputBar, WHITE, CommonBlue, 3);
            ButtonAnimation(msg, goodsNameInputBar, WHITE, CommonBlue, 3);
            ButtonAnimation(msg, goodsPriceInputBar1, WHITE, CommonBlue, 3);
            ButtonAnimation(msg, goodsPriceInputBar2, WHITE, CommonBlue, 3);
            ButtonAnimation(msg, goodsCategoryInputBar, WHITE, CommonBlue, 3);
        }

        switch(msg.message) {
            case WM_LBUTTONDOWN:
                if (msg.x >= 0 && msg.x <= 170 && msg.y >= 25 && msg.y <= 720) {
                    choose = ChooseGraph(msg.x, msg.y);
                    if (choose != 4) {
                        flushmessage(EM_MOUSE);
                        return;
                    }
                }
        }
    }
}