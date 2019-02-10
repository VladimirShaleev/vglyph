namespace VGlyph
{
    /// <summary>
    /// Multisampling values
    /// </summary>
    public enum Multisampling
    {
        /// <summary>
        /// Default sampling value
        /// </summary>
        Default = 0,

        /// <summary>
        /// One sample per pixel
        /// </summary>
        Sample1 = 1,

        /// <summary>
        /// Two samples per pixel
        /// </summary>
        Sample2 = 2,

        /// <summary>
        /// Four samples per pixel
        /// </summary>
        Sample4 = 4,

        /// <summary>
        /// Eight sample per pixel
        /// </summary>
        Sample8 = 8,

        /// <summary>
        /// Sixteen samples per pixel
        /// </summary>
        Sample16 = 16,

        /// <summary>
        /// Thirty two sample per pixel
        /// </summary>
        Sample32 = 32
    }

    internal static class MultisamplingExtensions
    {
        public static Import.Multisampling GetUnmanagedMultisampling(this Multisampling multisampling)
            => (Import.Multisampling)multisampling;
    }
}
