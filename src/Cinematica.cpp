#include "Cinematica.h"
#include "ConfigMovimiento.h"
#include <math.h>

// MODULO DE CINEMATICA
// este modulo calcula la cantidad de pasos necesarios en cada motor
// para lograr un movimiento lineal en XY

float LargoCorrea(float X, float Y, bool IZQ = true) {
	const float motorX = IZQ ? 0.0f : Distancia_Motores;
	const float Px = X + Desfase_Gondola_X;
	const float Py = Y + Desfase_Gondola_Y;

	const float dx = Px - motorX;
	const float dy = Py;

	const float D_sq = dx * dx + dy * dy;
	const float D = sqrtf(D_sq); 								//Distancia P a centro de motor

	const float l = sqrtf(D * D - Radio_Polea_sq);    			//D1 Lapiz-PuntoTang
	const float ang = asinf(Radio_Polea / D) + atan2f(dy, -dx); // ang4
 
	return l + ang * Radio_Polea;          						//largo de correa Lapiz-Polea 90°
}

void XYaPasos(float X, float Y, int32_t& PasosIzq, int32_t& PasosDer) {
    const float Izq0 = LargoCorrea(Xinicio, Yinicio, true);
    const float Der0 = LargoCorrea(Xinicio, Yinicio, false);
    const float Izq1 = LargoCorrea(X, Y, true);
    const float Der1 = LargoCorrea(X, Y, false);
    
    PasosIzq = llround((Izq0 - Izq1) * PasosPorMM);
    PasosDer = llround((Der0 - Der1) * PasosPorMM);
}