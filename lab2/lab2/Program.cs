using System;

namespace csStackCLS
{
    class Stack<T>
    {
        public Stack(string mSize)
        {
            MaxSize = Convert.ToInt32(mSize);
            ST = new T[MaxSize];
            Console.WriteLine("Создан стек!");
        }

        int MaxSize, top = 0;

        T[] ST;

        public void push(T c)
        {
            if (top < MaxSize)
            {
                ST[top] = c;
                top++;
            }
            else Console.WriteLine("Стек переполнен!");
        }

        public T pop()
        {
            if (top > 0)
            {
                top--;
                return ST[top];
            }

            else
            {
                Console.WriteLine("Стек пуст!");
                return default(T);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {

            // Stack[] sar = { null, null, null };
            Stack<string> vs;
            Console.WriteLine("Создать стек?");

            if (Console.ReadLine() == "да")
            {
                Console.WriteLine("какой глубины?");
                vs = new Stack<string>(Console.ReadLine());
            }
            else return;

            string s;

            do
            {
                Console.WriteLine("Что сделать?");
                s = Console.ReadLine();
                if (s == "заложить")
                {
                    Console.WriteLine("Что?");
                    vs.push(Console.ReadLine());
                };
                if (s == "достать")
                {
                    Console.WriteLine(vs.pop());
                };
            }
            while (s != "Х");
        }
    }
}