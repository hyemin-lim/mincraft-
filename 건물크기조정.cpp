
#include "pch.h"
#include <iostream>
#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")
#include <math.h>
#define M_PI       3.14159265358979323846


int find_length(int n, int m);
int shorter(int n, int m);
void gold_circle (int x, int y, int z, int rad);
void glowstone_circle(int x, int y, int z, int rad);
void glass_circle(int x, int y, int z, int rad);
void lava(int x, int y, int z);
void water_circle(int x, int y, int z, int radius);
void dirt_circle(int x, int y, int z, int radius);
void plant_circle(int x, int y, int z, int radius);

int main()
{
	int sx, sy, sz, ex, ey, ez;
	do{
		printf("좌표 1을 입력하시오.\n");
		scanf_s("%d %d %d", &sx, &sy, &sz);        //좌표 설정
		printf("좌표 2를 입력하시오.\n");
		scanf_s("%d %d %d", &ex, &ey, &ez);
	} while (sx == ex || sy == ey || sz == ez);

	int cx = (sx + ex)/2;
	int cy = (sy + ey)/2;         //공간의 중간점 설정 : center x, y, z
	int cz = (sz + ez)/2;

	int dx = find_length(cx, sx);
	int dy = find_length(cy, sy);         //공간의 크기(1/2)
	int dz = find_length(cz, sz);

	int length = shorter(dx, dz);         //x방향과 z방향의 길이 중 더 작은 것

	for (int i = 0; i <= length; i++) {
		glowstone_circle(cx, cy - dy, cz, i);  //바닥
		glowstone_circle(cx, cy, cz, i);  //천장
		water_circle(cx, cy - dy + 1, cz, i - 1);  //물
	}

	lava(cx, cy, cz);  //용암

	for (int j = dy; j >= 0; j--) {
		gold_circle(cx, cy - j, cz, length);  //벽 (공간의 바닥부터 중간높이까지 원형으로 세운다.)
	}

	glass_circle(cx, cy - (dy / 2), cz, length);
	glass_circle(cx, cy - (dy / 2) + 1, cz, length);  //창문
	glass_circle(cx, cy - (dy / 2) - 1, cz, length);

	glass_circle(cx, cy - dy + 1, cz, length - 2);  //바닥 조명과 물을 분리하는 유리벽

	dirt_circle(cx, cy - dy + 1, cz, length / 2);   //토양

	plant_circle(cx, cy - dy + 2, cz, length / 2);   //나무

	glowstone_circle(cx, cy - dy + 1, cz, length - 1);  //바닥 조명
	
	




	
	

}

int find_length (int n, int m) {
	if (n < m) {
		return m - n;
	}                                                    //길이가 항상 양수가 되도록 한다.
	else if (n > m)
		return n - m;
}

int shorter(int n, int m) {
	if (n < m) {
		return n;
	}                                                              //두 값 중 더 작은 값을 반환한다.
	else if (m < n) {
		return m;
	}
}

void gold_circle(int x, int y, int z, int radius) {	        //금_원

	BlockID gold = createBlock(BLOCK_GOLD);
													
	double radian = M_PI / 180.;  //1도씩 차이를 둔다.

	for (int i = 0; i < 360; i++) {
		double x_ = radius * cos(radian * i);  //원의 x좌표
		double z_ = radius * sin(radian * i);  //원의 z좌표
		locateBlock(gold, x + x_, y, z + z_);
	}
}

void glowstone_circle(int x, int y, int z, int radius) {                  //발광석_원

	BlockID glowstone = createBlock(BLOCK_GLOWSTONE);

	double radian = M_PI / 180.;

	for (int i = 0; i < 360; i++) {
		double x_ = radius * cos(radian * i);
		double z_ = radius * sin(radian * i);
		locateBlock(glowstone, x + x_, y, z + z_);
	}
}

void glass_circle(int x, int y, int z, int radius) {                   //유리_원

	BlockID glass = createBlock(BLOCK_GLASS);

	double radian = M_PI / 180.;

	for (int i = 0; i < 360; i++) {
		double x_ = radius * cos(radian * i);
		double z_ = radius * sin(radian * i);
		locateBlock(glass, x + x_, y, z + z_);
	}
}

void lava (int x, int y, int z) {                             //용암_블록
	BlockID lava = createLava(true);
	locateWater(lava, x, y, z);
}

void water_circle(int x, int y, int z, int radius) {                 //물_원
	BlockID water = createWater(true);
	

	double radian = M_PI / 180.;

	for (int i = 0; i < 360; i++) {
		double x_ = radius * cos(radian * i);
		double z_ = radius * sin(radian * i);
		locateWater(water, x + x_, y, z + z_);
	}
}

void dirt_circle(int x, int y, int z, int radius) {                          //토양_원
	BlockID dirt = createBlock(BLOCK_DIRT);

	double radian = M_PI / 180;

	for (int i = 0; i < 360; i++) {
		double x_ = radius * cos(radian * i);
		double z_ = radius * sin(radian * i);
		locateBlock(dirt, x + x_, y, z + z_);
	}
}

void plant_circle(int x, int y, int z, int radius) {                             //나무_원

	double radian = M_PI / 180;

	for (int i = 0; i < 360; i++) {
		double x_ = radius * cos(radian * i);
		double z_ = radius * sin(radian * i);
		BlockID plant = createPlant(PlantType(19));
		locateBlock(plant, x + x_, y, z + z_);
	}
}