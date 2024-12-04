//Sebastián Núñez Rojas
//C35627
//En este proyecto se desarrollará un programa el cual reciba dos funciones cuadráticas las cuales
//tendrá que ingresar el usuario, además este mismo deberá ingresar un porcentaje de error. Con 
//esto el programa deberá encontrar un subdominio donde la diferencia entre ambas funciones no 
//supere el porcentaje de error. 

//El programa para graficar estas funciones utilizará la biblioteca Gnuplot.


#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
 
#define DOMINIO_INICIAL -10 
#define DOMINIO_FINAL 10 
#define PASO 0.1 
 
//Funciones cuadráticas 
double func1(double x, double a, double b, double c) { 
    return a * x * x + b * x + c; 
} 
 
double func2(double x, double d, double e, double f) { 
    return d * x * x + e * x + f; 
} 
 
//Función para graficar usando gnuplot 
void plot_graph(double *x_valores, double *y1_valores, double *y2_valores, int size, double *x_aceptable, double *y_aceptable, int aceptable_size) { 
    FILE *gnuplot = popen("gnuplot -persistent", "w"); 
    if (gnuplot == NULL) { 
        fprintf(stderr, "Error: No se pudo abrir gnuplot.\n"); 
        exit(1); 
    } 
 
    fprintf(gnuplot, "set title 'Gráfica de Funciones Cuadráticas'\n"); 
    fprintf(gnuplot, "set xlabel 'x'\n"); 
    fprintf(gnuplot, "set ylabel 'f(x)'\n"); 
    fprintf(gnuplot, "set grid\n"); 
    fprintf(gnuplot, "set xrange [%d:%d]\n", DOMINIO_INICIAL, DOMINIO_FINAL); 
     
    //Determina el rango de y para las funciones 
    double min_y = fmin(fmin(y1_valores[0], y2_valores[0]), fmin(y1_valores[size-1], y2_valores[size-1])); 
    double max_y = fmax(fmax(y1_valores[0], y2_valores[0]), fmax(y1_valores[size-1], y2_valores[size-1])); 
 
    fprintf(gnuplot, "set yrange [%f:%f]\n", min_y - 1, max_y + 1); 
 
    //Grafica las funciones 
    fprintf(gnuplot, "plot '-' with lines title 'Función 1', '-' with lines title 'Función 2', '-' with lines title 'Rango Aceptable'\n"); 
 
    //Función 1 
    for (int i = 0; i < size; i++) { 
        fprintf(gnuplot, "%f %f\n", x_valores[i], y1_valores[i]); 
    } 
    fprintf(gnuplot, "e\n"); 
 
    //Función 2 
    for (int i = 0; i < size; i++) { 
        fprintf(gnuplot, "%f %f\n", x_valores[i], y2_valores[i]); 
    } 
    fprintf(gnuplot, "e\n"); 
 
    //Rango aceptable como una línea 
    for (int i = 0; i < aceptable_size; i++) { 
        fprintf(gnuplot, "%f %f\n", x_aceptable[i], y_aceptable[i]); 
    } 
    fprintf(gnuplot, "e\n"); 
 
    pclose(gnuplot); 
} 
 
int main() { 
    
    double a, b, c, d, e, f, error_percentage; 
 
    //Entradas del usuario
    printf("Ingrese el coeficiente a: "); 
    scanf("%lf", &a); 
    printf("Ingrese el coeficiente b: "); 
    scanf("%lf", &b); 
    printf("Ingrese el coeficiente c: "); 
    scanf("%lf", &c); 
    printf("Ingrese el coeficiente d: "); 
    scanf("%lf", &d); 
    printf("Ingrese el coeficiente e: "); 
    scanf("%lf", &e); 
    printf("Ingrese el coeficiente f: "); 
    scanf("%lf", &f); 
    printf("Ingrese el porcentaje de error (0-100): "); 
    scanf("%lf", &error_percentage); 
 
    //Arrays para valores de x, y1, y2 
    int size = (int)((DOMINIO_FINAL - DOMINIO_INICIAL) / PASO) + 1; 
    double *x_valores = malloc(size * sizeof(double)); 
    double *y1_valores = malloc(size * sizeof(double)); 
    double *y2_valores = malloc(size * sizeof(double)); 
    double *x_aceptable = malloc(size * sizeof(double)); 
    double *y_aceptable = malloc(size * sizeof(double)); 
 
    int aceptable_size = 0; 
 
    //Calcular valores 
    for (double x = DOMINIO_INICIAL; x <= DOMINIO_FINAL; x += PASO) { 
        int index = (int)((x - DOMINIO_INICIAL) / PASO); 
        x_valores[index] = x; 
        y1_valores[index] = func1(x, a, b, c); 
        y2_valores[index] = func2(x, d, e, f); 
         
        //Calcular el rango aceptable basado en el porcentaje de error 
        double error = (error_percentage / 100.0) * fabs(y1_valores[index]); 
        if (fabs(y1_valores[index] - y2_valores[index]) <= error) { 
            x_aceptable[aceptable_size] = x; 
            y_aceptable[aceptable_size] = y2_valores[index]; 
            aceptable_size++; 
        } 
    } 
 
    //Graficar 
    plot_graph(x_valores, y1_valores, y2_valores, size, x_aceptable, y_aceptable, aceptable_size); 
 
    //Libera memoria 
    free(x_valores); 
    free(y1_valores); 
    free(y2_valores); 
    free(x_aceptable); 
    free(y_aceptable); 
 
    return 0;

}