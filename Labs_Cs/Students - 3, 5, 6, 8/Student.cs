using System;
using System.Collections.Generic;

namespace Students
{
    abstract class Student : Human, IComparable<Student>
    {
        public Student(GetString method) : base(method) //Создание персонажа
        {
            SetUniversity();
            SetDegree();

            if (Age < 17)
                SetAge();
        }
        override public void SetAge()
        {
            CallMessageSent("\tВозраст:");
            int age;
            while (!(int.TryParse(CallGetLine(), out age) && age >= 17 && age <= 120))
                CallMessageSent("\tЧеловек такого возраста не может быть студентом." +
                  " Может передумаете?)");
            Age = age;
        }

        public enum Universities
        {
            None,
            BSUIR,
            BSU,
            BNTU,
            BSEU,
            BSPU,
            BSMU,
            BSTU
        }
        public Universities University { get; set; }

        public enum Degrees
        {
            Undergraduate,
            Graduate,
            Postgraduate
        }
        public Degrees Degree { get; set; }

        public enum PerformanceList //успеваемость (для последующего расчета стипендии)
        {
            None,
            Unsatisfactory, //0-3
            Satisfactory,   //4-5
            Good,           //6-8
            Excellent       //9-10
        }
        public PerformanceList Performance { get; private set; } //SetPerformance(), GetLeave()[None]

        public double AveragePoint { get; private set; } //SetAveragePoint();
        public int NumberOfRetakes { get; private set; } //Retake()
        public bool IsExpelled { get; protected set; } //отчислен Retake(), GetExpelled(), GetBack()

        abstract public List<int> SessionMarks { get; protected set; } // PassSession() returns List<int> SessionMarks

        public void SetUniversity()
        {
            CallMessageSent("\tВыберите университет:\n\t1 - BSUIR, 2 - BSU, 3 - BNTU, 4 - BSEU," +
                " 5 - BSPU, 6 - BSMU, 7 - BSTU");
            int ans;
            while (!(int.TryParse(CallGetLine(), out ans) && (ans >= 1 && ans <= 7)))
                CallMessageSent("Wrong input! Try again :)");
            University = (Universities)ans;
        }

        public void SetDegree()
        {
            CallMessageSent("\tВыберите степень студента:\n\t1 - Undergraduate," +
                " 2 - Graduate, 3 - Postgraduate");
            int ans;
            while (!(int.TryParse(CallGetLine(), out ans) && (ans >= 1 && ans <= 3)))
                CallMessageSent("Wrong input! Try again :)");
            Degree = (Degrees)(ans - 1);
        }

        public void UpdateAveragePoint()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");
            if (SessionMarks.Count == 0)
                throw new Exception("Firstly this student mast pass session");

            double sum = 0;
            foreach (int mark in SessionMarks)
                sum += mark;
            AveragePoint = sum / SessionMarks.Count;

            CallMessageSent($"------- Средний балл студента {Name} обновлен и составляет {AveragePoint:F2}");
        }

        public void SetPerformance() //Study() возвращает int отметку. Сначала успеваемость
        {                           //считатется по отметкам, полученным в процессе учебы
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            for (int marksAmount = 0; marksAmount < 10; marksAmount++)
            {
                int mark = Study();
                switch (Performance)
                {
                    case PerformanceList.Unsatisfactory:
                        {
                            if (mark >= 5)
                                Performance = PerformanceList.Satisfactory;
                            else if (mark < 4)
                                Performance = PerformanceList.None;
                            break;
                        }
                    case PerformanceList.Satisfactory:
                        {
                            if (mark >= 8)
                                Performance = PerformanceList.Good;
                            else if (mark < 4)
                                Performance = PerformanceList.Unsatisfactory;
                            break;
                        }
                    case PerformanceList.Good:
                        {
                            if (mark == 10)
                                Performance = PerformanceList.Excellent;
                            else if (mark < 6)
                                Performance = PerformanceList.Satisfactory;
                            break;
                        }
                    case PerformanceList.Excellent:
                        {
                            if (mark < 9)
                                Performance = PerformanceList.Good;
                            break;
                        }
                    default:
                        {
                            Performance = PerformanceList.Unsatisfactory;
                            break;
                        }
                }
            }
            CallMessageSent($"------- {Name} упорно учился весь год и теперь его успеваемость:{Performance}");
        }

        public void Retake()
        {
            CallMessageSent($"------- {Name} схлопотал пересдачу :(");

            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            NumberOfRetakes++;
            if (NumberOfRetakes > 3)
            {
                GetExpelled();

                IsHappy = false;
            }
            else
                PassSession();
        }

        public void GetExpelled()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            IsExpelled = true;
            University = Universities.None;

            CallMessageSent($"------- {Name} отчислен.");
        }

        public void GetBack() //перепоступить
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            IsExpelled = false;
            SetUniversity();

            CallMessageSent($"------- {Name} снова стал студентом!");
        }
        
        public override string ToString(string format, IFormatProvider formatProvider = null)
        {
            if (format == "All" || format == "Main")
            {
                string add = $"Университет:\t{University}\nСтатус:\t{Degree}\n" +
                $"Средний балл:\t{AveragePoint:F2}\nСтипендия:\t{GetGrants()}";

                return base.ToString(format) + "\n" + add;
            }
            else
                return base.ToString(format);
        }

        abstract public int Study(); //нужен для SetPerformance()
        abstract public void PassSession(); //вызывет метод UpdateAveragePoint()
        abstract public void SetGrants(); //рассчитывает стипендию, вызывается в PassSession()
        abstract public int GetGrants();

        public int CompareTo(Student other)
        {
            if (AveragePoint > other.AveragePoint)
                return 1;
            else if (AveragePoint < other.AveragePoint)
                return -1;
            else
                return 0;
        }
    }
}
