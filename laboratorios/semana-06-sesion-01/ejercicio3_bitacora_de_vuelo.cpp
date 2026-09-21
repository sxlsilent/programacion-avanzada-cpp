#include <iostream>
#include <utility>


class BitacoraDeVuelo {
    private:
        double* consumos;
        int capacidad;

    public:
        BitacoraDeVuelo(int nuevaCapacidad) {
            capacidad = nuevaCapacidad;
            consumos = new double[capacidad];

            std::cout << "Bitacora creada para " << capacidad << " tramos" << std::endl;
    }

        BitacoraDeVuelo(BitacoraDeVuelo&& otra) {
            consumos = otra.consumos;
            capacidad = otra.capacidad;

            otra.consumos = nullptr;
            otra.capacidad = 0;
    }

        BitacoraDeVuelo& operator=(BitacoraDeVuelo&& otra) {
            if (this != &otra) {
                delete[] consumos;

                consumos = otra.consumos;
                capacidad = otra.capacidad;

                    otra.consumos = nullptr;
                otra.capacidad = 0;
            }

        return *this;
    }

    void guardarConsumo(int indice, double valor) {
        consumos[indice] = valor;
    }

    double getConsumo(int indice) {
        if (consumos == nullptr) {
            std::cout << "Bitacora vacia (fue movida)" << std::endl;
            return 0.0;
        }

        return consumos[indice];
    }

    ~BitacoraDeVuelo() {
        std::cout << "Destruyendo bitacora (capacidad "
                  << capacidad
                  << ")"
                  << std::endl;

        delete[] consumos;
    }
};


int main() {
    BitacoraDeVuelo original(4);
    original.guardarConsumo(0, 850.5);

    BitacoraDeVuelo trasladada = std::move(original);
    std::cout << "original.getConsumo(0) = " << original.getConsumo(0) << std::endl;
    std::cout << "trasladada.getConsumo(0) = " << trasladada.getConsumo(0) << std::endl;

    BitacoraDeVuelo otra(2);
    otra = std::move(trasladada);
    std::cout << "otra.getConsumo(0) = " << otra.getConsumo(0) << std::endl;

    return 0;
}
