# Surface.CaptureStream Method 
Back to <a href="Home.md">Home page</a> 

Capture stream bytes of surface

**Namespace:**&nbsp;<a href="N_VGlyph.md">VGlyph</a><br />**Assembly:**&nbsp;VGlyph.Wrapper (in VGlyph.Wrapper.dll) Version: 1.0.0

## Syntax

**C#**<br />
``` C#
public Stream CaptureStream(
	int x,
	int y,
	int width,
	int height
)
```

**VB**<br />
``` VB
Public Function CaptureStream ( 
	x As Integer,
	y As Integer,
	width As Integer,
	height As Integer
) As Stream
```

**F#**<br />
``` F#
member CaptureStream : 
        x : int * 
        y : int * 
        width : int * 
        height : int -> Stream 

```


#### Parameters
&nbsp;<dl><dt>x</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />left bound to lock</dd><dt>y</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />top bound to lock</dd><dt>width</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />width lock</dd><dt>height</dt><dd>Type: <a href="http://msdn2.microsoft.com/en-us/library/td2s409d" target="_blank">System.Int32</a><br />height lock</dd></dl>

#### Return Value
Type: <a href="http://msdn2.microsoft.com/en-us/library/8f86tw9e" target="_blank">Stream</a><br />Stream bytes

## Exceptions
&nbsp;<table><tr><th>Exception</th><th>Condition</th></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/8xt94y6e" target="_blank">ArgumentOutOfRangeException</a></td><td>*width* or *height* less than zero</td></tr><tr><td><a href="http://msdn2.microsoft.com/en-us/library/y31w16ca" target="_blank">ObjectDisposedException</a></td><td>Object disposed</td></tr></table>

## See Also


#### Reference
<a href="T_VGlyph_Surface.md">Surface Class</a><br /><a href="N_VGlyph.md">VGlyph Namespace</a><br />