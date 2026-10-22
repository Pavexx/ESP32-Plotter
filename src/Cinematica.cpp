#include "Cinematica.h"
#include "ConfigMovimiento.h"
#include <math.h>

// MODULO DE CINEMATICA
// este modulo calcula la cantidad de pasos necesarios en cada motor
// para lograr un movimiento lineal en XY

double LargoCorrea(double X, double Y, bool IZQ = true) {
	const double motorX = IZQ ? 0.0 : Distancia_Motores;
	const double motorY = 0.0;
	const double Px = X + Desfase_Gondola_X;
	const double Py = Y + Desfase_Gondola_Y;
	const double D = sqrt(pow(Px - motorX, 2) + pow(Py - motorY, 2)); //Distancia P a centro de motor
	const double l = sqrt(D * D - Radio_Polea * Radio_Polea);   //D1 Lapiz-PuntoTang
	const double ang = 1.5707963268 - (acos(Radio_Polea/D) - atan2(Py - motorY, motorX - Px)); // ang4
	const double largoTotal = l + ang * Radio_Polea;          //largo de correa Lapiz-Polea 90°
	return largoTotal;
}

static double PasosPorMM() {
    const double pulleyTravelPerRev = GT2_Dientes * GT2_PasoMM;
    return (PasosPorVuelta * MICROSTEPS) / pulleyTravelPerRev;
}

void XYaPasos(double X, double Y, int64_t& PasosIzq, int64_t& PasosDer) {
    const double Izq0 = LargoCorrea(Xinicio, Yinicio, true);
    const double Der0 = LargoCorrea(Xinicio, Yinicio, false);
    const double Izq1 = LargoCorrea(X, Y, true);
    const double Der1 = LargoCorrea(X, Y, false);
    
    PasosIzq = llround((Izq0 - Izq1) * PasosPorMM());
    PasosDer = llround((Der0 - Der1) * PasosPorMM());
}