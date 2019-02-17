using System;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Transform
    /// </summary>
    public class Transform : IDisposable
    {
        private bool _disposed;

        internal ObjectHandle Object { get; private set; }

        internal ObjectHandle ThrowOrObject
            => Object.IsInvalid ? throw new NullReferenceException() : Object;

        internal static ObjectHandle Type
            => Api.GetTransformType();

        /// <summary>
        /// Unmanaged handle of vglyph library
        /// </summary>
        protected IntPtr Handle
            => Object?.DangerousGetHandle() ?? IntPtr.Zero;

        /// <summary>
        /// Constructs new object <see cref="Transform"/>
        /// </summary>
        public Transform() : this(Api.TransformCreate())
        {
        }

        /// <summary>
        /// Constructs new object <see cref="Transform"/> for unmanaged handle
        /// </summary>
        /// <param name="handle">Unmanaged handle of vglyph library</param>
        /// <exception cref="ArgumentException">Invalid unmanaged handle</exception>
        protected Transform(IntPtr handle) : this(new ObjectHandle(handle))
        {
        }

        internal Transform(ObjectHandle handle)
        {
            Object = handle ?? throw new ArgumentNullException();

            if (Object.IsInvalid)
                throw new ArgumentException();

            Object.CheckState();
        }

        /// <summary>
        /// Free resources and perform other cleanup operations
        /// </summary>
        ~Transform()
        {
            Dispose(false);
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
                throw new ObjectDisposedException(nameof(Transform));

            Object.CheckDisposed(nameof(Transform));
        }
    }
}
