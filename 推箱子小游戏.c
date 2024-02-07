/*
注意事项:
1.不要去动后面caozuo函数的所有代码，最好只去理解就行了。另外不要试图去修改数据触发bug，经测试本游戏并无任何bug，如果有bug属于自己的问题。
2.本游戏架构为这样的:

1.main函数，主要开始分关卡
2.guanqia函数，输入关卡后将会显示游戏界面(由于技术限制没法清屏)，这时会根据用户输入的数字判断指令跳转到caozuo函数。
3.caozuo函数由本人手打的算法，目的是操作人物，之前在显示屏幕前已经获取了玩家坐标来判断移动。
4.返回guanqia函数重复...

3.独立关卡添加的地方我会指出，请认真观察。
4.地图采用的编辑方式是数字代写，便于编写，但不易理解。
5.这里解释下编码意思:

0.空
1.墙
2.换行
3.墙并且换行
4.箱子
5.人物
6.目标
7.目标箱子
8.目标人物

*/
#define ditus 7//地图数量
#define dituskf 3//已开发教程模式的关卡
#define sj 9000 //时间
#include <stdio.h>

int h,l,gk,ydbs,boo,w,fx;//不要动

struct dt{
int ditu[15][15];
}d[ditus]={{
{{0,0,0,1,1,1,0,2},{0,0,0,1,6,1,0,2},{1,1,1,1,4,1,0,2},{1,6,0,4,5,1,1,3},{1,1,1,4,0,4,6,3},{0,0,1,0,1,1,1,3},{0,0,1,6,1,0,0,2},{0,0,1,1,1,0,0,2}}
},{
{{1,1,1,1,1,0,0,0,2},{1,5,0,0,1,0,0,0,2},{1,0,4,4,1,0,1,1,3},{1,0,4,0,1,0,1,6,3},{1,1,1,0,1,1,1,6,3},{0,1,1,0,0,0,0,6,3},{0,1,0,0,0,1,0,0,3},{0,1,0,0,0,1,1,1,3},{0,1,1,1,1,1,0,0,2}}
},{
{{0,1,1,1,1,1,1,1,0,2},{0,1,0,0,0,0,0,1,1,3},{1,1,4,1,1,1,0,0,0,3},{1,0,5,0,4,0,0,4,0,3},{1,0,6,6,1,0,4,0,1,3},{1,1,6,6,1,0,0,0,1,2},{0,1,1,1,1,1,1,1,1,0}}
},{
{{0,1,1,1,1,2},{1,1,0,0,1,2},{1,5,4,0,1,2},{1,1,4,0,1,3},{1,1,0,4,0,3},{1,6,4,0,0,3},{1,6,6,7,6,3},{1,1,1,1,1,3}}
},{
{{0,1,1,1,1,0,0,2},{0,1,5,0,1,1,1,2},{0,1,0,4,0,0,1,2},{1,1,1,0,1,0,1,3},{1,6,1,0,1,0,0,3},{1,6,0,4,0,1,0,3},{1,6,0,0,0,4,0,3},{1,1,1,1,1,1,1,1}}
},{
{{0,0,0,1,1,1,1,1,1,1,0,0,2},{1,1,1,1,0,0,0,0,0,1,0,0,2},{1,0,0,0,6,1,1,1,0,1,0,0,2},{1,0,1,0,1,0,0,0,0,1,1,0,2},{1,0,1,0,4,0,4,1,6,0,1,0,2},{1,0,1,0,0,7,0,0,1,0,1,0,2},{1,0,6,1,4,0,4,0,1,0,1,0,2},{1,1,0,0,0,0,1,0,1,0,1,1,3},{0,1,0,1,1,1,6,0,0,0,0,5,3},{0,1,0,0,0,0,0,1,1,0,0,0,3},{0,1,1,1,1,1,1,1,1,1,1,1,1}}
},{
{{0,0,0,1,1,1,1,1,1,3},{0,0,1,1,0,0,1,0,5,3},{0,0,1,0,0,0,1,0,0,3},{0,0,1,4,0,4,0,4,0,3},{0,0,1,0,4,1,1,0,0,3},{1,1,1,0,4,0,1,0,1,3},{1,6,6,6,6,6,0,0,1,2},{1,1,1,1,1,1,1,1,1,2}}
}
};
//地图数据！谨慎修改！

