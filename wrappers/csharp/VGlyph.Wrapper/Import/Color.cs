using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct Color
    {
        public double Red;
        public double Green;
        public double Blue;
        public double Alpha;
    }
}
