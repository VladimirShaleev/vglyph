using System.Runtime.InteropServices;

namespace VGlyph
{
    internal static partial class Import
    {
        [DllImport(_library, EntryPoint = "vglyph_version")]
        public static extern uint Version();
        
        [DllImport(_library, EntryPoint = "vglyph_is_version_compatible")]
        public static extern bool IsVersionCompatible(uint compileVersion);
        
        private const string _library =
#if WIN
            "vglyph.dll";
#else
            " ";
#endif
    }
}
