using System;
using System.Runtime.CompilerServices;
using VGlyph.Import;

[assembly: CLSCompliant(true)]
[assembly: InternalsVisibleTo("VGlyph.Wrapper.Test")]

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
        public static Version Version => new Version(Api.Version());

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

            return Api.IsVersionCompatible(version.Version32);
        }

        internal static object CreateObjectFromHandle(ObjectHandle handle)
        {
            if (handle == null)
                throw new ArgumentNullException(nameof(handle));

            using (var type = Surface.Type)
            {
                if (handle.IsCast(type))
                    return new Surface(handle);
            }

            using (var type = RgbaUintFormat.Type)
            {
                if (handle.IsCast(type))
                    return new RgbaUintFormat(handle);
            }

            using (var type = Face.Type)
            {
                if (handle.IsCast(type))
                    return new Face(handle);
            }

            using (var type = Glyph.Type)
            {
                if (handle.IsCast(type))
                    return new Glyph(handle);
            }

            using (var type = Figure.Type)
            {
                if (handle.IsCast(type))
                    return new Figure(handle);
            }

            throw new InvalidOperationException();
        }

        internal static T CreateObjectFromHandle<T>(ObjectHandle handle) where T : class
        {
            var obj = CreateObjectFromHandle(handle);

            if (!(obj is T result))
                throw new InvalidCastException();

            return result;
        }
    }
}
