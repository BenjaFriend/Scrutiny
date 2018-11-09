using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace CSharp_Scrutiny_Testing
{

    /// <summary>
    /// A test class that holds some fake vector info
    /// </summary>
    class Vector
    {
        public float x;
        public float y;
        public float z;

        public override string ToString()
        {
            return string.Format( "Vector ( {0}, {1}, {2} )", x, y, z);
        }
    }


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

            Vector testVec = new Vector();
            testVec.x = 1.5f;
            testVec.y = 2.5f;
            testVec.z = 3.5f;

            Console.WriteLine( "Test vec: " + testVec.ToString() );

            int r = TestRequest(Scrutiny);

            Console.WriteLine("From C++ Unmanaged Dll: " + r.ToString());

            Console.WriteLine("Hello world from C#!");

        }
    }
}
