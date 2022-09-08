#include <iostream>
#include <fstream>

using namespace std;

void mostrarVector(int vec[], int vecDim){
    for (int i = 0 ; i < vecDim ; i++){
        if (i == 0){
            cout << "[" << vec[i];
        }
        else if(i != vecDim-1){
            cout << ", " << vec[i];
        }
        else{
            cout << ", " << vec[i] << "]" << endl;
        }
    }
}

void mostrarVector(string vec[], int vecDim){
    for (int i = 0 ; i < vecDim ; i++){
        if (i == 0){
            cout << "[" << vec[i];
        }
        else if(i != vecDim-1){
            cout << ", " << vec[i];
        }
        else{
            cout << ", " << vec[i] << "]" << endl;
        }
    }
}

void mostrarVector(double vec[], int vecDim){
    for (int i = 0 ; i < vecDim ; i++){
        if (i == 0){
            cout << "[" << vec[i];
        }
        else if(i != vecDim-1){
            cout << ", " << vec[i];
        }
        else{
            cout << ", " << vec[i] << "]" << endl;
        }
    }
}

void buscarMayorVector (int vec[], int dimVec, int& max, int& maxPos){
    max = vec[0];
    maxPos = 0;
    for(int i = 1 ; i < dimVec ; i++){
        if (vec[i] > max){
            max = vec[i];
            maxPos = i;
        }
    }
}

void ordVecAscConRef (double vec[], int vecDim, int vecRef[]){//Ordena un vector de forma ascendente con un vector de referencia (o de nombres)
    double aux;
    for (int vuelta = 0 ; vuelta < vecDim ; vuelta++){
        for(int i = 1 ; i < vecDim-vuelta ; i++){
            if (vec[i] < vec[i-1]){
                aux = vec[i];
                vec[i] = vec[i-1];
                vec[i-1] = aux;
                aux = vecRef[i];
                vecRef[i] = vecRef[i-1];
                vecRef[i-1] = aux;
            }
        }
    }
}//Nota: vec y vecRef deben tener la misma dimensión

void mostrarMatriz(string m[][5], int dimFil){
	const int dimCol {5}; // solo por prolijidad
	for (int i = 0; i < dimFil; ++i) {
        cout << "Cliente " << i << ": ";
		for (int j = 0; j < dimCol; ++j)
			cout << m[i][j] << '\t';
		cout << endl;
	}
}

void mostrarMatriz(int m[][5], int dimFil){
	const int dimCol {5}; // solo por prolijidad
	for (int i = 0; i < dimFil; ++i) {
        cout << "Cliente " << i << ": ";
		for (int j = 0; j < dimCol; ++j)
			cout << m[i][j] << '\t';
		cout << endl;
	}
}

void mostrarMatriz(double m[][5], int dimFil){
	const int dimCol {5}; // solo por prolijidad
	for (int i = 0; i < dimFil; ++i) {
        cout << "Cliente " << i << ": ";
		for (int j = 0; j < dimCol; ++j)
			cout << m[i][j] << '\t';
		cout << endl;
	}
}

