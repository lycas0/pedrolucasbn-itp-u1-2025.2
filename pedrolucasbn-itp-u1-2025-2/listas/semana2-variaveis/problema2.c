#include <stdio.h>
#include <math.h>

int main() {
    float TemperaturaCelsius, TemperaturaFahrenheit, TemperaturaKelvin;
    
    printf("Digite a temperatura em Celsius: ");
    scanf("%f", &TemperaturaCelsius);

    TemperaturaFahrenheit = (TemperaturaCelsius * 9.0 / 5.0) + 32.0;
    TemperaturaKelvin = TemperaturaCelsius + 273.15;

    printf("A temperatura em Fahrenheit é: %.1f\n", TemperaturaFahrenheit);
    printf("A temperatura em Kelvin é: %.1f\n", TemperaturaKelvin);

    return 0;
}