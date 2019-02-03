using System.Runtime.InteropServices;

namespace VGlyph
{
    internal static partial class Import
    {
        [DllImport(_library, EntryPoint = "vglyph_version")]
        public static extern uint Version();

        private const string _library =
#if WIN
            "vglyph.dll";
#else
            " ";
#endif
    }
}
