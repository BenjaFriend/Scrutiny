using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CSharp_Scrutiny_Testing
{

    class Program
    {

        [DllImport("Scrutiny.dll")]
        public static extern IntPtr CreateScrutiny(string aServerAddress, string aServerPort);

        [DllImport("Scrutiny.dll")]
        public static extern void DestroyScrutiny(IntPtr obj);


        // Straight From the c++ Dll (unmanaged)
        [DllImport("Scrutiny.dll")]
        public static extern int TestRequest(IntPtr obj);

        /// <summary>
        /// A pointer to the scrutiny object
        /// </summary>
        private static IntPtr Scrutiny;

        static void Main(string[] args)
        {
            // Create scrutiny
            Scrutiny = CreateScrutiny("127.0.0.1", "9200");            

            Console.WriteLine("Scrutiny : " + Scrutiny);

            int r = TestRequest(Scrutiny);

            Console.WriteLine("From C++ Unmanaged Dll: " + r.ToString());

            Console.WriteLine("Hello world from C#!");

        }
    }
}