struct x{
int sh;//地图行
int sl;//地图列
}xx[ditus]={
{8,8},
{9,9},
{7,10},
{8,6},
{8,8},
{11,13},
{8,10}
};
//关于每张地图的信息，属于地图数据！

struct zidong{
int zd[150];
}z[ditus]={{1,2,3,3,4,2,2,1,4,4},
{4,4,2,2,2,2,4,2,2,3,3,1,4,2,4,1,3,1,4,4,4,2,4,1,1,2,3,3,3,3,1,1,1,1,3,3,2,4,1,4,2,2,2,2,4,2,2,3,3,1,4,2,4,1,3,1,4,4,4,2,4,1,3,3,3,3,1,1,1,3,3,2,4,1,4,2,2,2,4,2,2,3,3,1,4,2,4,1,3,1,4,4,4},
{4,4,4,2,2,4,4,1,1,3,1,1,3,3,3,3,2,2,3,2,4,1,4,2,1,3,1,1,4,4,4,4,2,2,3,3,3,4,4,4,1,1,3,3,3,3,2,2,3,2,4,1,4,3,1,1,4,4,4,4,2,2,4,4,1,3,2,3,3,3,3,3,1,1,4,4,4,4,2,4,2,3,3,3,3,4,4,4,1,1,3,3,3,3,2,2,2,3,1,4,4,4,4,4,4,2,3,2,3,1,4,1,3,3,3,4,4,4,1,1,3,3,3,3,2,2}
};
//自动移动方向数据！谨慎操作

enum xs {kong,qiang,huanhang,qianghuanhang,xiangzi,renwu,mubiao,mubiaoxiangzi,mubiaorenwu}zhi;
//这个不要动了

int main(){
printf("请输入关卡:\n");
scanf("%d",&gk);
if(gk<1||gk>ditus){
printf("错误！\n");main();
}
guanqia(gk-1);
//关卡
}

guanqia(gq){

switch(gq){
case 0:{
if(d[gq].ditu[1][4]==7&&d[gq].ditu[3][1]==7&&d[gq].ditu[4][6]==7&&d[gq].ditu[6][3]==7){printf("恭喜你完成了第一关！\n");boo=0;w=0;main();break;}
}
case 1:{
if(d[gq].ditu[3][7]==7&&d[gq].ditu[4][7]==7&&d[gq].ditu[5][7]==7){
printf("恭喜你完成第二关！\n");boo=0;w=0;main();break;}
}
case 2:{
if(d[gq].ditu[4][2]==7&&d[gq].ditu[4][3]==7&&d[gq].ditu[5][2]==7&&d[gq].ditu[5][3]==7){
printf("恭喜你完成第三关！\n");boo=0;w=0;main();break;}
}
case 3:{
if(d[gq].ditu[5][1]==7&&d[gq].ditu[6][1]==7&&d[gq].ditu[6][2]==7&&d[gq].ditu[6][3]==7&&d[gq].ditu[6][4]==7){
printf("恭喜你完成第四关！\n");boo=0;w=0;main();break;}
}
case 4:{
if(d[gq].ditu[4][1]==7&&d[gq].ditu[5][1]==7&&d[gq].ditu[6][1]==7){
printf("恭喜你完成第五关！\n");boo=0;w=0;main();break;}
}
case 5:{
if(d[gq].ditu[2][4]==7&&d[gq].ditu[4][8]==7&&d[gq].ditu[5][5]==7&&d[gq].ditu[6][2]==7&&d[gq].ditu[8][6]==7){
printf("恭喜你完成第六关！\n");boo=0;w=0;main();break;}
}
case 6:{
if(d[gq].ditu[6][1]==7&&d[gq].ditu[6][2]==7&&d[gq].ditu[6][3]==7&&d[gq].ditu[6][4]==7&&d[gq].ditu[6][5]==7){
printf("恭喜你完成第七关！\n");boo=0;w=0;main();break;}
}
//新关卡验证，请填写。
}

printf("\n↑-1 ↓-2 ←-3 →-4 观看完成教程-5 退出-6\n");
printf("移动步数:%d\n",ydbs);

for(int j=0;j<xx[gq].sh;j++){//几行
for(int i=0;i<xx[gq].sl;i++){//列
zhi=d[gq].ditu[j][i];
switch(zhi){
case kong:{printf("    ");break;}
case qiang:{printf("▓");break;}
case huanhang:{printf("\n");break;}
case qianghuanhang:{printf("▓\n");break;}
case xiangzi:{printf("回");break;}
case renwu:{printf("♚");h=j;l=i;break;}
case mubiao:{printf("⊕");break;}
case mubiaoxiangzi:{printf("■");break;}
case mubiaorenwu:{printf("♛");h=j;l=i;break;}
}
}
}

if(boo==0){
scanf("%d",&fx);
if(fx<1||fx>6){printf("错误\n");guanqia(gq);}
}
else{fx=z[gq].zd[w];w++;delay();}
caozuo(gq);
}

