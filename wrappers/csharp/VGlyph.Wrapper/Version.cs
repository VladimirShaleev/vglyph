using System;

namespace VGlyph
{
    /// <summary>
    /// Version
    /// </summary>
    public sealed class Version : ICloneable, IComparable, IComparable<Version>, IEquatable<Version>
    {
        /// <summary>
        /// Major version
        /// </summary>
        public byte Major { get; set; }

        /// <summary>
        /// Minor version
        /// </summary>
        public byte Minor { get; set; }

        /// <summary>
        /// Micro version
        /// </summary>
        public byte Micro { get; set; }
        
        internal uint Version32
        {
            get
            {
                return unchecked((uint)(
                    (Major << 16) |
                    (Minor << 8) |
                    (Micro << 0)));
            }
        }

        /// <summary>
        /// Initialize <see cref="Version"/> to 0.0.0
        /// </summary>
        public Version() : this(0)
        {
        }

        /// <summary>
        /// Initialize <see cref="Version"/> to <paramref name="major"/>.0.0
        /// </summary>
        /// <param name="major">major version</param> 
        public Version(byte major) : this(major, 0)
        {
        }

        /// <summary>
        /// Initialize <see cref="Version"/> to <paramref name="major"/>.<paramref name="minor"/>.0
        /// </summary>
        /// <param name="major">major version</param> 
        /// <param name="minor">minor version</param> 
        public Version(byte major, byte minor) : this(major, minor, 0)
        {
        }

        /// <summary>
        /// Initialize <see cref="Version"/> to <paramref name="major"/>.<paramref name="minor"/>.<paramref name="micro"/>
        /// </summary>
        /// <param name="major">major version</param> 
        /// <param name="minor">minor version</param> 
        /// <param name="micro">micro version</param> 
        public Version(byte major, byte minor, byte micro)
        {
            Major = major;
            Minor = minor;
            Micro = micro;
        }

        internal Version(uint version) : this(
            (byte)((version >> 16) & 0xFF),
            (byte)((version >> 8) & 0xFF),
            (byte)((version >> 0) & 0xFF))
        {
        }

        /// <summary>
        /// Clone <see cref="Version"/>
        /// </summary>
        /// <returns>Return clone object</returns>
        public object Clone()
        {
            return new Version(Major, Minor, Micro);
        }

        /// <summary>
        /// Compare versions
        /// </summary>
        /// <param name="version">Compare version</param> 
        /// <returns>Compare result</returns>
        /// <exception cref="ArgumentException">Argument <paramref name="version"/> is not a <see cref="Version"/></exception>
        public int CompareTo(object version)
        {
            if (version == null)
                return 1;
            
            if (version is Version v)
                return CompareTo(v);

            throw new ArgumentException("Argument must be Version", nameof(version));
        }

        /// <summary>
        /// Compare versions
        /// </summary>
        /// <param name="version">Compare version</param> 
        /// <returns>Compare result</returns>
        public int CompareTo(Version version)
        {
            if (version == null)
                return 1;

            if (Major != version.Major)
                return Major > version.Major ? 1 : -1;

            if (Minor != version.Minor)
                return Minor > version.Minor ? 1 : -1;

            if (Micro != version.Micro)
                return Micro > version.Micro ? 1 : -1;

            return 0;
        }

        /// <summary>
        /// Equals versions
        /// </summary>
        /// <param name="version">Equals version</param> 
        /// <returns>Result of equal</returns>
        public override bool Equals(object version)
        {
            if (version is Version v)
                return Equals(v);

            return false;
        }

        /// <summary>
        /// Equals versions
        /// </summary>
        /// <param name="version">Equals version</param> 
        /// <returns>Result of equal</returns>
        public bool Equals(Version version)
        {
            if (version is null)
                return false;

            return
                Major == version.Major &&
                Minor == version.Minor &&
                Micro == version.Micro;
        }

        /// <summary>
        /// Get hash code of <see cref="Version"/>
        /// </summary>
        /// <returns>Return hash code</returns>
        public override int GetHashCode()
        {
            return unchecked(
                (Major << 16) |
                (Minor << 8) |
                (Micro << 0));
        }

        /// <summary>
        /// Convert Version to string
        /// </summary>
        /// <returns>String representation of <see cref="Version"/></returns>
        public override string ToString()
        {
            return $"{Major}.{Minor}.{Micro}";
        }

        /// <summary>
        /// Compare two <see cref="Version"/>'s on equality
        /// </summary>
        /// <param name="v1">Version left param</param> 
        /// <param name="v2">Version right param</param> 
        /// <returns>Result of compare</returns>
        public static bool operator ==(Version v1, Version v2)
        {
            if (v1 is null)
                return v2 is null;

            return v1.Equals(v2);
        }

        /// <summary>
        /// Compare two <see cref="Version"/>'s on not equality
        /// </summary>
        /// <param name="v1">Version left param</param> 
        /// <param name="v2">Version right param</param> 
        /// <returns>Result of compare</returns>
        public static bool operator !=(Version v1, Version v2)
        {
            return !(v1 == v2);
        }

        /// <summary>
        /// Compare two <see cref="Version"/>'s on less
        /// </summary>
        /// <returns>Result of compare</returns>
        public static bool operator <(Version v1, Version v2)
        {
            if (v1 is null)
                return !(v2 is null);

            return v1.CompareTo(v2) < 0;
        }

        /// <summary>
        /// Compare two <see cref="Version"/>'s on big
        /// </summary>
        /// <param name="v1">Version left param</param> 
        /// <param name="v2">Version right param</param> 
        /// <returns>Result of compare</returns>
        public static bool operator >(Version v1, Version v2)
        {
            return v2 < v1;
        }

        /// <summary>
        /// Compare two <see cref="Version"/>'s on less or equal
        /// </summary>
        /// <param name="v1">Version left param</param> 
        /// <param name="v2">Version right param</param> 
        /// <returns>Result of compare</returns>
        public static bool operator <=(Version v1, Version v2)
        {
            if (v1 is null)
                return true;

            return v1.CompareTo(v2) <= 0;
        }

        /// <summary>
        /// Compare two <see cref="Version"/>'s on big or equal
        /// </summary>
        /// <param name="v1">Version left param</param> 
        /// <param name="v2">Version right param</param> 
        /// <returns>Result of compare</returns>
        public static bool operator >=(Version v1, Version v2)
        {
            return v2 <= v1;
        }
    }
}
