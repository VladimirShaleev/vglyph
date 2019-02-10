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
        /// Move point to
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="point"/> from the previous point</param>
        /// <param name="point">Point added to the path of figure</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>
        public void DrawMoveto(Coordinate coordinate, Point point)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };

            Api.FigureDrawMoveto(Object, coordinate.GetUnmanagedCoordinate(), ref unmanagedPoint);
            Object.CheckState();
        }

        /// <summary>
        /// Draw line to point from prev point
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="point"/> from the previous point</param>
        /// <param name="point">Point added to the path of figure</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>        
        public void DrawLineto(Coordinate coordinate, Point point)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };

            Api.FigureDrawLineto(Object, coordinate.GetUnmanagedCoordinate(), ref unmanagedPoint);
            Object.CheckState();
        }

        /// <summary>
        /// Draw curve cubic
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="point"/> from the previous point</param>
        /// <param name="point">New current point </param>
        /// <param name="point1">Control point at the beginning of the curve</param>
        /// <param name="point2">Control point at the end of the curve.</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>        
        public void DrawCurvetoCubic(Coordinate coordinate, Point point, Point point1, Point point2)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };

            var unmanagedPoint1 = new Import.Point
            {
                x = point1.X,
                y = point1.Y
            };

            var unmanagedPoint2 = new Import.Point
            {
                x = point2.X,
                y = point2.Y
            };

            Api.FigureDrawCurvetoCubic(Object, coordinate.GetUnmanagedCoordinate(), ref unmanagedPoint, ref unmanagedPoint1, ref unmanagedPoint2);
            Object.CheckState();
        }

        /// <summary>
        /// Draw curve quadratic
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="point"/> from the previous point</param>
        /// <param name="point">New current point </param>
        /// <param name="point1">Control point of the curve</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>         
        public void DrawCurvetoQuadratic(Coordinate coordinate, Point point, Point point1)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };

            var unmanagedPoint1 = new Import.Point
            {
                x = point1.X,
                y = point1.Y
            };

            Api.FigureDrawCurvetoQuadratic(Object, coordinate.GetUnmanagedCoordinate(), ref unmanagedPoint, ref unmanagedPoint1);
            Object.CheckState();
        }

        /// <summary>
        /// Draw arc
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="point"/> from the previous point</param>
        /// <param name="point">New current point </param>
        /// <param name="radius">Define the size and orientation of the ellipse</param>
        /// <param name="angle">Rotated in degrees relative to the current coordinate system</param>
        /// <param name="largeArcFlag">
        /// Of the four candidate arc sweeps, two will represent an arc sweep of greater than or equal to 180 degrees 
        /// (the "large-arc"), and two will represent an arc sweep of less than or equal to 180 degrees 
        /// (the "small-arc"). If <paramref name="largeArcFlag"/> is true, then one of the two larger arc sweeps will be chosen; 
        /// otherwise, if <paramref name="largeArcFlag"/> is false, one of the smaller arc sweeps will be chosen
        /// </param>
        /// <param name="sweepFlag">
        /// If <paramref name="sweepFlag"/> is true, then the arc will be drawn in a "positive-angle" direction 
        /// (i.e., the ellipse formula x=cx+rx*cos(theta) and y=cy+ry*sin(theta) is evaluated such that theta 
        /// starts at an angle corresponding to the current point and increases positively until the arc reaches 
        /// (x,y)). A value of 0 causes the arc to be drawn in a "negative-angle" direction (i.e., theta starts 
        /// at an angle value corresponding to the current point and decreases until the arc reaches (x,y)).
        /// </param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>        
        public void DrawArc(Coordinate coordinate, Point point, Point radius, float angle, bool largeArcFlag, bool sweepFlag)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };

            var unmanagedRadius = new Import.Point
            {
                x = radius.X,
                y = radius.Y
            };

            Api.FigureDrawArc(Object, coordinate.GetUnmanagedCoordinate(), ref unmanagedPoint, ref unmanagedRadius, angle, largeArcFlag, sweepFlag);
            Object.CheckState();
        }

        /// <summary>
        /// Draw horizontal line from prev point
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="x"/> from the previous point</param>
        /// <param name="x">New position</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>         
        public void DrawLinetoHorizontal(Coordinate coordinate, float x)
        {
            CheckDisposed();
            
            Api.FigureDrawLinetoHorizontal(Object, coordinate.GetUnmanagedCoordinate(), x);
            Object.CheckState();
        }

        /// <summary>
        /// Draw vertical line from prev point
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="y"/> from the previous point</param>
        /// <param name="y">New position</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>        
        public void DrawLinetoVertical(Coordinate coordinate, float y)
        {
            CheckDisposed();

            Api.FigureDrawLinetoVertical(Object, coordinate.GetUnmanagedCoordinate(), y);
            Object.CheckState();
        }

        /// <summary>
        /// Draw curve cubic smooth
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="point"/> from the previous point</param>
        /// <param name="point">New current point</param>
        /// <param name="point2">Second control point (i.e., the control point at the end of the curve)</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>       
        public void DrawCurvetoCubicSmooth(Coordinate coordinate, Point point, Point point2)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };

            var unmanagedPoint2 = new Import.Point
            {
                x = point2.X,
                y = point2.Y
            };

            Api.FigureDrawCurvetoCubicSmooth(Object, coordinate.GetUnmanagedCoordinate(), ref unmanagedPoint, ref unmanagedPoint2);
            Object.CheckState();
        }

        /// <summary>
        /// Draw quadratic smooth
        /// </summary>
        /// <param name="coordinate">Specifies how to shift <paramref name="point"/> from the previous point</param>
        /// <param name="point">New current point</param>
        /// <exception cref="ObjectDisposedException">Object disposed</exception>       
        public void DrawCurvetoQuadraticSmooth(Coordinate coordinate, Point point)
        {
            CheckDisposed();

            var unmanagedPoint = new Import.Point
            {
                x = point.X,
                y = point.Y
            };
            
            Api.FigureDrawCurvetoQuadraticSmooth(Object, coordinate.GetUnmanagedCoordinate(), ref unmanagedPoint);
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
