# Format Class
Back to <a href="Home.md">Home page</a> 

Format of <a href="T_VGlyph_Surface.md">Surface</a>


## Inheritance Hierarchy
<a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">System.Object</a><br />&nbsp;&nbsp;VGlyph.Format<br />&nbsp;&nbsp;&nbsp;&nbsp;<a href="T_VGlyph_RgbaUintFormat.md">VGlyph.RgbaUintFormat</a><br />
**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public abstract class Format : IDisposable
```

**VB**<br />
``` VB
Public MustInherit Class Format
	Implements IDisposable
```

**F#**<br />
``` F#
[<AbstractClassAttribute>]
type Format =  
    class
        interface IDisposable
    end
```

The Format type exposes the following members.


## Constructors
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Format__ctor.md">Format</a></td><td>
Constructs new object Format for unmanaged handle</td></tr></table>&nbsp;
<a href="#format-class">Back to Top</a>

## Properties
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Format_BitsPerPixel.md">BitsPerPixel</a></td><td>
Get bits per pixel</td></tr><tr><td>![Protected property](media/protproperty.gif "Protected property")</td><td><a href="P_VGlyph_Format_Handle.md">Handle</a></td><td>
Unmanaged handle of vglyph library</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Format_PackagingBytes.md">PackagingBytes</a></td><td>
Get packaging bytes</td></tr></table>&nbsp;
<a href="#format-class">Back to Top</a>

## Methods
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Format_Dispose.md">Dispose()</a></td><td>
Dispose object</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Format_Dispose_1.md">Dispose(Boolean)</a></td><td>
Dispose object</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/bsc2ak47" target="_blank">Equals</a></td><td>
Determines whether the specified object is equal to the current object.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Format_Finalize.md">Finalize</a></td><td>
Free resources and perform other cleanup operations
 (Overrides <a href="http://msdn2.microsoft.com/en-us/library/4k87zsw7" target="_blank">Object.Finalize()</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/zdee4b3y" target="_blank">GetHashCode</a></td><td>
Serves as the default hash function.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/dfwy45w9" target="_blank">GetType</a></td><td>
Gets the <a href="http://msdn2.microsoft.com/en-us/library/42892f65" target="_blank">Type</a> of the current instance.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/57ctke0a" target="_blank">MemberwiseClone</a></td><td>
Creates a shallow copy of the current <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/7bxwbwt2" target="_blank">ToString</a></td><td>
Returns a string that represents the current object.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr></table>&nbsp;
<a href="#format-class">Back to Top</a>

## See Also


#### Reference
<a href="N_VGlyph.md">VGlyph Namespace</a><br />