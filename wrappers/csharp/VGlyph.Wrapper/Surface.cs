using System;
using System.IO;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Surface
    /// </summary>
    public class Surface : IDisposable
    {
        private bool _disposed;

        internal ObjectHandle Object { get; private set; }

        internal static ObjectHandle Type
            => Api.GetSurfaceType();

        /// <summary>
        /// Unmanaged handle of vglyph library
        /// </summary>
        protected IntPtr Handle
            => Object?.DangerousGetHandle() ?? IntPtr.Zero;

        /// <summary>
        /// Constructs new object <see cref="Surface"/>
        /// </summary>
        /// <param name="format">Format of <see cref="Surface"/></param>
        /// <param name="width">width of <see cref="Surface"/></param>
        /// <param name="height">height of <see cref="Surface"/></param>
        /// <param name="rowAlignment">Bytes aligment for row <see cref="Surface"/></param>
        /// <exception cref="ArgumentNullException"><paramref name="format"/> is null</exception>
        /// <exception cref="ArgumentOutOfRangeException"><paramref name="width"/> or <paramref name="height"/> less than zero</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>   
        public Surface(Format format, int width, int height, Alignment rowAlignment)
            : this(Create(format, width, height, rowAlignment))
        {
        }

        /// <summary>
        /// Constructs new object <see cref="Surface"/> for unmanaged handle
        /// </summary>
        /// <param name="handle">Unmanaged handle of vglyph library</param>
        /// <exception cref="ArgumentException">Invalid unmanaged handle</exception>
        protected Surface(IntPtr handle) : this(new ObjectHandle(handle))
        {
        }

        internal Surface(ObjectHandle handle)
        {
            Object = handle ?? throw new ArgumentNullException();

            if (Object.IsInvalid)
                throw new ArgumentException();

            Object.CheckState();
        }

        ~Surface()
        {
            Dispose(false);
        }

        /// <summary>
        /// Get <see cref="Format"/> of surface
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public Format Format
        {
            get
            {
                CheckDisposed();

                var result = Api.SurfaceGetFormat(Object);
                Object.CheckState();

                return Library.CreateObjectFromHandle<Format>(result);
            }
        }

        /// <summary>
        /// Get width of row surface
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public int Width
        {
            get
            {
                CheckDisposed();
                var result = Api.SurfaceGetWidth(Object);
                Object.CheckState();

                return (int)result;
            }
        }

        /// <summary>
        /// Get height of row surface
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public int Height
        {
            get
            {
                CheckDisposed();
                var result = Api.SurfaceGetHeight(Object);
                Object.CheckState();

                return (int)result;
            }
        }

        /// <summary>
        /// Get pitch of row surface
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public int Pitch
        {
            get
            {
                CheckDisposed();
                var result = Api.SurfaceGetPitch(Object);
                Object.CheckState();

                return (int)result;
            }
        }

        /// <summary>
        /// Number of samples per pixel
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public Multisampling Multisampling
        {
            get
            {
                CheckDisposed();
                var result = Api.SurfaceGetMultisampling(Object);
                Object.CheckState();

                return (Multisampling)result;
            }
            set
            {
                CheckDisposed();
                Api.SurfaceSetMultisampling(Object, value.GetUnmanagedMultisampling());
                Object.CheckState();
            }
        }

        /// <summary>
        /// Capture stream bytes of surface
        /// </summary>
        /// <param name="x">left bound to lock</param>
        /// <param name="y">top bound to lock</param>
        /// <param name="width">width lock</param>
        /// <param name="height">height lock</param>
        /// <exception cref="ArgumentOutOfRangeException"><paramref name="width"/> or <paramref name="height"/> less than zero</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        /// <returns>Stream bytes</returns>
        public Stream CaptureStream(int x, int y, int width, int height)
        {
            CheckDisposed();

            if (x < 0)
                throw new ArgumentOutOfRangeException(nameof(x), "x must not be less than zero");

            if (y < 0)
                throw new ArgumentOutOfRangeException(nameof(y), "y must not be less than zero");

            if (width < 0)
                throw new ArgumentOutOfRangeException(nameof(width), "width must not be less than zero");

            if (height < 0)
                throw new ArgumentOutOfRangeException(nameof(height), "height must not be less than zero");

            IntPtr ptr;

            try
            {
                ptr = Api.SurfaceLock(Object, (uint)x, (uint)y, (uint)width, (uint)height);
                Object.CheckState();
            }
            catch
            {
                Api.SurfaceUnlock(Object);
                Object.CheckState();
                throw;
            }

            return new SurfaceStream(this, ptr);
        }

        /// <summary>
        /// Compute size of data surface in bytes
        /// </summary>
        /// <param name="format">Format of <see cref="Surface"/></param>
        /// <param name="width">width of <see cref="Surface"/></param>
        /// <param name="height">height of <see cref="Surface"/></param>
        /// <param name="rowAlignment">Bytes aligment for row <see cref="Surface"/></param>
        /// <exception cref="ArgumentNullException"><paramref name="format"/> is null</exception>
        /// <exception cref="ArgumentOutOfRangeException"><paramref name="width"/> or <paramref name="height"/> less than zero</exception>
        /// <returns>Size of data in bytes</returns>
        public static int GetDataSize(Format format, int width, int height, Alignment rowAlignment)
        {
            if (format == null)
                throw new ArgumentNullException(nameof(format));

            if (width < 0)
                throw new ArgumentOutOfRangeException(nameof(width), "width must not be less than zero");

            if (height < 0)
                throw new ArgumentOutOfRangeException(nameof(height), "height must not be less than zero");

            return (int)Api.SurfaceGetDataSize(format.ThrowOrObject, (uint)width, (uint)height, rowAlignment.GetUnmanagedAlignment());
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

        private static ObjectHandle Create(Format format, int width, int height, Alignment rowAlignment)
        {
            if (format == null)
                throw new ArgumentNullException(nameof(format));

            if (width < 0)
                throw new ArgumentOutOfRangeException(nameof(width), "width must not be less than zero");

            if (height < 0)
                throw new ArgumentOutOfRangeException(nameof(height), "height must not be less than zero");

            return Api.SurfaceCreate(format.ThrowOrObject, (uint)width, (uint)height, rowAlignment.GetUnmanagedAlignment());
        }

        private void CheckDisposed()
        {
            if (Object == null)
                throw new ObjectDisposedException(nameof(Surface));

            Object.CheckDisposed(nameof(Surface));
        }
    }
}
