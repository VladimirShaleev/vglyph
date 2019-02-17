# Figure.DrawLinetoVertical Method 
Back to <a href="Home.md">Home page</a> 

Draw vertical line from prev point

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public void DrawLinetoVertical(
	Coordinate coordinate,
	float y
)
```

**VB**<br />
``` VB
Public Sub DrawLinetoVertical ( 
	coordinate As Coordinate,
	y As Single
)
```

**F#**<br />
``` F#
member DrawLinetoVertical : 
        coordinate : Coordinate * 
        y : float32 -> unit 

```


#### Parameters
&nbsp;<dl><dt>coordinate</dt><dd>Type: <a href="T_VGlyph_Coordinate.md">VGlyph.Coordinate</a><br />Specifies how to shift *y* from the previous point</dd><dt>y</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/3www918f" target="_blank">System.Single</a><br />New position</dd></dl>

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Figure.md">Figure Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />