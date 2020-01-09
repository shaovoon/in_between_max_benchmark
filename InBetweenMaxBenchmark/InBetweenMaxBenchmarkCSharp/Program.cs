using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace InBetweenMaxBenchmarkCSharp
{
    class Fraction
    {
        public int numerator;
        public int denominator;
    }

    class Program
    {
        static Random random = new Random();

        // Generate a random number between two numbers  
        static public int GetRand()
        {
            return random.Next(0, 1000);
        }
        static void DisplayElapseTime(string title, TimeSpan ts)
        {
            // Format and display the TimeSpan value.
            string elapsedTime = String.Format("{0}{1:000}ms",
                ts.Seconds,
                ts.Milliseconds);
            Console.WriteLine(title + " timing: " + elapsedTime);
        }

        static void Main(string[] args)
        {
            const int MAX_LOOP = 1000000;
            int max_value = 280;
            int sum1 = 0;
            int sum2 = 0;
            int sum3 = 0;

            List<Fraction> list = new List<Fraction>();
            for (int i = 0; i < 1000; ++i)
            {
                Fraction pt = new Fraction();
                pt.numerator = GetRand();
                pt.denominator = 1000;
                list.Add(pt);
            }


            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            for (int i = 0; i < MAX_LOOP; ++i)
            {
                sum1 = 0;
                for (int j = 0; j < list.Count; ++j)
                {
                    Fraction frac = list[j];
                    int value = (int)(((float)frac.numerator / frac.denominator) * max_value);
                    sum1 += value;
                }
            }
            stopWatch.Stop();
            DisplayElapseTime("With float conversion", stopWatch.Elapsed);

            stopWatch = new Stopwatch();
            stopWatch.Start();
            for (int i = 0; i < MAX_LOOP; ++i)
            {
                sum2 = 0;
                for (int j = 0; j < list.Count; ++j)
                {
                    Fraction frac = list[j];
                    int value = max_value * frac.numerator / frac.denominator;
                    sum2 += value;
                }
            }
            stopWatch.Stop();
            DisplayElapseTime("Without float conversion", stopWatch.Elapsed);

            stopWatch = new Stopwatch();
            stopWatch.Start();
            for (int i = 0; i < MAX_LOOP; ++i)
            {
                sum3 = 0;
                for (int j = 0; j < list.Count; ++j)
                {
                    Fraction frac = list[j];
                    int value = max_value * frac.numerator / 1000;
                    sum3 += value;
                }
            }
            stopWatch.Stop();
            DisplayElapseTime("Without float conversion with constant divisor", stopWatch.Elapsed);

            Console.WriteLine("sum: {0}, {1}, {2}", sum1, sum2, sum3);
        }
    }
}
