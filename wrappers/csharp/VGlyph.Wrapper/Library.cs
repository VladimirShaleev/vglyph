using System;

[assembly: CLSCompliant(true)]

namespace VGlyph
{
    /// <summary>
    /// Infromation of library
    /// </summary>
    public static class Library
    {
        /// <summary>
        /// Version of library
        /// </summary>
        public static Version Version => new Version(Import.Version());
    }
}
