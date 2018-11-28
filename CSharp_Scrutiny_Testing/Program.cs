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

    class LibWrapper
    {
        [DllImport("Scrutiny.dll")]
        public static extern IntPtr CreateScrutiny(string aServerAddress, string aServerPort);

        [DllImport("Scrutiny.dll")]
        public static extern void DestroyScrutiny(IntPtr obj);

        [DllImport("Scrutiny.dll")]
        public static extern int TestRequest(IntPtr obj);

        [DllImport("Scrutiny.dll")]
        public static extern void StartReport(IntPtr obj);

        [DllImport("Scrutiny.dll")]
        public static extern void SendReport(IntPtr obj);

        [DllImport("Scrutiny.dll")]
        public static extern void ReportFloat(IntPtr Impl, string key, float aToStrFuncPtr);

        [DllImport("Scrutiny.dll")]
        public static extern void ReportCharacter(IntPtr Impl, string key, string aToStrFuncPtr);

        [DllImport("Scrutiny.dll")]
        public static extern void ReportCustom(IntPtr Impl, string key, IntPtr aToStrFuncPtr, IntPtr aObject);

    }

    class Program
    {
        /** A pointer to the actual object implementation, because of Unity */
        private static IntPtr Scrutiny;

        public delegate string CustomToStringDelegate(IntPtr value);

        static void Main(string[] args)
        {
            // Create scrutiny
            Scrutiny = LibWrapper.CreateScrutiny("127.0.0.1", "9200");

            Console.WriteLine("Scrutiny : " + Scrutiny);

            Vector testVec = new Vector();
            testVec.x = 1.5f;
            testVec.y = 2.5f;
            testVec.z = 3.5f;

            // Need to keep the delegate around so it doesnt get eaten by the GC
            CustomToStringDelegate myCustomToString = new CustomToStringDelegate(Vector.CustomVectorString);

            LibWrapper.StartReport(Scrutiny);
            LibWrapper.ReportFloat(Scrutiny, "float_cs", 42.75f);

            GCHandle gch = GCHandle.Alloc(testVec);

            LibWrapper.ReportCustom(
                Scrutiny,
                "C# Delegate",
                Marshal.GetFunctionPointerForDelegate(myCustomToString),
                GCHandle.ToIntPtr(gch)
                );

            LibWrapper.SendReport(Scrutiny);

            Console.WriteLine("Test vector: " + testVec.ToString());

            int r = LibWrapper.TestRequest(Scrutiny);

            Console.WriteLine("From C++ Unmanaged Dll: " + r.ToString());

            Console.WriteLine("Finished reports!");
            gch.Free();
        }
  
    }

}