using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class Scrutiny
{

    private class LibWrapper
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

    #region Fields

    /// <summary>
    /// The current Instance of Scrutiny
    /// </summary>
    private static IntPtr Instance;

    /// <summary>
    /// Message to send to users when they try and use Scrutiny without calling init
    /// </summary>
    private static string UninitalizedMessage =
        "You must initialize Scrutiny before using it! Call Scrutiny.Init";

    public delegate string CustomToStringDelegate(IntPtr value);

    #endregion

    public static IntPtr Init(string aServerAddress, string aServerPort)
    {       
        Instance = LibWrapper.CreateScrutiny(aServerAddress, aServerPort);
        
        return Instance;
    }

    /// <summary>
    /// Release the current Scrutiny Instance
    /// </summary>
    public static void Release()
    {
        if (Instance != null)
        {
            LibWrapper.DestroyScrutiny(Instance);
        }
    }

    /// <summary>
    /// Get the instance of scrutiny
    /// </summary>
    /// <returns>Pointer to the Scrutiny Instance</returns>
    public static IntPtr GetInstance()
    {
        return Instance;
    }

    /// <summary>
    /// Attempt to send a test report to Scrutiny to make sure that it 
    /// it all hooked up correctly. 
    /// </summary>
    public static int TestRequest()
    {
        Debug.Assert(Instance != null, UninitalizedMessage);

        return LibWrapper.TestRequest(Instance);
    }

    public static void StartReport()
    {
        Debug.Assert(Instance != null, UninitalizedMessage);

        LibWrapper.StartReport(Instance);
    }

    public static void SendReport()
    {
        Debug.Assert(Instance != null, UninitalizedMessage);

        LibWrapper.SendReport(Instance);
    }

    public static void ReportFloat(string key, float aVal)
    {
        Debug.Assert(Instance != null, UninitalizedMessage);

        LibWrapper.ReportFloat(Instance, key, aVal);
    }

    public static void ReportCharacter(string key, string aVal)
    {
        Debug.Assert(Instance != null, UninitalizedMessage);

        LibWrapper.ReportCharacter(Instance, key, aVal);
    }

    public static void ReportCustom(string key, IntPtr aToStrFuncPtr, IntPtr aObject)
    {
        Debug.Assert(Instance != null, UninitalizedMessage);

        LibWrapper.ReportCustom(Instance, key, aToStrFuncPtr, aObject);
    }
}

