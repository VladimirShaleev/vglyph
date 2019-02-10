#if WIN

using System;
using System.IO;
using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    internal static partial class Api
    {
        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string path);

        static Api()
        {
            var directory = Path.GetDirectoryName(typeof(Api).Assembly.Location);
            var folder = Environment.Is64BitProcess ? "x64" : "x86";
            var libraryPath = Path.Combine(directory, folder, "vglyph.dll");

            LoadLibrary(libraryPath);
        }
    }
}

#endif
