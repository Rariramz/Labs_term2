using System;

namespace Students
{
    class Program
    {
        static void Main(string[] args)
        {
            Human.MessageSent += (obj, message) => Console.WriteLine(message);

            bool Again = true;
            while (Again)
            {
                Console.Clear();
                Console.WriteLine("------------ ~ Создадим первого студента ~ ------------");
                Programmer first = new Programmer(Console.ReadLine);

                if (!first.IsAlive) //а вдруг Вы решили испортить сюжет :)
                    first.Resurrect();
                //Теперь дадим возможность случиться некоторым событиям..
                first.SetPerformance();
                first.PassSession();
                first.GetSick();
                if (!first.IsAlive) //если рандом сыграл плохую шутку
                    first.Resurrect();
                first.GetWell();
                ICreator master1 = first;
                master1.CreateMasterpiece();
                Console.WriteLine("\n----------- ~ Информация о первом студенте ~ ----------");
                Console.WriteLine(first.ToString("Main"));
                Console.WriteLine(first.ToString("State"));

                Console.WriteLine("\n------------ ~ Создадим второго студента ~ ------------");
                Artist second = new Artist(Console.ReadLine);
                if (!first.IsAlive)
                    first.Resurrect();
                //Некоторые события снова случаются
                second.GetSick();
                if (!first.IsAlive)
                    first.Resurrect();
                second.GetWell();
                second.SetPerformance();
                second.PassSession();
                ICreator master2 = second;
                master2.CreateMasterpiece();
                Console.WriteLine("\n------------ ~ Информация о втором студенте ~ -----------");
                Console.WriteLine(second.ToString("Main"));
                Console.WriteLine(second.ToString("State"));

                Console.WriteLine("\n-------------- ~ Семейная пара, например ~ --------------");
                try
                {
                    first.Wedding(second);
                    Human child = new Human(true, Console.ReadLine);
                    first.AddChild(child);

                    Console.Clear();
                    Console.WriteLine("\n---------------- ~ Информация о ребенке ~ ---------------");
                    Console.WriteLine(child.ToString("All"));

                    Console.WriteLine("\n------------ ~ Информация о первом родителе ~ -----------");
                    Console.WriteLine(first.ToString("All"));

                    Console.WriteLine("\n------------ ~ Информация о втором родителе ~ -----------");
                    Console.WriteLine(second.ToString("All"));

                    /*Console.WriteLine("\n-------- ~ Накрутим ребенку немного годиков... ~ --------");
                    for (int i = 0; i < 120; i++)
                    {
                        if (child.IsAlive)       //таким нехитрым способом можем увидеть, 
                            child.Birthday();   //сколько лет предначертано было пожить этому человеку.
                    }
                    child.Resurrect(); //...ну увидели и хватит :)*/
                }
                catch (Exception)
                {
                    if (first.Gender == second.Gender)
                        Console.WriteLine("\n--------- ~ Эх, у Вас люди пола одинакового :/ ~ --------");
                    if (first.IsMarried || second.IsMarried)
                        Console.WriteLine("\n------------ ~ Кто-то из них уже был женат ~ ------------");
                }

                Console.WriteLine("\n\n\t\tПопробуете снова? Нажмите +, если \"Да\"");
                char ans;
                if (char.TryParse(Console.ReadLine(), out ans) && ans == '+')
                    Again = true;
                else
                    Again = false;
            }
        }
    }
}
