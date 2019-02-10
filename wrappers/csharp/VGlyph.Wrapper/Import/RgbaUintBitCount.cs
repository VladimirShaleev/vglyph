using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct RgbaUintBitCount
    {
        public uint r;
        public uint g;
        public uint b;
        public uint a;
    }
}
