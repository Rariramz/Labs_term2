using System;
using System.Collections.Generic;

namespace Students
{
    class Artist : Student, ICreator, ICareerMac
    {
        public Artist(GetString method) : base(method)
        {
            Marks = new Subjects();
            SessionMarks = new List<int>();
            SetListOfMasterpieces();
        }

        override public List<int> SessionMarks { get; protected set; }
        private struct Subjects
        {
            public int GraphicArts, Design, Painting, Drawing, Sculpture;
        }
        Subjects Marks;

        private enum GrantsList
        {
            None = 0,
            Low = 77,
            Medium = 84,
            High = 100,
            Elevated = 115
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
                        Marks.GraphicArts = random.Next(0, 5);
                        Marks.Design = random.Next(0, 5);
                        Marks.Painting = random.Next(0, 5);
                        Marks.Drawing = random.Next(0, 5);
                        Marks.Sculpture = random.Next(0, 5);
                        break;
                    }
                case PerformanceList.Satisfactory:
                    {
                        Marks.GraphicArts = random.Next(4, 7);
                        Marks.Design = random.Next(4, 7);
                        Marks.Painting = random.Next(4, 7);
                        Marks.Drawing = random.Next(4, 7);
                        Marks.Sculpture = random.Next(4, 7);
                        break;
                    }
                case PerformanceList.Good:
                    {
                        Marks.GraphicArts = random.Next(6, 10);
                        Marks.Design = random.Next(6, 10);
                        Marks.Painting = random.Next(6, 10);
                        Marks.Drawing = random.Next(6, 10);
                        Marks.Sculpture = random.Next(6, 10);
                        break;
                    }
                case PerformanceList.Excellent:
                    {
                        Marks.GraphicArts = random.Next(9, 11);
                        Marks.Design = random.Next(9, 11);
                        Marks.Painting = random.Next(9, 11);
                        Marks.Drawing = random.Next(9, 11);
                        Marks.Sculpture = random.Next(9, 11);
                        break;
                    }
                default:
                    {
                        GetExpelled();     //Успеваемость - none,
                        break;            //студент не был допущен к сессии
                    }
            }
            if (Marks.GraphicArts < 4 || Marks.Design < 4 ||
                Marks.Painting < 4 || Marks.Drawing < 4 || Marks.Sculpture < 4)
            {
                Retake();
            }
            else
            {
                SessionMarks.Add(Marks.GraphicArts);
                SessionMarks.Add(Marks.Design);
                SessionMarks.Add(Marks.Painting);
                SessionMarks.Add(Marks.Drawing);
                SessionMarks.Add(Marks.Sculpture);

                CallMessageSent($"------- {Name} сдал сессию с отметками {Marks.GraphicArts}, {Marks.Design}," +
                    $" {Marks.Painting}, {Marks.Sculpture}.");

                UpdateAveragePoint();
                SetGrants();
            }
        }

        override public int Study()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            int Mark = 0;
            if (Mentality == MentalityKinds.Artistic)
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
            return base.ToString(format) + "\n" + "Artist";
        }

        /* -------------------------- ICreator -------------------------- */
        private List<string> Masterpieces { get; set; }
        private void SetListOfMasterpieces()
        {
            Masterpieces = new List<string>()
            {
                "Mona Lisa", "Girl with a Pearl Earring",
                "The Birth of Venus", "The Starry Night",
                "The Scream", "The Arnolfini Portrait",
                "The Garden of Earthly Delights",
                "The Creation Of Adam", "The Ninth Wave",
                "Napoleon Crossing The Alps",
                "The Liberty Leading The People",
                "The Triumph Of Galatea",
                "The Wanderer Above The Sea Of Fog",
                "The Last Supper", "Flaming June",
                "Saturn Devouring His Son",
                "A Friend In Need"
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

            CallMessageSent($"------- {Name} потерпел фиаско :(" +
                $"\n...и решил попробовать себя в другом направлении :)");

            WorkInMac();
        } 

        public void Success()
        {
            IsHappy = true;

            CallMessageSent($"------- {Name} прославился :)");
        }

        /* ----------------------- ICareerMac ----------------------- */
        public void WorkInMac()
        {
            IsHappy = false;

            CallMessageSent($"------- {Name} получил ценный экзистенциальный опыт работы в Маке :)");
        }
    }
}
