using System;
using System.Collections.Generic;

namespace Students
{
    class Human : IComparable<Human>, IFormattable
    {
        // Events ----------------------------------------------------------------------

        public static event EventHandler<string> MessageSent; //Message sent

        public delegate string GetString();
        public GetString GetLine;

        // -----------------------------------------------------------------------------

        public Human(GetString method)
        {
            GetLine = method;
            random = new Random();

            SetCharacter();
        }

        public void CallMessageSent(string message)
        {
            MessageSent?.Invoke(this, message);
        }

        public string CallGetLine()
        {
            return GetLine();
        }

        public Human(bool birth, GetString method)
        {
            GetLine = method;
            random = new Random();

            if (birth)
            {
                MessageSent?.Invoke(this, "------- Человек родился!");
                IsHappy = true;
                IsDiseased = false;
                Birthday();
            }
        }

        protected Random random;

        public string Surname { get; private set; }
        public string Name { get; private set; }
        public int Age { get; protected set; }
        public enum Genders
        {
            Man,
            Woman
        }
        public Genders Gender { get; set; }

        public enum MentalityKinds
        {
            Humanitarian,
            Mathematical,
            Artistic,
            Practical
        }
        public MentalityKinds Mentality { get; set; }

        public Human Mother { get; set; }
        public Human Father { get; set; }
        public bool IsMarried { get; private set; }  // Wedding
        public Human Partner { get; private set; }
        public List<Human> Children = new List<Human>();

        public bool IsAlive { get; private set; } // Birthday & Die
        public bool IsDiseased { get; private set; } // GetSick & GetWell
        public bool IsTalented { get; private set; } // Birthday
        public bool IsHappy { get; protected set; }

        public void SetNameAndSurname()
        {
            MessageSent?.Invoke(this, "\tФамилия:"); //Фамилия
            Surname = GetLine();
            MessageSent?.Invoke(this, "\tИмя:"); //Имя
            Name = GetLine();
        }

        virtual public void SetAge()
        {
            MessageSent?.Invoke(this, "\tВозраст:"); //Возраст
            int age;
            while (!(int.TryParse(GetLine(), out age) && age >= 1 && age <= 120))
                MessageSent?.Invoke(this, "Wrong input! Try again :)");
            Age = age;
        }

        public void SetCharacter()
        {
            MessageSent?.Invoke(this, "------- Добавьте нового персонажа:");
            SetNameAndSurname();
            SetAge();

            char ans;
            int num;
            MessageSent?.Invoke(this, "\tКакого этот человек пола? 1 - Мужской, 2 - Женский"); //Пол
            while (!(int.TryParse(GetLine(), out num) && (num >= 1 && num <= 2)))
                MessageSent?.Invoke(this, "Wrong input! Try again :)");
                Gender = (Genders)(num - 1);

            MessageSent?.Invoke(this, "\tЭтот человек жив? +, если \"Да\", иначе \"Нет\""); //
            while (!char.TryParse(GetLine(), out ans))
                MessageSent?.Invoke(this, "Wrong input! Try again :)");
            IsAlive = ans == '+';

            if (Age >= 18)
            {
                MessageSent?.Invoke(this, "\tЭтот человек женат/замужем? +, если \"Да\", иначе \"Нет\""); //Женат/замужем
                while (!char.TryParse(GetLine(), out ans))
                    MessageSent?.Invoke(this, "Wrong input! Try again :)");
                IsMarried = ans == '+';
            }
            else
                IsMarried = false;

            MessageSent?.Invoke(this, "\tЭтот человек здоров? +, если \"Да\", иначе \"Нет\""); //Здоров/болен
            while (!char.TryParse(GetLine(), out ans))
                MessageSent?.Invoke(this, "Wrong input! Try again :)");
            IsDiseased = ans == '-';

            MessageSent?.Invoke(this, "\tЭтот человек талантлив? +, если \"Да\", иначе \"Нет\""); //
            while (!char.TryParse(GetLine(), out ans))
                MessageSent?.Invoke(this, "Wrong input! Try again :)");
            IsTalented = ans == '+';

            MessageSent?.Invoke(this, "\tЭтот человек счастлив? +, если \"Да\", иначе \"Нет\""); //Счастлив/несчастен
            while (!char.TryParse(GetLine(), out ans))
                MessageSent?.Invoke(this, "Wrong input! Try again :)");
            IsHappy = ans == '+';

            MessageSent?.Invoke(this, "\tКакой склад ума у этого человека?\n" +
                "\t1 - Humanitarian, 2 - Mathematical, 3 - Artistic, 4 - Practical");
            while (!(int.TryParse(GetLine(), out num) && (num >= 1 && num <= 4)))
                MessageSent?.Invoke(this, "Wrong input! Try again :)");
            Mentality = (MentalityKinds)(num - 1);
        }

