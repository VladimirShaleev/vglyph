# Surface.GetPixel Method 
Back to <a href="Home.md">Home page</a> 

Get <a href="T_VGlyph_Color.md">Color</a> of pixel

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public Color GetPixel(
	int x,
	int y
)
```

**VB**<br />
``` VB
Public Function GetPixel ( 
	x As Integer,
	y As Integer
) As Color
```

**F#**<br />
``` F#
member GetPixel : 
        x : int * 
        y : int -> Color 

```


#### Parameters
&nbsp;<dl><dt>x</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />X position</dd><dt>y</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />Y position</dd></dl>

#### Return Value
Type: <a href="T_VGlyph_Color.md">Color</a><br /><a href="T_VGlyph_Color.md">Color</a> of pixel

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />