#include <stdio.h>
#include <lapacke.h>

int main() {
    int n = 3; // Matrix size
    int nrhs = 1; // Number of right-hand sides (b vector)
    int lda = n, ldb = n, info;
    int ipiv[n]; // Pivot indices

    // Define A matrix (column-major order)
    double A[3*3] = {
        3.0, 2.0, -1.0,
        2.0, -2.0, 4.0,
        -1.0, 0.5, -1.0
    };

    // Define b vector
    double b[3] = {1.0, -2.0, 0.0};

    // Solve Ax = b using LAPACK's dgesv function
    info = LAPACKE_dgesv(LAPACK_ROW_MAJOR, n, nrhs, A, lda, ipiv, b, ldb);

    // Check for success
    if (info == 0) {
        printf("Solution:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = %lf\n", i, b[i]);
        }
    } else {
        printf("Error: dgesv failed with info = %d\n", info);
    }

    return 0;
}
