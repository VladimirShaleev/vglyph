namespace VGlyph
{
    /// <summary>
    /// Byte Alignment.
    /// </summary>
    public enum Alignment
    {
        /// <summary>
        /// Alignment to 1 byte boundary
        /// </summary>
        Align1 = 1,

        /// <summary>
        /// Alignment to 2 byte boundary
        /// </summary>
        Align2 = 2,

        /// <summary>
        /// Alignment to 4 byte boundary
        /// </summary>
        Align4 = 4,

        /// <summary>
        /// Alignment to 8 byte boundary
        /// </summary>
        Align8 = 8
    }

    internal static class AlignmentExtensions
    {
        public static Import.Alignment GetUnmanagedAlignment(this Alignment alignment)
            => (Import.Alignment)alignment;
    }
}
