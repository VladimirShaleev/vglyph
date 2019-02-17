# Surface.GetDataSize Method 
Back to <a href="Home.md">Home page</a> 

Compute size of data surface in bytes

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public static int GetDataSize(
	Format format,
	int width,
	int height,
	Alignment rowAlignment
)
```

**VB**<br />
``` VB
Public Shared Function GetDataSize ( 
	format As Format,
	width As Integer,
	height As Integer,
	rowAlignment As Alignment
) As Integer
```

**F#**<br />
``` F#
static member GetDataSize : 
        format : Format * 
        width : int * 
        height : int * 
        rowAlignment : Alignment -> int 

```


#### Parameters
&nbsp;<dl><dt>format</dt><dd>Type: <a href="T_VGlyph_Format.md">VGlyph.Format</a><br />Format of <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>width</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />width of <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>height</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />height of <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>rowAlignment</dt><dd>Type: <a href="T_VGlyph_Alignment.md">VGlyph.Alignment</a><br />Bytes aligment for row <a href="T_VGlyph_Surface.md">Surface</a></dd></dl>

#### Return Value
Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">Int32</a><br />Size of data in bytes

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>*format* is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/8xt94y6e" target="_blank">ArgumentOutOfRangeException</a></td><td>*width* or *height* less than zero</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />