
int** rand_mx(int rows, int columns) {
    
    int** mx = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        mx[i] = (int*)malloc(sizeof(int) * columns);
        for (int j = 0; j < columns; j++) {
            mx[i][j] = rand() % 2;
        }
    }

    return mx;
}

int** alloc_mx(int rows, int columns) {
    
    int** mx = (int**)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; i++) {
        mx[i] = (int*)calloc(columns, sizeof(int));
    }

    return mx;
}

void free_mx(int** mx, int rows) {
	for (int i = 0; i < rows; i++)
		free((mx)[i]);
	free(mx);
}

int scalar_product(int* a, int* b, int length) {
    int product = 0;
    for (int i = 0; i < length; i++) {
        product += a[i] * b[i];
    }
    return product;
}

int** transpose(int** mx, int rows, int columns) {
    int** mx_t = alloc_mx(columns, rows);
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < rows; i++) {
            mx_t[j][i] = mx[i][j];
        }
    }
    return mx_t;
} 

void print_mx(int** mx, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", mx[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}