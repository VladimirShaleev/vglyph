namespace VGlyph
{
    /// <summary>
    /// Defines byte order.
    /// </summary>
    public enum Endianness
    {
        /// <summary>
        /// Use host byte order.
        /// </summary>
        Host,

        /// <summary>
        /// Use big-endian order.
        /// </summary>
        Big,

        /// <summary>
        /// Use little-endian order.
        /// </summary>
        Little,
    }

    internal static class EndiannessExtensions
    {
        public static Import.Endianness GetUnmanagedEndianness(this Endianness endianness)
            => (Import.Endianness)endianness;
    }
}
