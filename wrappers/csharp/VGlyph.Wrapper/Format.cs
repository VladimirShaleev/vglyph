using System;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Format of <see cref="Surface"/>
    /// </summary>
    public abstract partial class Format : IDisposable
    {
        private bool _disposed;

        internal ObjectHandle Object { get; private set; }

        internal ObjectHandle ThrowOrObject
            => Object.IsInvalid ? throw new NullReferenceException() : Object;

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
        /// Free resources and perform other cleanup operations
        /// </summary>
        ~Format()
        {
            Dispose(false);
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
        /// Create <see cref="Format"/>
        /// </summary>
        /// <param name="format">Format</param>
        /// <param name="endianness">Byte order</param>
        /// <exception cref="ArgumentException">Format string is empty of param <paramref name="format"/></exception>  
        /// <exception cref="FormatException">Invalid format of param <paramref name="format"/></exception>
        /// <returns>Return <see cref="Format"/></returns>
        public static Format Create(string format, Endianness endianness)
        {
            if (string.IsNullOrWhiteSpace(format))
                throw new ArgumentException("Format is empty", nameof(format));

            using (var unmanagedFormat = new StringHandle(format.Trim()))
            {
                var result = Api.FormatCreate(unmanagedFormat, endianness.GetUnmanagedEndianness());
                result.CheckState();

                return Library.CreateObjectFromHandle<Format>(result);
            }
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
