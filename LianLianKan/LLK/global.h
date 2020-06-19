#pragma once

//顶点结构体
typedef struct tagVertex
{
	int row;//行
	int col;//列
	int info;//信息
}Vertex;

#define BLANK -1//元素为空
#define MAX_WID 12//地图每行每列可容纳元素数
#define MAX_VERTEX_NUM 144//顶点个数
#define MAX_PIC_NUM 12//图片花色
#define REPEAT_NUM 12//每种花色图片重复个数
#define PIC_WIDTH 40//游戏图片宽度
#define PIC_HEIGHT 40//游戏图片高度
#define MAP_TOP 50//地图左上角纵坐标
#define MAP_LEFT 130//地图左上角横坐标
#define PLAY_TIMER_ID 1//计时器ID
#define GAME_LOSE -1//失败
#define GAME_SUCCESS 0//胜利
#define GAME_PLAY 1//游戏正在进行