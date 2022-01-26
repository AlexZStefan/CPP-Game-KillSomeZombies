#pragma once
#include <SDL.h>
#include <random>
#include <iostream>
#include <math.h>

const int size = 3;

class Functions
{
	
public:
	Functions() {};
	static SDL_bool collision( SDL_Rect& rect1, SDL_Rect& rect2);

	static int randomNumber(int a, int b);

	static bool circleCollision(float aX, float aY, float aR, SDL_Rect& b);

	static double distanceSquared(int x1, int y1, int x2, int y2);

	static bool myCollision(SDL_Rect& rect1, SDL_Rect& rect2);
private:
};

static int dot_product(int vector_a[], int vector_b[]) {
	int product = 0;
	for (int i = 0; i < size; i++)
		product = product + vector_a[i] * vector_b[i];
	return product;
};

static void cross_product(int vector_a[], int vector_b[], int temp[]) {
	temp[0] = vector_a[1] * vector_b[2] - vector_a[2] * vector_b[1];
	temp[1] = -(vector_a[0] * vector_b[2] - vector_a[2] * vector_b[0]);
	temp[2] = vector_a[0] * vector_b[1] - vector_a[1] * vector_b[0];
};
