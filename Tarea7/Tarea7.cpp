#include <iostream>
#include <string>
#include <stdexcept>
#include "BSTDictionary.h"
#include "ArrayList.h"

using namespace std;
using std::runtime_error;
using std::cout;
using std::endl;


int main() {

    BSTDictionary<int, string> diccionario1;
    BSTDictionary<int, string> diccionario2;
    int opcion = -1;
    while (opcion != 0) {
        cout << "Diccionario 1:\n";
        diccionario1.print();
        cout << "\nDiccionario 2:\n";
        diccionario2.print();
        cout << "\n---- MENU ----\n";
        cout << "1. Insert\n";
        cout << "2. Remove\n";
        cout << "3. GetValue\n";
        cout << "4. SetValue\n";
        cout << "5. Contains\n";
        cout << "6. Clear\n";
        cout << "7. GetKeys\n";
        cout << "8. GetValues\n";
        cout << "9. Update\n";
        cout << "10. Zip\n";
        cout << "0. Salir\n";

        try {
            cout << "\nOpcion: ";
            cin >> opcion;
            if (opcion == 0)
                break;
            int numeroDiccionario;
            cout << "Diccionario (1 o 2): ";
            cin >> numeroDiccionario;
            if (numeroDiccionario != 1 && numeroDiccionario != 2)
                throw runtime_error("numero de diccionario invalido");
            BSTDictionary<int, string>* D = nullptr;
            if (numeroDiccionario == 1)
                D = &diccionario1;
            if (numeroDiccionario == 2)
                D = &diccionario2;
            if (opcion == 1) {
                int key;
                string value;
                cout << "Llave: ";
                cin >> key;
                cin.ignore();
                cout << "Valor: ";
                getline(cin, value);
                D->insert(key, value);
            }
            if (opcion == 2) {
                int key;
                cout << "Llave: ";
                cin >> key;
                string value = D->remove(key);
                cout << "Valor eliminado: " << value << endl;
            }
            if (opcion == 3) {
                int key;
                cout << "Llave: ";
                cin >> key;
                cout << "Valor asociado: "
                    << D->getValue(key) << endl;
            }
            if (opcion == 4) {
                int key;
                string value;
                cout << "Llave: ";
                cin >> key;
                cin.ignore();
                cout << "Nuevo valor: ";
                getline(cin, value);
                D->setValue(key, value);
            }
            if (opcion == 5) {
                int key;
                cout << "Llave: ";
                cin >> key;
                if (D->contains(key))
                    cout << "La llave existe.\n";
                else
                    cout << "La llave no existe.\n";
            }
            if (opcion == 6) {
                D->clear();
                cout << "Diccionario vaciado.\n";
            }
            if (opcion == 7) {
                List<int>* keys = D->getKeys();
                cout << "Llaves:\n";
                keys->print();
                delete keys;
            }
            if (opcion == 8) {
                List<string>* values = D->getValues();
                cout << "Valores:\n";
                values->print();
                delete values;
            }
            if (opcion == 9) {
                if (D == &diccionario1)
                    diccionario1.update(&diccionario2);
                else
                    diccionario2.update(&diccionario1);
                cout << "Update realizado.\n";
            }
            if (opcion == 10) {
                int cantidad;
                cout << "Cantidad de elementos: ";
                cin >> cantidad;
                List<int>* keys = new ArrayList<int>(cantidad);
                List<string>* values = new ArrayList<string>(cantidad);
                for (int i = 0; i < cantidad; i++) {
                    int key;
                    cout << "Llave #" << i + 1 << ": ";
                    cin >> key;
                    keys->append(key);
                    cin.ignore();
                    string value;
                    cout << "Valor #" << i + 1 << ": ";
                    getline(cin, value);
                    values->append(value);
                }
                D->zip(keys, values);
                delete keys;
                delete values;
                cout << "Zip realizado.\n";
            }
            if (opcion < 0 || opcion > 10)
                throw runtime_error("Opcion invalida.");
        }
        catch (runtime_error& e) {
            cout << "\nERROR: " << e.what() << endl;
        }
    }
    cout << "\nGracias por usar el programa :) \n";
    return 0;
}

