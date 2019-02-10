namespace VGlyph
{
    /// <summary>
    /// Packaging bytes
    /// </summary>
    public class PackagingBytes
    {
        /// <summary>
        /// Byte count per pixel
        /// </summary>
        public int ByteCount { get; set; }

        /// <summary>
        /// Defines byte order
        /// </summary>
        public Endianness Endianness { get; set; }
    }
}
