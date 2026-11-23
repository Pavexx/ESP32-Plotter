#include "Cinematica.h"
#include "ConfigMovimiento.h"

float UltimaX, UltimaY = 0;
float X0, Y0 = 0;
float dx, dy = 0;
int16_t Segmentos = 0;

// MODULO DE CINEMATICA
// este modulo calcula la cantidad de pasos necesarios en cada motor
// para lograr un movimiento lineal en XY

// Calcula el largo de cada correa en MM a partir de coordenadas relativas
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

// Cantidad de pasos relativos desde home hasta coordenadas X/Y relativas al centro
void XYaPasos(float X, float Y, int32_t& PasosIzq, int32_t& PasosDer) {
    const float Izq1 = LargoCorrea(X, Y, true);
    const float Der1 = LargoCorrea(X, Y, false);

	PasosIzq = (int32_t)lroundf((Izq1 - Izq0) * PasosPorMM);
	PasosDer = (int32_t)lroundf((Der1 - Der0) * PasosPorMM);

	UltimaX = X;
	UltimaY = Y;
}

// Calcula la cantidad de segmentos entre la ultima posicion calculada y la actual,
// guarda los valores necesarios para calcular cada segmento
int16_t CantSegmentos(float X, float Y) {
	X0 = UltimaX;
	Y0 = UltimaY;
	dx = X - X0;
	dy = Y - Y0;
	float Distancia = sqrtf(dx * dx + dy * dy);
	Segmentos = ceilf(Distancia / SegmentoMaximo);
	return Segmentos;
}

// Calcula el siguiente paso a ejecutar a partir de los valores registrados por
// CantSegmentos(), cumple el rol de XYaPasos() para segmentos. Podría tener una
// implementación más limpia que no dependa tanto de CantSegmentos(), pero quiero
// simplificar del lado de app.cpp
void PasosIntermedio(int16_t i, int32_t& PasosIzq, int32_t& PasosDer) {

	float incremento = (float)i / (float)Segmentos;

    float Xintermedia = X0 + incremento * dx;
    float Yintermedia = Y0 + incremento * dy;
	Serial.print("- paso intermedio a X:");
    Serial.print(Xintermedia);
    Serial.print(" | Y:");
    Serial.println(Yintermedia);
	XYaPasos(Xintermedia, Yintermedia, PasosIzq, PasosDer);
}