void mostrarMatrizNombres(int m[][5], int dimFil, string filas[], string columnas[]){
    const int dimCol {5}; // solo por prolijidad
    cout << '\t';
    for (int i = 0 ; i < dimCol ; i++){
        cout << '\t' << "|" << columnas[i] << "|";
    }
    cout << endl;
    for (int i = 0 ; i < dimFil; ++i) {
        cout << filas[i] << ":     " << '\t';
		for (int j = 0; j < dimCol; ++j)
			cout << '\t' << m[i][j] << '\t';
		cout << endl;
	}
}
int main(){
    int const cantCli {8};
    int const cantProd {5};
    bool debug {true};
    if(debug){
        cout << "Debug activo" << endl;
    }

    fstream nombres;
    nombres.open("Nombres.txt");
    if(!nombres){
        cout << "Error al leer archivo de Nombres" << endl;
        return 1;
    }
    if (debug){
        cout << "Archivo de Nombres abierto con éxito" << endl;
    }

    string clientes[cantCli];
    string productos[cantProd];

    for (int i = 0; i < cantCli && nombres >> clientes[i] ; i++);
    for (int i = 0; nombres >> productos[i] ; i++);

    nombres.close();

    if (debug){
        cout << "Clientes: ";
        mostrarVector(clientes, cantCli);
        cout << "Productos: ";
        mostrarVector(productos, cantProd);
        cout << endl;
    }

    fstream datos;
    datos.open("Datos.txt");
    if(!datos){
        cout << "Error al leer archivo de Datos" << endl;
        return 1;
    }
    if (debug){
        cout << "Archivo de Datos abierto con éxito" << endl;
    }

    double cliTipoProd[cantCli][cantProd]{};//Matriz de clientes por tipo de producto
    double kmAcumXProd[cantCli][cantProd]{};//Matriz de kilómetros acumulados por producto
    int entregasGeneral[cantProd]{};//Array de entregas totales por producto
    int idCli, idProd;
    double peso, dist;

    while (datos >> idCli >> idProd >> peso >> dist){//Cargo las matrices
        cliTipoProd[idCli][idProd] += peso;
        kmAcumXProd[idCli][idProd] += dist;
        entregasGeneral[idProd]++;
    }

    datos.close();

    if (debug){//Muestro la matriz cargada
        cout << '\t' << "   Prod 0" << '\t' << "Prod 1" << '\t' << "Prod 2" << '\t' << "Prod 3" << '\t' << "Prod 4" << '\t' << endl;
        mostrarMatriz(cliTipoProd, cantCli);
    }

    int const parametro {13000};
    int listado1[cantCli][cantProd];

    for (int i = 0 ; i < cantCli ; i++){
        for (int j = 0 ; j < cantProd ; j++){
            if(cliTipoProd[i][j] > parametro){
                listado1[i][j] = 1;
            }
            else{
                listado1[i][j] = 0;
            }
        }
    }
    
    //Punto 1
    cout << "Lista de productos por cliente que superaron los " << parametro << " kg:" << endl;
    cout << "0 = no supera. 1 = supera" <<  endl;
    mostrarMatrizNombres(listado1, cantCli, clientes, productos);

    cout << "===========================================================================================" << endl;
    
    int prodAcumXCli[cantCli]{};//Cantidad de productos con más de 13000 kg por cliente

    for (int i = 0 ; i < cantCli ; i++){
        for (int j = 0 ; j < cantProd ; j++){
            if (listado1[i][j] == 1){
                prodAcumXCli[i]++;
            }
        }
    }

    int max, maxPos;
    buscarMayorVector(prodAcumXCli, cantCli, max, maxPos);//maxPos va a ser el cliente con más productos con +13000 kg
    if (debug){
        cout << "El cliente con más productos con más de " << parametro << " kg es el cliente " << clientes[maxPos] << ", con " << max << " productos." << endl;
    }

    double kmXProd[cantProd]{};//Acumula los km por producto del cliente "maxPos"
    for (int j = 0 ; j < cantProd ; j++){
        kmXProd[j] += kmAcumXProd[maxPos][j];
    }

    int refProd[cantProd];
    for (int i = 0 ; i < cantProd ; i++){//Cargo un vector para referenciar los nombres de los productos
        refProd[i] = i;
    }

    if(debug){
        cout << "kmXProd antes de ordenar: " << endl;
        mostrarVector(kmXProd, cantProd);
        cout << "refProd después de ordenar: " << endl;
        mostrarVector(refProd, cantProd);
    }
    
    ordVecAscConRef(kmXProd, cantProd, refProd);

    if(debug){
        cout << "kmXProd después de ordenar: " << endl;
        mostrarVector(kmXProd, cantProd);
        cout << "refProd después de ordenar: " << endl;
        mostrarVector(refProd, cantProd);
    }
    //Punto 2
    cout << "La matriz de kilómetros por producto del cliente con más productos con más de " << parametro << " kg es:" << endl;
    for (int i = 0 ; i < cantProd ; i++){
        cout << productos[refProd[i]] << '\t';
    }
    cout << endl;
    for (int i = 0 ; i < cantProd ; i++){
        cout << kmXProd[i] << '\t' << '\t';
    }
    cout << endl << "===========================================================================================" << endl;

    //Punto 3
    if(debug){
        cout << "Entregas totales por producto: " << endl;
        mostrarVector(productos, cantProd);
        mostrarVector(entregasGeneral, cantProd);
    }
    cout << "El tipo de producto con mayor cantidad de km recorridos es " << productos[refProd[cantProd-1]] << endl;
    cout << "Para el tipo de producto " << productos[refProd[cantProd-1]] << " se registraron " << entregasGeneral[refProd[cantProd-1]] << " entregas en total." << endl;
    return 0;
}