#include <iostream>

using namespace std;

#include "Examen.h"
#include "venta.h"
#include "ArchivoVentas.h"


void Examen::Punto1(){
// La cantidad de sectores con menos de 100 entradas vendidas.
    const int TamSectores= 12, LimiteEntradasVendidas=100;
    int cantidadSectores =0, indiceSector=0;


    ArchivoVentas archivo("entradas.dat");
    int cantidadRegistros = archivo.CantidadRegistros();

    if (cantidadRegistros==0){
        cout << "No hay registros." << endl;
        return;
    }


    int VecEntradasSector [TamSectores] = {0};

   for (int i=0; i < cantidadRegistros; i++){
        Venta registro;
        registro = archivo.Leer(i);

    if (registro.getEstado()==true){
        indiceSector = registro.getIdSector() -1;
        if (indiceSector>=0 && indiceSector<TamSectores){
            VecEntradasSector [indiceSector] += registro.getCantidad() ;
        }
    }

}

for (int i =0; i<TamSectores; i++){
    if (VecEntradasSector[i]<LimiteEntradasVendidas){
        cantidadSectores++;
    }
}
cout << "PUNTO 1: La cantidad de sectores con menos de " << LimiteEntradasVendidas << " entradas vendidas es/son: " << cantidadSectores << endl;
cout << endl;
}

void Examen::Punto2(){
// La/s ID/s de Sector con un importe total recaudado mayor a $ 450 millones.

    const int TamSectores=12, LimiteImporteTotalRecaudado=450000000;
    float importeTotalXSector [TamSectores] = {0};
    int indiceSector=0;
    bool encontrado = false;

    ArchivoVentas archivo("entradas.dat");
    int cantidadRegistros = archivo.CantidadRegistros();

    if (cantidadRegistros==0){
        cout << "No hay registros." << endl;
        return;
    }


    for (int i=0; i < cantidadRegistros; i++){
        Venta registro;
        registro = archivo.Leer(i);

    if (registro.getEstado()==true){
        indiceSector = registro.getIdSector() -1;
        if (indiceSector>=0 && indiceSector<TamSectores){
            importeTotalXSector[indiceSector] += registro.getImporte();
        }
    }
}


     cout << "PUNTO 2: ID de los sectores que recaudaron un importe total mayor a $" << LimiteImporteTotalRecaudado;
     cout << endl;

     for (int i =0;i<TamSectores;i++){
        if (importeTotalXSector[i]>LimiteImporteTotalRecaudado){
            cout << "Sector: " << i+1 << endl;
            encontrado=true;
        }
     }
    if (encontrado==false){
        cout << "Ningun sector supero los $"<< LimiteImporteTotalRecaudado<< " recaudados." << endl;
    }



}

void Examen::Punto3(){

/* Crear mecanismo de autenticación que se obtiene a partir del análisis del contenido del archivo.
1. Tamaño en bytes del archivo.
2. Cantidad de registros activos.
3. Cantidad de registros borrados.
4. Valor máximo de la cantidad de entradas vendidas correspondiente a un registro activo.
*/
const int Tam = 4;
int cantidadActivos = 0, cantidadBorrados=0, mayorcantidadEntradas=0;

FILE *pArchivo = fopen ("entradas.dat" , "rb");

if (pArchivo== nullptr){
    cout<< "ERROR: NO SE PUDO ABRIR EL ARCHIVO." << endl;
    return;
}

fseek (pArchivo, 0, SEEK_END );
int tamanioBytes = ftell (pArchivo);
fclose (pArchivo);

ArchivoVentas archivo ("entradas.dat");
int cantidadRegistros = archivo.CantidadRegistros();


for (int i =0; i<cantidadRegistros;i++){
    Venta registro;
    registro = archivo.Leer(i);
    if ( registro.getEstado()==true){
        cantidadActivos++;
        if (registro.getCantidad()>mayorcantidadEntradas){
            mayorcantidadEntradas=registro.getCantidad();
        }
    }else {
    cantidadBorrados++;
    }
}
int VecAutenticacion [Tam]= {tamanioBytes, cantidadActivos, cantidadBorrados, mayorcantidadEntradas};

cout << "PUNTO 3: mecanismo de autenticacion: " << endl;

for (int i =0; i<Tam; i++){
    cout << VecAutenticacion[i] << endl;
}


}
