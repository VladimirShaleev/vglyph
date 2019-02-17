using System;
using System.Collections.Generic;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Face
    /// </summary>
    public class Face : IDisposable
    {
        private bool _disposed;

        internal ObjectHandle Object { get; private set; }

        internal ObjectHandle ThrowOrObject
            => Object.IsInvalid ? throw new NullReferenceException() : Object;

        internal static ObjectHandle Type
            => Api.GetFaceType();

        /// <summary>
        /// Unmanaged handle of vglyph library
        /// </summary>
        protected IntPtr Handle
            => Object?.DangerousGetHandle() ?? IntPtr.Zero;

        /// <summary>
        /// Constructs new object <see cref="Face"/>
        /// </summary>
        public Face() : this(Api.FaceCreate())
        {
        }

        /// <summary>
        /// Constructs new object <see cref="Face"/> for unmanaged handle
        /// </summary>
        /// <param name="handle">Unmanaged handle of vglyph library</param>
        /// <exception cref="ArgumentException">Invalid unmanaged handle</exception>
        protected Face(IntPtr handle) : this(new ObjectHandle(handle))
        {
        }

        internal Face(ObjectHandle handle)
        {
            Object = handle ?? throw new ArgumentNullException();

            if (Object.IsInvalid)
                throw new ArgumentException();

            Object.CheckState();
        }

        /// <summary>
        /// Free resources and perform other cleanup operations
        /// </summary>
        ~Face()
        {
            Dispose(false);
        }

        /// <summary>
        /// Get <see cref="Glyph"/> on char code
        /// </summary>
        /// <param name="charCode">char code</param>
        /// <returns>Get <see cref="Glyph"/></returns>
        /// <exception cref="KeyNotFoundException">char code not found</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public Glyph GetGlyph(int charCode)
        {
            return GetGlyph(unchecked((uint)charCode));
        }

        /// <summary>
        /// Get <see cref="Glyph"/> on char code
        /// </summary>
        /// <param name="charCode">char code</param>
        /// <returns>Get <see cref="Glyph"/></returns>
        /// <exception cref="KeyNotFoundException">char code not found</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        [CLSCompliant(false)]
        public Glyph GetGlyph(uint charCode)
        {
            CheckDisposed();

            var glyph = Api.FaceGetGlyph(Object, charCode);
            Object.CheckState();

            if (glyph.IsInvalid)
                throw new KeyNotFoundException();

            return new Glyph(glyph);
        }

        /// <summary>
        /// Add <see cref="Glyph"/> to <see cref="Face"/>
        /// </summary>
        /// <param name="glyph"><see cref="Glyph"/></param>
        /// <param name="charCode">char code</param>
        /// <exception cref="ArgumentNullException">glyph is null</exception>
        /// <exception cref="ArgumentException">glyph is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void AddGlyph(Glyph glyph, int charCode)
        {
            AddGlyph(glyph, unchecked((uint)charCode));
        }

        /// <summary>
        /// Add <see cref="Glyph"/> to <see cref="Face"/>
        /// </summary>
        /// <param name="glyph"><see cref="Glyph"/></param>
        /// <param name="charCode">char code</param>
        /// <exception cref="ArgumentNullException">glyph is null</exception>
        /// <exception cref="ArgumentException">glyph is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        [CLSCompliant(false)]
        public void AddGlyph(Glyph glyph, uint charCode)
        {
            CheckDisposed();

            if (glyph == null)
                throw new ArgumentNullException(nameof(glyph));

            if (glyph.Object.IsInvalid)
                throw new ArgumentException("glyph is invalid", nameof(glyph));

            Api.FaceAddGlyph(Object, glyph.Object, charCode);
            Object.CheckState();
        }

        /// <summary>
        /// Remove <see cref="Glyph"/> from <see cref="Face"/>
        /// </summary>
        /// <param name="charCode">char code</param>
        /// <returns>Return true is remove <see cref="Glyph"/> from face. And false if glyph not found</returns>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public bool RemoveGlyph(int charCode)
        {
            return RemoveGlyph(unchecked((uint)charCode));
        }

        /// <summary>
        /// Remove <see cref="Glyph"/> from <see cref="Face"/>
        /// </summary>
        /// <param name="charCode">char code</param>
        /// <returns>Return true is remove <see cref="Glyph"/> from face. And false if glyph not found</returns>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        [CLSCompliant(false)]
        public bool RemoveGlyph(uint charCode)
        {
            CheckDisposed();

            var result = Api.FaceRemoveGlyph(Object, charCode);
            Object.CheckState();

            return result;
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
                throw new ObjectDisposedException(nameof(Face));

            Object.CheckDisposed(nameof(Face));
        }
    }
}
