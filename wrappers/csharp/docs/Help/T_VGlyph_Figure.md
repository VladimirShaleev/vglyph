# Figure Class
Back to <a href="Home.md">Home page</a> 

Figure


## Inheritance Hierarchy
<a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">System.Object</a><br />&nbsp;&nbsp;VGlyph.Figure<br />
**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public class Figure : IDisposable
```

**VB**<br />
``` VB
Public Class Figure
	Implements IDisposable
```

**F#**<br />
``` F#
type Figure =  
    class
        interface IDisposable
    end
```

The Figure type exposes the following members.


## Constructors
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure__ctor.md">Figure()</a></td><td>
Constructs new object Figure</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Figure__ctor_1.md">Figure(IntPtr)</a></td><td>
Constructs new object Figure for unmanaged handle</td></tr></table>&nbsp;
<a href="#figure-class">Back to Top</a>

## Properties
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Protected property](media/protproperty.gif "Protected property")</td><td><a href="P_VGlyph_Figure_Handle.md">Handle</a></td><td>
Unmanaged handle of vglyph library</td></tr></table>&nbsp;
<a href="#figure-class">Back to Top</a>

## Methods
&nbsp;<table><tr><th></th><th>Name</th><th>Description</th></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_Dispose.md">Dispose()</a></td><td>
Dispose object</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Figure_Dispose_1.md">Dispose(Boolean)</a></td><td>
Dispose object</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawArc.md">DrawArc</a></td><td>
Draw arc</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawClear.md">DrawClear</a></td><td>
Clear path figure</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawClosepath.md">DrawClosepath</a></td><td>
Close path figure</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawCurvetoCubic.md">DrawCurvetoCubic</a></td><td>
Draw curve cubic</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawCurvetoCubicSmooth.md">DrawCurvetoCubicSmooth</a></td><td>
Draw curve cubic smooth</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawCurvetoQuadratic.md">DrawCurvetoQuadratic</a></td><td>
Draw curve quadratic</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawCurvetoQuadraticSmooth.md">DrawCurvetoQuadraticSmooth</a></td><td>
Draw quadratic smooth</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawLineto.md">DrawLineto</a></td><td>
Draw line to point from prev point</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawLinetoHorizontal.md">DrawLinetoHorizontal</a></td><td>
Draw horizontal line from prev point</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawLinetoVertical.md">DrawLinetoVertical</a></td><td>
Draw vertical line from prev point</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="M_VGlyph_Figure_DrawMoveto.md">DrawMoveto</a></td><td>
Move point to</td></tr><tr><td>![Public method](media/pubmethod.gif "Public method")</td><td><a href="http://msdn2.microsoft.com/en-us/library/bsc2ak47" target="_blank">Equals</a></td><td>
Determines whether the specified object is equal to the current object.
 (Inherited from <a href="http://msdn2.microsoft.com/en-us/library/e5kfa45b" target="_blank">Object</a>.)</td></tr><tr><td>![Protected method](media/protmethod.gif "Protected method")</td><td><a href="M_VGlyph_Figure_Finalize.md">Finalize</a></td><td>
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
<a href="#figure-class">Back to Top</a>

## Remarks
Object need for draw primitives

## See Also


#### Reference
<a href="N_VGlyph.md">VGlyph Namespace</a><br />