//不要往下翻！！！

caozuo(gq){
switch(fx){

case 1:{
if(d[gq].ditu[h-1][l]==7){
//当前↑为目标箱子
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h-2][l]==6){
//当前是目标人物且↑x2是目标
d[gq].ditu[h-2][l]=7;d[gq].ditu[h-1][l]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h-2][l]==0){
//当前是目标人物且↑x2是空
d[gq].ditu[h-2][l]=4;d[gq].ditu[h-1][l]=8;d[gq].ditu[h][l]=6;break;
}

if(d[gq].ditu[h][l]==5&&d[gq].ditu[h-2][l]==6){
//当前是人物且↑x2是目标
d[gq].ditu[h-2][l]=7;d[gq].ditu[h-1][l]=8;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h][l]==5&&d[gq].ditu[h-2][l]==0){
//当前是人物且↑x2是空
d[gq].ditu[h-2][l]=4;d[gq].ditu[h-1][l]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h-1][l]==6){
//当前↑为目标
if(d[gq].ditu[h][l]==8){
//踩中目标
d[gq].ditu[h-1][l]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//普通人物
d[gq].ditu[h-1][l]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h-1][l]==4){
//当前↑是箱子
if(d[gq].ditu[h-2][l]==0){
//↑x2是空
d[gq].ditu[h-2][l]=4;d[gq].ditu[h-1][l]=5;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h-2][l]==6){
//↑x2是目标
d[gq].ditu[h-2][l]=7;d[gq].ditu[h-1][l]=5;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h-1][l]==0){
//当前↑是空
if(d[gq].ditu[h][l]==8){
//当前是目标人物
d[gq].ditu[h-1][l]=5;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//当前是普通人物
d[gq].ditu[h-1][l]=5;d[gq].ditu[h][l]=0;break;
}
}

else{ydbs--;printf("错误\n");break;}
}

case 2:{

if(d[gq].ditu[h+1][l]==7){
//当前↓为目标箱子
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h+2][l]==6){
//当前是目标人物且↓x2是目标
d[gq].ditu[h+2][l]=7;d[gq].ditu[h+1][l]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h+2][l]==0){
//当前是目标人物且↓x2是空
d[gq].ditu[h+2][l]=4;d[gq].ditu[h+1][l]=8;d[gq].ditu[h][l]=6;break;
}

if(d[gq].ditu[h][l]==5&&d[gq].ditu[h+2][l]==6){
//当前是人物且↓x2是目标
d[gq].ditu[h+2][l]=7;d[gq].ditu[h+1][l]=8;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h][l]==5&&d[gq].ditu[h+2][l]==0){
//当前是人物且↓x2是空
d[gq].ditu[h+2][l]=4;d[gq].ditu[h+1][l]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h+1][l]==6){
//当前↓为目标
if(d[gq].ditu[h][l]==8){
//踩中目标
d[gq].ditu[h+1][l]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//普通人物
d[gq].ditu[h+1][l]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h+1][l]==4){
//当前↓是箱子
if(d[gq].ditu[h+2][l]==0){
//↓x2是空
d[gq].ditu[h+2][l]=4;d[gq].ditu[h+1][l]=5;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h+2][l]==6){
//↓x2是目标
d[gq].ditu[h+2][l]=7;d[gq].ditu[h+1][l]=5;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h+1][l]==0){
//当前↓是空
if(d[gq].ditu[h][l]==8){
//当前是目标人物
d[gq].ditu[h+1][l]=5;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//当前是普通人物
d[gq].ditu[h+1][l]=5;d[gq].ditu[h][l]=0;break;
}
}

else{ydbs--;printf("错误\n");break;}
}

