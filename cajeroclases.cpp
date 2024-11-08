#include <iostream>
#include <fstream>
#include <sstream>  // Incluye sstream para usar stringstream
#include <string>

using namespace std;

// Clase Cajero que maneja el saldo y las operaciones
class Cajero {
private:
    double saldo;

    // Generar archivo de log
    void registrarOperacion(const string& mensaje) {
        ofstream archivo("ticket.txt", ios::app); // Abre el archivo en modo de añadir
        if (archivo.is_open()) {
            archivo << mensaje << endl;
            archivo.close();
        } else {
            cout << "No se pudo abrir el archivo para registrar la operación." << endl;
        }
    }

    // Convertir número a cadena
    string numeroAString(double numero) {
        stringstream ss;
        ss << numero;
        return ss.str();
    }

public:
    // Constructor
    Cajero(double saldoInicial) : saldo(saldoInicial) {}

    // Mostrar saldo
    void consultarSaldo() {
        cout << "Saldo actual: $" << saldo << endl;
         registrarOperacion("Saldo actual: $" + numeroAString(saldo));
    }

    // Depositar efectivo
    void depositarEfectivo(double monto) {
        saldo += monto;
        cout << "Depósito exitoso. Nuevo saldo: $" << saldo << endl;
        registrarOperacion("Depósito realizado: $" + numeroAString(monto) + "\nSaldo despues del deposito: $" + numeroAString(saldo));
    }

    // Transferir dinero
    void transferir(double monto) {
        if (monto > saldo) {
            cout << "No cuenta con el saldo suficiente para la transferencia." << endl;
        } else {
            saldo -= monto;
            cout << "Transferencia exitosa. Nuevo saldo: $" << saldo << endl;
            registrarOperacion("Transferencia realizada: $" + numeroAString(monto) + "\nSaldo después de la transferencia: $" + numeroAString(saldo));
        }
    }

    // Extraer dinero
    void extraerEfectivo(double monto) {
        if (monto > saldo) {
            cout << "No cuenta con el saldo suficiente para la disposición de efectivo." << endl;
        } else {
            saldo -= monto;
            cout << "Extracción exitosa. Nuevo saldo: $" << saldo << endl;
            registrarOperacion("Extracción realizada: $" + numeroAString(monto) + "\nSaldo despues de la disposición: $" + numeroAString(saldo));
        }
    }
};

// Función principal
int main() {
	setlocale(LC_ALL, "Spanish");
    Cajero cajero(5000);  // Inicializamos el saldo en 5000
    int opcion;
    double monto;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Consultar Saldo" << endl;
        cout << "2. Depositar Efectivo" << endl;
        cout << "3. Transferir" << endl;
        cout << "4. Extraer Efectivo" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cajero.consultarSaldo();
                break;
            case 2:
                cout << "Ingrese el monto a depositar: $";
                cin >> monto;
                cajero.depositarEfectivo(monto);
                break;
            case 3:
                cout << "Ingrese el monto a transferir: $";
                cin >> monto;
                cajero.transferir(monto);
                break;
            case 4:
                cout << "Ingrese el monto a extraer: $";
                cin >> monto;
                cajero.extraerEfectivo(monto);
                break;
            case 5:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción inválida. Inténtelo de nuevo." << endl;
        }
    } while(opcion != 5);

    return 0;
}

