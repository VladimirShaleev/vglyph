# Surface.Fill Method 
Back to <a href="Home.md">Home page</a> 

Fills the surface with a solid color.

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void Fill(
	int x,
	int y,
	int width,
	int height,
	Color color
)
```

**VB**<br />
``` VB
Public Sub Fill ( 
	x As Integer,
	y As Integer,
	width As Integer,
	height As Integer,
	color As Color
)
```

**F#**<br />
``` F#
member Fill : 
        x : int * 
        y : int * 
        width : int * 
        height : int * 
        color : Color -> unit 

```


#### Parameters
&nbsp;<dl><dt>x</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />Starting horizontal position to fill</dd><dt>y</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />Starting vertical position to fill</dd><dt>width</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />Width to fill</dd><dt>height</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />Height to fill</dd><dt>color</dt><dd>Type: <a href="T_VGlyph_Color.md">VGlyph.Color</a><br />Solid color to fill</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/8xt94y6e" target="_blank">ArgumentOutOfRangeException</a></td><td>Width and height can not be negative</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/27426hcy" target="_blank">ArgumentNullException</a></td><td>Color is null</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />