using System;
using System.Runtime.InteropServices;

/// <summary>
/// Wrapper class for C# function calls from the Scrutiny library
/// </summary>
/// <author>Ben Hoffman</author>
static class Scrutiny
{
    /// <summary>
    /// Initialize the Scrutiny library for use. This must be done before the use
    /// of any reporting functionality 
    /// </summary>
    /// <param name="aServerAddress">Address of the elasticsearch server</param>
    /// <param name="aServerPort">Port that elasticsearch is running on (Default is 9200)</param>
    [DllImport("Scrutiny.dll")]
    public static extern void InitLib(string aServerAddress, string aServerPort);

    /// <summary>
    /// Release the instance of Scrutiny, must be done at the end of using 
    /// the library or there will be memory leaks!
    /// </summary>
    [DllImport("Scrutiny.dll")]
    public static extern void Release();

    [DllImport("Scrutiny.dll")]
    public static extern int TestRequest();

    [DllImport("Scrutiny.dll")]
    public static extern void StartReport();

    [DllImport("Scrutiny.dll")]
    public static extern void SendReport();

    [DllImport("Scrutiny.dll")]
    public static extern void ReportFloat(string key, float aToStrFuncPtr);

    [DllImport("Scrutiny.dll")]
    public static extern void ReportCharacter(string key, string aToStrFuncPtr);

    [DllImport("Scrutiny.dll")]
    public static extern void ReportCustom(string key, IntPtr aToStrFuncPtr, IntPtr aObject);

    public delegate string CustomToStringDelegate(IntPtr value);
    
}