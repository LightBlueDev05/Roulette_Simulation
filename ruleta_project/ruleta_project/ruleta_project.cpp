#include <iostream>
#include <conio.h>
#include <math.h>
#include <windows.h>
using namespace std;

int main() {
	int numero_final = 0, conta_0, conta_negro, conta_rojo, contenedor = 10, acumulador, apuesta_w = 0, apuesta_l = 0, numero_apostar = 0;
	int n, contenedor_apuestas = 0, apuesta_hecha = 0, contador_apuestas = 1;
	double numero_a, numero_b, valor_apuesta, valor_apuesta_max=0, max_gasto=0;
	double beneficio, beneficio_total=0, valor_por_apuesta;
	int presupuesto;

	int apuesta(int repeticion, int color);
	
	cout << "Inserte cuanto dinero usara por apuesta: S/."; cin >> valor_por_apuesta;//Cantidad de dinero en cada apuesta
	cout << "Inserte su presupuesto: S/."; cin >> presupuesto;//Tope de dinero
	cout << "Inserte numero de simulaciones: "; cin >> n;//Nro Simulaciones
	cout << "\n";

	/*
	Cero=0
	Negro=1
	Rojo=2
	*/

	//Inicializacion de contadores
	conta_0 = 0;
	conta_negro = 0;
	conta_rojo = 0;
	acumulador = 0;

	/*
	peso 0 = 0.0270;
	peso negro = 0.4865;
	peso rojo = 0.4865;
	*/

	//Array de acumuladas para los pesos porcentuales
	double acumuladas[] = { 0.0270,0.5135,1 };

	//Bucle for para la simulacion
	for (int i = 1; i <= n; i++) {
		// * * Contenedor apuestas
		contenedor_apuestas = apuesta_hecha;

		//Apuesta
		apuesta_hecha = apuesta(acumulador, numero_apostar); //color apostado
		if (apuesta_hecha != 0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			cout << "APUESTA: " << apuesta_hecha << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else {
			cout << "APUESTA: " << apuesta_hecha << endl;
		}
		

		// * * Cantidad de apuestas iguales seguidas
		if (apuesta_hecha != 0 && apuesta_hecha == contenedor_apuestas) {
			contador_apuestas = contador_apuestas + 1;
		}
		else if (apuesta_hecha!=0){
			contador_apuestas = 1;
		}
		else {
			contador_apuestas = 0;
		};
		cout << "Apuestas seguidas: " << contador_apuestas << endl;

		//APUESTA EN SOLES
		if (apuesta_hecha != 0) {
			int exponencial = pow(2,contador_apuestas-1);
			valor_apuesta = valor_por_apuesta * exponencial;
		}
		else {
			valor_apuesta = 0;
		};
		cout << "VALOR APUESTA: S/." << valor_apuesta << endl;

		//MAXIMO GASTO
		if (apuesta_hecha != 0 && apuesta_hecha == contenedor_apuestas) {
			valor_apuesta_max = valor_apuesta_max + valor_apuesta;
		}
		else if (apuesta_hecha != 0) {
			valor_apuesta_max = valor_por_apuesta;
		}
		else {
			valor_apuesta_max = 0;
		};

		if (valor_apuesta_max > max_gasto) {
			max_gasto = valor_apuesta_max;
		};
		

		//Numero random del 0 al 1, en decimales
		numero_a = rand() % 1001;
		numero_b = numero_a / 1000;

		//Decodificacion del numero obtenido en 0, rojo o negro
		if (numero_b <= acumuladas[0]) {
			numero_final = 0;
			conta_0 = conta_0 + 1;
		}
		else if (numero_b <= acumuladas[1]) {
			numero_final = 1;
			conta_negro = conta_negro + 1;
		}
		else if (numero_b <= acumuladas[2]) {
			numero_final = 2;
			conta_rojo = conta_rojo + 1;
		};

		//Convertidor a numero contrario
		if (numero_final == 1) {
			numero_apostar = 2;
		}
		else if (numero_final == 2) {
			numero_apostar = 1;
		}
		else {
			numero_apostar = numero_apostar;
		};

		//Contador de repeticion continua del mismo color
		if (numero_final == contenedor) {
			acumulador = acumulador + 1;
		}
		else if (numero_final==0) {
			acumulador = acumulador+1;
		}
		else {
			acumulador = 1;
		};

		//Contenedor numero anterior
		if(numero_final!=0){
			contenedor = numero_final;
		}
		

		//Corroboracion de apuesta
		if (apuesta_hecha!=0 && apuesta_hecha == numero_final) {
			apuesta_w = apuesta_w + 1;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			cout<< "Apuesta ganada" << endl;
			beneficio = valor_apuesta;
			cout << "Beneficio parcial: S/."<< beneficio << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else if (apuesta_hecha!=0 && apuesta_hecha!=numero_final) {
			apuesta_l = apuesta_l + 1;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			cout << "Apuesta perdida" << endl;
			beneficio = (-1) * valor_apuesta;
			cout << "Beneficio parcial: S/." << beneficio << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
			cout << "NO HAY APUESTA" << endl;
			beneficio = 0;
			cout << "Beneficio parcial: S/." << beneficio << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		beneficio_total = beneficio_total + beneficio;


		//Corroboracion de Datos
		if (numero_final != 0 && apuesta_hecha!=0) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
			cout << "COLOR DE LA RULETA: " << numero_final << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		else {
			cout << "COLOR DE LA RULETA: " << numero_final << endl;
		}
		
		cout<< "Colores seguidos: " << acumulador << endl;
		cout<< "------------------------------------" << endl;
	};
	//Corroboracion de contadores
	cout << "0: " << conta_0 << endl;
	cout << "negro: " << conta_negro << endl;
	cout << "rojo: " << conta_rojo << endl;
	cout << "----------------------------------------" << endl;
	cout << "Apuestas ganadas: " << apuesta_w << endl;
	cout << "Apuestas perdidas: " << apuesta_l << endl;
	if (beneficio_total >= 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "Beneficio total: S/." << beneficio_total << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (beneficio_total < 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "Beneficio total: S/." << beneficio_total << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	if (max_gasto <= presupuesto) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		cout << "Max Gasto: S/." << max_gasto << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (max_gasto > presupuesto) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "Max Gasto: S/." << max_gasto << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	cout << "\nMax gasto representa cual es el maximo de dinero que se uso en una jugada" << endl;
	cout << "hasta ganar, es decir, el presupuesto 'minimo' necesario para realizar la jugada." << endl;
	cout << "Si esta en rojo significa que sobrepaso tu presupuesto." << endl;
	cout << "\nSe recomienda probar distintas combinaciones con distinto numero de"<<endl;
	cout << "simulaciones para obtener una mejor vision de lo que sucede" << endl;
	cout << "Recuerda que al final siempre afecta un poco la suerte, y no caigas en la LUDOPATIA." << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	system("pause");
}

//BETA 2.0, INICIAR NUEVO PROYECTO
//ESTO ES UNA PRUEBA
//HOLA


//Funcion apuesta
 int apuesta(int repeticion, int color) {
	int color_apuesta;
	if (repeticion >= 3) {
		color_apuesta = color;
	}
	else {
		color_apuesta = 0;
	};
	return color_apuesta;
}
