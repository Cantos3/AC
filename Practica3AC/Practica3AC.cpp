// Practica3AC.cpp : main project file.

#include "stdafx.h"
#include <random>
#include <time.h>
#include <stdlib.h>


using namespace System;

long double
tiempo(void) {
	//TODO: Implementar
	return 0.0;
}
void 
gestionaArgumentos()
{
	//TODO: Implementar
};

void 
initializeRandom(float*  vpoints, int dim)
{
	srand(time(NULL));
	for (int i = 0; i < dim; i++)
	{
		vpoints[i] = (float)rand() / (float)RAND_MAX;
	}
}

void
applyNormal(float* vpoints, float* vnormal, int u, int v)
{
	for (int i = 1; i+1 < u; i++) //Iterates trough 2nd to next-to-last row
	{
		for (int j = 3; j + 3 < v; j = j + 3) //Iterates throw colums from 2nd to next-to-last
		{
			int top_left = (i - 1) * v + j - 3;
			int top = top_left + 3;
			int top_right = top + 3;
			int left = top_left + v;
			int right = top_right + v;
			int down_left = left + v;
			int down = top + 2 * v;
			int down_right = right + v;
			int center = i * v + j;

			float x1, y1, z1, x2, y2, z2, nx, ny, nz = 0.0;
			//vtop-left vs vtop
			x1 = vpoints[top_left] - vpoints[center];
			y1 = vpoints[top_left + 1] - vpoints[center + 1];
			z1 = vpoints[top_left + 2] - vpoints[center + 2];
			x2 = vpoints[top] - vpoints[center];
			y2 = vpoints[top + 1] - vpoints[center + 1];
			z2 = vpoints[top + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vtop vs vtop-right
			x1 = vpoints[top_right] - vpoints[center];
			y1 = vpoints[top_right + 1] - vpoints[center + 1];
			z1 = vpoints[top_right + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			//vtop-right vs vright
			x2 = vpoints[right] - vpoints[center];
			y2 = vpoints[right + 1] - vpoints[center + 1];
			z2 = vpoints[right + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vright vs vdown-right
			x1 = vpoints[down_right] - vpoints[center];
			y1 = vpoints[down_right + 1] - vpoints[center + 1];
			z1 = vpoints[down_right + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			//vdown-right vs vdown
			x2 = vpoints[down] - vpoints[center];
			y2 = vpoints[down + 1] - vpoints[center + 1];
			z2 = vpoints[down + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vdown vs vdown-left
			x1 = vpoints[down_left] - vpoints[center];
			y1 = vpoints[down_left + 1] - vpoints[center + 1];
			z1 = vpoints[down_left + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			//vdown-left vs vleft
			x2 = vpoints[left] - vpoints[center];
			y2 = vpoints[left + 1] - vpoints[center + 1];
			z2 = vpoints[left + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vleft vs vtop-left
			x1 = vpoints[top_left] - vpoints[center];
			y1 = vpoints[top_left + 1] - vpoints[center + 1];
			z1 = vpoints[top_left + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			vnormal[center] = nx / 8;
			vnormal[center + 1] = ny / 8;
			vnormal[center + 2] = nz / 8;
		}
	}
}
void 
printMalla(float * vpoints, int u, int v)
{
	for (int i = 0; i < u; i++)
	{
		for (int j = 0; j < v ; j = j + 3)
		{

			Console::Write( vpoints[i*v + j] + "x ");
			Console::Write( vpoints[i*v + j + 1] + "y ");
			Console::Write( vpoints[i*v + j + 2] + "z ,");
		}
		Console::Write("\n");
	}
}

int
main(int argc, char* argv[])
{
	int u, v;
	if (argc == 1)
	{
		Console::WriteLine("Introduzca la dimension x de la matriz");
		v = 3 * int::Parse(Console::ReadLine());
		Console::WriteLine("Introduzca la dimension y de la matriz");
		u = int::Parse(Console::ReadLine());
	}
	float * vpoints = new float[u * v];
	initializeRandom(vpoints,u*v);
	Console::WriteLine("MALLA DE PUNTOS CON VALOR ALEATORIO");
	printMalla(vpoints, u, v);

	float* vnormal = new float[u * v];
	for (int i = 0; i < u * v; i++)
	{
		vnormal[i] = 0.0;
	}
	applyNormal(vpoints, vnormal, u, v);
	Console::WriteLine("MALLA DE NORMALES A ESOS PUNTOS");
	printMalla(vnormal, u, v);
	Console::Read();
	return 0;
}