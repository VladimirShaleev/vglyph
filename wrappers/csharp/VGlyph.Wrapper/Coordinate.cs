namespace VGlyph
{
    /// <summary>
    /// Indicates how to shift the coordinate
    /// </summary>
    public enum Coordinate
    {
        /// <summary>
        /// Absolute coordinate
        /// </summary>
        Absolute,

        /// <summary>
        /// For the relative versions of the commands, all coordinate 
        /// values are relative from previous coordinate.
        /// </summary>
        Relative
    }
}
