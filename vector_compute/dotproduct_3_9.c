/* ******************************************************************



****************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void get_input(double* vector_x, double* vector_y, double* scalar, int* vec_len, int* local_vec_len, int comm_sz, int my_rank, MPI_Comm comm);
void dotproduct(double* x, double* y,double* result, int length);
void vec_mul(double* x, double* scalar, double* result, int length);

int main(void){
	int	comm_sz;
	int my_rank;

    // Matrix Multiplication Calculation
    int* vec_len = NULL;
    int* local_vec_len = NULL;
    double* vector_x = NULL;
    double* vector_y = NULL;
    double* local_vector_x = NULL;
    double* local_vector_y = NULL;
    double* scalar = NULL;
    double* result_dotproduct;
    double* result_scalar_mul1;
    double* result_scalar_mul2;
    double* local_result_dotproduct;
    double* local_result_scalar_mul1;
    double* local_result_scalar_mul2;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm comm = MPI_COMM_WORLD;
    
    scalar = malloc(sizeof(double));
    local_vec_len = malloc(sizeof(int));

    if (my_rank == 0){
        vec_len = malloc(sizeof(int));  
        vector_x = malloc(vec_len[0]*sizeof(double));
        vector_y = malloc(vec_len[0]*sizeof(double));
    }

    // read the input from user
    get_input(vector_x, vector_y, scalar, vec_len, local_vec_len, comm_sz, my_rank, comm);
    // broadcast the data
    MPI_Bcast(scalar, 1, MPI_DOUBLE, 0, comm);
    MPI_Bcast(local_vec_len, 1, MPI_INT, 0, comm);

    // prepare the space for computing
    local_vector_x = malloc(local_vec_len[0]*sizeof(double));
    local_vector_y = malloc(local_vec_len[0]*sizeof(double));
    local_result_dotproduct = malloc(local_vec_len[0]*sizeof(double));  
    local_result_scalar_mul1 = malloc(local_vec_len[0]*sizeof(double));  
    local_result_scalar_mul2 = malloc(local_vec_len[0]*sizeof(double)); 

    // scatter vector x and y
    MPI_Scatter(vector_x, local_vec_len[0], MPI_DOUBLE, local_vector_x, local_vec_len[0], MPI_DOUBLE, 0, comm);
    MPI_Scatter(vector_y, local_vec_len[0], MPI_DOUBLE, local_vector_y, local_vec_len[0], MPI_DOUBLE, 0, comm);
    free(vector_x);
    free(vector_y);

    // dot product
    dotproduct(local_vector_x, local_vector_y, local_result_dotproduct, local_vec_len[0]);
    // vector multiply a scalar
    vec_mul(local_vector_x, scalar, local_result_scalar_mul1, local_vec_len[0]);
    vec_mul(local_vector_y, scalar, local_result_scalar_mul2, local_vec_len[0]);
    free(local_vector_x);
    free(local_vector_y);

    // prepare the space for result
    if (my_rank == 0){
        result_dotproduct = malloc(vec_len[0]*sizeof(double));
        result_scalar_mul1 = malloc(vec_len[0]*sizeof(double));
        result_scalar_mul2 = malloc(vec_len[0]*sizeof(double));
    }

    // gather the result
    MPI_Gather(local_result_dotproduct, local_vec_len[0], MPI_DOUBLE, result_dotproduct, local_vec_len[0], MPI_DOUBLE, 0, comm);
    MPI_Gather(local_result_scalar_mul1, local_vec_len[0], MPI_DOUBLE, result_scalar_mul1, local_vec_len[0], MPI_DOUBLE, 0, comm);
    MPI_Gather(local_result_scalar_mul2, local_vec_len[0], MPI_DOUBLE, result_scalar_mul2, local_vec_len[0], MPI_DOUBLE, 0, comm);
    free(local_result_dotproduct);
    free(local_result_scalar_mul1);
    free(local_result_scalar_mul2);
    
    // print the result by process 0
    if (my_rank == 0){
        printf("The dot product result is: \n");
        for (int i=0; i<vec_len[0]; i++){
            printf("%f ", result_dotproduct[i]);
        }
        printf("\n");

        printf("The result of vector 1 multiply scalar is: \n");
        for (int i=0; i<vec_len[0]; i++){
            printf("%f ", result_scalar_mul1[i]);
        }
        printf("\n");

        printf("The result of vector 2 multiply scalar is: \n");
        for (int i=0; i<vec_len[0]; i++){
            printf("%f ", result_scalar_mul2[i]);
        }
        printf("\n");

        free(vec_len);
        free(result_dotproduct);
        free(result_scalar_mul1);
        free(result_scalar_mul2);
    }

	MPI_Finalize();
	return 0;
}




void get_input(double* vector_x, double* vector_y, double* scalar, int* vec_len, int* local_vec_len, int comm_sz, int my_rank, MPI_Comm comm){
    if (my_rank == 0){
        printf("Please input the length of vector, which should be a multiply of %d: \n", comm_sz);
        scanf("%d", vec_len);
        local_vec_len[0] = vec_len[0] / comm_sz;
        printf("Please input the 1st vector: \n");
        for (int i=0; i<vec_len[0]; i++){
            scanf("%lf", &vector_x[i]);
        }
        printf("Please input the 2st vector: \n");
        for (int i=0; i<vec_len[0]; i++){
            scanf("%lf", &vector_y[i]);
        }
        printf("Please input the scalar: \n");
        scanf("%lf", scalar);
    }
}

void dotproduct(double* x, double* y, double* result, int length){
    for (int i=0; i<length; i++){
        result[i] = x[i]*y[i];
    }
}

void vec_mul(double* x, double* scalar, double* result, int length){
    for (int i=0; i<length; i++){
        result[i] = x[i] * scalar[0];
    }
}