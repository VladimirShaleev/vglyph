using System.Runtime.InteropServices;

namespace VGlyph.Import
{
    [StructLayout(LayoutKind.Sequential)]
    internal struct PackagingBytes
    {
        public uint byteCount;
        public Endianness endianness;
    }
}
