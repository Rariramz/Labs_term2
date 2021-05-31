using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace lab4_Csharp
{
    class Program
    {
        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int add(int a, int b);
        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int substract(int a, int b);
        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int multiply(int a, int b);
        [DllImport("Dll.dll", CallingConvention = CallingConvention.Cdecl)]
        static extern int divide(int a, int b);
        static void Main(string[] args)
        {
            int resAdd = add(5, 10);
            int resSubstract = substract(4, 7);
            int resMultiply = multiply(6, 7);
            int resDivide = divide(10, 3);

            Console.WriteLine("Addition\t5 + 10 = " + resAdd);
            Console.WriteLine("Subtraction\t4 - 7 = " + resSubstract);
            Console.WriteLine("Multiplication\t6 * 7 = " + resMultiply);
            Console.WriteLine("Division\t10 / 3 = " + resDivide);
        }
    }
}
