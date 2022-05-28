# MFF - Manix File Fragmenter
- Manix File Fragmenter (MFF) is a very simple file fragmenter/defragmenter program.
- It is completely written in C Language using the C Standard Library.
- To generate de executable by yourself, simply run the file *build.bat* (Windows Only)

# Usage (Windows' command line only)
<dl>
	<dt><pre>mff &lt;file&gt; frag &lt;fragment size&gt;</pre></dt>
	<dd>Fragment 'file' into pieces of <code>fragment size</code> bytes</dd>
	<dt><pre>mff &lt;file&gt; defrag</pre></dt>
	<dd>Gather all the fragments in the current directory into <code>file</code></dd>
</dl>
