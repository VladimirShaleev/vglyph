using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct Color
    {
        public double red;
        public double green;
        public double blue;
        public double alpha;
    }
}
