using System;
using System.Diagnostics;
using System.IO;

namespace ConsoleApplication1
{
    class Program
    {
        static void Main(string[] args)
        {
            long start = Stopwatch.GetTimestamp();

            Process sgl = new Process();
            sgl.StartInfo.FileName = "C:/Users/labadmin/Desktop/HelloSGLX-win/HelloSGLX.exe";
            sgl.StartInfo.Arguments = "-host=127.0.0.1 -cmd=getVersion";
            sgl.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
            sgl.StartInfo.UseShellExecute = false;
            sgl.StartInfo.RedirectStandardOutput = true;
            sgl.StartInfo.RedirectStandardError = true;
            sgl.Start();

            StreamReader rdr = sgl.StandardOutput;
            string result = rdr.ReadToEnd().Trim();

            // Output result can next be split, e.g.:
            // string[] parts = result.split('\n');
            // And applicable parts can be converted to numbers, e.g.:
            // double d = Convert.ToDouble(parts[0]);

            Console.WriteLine("[["+result+"]]");
            sgl.WaitForExit();

            long end = Stopwatch.GetTimestamp();
            Console.WriteLine("millis {0}", (end - start)/10000);
        }
    }
}


