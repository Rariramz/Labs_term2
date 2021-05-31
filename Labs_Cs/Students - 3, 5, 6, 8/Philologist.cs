using System;
using System.Collections.Generic;

namespace Students
{
    class Philologist : Student
    {
        public Philologist(GetString method) : base(method)
        {
            Marks = new Subjects();
            SessionMarks = new List<int>();
        }

        override public List<int> SessionMarks { get; protected set; }
        public struct Subjects
        {
            public int SocialScience, Language, History, Literature;
        }
        Subjects Marks;

        private enum GrantsList
        {
            None = 0,
            Low = 77,
            Medium = 93,
            High = 108,
            Elevated = 123
        }
        GrantsList Grants { get; set; }

        override public void PassSession()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            switch (Performance)
            {
                case PerformanceList.Unsatisfactory:
                    {
                        Marks.SocialScience = random.Next(0, 5);
                        Marks.Language = random.Next(0, 5);
                        Marks.History = random.Next(0, 5);
                        Marks.Literature = random.Next(0, 5);
                        break;
                    }
                case PerformanceList.Satisfactory:
                    {
                        Marks.SocialScience = random.Next(4, 7);
                        Marks.Language = random.Next(4, 7);
                        Marks.History = random.Next(4, 7);
                        Marks.Literature = random.Next(4, 7);
                        break;
                    }
                case PerformanceList.Good:
                    {
                        Marks.SocialScience = random.Next(6, 10);
                        Marks.Language = random.Next(6, 10);
                        Marks.History = random.Next(6, 10);
                        Marks.Literature = random.Next(6, 10);
                        break;
                    }
                case PerformanceList.Excellent:
                    {
                        Marks.SocialScience = random.Next(9, 11);
                        Marks.Language = random.Next(9, 11);
                        Marks.History = random.Next(9, 11);
                        Marks.Literature = random.Next(9, 11);
                        break;
                    }
                default:
                    {
                        GetExpelled();     //Успеваемость - none,
                        break;            //студент не был допущен к сессии
                    }
            }

            if (Marks.SocialScience < 4 || Marks.Language < 4 ||
                Marks.History < 4 || Marks.Literature < 4)
            {
                WorkInMac();
                Retake();
            }
            else
            {
                SessionMarks.Add(Marks.SocialScience);
                SessionMarks.Add(Marks.Language);
                SessionMarks.Add(Marks.History);
                SessionMarks.Add(Marks.Literature);

                CallMessageSent($"------- {Name} сдал сессию с отметками {Marks.SocialScience}," +
                    $" {Marks.Language}, {Marks.History}, {Marks.Literature}.");

                UpdateAveragePoint();
                SetGrants();
            }
        }

        override public int Study()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            int Mark = 0;
            if (Mentality == MentalityKinds.Humanitarian)
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

        override public int GetGrants() => (int)Grants;

        override public string ToString(string format, IFormatProvider formatProvider = null)
        {
            return base.ToString(format) + "\n" + "Philologist";
        }

        /* ----------------------- ICareerMac ----------------------- */
        public void WorkInMac()
        {
            IsHappy = false;

            CallMessageSent($"------- {Name} получил ценный экзистенциальный опыт работы в Маке :)");
        }
    }
}
