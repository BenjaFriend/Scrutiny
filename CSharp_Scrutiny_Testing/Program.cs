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
            return string.Format("Vector ( {0}, {1}, {2} )", x, y, z);
        }

        public static string CustomVectorString(IntPtr value)
        {
            GCHandle gch = GCHandle.FromIntPtr(value);
            Vector vec = (Vector)gch.Target;
            return vec.ToString();
        }
    }



    class Program
    {
        /** A pointer to the actual object implementation, because of Unity */
        //private static IntPtr ScrutinyInstance;

        public delegate string CustomToStringDelegate(IntPtr value);

        static void Main(string[] args)
        {
            // Create scrutiny
            //ScrutinyInstance = Scrutiny.LibWrapper.CreateScrutiny("127.0.0.1", "9200");
            Scrutiny.Init("127.0.0.1", "9200");

            //Console.WriteLine("Scrutiny : " + ScrutinyInstance);

            Vector testVec = new Vector();
            testVec.x = 1.5f;
            testVec.y = 2.5f;
            testVec.z = 3.5f;

            // Need to keep the delegate around so it doesnt get eaten by the GC
            CustomToStringDelegate myCustomToString = new CustomToStringDelegate(Vector.CustomVectorString);

            Scrutiny.StartReport();
            Scrutiny.ReportFloat("float_cs", 42.75f);

            GCHandle gch = GCHandle.Alloc(testVec);

            Scrutiny.ReportCustom(                
                "C# Delegate",
                Marshal.GetFunctionPointerForDelegate(myCustomToString),
                GCHandle.ToIntPtr(gch)
                );

            Scrutiny.ReportCharacter("Language", "C#");

            Scrutiny.SendReport();

            Console.WriteLine("Test vector: " + testVec.ToString());

            int r = Scrutiny.TestRequest();

            Console.WriteLine("From C++ Unmanaged Dll: " + r.ToString());

            Console.WriteLine("Finished reports!");
            gch.Free();
        }
  
    }

}