#include <iostream>
#include <cmath>
#include <vector>

// Funcția pentru calculul diferențelor divizate
std::vector<std::vector<double>> calculeazaDiferenteDivizate(const std::vector<double>& noduriX, const std::vector<double>& noduriY) {
    int n = noduriX.size();
    std::vector<std::vector<double>> diferente(n, std::vector<double>(n));

    for (int i = 0; i < n; i++) {
        diferente[i][0] = noduriY[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            diferente[i][j] = (diferente[i + 1][j - 1] - diferente[i][j - 1]) / (noduriX[i + j] - noduriX[i]);
        }
    }

    return diferente;
}

// Funcția pentru calculul valorii interpolării într-un punct
double interpolareNewton(double x, const std::vector<double>& noduriX, const std::vector<double>& diferenta0) {
    int n = noduriX.size();
    double rezultat = diferenta0[0];
    double produs = 1.0;

    for (int i = 1; i < n; i++) {
        produs *= (x - noduriX[i - 1]);
        rezultat += diferenta0[i] * produs;
    }

    return rezultat;
}

int main() {
    // Cazul când funcția f(x) este dată în mod discret
    std::vector<double> noduriX = {1.0, 2.0, 3.0, 4.0, 5.0}; // Exemplu de noduri x
    std::vector<double> noduriY = {0.0, 1.0, 8.0, 27.0, 64.0}; // Exemplu de valori funcție în noduri y

    int N = noduriX.size();

    // Calculul diferențelor divizate
    std::vector<std::vector<double>> diferente = calculeazaDiferenteDivizate(noduriX, noduriY);

    // Interpolare pentru punctele de cercetare z_j
    std::vector<double> puncteCercetare = {1.5, 3.5}; // Exemplu de puncte de cercetare
    int M = puncteCercetare.size();

    std::cout << "Interpolare pentru cazul când funcția este dată în mod discret:\n";

    for (int j = 0; j < M; j++) {
        double rezultat = interpolareNewton(puncteCercetare[j], noduriX, diferente[0]);
        std::cout << "f(" << puncteCercetare[j] << ") = " << rezultat << "\n";
    }

    // Cazul când expresia funcției f(x) este cunoscută (pentru testare)
    double a = 10.0;
    double b = 20.0;
    int n = 10;

    // Generare noduri echidistante
    double h = (b - a) / (n - 1);
    std::vector<double> noduriXEchidistante(n);
    std::vector<double> noduriYEchidistante(n);

    for (int i = 0; i < n; i++) {
        noduriXEchidistante[i] = a + i * h;
        noduriYEchidistante[i] = std::log(noduriXEchidistante[i] + 1) / noduriXEchidistante[i]; // Exemplu de expresie funcție g(x)
    }

    // Calculul diferențelor divizate pentru nodurile echidistante
    std::vector<std::vector<double>> diferenteEchidistante = calculeazaDiferenteDivizate(noduriXEchidistante, noduriYEchidistante);

    // Punctele de cercetare pentru testare
    std::vector<double> puncteCercetareTest = {a, (a + b) / 2, b, 11.0, 15.0}; // Exemplu de puncte de cercetare pentru testare
    int MTest = puncteCercetareTest.size();

    std::cout << "\nInterpolare pentru cazul când expresia funcției este cunoscută:\n";

    for (int j = 0; j < MTest; j++) {
        double rezultat = interpolareNewton(puncteCercetareTest[j], noduriXEchidistante, diferenteEchidistante[0]);
        std::cout << "f(" << puncteCercetareTest[j] << ") = " << rezultat << "\n";
    }

    return 0;
}
