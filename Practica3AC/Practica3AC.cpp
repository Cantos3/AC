// Practica3AC.cpp : main project file.
/**
---------------------------------------------------------------------------------------------------------------
---------------------------------------------PRÁCTICA DE AC----------------------------------------------------
---     Este main es la base del proyecto, la idea es que, dependiendo de los argumentos del programa,      ---
---     ejecute los métodos de ordenación de matrices en C, ensamblador, o ensamblador con SSE y además     ---
---     se introduzca la matriz desde teclado o desde un fichero (a implementar)                            ---
---------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------
*/
#include "stdafx.h"
#include <random>
#include <time.h>
#include <stdlib.h>


using namespace System;


//Variables globales de gestión de argumentos
bool ALGc = false, ALGassemble = false, ALGassemblysse = false, fromFile = false;
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
		vpoints[i] = (float)rand() / (float)RAND_MAX * 10;
	}
}

void
applyNormal(float* vpoints, float* vnormal, int u, int v)
{
	float x1, y1, z1, x2, y2, z2, nx=0.0, ny=0.0, nz=0.0;
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
			//vtop-left x vtop
			x1 = vpoints[top_left] - vpoints[center];
			y1 = vpoints[top_left + 1] - vpoints[center + 1];
			z1 = vpoints[top_left + 2] - vpoints[center + 2];
			x2 = vpoints[top] - vpoints[center];
			y2 = vpoints[top + 1] - vpoints[center + 1];
			z2 = vpoints[top + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vtop x vtop-right
			x1 = vpoints[top_right] - vpoints[center];
			y1 = vpoints[top_right + 1] - vpoints[center + 1];
			z1 = vpoints[top_right + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			//vtop-right x vright
			x2 = vpoints[right] - vpoints[center];
			y2 = vpoints[right + 1] - vpoints[center + 1];
			z2 = vpoints[right + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vright x vdown-right
			x1 = vpoints[down_right] - vpoints[center];
			y1 = vpoints[down_right + 1] - vpoints[center + 1];
			z1 = vpoints[down_right + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			//vdown-right x vdown
			x2 = vpoints[down] - vpoints[center];
			y2 = vpoints[down + 1] - vpoints[center + 1];
			z2 = vpoints[down + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vdown x vdown-left
			x1 = vpoints[down_left] - vpoints[center];
			y1 = vpoints[down_left + 1] - vpoints[center + 1];
			z1 = vpoints[down_left + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			//vdown-left x vleft
			x2 = vpoints[left] - vpoints[center];
			y2 = vpoints[left + 1] - vpoints[center + 1];
			z2 = vpoints[left + 2] - vpoints[center + 2];

			nx += y1 * z2 - y2 * z1;
			ny += z1 * x2 - z2 * x1;
			nz += x1 * y2 - x2 * y1;

			//vleft x vtop-left
			x1 = vpoints[top_left] - vpoints[center];
			y1 = vpoints[top_left + 1] - vpoints[center + 1];
			z1 = vpoints[top_left + 2] - vpoints[center + 2];

			nx += y2 * z1 - y1 * z2;
			ny += z2 * x1 - z1 * x2;
			nz += x2 * y1 - x1 * y2;

			vnormal[center] = nx / 8;
			vnormal[center + 1] = ny / 8;
			vnormal[center + 2] = nz / 8;

			nx = 0.0;ny = 0.0;nz = 0.0;
		}
	}
	//top-left corner: 
		//right x down-right
	x1 = vpoints[3] - vpoints[0];
	y1 = vpoints[4] - vpoints[1];
	z1 = vpoints[5] - vpoints[2];

	x2 = vpoints[v+3] - vpoints[0];
	y2 = vpoints[v+4] - vpoints[1];
	z2 = vpoints[v+5] - vpoints[2];

	nx += y1 * z2 - y2 * z1;
	ny += z1 * x2 - z2 * x1;
	nz += x1 * y2 - x2 * y1;

		//down-right x down
	x1 = vpoints[v + 3] - vpoints[0];
	y1 = vpoints[v + 4] - vpoints[1];
	z1 = vpoints[v + 5] - vpoints[2];

	nx += y2 * z1 - y1 * z2;
	ny += z2 * x1 - z1 * x2;
	nz += x2 * y1 - x1 * y2;

	//down x right

	x2 = vpoints[3] - vpoints[0];
	y2 = vpoints[4] - vpoints[1];
	z2 = vpoints[5] - vpoints[2];

	nx += y1 * z2 - y2 * z1;
	ny += z1 * x2 - z2 * x1;
	nz += x1 * y2 - x2 * y1;

	vnormal[0] = nx / 3;
	vnormal[1] = ny / 3;
	vnormal[2] = nz / 3;

	nx = 0.0;ny = 0.0;nz = 0.0;

	//down-left corner:
		//top x top-right
	x1 = vpoints[(u-2) * v] - vpoints[(u-1)* v];
	y1 = vpoints[(u-2) * v +1] - vpoints[(u-1) * v + 1];
	z1 = vpoints[(u-2) * v +2] - vpoints[(u-1) * v + 2];

	x2 = vpoints[(u - 2) * v + 3] - vpoints[(u - 1)* v];
	y2 = vpoints[(u - 2) * v + 4] - vpoints[(u - 1) * v + 1];
	z2 = vpoints[(u - 2) * v + 5] - vpoints[(u - 1) * v + 2];

	nx += y1 * z2 - y2 * z1;
	ny += z1 * x2 - z2 * x1;
	nz += x1 * y2 - x2 * y1;

		//top-right x right
	x1 = vpoints[(u - 1) * v + 3] - vpoints[(u - 1)* v];
	y1 = vpoints[(u - 1) * v + 4] - vpoints[(u - 1) * v + 1];
	z1 = vpoints[(u - 1) * v + 5] - vpoints[(u - 1) * v + 2];

	nx += y2 * z1 - y1 * z2;
	ny += z2 * x1 - z1 * x2;
	nz += x2 * y1 - x1 * y2;

		//right x top
	x2 = vpoints[(u - 2) * v] - vpoints[(u - 1)* v];
	y2 = vpoints[(u - 2) * v + 1] - vpoints[(u - 1) * v + 1];
	z2 = vpoints[(u - 2) * v + 2] - vpoints[(u - 1) * v + 2];

	nx += y1 * z2 - y2 * z1;
	ny += z1 * x2 - z2 * x1;
	nz += x1 * y2 - x2 * y1;

	vnormal[(u - 1)* v] = nx / 3;
	vnormal[(u - 1)* v + 1] = ny / 3;
	vnormal[(u - 1)* v + 2] = nz / 3;

	nx = 0.0;ny = 0.0;nz = 0.0;
	//top-right corner
	//top-down corner
	//topmost row
	//downmost row
	//leftmost column
	//rightmost column
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
	//Gestión de argumentos
	for (int i = 1; i <= argc; i++)
	{
		if (argv[i] == "-c") ALGc = true;
		if (argv[i] == "-a") ALGassemble = true;
		if (argv[i] == "-s") ALGassemblysse = true;
		if (argv[i] == "-f")
		{
			fromFile = true;
			//Gestiona fichero
		}
	}
	if (!fromFile)
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