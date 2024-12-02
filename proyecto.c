#include <stdio.h>
#include <math.h>

int main(){
    double a, b, c, d, e, f, error_max;

    printf("Introduce los valores de la primer ecuacion cuadrática: ");
    scanf("%lf %lf %lf", &a, &b, &c);

    printf("Introduce los valores de la segunda ecuacion cuadrática: ");
    scanf("%lf %lf %lf", &d, &e, &f);

    printf("Introduce el porcentaje de error máximo: ");
    scanf("%lf", &error_max);   

    FILE *fichero = fopen("ecuaciones.txt", "w");
    double x;
    double delta = 0.1;
    double f1, f2, error;

    for (x = -100000; x <= 100000; x += delta){
        f1 = a*x*x + b*x + c;
        f2 = d*x*x + e*x + f;

        if(fabs(f1) > 1000000000) {
            error = 100 * fabs(f1 - f2) / fabs(f1);
            if (error <= error_max) {
                fprintf(fichero, "%lf %lf %lf, x, f1, f2");
        }
    }   
}
    fclose(fichero);

    FILE *fp=popen("gnuplot -persistent", "w");
    fprintf(fp, "set title 'Ecuaciones cuadráticas'\n");
    fprintf(fp, "set xlabel 'x'\n");
    fprintf(fp, "set ylabel 'f(x), g(x)'\n");
    fprintf(fp, "plot 'ecuaciones.txt' using 1:2 with lines tittle 'f(x)' lc rgb 'blue'\n");
    fprintf(fp, "replot 'ecuaciones.txt' using 1:3 with lines tittle 'g(x)' lc rgb 'red'\n");
    pclose(fp);

    return 0;
}