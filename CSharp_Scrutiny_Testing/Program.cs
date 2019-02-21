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

        static void Main(string[] args)
        {
            // Libary initalizeation -------------------------
            // Create scrutiny, must be done before using the library
            Scrutiny.InitLib("127.0.0.1", "9200");

            // Test Connection -------------------------------------
            // Test request for making sure that you can communicate to your library
            int r = Scrutiny.TestRequest();

            // Reporting basic types --------------------------
            // To start generating an Elasticsearch report, call start report
            Scrutiny.StartReport();

            // Report and data that you want send to your server given a key and value
            Scrutiny.ReportCharacter("TestKey", "You can report string and other basic types like this");
            Scrutiny.ReportFloat("TestInt", 15);

            // When you have all the data in the report that you want, send it! 
            Scrutiny.SendReport();


            // Reporting non-basic types --------------------------
            Vector testVec = new Vector();
            testVec.x = 1.5f;
            testVec.y = 2.5f;
            testVec.z = 3.5f;

            // Need to keep the delegate around so it doesnt get eaten by the GC
            Scrutiny.CustomToStringDelegate myCustomToString = new Scrutiny.CustomToStringDelegate(Vector.CustomVectorString);

            Scrutiny.StartReport();

            // Get a pointer/ handle to your object to report
            GCHandle gch = GCHandle.Alloc(testVec);

            // Report the custom object
            Scrutiny.ReportCustom(  
                // Key, as normal
                "C# Delegate",
                // Basically gets a function pointer that is compatible with C/C++
                Marshal.GetFunctionPointerForDelegate(myCustomToString),    
                // Pointer to your object to report
                GCHandle.ToIntPtr(gch) 
                );

            // Of course, you can always write custom ToString methods to objects 
            // and use ReportCharacter instead. 

            // Finish report
            Scrutiny.SendReport();

            gch.Free(); // Free your pointers that you have created

            // Library cleanup -------------------------
            // Release the library to clean up memory that is used
            Scrutiny.Release();
        }
  
    }

}