# Surface Constructor (Format, Int32, Int32, Alignment)
Back to <a href="Home.md">Home page</a> 

Constructs new object <a href="T_VGlyph_Surface.md">Surface</a>

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public Surface(
	Format format,
	int width,
	int height,
	Alignment rowAlignment
)
```

**VB**<br />
``` VB
Public Sub New ( 
	format As Format,
	width As Integer,
	height As Integer,
	rowAlignment As Alignment
)
```

**F#**<br />
``` F#
new : 
        format : Format * 
        width : int * 
        height : int * 
        rowAlignment : Alignment -> Surface
```


#### Parameters
&nbsp;<dl><dt>format</dt><dd>Type: <a href="T_VGlyph_Format.md">VGlyph.Format</a><br />Format of <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>width</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />width of <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>height</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />height of <a href="T_VGlyph_Surface.md">Surface</a></dd><dt>rowAlignment</dt><dd>Type: <a href="T_VGlyph_Alignment.md">VGlyph.Alignment</a><br />Bytes aligment for row <a href="T_VGlyph_Surface.md">Surface</a></dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>*format* is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/8xt94y6e" target="_blank">ArgumentOutOfRangeException</a></td><td>*width* or *height* less than zero</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="Overload_VGlyph_Surface__ctor.md">Surface Overload</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />