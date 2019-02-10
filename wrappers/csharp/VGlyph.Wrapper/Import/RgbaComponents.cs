using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct RgbaComponents
    {
        public Component r;
        public Component g;
        public Component b;
        public Component a;
    }
}
