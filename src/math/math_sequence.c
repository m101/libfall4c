double sequence_sum_arithmethic (long n, double nfirst, double nlast) {
    double sum_results = n * (nfirst + nlast)/2;

    return sum_results;
}

double sequence_sum_geometric (long n, double nfirst, double nlast) {
    double sum_results = n * (nfirst + nlast)/2;

    return sum_results;
}

long fibonacci (long position) {
    int i = 0;
    long nombre1 = 0, nombre2 = 1, temp = 0;


    for (i = 0; i < position; i++) {
        temp = nombre1;
        nombre1 = nombre2;
        nombre2 = temp + nombre2;
    }

    return nombre1;
}

