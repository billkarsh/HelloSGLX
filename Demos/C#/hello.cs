using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            Console.WriteLine("[["+rdr.ReadToEnd().Trim()+"]]");
            sgl.WaitForExit();

            long end = Stopwatch.GetTimestamp();
            Console.WriteLine("millis {0}", (end - start)/10000);
        }
    }
}