case 3:{
if(d[gq].ditu[h][l-1]==7){
//当前←为目标箱子
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h][l-2]==6){
//当前是目标人物且←x2是目标
d[gq].ditu[h][l-2]=7;d[gq].ditu[h][l-1]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h][l-2]==0){
//当前是目标人物且←x2是空
d[gq].ditu[h][l-2]=4;d[gq].ditu[h][l-1]=8;d[gq].ditu[h][l]=6;break;
}

if(d[gq].ditu[h][l]==5&&d[gq].ditu[h][l-2]==6){
//当前是人物且←x2是目标
d[gq].ditu[h][l-2]=7;d[gq].ditu[h][l-1]=8;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h][l]==5&&d[gq].ditu[h][l-2]==0){
//当前是人物且←x2是空
d[gq].ditu[h][l-2]=4;d[gq].ditu[h][l-1]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h][l-1]==6){
//当前←为目标
if(d[gq].ditu[h][l]==8){
//踩中目标
d[gq].ditu[h][l-1]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//普通人物
d[gq].ditu[h][l-1]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h][l-1]==4){
//当前←是箱子
if(d[gq].ditu[h][l-2]==0){
//←x2是空
d[gq].ditu[h][l-2]=4;d[gq].ditu[h][l-1]=5;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h][l-2]==6){
//←x2是目标
d[gq].ditu[h][l-2]=7;d[gq].ditu[h][l-1]=5;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h][l-1]==0){
//当前←是空
if(d[gq].ditu[h][l]==8){
//当前是目标人物
d[gq].ditu[h][l-1]=5;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//当前是普通人物
d[gq].ditu[h][l-1]=5;d[gq].ditu[h][l]=0;break;
}
}

else{ydbs--;printf("错误\n");break;}
}

case 4:{

if(d[gq].ditu[h][l+1]==7){
//当前↓为目标箱子
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h][l+2]==6){
//当前是目标人物且↓x2是目标
d[gq].ditu[h][l+2]=7;d[gq].ditu[h][l+1]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==8&&d[gq].ditu[h][l+2]==0){
//当前是目标人物且↓x2是空
d[gq].ditu[h][l+2]=4;d[gq].ditu[h][l+1]=8;d[gq].ditu[h][l]=6;break;
}

if(d[gq].ditu[h][l]==5&&d[gq].ditu[h][l+2]==6){
//当前是人物且↓x2是目标
d[gq].ditu[h][l+2]=7;d[gq].ditu[h][l+1]=8;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h][l]==5&&d[gq].ditu[h][l+2]==0){
//当前是人物且↓x2是空
d[gq].ditu[h][l+2]=4;d[gq].ditu[h][l+1]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h][l+1]==6){
//当前↓为目标
if(d[gq].ditu[h][l]==8){
//踩中目标
d[gq].ditu[h][l+1]=8;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//普通人物
d[gq].ditu[h][l+1]=8;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h][l+1]==4){
//当前↓是箱子
if(d[gq].ditu[h][l+2]==0){
//↓x2是空
d[gq].ditu[h][l+2]=4;d[gq].ditu[h][l+1]=5;d[gq].ditu[h][l]=0;break;
}
if(d[gq].ditu[h][l+2]==6){
//↓x2是目标
d[gq].ditu[h][l+2]=7;d[gq].ditu[h][l+1]=5;d[gq].ditu[h][l]=0;break;
}
}

if(d[gq].ditu[h][l+1]==0){
//当前↓是空
if(d[gq].ditu[h][l]==8){
//当前是目标人物
d[gq].ditu[h][l+1]=5;d[gq].ditu[h][l]=6;break;
}
if(d[gq].ditu[h][l]==5){
//当前是普通人物
d[gq].ditu[h][l+1]=5;d[gq].ditu[h][l]=0;break;
}
}

else{ydbs--;printf("错误\n");break;}
}
case 5:{
if(gq+1>dituskf){
printf("对不起，除了");
for(int i=0;i<dituskf;i++){
printf("%d.",i+1);
}
printf("关卡外其他未开放教程！\n");guanqia(gq);
}
if(ydbs!=0){
printf("对不起，请您重新开始才能进行教程！\n");guanqia(gq);
}
printf("\n正在切换，每1秒执行一次\n");
delay();boo=1;ydbs=0;guanqia(gq);break;}
case 6:{
boo=0;w=0;main();break;
}
}
ydbs++;
guanqia(gq);
}

delay()
{
 int i, j, n = sj;
 for (i = 0; i < n; i ++)
  for (j = 0; j < n; j ++)
  {
  }
}