        public void Birthday()
        {
            IsAlive = true;
            Age++;
            MessageSent?.Invoke(this, $"------- Человеку {Name} исполнилось {Age}. С Днём рождения!");

            if (Age == 1)
            {
                Gender = (Genders)(random.Next(0, 2));
                Mentality = (MentalityKinds)(random.Next(0, 4));
                IsTalented = random.Next(0, 2) == 1;
                MessageSent?.Invoke(this, $"------- Это {(Gender == Genders.Man ? "мальчик" : "девочка")}!");
                SetNameAndSurname();
            }

            if (random.Next(0, 120 - Age) == 0) //С возрастом вероятность смерти повышается
                Die();

            if (Partner != null)
            {
                if (random.Next(0,2) == 1)
                {
                    Partner.Die(); // ..и умереть в один день =)
                    IsHappy = true;
                    Partner.IsHappy = true;
                }
            }
        }

        public void Die()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is already dead!");

            IsAlive = false;
            MessageSent?.Invoke(this, $"------- {Name} умер :(");
        }

        public void Resurrect()
        {
            IsAlive = true; //воскресить
            MessageSent?.Invoke(this, $"------- {Name} был воскрешён");
        }

        public void GetSick()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is dead.");

            IsDiseased = true;
            IsHappy = false;
            MessageSent?.Invoke(this, $"------- {Name} болен :(");

            if (random.Next(0, 10) == 1 && IsDiseased)
                Die();
        }

        virtual public void GetWell()
        {
            if (!(IsAlive == true))
                throw new Exception("This one is dead.");

            IsDiseased = false;
            MessageSent?.Invoke(this, $"------- {Name}, с выздоровлением!");
        }

        public void Wedding(Human partner)
        {
            if (Gender == partner.Gender)
                throw new Exception("Genders are equal!");
            if (!(IsAlive == true && partner.IsAlive == true))
                throw new Exception("Somebody is dead!");
            if (Age < 18 || partner.Age < 18)
                throw new Exception("These people are too young for wedding");
            if (IsMarried || partner.IsMarried)
                throw new Exception("Somebody is already married");

            IsMarried = true;
            partner.IsMarried = true;
            Partner = partner;
            partner.Partner = this;
            MessageSent?.Invoke(this, $"------- {Name} и {partner.Name} теперь женаты");
        }

        public void SetParent(Human human)
        {
            if (!(IsAlive == true && human.IsAlive == true))
                throw new Exception("Somebody is dead!");

            if (human.Gender == Genders.Man)
                Father = human;
            else
                Mother = human;
            MessageSent?.Invoke(this, $"------- {human.Name} - {(human.Gender == Genders.Man ? "папа" : "мама")} ребёнка {Name}");

            if (!human.Children.Contains(this))
                human.AddChild(this);
        }

        public void AddChild(Human human)
        {
            if (!(IsAlive == true && human.IsAlive == true))
                throw new Exception("Somebody is dead!");

            if (!Children.Contains(this))
            {
                Children.Add(human);
                human.SetParent(this);
            }

            if (IsMarried == true)
            {
                if (!Partner.Children.Contains(this))
                {
                    Partner.Children.Add(human);
                    human.SetParent(Partner);
                }
            }

            MessageSent?.Invoke(this, $"------- {human.Name} - ребёнок пары {Name} и {Partner.Name}");
        }

        public override int GetHashCode() => base.GetHashCode();

        public int CompareTo(Human other)
        {
            if (Age > other.Age)
                return 1;
            else if (Age < other.Age)
                return -1;
            else
                return 0;
        }

        virtual public string ToString(string format, IFormatProvider formatProvider = null)
        {
            string name = $"{Surname} {Name}";
            string main = $"Фамилия:{Surname}\nИмя:\t{Name}\nВозраст:{Age}\nПол:\t{Gender}";
            string state = $"{Mentality}\n{(IsTalented ? "-Талантлив" : "-Не одарен талантом")}" +
                $"\n{(IsHappy ? "-Счастлив" : "-Несчастен")}\n{(IsDiseased ? "-Болен" : "-Абсолютно здоров")}" +
                $"\n{(IsAlive ? "-Еще жив" : "-Уже умер")}\n{(IsMarried ? "-Состоит в браке" : "-Не состоит в браке")}";

            if (format == "All")
            {
                string parents = $"Мать:\t{(Mother != null ? Mother.ToString("Name") : "-")}" +
                    $"\nОтец:\t{(Father != null ? Father.ToString("Name") : "-")}";

                string partner = $"Партнер:{(Partner != null ? Partner.ToString("Name") : "-")}";

                string children = "Дети:\t";
                if (Children.Count == 0)
                    children += "-";
                else
                    foreach (Human h in Children)
                        children += h.ToString("Name") + "\t";

                return main + "\n" + parents + "\n" + partner + "\n" + children + "\n" + state;
            }
            if (format == "Name")
                return name;
            else
            if (format == "Main")
                return main;
            else
            if (format == "State")
                return state;
            else
                return "Wrong format";
        }
    }
}
