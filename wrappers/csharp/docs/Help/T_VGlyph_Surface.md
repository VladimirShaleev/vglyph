# Surface Class
Back to <a href="Home.md">Home page</a> 

Surface


## Inheritance Hierarchy
<a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">System.Object</a><br />&nbsp;&nbsp;VGlyph.Surface<br />
**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public class Surface : IDisposable
```

**VB**<br />
``` VB
Public Class Surface
	Implements IDisposable
```

**F#**<br />
``` F#
type Surface =  
    class
        interface IDisposable
    end
```

The Surface type exposes the following members.


## Constructors
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Surface__ctor.md">Surface(IntPtr)</a></td><td>
Constructs new object Surface for unmanaged handle</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Surface__ctor_1.md">Surface(Format, Int32, Int32, Alignment)</a></td><td>
Constructs new object Surface</td></tr></table>&nbsp;
<a href="#surface-class">Back to Top</a>

## Properties
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Surface_Format.md">Format</a></td><td>
Get <a href="P_VGlyph_Surface_Format.md">Format</a> of surface</td></tr><tr><td>![Protected property](media/protproperty.gif "Protected property")</td><td><a href="P_VGlyph_Surface_Handle.md">Handle</a></td><td>
Unmanaged handle of vglyph library</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Surface_Height.md">Height</a></td><td>
Get height of row surface</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Surface_Multisampling.md">Multisampling</a></td><td>
Number of samples per pixel</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Surface_Pitch.md">Pitch</a></td><td>
Get pitch of row surface</td></tr><tr><td>![Public property](media/pubproperty.gif "Public property")</td><td><a href="P_VGlyph_Surface_Width.md">Width</a></td><td>
Get width of row surface</td></tr></table>&nbsp;
<a href="#surface-class">Back to Top</a>

## Methods
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Surface_CaptureStream.md">CaptureStream</a></td><td>
Capture stream bytes of surface</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Surface_Dispose.md">Dispose()</a></td><td>
Dispose object</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Surface_Dispose_1.md">Dispose(Boolean)</a></td><td>
Dispose object</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Surface_DrawGlyph.md">DrawGlyph</a></td><td>
Draw glyph on surface</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/bsc2ak47" target="_blank">Equals</a></td><td>
Determines whether the specified object is equal to the current object.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Surface_Fill.md">Fill</a></td><td>
Fills the surface with a solid color.</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Surface_Finalize.md">Finalize</a></td><td>
Free resources and perform other cleanup operations
 (Overrides <a href="http://msdn2.microsoft.com/en-us/library/4k87zsw7" target="_blank">Object.Finalize()</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")![Static member](media/static.gif "Static member")</td><td><a href="M_VGlyph_Surface_GetDataSize.md">GetDataSize</a></td><td>
Compute size of data surface in bytes</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/zdee4b3y" target="_blank">GetHashCode</a></td><td>
Serves as the default hash function.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Surface_GetPixel.md">GetPixel</a></td><td>
Get <a href="T_VGlyph_Color.md">Color</a> of pixel</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/dfwy45w9" target="_blank">GetType</a></td><td>
Gets the <a href="http://msdn2.microsoft.com/en-us/library/42892f65" target="_blank">Type</a> of the current instance.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/57ctke0a" target="_blank">MemberwiseClone</a></td><td>
Creates a shallow copy of the current <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Surface_SetPixel.md">SetPixel</a></td><td>
Set <a href="T_VGlyph_Color.md">Color</a> of pixel</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/7bxwbwt2" target="_blank">ToString</a></td><td>
Returns a string that represents the current object.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr></table>&nbsp;
<a href="#surface-class">Back to Top</a>

## See Also


#### Reference
<a href="N_VGlyph.md">VGlyph Namespace</a><br />