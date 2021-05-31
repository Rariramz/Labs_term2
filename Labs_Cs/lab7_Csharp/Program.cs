using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7_Csharp
{
    class Program
    {
        /*
        Необходимо разработать и протестировать класс для
        представления рационального числа, т.е.числа вида n/m, где n – целое, m – натуральное
        число.

         Реализовать в этом классе перекрытие математических операций и операций
        сравнения.

         Реализовать метод для представления объекта класса в виде строки в
        различных форматах.

         Реализовать метод для получения объекта класса по строковому
        представлению из разных форматов (по желанию использовать для этого регулярные
        выражения).

         Реализовать в классе стандартные интерфейсы для проверки двух объектов
        на равенство и порядкового сравнения.

         Перекрыть явные или неявные операторы
        преобразования к типам целых и действительных чисел.
        
         Рекомендуется обратить
        внимание на правильные шаблоны реализации этих методов и операций.
        */
        static void Main(string[] args)
        {
            Console.WriteLine("\n----------- ~ Math operations: ~ -----------");
            Fraction f1 = new Fraction(1, 2) + new Fraction(3, 4);
            Console.WriteLine("\t1/2 + 3/4 = {0}", f1.ToString("N/M"));
            Fraction f2 = new Fraction(5, 10) - new Fraction(12, 5);
            Console.WriteLine("\t5/10 - 12/5 = {0}", f2.ToString("N/M"));
            Fraction f3 = new Fraction(3, 4) * new Fraction(10, 3);
            Console.WriteLine("\t3/4 * 10/3 = {0}", f3.ToString("N/M"));
            Fraction f4 = new Fraction(9, 10) / new Fraction(16, 20);
            Console.WriteLine("\t9/10 / 16/20 = {0}", f4.ToString("N/M"));

            Console.WriteLine("\n-------- ~ Comparison operations: ~ --------");
            Console.WriteLine("\t2/7 > 1/8 : {0}", new Fraction(2, 7) > new Fraction(1, 8));
            Console.WriteLine("\t2/7 < 1/8 : {0}", new Fraction(2, 7) < new Fraction(1, 8));
            Console.WriteLine("\t1/2 <= 1/2 : {0}", new Fraction(1, 2) <= new Fraction(1, 2));
            Console.WriteLine("\t1/3 >= 1/2 : {0}", new Fraction(1, 3) >= new Fraction(1, 2));
            Console.WriteLine("\t1/-3 == -3/9 : {0}", new Fraction(1, -3) == new Fraction(-3, 9));
            Console.WriteLine("\t1/-3 != -1/-3 : {0}", new Fraction(1, -3) != new Fraction(-1, -3));

            Console.WriteLine("\n---------- ~ Object from string ~ ----------");
            Fraction f5 = Fraction.Parse("2.22");
            Fraction f7 = Fraction.Parse("-3/2");

            Console.WriteLine("    ~ To string in different formats: ~    ");
            Console.WriteLine("\t\"2.22\" =[in format N/M] " + f5.ToString("N/M"));
            Console.WriteLine("\t\"-3/2\" =[in format n.M] " + f7.ToString("n.M"));

            Console.WriteLine("\n---- ~ Conversions to int and double: ~ ----");
            Console.WriteLine("\t(int)5/2 = " + (int)new Fraction(5, 2));
            Console.WriteLine("\t(double)5/2 = " + (double)new Fraction(5, 2));

            Console.WriteLine("\n-------- ~ Equals and CompareTo: ~ ---------");
            List<Fraction> fractions = new List<Fraction>();
            fractions.Add(new Fraction(1, 3));
            fractions.Add(new Fraction(1, 4));
            fractions.Add(new Fraction(-1, -3));
            fractions.Add(new Fraction(9, 5));
            fractions.Add(new Fraction(5, 6));
            fractions.Add(new Fraction(3, 8));

            Console.WriteLine("\t{0} = {1} : {2}", fractions[0].ToString("N/M"), fractions[1].ToString("N/M"),
                fractions[0].Equals(fractions[1]));
            Console.WriteLine("\t{0} = {1} : {2}\n", fractions[0].ToString("N/M"), fractions[2].ToString("N/M"),
                fractions[0].Equals(fractions[2]));

            Console.WriteLine("\t{0} CompareTo {1}  is {2}", fractions[0].ToString("N/M"), fractions[1].ToString("N/M"),
                fractions[0].CompareTo(fractions[1]));
            Console.WriteLine("\t{0} CompareTo {1}  is {2}", fractions[1].ToString("N/M"), fractions[0].ToString("N/M"),
                fractions[1].CompareTo(fractions[0]));
            Console.WriteLine("\t{0} CompareTo {1}  is {2}", fractions[0].ToString("N/M"), fractions[2].ToString("N/M"),
                fractions[0].CompareTo(fractions[2]));

            Console.WriteLine("\n ~ The list before Sort(): ~ ");
            foreach (Fraction f in fractions)
                Console.WriteLine("\t" + f.ToString("N/M"));

            Console.WriteLine("\n ~ The list after Sort(): ~ ");
            fractions.Sort();
            foreach (Fraction f in fractions)
                Console.WriteLine("\t" + f.ToString("N/M"));

            Console.WriteLine("--------------------------------------------\n");
        }
    }
}
