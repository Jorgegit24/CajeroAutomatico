#include <iostream>
#include <fstream>
#include <sstream> // Incluye sstream para la alternativa a to_string
using namespace std;

// Variable global para el saldo
int saldo = 5000;

// Funci�n para convertir n�meros a cadenas
string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

// Funci�n para escribir en el archivo de registro
void escribirEnArchivo(const string& mensaje) {
    ofstream archivo("registro.txt", ios::app); // Abre el archivo en modo agregar
    if (archivo.is_open()) {
        archivo << mensaje << endl;
        archivo.close();
    } else {
        cout << "Error al abrir el archivo de registro." << endl;
    }
}

// Funciones del programa
void consultarSaldo() {
    cout << "Saldo actual: $" << saldo << endl;
    escribirEnArchivo("Consulta de saldo: $" + intToString(saldo));
}

void depositarEfectivo(int monto) {
    saldo += monto;
    cout << "Dep�sito exitoso. Nuevo saldo: $" << saldo << endl;
    escribirEnArchivo("Dep�sito: $" + intToString(monto) + " | Saldo despu�s del dep�sito: $" + intToString(saldo));
}

void transferir(int monto) {
    if (monto > saldo) {
        cout << "No cuenta con el saldo suficiente para realizar la transferencia." << endl;
        escribirEnArchivo("Transferencia fallida: $" + intToString(monto) + " | Saldo insuficiente.");
    } else {
        saldo -= monto;
        ofstream archivo("transferencia.txt");
        if (archivo.is_open()) {
            archivo << "Transferencia realizada\n";
            archivo << "Monto transferido: $" << monto << endl;
            archivo.close();
            cout << "Transferencia exitosa. Nuevo saldo: $" << saldo << endl;
        } else {
            cout << "Error al generar el archivo de transferencia." << endl;
        }
        escribirEnArchivo("Transferencia: $" + intToString(monto) + " | Saldo despu�s de la transferencia: $" + intToString(saldo));
    }
}

void extraerEfectivo(int monto) {
    if (monto > saldo) {
        cout << "No cuenta con el saldo suficiente para la disposici�n de efectivo." << endl;
        escribirEnArchivo("Extracci�n fallida: $" + intToString(monto) + " | Saldo insuficiente.");
    } else {
        saldo -= monto;
        cout << "Extracci�n exitosa. Nuevo saldo: $" << saldo << endl;
        escribirEnArchivo("Extracci�n: $" + intToString(monto) + " | Saldo despu�s de la extracci�n: $" + intToString(saldo));
    }
}

int main() {
	setlocale(LC_ALL, "Spanish");
    int opcion, monto;

    // Inicializa el archivo de registro
    escribirEnArchivo("Inicio del programa. Saldo inicial: $" + intToString(saldo));

    do {
        cout << "\nMen�:\n";
        cout << "1. Consultar Saldo\n";
        cout << "2. Depositar Efectivo\n";
        cout << "3. Transferir\n";
        cout << "4. Extraer Efectivo\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opci�n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                consultarSaldo();
                break;
            case 2:
                cout << "Ingrese el monto a depositar: $";
                cin >> monto;
                depositarEfectivo(monto);
                break;
            case 3:
                cout << "Ingrese el monto a transferir: $";
                cin >> monto;
                transferir(monto);
                break;
            case 4:
                cout << "Ingrese el monto a extraer: $";
                cin >> monto;
                extraerEfectivo(monto);
                break;
            case 5:
                cout << "Gracias por usar el cajero autom�tico. �Hasta luego!" << endl;
                escribirEnArchivo("Fin del programa. Saldo final: $" + intToString(saldo));
                break;
            default:
                cout << "Opci�n inv�lida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}

