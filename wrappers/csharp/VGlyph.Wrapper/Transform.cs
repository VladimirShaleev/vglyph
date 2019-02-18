using System;
using VGlyph.Import;

namespace VGlyph
{
    /// <summary>
    /// Transform
    /// </summary>
    public class Transform : IDisposable, ICloneable
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
        /// Create copy of <see cref="Transform"/>
        /// </summary>
        /// <returns>Return copy of this <see cref="Transform"/></returns>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public Transform CreateCopy()
        {
            CheckDisposed();

            var result = Api.TransformCreateCopy(Object);
            Object.CheckState();

            return new Transform(result);
        }

        /// <summary>
        /// To identity matrix
        /// </summary>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void Clear()
        {
            CheckDisposed();

            Api.TransformClear(Object);
            Object.CheckState();
        }

        /// <summary>
        /// Multiply of two matrices
        /// </summary>
        /// <param name="value">matrix</param>
        /// <exception cref="ArgumentNullException">value is null</exception>
        /// <exception cref="ArgumentException">value is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void Combine(Transform value)
        {
            CheckDisposed();

            if (value == null)
                throw new ArgumentNullException(nameof(value));

            if (value.Object.IsInvalid)
                throw new ArgumentException("value is invalie", nameof(value));

            Api.TransformCombine(Object, value.Object);
            Object.CheckState();
        }

        /// <summary>
        /// Translate matrix
        /// </summary>
        /// <param name="x">Translate X</param>
        /// <param name="y">Translate Y</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void Translate(float x, float y)
        {
            CheckDisposed();

            Api.TransformTranslate(Object, x, y);
            Object.CheckState();
        }

        /// <summary>
        /// Scale matrix
        /// </summary>
        /// <param name="sx">Scale X</param>
        /// <param name="sy">Scale Y</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void Scale(float sx, float sy)
        {
            CheckDisposed();

            Api.TransformScale(Object, sx, sy);
            Object.CheckState();
        }

        /// <summary>
        /// Rotate matrix
        /// </summary>
        /// <param name="angle">angle</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void Rotate(float angle)
        {
            CheckDisposed();

            Api.TransformRotate(Object, angle);
            Object.CheckState();
        }

        /// <summary>
        /// Transform point
        /// </summary>
        /// <param name="point"><see cref="Point"/> for transform</param>
        /// <returns>Result transform</returns>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public Point TransformPoint(Point point)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };

            Api.TransformTransformPoint(Object, ref unmanagedPoint);
            Object.CheckState();

            return new Point(unmanagedPoint.x, unmanagedPoint.y);
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

        /// <summary>
        /// Clone of <see cref="Transform"/>
        /// </summary>
        /// <returns>Return copy of this <see cref="Transform"/></returns>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public object Clone()
        {
            return CreateCopy();
        }

        private void CheckDisposed()
        {
            if (Object == null)
                throw new ObjectDisposedException(nameof(Transform));

            Object.CheckDisposed(nameof(Transform));
        }

        /// <summary>
        /// Multiply of two matrices
        /// </summary>
        /// <param name="value1">Matrix 1</param>
        /// <param name="value2">Matrix 2</param>
        /// <returns>Result matrix</returns>
        /// <exception cref="ArgumentNullException">value1 or value2 is null</exception>
        /// <exception cref="ArgumentException">value1 or value2 is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public static Transform operator *(Transform value1, Transform value2)
        {
            if (value1 == null)
                throw new ArgumentNullException(nameof(value1));
            
            if (value2 == null)
                throw new ArgumentNullException(nameof(value2));

            if (value1.Object.IsInvalid)
                throw new ArgumentException("value1 is invalide", nameof(value1));

            if (value2.Object.IsInvalid)
                throw new ArgumentException("value2 is invalide", nameof(value2));

            var result = value1.CreateCopy();
            result.Combine(value2);

            return result;
        }

        /// <summary>
        /// Transform point
        /// </summary>
        /// <param name="transform">Matrix</param>
        /// <param name="point">transform <see cref="Point"/></param>
        /// <returns>Result transform of <paramref name="point"/></returns>
        /// <exception cref="ArgumentNullException">transform is null</exception>
        /// <exception cref="ArgumentException">transform is invalid</exception>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public static Point operator *(Transform transform, Point point)
        {
            if (transform == null)
                throw new ArgumentNullException(nameof(transform));

            if (transform.Object.IsInvalid)
                throw new ArgumentException("transform is invalide", nameof(transform));

            return transform.TransformPoint(point);
        }
    }
}
