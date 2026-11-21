#include "Cinematica.h"
#include "ConfigMovimiento.h"
#include <math.h>

// MODULO DE CINEMATICA
// este modulo calcula la cantidad de pasos necesarios en cada motor
// para lograr un movimiento lineal en XY

float LargoCorrea(float X, float Y, bool IZQ = true) {
	const float motorX = IZQ ? 0.0f : Distancia_Motores;
	const float Px = X + Xinicio - motorX;
	const float Py = Y + Yinicio;

	const float D_sq = Px * Px + Py * Py;
	const float D = sqrtf(D_sq); 								//Distancia P a centro de motor
	return D;

	const float l = sqrtf(D * D - Radio_Polea_sq);    			//D1 Lapiz-PuntoTang
	const float ang = asinf(Radio_Polea / D) + atan2f(Py, -Px); // ang4	
	return l + ang * Radio_Polea;          						//largo de correa Lapiz-Polea 90°
}

void XYaPasos(float X, float Y, int32_t& PasosIzq, int32_t& PasosDer) {
    const float Izq1 = LargoCorrea(X, Y, true);
    const float Der1 = LargoCorrea(X, Y, false);

	PasosIzq = (int32_t)lroundf((Izq1 - Izq0) * PasosPorMM);
	PasosDer = (int32_t)lroundf((Der1 - Der0) * PasosPorMM);
}