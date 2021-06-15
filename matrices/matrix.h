#ifndef __MATRIX__
#define __MATRIX__

typedef struct {
	//количество строк в массиве с данными
	unsigned int    m;
	//количество столбцов в массиве с данными
	unsigned int    n;
	//ссылка на массив с данными
	double          *a;
} TMatrix;

/**
Освобождает память
*/
void mx_free(TMatrix *m);

/**
Выводит на экран матрицу m
*/
void mx_print(TMatrix *m);

/**
Возвращает единичную матрицу размером n
*/
TMatrix *mx_identity(unsigned int n);

/**
Возвращает матрицу, созданную из строки, где элементы строки заданы через пробел, а строки разделены прямым слешем.
*/
TMatrix *mx_from_text(const char *s);

/**
Возвращает результат умножения m1 и m2
*/
TMatrix *mx_mul(TMatrix *m1, TMatrix *m2);

/**
Возвращает результат сложения m1 и m2
*/
TMatrix *mx_add(TMatrix *m1, TMatrix *m2);

/**
Возвращает результат умножения матрицы m на скаляр s
*/
TMatrix *mx_mul_scalar(TMatrix *m, double s);

/**
Возвращает результат возведения матрицы m в степень s
*/
TMatrix *mx_pow(TMatrix *m, double s);

/**
Возвращает результат транспонирования матрицы m
*/
TMatrix *mx_transponse(TMatrix *m);

/**
Возвращает определитель матрицы m
*/
int mx_det(TMatrix *m);

#endif