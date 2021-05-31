using System;
using System.Text;
using System.Threading.Tasks;

namespace lab1_Csharp
{
    public class Matrix
    {
        //public int rows { get; }
        //public int cols { get; }
        private int rows, cols;
        private int[,] array;
        public int GetRows()
        {
            return rows;
        }
        public int GetCols()
        {
            return cols;
        }

        public Matrix()
        {
        }
        public Matrix(int rows, int cols)
        {
            this.rows = rows;
            this.cols = cols;
            array = new int[rows, cols];
        }
        public Matrix(int[,] array)
        {
            this.array = array;
            rows = array.GetLength(0);
            cols = array.GetLength(1);
        }
        public int this[int i, int j]
        {
            get
            {
                return array[i, j];
            }
            set
            {
                array[i, j] = value;
            }
        }
        public static Matrix operator +(Matrix matrix1, Matrix matrix2)        //Сложение матриц
        {
            Matrix matrix3 = new Matrix(matrix1.rows, matrix2.cols);
            if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols)
                throw new Exception();

            for (int i = 0; i < matrix1.rows; i++)
            {
                for (int j = 0; j < matrix1.cols; j++)
                {
                    matrix3[i, j] = matrix1[i, j] + matrix2[i, j];
                }
            }
            return matrix3;
        }
        public static Matrix operator -(Matrix matrix1, Matrix matrix2)           //Вычитание матриц
        {
            Matrix matrix3 = new Matrix(matrix1.rows, matrix2.cols);
            if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols)
                throw new Exception();

            for (int i = 0; i < matrix1.rows; i++)
            {
                for (int j = 0; j < matrix1.cols; j++)
                {
                    matrix3[i, j] = matrix1[i, j] - matrix2[i, j];
                }
            }
            return matrix3;
        }
        public static Matrix operator *(Matrix matrix1, Matrix matrix2)           //Перемножение матриц
        {
            Matrix matrix3 = new Matrix(matrix1.rows, matrix2.cols);
            if (matrix1.cols != matrix2.rows)
                throw new Exception();

            for (int i = 0; i < matrix1.rows; i++)
            {
                for (int k = 0; k < matrix2.cols; k++)
                {
                    for (int j = 0; j < matrix1.cols; j++)
                    {
                        matrix3[i, k] += matrix1[i, j] * matrix2[j, k];
                    }
                }
            }
            return matrix3;
        }
        public static Matrix MatrixMultiplicationByNumber(Matrix matrix1, int k)           //Произведение матрицы на число
        {
            Matrix matrix3 = new Matrix(matrix1.rows, matrix1.cols);

            for (int i = 0; i < matrix1.rows; i++)
            {
                for (int j = 0; j < matrix1.cols; j++)
                {
                    matrix3[i, j] = matrix1[i, j] * k;
                }
            }
            return matrix3;
        }
        public static Matrix GetTransposeMatrix(Matrix matrix1)           //Транспонирование квадратной матрицы
        {
            Matrix matrix3 = new Matrix(matrix1.cols, matrix1.rows);

            if (matrix1.rows != matrix1.cols)
                throw new Exception();

            for (int i = 0; i < matrix1.rows; i++)
            {
                for (int j = 0; j < matrix1.cols; j++)
                {
                    matrix3[i, j] = matrix1[j, i];
                }
            }
            return matrix3;
        }
        ~Matrix()
        {
        }
    }
}
