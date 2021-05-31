using System;
using System.Text;
using System.Threading.Tasks;

namespace lab1_Csharp
{
    static class MatrixFromConsole
    {
        public static int[,] GetNewMatrix()
        {
            int rows = 0, cols = 0;

            while (rows <= 0)                 //Ввод числа строк и столбцов матрицы с проверкой на положительное число
            {
                try
                {
                    Console.Write("\nEnter the number of rows of the matrix\nrows = ");
                    rows = int.Parse(Console.ReadLine());
                    if (rows <= 0)
                        throw new Exception();
                }
                catch (Exception)
                {
                    Console.WriteLine("Wrong input! Try again, please :)");
                }
            }
            while (cols <= 0)
            {
                try
                {
                    Console.Write("Enter the number of colomns of the matrix\ncolomns = ");
                    cols = int.Parse(Console.ReadLine());
                    if (cols <= 0)
                        throw new Exception();
                }
                catch (Exception)
                {
                    Console.WriteLine("Wrong input! Try again, please :)");
                }
            }

            int[,] array = new int[rows, cols];
            bool matrixIsFull = false;

            Console.WriteLine("Enter matrix elements");                 //Ввод элементов матрицы с проверкой на числа
            while (!matrixIsFull)
            {
                try
                {
                    string s;
                    string[] arr;
                    int i = 0, j = 0, k = 0, n = 0;

                    while (n < rows * cols)
                    {
                        k = 0;
                        s = Console.ReadLine();
                        arr = s.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);

                        while (k < arr.Length && i < rows)
                        {
                            if (j < cols)
                            {
                                array[i, j++] = int.Parse(arr[k++]);
                                n++;
                            }
                            else
                            {
                                j = 0;
                                i++;
                            }
                        }
                    }
                    matrixIsFull = true;
                }
                catch (Exception)
                {
                matrixIsFull = false;
                Console.WriteLine("Wrong input! Try again, please :)");
                }
            }
            return array;
        }
        public static void PrintMatrix(Matrix array)
        {
            Console.ForegroundColor = ConsoleColor.Cyan;
            for (int i = 0; i < array.GetRows(); i++)
            {
                Console.Write("          ");
                for (int j = 0; j < array.GetCols(); j++)
                {
                    Console.Write(array[i, j] + "\t");
                }
                Console.WriteLine();
            }
            Console.ForegroundColor = ConsoleColor.White;
        }
        public static void ShowMenuOfMatrixOperations()
        {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("\n\n-----------------------------------MATRIX CALCULATOR:-----------------------------------");
            Console.WriteLine("1. Matrix addition");
            Console.WriteLine("2. Matrix subtraction");
            Console.WriteLine("3. Multiplication of a matrix by a number");
            Console.WriteLine("4. Matrix multiplication");
            Console.WriteLine("5. Matrix transpose");
            Console.WriteLine("6. Exit");
            Console.WriteLine("----------------------------------------------------------------------------------------");
            Console.ForegroundColor = ConsoleColor.White;
        }
    }
}
