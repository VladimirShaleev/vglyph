# Version Class
Back to <a href="Home.md">Home page</a> 

Version


## Inheritance Hierarchy
<a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">System.Object</a><br />&nbsp;&nbsp;VGlyph.Version<br />
**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
[SerializableAttribute]
public sealed class Version : ICloneable, 
	IComparable, IComparable<Version>, IEquatable<Version>, 
	ISerializable
```

**VB**<br />
``` VB
<SerializableAttribute>
Public NotInheritable Class Version
	Implements ICloneable, IComparable, IComparable(Of Version), 
	IEquatable(Of Version), ISerializable
```

**F#**<br />
``` F#
[<SealedAttribute>]
[<SerializableAttribute>]
type Version =  
    class
        interface ICloneable
        interface IComparable
        interface IComparable<Version>
        interface IEquatable<Version>
        interface ISerializable
    end
```

The Version type exposes the following members.


## Constructors
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version__ctor.md">Version()</a></td><td>
Initialize Version to 0.0.0</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version__ctor_1.md">Version(Byte)</a></td><td>
Initialize Version to *major*.0.0</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version__ctor_2.md">Version(Byte, Byte)</a></td><td>
Initialize Version to *major*.*minor*.0</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version__ctor_3.md">Version(Byte, Byte, Byte)</a></td><td>
Initialize Version to *major*.*minor*.*micro*</td></tr></table>&nbsp;
<a href="#version-class">Back to Top</a>

## Properties
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Version_Major.md">Major</a></td><td>
Major version</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Version_Micro.md">Micro</a></td><td>
Micro version</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Version_Minor.md">Minor</a></td><td>
Minor version</td></tr></table>&nbsp;
<a href="#version-class">Back to Top</a>

## Methods
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version_Clone.md">Clone</a></td><td>
Clone Version</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version_CompareTo.md">CompareTo(Object)</a></td><td>
Compare versions</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version_CompareTo_1.md">CompareTo(Version)</a></td><td>
Compare versions</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version_Equals.md">Equals(Object)</a></td><td>
Equals versions
 (Overrides <a href="http://msdn2.microsoft.com/en-us/library/bsc2ak47" target="_blank">Object.Equals(Object)</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version_Equals_1.md">Equals(Version)</a></td><td>
Equals versions</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version_GetHashCode.md">GetHashCode</a></td><td>
Get hash code of Version
 (Overrides <a href="http://msdn2.microsoft.com/en-us/library/zdee4b3y" target="_blank">Object.GetHashCode()</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/dfwy45w9" target="_blank">GetType</a></td><td>
Gets the <a href="http://msdn2.microsoft.com/en-us/library/42892f65" target="_blank">Type</a> of the current instance.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_Parse.md">Parse</a></td><td>
Parse string to Version</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Version_ToString.md">ToString</a></td><td>
Convert Version to string
 (Overrides <a href="http://msdn2.microsoft.com/en-us/library/7bxwbwt2" target="_blank">Object.ToString()</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_TryParse.md">TryParse</a></td><td>
Try parse string to Version</td></tr></table>&nbsp;
<a href="#version-class">Back to Top</a>

## Operators
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public operator](media/puboperator.gif "Public operator")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_op_Equality.md">Equality</a></td><td>
Compare two Version's on equality</td></tr><tr><td>![Public operator](media/puboperator.gif "Public operator")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_op_GreaterThan.md">GreaterThan</a></td><td>
Compare two Version's on big</td></tr><tr><td>![Public operator](media/puboperator.gif "Public operator")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_op_GreaterThanOrEqual.md">GreaterThanOrEqual</a></td><td>
Compare two Version's on big or equal</td></tr><tr><td>![Public operator](media/puboperator.gif "Public operator")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_op_Inequality.md">Inequality</a></td><td>
Compare two Version's on not equality</td></tr><tr><td>![Public operator](media/puboperator.gif "Public operator")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_op_LessThan.md">LessThan</a></td><td>
Compare two Version's on less</td></tr><tr><td>![Public operator](media/puboperator.gif "Public operator")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Version_op_LessThanOrEqual.md">LessThanOrEqual</a></td><td>
Compare two Version's on less or equal</td></tr></table>&nbsp;
<a href="#version-class">Back to Top</a>

## See Also


#### Reference
<a href="N_VGlyph.md">VGlyph Namespace</a><br />