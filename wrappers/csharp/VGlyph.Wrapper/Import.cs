using System;
using System.IO;
using System.Runtime.InteropServices;

namespace VGlyph
{
    internal static class Import
    {
        [DllImport(_library, EntryPoint = "vglyph_version")]
        public static extern uint Version();

        [DllImport("kernel32.dll")]
        private static extern IntPtr LoadLibrary(string path);

        static Import()
        {
            var directory = Path.GetDirectoryName(typeof(Import).Assembly.Location);
            var folder = Environment.Is64BitProcess ? "x64" : "x86";
            var libraryPath = Path.Combine(directory, folder, "vglyph.dll");

            LoadLibrary(libraryPath);
        }

        private const string _library =
#if NET45
            "vglyph.dll";
#elif ANDROID
            "libvglyph.so";
#else
            " ";
#endif
    }

}
