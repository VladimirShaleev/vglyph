using System;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Glyph
    /// </summary>
    public class Glyph : IDisposable
    {
        private bool _disposed;

        internal ObjectHandle Object { get; private set; }

        internal static ObjectHandle Type
            => Api.GetGlyphType();

        /// <summary>
        /// Unmanaged handle of vglyph library
        /// </summary>
        protected IntPtr Handle
            => Object?.DangerousGetHandle() ?? IntPtr.Zero;

        /// <summary>
        /// Constructs new object <see cref="Glyph"/>
        /// </summary>
        /// <param name="figure">figure</param>
        /// <exception cref="ArgumentNullException">param <paramref name="figure"/> is null</exception>
        public Glyph(Figure figure) : this(Api.GlyphCreate(
            figure?.ThrowOrObject ?? throw new ArgumentNullException(nameof(figure))))
        {
        }

        /// <summary>
        /// Constructs new object <see cref="Glyph"/> for unmanaged handle
        /// </summary>
        /// <param name="handle">Unmanaged handle of vglyph library</param>
        /// <exception cref="ArgumentException">Invalid unmanaged handle</exception>
        protected Glyph(IntPtr handle) : this(new ObjectHandle(handle))
        {
        }

        internal Glyph(ObjectHandle handle)
        {
            Object = handle ?? throw new ArgumentNullException();

            if (Object.IsInvalid)
                throw new ArgumentException();

            Object.CheckState();
        }

        ~Glyph()
        {
            Dispose(false);
        }

        /// <summary>
        /// Get <see cref="Figure"/>
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>   
        public Figure Figure
        {
            get
            {
                CheckDisposed();

                var result = Api.GlyphGetFigure(Object);
                Object.CheckState();

                return new Figure(result);
            }
        }

        /// <summary>
        /// Get width of <see cref="Figure"/>
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>   
        public float Width
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetWidth(Object);
                Object.CheckState();

                return result;
            }
        }

        /// <summary>
        /// Get height of <see cref="Figure"/>
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>   
        public float Height
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetHeight(Object);
                Object.CheckState();

                return result;
            }
        }

        /// <summary>
        /// Horizontal bearing X
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>   
        public float HorizontalBearingX
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetHorizontalBearingX(Object);
                Object.CheckState();

                return result;
            }
            set
            {
                CheckDisposed();
                Api.GlyphSetHorizontalBearingX(Object, value);
                Object.CheckState();
            }
        }

        /// <summary>
        /// Horizontal bearing Y
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>  
        public float HorizontalBearingY
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetHorizontalBearingY(Object);
                Object.CheckState();

                return result;
            }
            set
            {
                CheckDisposed();
                Api.GlyphSetHorizontalBearingY(Object, value);
                Object.CheckState();
            }
        }

        /// <summary>
        /// Horizontal advance
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>  
        public float HorizontalAdvance
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetHorizontalAdvance(Object);
                Object.CheckState();

                return result;
            }
            set
            {
                CheckDisposed();
                Api.GlyphSetHorizontalAdvance(Object, value);
                Object.CheckState();
            }
        }

        /// <summary>
        /// Vertical bearing X
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>  
        public float VerticalBearingX
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetVerticalBearingX(Object);
                Object.CheckState();

                return result;
            }
            set
            {
                CheckDisposed();
                Api.GlyphSetVerticalBearingX(Object, value);
                Object.CheckState();
            }
        }

        /// <summary>
        /// Vertical bearing Y
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>  
        public float VerticalBearingY
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetVerticalBearingY(Object);
                Object.CheckState();

                return result;
            }
            set
            {
                CheckDisposed();
                Api.GlyphSetVerticalBearingY(Object, value);
                Object.CheckState();
            }
        }

        /// <summary>
        /// Vertical advance
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>  
        public float VerticalAdvance
        {
            get
            {
                CheckDisposed();
                var result = Api.GlyphGetVerticalAdvance(Object);
                Object.CheckState();

                return result;
            }
            set
            {
                CheckDisposed();
                Api.GlyphSetVerticalAdvance(Object, value);
                Object.CheckState();
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
                throw new ObjectDisposedException(nameof(Glyph));

            Object.CheckDisposed(nameof(Glyph));
        }
    }
}
