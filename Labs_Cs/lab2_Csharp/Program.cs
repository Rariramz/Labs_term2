using System;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace lab2_Csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                int ans = 0;
                try
                {
                    Console.ForegroundColor = ConsoleColor.Cyan;
                    Console.WriteLine("\nВыберите номер задания:");
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.WriteLine("1. В заданной строке поменять порядок слов на обратный (слова разделены пробелами).");
                    Console.WriteLine("2. Дана строка. Найти в ней все заглавные буквы, не входящие в английский алфавит.");
                    Console.WriteLine("3. Дана строка, содержащая число с десятичной точкой. Преобразовать эту строку " +
                        "в число действительного типа\n(не пользуясь стандартным Parse/TryParse).");
                    Console.ForegroundColor = ConsoleColor.Cyan;
                    Console.Write("Номер:");
                    Console.ForegroundColor = ConsoleColor.Red;

                    ans = int.Parse(Console.ReadLine());
                    if (!(ans >= 1 && ans <= 3))
                    {
                        throw new Exception();
                    }
                }
                catch (Exception)
                {
                    Console.ForegroundColor = ConsoleColor.White;
                    Console.Clear();
                    Console.WriteLine("Такого номера нет. Попробуйте снова :)");
                }

                Console.ForegroundColor = ConsoleColor.White;
                switch (ans)
                {
                    case 1:
                        {
                            Console.Clear();
                            Console.WriteLine("\nВведите строку, в которой вы хотите поменять порядок слов на обратный.");
                            Console.WriteLine("Преобразованная строка:\n" + ReverseWordOrder(Console.ReadLine()));
                            break;
                        }
                    case 2:
                        {
                            Console.Clear();
                            Console.WriteLine("\nВведите строку, в которой нужно найти все заглавные буквы, не входящие в английский алфавит.");
                            char[] letters = FindNotEnglishUpLetters(Console.ReadLine());
                            Console.WriteLine("Результат:");
                            foreach (char letter in letters)
                                Console.Write(letter);
                            break;
                        }
                    case 3:
                        {
                            Console.Clear();
                            bool Done = false; //Если введенная строка НЕ представляет собой число с плавающей точкой,
                                              //пользователя просят повторить ввод
                            do
                            {
                                try
                                {
                                    Console.WriteLine("\nВведите строку, содержащую число с десятичной точкой.");
                                    string input = Console.ReadLine();

                                    Regex pattern = new Regex(@"^(-?\d*)[\.|,](\d*)$");
                                    if (pattern.IsMatch(input))
                                    {
                                        Match val = pattern.Match(input);
                                        Console.WriteLine("Строка, преобразованная в числодействительного типа: {0}",
                                        StringToRealDigit(input));
                                        Done = true;
                                    }
                                    else
                                    {
                                        throw new Exception("Wrong format");
                                    }
                                }
                                catch (Exception)
                                {
                                    Console.WriteLine("Введённая строка имеет неверный формат. Попробуйте ещё раз :)");
                                }
                            } while (!Done);
                            break;
                        }
                }
            }
        }

        static string ReverseWordOrder(string str)
        {
            string[] words = str.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            Array.Reverse(words);
            string result = String.Join(" ", words);
            return result;
        }

        static char[] FindNotEnglishUpLetters(string str)
        {
            char[] input = str.ToCharArray();
            List<char> result = new List<char>();
            for (int i = 0; i < input.Length; i++)
            {
                if (char.IsUpper(input[i]))
                    if (!(input[i] >= 'A' && input[i] <= 'Z'))
                    {
                        result.Add(input[i]);
                        result.Add(' ');
                    }
            }
            char[] Result = result.ToArray();
            return Result;
        }

        static double StringToRealDigit(string str)
        {
            bool isNegative = false;

            Regex pattern = new Regex(@"^(-?\d*)[\.|,](\d*)$");
            if (pattern.IsMatch(str))
            {
                Match val = pattern.Match(str);
                string BeforePoint = val.Groups[1].Value;
                string AfterPoint = val.Groups[2].Value;
                double sumOne = 0, sumSec = 0;

                if (BeforePoint[0] == '-')
                    isNegative = true;

                for (int i = (isNegative ? 1 : 0),
                    k = (isNegative ? BeforePoint.Length - 2 : BeforePoint.Length - 1);
                    i < BeforePoint.Length; i++, k--)
                {
                    char c = BeforePoint[i];
                    sumOne += (c - '0') * BinPow(10, k);
                }
                for (int i = 0; i < AfterPoint.Length; i++)
                {
                    char c = AfterPoint[i];
                    sumSec += (c - '0') * (double)1 / BinPow(10, (i + 1));
                }

                return isNegative ? -(sumOne + sumSec) : (sumOne + sumSec);
            }
            else
            {
                throw new Exception("Wrong format");
            }
        }

        static int BinPow(int x, int n)
        {
            if (n == 0)
                return 1;
            if (n % 2 == 1)
                return x * BinPow(x, n - 1);

            int a = BinPow(x, n / 2);
            return a * a;
        }

    }
}
