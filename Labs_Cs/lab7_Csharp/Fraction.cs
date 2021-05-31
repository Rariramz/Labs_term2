using System;
using System.Text.RegularExpressions;

namespace lab7_Csharp
{
    class Fraction : IComparable<Fraction>, IFormattable
    {
        public int Numerator { get => n; set => SetNumerator(value); }
        public int Denominator { get => m; set => SetDenominator(value); }

        int n, m;

        public Fraction()
        {

        }

        public Fraction(int n, int m)
        {
            Numerator = n;
            Denominator = m;
        }

        void SetNumerator(int n)
        {
            this.n = n;
            Reduce();
        }

        void SetDenominator(int m)
        {
            if (m == 0)
                throw new ArgumentException("This denominator isn't correct :(");
            if (m < 0)
            {
                n *= -1;
                m *= -1;
            }

            this.m = m;
            Reduce();
        }

        public override bool Equals(object obj)
        {
            return obj is Fraction fraction &&
                   n == fraction.n &&
                   m == fraction.m;
        }

        public int CompareTo(Fraction f)
        {
            int lcm = LCM(this.m, f.m);
            int n1 = this.n * (lcm / this.m);
            int n2 = f.n * (lcm / f.m);

            return n1.CompareTo(n2);
        }

        public string ToString(string format, IFormatProvider provider = null)
        {
            if (format.ToUpper() == "N.M")
            {
                return ((double)n / m).ToString();
            }
            else if (format.ToUpper() == "N/M")
            {
                return n + "/" + m;
            }
            else
            {
                throw new Exception("\nThis format is not available :(");
            }
        }

        static int GCD(int n, int m) //greatest common divisor
        {
            if (n > m)
                (n, m) = (m, n);

            while (m != 0)
            {
                n %= m;
                (n, m) = (m, n);
            }
            return Math.Abs(n);
        }

        static int LCM(int n, int m) //least common multiple
        {
            return (n * m) / GCD(n, m);
        }

        void Reduce()
        {
            if (n != 0 && m != 0)
            {
                int gcd = GCD(n, m);
                n /= gcd;
                m /= gcd;
            }
        }

        public static Fraction operator +(Fraction f1, Fraction f2)
        {
            int n, m;

            m = LCM(f1.m, f2.m);
            n = f1.n * (m / f1.m) + f2.n * (m / f2.m);

            return new Fraction(n, m);
        }

        public static Fraction operator -(Fraction f)
        {
            return new Fraction(-f.n, f.m);
        }

        public static Fraction operator -(Fraction f1, Fraction f2)
        {
            return f1 + (-f2);
        }

        public static Fraction operator *(Fraction f1, Fraction f2)
        {
            return new Fraction(f1.n * f2.n, f1.m * f2.m);
        }

        public static Fraction operator /(Fraction f1, Fraction f2)
        {
            return new Fraction(f1.n * f2.m, f1.m * f2.n);
        }

        public static bool operator >(Fraction f1, Fraction f2)
        {
            return f1.CompareTo(f2) == 1;
        }

        public static bool operator <(Fraction f1, Fraction f2)
        {
            return f1.CompareTo(f2) == -1;
        }

        public static bool operator ==(Fraction f1, Fraction f2)
        {
            return f1.CompareTo(f2) == 0;
        }

        public static bool operator !=(Fraction f1, Fraction f2)
        {
            return f1.CompareTo(f2) != 0;
        }

        public static bool operator >=(Fraction f1, Fraction f2)
        {
            return f1.CompareTo(f2) != -1;
        }

        public static bool operator <=(Fraction f1, Fraction f2)
        {
            return f1.CompareTo(f2) != 1;
        }

        public static Fraction Parse(string str)
        {
            Regex pattern1 = new Regex(@"^(-?\d*)[\.|,](\d*)$");
            Regex pattern2 = new Regex(@"^(-?\d*)\/(\d*)$");

            if (pattern1.IsMatch(str))
            {
                Match val = pattern1.Match(str);
                int a = BinPow(10, val.Groups[2].Value.Length);
                return new Fraction(int.Parse(val.Groups[1].Value) * a + int.Parse(val.Groups[2].Value), a);
            }
            else if (pattern2.IsMatch(str))
            {
                Match val = pattern2.Match(str);
                return new Fraction(int.Parse(val.Groups[1].Value), int.Parse(val.Groups[2].Value));
            }
            else
            {
                throw new Exception("\nWrong format :(");
            }
        }

        public static explicit operator int(Fraction f)
        {
            return f.n / f.m;
        }

        public static explicit operator double(Fraction f)
        {
            return (double)f.n / f.m;
        }

        public static int BinPow(int x, int n)
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

