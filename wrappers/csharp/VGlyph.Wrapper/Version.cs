using System;
using System.Globalization;

namespace VGlyph
{
    /// <summary>
    /// Version
    /// </summary>
    [Serializable]
    public sealed class Version : ICloneable, IComparable, IComparable<Version>, IEquatable<Version>
    {
        [Explicit] private byte _major { get; set; }
        [Explicit] private byte _minor { get; set; }
        [Explicit] private byte _micro { get; set; }

        /// <summary>
        /// Major version
        /// </summary>
        public byte Major
        {
            get => _major;
            set => _major = value;
        }

        /// <summary>
        /// Minor version
        /// </summary>
        public byte Minor
        {
            get => _minor;
            set => _minor = value;
        }

        /// <summary>
        /// Micro version
        /// </summary>
        public byte Micro
        {
            get => _micro;
            set => _micro = value;
        }

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
        /// Parse string to <see cref="Version"/>
        /// </summary>
        /// <param name="input">string with version</param> 
        /// <returns>Result of parse string</returns>
        /// <exception cref="ArgumentNullException">Argument <paramref name="input"/> is null</exception>
        /// <exception cref="ArgumentException">Argument <paramref name="input"/> has an incorrect format</exception>
        /// <exception cref="FormatException">Argument <paramref name="input"/> has an incorrect format of component</exception>
        /// <exception cref="OverflowException">Component of argument <paramref name="input"/> out of range 0-255</exception>
        public static Version Parse(string input)
        {
            if (input == null)
                throw new ArgumentNullException(nameof(input));

            var result = new VersionResult();
            result.Init(nameof(input));

            if (!TryParseVersion(input, ref result))
                throw result.GetException();

            return result.Result;
        }

        /// <summary>
        /// Try parse string to <see cref="Version"/>
        /// </summary>
        /// <param name="input">string with version</param> 
        /// <param name="result">result of parse string to <see cref="Version"/></param> 
        /// <returns>Result of parse string</returns>
        public static bool TryParse(string input, out Version result)
        {
            if (input == null)
            {
                result = null;
                return false;
            }

            var tryResult = new VersionResult();
            tryResult.Init(nameof(input));

            var success = TryParseVersion(input, ref tryResult);
            result = tryResult.Result;

            return success;
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
        /// <param name="v1">Version left param</param> 
        /// <param name="v2">Version right param</param> 
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
        
        private static bool TryParseVersion(string version, ref VersionResult result)
        {
            var components = version.Split('.');
            var componentsCount = components.Length;

            if (componentsCount < 2 || componentsCount > 3)
            {
                result.SetFailure(ParseFailureType.ArgumentException);
                return false;
            }
            
            if (!TryParseComponent(components[0], nameof(Major), ref result, out var major))
                return false;

            if (!TryParseComponent(components[1], nameof(Minor), ref result, out var minor))
                return false;

            componentsCount -= 2;

            if (componentsCount > 0)
            {
                if (!TryParseComponent(components[2], nameof(Micro), ref result, out var micro))
                    return false;

                result.Result = new Version(major, minor, micro);
            }
            else
            {
                result.Result = new Version(major, minor);
            }

            return true;
        }

        private static bool TryParseComponent(string component, string componentName, ref VersionResult result, out byte parsedComponent)
        {
            if (!byte.TryParse(component, NumberStyles.Integer, CultureInfo.InvariantCulture, out parsedComponent))
            {
                result.SetFailure(ParseFailureType.FormatException, componentName, component);
                return false;
            }

            return true;
        }
        
        private struct VersionResult
        {
            internal string _errorComponentName;
            internal string _errorComponentValue;
            internal string _argumentName;
            internal ParseFailureType _failure;

            public Version Result;

            public void Init(string argumentName)
            {
                _argumentName = argumentName;
            }

            public void SetFailure(ParseFailureType failure)
            {
                SetFailure(failure, null, null);
            }
            
            public void SetFailure(ParseFailureType failure, string errorComponentName, string errorComponentValue)
            {
                _failure = failure;
                _errorComponentName = errorComponentName;
                _errorComponentValue = errorComponentValue;
            }

            public Exception GetException()
            {
                switch (_failure)
                {
                    case ParseFailureType.ArgumentException:
                        return new ArgumentException("Parsing failed", _argumentName);

                    case ParseFailureType.FormatException:
                        try
                        {
                            byte.Parse(_errorComponentValue, CultureInfo.InvariantCulture);
                        }
                        catch (FormatException)
                        {
                            // return new FormatException
                        }
                        catch (OverflowException)
                        {
                            return new OverflowException($"The component '{_errorComponentName}' out of range (0-255): {_errorComponentValue} - of argument '{_argumentName}'");
                        }

                        return new FormatException($"The component '{_errorComponentName}' has an incorrect format '{_errorComponentValue}' - of argument '{_argumentName}'.");

                    default:
                        return new ArgumentException($"Parsing failed of argument '{_argumentName}'");
                }
            }
        }

        private enum ParseFailureType
        {
            ArgumentException,
            FormatException
        }
    }
}
