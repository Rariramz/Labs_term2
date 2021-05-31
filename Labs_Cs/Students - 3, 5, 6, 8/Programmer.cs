using System;
using System.Collections.Generic;

namespace Students
{
    class Programmer : Student, ICreator
    {
        public Programmer(GetString method) : base(method)
        {
            Marks = new Subjects();
            SessionMarks = new List<int>();
            SetListOfMasterpieces();
        }

        override public List<int> SessionMarks { get; protected set; }

        private struct Subjects
        {
            public int Mathematics, Programming, Physics;
        }
        Subjects Marks;

        private enum GrantsList
        {
            None = 0,
            Low = 80,
            Medium = 96,
            High = 112,
            Elevated = 128
        }
        GrantsList Grants { get; set; }

        override public void PassSession() //По успеваемости, определенной в методе SetPerformance()
        {                                 //генерирует список отметок за сессию, после чего
            if (!(IsAlive == true))      //вызывает метод UpdateAveragePoint()
                throw new Exception("This one is already dead!");

            switch (Performance)
            {
                case PerformanceList.Unsatisfactory:
                    {
                        Marks.Mathematics = random.Next(0, 5);
                        Marks.Programming = random.Next(0, 5);
                        Marks.Physics = random.Next(0, 5);
                        break;
                    }
                case PerformanceList.Satisfactory:
                    {
                        Marks.Mathematics = random.Next(4, 7);
                        Marks.Programming = random.Next(4, 7);
                        Marks.Physics = random.Next(4, 7);
                        break;
                    }
                case PerformanceList.Good:
                    {
                        Marks.Mathematics = random.Next(6, 10);
                        Marks.Programming = random.Next(6, 10);
                        Marks.Physics = random.Next(6, 10);
                        break;
                    }
                case PerformanceList.Excellent:
                    {
                        Marks.Mathematics = random.Next(9, 11);
                        Marks.Programming = random.Next(9, 11);
                        Marks.Physics = random.Next(9, 11);
                        break;
                    }
                default:
                    {
                        GetExpelled();     //Успеваемость - none,
                        break;            //студент не был допущен к сессии
                    }
            }

            if (Marks.Mathematics < 4 || Marks.Programming < 4 || Marks.Physics < 4)
                Retake();
            else
            {
                SessionMarks.Add(Marks.Mathematics);
                SessionMarks.Add(Marks.Programming);
                SessionMarks.Add(Marks.Physics);


                CallMessageSent($"------- {Name} сдал сессию с отметками {Marks.Mathematics}," +
                    $" {Marks.Programming}, {Marks.Physics}");

                UpdateAveragePoint();
                SetGrants();
            }
        }

        override public int Study()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            int Mark = 0;
            if (Mentality == MentalityKinds.Mathematical)
                Mark += random.Next(7, 11);            
            else
                Mark += random.Next(0, 11);
            if (Mark != 10) Mark += IsTalented ? 1 : 0;

            CallMessageSent($"------- {Name} получил {Mark}.");

            return Mark;
        }

        override public void SetGrants()
        {
            switch (Performance)
            {
                case PerformanceList.Unsatisfactory:
                    Grants = GrantsList.Low;
                    break;
                case PerformanceList.Satisfactory:
                    Grants = GrantsList.Medium;
                    break;
                case PerformanceList.Good:
                    Grants = GrantsList.High;
                    break;
                case PerformanceList.Excellent:
                    Grants = GrantsList.Elevated;
                    break;
                default:
                    Grants = GrantsList.None;
                    break;
            }

            CallMessageSent($"------- Стипендия студента {Name} составляет {(int)Grants}");
        }

        override public string ToString(string format, IFormatProvider formatProvider = null)
        {
            return base.ToString(format) + "\n" + "Programmer";
        }

        override public int GetGrants() => (int)Grants;

        /* -------------------------- ICreator -------------------------- */
        private List<string> Masterpieces { get; set; }

        private void SetListOfMasterpieces()
        {
            Masterpieces = new List<string>()
            {
            "Linux", "TeX", "HTTP protocol", "TeX",
            "Java", "NEWS", "compiler for Pascal",
            "Borland Delphi", "Facebook", "C++",
            "BitTorrent protocol", "JavaScript"
            };
        }

        public string CreateMasterpiece()
        {
            int rand = random.Next(0, Masterpieces.Count);

            CallMessageSent($"------- {Name} только что создал шедевр: \"{Masterpieces[rand]}\"");

            if (random.Next(0, 2) == 1 || IsTalented)
                Success();
            else
                Fiasco();

            return Masterpieces[rand];
        }

        public void Fiasco()
        {
            IsHappy = false;

            CallMessageSent($"------- {Name} потерпел фиаско :(");
        }

        public void Success()
        {
            IsHappy = true;

            CallMessageSent($"------- {Name} прославился :)");
        }
    }
}
