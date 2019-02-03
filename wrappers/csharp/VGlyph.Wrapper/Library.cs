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

        /// <summary>
        /// Check of compatible library
        /// </summary>
        /// <param name="version">Version of 'compile time' library</param> 
        /// <returns>Return true is runtime library is compatible</returns>
        /// <exception cref="ArgumentNullException">Argument <paramref name="version"/> is null</exception>
        public static bool IsVersionCompatible(Version version)
        {
            if (version == null)
                throw new ArgumentNullException(nameof(version));

            return Import.IsVersionCompatible(version.Version32);
        }
    }
}
