# LenSplit
A simple command-line tool to split a file in smaller chunks. 

**Language: C**

**Start: 2006**

## Why
A few lines as proof of concept of a trivial file splitter.

## Example
Split a file in n chunks of 1000 bytes:

```
lsplit -b 1000 myfile.bin

dir /b myfile.bin.l*
myfile.bin.l0
myfile.bin.l1
...
```

Join them back:

```
lsplit -j myfile.bin
```