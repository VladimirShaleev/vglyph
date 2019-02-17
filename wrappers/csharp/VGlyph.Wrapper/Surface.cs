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

        /// <summary>
        /// Free resources and perform other cleanup operations
        /// </summary>
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
        /// Fills the surface with a solid color.
        /// </summary>
        /// <param name="x">Starting horizontal position to fill</param>
        /// <param name="y">Starting vertical position to fill</param>
        /// <param name="width">Width to fill</param>
        /// <param name="height">Height to fill</param>
        /// <param name="color">Solid color to fill</param>
        /// <exception cref="ArgumentOutOfRangeException">Width and height can not be negative</exception>
        /// <exception cref="ArgumentNullException">Color is null</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void Fill(int x, int y, int width, int height, Color color)
        {
            CheckDisposed();

            if (x < 0)
                x = 0;

            if (y < 0)
                y = 0;

            if (width < 0)
                new ArgumentOutOfRangeException(nameof(width), "Width can not be negative");

            if (height < 0)
                new ArgumentOutOfRangeException(nameof(height), "Height can not be negative");

            if (color == null)
                new ArgumentNullException(nameof(color), "Color is null");

            var unmanagedColor = new Import.Color
            {
                red = color.Red,
                green = color.Green,
                blue = color.Blue,
                alpha = color.Alpha
            };

            Api.SurfaceFill(Object, (uint)x, (uint)y, (uint)width, (uint)height, ref unmanagedColor);
            Object.CheckState();
        }

        /// <summary>
        /// Get <see cref="Color"/> of pixel
        /// </summary>
        /// <param name="x">X position</param>
        /// <param name="y">Y position</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        /// <returns><see cref="Color"/> of pixel</returns>
        public Color GetPixel(int x, int y)
        {
            CheckDisposed();

            Api.SurfaceGetPixel(Object, x, y, out var color);
            Object.CheckState();

            return new Color(color.red, color.green, color.blue, color.alpha);
        }

        /// <summary>
        /// Set <see cref="Color"/> of pixel
        /// </summary>
        /// <param name="x">X position</param>
        /// <param name="y">Y position</param>
        /// <param name="color"><see cref="Color"/> of pixel</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void SetPixel(int x, int y, Color color)
        {
            CheckDisposed();

            var unmanagedColor = new Import.Color
            {
                red = color.Red,
                green = color.Green,
                blue = color.Blue,
                alpha = color.Alpha
            };

            Api.SurfaceSetPixel(Object, x, y, ref unmanagedColor);
            Object.CheckState();
        }

        /// <summary>
        /// Draw glyph on surface
        /// </summary>
        /// <param name="glyph">Draw <see cref="Glyph"/></param>
        /// <param name="pt">Size glyph in punkt</param>
        /// <param name="color"><see cref="Color"/> of <see cref="Glyph"/></param>
        /// <param name="position">Position to draw on <see cref="Surface"/></param>
        /// <param name="origin">Origin of <see cref="Glyph"/></param>
        /// <param name="scale">Scale of <see cref="Glyph"/></param>
        /// <param name="angle">Rotation of <see cref="Glyph"/></param>
        /// <param name="verticalLayout"><see cref="Glyph"/> orientation</param>
        /// <exception cref="ArgumentNullException">parameter is null</exception>
        /// <exception cref="ArgumentException">glyph handle is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void DrawGlyph(Glyph glyph, float pt, Color color, Point position, Point origin, Point scale, float angle, bool verticalLayout)
        {
            CheckDisposed();

            if (glyph == null)
                throw new ArgumentNullException(nameof(glyph));

            if (glyph.Object.IsInvalid)
                throw new ArgumentException("glyph invalid", nameof(glyph));

            if (color == null)
                throw new ArgumentNullException(nameof(color));

            var unmanagedColor = new Import.Color
            {
                red = color.Red,
                green = color.Green,
                blue = color.Blue,
                alpha = color.Alpha
            };

            var unmanagedPosition = new Import.Point
            {
                x = position.X,
                y = position.Y
            };

            var unmanagedOrigin = new Import.Point
            {
                x = origin.X,
                y = origin.Y
            };

            var unmanagedScale = new Import.Point
            {
                x = scale.X,
                y = scale.Y
            };

            Api.SurfaceDrawGlyph(Object, glyph.Object, pt, ref unmanagedColor, ref unmanagedPosition, ref unmanagedOrigin, ref unmanagedScale, angle, verticalLayout);
            Object.CheckState();
        }

        /// <summary>
        /// Draw glyph on surface to viewport
        /// </summary>
        /// <param name="glyph">Draw <see cref="Glyph"/></param>
        /// <param name="color"><see cref="Color"/> of <see cref="Glyph"/></param>
        /// <param name="position">Position to draw on <see cref="Surface"/></param>
        /// <param name="viewport">Viewport for glyph</param>
        /// <param name="origin">Origin of <see cref="Glyph"/></param>
        /// <param name="angle">Rotation of <see cref="Glyph"/></param>
        /// <param name="fitToViewport">Fit glyph to viewport without bearing</param>
        /// <exception cref="ArgumentNullException">parameter is null</exception>
        /// <exception cref="ArgumentException">glyph handle is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void DrawGlyphViewport(Glyph glyph, Color color, Point position, Point viewport, Point origin, float angle, bool fitToViewport)
        {
            CheckDisposed();

            if (glyph == null)
                throw new ArgumentNullException(nameof(glyph));

            if (glyph.Object.IsInvalid)
                throw new ArgumentException("glyph invalid", nameof(glyph));

            if (color == null)
                throw new ArgumentNullException(nameof(color));

            var unmanagedColor = new Import.Color
            {
                red = color.Red,
                green = color.Green,
                blue = color.Blue,
                alpha = color.Alpha
            };

            var unmanagedPosition = new Import.Point
            {
                x = position.X,
                y = position.Y
            };

            var unmanagedViewport = new Import.Point
            {
                x = viewport.X,
                y = viewport.Y
            };

            var unmanagedOrigin = new Import.Point
            {
                x = origin.X,
                y = origin.Y
            };

            Api.SurfaceDrawGlyphViewport(Object, glyph.Object, ref unmanagedColor, ref unmanagedPosition, ref unmanagedViewport, ref unmanagedOrigin, angle, fitToViewport);
            Object.CheckState();
        }

        /// <summary>
        /// Draw glyph on surface
        /// </summary>
        /// <param name="glyph">Draw <see cref="Glyph"/></param>
        /// <param name="color"><see cref="Color"/> of <see cref="Glyph"/></param>
        /// <param name="transform"><see cref="Transform"/> on <see cref="Glyph"/></param>
        /// <exception cref="ArgumentNullException">parameter is null</exception>
        /// <exception cref="ArgumentException">glyph and/or transform handle is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void DrawGlyphTransform(Glyph glyph, Color color, Transform transform)
        {
            CheckDisposed();

            if (glyph == null)
                throw new ArgumentNullException(nameof(glyph));

            if (glyph.Object.IsInvalid)
                throw new ArgumentException("glyph invalid", nameof(glyph));

            if (transform == null)
                throw new ArgumentNullException(nameof(transform));

            if (transform.Object.IsInvalid)
                throw new ArgumentException("transform invalid", nameof(transform));

            if (color == null)
                throw new ArgumentNullException(nameof(color));

            var unmanagedColor = new Import.Color
            {
                red = color.Red,
                green = color.Green,
                blue = color.Blue,
                alpha = color.Alpha
            };

            Api.SurfaceDrawGlyphTransform(Object, glyph.Object, ref unmanagedColor, transform.Object);
            Object.CheckState();
        }

        /// <summary>
        /// Draw text on surface
        /// </summary>
        /// <param name="face">Draw glyphs in <see cref="Face"/></param>
        /// <param name="pt">Size glyph in punkt</param>
        /// <param name="text">Text for drawing</param>
        /// <param name="color"><see cref="Color"/> of <see cref="Glyph"/></param>
        /// <param name="position">Position to draw on <see cref="Surface"/></param>
        /// <param name="origin">Origin of <see cref="Glyph"/></param>
        /// <param name="scale">Scale of <see cref="Glyph"/></param>
        /// <param name="angle">Rotation of <see cref="Glyph"/></param>
        /// <param name="verticalLayout"><see cref="Glyph"/> orientation</param>
        /// <exception cref="ArgumentNullException">parameter is null</exception>
        /// <exception cref="ArgumentException"><see cref="Face"/> handle is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void DrawText(Face face, float pt, string text, Color color, Point position, Point origin, Point scale, float angle, bool verticalLayout)
        {
            CheckDisposed();

            if (face == null)
                throw new ArgumentNullException(nameof(face));

            if (face.Object.IsInvalid)
                throw new ArgumentException("face invalid", nameof(face));

            if (text == null)
                throw new ArgumentNullException(nameof(text));

            if (color == null)
                throw new ArgumentNullException(nameof(color));

            if (text.Length != 0)
            {
                var unmanagedColor = new Import.Color
                {
                    red = color.Red,
                    green = color.Green,
                    blue = color.Blue,
                    alpha = color.Alpha
                };

                var unmanagedPosition = new Import.Point
                {
                    x = position.X,
                    y = position.Y
                };

                var unmanagedOrigin = new Import.Point
                {
                    x = origin.X,
                    y = origin.Y
                };

                var unmanagedScale = new Import.Point
                {
                    x = scale.X,
                    y = scale.Y
                };

                using (var unmanagedText = new StringHandle(text))
                {
                    Api.SurfaceDrawText(Object, face.Object, pt, unmanagedText, ref unmanagedColor, ref unmanagedPosition, ref unmanagedOrigin, ref unmanagedScale, angle, verticalLayout);
                }

                Object.CheckState();
            }
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
