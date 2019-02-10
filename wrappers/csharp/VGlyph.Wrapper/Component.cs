namespace VGlyph
{
    /// <summary>
    /// Defines components for color channels.
    /// </summary>
    public enum Component
    {
        /// <summary>
        /// Write 0 in channel
        /// </summary>
        Zero,

        /// <summary>
        /// Write 1 in channel
        /// </summary>
        One,

        /// <summary>
        /// Write red componet in channel
        /// </summary>
        Red,

        /// <summary>
        /// Write green componet in channel
        /// </summary>
        Green,

        /// <summary>
        /// Write blue componet in channel
        /// </summary>
        Blue,

        /// <summary>
        /// Write alpha componet in channel
        /// </summary>
        Alpha
    }

    internal static class ComponentExtensions
    {
        public static Import.Component GetUnmanagedComponent(this Component component)
            => (Import.Component)component;
    }
}
