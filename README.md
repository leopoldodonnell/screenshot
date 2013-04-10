# Screenshot

This utility takes a screenshot of all of a user's active displays on Mac OS X and writes a JPG file
where they are displayed in their relative positions.

The underlying code was written to be included in a larger project and is being provided as is for all.
Its a good source to learn how deal with screenshots on Max OS X in general and should save folks hours
of messing around within the Max Developer Library.


## Building the Project

This project uses a simple Makefile that should work just fine if you've installed Xcode. Just...

    > make
    
and it will generate screenshot and screenshot.dylib. The dynamic library is offered for use in other projects,
but is not needed to run the program.

It has not been verified on older Max OS X versions, but uses frameworks that have been around for quite a few years.

## Usage:

Screenshot will generate the file specified with a type that depends on the file extension. Supported types are:

* jpg : JPEG 2000 (supports compression)
* gif : supports compression
* png : No compression
* bmp : No compression
* tiff : No Compression

To generate a JPEG file...

    > ./screenshot my_screenshot.jpg

You can also specify compression for file types that support compression as a value between 0.0 and 1.0

    > ./screenshot -c 0.5 my_screenshot.jpg


That's it!

## Installation

After you've built it, just copy it to a directory in your path and you are good to go.

## License

This project rocks and uses MIT-LICENSE. Copyright 2013 Leopold O'Donnell
