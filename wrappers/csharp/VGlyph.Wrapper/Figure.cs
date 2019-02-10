using System;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Figure
    /// </summary>
    /// <remarks>
    /// Object need for draw primitives
    /// </remarks>
    public class Figure : IDisposable
    {
        private bool _disposed;

        internal ObjectHandle Object { get; private set; }

        internal static ObjectHandle Type
            => Api.GetFigureType();

        /// <summary>
        /// Unmanaged handle of vglyph library
        /// </summary>
        protected IntPtr Handle
            => Object?.DangerousGetHandle() ?? IntPtr.Zero;

        /// <summary>
        /// Constructs new object <see cref="Figure"/>
        /// </summary>
        public Figure() : this(Api.FigureCreate())
        {
        }

        /// <summary>
        /// Constructs new object <see cref="Figure"/> for unmanaged handle
        /// </summary>
        /// <param name="handle">Unmanaged handle of vglyph library</param>
        /// <exception cref="ArgumentException">Invalid unmanaged handle</exception>
        protected Figure(IntPtr handle) : this(new ObjectHandle(handle))
        {
        }

        internal Figure(ObjectHandle handle)
        {
            Object = handle ?? throw new ArgumentNullException();

            if (Object.IsInvalid)
                throw new ArgumentException();

            Object.CheckState();
        }

        /// <summary>
        /// Clear path figure
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void DrawClear()
        {
            CheckDisposed();

            Api.FigureDrawClear(Object);
            Object.CheckState();
        }

        /// <summary>
        /// Close path figure
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void DrawClosepath()
        {
            CheckDisposed();

            Api.FigureDrawClosepath(Object);
            Object.CheckState();
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
                throw new ObjectDisposedException(nameof(Figure));

            Object.CheckDisposed(nameof(Figure));
        }
    }
}
