using System;
using System.Text;
using System.Threading.Tasks;

namespace lab1_Csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                int ans = 0;
                Matrix matrix1, matrix2, matrix3;

                MatrixFromConsole.ShowMenuOfMatrixOperations();            //Выбор опции
                while (ans == 0)
                {
                    try
                    {
                        Console.Write("Choose option, please. Enter a number 1-6\nOption #");
                        Console.ForegroundColor = ConsoleColor.Red;
                        ans = int.Parse(Console.ReadLine());
                        Console.ForegroundColor = ConsoleColor.White;
                        if (!(ans >= 1 && ans <= 6))
                            throw new Exception();
                    }
                    catch (Exception)
                    {
                        Console.ForegroundColor = ConsoleColor.White;
                        Console.WriteLine("Wrong input! Try again, please :)");
                    }
                }

                if (ans != 3 && ans != 5 && ans != 6)        //операции с двумя матрицами
                {
                    matrix1 = new Matrix(MatrixFromConsole.GetNewMatrix());
                    matrix2 = new Matrix(MatrixFromConsole.GetNewMatrix());
                    Console.Clear();

                    switch (ans)
                    {
                        case 1:
                            try
                            {
                                matrix3 = matrix1 + matrix2;
                                Console.WriteLine("The result of adding matrices");
                                MatrixFromConsole.PrintMatrix(matrix1);
                                Console.WriteLine("   and matrix");
                                MatrixFromConsole.PrintMatrix(matrix2);
                                Console.WriteLine("     is matrix");
                                MatrixFromConsole.PrintMatrix(matrix3);
                            }
                            catch (Exception)
                            {
                                Console.WriteLine("\nThese matrices cannot be added :(");
                            }
                            break;
                        case 2:
                            try
                            {
                                matrix3 = matrix1 - matrix2;
                                Console.WriteLine("The result of substracting from matrix");
                                MatrixFromConsole.PrintMatrix(matrix1);
                                Console.WriteLine("   of matrix");
                                MatrixFromConsole.PrintMatrix(matrix2);
                                Console.WriteLine("     is matrix");
                                MatrixFromConsole.PrintMatrix(matrix3);
                            }
                            catch (Exception)
                            {
                                Console.WriteLine("\nThese matrices cannot be substract :(");
                            }
                            break;
                        case 4:
                            try
                            {
                                matrix3 = matrix1 * matrix2;
                                Console.WriteLine("The result of multiplying matrix");
                                MatrixFromConsole.PrintMatrix(matrix1);
                                Console.WriteLine("   and matrix");
                                MatrixFromConsole.PrintMatrix(matrix2);
                                Console.WriteLine("     is matrix");
                                MatrixFromConsole.PrintMatrix(matrix3);
                            }
                            catch (Exception)
                            {
                                Console.WriteLine("\nThese matrices cannot be multiplied :(");
                            }
                            break;
                    }
                }
                else if (ans != 6)                          //операции с одной матрицей
                {
                    matrix1 = new Matrix(MatrixFromConsole.GetNewMatrix());
                    Console.Clear();

                    switch (ans)
                    {
                        case 3:
                            {
                                int k = 0;
                                bool tmp = false;

                                do
                                {
                                    try
                                    {
                                        Console.Write("\nEnter the number by which you want to multiply the matrix\nk = ");
                                        k = int.Parse(Console.ReadLine());
                                        tmp = true;
                                    }
                                    catch (Exception)
                                    {
                                        tmp = false;
                                        Console.WriteLine("Wrong input! Try again, please :)");
                                    }
                                } while (!tmp);

                                matrix3 = Matrix.MatrixMultiplicationByNumber(matrix1, k); Console.Clear();
                                Console.WriteLine("The result of multiplying matrix");
                                MatrixFromConsole.PrintMatrix(matrix1);
                                Console.WriteLine("   by a nummber {0}", k);
                                Console.WriteLine("     is matrix");
                                MatrixFromConsole.PrintMatrix(matrix3);
                                break;
                            }
                        case 5:
                            try
                            {
                                matrix3 = Matrix.GetTransposeMatrix(matrix1);
                                Console.WriteLine("The result of transposing matrix");
                                MatrixFromConsole.PrintMatrix(matrix1);
                                Console.WriteLine("     is matrix");
                                MatrixFromConsole.PrintMatrix(matrix3);
                            }
                            catch (Exception)
                            {
                                Console.WriteLine("This function is available only for square matrices :(");
                            }
                            break;
                    }
                }
                else
                    Environment.Exit(0);
            }
        }
    }
}
