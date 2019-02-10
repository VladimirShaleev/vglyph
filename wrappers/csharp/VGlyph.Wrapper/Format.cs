using System;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Format of <see cref="Surface"/>
    /// </summary>
    public abstract class Format : IDisposable
    {
        private bool _disposed;

        internal ObjectHandle Object { get; private set; }

        internal static ObjectHandle Type
            => Api.GetFormatType();

        /// <summary>
        /// Unmanaged handle of vglyph library
        /// </summary>
        protected IntPtr Handle
            => Object?.DangerousGetHandle() ?? IntPtr.Zero;

        /// <summary>
        /// Constructs new object <see cref="Format"/> for unmanaged handle
        /// </summary>
        /// <param name="handle">Unmanaged handle of vglyph library</param>
        /// <exception cref="ArgumentException">Invalid unmanaged handle</exception>
        protected Format(IntPtr handle) : this(new ObjectHandle(handle))
        {
        }

        internal Format(ObjectHandle handle)
        {
            Object = handle ?? throw new ArgumentNullException();

            if (Object.IsInvalid)
                throw new ArgumentException();

            Object.CheckState();
        }

        /// <summary>
        /// Get bits per pixel
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>   
        public int BitsPerPixel
        {
            get
            {
                CheckDisposed();
                var result = Api.FormatGetBitsPerPixel(Object);
                Object.CheckState();

                return (int)result;
            }
        }

        /// <summary>
        /// Get packaging bytes
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>   
        public PackagingBytes PackagingBytes
        {
            get
            {
                CheckDisposed();
                Api.FormatGetPackagingBytes(Object, out Import.PackagingBytes result);
                Object.CheckState();

                return new PackagingBytes
                {
                    ByteCount = (int)result.byteCount,
                    Endianness = (Endianness)result.endianness
                };
            }
        }

        /// <summary>
        /// Dispose object
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Dispose object
        /// </summary>
        /// <param name="disposing">If <paramref name="disposing"/> equals false only unmanaged resources can be disposed.</param>
        protected virtual void Dispose(bool disposing)
        {
            if (!_disposed)
            {
                if (disposing)
                {
                    Object?.Close();
                    Object = null;
                }

                _disposed = true;
            }
        }

        private void CheckDisposed()
        {
            if (Object == null)
                throw new ObjectDisposedException(nameof(Format));

            Object.CheckDisposed(nameof(Format));
        }
    }
}
