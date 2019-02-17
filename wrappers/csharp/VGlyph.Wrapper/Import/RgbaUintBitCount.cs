using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct RgbaUintBitCount
    {
        public byte r;
        public byte g;
        public byte b;
        public byte a;
    }
}
