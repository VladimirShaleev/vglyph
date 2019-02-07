#if (WIN || WIN_X64 || WIN_X86)

using System;
using System.IO;
using System.Runtime.InteropServices;

namespace VGlyph
{
    internal static partial class Import
    {
        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string path);

        static Import()
        {
            var directory = Path.GetDirectoryName(typeof(Import).Assembly.Location);
            var folder = Environment.Is64BitProcess ? "x64" : "x86";
            var libraryPath = Path.Combine(directory, folder, "vglyph.dll");

            LoadLibrary(libraryPath);
        }
    }
}

#endif
